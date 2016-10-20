#include "mesh.hpp"

#include <logger.hpp>


Mesh::Mesh(const std::string& name,
		   const glm::vec3& pos,
		   const glm::vec3& rot,
		   const glm::vec3& sca)
	: Object(Object::Type::MESH, name)
{
	logDebug << "Mesh object created" << logEnd;
	setPosition(pos);
	setRotation(rot);
	setScale(sca);
}


Mesh::Mesh(const Mesh& mesh)
	: Object(mesh),
	  _vertices(mesh._vertices),
	  _faces(mesh._faces),
	  _material(mesh._material)
{
	_reassignDataReferences();
}


Mesh::Mesh(Mesh&& mesh)
	: Object(std::move(mesh)),
	  _vertices(std::move(mesh._vertices)),
	  _faces(std::move(mesh._faces)),
	  _material(std::move(mesh._material))
{
}


Mesh::~Mesh()
{
	logDebug << "Mesh object removed and it's "
			 << _vertices.size() << " vertices, "
			 << _faces.size() << " faces"
			 << logEnd;
}


Mesh& Mesh::operator=(const Mesh& mesh)
{
	Object::operator=(mesh);
	_vertices = mesh._vertices;
	_faces = mesh._faces;
	_reassignDataReferences();

	return (*this);
}


Mesh& Mesh::operator=(Mesh&& mesh)
{
	Object::operator=(mesh);
	_vertices = std::move(mesh._vertices);
	_faces = std::move(mesh._faces);
	_reassignDataReferences();

	return (*this);
}


const Mesh::Vertex& Mesh::getVertex(const size_t& i) const
{
	return _vertices[i % _vertices.size()];
}


const Mesh::Vertices& Mesh::getVertices() const
{
	return _vertices;
}


void Mesh::addVertex(const Mesh::Vertex& vertex)
{
	_vertices.push_back(vertex);
	_vertices.back()._idx = _vertices.size();
	_vertices.back()._mesh = this;
}


const Mesh::Face&Mesh::getFace(const size_t& i) const
{
	return _faces[i % _faces.size()];
}


const Mesh::Faces&Mesh::getFaces() const
{
	return _faces;
}


void Mesh::addFace(const Mesh::Face& face)
{
	_faces.push_back(face);
	_faces.back()._mesh = this;
}


void Mesh::recalculateNormals()
{

}


void Mesh::_reassignDataReferences()
{
	for (Vertex& v : _vertices)
		v._mesh = this;

	for (Face& f : _faces)
		f._mesh = this;
}


Mesh::Vertex::Vertex(const float& x, const float& y, const float& z, const Color& color)
	: _position(x, y, z),
	  _color(color),
	  _idx(0),
	  _mesh(nullptr)
{
}


Mesh::Vertex::Vertex(const glm::vec3& pos, const Color& color)
	: _position(pos),
	  _color(color),
	  _idx(0),
	  _mesh(nullptr)
{
}


Mesh::Vertex::Vertex(const Mesh::Vertex& v)
	: _position(v._position),
	  _color(v._color),
	  _idx(v._idx),
	  _mesh(v._mesh)
{
}


Mesh::Vertex::Vertex(Mesh::Vertex&& v)
	: _position(std::move(v._position)),
	  _color(std::move(v._color)),
	  _idx(std::move(v._idx)),
	  _mesh(nullptr)
{
}


Mesh::Vertex::~Vertex()
{
}


Mesh::Vertex& Mesh::Vertex::operator=(const Mesh::Vertex& v)
{
	_idx = v._idx;
	_position = v._position;
	_color = v._color;
	_mesh = v._mesh;

	return (*this);
}


Mesh::Vertex& Mesh::Vertex::operator=(Mesh::Vertex&& v)
{
	_idx = std::move(v._idx);
	_position = std::move(v._position);
	_color = std::move(v._color);
	_mesh = nullptr;

	return (*this);
}


const glm::vec3& Mesh::Vertex::getPosition() const
{
	return _position;
}


void Mesh::Vertex::setPosition(const glm::vec3& pos)
{
	_position = pos;
}


const Color& Mesh::Vertex::getColor() const
{
	return _color;
}


void Mesh::Vertex::setColor(const Color& color)
{
	_color = color;
}


const size_t& Mesh::Vertex::getIndex() const
{
	return _idx;
}


Mesh::Face::Face(const Vertex& f,
				 const Vertex& s,
				 const Vertex& t)
	: _first(f.getIndex()),
	  _second(s.getIndex()),
	  _third(t.getIndex()),
	  _mesh(nullptr)
{
}


Mesh::Face::Face(const size_t& f, const size_t& s, const size_t& t)
	: _first(f),
	  _second(s),
	  _third(t)
{
}


Mesh::Face::Face(const Mesh::Face& f)
	: _first(f._first),
	  _second(f._second),
	  _third(f._third),
	  _mesh(f._mesh)
{
}


Mesh::Face::Face(Mesh::Face&& f)
	: _first(std::move(f._first)),
	  _second(std::move(f._second)),
	  _third(std::move(f._third)),
	  _mesh(nullptr)
{
}


Mesh::Face::~Face()
{
}


Mesh::Face& Mesh::Face::operator=(const Mesh::Face& f)
{
	_first = f._first;
	_second = f._second;
	_third = f._third;
	_mesh = f._mesh;

	return (*this);
}


Mesh::Face& Mesh::Face::operator=(Mesh::Face&& f)
{
	_first = std::move(f._first);
	_second = std::move(f._second);
	_third = std::move(f._third);
	_mesh = nullptr;

	return (*this);
}


const size_t& Mesh::Face::getFirstIndex() const
{
	return _first;
}


const size_t& Mesh::Face::getSecondIndex() const
{
	return _second;
}


const size_t& Mesh::Face::getThirdIndex() const
{
	return _third;
}


glm::vec3 Mesh::Face::getNormal() const
{
	if (!_mesh)
		return glm::vec3();

	const Vertex& f = _mesh->getVertex(_first);
	const Vertex& s = _mesh->getVertex(_second);
	const Vertex& t = _mesh->getVertex(_third);

	const glm::vec3 left = (t.getPosition() - f.getPosition());
	const glm::vec3 right = (s.getPosition() - f.getPosition());

	return glm::cross(right, left);
}


void Mesh::Face::flip()
{
	std::swap(_second, _third);
}
