<!---
Title:       |  OpenCV haar cascade detector is naked!!
Subtitle:    |  Show internals of OpenCV detector.
Project:     |  detection-naked
Author:      Ashok Kumar Pant 
Affiliation: Tribhuvan University, Kathmandu 
Web:         http://ashokpant.github.io
Date:        August 18, 2016 
-->

# **OpenCV detector is naked!!**
Displays internal stages of detection.

## Dependencies
* [OpenCV](http://opencv.org/)
* Other: sudo apt-get install libgflags-dev libgoogle-glog-dev

## Compilation
	$ git clone https://github.com/ashokpant/detection-naked.git
	$ cd detection-naked
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make 
	
## Uses Example
	$ cd detection-naked/build
	$ ./detection_demo --detector=../data/haarcascade_frontalface_alt2.xml --image=../images/ashok.jpg -minWH=300x300 --parallel=false --naked=true --group=true --minNeighbour=1
	
	Options:
	--naked <detection mode (true/false), default true>
	--dh <draw haar features (true/false), default true>
	--parallel <run detector in parallel (true/false), default true>
	--group <group final results (true/false), default true>
	
	--image <input image>
	--video <input video>
	--camera <input camera id, default 0>
	
	--detector <cascade detector>
	--minWH <detector minimum widthxheight>
	--minNeighbour <minimum number of neighbours to group the matched patches>

![](https://github.com/ashokpant/text-on-image/blob/master/demo/all-stages.png)
	
## Other Examples

![Haar Features](https://github.com/ashokpant/detection-naked/blob/master/demo/detection.gif)

