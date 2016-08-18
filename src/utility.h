#ifndef UTILITY_H
#define UTILITY_H

#include <time.h>
#include<sys/types.h>
#include<sys/types.h>
#include<fcntl.h>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;
namespace dv {
    class Utils {
    public:
        static  double tic() {
            return (double) cvGetTickCount();
        }

        static   double toc(double t) {
            double t1;
            t1 = (double) cvGetTickCount() - t;
            return (t1 / ((double) cvGetTickFrequency() * 1000.));
        }

        static  string getDynamicImageFileName() {
            char s[30];
            int fp;
            size_t i;
            struct tm tim;
            time_t now;
            now = time(NULL);
            tim = *(localtime(&now));
            i = strftime(s, 30, "%Y_%m_%d_%H_%M_%S", &tim);
            char index[10];
            char folder[40] = "Faces\\";
            std::sprintf(index, "%d.jpg", rand());
            std::strcat(folder, s);
            std::strcat(folder, index);
            return folder;
        }

        static  inline std::string &ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }

        static  inline std::string &rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }

        static  inline std::string &trim(std::string &s) {
            return ltrim(rtrim(s));
        }

        static  void strSplit(vector<string> &tokens, string &text, char sep) {
            int start = 0, end = 0;
            while ((end = text.find(sep, start)) != string::npos) {
                string str = text.substr(start, end - start);
                str = trim(str);
                tokens.push_back(str);
                start = end + 1;
            }
            string str = text.substr(start);
            str = trim(str);
            tokens.push_back(str);
        }

        static  Size parseString(string wxh) {
            int w = 0;
            int h = 0;
            if (strcmp(wxh.c_str(), "0x0") != 0) {
                vector<string> tokens;
                strSplit(tokens, wxh, 'x');

                if (tokens.size() != 2) {
                    cout << "Invalid width x height format" << endl;
                } else {
                    w = stoi(tokens[0]);
                    h = stoi(tokens[1]);
                }
            }
            return Size(w, h);
        }

        static  int imresize(Mat &src, Mat &dst, int width, int height, double &wScale, double &hScale) {
            wScale = 1;
            hScale = 1;

            if (width <= 0 && height <= 0) {
                src.copyTo(dst);
                return 1;
            }

            if (width > 0) {
                wScale = (double) src.cols / width;
            }
            if (height > 0) {
                hScale = (double) src.rows / height;
            }

            if (wScale != 1 && hScale == 1) {
                width = (int) (src.cols / wScale);
                height = (int) (src.rows / wScale);
                hScale = wScale;
            } else if (wScale == 1 && hScale != 1) {
                width = (int) (src.cols / hScale);
                height = (int) (src.rows / hScale);
                wScale = hScale;
            } else {
                width = (int) (src.cols / wScale);
                height = (int) (src.rows / hScale);
            }

            Size size(width, height);
            resize(src, dst, size);
            return 1;
        }

        static  int imresize(Mat &src, Mat &dst, int width, int height) {
            double wScale = 1;
            double hScale = 1;
            return imresize(src, dst, width, height, wScale, hScale);
        }
    };
}

#endif