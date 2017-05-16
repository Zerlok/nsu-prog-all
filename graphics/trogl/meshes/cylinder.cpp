#include "cylinder.hpp"


#include "shaders/screwshader.hpp"


Cylinder::Cylinder(const size_t& segments,
				   const size_t& rows)
	: Mesh("Cylinder")
{
	const double psyStep = 2.0 * M_PI / (segments);
	const double heightStep = 1.0 / (rows+1);

	size_t northIdx;
	size_t southIdx;

	// Vertices.
	{
		northIdx = addVertex(
				0.0, 1.0, 0.0,
				0.0, 1.0, 0.0);

		// Cups.
		float x;
		float z;

		for (size_t s = 0; s < segments; ++s)
		{
			x = std::cos(psyStep * s);
			z = std::sin(psyStep * s);

			addVertex(x, 1.0, z, 0.0, 1.0, 0.0);
			addVertex(x, 1.0, z, x, 0.0, z);
			addVertex(x, -1.0, z, x, 0.0, z);
			addVertex(x, -1.0, z, 0.0, -1.0, 0.0);
		}

		southIdx = addVertex(
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0);
	}

	// Faces.
	{
		// Segment faces.
		size_t currOffset = 1;
		size_t nextOffset = currOffset + rows;
		for (size_t segNum = 0; segNum < segments-1; ++segNum)
		{
			for (size_t rowNum = 1; rowNum < rows-1; ++rowNum)
			{
				addPolygon(nextOffset + rowNum,
						nextOffset + rowNum + 1,
						currOffset + rowNum);
				addPolygon(currOffset + rowNum + 1,
						currOffset + rowNum,
						nextOffset + rowNum + 1);
			}

			currOffset = nextOffset;
			nextOffset = currOffset + rows;
		}

		// Joint
		for (size_t rowNum = 1; rowNum < rows-1; ++rowNum)
		{
			addPolygon(rowNum + 1,
					rowNum + 2,
					currOffset + rowNum);
			addPolygon(currOffset + rowNum + 1,
					currOffset + rowNum,
					rowNum + 2);
		}

		// Caps faces.
		currOffset = 1;
		nextOffset = currOffset + rows;
		for (size_t segNum = 0; segNum < segments-1; ++segNum)
		{
			addPolygon(northIdx, nextOffset, currOffset);
			currOffset = nextOffset;
			nextOffset = currOffset + rows;
			addPolygon(southIdx, currOffset-1, nextOffset-1);
		}

		addPolygon(northIdx, 1, currOffset);
		addPolygon(southIdx, southIdx - 1, rows);
	}

	setScale({radius, radius, radius});
	applyScale();
}
