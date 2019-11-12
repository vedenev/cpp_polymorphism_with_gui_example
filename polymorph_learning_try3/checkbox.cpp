#include "checkbox.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
typedef void (*CallbackType2)(int);
const string WINDOW_NAME = "Test Window";

checkbox::checkbox(Mat& image, int x_offset_inp, int y_offset_inp, int width_inp, int height_inp, Scalar color_bgr_inp, string text_inp, CallbackType2 callback_inp)
{
	x_offset = x_offset_inp;
	y_offset = y_offset_inp;
	width = width_inp;
	height = height_inp;
	callback = callback_inp;
	state = 0;
	x_offset_2 = x_offset + (width - 1);
	y_offset_2 = y_offset + (height - 1);

	image_unchecked = Mat::zeros(height, width, CV_8UC3);

	const int n_points_tmp = 4;
	const int lineType = LINE_8;
	Point points_tmp[1][n_points_tmp];
	points_tmp[0][0] = Point(0, 0);
	points_tmp[0][1] = Point(0, 0);
	points_tmp[0][2] = Point(0, 0);
	points_tmp[0][3] = Point(0, 0);
	const Point* points_tmp2[1] = { points_tmp[0] };
	int n_points_tmp2[] = { n_points_tmp };

	int edge_size = 3;
	float scale_factor_tmp = 0.5;
	int square_size = (int)(scale_factor_tmp * height);
	int x1_square = height / 2 - square_size / 2;
	int x2_square = x1_square + square_size - 1;
	int y1_square = height / 2 - square_size / 2;
	int y2_square = y1_square + square_size - 1;
	int x1_square_inside = x1_square + edge_size;
	int x2_square_inside = x2_square - edge_size;
	int y1_square_inside = y1_square + edge_size;
	int y2_square_inside = y2_square - edge_size;


	

	Scalar color_bgr_center;
	Scalar color_bgr_1;
	Scalar color_bgr_2;
	Scalar color_bgr_3;
	Scalar color_bgr_4;

	color_bgr_center = Scalar(6 * (color_bgr_inp[0] / 8), 6 * (color_bgr_inp[1] / 8), 6 * (color_bgr_inp[2] / 8));
	color_bgr_4 = Scalar(color_bgr_inp[0], color_bgr_inp[1], color_bgr_inp[2]);
	color_bgr_3 = Scalar(7 * (color_bgr_inp[0] / 8), 7 * (color_bgr_inp[1] / 8), 7 * (color_bgr_inp[2] / 8));
	color_bgr_2 = Scalar(5 * (color_bgr_inp[0] / 8), 5 * (color_bgr_inp[1] / 8), 5 * (color_bgr_inp[2] / 8));
	color_bgr_1 = Scalar(4 * (color_bgr_inp[0] / 8), 4 * (color_bgr_inp[1] / 8), 4 * (color_bgr_inp[2] / 8));


	
	points_tmp[0][0] = Point(0, 0);
	points_tmp[0][1] = Point(width, 0);
	points_tmp[0][2] = Point(width, height);
	points_tmp[0][3] = Point(0, height);
	points_tmp2[0] = points_tmp[0];

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		color_bgr_center,
		lineType);

	
	points_tmp[0][0] = Point(x1_square, y1_square);
	points_tmp[0][1] = Point(x2_square, y1_square);
	points_tmp[0][2] = Point(x2_square_inside, y1_square_inside);
	points_tmp[0][3] = Point(x1_square_inside, y1_square_inside);

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		color_bgr_1,
		lineType);

	points_tmp[0][0] = Point(x2_square, y1_square);
	points_tmp[0][1] = Point(x2_square_inside, y1_square_inside);
	points_tmp[0][2] = Point(x2_square_inside, y2_square_inside);
	points_tmp[0][3] = Point(x2_square, y2_square);

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		color_bgr_3,
		lineType);

	points_tmp[0][0] = Point(x2_square, y2_square);
	points_tmp[0][1] = Point(x2_square_inside, y2_square_inside);
	points_tmp[0][2] = Point(x1_square_inside, y2_square_inside);
	points_tmp[0][3] = Point(x1_square, y2_square);

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		color_bgr_4,
		lineType);

	points_tmp[0][0] = Point(x1_square, y1_square);
	points_tmp[0][1] = Point(x1_square_inside, y1_square_inside);
	points_tmp[0][2] = Point(x1_square_inside, y2_square_inside);
	points_tmp[0][3] = Point(x1_square, y2_square);

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		color_bgr_2,
		lineType);

	points_tmp[0][0] = Point(x1_square_inside, y1_square_inside);
	points_tmp[0][1] = Point(x2_square_inside, y1_square_inside);
	points_tmp[0][2] = Point(x2_square_inside, y2_square_inside);
	points_tmp[0][3] = Point(x1_square_inside, y2_square_inside);

	fillPoly(image_unchecked,
		points_tmp2,
		n_points_tmp2,
		1,
		Scalar(255, 255, 255),
		lineType);

	int thickness_tmp = 1;
	int baseline = -1;

	double font_scale_tmp = 1.0;

	Size text_size_tmp = getTextSize(text_inp, FONT_HERSHEY_COMPLEX_SMALL,
		font_scale_tmp, thickness_tmp, &baseline);

	double width_normalized_tmp = ((double)text_size_tmp.width) / (width - height);
	double height_normalized_tmp = ((double)text_size_tmp.height) / (height);
	if (width_normalized_tmp > height_normalized_tmp)
	{
		font_scale_tmp = font_scale_tmp / width_normalized_tmp;
	}
	else
	{
		font_scale_tmp = font_scale_tmp / height_normalized_tmp;
	}
	font_scale_tmp = font_scale_tmp * 0.9;

	Size text_size = getTextSize(text_inp, FONT_HERSHEY_COMPLEX_SMALL,
		font_scale_tmp, thickness_tmp, &baseline);
	Point textOrg(height - height / 10 + (width - height) / 2 - text_size.width / 2,
		height / 2 + text_size.height / 2);
	putText(image_unchecked, text_inp, textOrg,
		FONT_HERSHEY_COMPLEX_SMALL, font_scale_tmp, cvScalar(0, 0, 0), 1, CV_AA);

	image_checked = image_unchecked.clone();

	// check:
	int check_margin = 3;
	int y1_check = y1_square_inside + check_margin;
	int y2_check = y2_square_inside - check_margin;
	int ym_check = (y1_check + y2_check) / 2;
	int x1_check = x1_square_inside + check_margin;
	int x2_check = x2_square_inside - check_margin;
	int xm_check = (x1_check + x2_check) / 2;
	int thickness_ckeck = 2;
	int lineType_check = LINE_AA;
	line(image_checked,
		Point(x1_check, ym_check), Point(xm_check, y2_check),
		Scalar(0, 0, 0),
		thickness_ckeck,
		lineType_check);

	line(image_checked,
		Point(xm_check, y2_check), Point(x2_check, y1_check),
		Scalar(0, 0, 0),
		thickness_ckeck,
		lineType_check);

	Mat image_roi = image(Rect(x_offset, y_offset, image_unchecked.cols, image_unchecked.rows));
	image_unchecked.copyTo(image_roi);
	imshow(WINDOW_NAME, image);

}
void checkbox::check_mouse(Mat& image, int x, int y, int event_no)
{
	
	int state_old = state;

	if ((event_no == EVENT_LBUTTONDOWN || event_no == EVENT_LBUTTONDBLCLK) && ((x_offset <= x && x <= x_offset_2) && (y_offset <= y && y <= y_offset_2)))
	{
		if (state == 0)
		{
			state = 1;
			callback(state);
		}
		else
		{
			state = 0;
			callback(state);
		}
	}

	
	if (state != state_old)
	{
		if (state == 1)
		{
			Mat image_roi = image(Rect(x_offset, y_offset, image_checked.cols, image_checked.rows));
			image_checked.copyTo(image_roi);
		}
		else
		{
			Mat image_roi = image(Rect(x_offset, y_offset, image_unchecked.cols, image_unchecked.rows));
			image_unchecked.copyTo(image_roi);
		}
		imshow(WINDOW_NAME, image);
	}
}
checkbox::~checkbox()
{
	image_checked.release();
	image_unchecked.release();
}
