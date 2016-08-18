#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <iostream>
#include "vector"
#include "string"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include<opencv2/opencv.hpp>

namespace dv{
	class Preprocessing {
	public:
		cv::Mat convertColor(cv::Mat &src, std::string color) {
			cv::Mat dst;
			if (color.compare("rgb2gray") == 0) {
				cv::cvtColor(src, dst, CV_RGB2GRAY);
				return dst;
			}
			else if (color.compare("rgb2hsv") == 0) {
				cv::cvtColor(src, dst, CV_RGB2HSV);
				return dst;
			}
			else if (color.compare("rgb2ycbcr") == 0) {
				cv::cvtColor(src, dst, CV_RGB2YCrCb);
				return dst;
			}
			else if (color.compare("rgb2bgr") == 0) {
				cvtColor(src, dst, CV_RGB2BGR);
				return dst;
			}
			else if (color.compare("bgr2rgb") == 0) {
				cv::cvtColor(src, dst, CV_BGR2RGB);
				return dst;
			}
			else if (color.compare("hsv2rgb") == 0) {
				cv::cvtColor(src, dst, CV_HSV2RGB);
				return dst;
			}
			else if (color.compare("gray2rgb") == 0) {
				cv::cvtColor(src, dst, CV_GRAY2RGB);
				return dst;
			} else {
				return src;
			}
		}

		cv::Mat im2bw(cv::Mat src) {
			cv::Mat bwImage;
			// Apply a fixed-level threshold to each pixel
			//threshold(src,bwImage,0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);

			// Apply an adaptive threshold to a grayscale image
			cv::adaptiveThreshold(src, bwImage, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 8);
			return bwImage;
		}

		cv::Mat histeq(cv::Mat src) {
			cv::Mat dst;
			cv::equalizeHist(src, dst);
			return dst;
		}

		cv::Mat imresize(cv::Mat src, int width, int height) {
			cv::Mat dst;
			cv::resize(src, dst, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);
			return dst;
		}

		cv::Mat imresize(cv::Mat src, double scale) {
			cv::Mat dst;
			cv::resize(src, dst, cv::Size(), scale, scale, cv::INTER_CUBIC);
			return dst;
		}
	};
}
#endif