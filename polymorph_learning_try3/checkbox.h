#pragma once
#include "view.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
//https://stackoverflow.com/questions/2298242/callback-functions-in-c
typedef void (*CallbackType2)(int);
class checkbox :
	public view
{
private:
	int x_offset;
	int y_offset;
	int width;
	int height;
	Mat image_checked;
	Mat image_unchecked;
	int state;
	int x_offset_2;
	int y_offset_2;
	CallbackType2 callback;
public:
	checkbox(Mat& image, int x_offset_inp, int y_offset_inp, int width_inp, int height_inp, Scalar color_bgr_inp, string text_inp, CallbackType2 callback_inp);
	void check_mouse(Mat& image, int x, int y, int event_no);
	~checkbox();
};

