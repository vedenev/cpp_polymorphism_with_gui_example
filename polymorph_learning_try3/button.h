#pragma once
#include "view.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
//https://stackoverflow.com/questions/2298242/callback-functions-in-c
typedef void (*CallbackType)();
class button :
	public view
{
private:
	int x_offset;
	int y_offset;
	int width;
	int height;
	Mat image_up;
	Mat image_down;
	int state;
	int x_offset_2;
	int y_offset_2;
	CallbackType callback;
public:
	button(Mat& image, int x_offset_inp, int y_offset_inp, int width_inp, int height_inp, Scalar color_bgr_inp, string text_inp, CallbackType callback_inp);
	void check_mouse(Mat& image, int x, int y, int event_no);
	~button();
};

