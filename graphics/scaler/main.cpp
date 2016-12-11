#ifdef __RELEASE__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "image.hpp"


using Args = std::vector<std::string>;


static const std::string ERR_CANNOT_OPEN_INPUT_FILE = "ERROR: Cannot open file in read mode: ";
static const std::string ERR_CANNOT_OPEN_OUTPUT_FILE = "ERROR: Cannot open file in write mode: ";
static const std::string ERR_PATH_TO_IMAGE_REQUIRED = "ERROR: A path to image is required, got: ";
static const std::string ERR_FLAG_PARAMETR_REQUIRED = "ERROR: A parametr is required for flag: ";
static const std::string ERR_FLOAT_REQUIRED = "ERROR: A float parametr is required for flag: ";
static const std::string ERR_EMPTY_INPUT_IMAGE = "ERROR: Input image is empty!";

static const std::string WARN_UNKNOWN_FLAG_OR_PARAMETR = "WARNING: Unkown flag given or flag parametr was messed: ";
static const std::string WARN_SCALE_WAS_NOT_SET = "WARNING: Output image scale was not set - using default 1.0 ratio (the same size)";

static const std::string IMG_AVAILABLE_FORMATS = "JPG, PNG, BMP";


void doc()
{
	std::cout << "A simple image rescale application. Loads image from input path, scales a copy of input image and saves it into output path. Image input available formats: "
			  << IMG_AVAILABLE_FORMATS << std::endl
			  << "The output image format is the same as input image format." << std::endl
			  << std::endl;
}


void help(const std::string& name)
{
	std::cout << "Usage: " << name << " [INPUT_IMAGE_PATH] [OUTPUT_IMAGE_PATH] [FLAGS] [PARAMS]" << std::endl
			  << "   [INPUT_IMAGE_PATH] - path to input image, required." << std::endl
			  << "   [OUTPUT_IMAGE_PATH] - path to output image, required." << std::endl
			  << "NOTE: all flags parametrs must be floats (for example: 2.0)" << std::endl
			  << "FLAGS:" << std::endl
			  << "   -r, --ratio [ratio] - image scale ratio (scales image width and height by given ratio)" << std::endl
			  << "   -c, --scale [width] [heigth] - specify the scale ratio for width and height" << std::endl
				 // TODO: add 'auto' keyword.
			  << "   -z, --size [width] [height] - specify width and height of output image (in pixels)" << std::endl
			  << "   -h, --help - shows this message."
			  << std::endl;
}


Args toArgs(int argc, char *argv[])
{
	Args strings(argc);
	for (int i = 0; i < argc; ++i)
		strings[i] = argv[i];

	return strings;
}


bool isFlag(const std::string& s)
{
	return ((!s.empty())
			&& (((s.length() > 1)
				 && (s[0] == '-'))
				|| ((s.length() > 2)
					&& (s[0] == '-')
					&& (s[1] == '-'))
			));
}


float getFlagFloatValue(const size_t& i, const std::string& flag, const Args& args)
{
	size_t formatErr = 0;
	float value = 0.0;

	if (i == args.size())
	{
		std::cerr << ERR_FLAG_PARAMETR_REQUIRED << flag << std::endl;
		return value;
	}

	value = std::stof(args[i], &formatErr);
	if (formatErr == 0)
	{
		std::cerr << ERR_FLOAT_REQUIRED << flag << std::endl;
		return value;
	}

	return value;
}


int main(int argc, char *argv[])
{
	const Args args = toArgs(argc, argv);

	const Args::const_iterator hIt = std::find(args.begin(), args.end(), "-h");
	const Args::const_iterator helpIt = std::find(args.begin(), args.end(), "--help");

	if ((args.size() == 1)
			|| (hIt != args.end())
			|| (helpIt != args.end()))
	{
		doc();
		help(args[0]);
		return 0;
	}

//	std::ifstream input;
//	std::ofstream output;
	QString input;
	QString output;
	float scaleRatio = 0.0;
	float widthScaleRatio = 0.0;
	float heightScaleRatio = 0.0;
	float scaledWidth = 0.0;
	float scaledHeight = 0.0;

	for (size_t i = 1; i < args.size(); ++i)
	{
		switch (i)
		{
			// TODO: check images formats!
			case 1:
				// TODO: open in 'rb' mode.
				if (isFlag(args[i]))
				{
					std::cerr << ERR_PATH_TO_IMAGE_REQUIRED << args[i] << std::endl;
					return 1;
				}
				input = QString::fromUtf8(args[i].c_str());

//				input.open(args[i]);
//				if (!input.is_open())
//				{
//					std::cerr << ERR_CANNOT_OPEN_INPUT_FILE << args[i] << std::endl;
//					return 1;
//				}
				break;
			case 2:
				// TODO: open in 'wb' mode.
				if (isFlag(args[i]))
				{
					std::cerr << ERR_PATH_TO_IMAGE_REQUIRED << args[i] << std::endl;
					return 1;
				}
				output = QString::fromUtf8(args[i].c_str());

//				output.open(args[i]);
//				if (!output.is_open())
//				{
//					std::cerr << ERR_CANNOT_OPEN_OUTPUT_FILE << args[i] << std::endl;
//					return 1;
//				}
				break;
			default:
				if ((args[i] == "-r")
						|| (args[i] == "--ratio"))
				{
					scaleRatio = getFlagFloatValue(i+1, args[i], args);
					i += 1;
				}
				else if ((args[i] == "-c")
						 || (args[i] == "--scale"))
				{
					widthScaleRatio = getFlagFloatValue(i+1, args[i], args);
					heightScaleRatio = getFlagFloatValue(i+2, args[i], args);
					i += 2;
				}
				else if ((args[i] == "-z")
						 || (args[i] == "--size"))
				{
					scaledWidth = getFlagFloatValue(i+1, args[i], args);
					scaledHeight = getFlagFloatValue(i+2, args[i], args);
				}
				else
				{
					std::cerr << WARN_UNKNOWN_FLAG_OR_PARAMETR << args[i] << std::endl;
				}
				break;
		}
	}

	if (((scaleRatio + widthScaleRatio + scaledWidth) == 0.0)
			|| ((scaleRatio + heightScaleRatio + scaledHeight) == 0.0))
	{
		std::cerr << WARN_SCALE_WAS_NOT_SET << std::endl;
		scaleRatio = 1.0;
	}

	Image img;
	img.load(input);

	if (img.isNull())
	{
		std::cerr << ERR_EMPTY_INPUT_IMAGE << std::endl;
		return 1;
	}

	if (scaleRatio != 0.0)
	{
		scaledWidth = img.width() * scaleRatio;
		scaledHeight = img.height() * scaleRatio;
	}
	else if ((widthScaleRatio != 0.0)
			 || (heightScaleRatio != 0.0))
	{
		scaledWidth = img.width() * widthScaleRatio;
		scaledHeight = img.height() * heightScaleRatio;
	}

	Image scaledImg;
	scaledImg = img.resize(scaledWidth, scaledHeight);
	scaledImg.save(output);

	std::cout << "Done." << std::endl;
	return 0;
}

#endif
