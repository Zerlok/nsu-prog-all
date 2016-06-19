#include <iostream>
#include <opencv2/opencv.hpp>


int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("/home/zerlok/Pictures/shakal.jpeg");
	cv::namedWindow("Image Display", cv::WINDOW_AUTOSIZE);
	cv::imshow("Image Display", img);
	cv::waitKey();
	
	return 0;
}
