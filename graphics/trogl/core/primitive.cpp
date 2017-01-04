#include "primitive.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


const size_t Primitive::_vertexStep = 4;
const size_t Primitive::_uvStep = 2;
const size_t Primitive::_indexStep = 3;


Primitive::Primitive(const MeshPtr& mesh)
	: _glVBO(0),
	  _glUVBO(0),
	  _glNBO(0),
	  _glIBO(0),
	  _indicesSize(0),
	  _position(mesh->getPosition()),
	  _material(mesh->getMaterial())
{
	/*
	 * Apply mesh vertices positions from object attributes
	 * (in reverse order: scale, rotation, position).
	 */
	MeshPtr mesh0 = mesh;
	mesh0->recalculateNormals();
	mesh0->applyScale();
	mesh0->applyRotation();
	mesh0->applyPosition();

	initGLGeometry(mesh);
	if (_isGLGeometryValid())
		_material->compile();

	logDebug << "Primitive from mesh " << mesh->getName() << " created." << logEndl;
}


Primitive::Primitive(Primitive&& obj)
	: _glVBO(std::move(obj._glVBO)),
	  _glUVBO(std::move(obj._glUVBO)),
	  _glNBO(std::move(obj._glNBO)),
	  _glIBO(std::move(obj._glIBO)),
	  _indicesSize(std::move(obj._indicesSize)),
	  _position(std::move(obj._position)),
	  _material(std::move(obj._material))
{
	obj._glVBO = 0;
	obj._glUVBO = 0;
	obj._glNBO = 0;
	obj._glIBO = 0;

	logDebug << "Primitive moved (VBO, UVBO, NBO, IBO): "
			 << _glVBO << ", " << _glUVBO << ", " << _glNBO << ", " << _glIBO
			 << " [" << _indicesSize << ']'
			 << logEndl;
}


Primitive::~Primitive()
{
	_deinitGLGeometry();

	if (isValid())
		logDebug << "Primitive removed (VBO, UVBO, NBO, IBO): "
				 << _glVBO << ", " << _glUVBO << ", " << _glNBO << ", " << _glIBO
				 << " [" << _indicesSize << ']'
				 << logEndl;
}


bool Primitive::isValid() const
{
	return (_isGLGeometryValid()
			&& _material->isValid());
}


void Primitive::initGLGeometry(const MeshPtr& mesh)
{
	if (_isGLGeometryValid())
		return;

	_initVertexBufferObject(mesh);
	_initUVBufferObject(mesh);
	_initIndexBufferObject(mesh);
}


void Primitive::draw(const LightPtr& light,
					 const CameraPtr& camera,
					 const glm::mat4x4& mv,
					 const glm::mat4x4& mvp)
{
	_material->use();

	const ShaderPtr& sh = _material->getShader();
	sh->passUniform("MV", mv);
	sh->passUniform("MVP", mvp);
	sh->passUniform("meshPosition", _position);
	sh->passComponent(light);
	sh->passComponent(camera);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glVertexAttribPointer(0, _vertexStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glNBO);
	glVertexAttribPointer(1, _vertexStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glUVBO);
	glVertexAttribPointer(2, _uvStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


bool Primitive::_isGLGeometryValid() const
{
	return ((_glVBO != 0)
			&& (_glUVBO != 0)
			&& (_glNBO != 0)
			&& (_glIBO != 0));
}


void Primitive::_initVertexBufferObject(const MeshPtr& mesh)
{
	std::vector<GLfloat> vertices((mesh->getVertices().size() * _vertexStep), 0.0f);
	std::vector<GLfloat> normals((mesh->getVertices().size() * _vertexStep), 0.0f);
	size_t idx = 0;

	for (size_t i = 0; i < vertices.size(); i += _vertexStep)
	{
		const Mesh::Vertex& v = mesh->getVertex(idx++);

		vertices[i] = v.getPosition().x;
		vertices[i+1] = v.getPosition().y;
		vertices[i+2] = v.getPosition().z;
		vertices[i+3] = 1.0f;

		normals[i] = v.getNormal().x;
		normals[i+1] = v.getNormal().y;
		normals[i+2] = v.getNormal().z;
		normals[i+3] = 0.0f;
	}

	glGenBuffers(1, &_glVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_glNBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glNBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
}


void Primitive::_initUVBufferObject(const MeshPtr &mesh)
{
	std::vector<GLfloat> maps((mesh->getVertices().size() * _uvStep), 0.0f);
	size_t idx = 0;

	for (size_t i = 0; i < maps.size(); i += _uvStep)
	{
		const Mesh::Vertex& v = mesh->getVertex(idx++);

		maps[i] = v.getUVMapping().x;
		maps[i+1] = v.getUVMapping().y;
	}

	glGenBuffers(1, &_glUVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glUVBO);
	glBufferData(GL_ARRAY_BUFFER, maps.size() * sizeof(GLfloat), maps.data(), GL_STATIC_DRAW);
}


void Primitive::_initIndexBufferObject(const MeshPtr& mesh)
{
	std::vector<GLuint> indicies((mesh->getPolygons().size() * _indexStep), 0.0f);
	size_t i = 0;

	// TODO: get indicies from mesh method, which knows their order and indexing type.
	for (const Mesh::Polygons::value_type& pair : mesh->getPolygons())
	{
		const Mesh::Polygon& poly = pair.second;
		indicies[i++] = poly.getIdx1();
		indicies[i++] = poly.getIdx2();
		indicies[i++] = poly.getIdx3();
	}
	_indexType = mesh->getIndexType();
	_indicesSize = indicies.size() * sizeof(GLuint);

	glGenBuffers(1, &_glIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, indicies.data(), GL_STATIC_DRAW);
}


void Primitive::_deinitGLGeometry()
{
	if (_glVBO != 0)
		glDeleteBuffers(sizeof(_glVBO), &_glVBO);

	if (_glUVBO != 0)
		glDeleteBuffers(sizeof(_glUVBO), &_glUVBO);

	if (_glNBO != 0)
		glDeleteBuffers(sizeof(_glNBO), &_glNBO);

	if (_glIBO != 0)
		glDeleteBuffers(sizeof(_glIBO), &_glIBO);
}
