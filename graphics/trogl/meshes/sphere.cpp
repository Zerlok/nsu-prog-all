#include "sphere.hpp"
#include <cmath>


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Sphere::Sphere(const float& radius,
			   const size_t& rowsNum,
			   const size_t& segmentsNum)
	: Mesh("Sphere")
{
	static const double maxPsy = 2.0 * M_PI;
	static const double maxPhi = M_PI;

	const size_t rows = (rowsNum != 0) ? rowsNum : 8;
	const size_t segments = (segmentsNum != 0) ? segmentsNum : rows*2;

	const double psyStep = maxPsy / (segments);
	const double phiStep = maxPhi / (rows+1);

	size_t polarPlusIdx;
	size_t polarMinusIdx;

	// Vertices.
	{
		float x = 0.0;
		float y = 1.0;
		float z = 0.0;

		polarPlusIdx = addVertex(x, y, z, mapU(x, y, z), mapV(x, y, z));
		for (double psy = 0; psy < maxPsy; psy += psyStep)
		{
			const double cosPsy = std::cos(psy);
			const double sinPsy = std::sin(psy);

			for (double phi = phiStep; phi < maxPhi; phi += phiStep)
			{
				x = std::sin(phi) * cosPsy;
				y = std::cos(phi) * 1.0;
				z = std::sin(phi) * sinPsy;

				addVertex(x, y, z, mapU(x, y, z), mapV(x, y, z));
			}
		}

		x = 0.0;
		y = -1.0;
		z = 0.0;
		polarMinusIdx = addVertex(x, y, z, mapU(x, y, z), mapV(x, y, z));
	}

	// Faces.
	{
		// Segment faces.
		size_t currOffset = 1;
		size_t nextOffset = currOffset + rows;
		for (size_t segNum = 0; segNum < segments-1; ++segNum)
		{
			for (size_t rowNum = 0; rowNum < rows-1; ++rowNum)
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

		for (size_t rowNum = 0; rowNum < rows-1; ++rowNum)
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
			addPolygon(polarPlusIdx, nextOffset, currOffset);
			currOffset = nextOffset;
			nextOffset = currOffset + rows;
			addPolygon(polarMinusIdx, currOffset-1, nextOffset-1);
		}

		addPolygon(polarPlusIdx, 1, currOffset);
		addPolygon(polarMinusIdx, polarMinusIdx - 1, rows);
	}

	setScale({radius, radius, radius});
	applyScale();
}


Sphere::~Sphere()
{
}


float Sphere::mapU(const float& x, const float& y, const float& z)
{
	return 0.5 + (std::atan2(z, x) / (2.0 * M_PI));
}


float Sphere::mapV(const float& x, const float& y, const float& z)
{
	return 0.5 - (std::asin(y) / M_PI);
}
