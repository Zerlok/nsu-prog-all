#ifndef __MESH_HPP__
#define __MESH_HPP__


#include <vector>

#include "common/color.hpp"
#include "object.hpp"
#include "material.hpp"


class Mesh : public Object
{
	public:
		class Vertex
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

				Mesh* _mesh;
				friend class Mesh;
		};
		using Vertices = std::vector<Vertex>;

		class Face
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

			protected:
				size_t _first;
				size_t _second;
				size_t _third;

				Mesh* _mesh;
				friend class Mesh;
		};
		using Faces = std::vector<Face>;

		Mesh(const std::string& name = std::string(),
			 const glm::vec3& pos = glm::vec3(0.0, 0.0, 0.0),
			 const glm::vec3& rot = glm::vec3(0.0, 0.0, 0.0),
			 const glm::vec3& sca = glm::vec3(1.0, 1.0, 1.0));
		Mesh(const Mesh& mesh);
		Mesh(Mesh&& mesh);
		virtual ~Mesh();

		Mesh& operator=(const Mesh& mesh);
		Mesh& operator=(Mesh&& mesh);

		const Vertex& getVertex(const size_t& i) const;
		const Vertices& getVertices() const;
		void addVertex(const Vertex& vertex);

		const Face& getFace(const size_t& i) const;
		const Faces& getFaces() const;
		void addFace(const Face& face);

		const Material& getMaterial() const;
		void setMaterial(const Material& material);

		void recalculateNormals();

	protected:
		Vertices _vertices;
		Faces _faces;
		Material _material;

		void _reassign();
};


#endif // __MESH_HPP__
