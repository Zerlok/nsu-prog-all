#ifdef _RELEASE_

#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

#include "cvtransformation.h"
#include "matrix.h"
#include "../task16-wavelet/transformators.h"
#include "../task16-wavelet/haar.h"
#include "../task16-wavelet/daub4.h"
#include "../task16-wavelet/utils.h"

using MatrixD = Matrix<double>;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "A path to image file is required!" << std::endl;
		return 1;
	}
	
	cv::Mat before = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
//	MatTransformator tor;
//	tor.set_transformation(new DAUB4Transformation<cv::Mat>());

//	OneDimTransformator<double> tor;
//	tor.set_transformation(new DAUB4Transformation<double>());

//	cv::Mat encoded = tor.apply_forward(before);
//	cv::Mat after = tor.apply_backward(encoded);
	MatrixTransformator<double, DAUB4Transformation> tor;
	MatrixD afterdouble = tor.apply_forward(mat2matrix<double>(before));
	cv::Mat encoded = matrix2mat(afterdouble);
	cv::Mat after = matrix2mat(tor.apply_backward(afterdouble));

	cv::namedWindow("Before", cv::WINDOW_NORMAL);
	cv::imshow("Before", before);
	cv::namedWindow("Encoded", cv::WINDOW_NORMAL);
	cv::imshow("Encoded", encoded);
	cv::namedWindow("After", cv::WINDOW_NORMAL);
	cv::imshow("After", after);
	cv::waitKey();
	
	return 0;
}


#endif
