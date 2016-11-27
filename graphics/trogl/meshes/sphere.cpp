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
		polarPlusIdx = addVertex(0.0, radius, 0.0);
		for (double psy = 0; psy < maxPsy; psy += psyStep)
		{
			const double cosPsy = std::cos(psy) * radius;
			const double sinPsy = std::sin(psy) * radius;

			for (double phi = phiStep; phi < maxPhi; phi += phiStep)
			{
				const double sinPhi = std::sin(phi);
				addVertex(sinPhi * cosPsy,
						  std::cos(phi) * radius,
						  sinPhi * sinPsy);
			}
		}
		polarMinusIdx = addVertex(0.0, -radius, 0.0);
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
}


Sphere::~Sphere()
{
}
