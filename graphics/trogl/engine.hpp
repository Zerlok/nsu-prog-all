#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"

#include "scene.hpp"


class TroglEngine
{
	public:
		TroglEngine();
		virtual ~TroglEngine();

		// OpenGL running.
		void showScene(const Scene& scene);
};


#endif // __ENGINE_HPP__
