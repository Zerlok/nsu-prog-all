#include "mesh.hpp"


#include <logger.hpp>
#include "materials/diffusematerial.hpp"


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


const MaterialPtr Mesh::DEFAULT_MATERIAL = new DiffuseMaterial();


Mesh::Mesh(const std::string& name,
		   const MaterialPtr& mat, const IndexingType& indexType)
	: Object(Object::Type::MESH, name),
	  _vertices(),
	  _faces(),
	  _material(mat),
	  _indexType(indexType)

{
	logModule << "Mesh object created" << logEndl;
}


Mesh::Mesh(const Mesh& mesh)
	: Object(mesh),
	  _vertices(mesh._vertices),
	  _faces(mesh._faces),
	  _material(mesh._material),
	  _indexType(mesh._indexType)
{
	_reassignDataReferences();
}


Mesh::Mesh(Mesh&& mesh)
	: Object(std::move(mesh)),
	  _vertices(std::move(mesh._vertices)),
	  _faces(std::move(mesh._faces)),
	  _material(std::move(mesh._material)),
	  _indexType(std::move(mesh._indexType))
{
	_reassignDataReferences();
}


Mesh::~Mesh()
{
	logModule << "Mesh object with "
			  << _vertices.size() << " vertices, "
			  << _faces.size() << " faces removed"
			  << logEndl;
}


Mesh& Mesh::operator=(const Mesh& mesh)
{
	Object::operator=(mesh);
	_vertices = mesh._vertices;
	_faces = mesh._faces;
	_material = mesh._material;
	_indexType = mesh._indexType;
	_reassignDataReferences();

	return (*this);
}


Mesh& Mesh::operator=(Mesh&& mesh)
{
	Object::operator=(mesh);
	_vertices = std::move(mesh._vertices);
	_faces = std::move(mesh._faces);
	_material = std::move(mesh._material);
	_indexType = std::move(mesh._indexType);
	_reassignDataReferences();

	return (*this);
}


const Mesh::Vertex& Mesh::getVertex(const size_t& i) const
{
	return _vertices[i];
}


const Mesh::Face& Mesh::getFace(const size_t& i1,
								const size_t& i2,
								const size_t& i3) const
{
	return _faces.at({i1, i2, i3});
}


const Mesh::Vertices& Mesh::getVertices() const
{
	return _vertices;
}


const Mesh::Faces&Mesh::getFaces() const
{
	return _faces;
}


const MaterialPtr& Mesh::getMaterial() const
{
	return _material;
}


size_t Mesh::addVertex(const float& x,
					   const float& y,
					   const float& z,
					   const Color& color)
{
	const size_t idx = _vertices.size();
	_vertices.push_back(Vertex(idx, x, y, z, color, this));
	return idx;
}


void Mesh::addFace(const size_t& i1,
				   const size_t& i2,
				   const size_t& i3)
{
	Vertex& v1 = _vertices[i1];
	Vertex& v2 = _vertices[i2];
	Vertex& v3 = _vertices[i3];
	_faces.insert({{i1, i2, i3}, Face(v1, v2, v3, this)});
}


void Mesh::setMaterial(const MaterialPtr& material)
{
	_material = material;
}


void Mesh::recalculateNormals()
{
}


void Mesh::applyPosition()
{
	for (Vertex& v : _vertices)
		v._position += _position;
}


void Mesh::applyRotation()
{
	glm::mat4 xRotationMat(1);
	glm::mat4 yRotationMat(1);
	glm::mat4 zRotationMat(1);

	xRotationMat = glm::rotate(xRotationMat, _rotation.x, AXIS_X);
	yRotationMat = glm::rotate(yRotationMat, _rotation.y, AXIS_Y);
	zRotationMat = glm::rotate(zRotationMat, _rotation.z, AXIS_Z);

	for (Vertex& v : _vertices)
	{
		v._position = glm::vec3(xRotationMat * glm::vec4(v._position, 1.0));
		v._position = glm::vec3(yRotationMat * glm::vec4(v._position, 1.0));
		v._position = glm::vec3(zRotationMat * glm::vec4(v._position, 1.0));

		v._normal = glm::vec3(xRotationMat * glm::vec4(v._position, 0.0));
		v._normal = glm::vec3(yRotationMat * glm::vec4(v._position, 0.0));
		v._normal = glm::vec3(zRotationMat * glm::vec4(v._position, 0.0));
	}
}


void Mesh::applyScale()
{
	for (Vertex& v : _vertices)
	{
		v._position *= _scale;
		v._normal = glm::normalize(v._normal / _scale);
	}
}


void Mesh::_reassignDataReferences()
{
	for (Vertex& v : _vertices)
		v._linkedMesh = this;

	for (auto it : _faces)
		it.second._linkedMesh = this;
}


Mesh::Vertex::Vertex(const size_t& idx,
					 const float& x,
					 const float& y,
					 const float& z,
					 const Color& color,
					 Mesh* mesh)
	: _idx(idx),
	  _position(x, y, z),
	  _normal(0.0, 0.0, 0.0),
	  _color(color),
	  _linkedMesh(mesh)
{
}


Mesh::Vertex::Vertex(const Mesh::Vertex& v)
	: _idx(v._idx),
	  _position(v._position),
	  _normal(v._normal),
	  _color(v._color),
	  _linkedMesh(v._linkedMesh)
{
}


Mesh::Vertex::Vertex(Mesh::Vertex&& v)
	: _idx(std::move(v._idx)),
	  _position(std::move(v._position)),
	  _normal(std::move(v._normal)),
	  _color(std::move(v._color)),
	  _linkedMesh(v._linkedMesh)
{
}


Mesh::Vertex::~Vertex()
{
}


Mesh::Vertex& Mesh::Vertex::operator=(const Mesh::Vertex& v)
{
	_idx = v._idx;
	_position = v._position;
	_normal = v._normal;
	_color = v._color;
	_linkedMesh = v._linkedMesh;

	return (*this);
}


Mesh::Vertex& Mesh::Vertex::operator=(Mesh::Vertex&& v)
{
	_idx = std::move(v._idx);
	_position = std::move(v._position);
	_normal = std::move(v._normal);
	_color = std::move(v._color);
	_linkedMesh = v._linkedMesh;

	return (*this);
}


const glm::vec3& Mesh::Vertex::getPosition() const
{
	return _position;
}


const glm::vec3& Mesh::Vertex::getNormal() const
{
	return _normal;
}


void Mesh::Vertex::setPosition(const glm::vec3& pos)
{
	_position = pos;
	_recalculateNormal();
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


void Mesh::Vertex::_recalculateNormal()
{
	_normal = glm::vec3(0.0, 0.0, 0.0);
	for (const Face* f : _linkedFaces)
		_normal += f->getNormal();

	_normal = glm::normalize(_normal);
}


Mesh::Face::Face(Mesh::Vertex& v1,
				 Mesh::Vertex& v2,
				 Mesh::Vertex& v3,
				 Mesh* mesh)
	: _first(&v1),
	  _second(&v2),
	  _third(&v3),
	  _linkedMesh(mesh),
	  _normal(_calculateNormal())
{
	_first->_linkedFaces.push_back(this);
	_second->_linkedFaces.push_back(this);
	_third->_linkedFaces.push_back(this);

	_first->_recalculateNormal();
	_second->_recalculateNormal();
	_third->_recalculateNormal();
}


Mesh::Face::Face(const Mesh::Face& f)
	: _first(f._first),
	  _second(f._second),
	  _third(f._third),
	  _linkedMesh(f._linkedMesh),
	  _normal(f._normal)
{
}


Mesh::Face::Face(Mesh::Face&& f)
	: _first(f._first),
	  _second(f._second),
	  _third(f._third),
	  _linkedMesh(f._linkedMesh),
	  _normal(std::move(f._normal))
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
	_linkedMesh = f._linkedMesh;
	_normal = f._normal;

	return (*this);
}


Mesh::Face& Mesh::Face::operator=(Mesh::Face&& f)
{
	_first = f._first;
	_second = f._second;
	_third = f._third;
	_linkedMesh = f._linkedMesh;
	_normal = std::move(f._normal);

	return (*this);
}


const Mesh::Vertex& Mesh::Face::getFirst() const
{
	return (*_first);
}


const Mesh::Vertex& Mesh::Face::getSecond() const
{
	return (*_second);
}


const Mesh::Vertex& Mesh::Face::getThird() const
{
	return (*_third);
}


const glm::vec3& Mesh::Face::getNormal() const
{
	return _normal;
}


void Mesh::Face::flip()
{
	std::swap(_second, _third);
	_normal *= -1;
}


glm::vec3 Mesh::Face::_calculateNormal()
{
	if (_linkedMesh == nullptr)
		return std::move(glm::vec3(0.0, 0.0, 0.0));

	const glm::vec3 leftEdge = (_third->getPosition() - _first->getPosition());
	const glm::vec3 rightEdge = (_second->getPosition() - _first->getPosition());

	return std::move(glm::normalize(glm::cross(rightEdge, leftEdge)));
}
