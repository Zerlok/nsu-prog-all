#include "cylinder.hpp"


#include "common/color.hpp"
#include "shaders/metamorphoseshader.hpp"


Cylinder::Cylinder(const Color& c1,
				   const Color& c2)
	: Mesh("Cylinder")
{
	static const MaterialPtr mat = new Material("CylMat", new MetamorphoseShader());
	setMaterial(mat);

	// Vertices.
	{
		addVertex(0.0, -1.0, 1.0, c2);
		addVertex(0.0, 1.0, 1.0, c1);
		addVertex(0.195, -1.0, 0.981, c2);
		addVertex(0.195, 1.0, 0.981, c2);
		addVertex(0.383, -1.0, 0.924, c2);
		addVertex(0.383, 1.0, 0.924, c1);
		addVertex(0.556, -1.0, 0.831, c1);
		addVertex(0.556, 1.0, 0.831, c2);
		addVertex(0.707, -1.0, 0.707, c1);
		addVertex(0.707, 1.0, 0.707, c2);
		addVertex(0.831, -1.0, 0.556, c1);
		addVertex(0.831, 1.0, 0.556, c1);
		addVertex(0.924, -1.0, 0.383, c2);
		addVertex(0.924, 1.0, 0.383, c1);
		addVertex(0.981, -1.0, 0.195, c2);
		addVertex(0.981, 1.0, 0.195, c2);
		addVertex(1.0, -1.0, 0.0, c2);
		addVertex(1.0, 1.0, 0.0, c1);
		addVertex(0.981, -1.0, -0.195, c2);
		addVertex(0.981, 1.0, -0.195, c2);
		addVertex(0.924, -1.0, -0.383, c1);
		addVertex(0.924, 1.0, -0.383, c1);
		addVertex(0.831, -1.0, -0.556, c1);
		addVertex(0.831, 1.0, -0.556, c2);
		addVertex(0.707, -1.0, -0.707, c1);
		addVertex(0.707, 1.0, -0.707, c1);
		addVertex(0.556, -1.0, -0.831, c1);
		addVertex(0.556, 1.0, -0.831, c1);
		addVertex(0.383, -1.0, -0.924, c1);
		addVertex(0.383, 1.0, -0.924, c1);
		addVertex(0.195, -1.0, -0.981, c2);
		addVertex(0.195, 1.0, -0.981, c1);
		addVertex(-0.0, -1.0, -1.0, c1);
		addVertex(-0.0, 1.0, -1.0, c1);
		addVertex(-0.195, -1.0, -0.981, c1);
		addVertex(-0.195, 1.0, -0.981, c2);
		addVertex(-0.383, -1.0, -0.924, c1);
		addVertex(-0.383, 1.0, -0.924, c1);
		addVertex(-0.556, -1.0, -0.831, c1);
		addVertex(-0.556, 1.0, -0.831, c2);
		addVertex(-0.707, -1.0, -0.707, c1);
		addVertex(-0.707, 1.0, -0.707, c2);
		addVertex(-0.831, -1.0, -0.556, c2);
		addVertex(-0.831, 1.0, -0.556, c1);
		addVertex(-0.924, -1.0, -0.383, c1);
		addVertex(-0.924, 1.0, -0.383, c2);
		addVertex(-0.981, -1.0, -0.195, c1);
		addVertex(-0.981, 1.0, -0.195, c2);
		addVertex(-1.0, -1.0, 0.0, c2);
		addVertex(-1.0, 1.0, 0.0, c1);
		addVertex(-0.981, -1.0, 0.195, c1);
		addVertex(-0.981, 1.0, 0.195, c2);
		addVertex(-0.924, -1.0, 0.383, c2);
		addVertex(-0.924, 1.0, 0.383, c1);
		addVertex(-0.831, -1.0, 0.556, c2);
		addVertex(-0.831, 1.0, 0.556, c1);
		addVertex(-0.707, -1.0, 0.707, c1);
		addVertex(-0.707, 1.0, 0.707, c2);
		addVertex(-0.556, -1.0, 0.831, c1);
		addVertex(-0.556, 1.0, 0.831, c2);
		addVertex(-0.383, -1.0, 0.924, c1);
		addVertex(-0.383, 1.0, 0.924, c2);
		addVertex(-0.195, -1.0, 0.981, c1);
		addVertex(-0.195, 1.0, 0.981, c1);
		addVertex(0.0, -1.0, 0.0, c1);
		addVertex(0.0, 1.0, 0.0, c2);
	}

	// Faces.
	{
		addFace(1, 2, 3);
		addFace(3, 4, 5);
		addFace(5, 6, 7);
		addFace(7, 8, 9);
		addFace(9, 10, 11);
		addFace(11, 12, 13);
		addFace(13, 14, 15);
		addFace(15, 16, 17);
		addFace(17, 18, 19);
		addFace(19, 20, 21);
		addFace(21, 22, 23);
		addFace(23, 24, 25);
		addFace(25, 26, 27);
		addFace(27, 28, 29);
		addFace(29, 30, 31);
		addFace(31, 32, 33);
		addFace(33, 34, 35);
		addFace(35, 36, 37);
		addFace(37, 38, 39);
		addFace(39, 40, 41);
		addFace(41, 42, 43);
		addFace(43, 44, 45);
		addFace(45, 46, 47);
		addFace(47, 48, 49);
		addFace(49, 50, 51);
		addFace(51, 52, 53);
		addFace(53, 54, 55);
		addFace(55, 56, 57);
		addFace(57, 58, 59);
		addFace(59, 60, 61);
		addFace(63, 0, 1);
		addFace(61, 62, 63);
		addFace(34, 64, 36);
		addFace(16, 64, 18);
		addFace(52, 64, 54);
		addFace(8, 64, 10);
		addFace(26, 64, 28);
		addFace(44, 64, 46);
		addFace(0, 64, 2);
		addFace(62, 64, 0);
		addFace(18, 64, 20);
		addFace(36, 64, 38);
		addFace(54, 64, 56);
		addFace(10, 64, 12);
		addFace(28, 64, 30);
		addFace(46, 64, 48);
		addFace(2, 64, 4);
		addFace(20, 64, 22);
		addFace(38, 64, 40);
		addFace(56, 64, 58);
		addFace(12, 64, 14);
		addFace(30, 64, 32);
		addFace(48, 64, 50);
		addFace(4, 64, 6);
		addFace(22, 64, 24);
		addFace(40, 64, 42);
		addFace(58, 64, 60);
		addFace(14, 64, 16);
		addFace(32, 64, 34);
		addFace(50, 64, 52);
		addFace(6, 64, 8);
		addFace(24, 64, 26);
		addFace(42, 64, 44);
		addFace(60, 64, 62);
		addFace(53, 65, 51);
		addFace(35, 65, 33);
		addFace(17, 65, 15);
		addFace(61, 65, 59);
		addFace(43, 65, 41);
		addFace(25, 65, 23);
		addFace(7, 65, 5);
		addFace(51, 65, 49);
		addFace(33, 65, 31);
		addFace(15, 65, 13);
		addFace(59, 65, 57);
		addFace(41, 65, 39);
		addFace(23, 65, 21);
		addFace(5, 65, 3);
		addFace(49, 65, 47);
		addFace(31, 65, 29);
		addFace(13, 65, 11);
		addFace(57, 65, 55);
		addFace(39, 65, 37);
		addFace(21, 65, 19);
		addFace(1, 65, 63);
		addFace(3, 65, 1);
		addFace(47, 65, 45);
		addFace(29, 65, 27);
		addFace(11, 65, 9);
		addFace(55, 65, 53);
		addFace(37, 65, 35);
		addFace(19, 65, 17);
		addFace(63, 65, 61);
		addFace(45, 65, 43);
		addFace(27, 65, 25);
		addFace(9, 65, 7);
		addFace(0, 2, 1);
		addFace(2, 4, 3);
		addFace(4, 6, 5);
		addFace(6, 8, 7);
		addFace(8, 10, 9);
		addFace(10, 12, 11);
		addFace(12, 14, 13);
		addFace(14, 16, 15);
		addFace(16, 18, 17);
		addFace(18, 20, 19);
		addFace(20, 22, 21);
		addFace(22, 24, 23);
		addFace(24, 26, 25);
		addFace(26, 28, 27);
		addFace(28, 30, 29);
		addFace(30, 32, 31);
		addFace(32, 34, 33);
		addFace(34, 36, 35);
		addFace(36, 38, 37);
		addFace(38, 40, 39);
		addFace(40, 42, 41);
		addFace(42, 44, 43);
		addFace(44, 46, 45);
		addFace(46, 48, 47);
		addFace(48, 50, 49);
		addFace(50, 52, 51);
		addFace(52, 54, 53);
		addFace(54, 56, 55);
		addFace(56, 58, 57);
		addFace(58, 60, 59);
		addFace(62, 0, 63);
		addFace(60, 62, 61);
	}
}


Cylinder::~Cylinder()
{
}
