#include "strangecube.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


StrangeCube::StrangeCube(const Color& c1,
						 const Color& c2)
	: Mesh("StrangeCube")
{
	const double start = getTimeDouble();

	// Vertices.
	{
		addVertex(-1.0, -1.0, -1.0, c1);
		addVertex(-1.0, -1.0, 1.0, c1);
		addVertex(-1.0, 1.0, -1.0, c1);
		addVertex(-1.0, 1.0, 1.0, c1);
		addVertex(1.0, -1.0, -1.0, c1);
		addVertex(1.0, -1.0, 1.0, c1);
		addVertex(1.0, 1.0, -1.0, c1);
		addVertex(1.0, 1.0, 1.0, c1);
		addVertex(-1.0, -1.0, -0.333, c1);
		addVertex(-1.0, -1.0, 0.333, c1);
		addVertex(-1.0, -0.333, 1.0, c1);
		addVertex(-1.0, 0.333, 1.0, c1);
		addVertex(-1.0, 1.0, 0.333, c1);
		addVertex(-1.0, 1.0, -0.333, c1);
		addVertex(-1.0, 0.333, -1.0, c1);
		addVertex(-1.0, -0.333, -1.0, c1);
		addVertex(-0.333, 1.0, 1.0, c1);
		addVertex(0.333, 1.0, 1.0, c1);
		addVertex(1.0, 1.0, 0.333, c1);
		addVertex(1.0, 1.0, -0.333, c1);
		addVertex(0.333, 1.0, -1.0, c1);
		addVertex(-0.333, 1.0, -1.0, c1);
		addVertex(1.0, 0.333, 1.0, c1);
		addVertex(1.0, -0.333, 1.0, c1);
		addVertex(1.0, -1.0, 0.333, c1);
		addVertex(1.0, -1.0, -0.333, c1);
		addVertex(1.0, -0.333, -1.0, c1);
		addVertex(1.0, 0.333, -1.0, c1);
		addVertex(0.333, -1.0, 1.0, c1);
		addVertex(-0.333, -1.0, 1.0, c1);
		addVertex(-0.333, -1.0, -1.0, c1);
		addVertex(0.333, -1.0, -1.0, c1);
		addVertex(0.333, -0.333, 1.0, c2);
		addVertex(-0.333, -0.333, 1.0, c2);
		addVertex(0.333, 0.333, 1.0, c2);
		addVertex(-0.333, 0.333, 1.0, c2);
		addVertex(-0.333, -0.333, -1.0, c2);
		addVertex(0.333, -0.333, -1.0, c2);
		addVertex(-0.333, 0.333, -1.0, c2);
		addVertex(0.333, 0.333, -1.0, c2);
		addVertex(0.333, -1.0, 0.333, c2);
		addVertex(0.333, -1.0, -0.333, c2);
		addVertex(-0.333, -1.0, 0.333, c2);
		addVertex(-0.333, -1.0, -0.333, c2);
		addVertex(1.0, 0.333, 0.333, c2);
		addVertex(1.0, 0.333, -0.333, c2);
		addVertex(1.0, -0.333, 0.333, c2);
		addVertex(1.0, -0.333, -0.333, c2);
		addVertex(-0.333, 1.0, 0.333, c2);
		addVertex(-0.333, 1.0, -0.333, c2);
		addVertex(0.333, 1.0, 0.333, c2);
		addVertex(0.333, 1.0, -0.333, c2);
		addVertex(-1.0, -0.333, 0.333, c2);
		addVertex(-1.0, -0.333, -0.333, c2);
		addVertex(-1.0, 0.333, 0.333, c2);
		addVertex(-1.0, 0.333, -0.333, c2);
	}

	// Faces.
	{
		addFace(23, 46, 22);
		addFace(5, 24, 23);
		addFace(44, 22, 46);
		addFace(46, 23, 24);
		addFace(44, 18, 22);
		addFace(18, 7, 22);
		addFace(24, 5, 28);
		addFace(1, 9, 29);
		addFace(1, 10, 9);
		addFace(3, 12, 11);
		addFace(12, 3, 16);
		addFace(7, 18, 17);
		addFace(7, 17, 22);
		addFace(3, 11, 16);
		addFace(1, 29, 10);
		addFace(5, 23, 28);
		addFace(6, 27, 20);
		addFace(6, 19, 27);
		addFace(6, 20, 19);
		addFace(2, 14, 13);
		addFace(2, 13, 21);
		addFace(2, 21, 14);
		addFace(0, 15, 30);
		addFace(0, 8, 15);
		addFace(8, 0, 30);
		addFace(4, 31, 26);
		addFace(4, 26, 25);
		addFace(4, 25, 31);
		addFace(23, 22, 34);
		addFace(32, 23, 34);
		addFace(32, 28, 23);
		addFace(10, 29, 33);
		addFace(22, 17, 34);
		addFace(28, 32, 29);
		addFace(32, 33, 29);
		addFace(34, 17, 35);
		addFace(11, 33, 35);
		addFace(10, 33, 11);
		addFace(35, 16, 11);
		addFace(17, 16, 35);
		addFace(35, 32, 34);
		addFace(32, 35, 33);
		addFace(17, 48, 16);
		addFace(50, 48, 17);
		addFace(50, 17, 18);
		addFace(16, 48, 12);
		addFace(49, 12, 48);
		addFace(12, 49, 13);
		addFace(21, 13, 49);
		addFace(49, 51, 21);
		addFace(20, 21, 51);
		addFace(51, 19, 20);
		addFace(51, 50, 19);
		addFace(19, 50, 18);
		addFace(46, 24, 47);
		addFace(24, 25, 47);
		addFace(47, 25, 26);
		addFace(26, 45, 47);
		addFace(27, 45, 26);
		addFace(27, 19, 45);
		addFace(45, 19, 44);
		addFace(18, 44, 19);
		addFace(29, 40, 28);
		addFace(42, 40, 29);
		addFace(29, 9, 42);
		addFace(9, 8, 42);
		addFace(42, 8, 43);
		addFace(43, 8, 30);
		addFace(30, 31, 43);
		addFace(41, 43, 31);
		addFace(31, 25, 41);
		addFace(25, 24, 41);
		addFace(41, 24, 40);
		addFace(28, 40, 24);
		addFace(11, 54, 10);
		addFace(52, 10, 54);
		addFace(10, 52, 9);
		addFace(9, 52, 8);
		addFace(52, 53, 8);
		addFace(15, 8, 53);
		addFace(15, 53, 14);
		addFace(14, 53, 55);
		addFace(55, 13, 14);
		addFace(13, 55, 12);
		addFace(54, 12, 55);
		addFace(54, 11, 12);
		addFace(37, 30, 36);
		addFace(30, 37, 31);
		addFace(36, 30, 15);
		addFace(15, 14, 36);
		addFace(38, 36, 14);
		addFace(14, 21, 38);
		addFace(21, 20, 38);
		addFace(38, 20, 39);
		addFace(39, 20, 27);
		addFace(27, 26, 39);
		addFace(37, 39, 26);
		addFace(26, 31, 37);
		addFace(39, 36, 38);
		addFace(36, 39, 37);
		addFace(51, 49, 50);
		addFace(48, 50, 49);
		addFace(45, 44, 47);
		addFace(47, 44, 46);
		addFace(41, 40, 43);
		addFace(43, 40, 42);
		addFace(52, 54, 53);
		addFace(54, 55, 53);
	}

	logDebug << "Initialized (duration: "
			  << getTimeDouble() - start << "ms)"
			  << logEndl;
}


StrangeCube::~StrangeCube()
{
}
