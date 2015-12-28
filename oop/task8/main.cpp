#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#include "imagepng.h"
#include "utils.h"


int main(int argc, char *argv[])
{
	ImagePNG src(argv[1]);
	cout << "Opened image size: " << src.get_width() << "x" << src.get_height() << " WxH"
		 << " = " << src.get_size() << " pixels in total" << endl
		 << "End: " << src.end()
		 << endl;

	Histogram histogram = pngutils::get_histogram(src);
	Histogram diff_histogram = pngutils::differentiate_histogram(histogram);
	sort(diff_histogram.begin(), diff_histogram.end());

//	cout << diff_histogram.front().first << " : " << diff_histogram.front().second << endl
//		 << diff_histogram.back().first << " : " << diff_histogram.back().second
//		 << endl;

//	ImagePNG histo = pngfilters::build_histogram(histogram);
//	histo.write("histo.png");

//	ImagePNG diff_histo = pngfilters::build_histogram(diff_histogram);
//	diff_histo.write("diff_histo.png");

	ImagePNG img = pngfilters::build_thresholded_image(src, double(diff_histogram.back().second) / pngconsts::palette_size);

	img.write("output.png");

	return 0;
}
