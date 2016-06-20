#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include "../task16-wavelet/transformators.h"
#include "../task16-wavelet/haar.h"
#include "../task16-wavelet/daub4.h"


template<>
class DataAdapter<uchar, cv::Mat>
{
	public:
		inline uchar& at(cv::Mat& mat, const size_t& idx) const { return mat.data[idx]; }
		inline const uchar& at(const cv::Mat& mat, const size_t& idx) const { return mat.data[idx]; }
		inline size_t size(const cv::Mat& mat) const { return (mat.rows * mat.cols); }
};


template<>
class TransformationTraits<cv::Mat>
{
	public:
		using Data = uchar;
		using DataSet = cv::Mat;
		using Adapter = DataAdapter<uchar, cv::Mat>;
};


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "A path to image file is required!" << std::endl;
		return 1;
	}
	
	cv::Mat before = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	cv::Mat after = before.clone();
	Transformation<cv::Mat>* haart = new HaarTransformation<cv::Mat>();
	after = haart->forward(after, 0, after.rows * after.cols);

	OneDimTransformator<cv::Mat> divtr;
	divtr.set_transformation(haart);
	after = divtr.apply_backward(after);

	cv::namedWindow("Before", cv::WINDOW_NORMAL);
	cv::imshow("Before", before);
	cv::namedWindow("After", cv::WINDOW_NORMAL);
	cv::imshow("After", after);
	cv::waitKey();
	
	return 0;
}
