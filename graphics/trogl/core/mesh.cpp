#include "mesh.hpp"


#include <algorithm>
#include <logger.hpp>
#include "materials/diffusematerial.hpp"


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


// ---------------------------- MESH ---------------------------- //

const MaterialPtr Mesh::DEFAULT_MATERIAL = new DiffuseMaterial(Color(200, 200, 200));


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
	_reassignData();
	logDebug << "Mesh " << getName() << " copied from " << mesh.getName() << logEndl;
}


Mesh::Mesh(Mesh&& mesh)
	: Object(std::move(mesh)),
	  _vertices(std::move(mesh._vertices)),
	  _polygons(std::move(mesh._polygons)),
	  _material(std::move(mesh._material)),
	  _indexType(std::move(mesh._indexType))
{
	_reassignData();
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
	_reassignData();

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
	_reassignData();

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
	return getPolygon({i1, i2, i3});
}


const Mesh::Polygon& Mesh::getPolygon(const Mesh::Triple& tr) const
{
	return _polygons.find(tr)->second;
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


size_t Mesh::addVertex(const float& x,
					   const float& y,
					   const float& z,
					   const float& u,
					   const float& v)
{
	const size_t idx = _vertices.size();
	_vertices.push_back({idx, x, y, z, u, v, this});
	return idx;
}


bool Mesh::addPolygon(const size_t& i1,
					  const size_t& i2,
					  const size_t& i3)
{
	const Triple tr {i1, i2, i3};
	const Polygons::iterator it = _polygons.find(tr);
	if (it != _polygons.end())
		return false;

	Polygon poly {tr, this};
	_polygons.insert({tr, poly});
	poly._linkVertices();

	return true;
}


void Mesh::setMaterial(const MaterialPtr& material)
{
	_material = material;
}


void Mesh::recalculateNormals()
{
	// TODO: update normal recalculation algorithm.
	/*
	 * Choice 1: Find a good polygon (or polygon at center), then start to compare
	 * angle between current polygon and adjacent with angle between therirs normals.
	 * It will be easy to see then, which normal is good and which is bad.
	 */
	for (Polygons::value_type& it : _polygons)
	{
		Polygon& poly = it.second;
		const float ratio = glm::dot(poly.calculateCenter(), poly.calculateNormal());
		if (ratio < -0.5)
			poly.flip();
	}
}


void Mesh::applyPosition()
{
	for (Vertex& v : _vertices)
		v._position += _position;

	_position = Object::DEFAULT_POSITION;
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
	}

	_rotation = Object::DEFAULT_ROTATION;
}


void Mesh::applyScale()
{
	for (Vertex& v : _vertices)
	{
		v._position *= _scale;
	}

	_scale = Object::DEFAULT_SCALE;
}


void Mesh::_reassignData()
{
	for (Vertex& v : _vertices)
		v._linkedMesh = this;

	for (Polygons::value_type& it : _polygons)
		it.second._linkedMesh = this;
}


// ---------------------------- MESH::VERTEX ---------------------------- //

Mesh::Vertex::Vertex(const size_t& idx,
					 const float& x,
					 const float& y,
					 const float& z,
					 const float& u,
					 const float& v,
					 Mesh* mesh)
	: _idx(idx),
	  _position(x, y, z),
	  _uvMapping(u, v),
	  _linkedTriples(),
	  _linkedMesh(mesh)
{
}


Mesh::Vertex::Vertex(const Mesh::Vertex& v)
	: _idx(v._idx),
	  _position(v._position),
	  _uvMapping(v._uvMapping),
	  _linkedTriples(v._linkedTriples),
	  _linkedMesh(v._linkedMesh)
{
}


Mesh::Vertex::Vertex(Mesh::Vertex&& v)
	: _idx(std::move(v._idx)),
	  _position(std::move(v._position)),
	  _uvMapping(std::move(v._uvMapping)),
	  _linkedTriples(std::move(v._linkedTriples)),
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
	_uvMapping = v._uvMapping;
	_linkedTriples = v._linkedTriples;
	_linkedMesh = v._linkedMesh;

	return (*this);
}


Mesh::Vertex& Mesh::Vertex::operator=(Mesh::Vertex&& v)
{
	_idx = std::move(v._idx);
	_position = std::move(v._position);
	_uvMapping = std::move(v._uvMapping);
	_linkedTriples = std::move(v._linkedTriples);
	_linkedMesh = v._linkedMesh;

	return (*this);
}


const size_t& Mesh::Vertex::getIndex() const
{
	return _idx;
}


const Object::vec& Mesh::Vertex::getPosition() const
{
	return _position;
}


Object::vec Mesh::Vertex::getNormal() const
{
	vec normal = vec(0.0, 0.0, 0.0);
	for (const Triple& tr : _linkedTriples)
		normal += _linkedMesh->getPolygon(tr).calculateNormal();

	return std::move(glm::normalize(normal));
}


const glm::vec2& Mesh::Vertex::getUVMapping() const
{
	return _uvMapping;
}


void Mesh::Vertex::setPosition(const glm::vec3& pos)
{
	_position = pos;
}


// ---------------------------- MESH::TRIPLE ---------------------------- //

Mesh::Triple::Triple(const size_t& i1,
					 const size_t& i2,
					 const size_t& i3)
	: idx1(i1),
	  idx2(i2),
	  idx3(i3)
{
}


Mesh::Triple::Triple(const Mesh::Triple& tr)
	: idx1(tr.idx1),
	  idx2(tr.idx2),
	  idx3(tr.idx3)
{
}


Mesh::Triple::Triple(Mesh::Triple&& tr)
	: idx1(std::move(tr.idx1)),
	  idx2(std::move(tr.idx2)),
	  idx3(std::move(tr.idx3))
{
}


Mesh::Triple::~Triple()
{
}


Mesh::Triple& Mesh::Triple::operator=(const Mesh::Triple& tr)
{
	idx1 = tr.idx1;
	idx2 = tr.idx2;
	idx3 = tr.idx3;

	return (*this);
}


Mesh::Triple& Mesh::Triple::operator=(Mesh::Triple&& tr)
{
	idx1 = std::move(tr.idx1);
	idx2 = std::move(tr.idx2);
	idx3 = std::move(tr.idx3);

	return (*this);
}


bool Mesh::Triple::operator==(const Mesh::Triple& tr) const
{
	return ((getFirst() == tr.getFirst())
			&& (getSecond() == tr.getSecond())
			&& (getThird() == tr.getThird()));
}


bool Mesh::Triple::operator!=(const Mesh::Triple& tr) const
{
	return (!this->operator==(tr));
}


bool Mesh::Triple::operator<(const Mesh::Triple& tr) const
{
	return ((getFirst() < tr.getFirst())
			&& (getSecond() < tr.getSecond())
			&& (getThird() < tr.getThird()));
}


size_t Mesh::Triple::getFirst() const
{
	return 	std::min(idx1, std::min(idx2, idx3));
}


size_t Mesh::Triple::getSecond() const
{
	return std::max(idx1, std::min(idx2, idx3));
}


size_t Mesh::Triple::getThird() const
{
	return std::max(idx1, std::max(idx2, idx3));
}


size_t Mesh::Triple::Hash::operator()(const Mesh::Triple& tr) const
{
	const size_t h1 = std::hash<size_t>()(tr.idx1);
	const size_t h2 = std::hash<size_t>()(tr.idx2);
	const size_t h3 = std::hash<size_t>()(tr.idx3);

	return (h1 ^ h2 ^ h3);
}


// ---------------------------- MESH::POLYGON ---------------------------- //

Mesh::Polygon::Polygon(const size_t& i1,
					   const size_t& i2,
					   const size_t& i3,
					   Mesh* mesh)
	: _triple(i1, i2, i3),
	  _linkedMesh(mesh)
{
}


Mesh::Polygon::Polygon(const Mesh::Triple& tr,
					   Mesh* mesh)
	: _triple(tr),
	  _linkedMesh(mesh)
{
}


Mesh::Polygon::Polygon(const Mesh::Polygon& p)
	: _triple(p._triple),
	  _linkedMesh(p._linkedMesh)
{
}


Mesh::Polygon::Polygon(Mesh::Polygon&& p)
	: _triple(std::move(p._triple)),
	  _linkedMesh(p._linkedMesh)
{
}


Mesh::Polygon::~Polygon()
{
}


Mesh::Polygon& Mesh::Polygon::operator=(const Mesh::Polygon& p)
{
	_triple = p._triple;
	_linkedMesh = p._linkedMesh;

	return (*this);
}


Mesh::Polygon& Mesh::Polygon::operator=(Mesh::Polygon&& p)
{
	_triple = std::move(p._triple);
	_linkedMesh = p._linkedMesh;

	return (*this);
}


bool Mesh::Polygon::operator==(const Mesh::Polygon& p) const
{
	return (_triple == p._triple);
}


bool Mesh::Polygon::operator!=(const Mesh::Polygon& p) const
{
	return (!this->operator==(p));
}


const size_t& Mesh::Polygon::getIdx1() const
{
	return _triple.idx1;
}


const size_t& Mesh::Polygon::getIdx2() const
{
	return _triple.idx2;
}


const size_t& Mesh::Polygon::getIdx3() const
{
	return _triple.idx3;
}


const Mesh::Vertex& Mesh::Polygon::getV1() const
{
	return _linkedMesh->getVertex(_triple.idx1);
}


const Mesh::Vertex& Mesh::Polygon::getV2() const
{
	return _linkedMesh->getVertex(_triple.idx2);
}


const Mesh::Vertex& Mesh::Polygon::getV3() const
{
	return _linkedMesh->getVertex(_triple.idx3);
}


Mesh::Vertex& Mesh::Polygon::getV1()
{
	return _linkedMesh->getVertex(_triple.idx1);
}


Mesh::Vertex& Mesh::Polygon::getV2()
{
	return _linkedMesh->getVertex(_triple.idx2);
}


Mesh::Vertex& Mesh::Polygon::getV3()
{
	return _linkedMesh->getVertex(_triple.idx3);
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
	std::swap(_triple.idx2, _triple.idx3);
}


void Mesh::Polygon::_linkVertices()
{
	getV1()._linkedTriples.push_back(_triple);
	getV2()._linkedTriples.push_back(_triple);
	getV3()._linkedTriples.push_back(_triple);
}
