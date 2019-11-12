#include "button.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;
//https://stackoverflow.com/questions/2298242/callback-functions-in-c
typedef void (*CallbackType)();

const string WINDOW_NAME = "Test Window";
const int from_z_shift = 1;


button::button(Mat& image, int x_offset_inp, int y_offset_inp, int width_inp, int height_inp, Scalar color_bgr_inp,  string text_inp, CallbackType callback_inp)
{
	x_offset = x_offset_inp;
	y_offset = y_offset_inp;
	width = width_inp;
	height = height_inp;
	callback = callback_inp;
	state = 0;
	x_offset_2 = x_offset + (width - 1);
	y_offset_2 = y_offset + (height - 1);

	int x1_external = x_offset;
	int x2_external = x_offset + width;
	int y1_external = y_offset;
	int y2_external = height;

	int edge_size = 5;

	//int x1_internal = x1_external + edge_size;
	//int x2_internal = x2_external - edge_size;
	//int y1_internal = y1_external + edge_size;
	//int y2_internal = y2_external - edge_size;

	int x1_internal_inside = edge_size;
	int x2_internal_inside = (width - 1) - edge_size;
	int y1_internal_inside = edge_size;
	int y2_internal_inside = (height - 1) - edge_size;


	image_up = Mat::zeros(height, width, CV_8UC3);
	image_down = Mat::zeros(height, width, CV_8UC3);

	/*
	vector<Point> points_tmp;
	points_tmp.push_back(Point(0, 0));
	points_tmp.push_back(Point((width - 1), 0));
	points_tmp.push_back(Point(x2_internal_inside, y1_internal_inside));
	points_tmp.push_back(Point(x1_internal_inside, y1_internal_inside));
	fillPoly(image_up, points_tmp, points_tmp.size, 1, Scalar(0, 0, 0), 8);
	fillPoly()
	*/

	

	const int n_points_tmp = 4;
	const int lineType = LINE_8;
	Point points_tmp[1][n_points_tmp];
	points_tmp[0][0] = Point(0, 0);
	points_tmp[0][1] = Point(0, 0);
	points_tmp[0][2] = Point(0, 0);
	points_tmp[0][3] = Point(0, 0);
	const Point* points_tmp2[1] = { points_tmp[0] };
	int n_points_tmp2[] = { n_points_tmp };

	Mat image_tmp;
	Scalar color_bgr_center;
	Scalar color_bgr_1;
	Scalar color_bgr_2;
	Scalar color_bgr_3;
	Scalar color_bgr_4;
	int from_z_shift_tmp = 0;
	for (int up_down_count = 0; up_down_count < 2; up_down_count++)
	{

		Mat image_tmp = Mat::zeros(height, width, CV_8UC3);

		if (up_down_count == 0)
		{
			color_bgr_center = Scalar(6 * (color_bgr_inp[0] / 8), 6 * (color_bgr_inp[1] / 8), 6 * (color_bgr_inp[2] / 8));
			color_bgr_1 = Scalar(color_bgr_inp[0], color_bgr_inp[1], color_bgr_inp[2]);
			color_bgr_2 = Scalar(7 * (color_bgr_inp[0] / 8), 7 * (color_bgr_inp[1] / 8), 7 * (color_bgr_inp[2] / 8));
			color_bgr_3 = Scalar(5 * (color_bgr_inp[0] / 8), 5 * (color_bgr_inp[1] / 8), 5 * (color_bgr_inp[2] / 8));
			color_bgr_4 = Scalar(4 * (color_bgr_inp[0] / 8), 4 * (color_bgr_inp[1] / 8), 4 * (color_bgr_inp[2] / 8));
			from_z_shift_tmp = -from_z_shift;
		}
		else
		{
			color_bgr_center = Scalar(6 * (color_bgr_inp[0] / 8), 6 * (color_bgr_inp[1] / 8), 6 * (color_bgr_inp[2] / 8));
			color_bgr_4 = Scalar(color_bgr_inp[0], color_bgr_inp[1], color_bgr_inp[2]);
			color_bgr_3 = Scalar(7 * (color_bgr_inp[0] / 8), 7 * (color_bgr_inp[1] / 8), 7 * (color_bgr_inp[2] / 8));
			color_bgr_2 = Scalar(5 * (color_bgr_inp[0] / 8), 5 * (color_bgr_inp[1] / 8), 5 * (color_bgr_inp[2] / 8));
			color_bgr_1 = Scalar(4 * (color_bgr_inp[0] / 8), 4 * (color_bgr_inp[1] / 8), 4 * (color_bgr_inp[2] / 8));
			from_z_shift_tmp = from_z_shift;
		}

		points_tmp[0][0] = Point(0, 0);
		points_tmp[0][1] = Point((width - 1), 0);
		points_tmp[0][2] = Point(x2_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);
		points_tmp[0][3] = Point(x1_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);

		fillPoly(image_tmp,
			points_tmp2,
			n_points_tmp2,
			1,
			color_bgr_1,
			lineType);

		points_tmp[0][0] = Point(0, 0);
		points_tmp[0][1] = Point(x1_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);
		points_tmp[0][2] = Point(x1_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp[0][3] = Point(0, (height - 1));
		points_tmp2[0] = points_tmp[0];

		fillPoly(image_tmp,
			points_tmp2,
			n_points_tmp2,
			1,
			color_bgr_2,
			lineType);

		points_tmp[0][0] = Point((width - 1), 0);
		points_tmp[0][1] = Point(x2_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);
		points_tmp[0][2] = Point(x2_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp[0][3] = Point((width - 1), (height - 1));
		points_tmp2[0] = points_tmp[0];

		fillPoly(image_tmp,
			points_tmp2,
			n_points_tmp2,
			1,
			color_bgr_3,
			lineType);

		points_tmp[0][0] = Point(0, (height - 1));
		points_tmp[0][1] = Point(x1_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp[0][2] = Point(x2_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp[0][3] = Point((width - 1), (height - 1));
		points_tmp2[0] = points_tmp[0];

		fillPoly(image_tmp,
			points_tmp2,
			n_points_tmp2,
			1,
			color_bgr_4,
			lineType);

		points_tmp[0][0] = Point(x1_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);
		points_tmp[0][1] = Point(x2_internal_inside + from_z_shift_tmp, y1_internal_inside + from_z_shift_tmp);
		points_tmp[0][2] = Point(x2_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp[0][3] = Point(x1_internal_inside + from_z_shift_tmp, y2_internal_inside + from_z_shift_tmp);
		points_tmp2[0] = points_tmp[0];

		fillPoly(image_tmp,
			points_tmp2,
			n_points_tmp2,
			1,
			color_bgr_center,
			lineType);

		int thickness_tmp = 1;
		int baseline = -1;

		double font_scale_tmp = 1.0;

		Size text_size_tmp = getTextSize(text_inp, FONT_HERSHEY_COMPLEX_SMALL,
			font_scale_tmp, thickness_tmp, &baseline);

		double width_normalized_tmp = ((double)text_size_tmp.width) / (x2_internal_inside - x1_internal_inside);
		double height_normalized_tmp = ((double)text_size_tmp.height) / (y2_internal_inside - y1_internal_inside);
		if (width_normalized_tmp > height_normalized_tmp)
		{
			font_scale_tmp = font_scale_tmp / width_normalized_tmp;
		}
		else
		{
			font_scale_tmp = font_scale_tmp / height_normalized_tmp;
		}
		font_scale_tmp = font_scale_tmp * 0.95;


		Size text_size = getTextSize(text_inp, FONT_HERSHEY_COMPLEX_SMALL,
			font_scale_tmp, thickness_tmp, &baseline);
		Point textOrg((image_tmp.cols - text_size.width) / 2 + from_z_shift_tmp,
			(image_tmp.rows + text_size.height) / 2 + from_z_shift_tmp);
		putText(image_tmp, text_inp, textOrg,
			FONT_HERSHEY_COMPLEX_SMALL, font_scale_tmp, cvScalar(0, 0, 0), 1, CV_AA);

		if (up_down_count == 0)
		{
			image_up = image_tmp;
		}
		else
		{
			image_down = image_tmp;
		}

	}
	Mat image_roi = image(Rect(x_offset, y_offset, image_up.cols, image_up.rows));
	image_up.copyTo(image_roi);
	imshow(WINDOW_NAME, image);
}



void button::check_mouse(Mat& image, int x, int y, int event_no)
{
	
	int state_old = state;

	if (!((x_offset <= x && x <= x_offset_2) && (y_offset <= y && y <= y_offset_2)))
	{
		state = 0;
	}

	if ((event_no == EVENT_LBUTTONDOWN || event_no == EVENT_LBUTTONDBLCLK) && ((x_offset <= x && x <= x_offset_2) && (y_offset <= y && y <= y_offset_2)))
	{
		state = 1;
	}
	
	if (state == 1 && event_no == EVENT_LBUTTONUP)
	{
		callback();
		state = 0;
	}

	if (state != state_old)
	{
		if (state == 1)
		{
			Mat image_roi = image(Rect(x_offset, y_offset, image_down.cols, image_down.rows));
			image_down.copyTo(image_roi);
		}
		else
		{
			Mat image_roi = image(Rect(x_offset, y_offset, image_up.cols, image_up.rows));
			image_up.copyTo(image_roi);
		}
		imshow(WINDOW_NAME, image);
	}
	
}

button::~button() {
	image_down.release();
	image_up.release();
}

