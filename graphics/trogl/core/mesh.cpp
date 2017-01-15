#include "mesh.hpp"


#include <algorithm>
#include <glm/glm.hpp>
#include <logger.hpp>
#include "materials/diffusematerial.hpp"


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


// ---------------------------- MESH ---------------------------- //

const MaterialPtr Mesh::DEFAULT_MATERIAL = new DiffuseMaterial(Color::white, 0.8, 0.8, 10.0);


Mesh::Mesh(const std::string& name,
		   const MaterialPtr& mat,
		   const IndexingType& indexType)
	: Object(Object::Type::MESH, name),
	  _vertices(),
	  _polygons(),
	  _material(mat),
	  _indexType(indexType)

{
	_regProperties();
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
	_regProperties();
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
	_regProperties();
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


/*
Mesh& Mesh::operator+=(const Mesh& mesh)
{
	Object::operator+=(mesh);
	_material->operator+=(mesh._material);

	return (*this);
}


Mesh& Mesh::operator*=(const float& ratio)
{
	Object::operator*=(ratio);
	_material->operator*=(ratio);

	return (*this);
}


Mesh Mesh::operator+(const Mesh& mesh) const
{
	Mesh tmp(*this);
	tmp += mesh;

	return std::move(tmp);
}


Mesh Mesh::operator*(const float& ratio) const
{
	Mesh tmp(*this);
	tmp *= ratio;

	return std::move(tmp);
}
*/


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


glm::mat4x4 Mesh::calculateWorldMatrix() const
{
	glm::mat4x4 mw(space::identic::m4x4);

	mw *= glm::translate(space::identic::m4x4, _position);
	mw *= glm::rotate(space::identic::m4x4, _rotation.z, space::axis::z);
	mw *= glm::rotate(space::identic::m4x4, _rotation.x, space::axis::x);
	mw *= glm::rotate(space::identic::m4x4, _rotation.y, space::axis::y);
	mw *= glm::scale(space::identic::m4x4, _scale);

	return std::move(mw);
}


size_t Mesh::addVertex(const float& x,
					   const float& y,
					   const float& z,
					   const float& nx,
					   const float& ny,
					   const float& nz,
					   const float& u,
					   const float& v)
{
	return addVertex({x, y, z}, {nx, ny, nz}, {u, v});
}


size_t Mesh::addVertex(const vec3& position,
					   const vec3& normal,
					   const vec2& uv)
{
	return addVertex(Vertex(position, normal, uv, this));
}


size_t Mesh::addVertex(const Mesh::Vertex& v)
{
	const size_t idx = _vertices.size();
	_vertices.push_back(v);
	_vertices.back()._idx = idx;

	return idx;
}


size_t Mesh::addUVVertex(const float& x,
						 const float& y,
						 const float& z,
						 const float& u,
						 const float& v)
{
	return addVertex(x, y, z, 0.0f, 0.0f, 0.0f, u, v);
}


bool Mesh::addPolygon(const size_t& i1,
					  const size_t& i2,
					  const size_t& i3)
{
	return addPolygon(Triple(i1, i2, i3));
}


bool Mesh::addPolygon(const Mesh::Triple& tr)
{
	const Polygons::iterator it = _polygons.find(tr);
	if (it != _polygons.end())
		return false;

	_polygons.insert({tr, Polygon(tr, this)});
	Polygon& p = _polygons.at(tr);
	p._linkVertices();

	return true;
}


bool Mesh::addPolygon(const Mesh::Polygon& p)
{
	return addPolygon(p._triple);
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
	 *
	 * Choice 2: Find out is face normal directed as total normal of its verticecs.
	 */
	vec3 vn;
	vec3 pn;
	float ratio;
	for (Polygons::value_type& it : _polygons)
	{
		Polygon& poly = it.second;
		pn = poly.calculateNormal();
		vn = poly.getV1().getNormal() + poly.getV2().getNormal() + poly.getV3().getNormal();

		if (vn == space::zero::xyz)
		{
			ratio = glm::dot(poly.calculateCenter(), pn);
			if (ratio < -0.5)
				poly.flip();
		}
		else
		{
			ratio = glm::dot(glm::normalize(vn), pn);
			if (ratio < 0.0)
				poly.flip();
		}
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
	const glm::mat4 rotationMat = (
			glm::rotate(space::identic::m4x4, _rotation.z, space::axis::z)
			* glm::rotate(space::identic::m4x4, _rotation.x, space::axis::x)
			* glm::rotate(space::identic::m4x4, _rotation.y, space::axis::y));

	for (Vertex& v : _vertices)
	{
		v._position = vec3(rotationMat * glm::vec4(v._position, 1.0));
		v._normal = vec3(rotationMat * glm::vec4(v._normal, 0.0));
	}

	_rotation = Object::DEFAULT_ROTATION;
}


void Mesh::applyScale()
{
	for (Vertex& v : _vertices)
	{
		v._position *= _scale;

		if (v._normal != space::zero::xyz)
			v._normal = glm::normalize(v._normal / _scale);
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


void Mesh::_regProperties()
{
	Object::_regProperties();
	_regInnerProperty(_material.get_pointer());
}


// ---------------------------- MESH::VERTEX ---------------------------- //

Mesh::Vertex::Vertex(const float& x,
					 const float& y,
					 const float& z,
					 const float& nx,
					 const float& ny,
					 const float& nz,
					 const float& u,
					 const float& v,
					 Mesh* mesh)
	: _idx(-1),
	  _position(x, y, z),
	  _normal(nx, ny, nz),
	  _uv(u, v),
	  _linkedTriples(),
	  _linkedMesh(mesh)
{
}


Mesh::Vertex::Vertex(const vec3& position,
					 const vec3& normal,
					 const vec2& uv,
					 Mesh* mesh)
	: _idx(-1),
	  _position(position),
	  _normal(normal),
	  _uv(uv),
	  _linkedTriples(),
	  _linkedMesh(mesh)
{
}


Mesh::Vertex::Vertex(const Mesh::Vertex& v)
	: _idx(v._idx),
	  _position(v._position),
	  _normal(v._normal),
	  _uv(v._uv),
	  _linkedTriples(v._linkedTriples),
	  _linkedMesh(v._linkedMesh)
{
}


Mesh::Vertex::Vertex(Mesh::Vertex&& v)
	: _idx(std::move(v._idx)),
	  _position(std::move(v._position)),
	  _normal(std::move(v._normal)),
	  _uv(std::move(v._uv)),
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
	_normal = v._normal;
	_uv = v._uv;
	_linkedTriples = v._linkedTriples;
	_linkedMesh = v._linkedMesh;

	return (*this);
}


Mesh::Vertex& Mesh::Vertex::operator=(Mesh::Vertex&& v)
{
	_idx = std::move(v._idx);
	_position = std::move(v._position);
	_normal = std::move(v._normal);
	_uv = std::move(v._uv);
	_linkedTriples = std::move(v._linkedTriples);
	_linkedMesh = v._linkedMesh;

	return (*this);
}


const size_t& Mesh::Vertex::getIndex() const
{
	return _idx;
}


const vec3& Mesh::Vertex::getPosition() const
{
	return _position;
}


const vec3& Mesh::Vertex::getNormal() const
{
	return _normal;
}


const vec2& Mesh::Vertex::getUV() const
{
	return _uv;
}


vec3 Mesh::Vertex::calculateNormal() const
{
	if (_linkedMesh == nullptr)
		return _normal;

	vec3 normal = vec3(0.0, 0.0, 0.0);
	for (const Triple& tr : _linkedTriples)
		normal += _linkedMesh->getPolygon(tr).calculateNormal();

	return std::move(glm::normalize(normal));
}


void Mesh::Vertex::setPosition(const glm::vec3& pos)
{
	_position = pos;
}


void Mesh::Vertex::setNormal(const glm::vec3& nor)
{
	_normal = nor;
}


void Mesh::Vertex::setUV(const vec2& uv)
{
	_uv = uv;
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


vec3 Mesh::Polygon::calculateNormal() const
{
	if (_linkedMesh == nullptr)
		return std::move(vec3(0.0f, 0.0f, 0.0f));

	const vec3& v1 = getV1().getPosition();
	const vec3& v2 = getV2().getPosition();
	const vec3& v3 = getV3().getPosition();

	return std::move(glm::normalize(glm::cross((v2 - v1), (v3 - v1))));
}


vec3 Mesh::Polygon::calculateCenter() const
{
	if (_linkedMesh == nullptr)
		return std::move(vec3(0.0f, 0.0f, 0.0f));

	const vec3& v1 = getV1().getPosition();
	const vec3& v2 = getV2().getPosition();
	const vec3& v3 = getV3().getPosition();

	return std::move((v1 + v2 + v3) / 3.0f);
}


void Mesh::Polygon::flip()
{
	std::swap(_triple.idx2, _triple.idx3);
}


void Mesh::Polygon::_linkVertices()
{
	if (_linkedMesh == nullptr)
		return;

	getV1()._linkedTriples.push_back(_triple);
	getV2()._linkedTriples.push_back(_triple);
	getV3()._linkedTriples.push_back(_triple);
}
