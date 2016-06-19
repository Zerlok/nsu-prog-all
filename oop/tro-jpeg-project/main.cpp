#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include "haar.h"


template<>
class DataSizeGetter<cv::Mat>
{
	public:
		inline size_t operator()(const cv::Mat& data) const { return (data.rows * data.cols); }
};


template<>
class TransformationTraits<Mat>
{
	public:
		using D = int;
		using DVector = Mat;
		using DSizeGetter = MatSizeGetter;
};


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "A path to image file is required!" << std::endl;
		return 1;
	}
	
	OneDimTransformator odtr;
	odtr.set_transformation(new HaarTransformation<int>());
	
	cv::Mat img;
	img = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	odtr.apply_forward()
	
	cv::namedWindow("Image Display", cv::WINDOW_AUTOSIZE);
	cv::imshow("Image Display", img);
	cv::waitKey();
	
	return 0;
}
