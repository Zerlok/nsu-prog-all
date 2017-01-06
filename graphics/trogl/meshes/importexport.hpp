#ifndef __MESH_IMPORT_EXPORT_HPP__
#define __MESH_IMPORT_EXPORT_HPP__


#include <iostream>
#include <vector>
#include "core/mesh.hpp"


namespace meshIEformats
{
	using Integers = std::vector<int>;
	using Floats = std::vector<float>;
	using Strings = std::vector<std::string>;

	using Vertex = Mesh::Vertex;
	using Polygon = Mesh::Triple;
	using Vertices = std::vector<Vertex>;
	using Polygons = std::vector<Polygon>;

	static const Vertex defaultVertex(
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f);
	static const Polygon defaultPolygon(0, 0, 0);

	struct Obj
	{
		static const char comment;
		static const char columnSep;
		static const char polygonValueSep;
		static const std::string vertex;
		static const std::string uv;
		static const std::string normal;
		static const std::string polygon;

		struct defaults
		{
			static const float position;
			static const float normal;
			static const float uv;
		};
	};
}


class Importer
{
	public:
		Importer();
		~Importer();

//		void setFormat();

		Mesh parse(std::istream& in);

	private:
		void _parseVertexPosition(const std::string& values);
		void _parseVertexUV(const std::string& values);
		void _parseVertexNormal(const std::string& values);
		void _parsePolygon(const std::string& values);

		void _validateTriplesIndeces(meshIEformats::Integers& indices);
		void _refresh();

		std::string _line;
		size_t _lineNum;
		size_t _positionCntr;
		size_t _uvCntr;
		size_t _normalCntr;

		meshIEformats::Vertices _parsedVertices;
		meshIEformats::Vertices _vertices;
		meshIEformats::Polygons _polygons;
};


class Exporter
{
	public:
		Exporter();
		~Exporter();

//		void setFormat();

		void translate(std::ostream& out, const Mesh& mesh);

	private:
//		void _writeRow(std::ostream& out, const std::string& name, );
};


#endif // __MESH_IMPORT_EXPORT_HPP__
