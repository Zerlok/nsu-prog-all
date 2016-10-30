#include "sphere.hpp"
#include <cmath>


#include <logger.hpp>


loggerModules lModules = loggerForModule(Logger::Level::INFO,
										 Logger::Description::FULL);


Sphere::Sphere(const float& radius,
			   const size_t& rows,
			   const size_t& segments)
	: Mesh("Sphere")
{
	static const Color c = Color::white;
	static const double maxPsy = 2 * M_PI;
	static const double maxPhi = M_PI;

	const double psyStep = maxPsy / (segments);
	const double phiStep = maxPhi / (rows+1);

	size_t polarPlusIdx;
	size_t polarMinusIdx;

	// Vertices.
	{
		polarPlusIdx = addVertex(0.0, radius, 0.0, c);
		for (double psy = 0; psy < maxPsy; psy += psyStep)
		{
			const double cosPsy = std::cos(psy) * radius;
			const double sinPsy = std::sin(psy) * radius;

			for (double phi = phiStep; phi < maxPhi; phi += phiStep)
			{
				const double sinPhi = std::sin(phi);
				addVertex(sinPhi * cosPsy,
						  std::cos(phi) * radius,
						  sinPhi * sinPsy,
						  c);
			}
		}
		polarMinusIdx = addVertex(0.0, -radius, 0.0, c);
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
				addFace(nextOffset + rowNum,
						nextOffset + rowNum + 1,
						currOffset + rowNum);
				addFace(currOffset + rowNum + 1,
						currOffset + rowNum,
						nextOffset + rowNum + 1);
			}

			currOffset = nextOffset;
			nextOffset = currOffset + rows;
		}

		for (size_t rowNum = 0; rowNum < rows-1; ++rowNum)
		{
			addFace(rowNum + 1,
					rowNum + 2,
					currOffset + rowNum);
			addFace(currOffset + rowNum + 1,
					currOffset + rowNum,
					rowNum + 2);
		}

		// Caps faces.
		currOffset = 1;
		nextOffset = currOffset + rows;
		for (size_t segNum = 0; segNum < segments-1; ++segNum)
		{
			addFace(polarPlusIdx, nextOffset, currOffset);
			currOffset = nextOffset;
			nextOffset = currOffset + rows;
			addFace(polarMinusIdx, currOffset-1, nextOffset-1);
		}

		addFace(polarPlusIdx, 1, currOffset);
		addFace(polarMinusIdx, polarMinusIdx - 1, rows);
	}
}


Sphere::~Sphere()
{
}

