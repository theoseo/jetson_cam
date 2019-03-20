#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


int main()
{
	const char* gst =  "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)30/1 ! \
							nvvidconv flip-method=4 ! video/x-raw, format=(string)BGRx ! \
										videoconvert ! video/x-raw, format=(string)BGR ! \
													appsink";

	cv::VideoCapture cap(gst);

	if(!cap.isOpened())
	{
		std::cout<<"Failed to open camera."<<std::endl;
		return -1;
	}

	unsigned int width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
	unsigned int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
	unsigned int pixels = width*height;
	std::cout <<"Frame size : "<<width<<" x "<<height<<", "<<pixels<<" Pixels "<<std::endl;

	cv::namedWindow("MyCameraPreview", CV_WINDOW_AUTOSIZE);
	cv::Mat frame_in(width, height, CV_8UC3);

	while(1)
	{
		if (!cap.read(frame_in)) {
			std::cout<<"Capture read error"<<std::endl;
			break;
		} else {
			cv::imshow("MyCameraPreview",frame_in);
			cv::waitKey(1000/120); // let imshow draw and wait for next frame 8 ms for 120 fps
		}	
	}

	cap.release();
	return 0;
}
