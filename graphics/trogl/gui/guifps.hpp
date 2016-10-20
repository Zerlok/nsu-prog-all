#ifndef __GUI_FPS_HPP__
#define __GUI_FPS_HPP__


#include "guilabel.hpp"


class GUIfps : public GUILabel
{
	public:
		GUIfps(const size_t& x,
			   const size_t& y,
			   const size_t& width,
			   const size_t& height);

		void tick();

	private:
		static const std::string LABEL;

		size_t _frameCounter;
};


#endif // __GUI_FPS_HPP__
