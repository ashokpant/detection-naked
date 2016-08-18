#include "detection.h"
#include "utility.h"
#include "preprocessing.h"
#include "config.hpp"

using namespace cv;
using namespace std;

namespace dv {
	Detector::Detector() : cascadeFile_(Config::DETECTOR) {
		this->intiCascade(cascadeFile_);
	}

	Detector::Detector(const string cascadeFile, int imgNewW, int imgNewH, double scale, int minNeighbours, int flags, Size minWH, int padW,
					   int padH):cascadeFile_(cascadeFile) {
		this->intiCascade(cascadeFile,imgNewW,imgNewH,scale,minNeighbours,flags,minWH,padW,padH);
	}

	int Detector::Detect(const string imageName, vector<Rect>& objects){
		Mat img = imread(imageName);
		if (img.empty()) {
			cerr<<"Invalid image: "<<imageName;
			return -1;
		}
		return Detect(img, objects);
	}

	int Detector::Detect(Mat& img, vector<Rect>& objects){
		int status = detect(img, objects);
		return status;
	}
	int Detector::detect(Mat& img, vector<Rect>& objects) {
		std::vector<Rect> objs;
		Mat image;
		double wScale = 1,hScale = 1;

		if(imgNewW_<0||imgNewH_<0){
			imgNewW_ = 0;
			imgNewH_ = 0;
		}

		if(imgNewW_>0||imgNewH_>0){
			Utils::imresize(img, image,imgNewW_,imgNewH_,wScale,hScale);
		}else{
			image = img;
		}

		cascade_.detectMultiScale(image, objs, scale_, minNeighbours_, flags_, minWH_ );

		for(size_t i = 0; i < objs.size(); i++ ){
			Rect rect;
			if(hScale != 1 || wScale != 1){
				rect = Rect((objs.at(i).x - padW_) < 0 ? 0 : objs.at(i).x - padW_,
							(objs.at(i).y - padH_) < 0 ? 0 : objs.at(i).y - padH_,
							(objs.at(i).width + padW_) > image.cols ? image.cols : objs.at(i).width + padW_,
							(objs.at(i).height + padH_) > image.rows ? image.rows : objs.at(i).height + padH_);
				rect.x = (int) (rect.x * wScale);
				rect.y = (int) (rect.y * hScale);
				rect.width = (int) (rect.width * wScale);
				rect.height = (int) (rect.height * hScale);
			}else{
				rect = Rect(objs.at(i).x, objs.at(i).y, objs.at(i).width, objs.at(i).height);
			}
			objects.push_back(rect);
		}
		return 1;
	}

	void Detector:: detectAndDisplay(Mat& img, double imgScale){
		std::vector<Rect> faces;
		string winname = "Input Image";
		cvNamedWindow(winname.c_str(),CV_WINDOW_AUTOSIZE);
		imshow(winname,img);
		cascade_.detectMultiScale(img, faces, scale_, minNeighbours_, flags_, minWH_);
		for( vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++) {
			rectangle(img, cvPoint((int) (r->x / imgScale), (int) (r->y / imgScale)), cvPoint(
					(int) (r->x / imgScale + r->width / imgScale), (int) (r->y / imgScale + r->height / imgScale)), Scalar(255, 0, 0) , 2, 8, 0);
		}
		imshow(winname, img );
	}

	void Detector::intiCascade(const string cascadeFile, int imgNewW, int imgNewH, double scale, int minNeighbours, int flags, Size minWH, int padW, int padH) {
		if(!cascade_.load(cascadeFile)) {
			cerr << "ERROR: Could not load classifier cascade." << endl;
		}
		imgNewW_ = imgNewW;
		imgNewH_ = imgNewH;
		scale_ = scale;
		minNeighbours_ = minNeighbours;
		flags_ = flags|CV_HAAR_DO_CANNY_PRUNING;
		padW_ = padW;
		padH_ = padH;
		minWH_ = minWH;
	}
}