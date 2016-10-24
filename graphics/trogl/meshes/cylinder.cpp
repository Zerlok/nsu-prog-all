#include "cylinder.hpp"


#include "common/color.hpp"
#include "shaders/metamorphose_shader.h"


Cylinder::Cylinder(const Color& c1,
				   const Color& c2)
	: Mesh("Cylinder")
{
	static const MaterialPtr mat = new Material("CylMat", new MetamorphoseShader());
	setMaterial(mat);

	// Vertices.
	{
		addVertex(Vertex(0.0, -1.0, 1.0, c2));
		addVertex(Vertex(0.0, 1.0, 1.0, c1));
		addVertex(Vertex(0.195, -1.0, 0.981, c2));
		addVertex(Vertex(0.195, 1.0, 0.981, c2));
		addVertex(Vertex(0.383, -1.0, 0.924, c2));
		addVertex(Vertex(0.383, 1.0, 0.924, c1));
		addVertex(Vertex(0.556, -1.0, 0.831, c1));
		addVertex(Vertex(0.556, 1.0, 0.831, c2));
		addVertex(Vertex(0.707, -1.0, 0.707, c1));
		addVertex(Vertex(0.707, 1.0, 0.707, c2));
		addVertex(Vertex(0.831, -1.0, 0.556, c1));
		addVertex(Vertex(0.831, 1.0, 0.556, c1));
		addVertex(Vertex(0.924, -1.0, 0.383, c2));
		addVertex(Vertex(0.924, 1.0, 0.383, c1));
		addVertex(Vertex(0.981, -1.0, 0.195, c2));
		addVertex(Vertex(0.981, 1.0, 0.195, c2));
		addVertex(Vertex(1.0, -1.0, 0.0, c2));
		addVertex(Vertex(1.0, 1.0, 0.0, c1));
		addVertex(Vertex(0.981, -1.0, -0.195, c2));
		addVertex(Vertex(0.981, 1.0, -0.195, c2));
		addVertex(Vertex(0.924, -1.0, -0.383, c1));
		addVertex(Vertex(0.924, 1.0, -0.383, c1));
		addVertex(Vertex(0.831, -1.0, -0.556, c1));
		addVertex(Vertex(0.831, 1.0, -0.556, c2));
		addVertex(Vertex(0.707, -1.0, -0.707, c1));
		addVertex(Vertex(0.707, 1.0, -0.707, c1));
		addVertex(Vertex(0.556, -1.0, -0.831, c1));
		addVertex(Vertex(0.556, 1.0, -0.831, c1));
		addVertex(Vertex(0.383, -1.0, -0.924, c1));
		addVertex(Vertex(0.383, 1.0, -0.924, c1));
		addVertex(Vertex(0.195, -1.0, -0.981, c2));
		addVertex(Vertex(0.195, 1.0, -0.981, c1));
		addVertex(Vertex(-0.0, -1.0, -1.0, c1));
		addVertex(Vertex(-0.0, 1.0, -1.0, c1));
		addVertex(Vertex(-0.195, -1.0, -0.981, c1));
		addVertex(Vertex(-0.195, 1.0, -0.981, c2));
		addVertex(Vertex(-0.383, -1.0, -0.924, c1));
		addVertex(Vertex(-0.383, 1.0, -0.924, c1));
		addVertex(Vertex(-0.556, -1.0, -0.831, c1));
		addVertex(Vertex(-0.556, 1.0, -0.831, c2));
		addVertex(Vertex(-0.707, -1.0, -0.707, c1));
		addVertex(Vertex(-0.707, 1.0, -0.707, c2));
		addVertex(Vertex(-0.831, -1.0, -0.556, c2));
		addVertex(Vertex(-0.831, 1.0, -0.556, c1));
		addVertex(Vertex(-0.924, -1.0, -0.383, c1));
		addVertex(Vertex(-0.924, 1.0, -0.383, c2));
		addVertex(Vertex(-0.981, -1.0, -0.195, c1));
		addVertex(Vertex(-0.981, 1.0, -0.195, c2));
		addVertex(Vertex(-1.0, -1.0, 0.0, c2));
		addVertex(Vertex(-1.0, 1.0, 0.0, c1));
		addVertex(Vertex(-0.981, -1.0, 0.195, c1));
		addVertex(Vertex(-0.981, 1.0, 0.195, c2));
		addVertex(Vertex(-0.924, -1.0, 0.383, c2));
		addVertex(Vertex(-0.924, 1.0, 0.383, c1));
		addVertex(Vertex(-0.831, -1.0, 0.556, c2));
		addVertex(Vertex(-0.831, 1.0, 0.556, c1));
		addVertex(Vertex(-0.707, -1.0, 0.707, c1));
		addVertex(Vertex(-0.707, 1.0, 0.707, c2));
		addVertex(Vertex(-0.556, -1.0, 0.831, c1));
		addVertex(Vertex(-0.556, 1.0, 0.831, c2));
		addVertex(Vertex(-0.383, -1.0, 0.924, c1));
		addVertex(Vertex(-0.383, 1.0, 0.924, c2));
		addVertex(Vertex(-0.195, -1.0, 0.981, c1));
		addVertex(Vertex(-0.195, 1.0, 0.981, c1));
		addVertex(Vertex(0.0, -1.0, 0.0, c1));
		addVertex(Vertex(0.0, 1.0, 0.0, c2));
	}

	// Faces.
	{
		addFace(Face(1, 2, 3));
		addFace(Face(3, 4, 5));
		addFace(Face(5, 6, 7));
		addFace(Face(7, 8, 9));
		addFace(Face(9, 10, 11));
		addFace(Face(11, 12, 13));
		addFace(Face(13, 14, 15));
		addFace(Face(15, 16, 17));
		addFace(Face(17, 18, 19));
		addFace(Face(19, 20, 21));
		addFace(Face(21, 22, 23));
		addFace(Face(23, 24, 25));
		addFace(Face(25, 26, 27));
		addFace(Face(27, 28, 29));
		addFace(Face(29, 30, 31));
		addFace(Face(31, 32, 33));
		addFace(Face(33, 34, 35));
		addFace(Face(35, 36, 37));
		addFace(Face(37, 38, 39));
		addFace(Face(39, 40, 41));
		addFace(Face(41, 42, 43));
		addFace(Face(43, 44, 45));
		addFace(Face(45, 46, 47));
		addFace(Face(47, 48, 49));
		addFace(Face(49, 50, 51));
		addFace(Face(51, 52, 53));
		addFace(Face(53, 54, 55));
		addFace(Face(55, 56, 57));
		addFace(Face(57, 58, 59));
		addFace(Face(59, 60, 61));
		addFace(Face(63, 0, 1));
		addFace(Face(61, 62, 63));
		addFace(Face(34, 64, 36));
		addFace(Face(16, 64, 18));
		addFace(Face(52, 64, 54));
		addFace(Face(8, 64, 10));
		addFace(Face(26, 64, 28));
		addFace(Face(44, 64, 46));
		addFace(Face(0, 64, 2));
		addFace(Face(62, 64, 0));
		addFace(Face(18, 64, 20));
		addFace(Face(36, 64, 38));
		addFace(Face(54, 64, 56));
		addFace(Face(10, 64, 12));
		addFace(Face(28, 64, 30));
		addFace(Face(46, 64, 48));
		addFace(Face(2, 64, 4));
		addFace(Face(20, 64, 22));
		addFace(Face(38, 64, 40));
		addFace(Face(56, 64, 58));
		addFace(Face(12, 64, 14));
		addFace(Face(30, 64, 32));
		addFace(Face(48, 64, 50));
		addFace(Face(4, 64, 6));
		addFace(Face(22, 64, 24));
		addFace(Face(40, 64, 42));
		addFace(Face(58, 64, 60));
		addFace(Face(14, 64, 16));
		addFace(Face(32, 64, 34));
		addFace(Face(50, 64, 52));
		addFace(Face(6, 64, 8));
		addFace(Face(24, 64, 26));
		addFace(Face(42, 64, 44));
		addFace(Face(60, 64, 62));
		addFace(Face(53, 65, 51));
		addFace(Face(35, 65, 33));
		addFace(Face(17, 65, 15));
		addFace(Face(61, 65, 59));
		addFace(Face(43, 65, 41));
		addFace(Face(25, 65, 23));
		addFace(Face(7, 65, 5));
		addFace(Face(51, 65, 49));
		addFace(Face(33, 65, 31));
		addFace(Face(15, 65, 13));
		addFace(Face(59, 65, 57));
		addFace(Face(41, 65, 39));
		addFace(Face(23, 65, 21));
		addFace(Face(5, 65, 3));
		addFace(Face(49, 65, 47));
		addFace(Face(31, 65, 29));
		addFace(Face(13, 65, 11));
		addFace(Face(57, 65, 55));
		addFace(Face(39, 65, 37));
		addFace(Face(21, 65, 19));
		addFace(Face(1, 65, 63));
		addFace(Face(3, 65, 1));
		addFace(Face(47, 65, 45));
		addFace(Face(29, 65, 27));
		addFace(Face(11, 65, 9));
		addFace(Face(55, 65, 53));
		addFace(Face(37, 65, 35));
		addFace(Face(19, 65, 17));
		addFace(Face(63, 65, 61));
		addFace(Face(45, 65, 43));
		addFace(Face(27, 65, 25));
		addFace(Face(9, 65, 7));
		addFace(Face(0, 2, 1));
		addFace(Face(2, 4, 3));
		addFace(Face(4, 6, 5));
		addFace(Face(6, 8, 7));
		addFace(Face(8, 10, 9));
		addFace(Face(10, 12, 11));
		addFace(Face(12, 14, 13));
		addFace(Face(14, 16, 15));
		addFace(Face(16, 18, 17));
		addFace(Face(18, 20, 19));
		addFace(Face(20, 22, 21));
		addFace(Face(22, 24, 23));
		addFace(Face(24, 26, 25));
		addFace(Face(26, 28, 27));
		addFace(Face(28, 30, 29));
		addFace(Face(30, 32, 31));
		addFace(Face(32, 34, 33));
		addFace(Face(34, 36, 35));
		addFace(Face(36, 38, 37));
		addFace(Face(38, 40, 39));
		addFace(Face(40, 42, 41));
		addFace(Face(42, 44, 43));
		addFace(Face(44, 46, 45));
		addFace(Face(46, 48, 47));
		addFace(Face(48, 50, 49));
		addFace(Face(50, 52, 51));
		addFace(Face(52, 54, 53));
		addFace(Face(54, 56, 55));
		addFace(Face(56, 58, 57));
		addFace(Face(58, 60, 59));
		addFace(Face(62, 0, 63));
		addFace(Face(60, 62, 61));
	}
}


Cylinder::~Cylinder()
{
}
