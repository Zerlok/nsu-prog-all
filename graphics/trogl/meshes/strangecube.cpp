#include "strangecube.hpp"


#include <logger.hpp>
#include "common/utils.h"


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


StrangeCube::StrangeCube(const Color& c1,
						 const Color& c2)
	: Mesh("StrangeCube")
{
	const double start = getTimeDouble();

	// Vertices.
	{
		addVertex(Vertex(-1.0, -1.0, -1.0, c1));
		addVertex(Vertex(-1.0, -1.0, 1.0, c1));
		addVertex(Vertex(-1.0, 1.0, -1.0, c1));
		addVertex(Vertex(-1.0, 1.0, 1.0, c1));
		addVertex(Vertex(1.0, -1.0, -1.0, c1));
		addVertex(Vertex(1.0, -1.0, 1.0, c1));
		addVertex(Vertex(1.0, 1.0, -1.0, c1));
		addVertex(Vertex(1.0, 1.0, 1.0, c1));
		addVertex(Vertex(-1.0, -1.0, -0.333, c1));
		addVertex(Vertex(-1.0, -1.0, 0.333, c1));
		addVertex(Vertex(-1.0, -0.333, 1.0, c1));
		addVertex(Vertex(-1.0, 0.333, 1.0, c1));
		addVertex(Vertex(-1.0, 1.0, 0.333, c1));
		addVertex(Vertex(-1.0, 1.0, -0.333, c1));
		addVertex(Vertex(-1.0, 0.333, -1.0, c1));
		addVertex(Vertex(-1.0, -0.333, -1.0, c1));
		addVertex(Vertex(-0.333, 1.0, 1.0, c1));
		addVertex(Vertex(0.333, 1.0, 1.0, c1));
		addVertex(Vertex(1.0, 1.0, 0.333, c1));
		addVertex(Vertex(1.0, 1.0, -0.333, c1));
		addVertex(Vertex(0.333, 1.0, -1.0, c1));
		addVertex(Vertex(-0.333, 1.0, -1.0, c1));
		addVertex(Vertex(1.0, 0.333, 1.0, c1));
		addVertex(Vertex(1.0, -0.333, 1.0, c1));
		addVertex(Vertex(1.0, -1.0, 0.333, c1));
		addVertex(Vertex(1.0, -1.0, -0.333, c1));
		addVertex(Vertex(1.0, -0.333, -1.0, c1));
		addVertex(Vertex(1.0, 0.333, -1.0, c1));
		addVertex(Vertex(0.333, -1.0, 1.0, c1));
		addVertex(Vertex(-0.333, -1.0, 1.0, c1));
		addVertex(Vertex(-0.333, -1.0, -1.0, c1));
		addVertex(Vertex(0.333, -1.0, -1.0, c1));
		addVertex(Vertex(0.333, -0.333, 1.0, c2));
		addVertex(Vertex(-0.333, -0.333, 1.0, c2));
		addVertex(Vertex(0.333, 0.333, 1.0, c2));
		addVertex(Vertex(-0.333, 0.333, 1.0, c2));
		addVertex(Vertex(-0.333, -0.333, -1.0, c2));
		addVertex(Vertex(0.333, -0.333, -1.0, c2));
		addVertex(Vertex(-0.333, 0.333, -1.0, c2));
		addVertex(Vertex(0.333, 0.333, -1.0, c2));
		addVertex(Vertex(0.333, -1.0, 0.333, c2));
		addVertex(Vertex(0.333, -1.0, -0.333, c2));
		addVertex(Vertex(-0.333, -1.0, 0.333, c2));
		addVertex(Vertex(-0.333, -1.0, -0.333, c2));
		addVertex(Vertex(1.0, 0.333, 0.333, c2));
		addVertex(Vertex(1.0, 0.333, -0.333, c2));
		addVertex(Vertex(1.0, -0.333, 0.333, c2));
		addVertex(Vertex(1.0, -0.333, -0.333, c2));
		addVertex(Vertex(-0.333, 1.0, 0.333, c2));
		addVertex(Vertex(-0.333, 1.0, -0.333, c2));
		addVertex(Vertex(0.333, 1.0, 0.333, c2));
		addVertex(Vertex(0.333, 1.0, -0.333, c2));
		addVertex(Vertex(-1.0, -0.333, 0.333, c2));
		addVertex(Vertex(-1.0, -0.333, -0.333, c2));
		addVertex(Vertex(-1.0, 0.333, 0.333, c2));
		addVertex(Vertex(-1.0, 0.333, -0.333, c2));
	}

	// Faces.
	{
		addFace(Face(23, 46, 22));
		addFace(Face(5, 24, 23));
		addFace(Face(44, 22, 46));
		addFace(Face(46, 23, 24));
		addFace(Face(44, 18, 22));
		addFace(Face(18, 7, 22));
		addFace(Face(24, 5, 28));
		addFace(Face(1, 9, 29));
		addFace(Face(1, 10, 9));
		addFace(Face(3, 12, 11));
		addFace(Face(12, 3, 16));
		addFace(Face(7, 18, 17));
		addFace(Face(7, 17, 22));
		addFace(Face(3, 11, 16));
		addFace(Face(1, 29, 10));
		addFace(Face(5, 23, 28));
		addFace(Face(6, 27, 20));
		addFace(Face(6, 19, 27));
		addFace(Face(6, 20, 19));
		addFace(Face(2, 14, 13));
		addFace(Face(2, 13, 21));
		addFace(Face(2, 21, 14));
		addFace(Face(0, 15, 30));
		addFace(Face(0, 8, 15));
		addFace(Face(8, 0, 30));
		addFace(Face(4, 31, 26));
		addFace(Face(4, 26, 25));
		addFace(Face(4, 25, 31));
		addFace(Face(23, 22, 34));
		addFace(Face(32, 23, 34));
		addFace(Face(32, 28, 23));
		addFace(Face(10, 29, 33));
		addFace(Face(22, 17, 34));
		addFace(Face(28, 32, 29));
		addFace(Face(32, 33, 29));
		addFace(Face(34, 17, 35));
		addFace(Face(11, 33, 35));
		addFace(Face(10, 33, 11));
		addFace(Face(35, 16, 11));
		addFace(Face(17, 16, 35));
		addFace(Face(35, 32, 34));
		addFace(Face(32, 35, 33));
		addFace(Face(17, 48, 16));
		addFace(Face(50, 48, 17));
		addFace(Face(50, 17, 18));
		addFace(Face(16, 48, 12));
		addFace(Face(49, 12, 48));
		addFace(Face(12, 49, 13));
		addFace(Face(21, 13, 49));
		addFace(Face(49, 51, 21));
		addFace(Face(20, 21, 51));
		addFace(Face(51, 19, 20));
		addFace(Face(51, 50, 19));
		addFace(Face(19, 50, 18));
		addFace(Face(46, 24, 47));
		addFace(Face(24, 25, 47));
		addFace(Face(47, 25, 26));
		addFace(Face(26, 45, 47));
		addFace(Face(27, 45, 26));
		addFace(Face(27, 19, 45));
		addFace(Face(45, 19, 44));
		addFace(Face(18, 44, 19));
		addFace(Face(29, 40, 28));
		addFace(Face(42, 40, 29));
		addFace(Face(29, 9, 42));
		addFace(Face(9, 8, 42));
		addFace(Face(42, 8, 43));
		addFace(Face(43, 8, 30));
		addFace(Face(30, 31, 43));
		addFace(Face(41, 43, 31));
		addFace(Face(31, 25, 41));
		addFace(Face(25, 24, 41));
		addFace(Face(41, 24, 40));
		addFace(Face(28, 40, 24));
		addFace(Face(11, 54, 10));
		addFace(Face(52, 10, 54));
		addFace(Face(10, 52, 9));
		addFace(Face(9, 52, 8));
		addFace(Face(52, 53, 8));
		addFace(Face(15, 8, 53));
		addFace(Face(15, 53, 14));
		addFace(Face(14, 53, 55));
		addFace(Face(55, 13, 14));
		addFace(Face(13, 55, 12));
		addFace(Face(54, 12, 55));
		addFace(Face(54, 11, 12));
		addFace(Face(37, 30, 36));
		addFace(Face(30, 37, 31));
		addFace(Face(36, 30, 15));
		addFace(Face(15, 14, 36));
		addFace(Face(38, 36, 14));
		addFace(Face(14, 21, 38));
		addFace(Face(21, 20, 38));
		addFace(Face(38, 20, 39));
		addFace(Face(39, 20, 27));
		addFace(Face(27, 26, 39));
		addFace(Face(37, 39, 26));
		addFace(Face(26, 31, 37));
		addFace(Face(39, 36, 38));
		addFace(Face(36, 39, 37));
		addFace(Face(51, 49, 50));
		addFace(Face(48, 50, 49));
		addFace(Face(45, 44, 47));
		addFace(Face(47, 44, 46));
		addFace(Face(41, 40, 43));
		addFace(Face(43, 40, 42));
		addFace(Face(52, 54, 53));
		addFace(Face(54, 55, 53));
	}

	logModule << "Initialized (duration: "
			  << getTimeDouble() - start << "ms)"
			  << logEndl;
}


StrangeCube::~StrangeCube()
{
}
