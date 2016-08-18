#include <opencv2/videoio.hpp>
#include <glog/logging.h>
#include "detection.h"
#include "preprocessing.h"
#include "utility.h"
#include "config.hpp"

using namespace std;
DEFINE_string(image,"","Optional: Input image");
DEFINE_string(video,"","Optional: Input video");
DEFINE_int32(camera,0, "Optional: Input camera");

DEFINE_string(detector, "../data/haarcascade_frontalface_alt2.xml", "Cascade detector");
DEFINE_int32(w, 0, "Optional: scaled width of image");
DEFINE_int32(h, 0, "Optional: scaled height of image");
DEFINE_int32(padW, 0, "Optional: detector width padding");
DEFINE_int32(padH, 0, "Optional: detector height padding");
DEFINE_string(minWH, "0x0", "Optional: detector minimum width x height");
DEFINE_int32(minNeighbour,2, "Optional: detector minimum neighbourhood");
DEFINE_double(dScale, 1.1, "Optional: detector scaling factor");
DEFINE_bool(biggest, false, "Optional: find biggest object");

DEFINE_bool(naked,true,"Naked the detector steps");
DEFINE_bool(dh,true,"Draw Haar features, works only if naked is true");
DEFINE_bool(parallel,true,"Run detector in parallel, works only if naked is true");
DEFINE_bool(group,true,"Group the detected patches");

int displayDetections(dv::Detector &detector, Mat &img) {
    vector<Rect> objects;
    detector.Detect(img, objects);
    for (vector<cv::Rect>::const_iterator r = objects.begin(); r != objects.end(); r++) {
        rectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(0, 255, 255), 2, 8, 0);

        //display text on image
        std::stringstream ht;
        ht << r->height;
        string h = ht.str();
        std::stringstream wd;
        wd << r->width;
        string w = wd.str();
        string text = h + " x " + w;
        putText(img, text, cvPoint(r->x + 10, r->y + r->height + 20), FONT_HERSHEY_PLAIN, 1,
                CV_RGB(192, 192, 192));
    }
    imshow("Final Results",img);
    return 0;
}

int imageMode(dv::Detector &detector, string imageName) {
    Mat img = imread(imageName);
    if (img.empty()) {
        cout << "Image not found." << endl;
        return -1;
    }
    imshow("Input", img );
    cvWaitKey(0);
    printf("Image Size: %d x %d\n",img.rows,img.cols);
    displayDetections(detector, img);
    return 0;
}
int videoMode(dv::Detector &detector, string videoName) {
    VideoCapture capture;
    Mat frame;

    capture.open(videoName);
    if (capture.isOpened()) {
        capture.read(frame);
        printf("Video Size: %d x %d\n",frame.rows,frame.cols);
        for (; ;) {
            capture.read(frame);
            if (!frame.empty()) {
                imshow("Input", frame );
                displayDetections(detector, frame);
            }
            else {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if ((char) c == 'q') { break; }

        }
    }
    return 0;
}

int cameraMode(dv::Detector &detector, int inputCamera) {
    VideoCapture capture;
    Mat frame;
    capture.open(inputCamera);
    if (capture.isOpened()) {
        capture.read(frame);
        printf("Video Size: %d x %d\n",frame.rows,frame.cols);
        for (; ;) {
            capture.read(frame);
            if (!frame.empty()) {
                imshow("Input", frame );
                displayDetections(detector, frame);
            }
            else {
                printf(" --(!) No captured frame -- Break!\n");
                break;
            }

            int c = waitKey(10);
            if ((char) c == 'q') { break; }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    //Print output to console (while still logging).
    FLAGS_alsologtostderr = 1;
    //google::SetLogDestination(google::INFO,"log/debuglog.INFO");
    //Uses message.
    google::SetUsageMessage("Uses\n"
                                    "image          Input image.\n"
                                    "video          Input video.\n"
                                    "camera         Input camera id, default 0.\n"
                                    "detector       Cascade detector\n"
                                    "naked          Show detection internals\n"
                                    "group          Group matched patches\n");
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    if (FLAGS_detector.size() == 0) {
        google::ShowUsageWithFlags(argv[0]);
        return 0;
    }

    Config::DETECTOR = FLAGS_detector;
    Config::NAKED = FLAGS_naked;
    Config::DRAW_HAAR_FEATURES = FLAGS_dh;
    Config::RUN_DETECTOR_IN_PARALLEL = FLAGS_parallel;

    if(!FLAGS_group){
        FLAGS_minNeighbour = 0;
    }

    Size minWH = dv::Utils::parseString(FLAGS_minWH);
    dv::Detector detector(FLAGS_detector, FLAGS_w, FLAGS_h, FLAGS_dScale, FLAGS_minNeighbour, 0, minWH, FLAGS_padW, FLAGS_padH);

    if (FLAGS_image.size() > 0) {
        cout << "Input image: " << FLAGS_image << endl;
        imageMode(detector, FLAGS_image);
    } else if (FLAGS_video.size() > 0) {
        cout << "Input video: " << FLAGS_video << endl;
        videoMode(detector, FLAGS_video);
    } else {
        cout << "Input camera id: " << FLAGS_camera << endl;
        cameraMode(detector, FLAGS_camera);
    }
    cvWaitKey(0);
    return 0;
}