#include "mesh.hpp"


#include <algorithm>
#include <logger.hpp>
#include "materials/diffusematerial.hpp"


logger_t modulesLogger = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


// ---------------------------- MESH ---------------------------- //

const MaterialPtr Mesh::DEFAULT_MATERIAL = new DiffuseMaterial();


Mesh::Mesh(const std::string& name,
		   const MaterialPtr& mat,
		   const IndexingType& indexType)
	: Object(Object::Type::MESH, name),
	  _vertices(),
	  _polygons(),
	  _material(mat),
	  _indexType(indexType)

{
	logDebug << "Mesh " << getName() << " created." << logEndl;
}


Mesh::Mesh(const Mesh& mesh)
	: Object(mesh),
	  _vertices(mesh._vertices),
	  _polygons(mesh._polygons),
	  _material(mesh._material),
	  _indexType(mesh._indexType)
{
	_reassignDataLinks();
	logDebug << "Mesh " << getName() << " copied from " << mesh.getName() << logEndl;
}


Mesh::Mesh(Mesh&& mesh)
	: Object(std::move(mesh)),
	  _vertices(std::move(mesh._vertices)),
	  _polygons(std::move(mesh._polygons)),
	  _material(std::move(mesh._material)),
	  _indexType(std::move(mesh._indexType))
{
	_reassignDataLinks();
	logDebug << "Mesh " << getName() << " moved." << logEndl;
}


Mesh::~Mesh()
{
	logDebug << "Mesh " << getName() << "with "
			  << _vertices.size() << " vertices, "
			  << _polygons.size() << " faces deleted."
			  << logEndl;
}


Mesh& Mesh::operator=(const Mesh& mesh)
{
	Object::operator=(mesh);
	_vertices = mesh._vertices;
	_polygons = mesh._polygons;
	_material = mesh._material;
	_indexType = mesh._indexType;
	_reassignDataLinks();

	logDebug << "Mesh " << getName() << " copied from " << mesh.getName() << logEndl;
	return (*this);
}


Mesh& Mesh::operator=(Mesh&& mesh)
{
	Object::operator=(mesh);
	_vertices = std::move(mesh._vertices);
	_polygons = std::move(mesh._polygons);
	_material = std::move(mesh._material);
	_indexType = std::move(mesh._indexType);
	_reassignDataLinks();

	logDebug << "Mesh " << getName() << " moved." << logEndl;
	return (*this);
}


Mesh::Vertex& Mesh::getVertex(const size_t& i)
{
	return _vertices[i];
}


const Mesh::Vertex& Mesh::getVertex(const size_t& i) const
{
	return _vertices[i];
}


const Mesh::Polygon& Mesh::getPolygon(const size_t& i1,
								const size_t& i2,
								const size_t& i3) const
{
	return *(_polygons.find({i1, i2, i3, nullptr}));
}


const Mesh::Vertices& Mesh::getVertices() const
{
	return _vertices;
}


const Mesh::Polygons& Mesh::getPolygons() const
{
	return _polygons;
}


const MaterialPtr& Mesh::getMaterial() const
{
	return _material;
}


const Mesh::IndexingType& Mesh::getIndexType() const
{
	return _indexType;
}


size_t Mesh::addVertex(const double& x,
					   const double& y,
					   const double& z,
					   const Color& color)
{
	const size_t idx = _vertices.size();
	_vertices.push_back({idx, x, y, z, color, this});
	return idx;
}


void Mesh::addPolygon(const size_t& i1,
				   const size_t& i2,
				   const size_t& i3)
{
	_polygons.insert({i1, i2, i3, this});
}


void Mesh::setMaterial(const MaterialPtr& material)
{
	_material = material;
}


void Mesh::recalculateNormals()
{
	// TODO: invert bad faces (their normals watching inside of a mesh).
	for (auto poly : _polygons)
	{
		const float ratio = glm::dot(poly.calculateCenter(), poly.calculateNormal());
		if (ratio < -0.5)
			poly.flip();
	}
}


void Mesh::applyPosition()
{
	// TODO: reset current mesh position to default.
	for (Vertex& v : _vertices)
		v._position += _position;
}


void Mesh::applyRotation()
{
	static const glm::mat4 I(1);
	const glm::mat4 xRotationMat = glm::rotate(I, _rotation.x, AXIS_X);
	const glm::mat4 yRotationMat = glm::rotate(I, _rotation.y, AXIS_Y);
	const glm::mat4 zRotationMat = glm::rotate(I, _rotation.z, AXIS_Z);

	for (Vertex& v : _vertices)
	{
		v._position = glm::vec3(xRotationMat * glm::vec4(v._position, 1.0));
		v._position = glm::vec3(yRotationMat * glm::vec4(v._position, 1.0));
		v._position = glm::vec3(zRotationMat * glm::vec4(v._position, 1.0));

		v._normal = glm::vec3(xRotationMat * glm::vec4(v._position, 0.0));
		v._normal = glm::vec3(yRotationMat * glm::vec4(v._position, 0.0));
		v._normal = glm::vec3(zRotationMat * glm::vec4(v._position, 0.0));
	}

	_rotation = Object::DEFAULT_ROTATION;
}


void Mesh::applyScale()
{
	for (Vertex& v : _vertices)
	{
		v._position *= _scale;
		v._normal = glm::normalize(v._normal / _scale);
	}

	_scale = Object::DEFAULT_SCALE;
}


void Mesh::_reassignDataLinks()
{
	for (Vertex& v : _vertices)
		v._linkedMesh = this;

	for (auto it : _polygons)
		it._linkedMesh = this;
}


// ---------------------------- MESH::VERTEX ---------------------------- //

Mesh::Vertex::Vertex(const size_t& idx,
					 const double& x,
					 const double& y,
					 const double& z,
					 const Color& color,
					 Mesh* mesh)
	: _idx(idx),
	  _position(x, y, z),
	  _normal(0.0, 0.0, 0.0),
	  _color(color),
	  _linkedMesh(mesh),
	  _linkedPolygons({})
{
}


Mesh::Vertex::~Vertex()
{
	for (Polygon* poly : _linkedPolygons)
		poly->_unlinkVertices();
}


const Object::vec& Mesh::Vertex::getPosition() const
{
	return _position;
}


const Object::vec& Mesh::Vertex::getNormal() const
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
	// TODO: get color from material.
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
	for (const Polygon* poly : _linkedPolygons)
		_normal += poly->calculateNormal();

	_normal = glm::normalize(_normal);
}


void Mesh::Vertex::_linkPolygon(Mesh::Polygon* poly)
{
	// FIXME: is it single poly in this vector? (Remove option may not work).
	_linkedPolygons.push_back(poly);
}


void Mesh::Vertex::_unlinkPolygon(Mesh::Polygon* poly)
{
	auto it = std::find(_linkedPolygons.begin(), _linkedPolygons.end(), poly);
	if (it == _linkedPolygons.end())
		return;

	_linkedPolygons.erase(it);
}


// ---------------------------- MESH::POLYGON ---------------------------- //

Mesh::Polygon::Polygon(const size_t& i1,
					   const size_t& i2,
					   const size_t& i3,
					   Mesh* mesh)
	: _idx1(std::min(i1, std::min(i2, i3))),
	  _idx2(std::max(i1, std::min(i2, i3))),
	  _idx3(std::max(i1, std::max(i2, i3))),
	  _linkedMesh(mesh)
{
	_linkVertices();
}


Mesh::Polygon::~Polygon()
{
	_unlinkVertices();
}


bool Mesh::Polygon::operator==(const Mesh::Polygon& p) const
{
	return ((_idx1 == p._idx1)
			&& (_idx2 == p._idx2)
			&& (_idx3 == p._idx3));
}


bool Mesh::Polygon::operator!=(const Mesh::Polygon& p) const
{
	return (!this->operator==(p));
}


bool Mesh::Polygon::operator<(const Mesh::Polygon& p) const
{
	return ((_idx1 < p._idx1)
			&& (_idx2 < p._idx2)
			&& (_idx3 < p._idx3));
}


const size_t& Mesh::Polygon::getIdx1() const
{
	return _idx1;
}


const size_t& Mesh::Polygon::getIdx2() const
{
	return _idx2;
}


const size_t& Mesh::Polygon::getIdx3() const
{
	return _idx3;
}


const Mesh::Vertex& Mesh::Polygon::getV1() const
{
	return _linkedMesh->getVertex(_idx1);
}


const Mesh::Vertex& Mesh::Polygon::getV2() const
{
	return _linkedMesh->getVertex(_idx2);
}


const Mesh::Vertex& Mesh::Polygon::getV3() const
{
	return _linkedMesh->getVertex(_idx3);
}


Mesh::Vertex& Mesh::Polygon::getV1()
{
	return _linkedMesh->getVertex(_idx1);
}


Mesh::Vertex& Mesh::Polygon::getV2()
{
	return _linkedMesh->getVertex(_idx2);
}


Mesh::Vertex& Mesh::Polygon::getV3()
{
	return _linkedMesh->getVertex(_idx3);
}


Object::vec Mesh::Polygon::calculateNormal() const
{
	const vec& v1 = getV1().getPosition();
	const vec& v2 = getV2().getPosition();
	const vec& v3 = getV3().getPosition();

	return std::move(glm::normalize(glm::cross((v2 - v1), (v3 - v1))));
}


Object::vec Mesh::Polygon::calculateCenter() const
{
	const vec& v1 = getV1().getPosition();
	const vec& v2 = getV2().getPosition();
	const vec& v3 = getV3().getPosition();

	return std::move((v1 + v2 + v3) / 3.0f);
}


void Mesh::Polygon::flip()
{
	std::swap(_idx2, _idx3);
}


void Mesh::Polygon::_linkVertices()
{
	if (_linkedMesh == nullptr)
		return;

	getV1()._linkPolygon(this);
	getV2()._linkPolygon(this);
	getV3()._linkPolygon(this);
}


void Mesh::Polygon::_unlinkVertices()
{
	if (_linkedMesh == nullptr)
		return;

	getV1()._unlinkPolygon(this);
	getV2()._unlinkPolygon(this);
	getV3()._unlinkPolygon(this);
}


size_t Mesh::Polygon::Hash::operator()(const Mesh::Polygon& p) const
{
	size_t h1 = std::hash<size_t>()(p._idx1);
	size_t h2 = std::hash<size_t>()(p._idx2);
	size_t h3 = std::hash<size_t>()(p._idx3);

	return (h1 ^ h2 ^ h3);
}
