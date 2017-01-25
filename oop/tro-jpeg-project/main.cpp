#ifdef _RELEASE_

#include <iostream>
#include <string>
#include <fstream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

#include "cvtransformation.h"
#include "matrix.h"
#include "../task16-wavelet/transformators.h"
#include "../task16-wavelet/haar.h"
#include "../task16-wavelet/daub4.h"
#include "../task16-wavelet/utils.h"

#include "../task13/serdeser.h"


template<class T>
Matrix<T> read_matrix(const std::string& filename)
{
	std::fstream input(filename);
	size_t rows_num;
	size_t cols_num;

	deserialize(input, rows_num);
	deserialize(input, cols_num);

	Matrix<T> mtrx(rows_num, cols_num);

	for (size_t i = 0; i < mtrx.size(); ++i)
		deserialize(input, mtrx[i]);

	return std::move(mtrx);
}


template<class T>
void write_matrix(const std::string& filename, const Matrix<T>& mtrx)
{
	std::ofstream output(filename);

	std::cout << output.is_open() << std::endl;

	serialize(output, mtrx.rows());
	serialize(output, mtrx.cols());

	for (size_t i = 0; i < mtrx.size(); ++i)
		serialize(output, mtrx[i]);

	output.close();
}


void compress_to_file(const std::string& imagepath, const std::string& filename, const float& tresh)
{
	cv::Mat img = cv::imread(imagepath, CV_LOAD_IMAGE_GRAYSCALE);

	MatrixTransformator<float, DAUB4Transformation> tor;
	Matrix<float> transformed = tor.apply_forward(mat2matrix<float>(img));

	const float thresh = transformed.sorted_abs()[transformed.size() * tresh];
	for (size_t i = 0; i < transformed.size(); ++i)
		if (std::abs(transformed[i]) <= thresh)
			transformed[i] = 0.0;

	write_matrix(filename, transformed);

	std::string cmd = "zip -r " + filename + " " + filename;
	std::system(cmd.c_str());

	cmd = "rm " + filename;
	std::system(cmd.c_str());
}


cv::Mat read_compressed(const std::string& filename)
{
	std::string cmd = "unzip -o " + filename;
	std::system(cmd.c_str());

	std::string actual_filename = filename.substr(0, filename.rfind('.'));
	Matrix<float> transformed = read_matrix<float>(actual_filename);

	cmd = "rm " + actual_filename;
	std::system(cmd.c_str());

	MatrixTransformator<float, DAUB4Transformation> tor;
	Matrix<float> revert = tor.apply_backward(transformed);

	return std::move(matrix2mat(revert));
}


int main(int argc, char *argv[])
{
	if ((argc < 2)
			|| (argv[1][0] != '-')
			|| (((argv[1][1] == 'c')
				 && (argc != 5))
				|| ((argv[1][1] == 'r')
					&& (argc != 3))))
	{
		std::cout << argc << std::endl;
		for (int i = 0; i < argc; ++i)
			std::cout << argv[i] << std::endl;
		std::cout << "Usage: " << argv[0] << " [FLAGS] [FILENAME1] [FILENAME2] [RATIO]" << std::endl
				  << "   -c - compress FILENAME1 image to FILENAME2 with given RATIO" << std::endl
				  << "   -r - read compressed FILENAME1" << std::endl;
		return 1;
	}
	
	if (argv[1][1] == 'c')
	{
		compress_to_file(argv[2], argv[3], std::atof(argv[4]));
		return 0;
	} else if (argv[1][1] != 'r')
		return 1;

	cv::Mat img = read_compressed(argv[2]);

	cv::namedWindow("Image", cv::WINDOW_NORMAL);
	cv::imshow("Image", img);
	cv::waitKey();
	
	return 0;
}


#endif
