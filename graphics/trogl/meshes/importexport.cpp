#include "importexport.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


const char meshIEformats::Obj::comment = '#';
const char meshIEformats::Obj::columnSep = ' ';
const char meshIEformats::Obj::polygonValueSep = '/';
const std::string meshIEformats::Obj::vertex = "v";
const std::string meshIEformats::Obj::uv = "vt";
const std::string meshIEformats::Obj::normal = "vn";
const std::string meshIEformats::Obj::polygon = "f";

const float meshIEformats::Obj::defaults::position = 1.0;
const float meshIEformats::Obj::defaults::normal = 0.0;
const float meshIEformats::Obj::defaults::uv = 0.0;


namespace stringutils
{
	template<>
	struct TypeTraits<int>
	{
		int parse(const std::string& val)
		{
			if (!val.empty())
				return std::stoi(val);
			else
				return 0;
		}
	};

	template<>
	struct TypeTraits<float>
	{
		float parse(const std::string& val)
		{
			return std::stof(val);
		}
	};
}


using namespace meshIEformats;


logger_t moduleLogger = loggerModule(loggerLDebug, (loggerDLevel | loggerDModul));


// ----------------------------- IMPORTER ----------------------------- //

Importer::Importer()
{
	_refresh();
}


Importer::~Importer()
{
}


Mesh Importer::parse(std::istream& in)
{
	std::string name;
	std::string values;

	while (std::getline(in, _line))
	{
		if (_line.empty()
				|| (_line.front() == Obj::comment))
		{
			logDebug << "Empty line#" << _lineNum << ": '" << _line << "' skipped."
					 << logEndl;
			continue;
		}

		size_t colSep = _line.find(Obj::columnSep);
		if (colSep == std::string::npos)
		{
			logWarning << "Invalid values at line#" << _lineNum << ": '" << _line << "' - 2 columns required, skipped."
					   << logEndl;
			continue;
		}

		name = _line.substr(0, colSep);
		values = _line.substr(colSep + 1, _line.size() - colSep - 1);
		logDebug << "Parsing row " << _lineNum << ": " << name << " | " << values << logEndl;

		if (name == Obj::vertex)
			_parseVertexPosition(values);
		else if (name == Obj::uv)
			_parseVertexUV(values);
		else if (name == Obj::normal)
			_parseVertexNormal(values);
		else if (name == Obj::polygon)
			_parsePolygon(values);
		else
		{
			logWarning << "Invalid column name '" << name
					   << "' at line#" << _lineNum
					   << ": '" << _line << "', skipped."
					   << logEndl;
			continue;
		}

		++_lineNum;
	}

	Mesh mesh;
	for (const Vertex& v : _vertices)
		mesh.addVertex(v);

	for (const Polygon& p : _polygons)
		mesh.addPolygon(p);

	_refresh();
	return std::move(mesh);
}


void Importer::_parseVertexPosition(const std::string& values)
{
	Floats floats = stringutils::split<float>(values, Obj::columnSep, true);
	if (floats.empty())
	{
		logWarning << "Invalid '" << Obj::vertex
				   << "' float values at line#" << _lineNum
				   << ": '" << _line << "', skipped."
				   << logEndl;
		return;
	}

	floats.resize(3, Obj::defaults::position);
	Vertex& v = vectorutils::getOrFill(_parsedVertices, _positionCntr, defaultVertex);
	v.setPosition({floats[0], floats[1], floats[2]});
	++_positionCntr;
}


void Importer::_parseVertexUV(const std::string& values)
{
	Floats floats = stringutils::split<float>(values, Obj::columnSep, true);
	if (floats.empty())
	{
		logWarning << "Invalid '" << Obj::normal
				   << "' float values at line#" << _lineNum
				   << ": '" << _line << "', skipped."
				   << logEndl;
		return;
	}

	floats.resize(2, Obj::defaults::uv);
	Vertex& v = vectorutils::getOrFill(_parsedVertices, _uvCntr, defaultVertex);
	v.setUV({floats[0], floats[1]});
	++_uvCntr;
}


void Importer::_parseVertexNormal(const std::string& values)
{
	Floats floats = stringutils::split<float>(values, Obj::columnSep, true);
	if (floats.empty())
	{
		logWarning << "Invalid '" << Obj::normal
				   << "' float values at line#" << _lineNum
				   << ": '" << _line << "', skipped."
				   << logEndl;
		return;
	}

	floats.resize(3, Obj::defaults::normal);
	Vertex& v = vectorutils::getOrFill(_parsedVertices, _normalCntr, defaultVertex);
	v.setNormal({floats[0], floats[1], floats[2]});
	++_normalCntr;
}


void Importer::_parsePolygon(const std::string& values)
{
	const Strings tmps = stringutils::split(values, Obj::columnSep, true);
	if (tmps.size() < 3)
	{
		logWarning << "Invalid polygon at line#" << _lineNum
				   << ": '" << _line << "' - 3 vertices at least required to build polygon, skipped."
				   << logEndl;
		return;
	}

	const size_t last = _vertices.size();
	Integers indices;

	for (const std::string& val : tmps)
	{
		indices = stringutils::split<int>(val, Obj::polygonValueSep, false);
		if (indices.empty())
		{
			logWarning << "Invalid '" << Obj::polygon
					   << "' integer values at line#" << _lineNum
					   << ": '" << _line << "', skipped."
					   << logEndl;
			return;
		}
		indices.resize(3, 0);
		_validateTriplesIndeces(indices);

		logDebug << "Parsed face vertex indices: " << indices
				 << " at line#" << _lineNum
				 << ": '" << _line << "'"
				 << logEndl;

		_vertices.push_back(Vertex(
				_parsedVertices[indices[0]].getPosition(),
				_parsedVertices[indices[2]].getNormal(),
				_parsedVertices[indices[1]].getUV()
		));
	}

	for (size_t i = last+1; i < _vertices.size(); ++i)
		_polygons.push_back({last, i, i+1});
}


void Importer::_validateTriplesIndeces(Integers& indices)
{
	const int verticesNum = _parsedVertices.size();
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int& v = indices[i];
		if (v < 0)
			v += verticesNum;
		else if (v == 0)
			v = indices[i-1];
		else
			v -= 1;

		if ((v < 0)
				|| (v > verticesNum))
		{
			logWarning << "Invalid vertex index '" << v
					   << "' at line#" << _lineNum
					   << ": '" << _line << "', skipped."
					   << logEndl;
			continue;
		}
	}
}


void Importer::_refresh()
{
	_line.clear();
	_lineNum = 0;

	_positionCntr = 0;
	_uvCntr = 0;
	_normalCntr = 0;

	_parsedVertices.clear();
	_vertices.clear();
	_polygons.clear();
}


// ----------------------------- EXPORTER ----------------------------- //

Exporter::Exporter()
{
}


Exporter::~Exporter()
{
}


void Exporter::translate(std::ostream& out, const Mesh& mesh)
{
}
