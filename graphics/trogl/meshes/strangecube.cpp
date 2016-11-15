#include "strangecube.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


StrangeCube::StrangeCube()
	: Mesh("StrangeCube")
{
	const double start = getTimeDouble();

	// Vertices.
	{
		addVertex(-1.0, -1.0, -1.0);
		addVertex(-1.0, -1.0, 1.0);
		addVertex(-1.0, 1.0, -1.0);
		addVertex(-1.0, 1.0, 1.0);
		addVertex(1.0, -1.0, -1.0);
		addVertex(1.0, -1.0, 1.0);
		addVertex(1.0, 1.0, -1.0);
		addVertex(1.0, 1.0, 1.0);
		addVertex(-1.0, -1.0, -0.333);
		addVertex(-1.0, -1.0, 0.333);
		addVertex(-1.0, -0.333, 1.0);
		addVertex(-1.0, 0.333, 1.0);
		addVertex(-1.0, 1.0, 0.333);
		addVertex(-1.0, 1.0, -0.333);
		addVertex(-1.0, 0.333, -1.0);
		addVertex(-1.0, -0.333, -1.0);
		addVertex(-0.333, 1.0, 1.0);
		addVertex(0.333, 1.0, 1.0);
		addVertex(1.0, 1.0, 0.333);
		addVertex(1.0, 1.0, -0.333);
		addVertex(0.333, 1.0, -1.0);
		addVertex(-0.333, 1.0, -1.0);
		addVertex(1.0, 0.333, 1.0);
		addVertex(1.0, -0.333, 1.0);
		addVertex(1.0, -1.0, 0.333);
		addVertex(1.0, -1.0, -0.333);
		addVertex(1.0, -0.333, -1.0);
		addVertex(1.0, 0.333, -1.0);
		addVertex(0.333, -1.0, 1.0);
		addVertex(-0.333, -1.0, 1.0);
		addVertex(-0.333, -1.0, -1.0);
		addVertex(0.333, -1.0, -1.0);
		addVertex(0.333, -0.333, 1.0);
		addVertex(-0.333, -0.333, 1.0);
		addVertex(0.333, 0.333, 1.0);
		addVertex(-0.333, 0.333, 1.0);
		addVertex(-0.333, -0.333, -1.0);
		addVertex(0.333, -0.333, -1.0);
		addVertex(-0.333, 0.333, -1.0);
		addVertex(0.333, 0.333, -1.0);
		addVertex(0.333, -1.0, 0.333);
		addVertex(0.333, -1.0, -0.333);
		addVertex(-0.333, -1.0, 0.333);
		addVertex(-0.333, -1.0, -0.333);
		addVertex(1.0, 0.333, 0.333);
		addVertex(1.0, 0.333, -0.333);
		addVertex(1.0, -0.333, 0.333);
		addVertex(1.0, -0.333, -0.333);
		addVertex(-0.333, 1.0, 0.333);
		addVertex(-0.333, 1.0, -0.333);
		addVertex(0.333, 1.0, 0.333);
		addVertex(0.333, 1.0, -0.333);
		addVertex(-1.0, -0.333, 0.333);
		addVertex(-1.0, -0.333, -0.333);
		addVertex(-1.0, 0.333, 0.333);
		addVertex(-1.0, 0.333, -0.333);
	}

	// Faces.
	{
		addPolygon(23, 46, 22);
		addPolygon(5, 24, 23);
		addPolygon(44, 22, 46);
		addPolygon(46, 23, 24);
		addPolygon(44, 18, 22);
		addPolygon(18, 7, 22);
		addPolygon(24, 5, 28);
		addPolygon(1, 9, 29);
		addPolygon(1, 10, 9);
		addPolygon(3, 12, 11);
		addPolygon(12, 3, 16);
		addPolygon(7, 18, 17);
		addPolygon(7, 17, 22);
		addPolygon(3, 11, 16);
		addPolygon(1, 29, 10);
		addPolygon(5, 23, 28);
		addPolygon(6, 27, 20);
		addPolygon(6, 19, 27);
		addPolygon(6, 20, 19);
		addPolygon(2, 14, 13);
		addPolygon(2, 13, 21);
		addPolygon(2, 21, 14);
		addPolygon(0, 15, 30);
		addPolygon(0, 8, 15);
		addPolygon(8, 0, 30);
		addPolygon(4, 31, 26);
		addPolygon(4, 26, 25);
		addPolygon(4, 25, 31);
		addPolygon(23, 22, 34);
		addPolygon(32, 23, 34);
		addPolygon(32, 28, 23);
		addPolygon(10, 29, 33);
		addPolygon(22, 17, 34);
		addPolygon(28, 32, 29);
		addPolygon(32, 33, 29);
		addPolygon(34, 17, 35);
		addPolygon(11, 33, 35);
		addPolygon(10, 33, 11);
		addPolygon(35, 16, 11);
		addPolygon(17, 16, 35);
		addPolygon(35, 32, 34);
		addPolygon(32, 35, 33);
		addPolygon(17, 48, 16);
		addPolygon(50, 48, 17);
		addPolygon(50, 17, 18);
		addPolygon(16, 48, 12);
		addPolygon(49, 12, 48);
		addPolygon(12, 49, 13);
		addPolygon(21, 13, 49);
		addPolygon(49, 51, 21);
		addPolygon(20, 21, 51);
		addPolygon(51, 19, 20);
		addPolygon(51, 50, 19);
		addPolygon(19, 50, 18);
		addPolygon(46, 24, 47);
		addPolygon(24, 25, 47);
		addPolygon(47, 25, 26);
		addPolygon(26, 45, 47);
		addPolygon(27, 45, 26);
		addPolygon(27, 19, 45);
		addPolygon(45, 19, 44);
		addPolygon(18, 44, 19);
		addPolygon(29, 40, 28);
		addPolygon(42, 40, 29);
		addPolygon(29, 9, 42);
		addPolygon(9, 8, 42);
		addPolygon(42, 8, 43);
		addPolygon(43, 8, 30);
		addPolygon(30, 31, 43);
		addPolygon(41, 43, 31);
		addPolygon(31, 25, 41);
		addPolygon(25, 24, 41);
		addPolygon(41, 24, 40);
		addPolygon(28, 40, 24);
		addPolygon(11, 54, 10);
		addPolygon(52, 10, 54);
		addPolygon(10, 52, 9);
		addPolygon(9, 52, 8);
		addPolygon(52, 53, 8);
		addPolygon(15, 8, 53);
		addPolygon(15, 53, 14);
		addPolygon(14, 53, 55);
		addPolygon(55, 13, 14);
		addPolygon(13, 55, 12);
		addPolygon(54, 12, 55);
		addPolygon(54, 11, 12);
		addPolygon(37, 30, 36);
		addPolygon(30, 37, 31);
		addPolygon(36, 30, 15);
		addPolygon(15, 14, 36);
		addPolygon(38, 36, 14);
		addPolygon(14, 21, 38);
		addPolygon(21, 20, 38);
		addPolygon(38, 20, 39);
		addPolygon(39, 20, 27);
		addPolygon(27, 26, 39);
		addPolygon(37, 39, 26);
		addPolygon(26, 31, 37);
		addPolygon(39, 36, 38);
		addPolygon(36, 39, 37);
		addPolygon(51, 49, 50);
		addPolygon(48, 50, 49);
		addPolygon(45, 44, 47);
		addPolygon(47, 44, 46);
		addPolygon(41, 40, 43);
		addPolygon(43, 40, 42);
		addPolygon(52, 54, 53);
		addPolygon(54, 55, 53);
	}

	logDebug << "Initialized (duration: "
			  << getTimeDouble() - start << "ms)"
			  << logEndl;
}


StrangeCube::~StrangeCube()
{
}
