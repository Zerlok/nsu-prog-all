#ifndef __MESH_HPP__
#define __MESH_HPP__


#include <vector>
#include <sharedpointer.h>

#include "object.hpp"
#include "common/color.hpp"
#include "material.hpp"


class Mesh : public Object
{
	public:
		class Vertex;
		class Face;

		using Vertices = std::vector<Vertex>;
		using Faces = std::vector<Face>;

		Mesh(const std::string& name = "",
			 const glm::vec3& pos = Object::DEFAULT_POSITION,
			 const glm::vec3& rot = Object::DEFAULT_ROTATION,
			 const glm::vec3& sca = Object::DEFAULT_SCALE);
		Mesh(const Mesh& mesh);
		Mesh(Mesh&& mesh);
		virtual ~Mesh();

		Mesh& operator=(const Mesh& mesh);
		Mesh& operator=(Mesh&& mesh);

		const Vertex& getVertex(const size_t& i) const;
		const Face& getFace(const size_t& i) const;

		const Vertices& getVertices() const;
		const Faces& getFaces() const;
		const MaterialPtr& getMaterial() const;

		void addVertex(const Vertex& vertex);
		void addFace(const Face& face);
		void setMaterial(const MaterialPtr& material);

		void recalculateNormals();

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	protected:
		Vertices _vertices;
		Faces _faces;
		MaterialPtr _material;

		void _reassignDataReferences();
};

using MeshPtr = SharedPointer<Mesh>;


class Mesh::Vertex
{
	public:
		Vertex(const float& x,
			   const float& y,
			   const float& z,
			   const Color& color = Color::black);
		Vertex(const glm::vec3& pos,
			   const Color& color = Color::black);
		Vertex(const Vertex& v);
		Vertex(Vertex&& v);
		~Vertex();

		Vertex& operator=(const Vertex& v);
		Vertex& operator=(Vertex&& v);

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3& pos);

		const Color& getColor() const;
		void setColor(const Color& color);

		const size_t& getIndex() const;

	private:
		glm::vec3 _position;
		Color _color;
		size_t _idx;

		Mesh* _mesh; // agregation reference to Mesh.
		friend class Mesh;
};


class Mesh::Face
{
	public:
		Face(const size_t& f, const size_t& s, const size_t& t);
		Face(const Vertex& f, const Vertex& s, const Vertex& t);
		Face(const Face& f);
		Face(Face&& f);
		~Face();

		Face& operator=(const Face& f);
		Face& operator=(Face&& f);

		const size_t& getFirstIndex() const;
		const size_t& getSecondIndex() const;
		const size_t& getThirdIndex() const;

		glm::vec3 getNormal() const;
		void flip();

	private:
		size_t _first;
		size_t _second;
		size_t _third;

		Mesh* _mesh; // agregation reference to Mesh.
		friend class Mesh;
};


#endif // __MESH_HPP__
