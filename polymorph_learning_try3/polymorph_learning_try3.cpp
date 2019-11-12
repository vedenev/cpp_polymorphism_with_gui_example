#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "view.h"
#include "button.h"
#include "checkbox.h"

using namespace std;
using namespace cv;

#define HEIGHT 480
#define WIDTH 640
#define N_VIEWS 5
const string WINDOW_NAME = "Test Window";

// dll missing:
//https://stackoverflow.com/questions/21707992/msvcp120d-dll-missing
//https://github.com/Emotiv/community-sdk/find/master


//https://stackoverflow.com/questions/2298242/callback-functions-in-c
typedef void (*CallbackType)();
typedef void (*CallbackType2)(int);

// globals:
Mat image;
view** views_all;

// https://www.opencv-srf.com/2011/11/mouse-events.html

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{	
	
	//https://stackoverflow.com/questions/41045/can-i-have-polymorphic-containers-with-value-semantics-in-c
	// But don't forget to define a virtual destructor in Base1
	// https://www.gamedev.net/forums/topic/623647-c-array-and-polymorphic-objects/
	for (int view_count = 0; view_count < N_VIEWS; view_count++)
	{
		views_all[view_count]->check_mouse(image, x, y, event);
	}
	
}

void button_1_callback()
{
	cout << "button 1 callback" << endl;
}

void button_2_callback()
{
	cout << "button 2 callback" << endl;
}

void checkbox_1_callback(int state_inp)
{
	cout << "checkbox 1 callback, state:" << state_inp << endl;
}

void checkbox_2_callback(int state_inp)
{
	cout << "checkbox 2 callback, state:" << state_inp << endl;
}

void checkbox_3_callback(int state_inp)
{
	cout << "checkbox 3 callback, state:" << state_inp << endl;
}

int main(int argc, char** argv)
{
	
	image = Mat(HEIGHT, WIDTH, CV_8UC3, Scalar(100, 100, 100));

	//Create a window
	namedWindow(WINDOW_NAME, 1);

	//set the callback function for any mouse event
	setMouseCallback(WINDOW_NAME, CallBackFunc, NULL);

	views_all = new view * [N_VIEWS];

	int x_offset_tmp = 20;
	int y_offset_tmp = 20;
	int width_tmp = 150;
	int height_tmp = 50;
	Scalar color_bgr_tmp = Scalar(255, 255, 255);
	string text_tmp = "button 1";
	
	views_all[0] = new button(image, x_offset_tmp, y_offset_tmp, width_tmp, height_tmp, color_bgr_tmp, text_tmp, &button_1_callback);

	
	x_offset_tmp = 20;
	y_offset_tmp = 80;
	width_tmp = 200;
	height_tmp = 70;
	color_bgr_tmp = Scalar(0, 255, 255);
	text_tmp = "button 2 yellow";

	views_all[1] = new button(image, x_offset_tmp, y_offset_tmp, width_tmp, height_tmp, color_bgr_tmp, text_tmp, &button_2_callback);
	

	x_offset_tmp = 300;
	y_offset_tmp = 20;
	width_tmp = 150;
	height_tmp = 50;
	color_bgr_tmp = Scalar(133, 133, 133);
	text_tmp = "checkbox 1";
	views_all[2] = new checkbox(image, x_offset_tmp, y_offset_tmp, width_tmp, height_tmp, color_bgr_tmp, text_tmp, &checkbox_1_callback);

	x_offset_tmp = 300;
	y_offset_tmp = 80;
	width_tmp = 220;
	height_tmp = 100;
	color_bgr_tmp = Scalar(181, 113, 255);
	text_tmp = "checkbox 2";
	views_all[3] = new checkbox(image, x_offset_tmp, y_offset_tmp, width_tmp, height_tmp, color_bgr_tmp, text_tmp, &checkbox_2_callback);

	x_offset_tmp = 320;
	y_offset_tmp = 200;
	width_tmp = 230;
	height_tmp = 80;
	color_bgr_tmp = Scalar(255, 112, 180);
	text_tmp = "checkbox 3, click me";
	views_all[4] = new checkbox(image, x_offset_tmp, y_offset_tmp, width_tmp, height_tmp, color_bgr_tmp, text_tmp, &checkbox_3_callback);
	
	Point textOrg(20, HEIGHT - 30);
	text_tmp = "Press any key to close the window.";
	putText(image, text_tmp, textOrg,
		FONT_HERSHEY_COMPLEX_SMALL, 0.5, cvScalar(255, 255, 255), 1, CV_AA);
	imshow(WINDOW_NAME, image);

	// Wait until user press some key
	waitKey(0);

	// delete all:
	for (int view_count = 0; view_count < N_VIEWS; view_count++)
	{
		delete views_all[view_count];
	}
	image.release();
	destroyWindow(WINDOW_NAME);

	

	return 0;

}