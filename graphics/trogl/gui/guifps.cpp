#include "guifps.hpp"


#include "common/utils.hpp"


const std::string GUIfps::LABEL = "fps: ";


GUIfps::GUIfps(const size_t& x,
			   const size_t& y,
			   const size_t& width,
			   const size_t& height)
	: GUILabel(LABEL, x, y, width, height),
	  _frameCounter(0)
{
}


void GUIfps::tick()
{
	static size_t startTimestamp = getTimestamp();
	size_t currentTimestamp = getTimestamp();

	if (currentTimestamp - startTimestamp >= 1)
	{
		_clearText();
		_textStream << LABEL << _frameCounter;
		_frameCounter = 0;
		startTimestamp = currentTimestamp;
	}
	++_frameCounter;
}
