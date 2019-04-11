#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat3b hh_canvas;
Rect btn1, btn2, btn_tmp;
enum INI_DATA {
	NO_PRESS,
	PRESS_BTN1,
	PRESS_BTN2
};
int press_btn = NO_PRESS;

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (btn1.contains(Point(x, y)))
		{
			rectangle(hh_canvas(btn1), btn_tmp, Scalar(0, 0, 255), 2);
			press_btn = PRESS_BTN1;

		}
		else if (btn2.contains(Point(x, y)))
		{
			rectangle(hh_canvas(btn2), btn_tmp, Scalar(0, 0, 255), 2);
			press_btn = PRESS_BTN2;
		}
	}
	if (event == EVENT_LBUTTONUP)
	{
		rectangle(hh_canvas(btn1), btn_tmp, Scalar(200, 200, 200), 2);
		rectangle(hh_canvas(btn2), btn_tmp, Scalar(200, 200, 200), 2);
	}

	imshow("UI show", hh_canvas);
	waitKey(100);
}

int UI_btn_function()
{
	// An image
	Mat3b img(120, 250, Vec3b(0, 255, 0));

	// Your button
	btn_tmp = Rect(0, 0, img.cols, 50);
	btn1 = Rect(10, 40, img.cols, 50);
	btn2 = Rect(10, 100, img.cols, 50);

	// The canvas
	hh_canvas = Mat3b(img.rows + btn1.height, 20+img.cols, Vec3b(0, 0, 0));

	// Draw the button
	hh_canvas(btn1) = Vec3b(100, 200, 220);
	hh_canvas(btn2) = Vec3b(100, 200, 220);
	putText(hh_canvas, "Press a button:", Point(20, 20), 1, 1, Scalar(255, 255, 255));
	putText(hh_canvas(btn1), "button-1", Point(btn1.width*0.12, btn1.height*0.7), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0));
	putText(hh_canvas(btn2), "button-2", Point(btn1.width*0.1, btn1.height*0.7), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0));
	
	// Setup callback function
	namedWindow("UI show");
	setMouseCallback("UI show", callBackFunc);

	imshow("UI show", hh_canvas);

	while (press_btn == NO_PRESS)
		waitKey(1);

	return press_btn;
}

int main()
{
	int prs = UI_btn_function();
	printf("You pressed button-%d\r\n", press_btn);
	system("pause");
	return 1;
}
