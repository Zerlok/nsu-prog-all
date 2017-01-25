#include "cylinder.hpp"


#include "shaders/screwshader.hpp"


Cylinder::Cylinder()
	: Mesh("Cylinder")
{
	static const MaterialPtr mat = new Material("ScrewMaterial", Color::white, new ScrewShader());
	setMaterial(mat);

	// Vertices.
	{
		addVertex(0.0, -1.0, 1.0);
		addVertex(0.0, 1.0, 1.0);
		addVertex(0.195, -1.0, 0.981);
		addVertex(0.195, 1.0, 0.981);
		addVertex(0.383, -1.0, 0.924);
		addVertex(0.383, 1.0, 0.924);
		addVertex(0.556, -1.0, 0.831);
		addVertex(0.556, 1.0, 0.831);
		addVertex(0.707, -1.0, 0.707);
		addVertex(0.707, 1.0, 0.707);
		addVertex(0.831, -1.0, 0.556);
		addVertex(0.831, 1.0, 0.556);
		addVertex(0.924, -1.0, 0.383);
		addVertex(0.924, 1.0, 0.383);
		addVertex(0.981, -1.0, 0.195);
		addVertex(0.981, 1.0, 0.195);
		addVertex(1.0, -1.0, 0.0);
		addVertex(1.0, 1.0, 0.0);
		addVertex(0.981, -1.0, -0.195);
		addVertex(0.981, 1.0, -0.195);
		addVertex(0.924, -1.0, -0.383);
		addVertex(0.924, 1.0, -0.383);
		addVertex(0.831, -1.0, -0.556);
		addVertex(0.831, 1.0, -0.556);
		addVertex(0.707, -1.0, -0.707);
		addVertex(0.707, 1.0, -0.707);
		addVertex(0.556, -1.0, -0.831);
		addVertex(0.556, 1.0, -0.831);
		addVertex(0.383, -1.0, -0.924);
		addVertex(0.383, 1.0, -0.924);
		addVertex(0.195, -1.0, -0.981);
		addVertex(0.195, 1.0, -0.981);
		addVertex(-0.0, -1.0, -1.0);
		addVertex(-0.0, 1.0, -1.0);
		addVertex(-0.195, -1.0, -0.981);
		addVertex(-0.195, 1.0, -0.981);
		addVertex(-0.383, -1.0, -0.924);
		addVertex(-0.383, 1.0, -0.924);
		addVertex(-0.556, -1.0, -0.831);
		addVertex(-0.556, 1.0, -0.831);
		addVertex(-0.707, -1.0, -0.707);
		addVertex(-0.707, 1.0, -0.707);
		addVertex(-0.831, -1.0, -0.556);
		addVertex(-0.831, 1.0, -0.556);
		addVertex(-0.924, -1.0, -0.383);
		addVertex(-0.924, 1.0, -0.383);
		addVertex(-0.981, -1.0, -0.195);
		addVertex(-0.981, 1.0, -0.195);
		addVertex(-1.0, -1.0, 0.0);
		addVertex(-1.0, 1.0, 0.0);
		addVertex(-0.981, -1.0, 0.195);
		addVertex(-0.981, 1.0, 0.195);
		addVertex(-0.924, -1.0, 0.383);
		addVertex(-0.924, 1.0, 0.383);
		addVertex(-0.831, -1.0, 0.556);
		addVertex(-0.831, 1.0, 0.556);
		addVertex(-0.707, -1.0, 0.707);
		addVertex(-0.707, 1.0, 0.707);
		addVertex(-0.556, -1.0, 0.831);
		addVertex(-0.556, 1.0, 0.831);
		addVertex(-0.383, -1.0, 0.924);
		addVertex(-0.383, 1.0, 0.924);
		addVertex(-0.195, -1.0, 0.981);
		addVertex(-0.195, 1.0, 0.981);
		addVertex(0.0, -1.0, 0.0);
		addVertex(0.0, 1.0, 0.0);
	}

	// Faces.
	{
		addPolygon(1, 2, 3);
		addPolygon(3, 4, 5);
		addPolygon(5, 6, 7);
		addPolygon(7, 8, 9);
		addPolygon(9, 10, 11);
		addPolygon(11, 12, 13);
		addPolygon(13, 14, 15);
		addPolygon(15, 16, 17);
		addPolygon(17, 18, 19);
		addPolygon(19, 20, 21);
		addPolygon(21, 22, 23);
		addPolygon(23, 24, 25);
		addPolygon(25, 26, 27);
		addPolygon(27, 28, 29);
		addPolygon(29, 30, 31);
		addPolygon(31, 32, 33);
		addPolygon(33, 34, 35);
		addPolygon(35, 36, 37);
		addPolygon(37, 38, 39);
		addPolygon(39, 40, 41);
		addPolygon(41, 42, 43);
		addPolygon(43, 44, 45);
		addPolygon(45, 46, 47);
		addPolygon(47, 48, 49);
		addPolygon(49, 50, 51);
		addPolygon(51, 52, 53);
		addPolygon(53, 54, 55);
		addPolygon(55, 56, 57);
		addPolygon(57, 58, 59);
		addPolygon(59, 60, 61);
		addPolygon(63, 0, 1);
		addPolygon(61, 62, 63);
		addPolygon(34, 64, 36);
		addPolygon(16, 64, 18);
		addPolygon(52, 64, 54);
		addPolygon(8, 64, 10);
		addPolygon(26, 64, 28);
		addPolygon(44, 64, 46);
		addPolygon(0, 64, 2);
		addPolygon(62, 64, 0);
		addPolygon(18, 64, 20);
		addPolygon(36, 64, 38);
		addPolygon(54, 64, 56);
		addPolygon(10, 64, 12);
		addPolygon(28, 64, 30);
		addPolygon(46, 64, 48);
		addPolygon(2, 64, 4);
		addPolygon(20, 64, 22);
		addPolygon(38, 64, 40);
		addPolygon(56, 64, 58);
		addPolygon(12, 64, 14);
		addPolygon(30, 64, 32);
		addPolygon(48, 64, 50);
		addPolygon(4, 64, 6);
		addPolygon(22, 64, 24);
		addPolygon(40, 64, 42);
		addPolygon(58, 64, 60);
		addPolygon(14, 64, 16);
		addPolygon(32, 64, 34);
		addPolygon(50, 64, 52);
		addPolygon(6, 64, 8);
		addPolygon(24, 64, 26);
		addPolygon(42, 64, 44);
		addPolygon(60, 64, 62);
		addPolygon(53, 65, 51);
		addPolygon(35, 65, 33);
		addPolygon(17, 65, 15);
		addPolygon(61, 65, 59);
		addPolygon(43, 65, 41);
		addPolygon(25, 65, 23);
		addPolygon(7, 65, 5);
		addPolygon(51, 65, 49);
		addPolygon(33, 65, 31);
		addPolygon(15, 65, 13);
		addPolygon(59, 65, 57);
		addPolygon(41, 65, 39);
		addPolygon(23, 65, 21);
		addPolygon(5, 65, 3);
		addPolygon(49, 65, 47);
		addPolygon(31, 65, 29);
		addPolygon(13, 65, 11);
		addPolygon(57, 65, 55);
		addPolygon(39, 65, 37);
		addPolygon(21, 65, 19);
		addPolygon(1, 65, 63);
		addPolygon(3, 65, 1);
		addPolygon(47, 65, 45);
		addPolygon(29, 65, 27);
		addPolygon(11, 65, 9);
		addPolygon(55, 65, 53);
		addPolygon(37, 65, 35);
		addPolygon(19, 65, 17);
		addPolygon(63, 65, 61);
		addPolygon(45, 65, 43);
		addPolygon(27, 65, 25);
		addPolygon(9, 65, 7);
		addPolygon(0, 2, 1);
		addPolygon(2, 4, 3);
		addPolygon(4, 6, 5);
		addPolygon(6, 8, 7);
		addPolygon(8, 10, 9);
		addPolygon(10, 12, 11);
		addPolygon(12, 14, 13);
		addPolygon(14, 16, 15);
		addPolygon(16, 18, 17);
		addPolygon(18, 20, 19);
		addPolygon(20, 22, 21);
		addPolygon(22, 24, 23);
		addPolygon(24, 26, 25);
		addPolygon(26, 28, 27);
		addPolygon(28, 30, 29);
		addPolygon(30, 32, 31);
		addPolygon(32, 34, 33);
		addPolygon(34, 36, 35);
		addPolygon(36, 38, 37);
		addPolygon(38, 40, 39);
		addPolygon(40, 42, 41);
		addPolygon(42, 44, 43);
		addPolygon(44, 46, 45);
		addPolygon(46, 48, 47);
		addPolygon(48, 50, 49);
		addPolygon(50, 52, 51);
		addPolygon(52, 54, 53);
		addPolygon(54, 56, 55);
		addPolygon(56, 58, 57);
		addPolygon(58, 60, 59);
		addPolygon(62, 0, 63);
		addPolygon(60, 62, 61);
	}
}


Cylinder::~Cylinder()
{
}
