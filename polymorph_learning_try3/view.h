#pragma once
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
class view
{
public:
	virtual void check_mouse(Mat& image, int x, int y, int event_no) = 0;
	virtual ~view() {};
};

