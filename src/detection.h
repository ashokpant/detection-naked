#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "opencv2/core.hpp"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "objectDetection.hpp"
//
// Created by ashok on 8/17/15.
//

using namespace std;
using namespace cv;
namespace dv {
	class Detector{
	public:
		Detector();
		~ Detector(){}
		Detector(const string cascadeFile, int imgNewW = 0, int imgNewH = 0, double scale = 1.1, int minNeigours = 3, int flags = 0, Size minWH = Size(), int padW = 0, int padH = 0);

		int Detect(Mat& img, std::vector<Rect>& objects);
		int Detect(const string imageName, std::vector<Rect>& objects);
		void detectAndDisplay(Mat& img, double imgScale);

		void setImgNewWidth(int imgNewW_) {
			Detector::imgNewW_ = imgNewW_;
		}

		void setImgNewHeight(int imgNewH_) {
			Detector::imgNewH_ = imgNewH_;
		}

		void setPadWidth(int padW_) {
			Detector::padW_ = padW_;
		}

		void setPadHeight(int padH_) {
			Detector::padH_ = padH_;
		}

		void setFlags(int flags_) {
			Detector::flags_ = flags_;
		}

		void setMinWH(const Size &minWH_) {
			Detector::minWH_ = minWH_;
		}

		void setScale(double scale_) {
			Detector::scale_ = scale_;
		}

		void setMinNeighbours(int minNeighbours_) {
			Detector::minNeighbours_ = minNeighbours_;
		}

		void setCascade(const CascadeClassifier &cascade_) {
			Detector::cascade_ = cascade_;
		}

	private:
		int detect(Mat& img, std::vector<Rect>& objects);
	private:
		CascadeClassifier cascade_;
		int imgNewW_, imgNewH_;
		int flags_;
		Size minWH_;
		double scale_;
		int minNeighbours_;
		int padW_, padH_;
		const string cascadeFile_;

		void intiCascade(const string cascadeFile, int imgNewW = 0, int imgNewH = 0, double scale = 1.1, int minNeigours = 3, int flags = 0, Size minWH = Size(), int padW = 0, int padH = 0);
	};
}