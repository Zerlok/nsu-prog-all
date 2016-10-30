#ifndef __MESH_HPP__
#define __MESH_HPP__


#include <vector>
#include <tuple>
#include <unordered_map>
#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "material.hpp"
#include "object.hpp"


class Mesh : public Object
{
	public:
		// Static.
		static const MaterialPtr DEFAULT_MATERIAL;

		// Inner classes.
		enum IndexingType
		{
			TRIANGLES = GL_TRIANGLES,
			TRIANGLES_STRIP = GL_TRIANGLE_STRIP,
		};

		class Face;
		class Vertex
		{
			public:
				// Constructors / Destructor.
				Vertex(const size_t& idx,
					   const float& x,
					   const float& y,
					   const float& z,
					   const Color& color,
					   Mesh* mesh);
				Vertex(const Vertex& v);
				Vertex(Vertex&& v);
				~Vertex();

				// Operators.
				Vertex& operator=(const Vertex& v);
				Vertex& operator=(Vertex&& v);

				// Methods.
				const size_t& getIndex() const;
				const glm::vec3& getPosition() const;
				const glm::vec3& getNormal() const;
				const Color& getColor() const;

				void setPosition(const glm::vec3& pos);
				void setColor(const Color& color);

			private:
				// Fields.
				size_t _idx;
				glm::vec3 _position;
				glm::vec3 _normal;
				// TODO: move color into material.
				Color _color;

				// Association link with Mesh.
				Mesh* _linkedMesh;
				friend class Mesh;

				// Aggregation link with Faces.
				std::vector<Face*> _linkedFaces;
				friend class Face;

				// Methods.
				void _recalculateNormal();
		};

		class Face
		{
			public:
				// Constructors / Destructor.
				Face(Vertex& v1,
					 Vertex& v2,
					 Vertex& v3,
					 Mesh* mesh);
				Face(const Face& f);
				Face(Face&& f);
				~Face();

				// Operators.
				Face& operator=(const Face& f);
				Face& operator=(Face&& f);

				// Methods.
				const Vertex& getFirst() const;
				const Vertex& getSecond() const;
				const Vertex& getThird() const;

				const glm::vec3& getNormal() const;
				void flip();

			private:
				// Fields.
				// Association link with Vertices.
				Vertex* _first;
				Vertex* _second;
				Vertex* _third;
				friend class Mesh::Vertex;

				// Association link with Mesh.
				Mesh* _linkedMesh;
				friend class Mesh;

				glm::vec3 _normal;

				// Methods.
				glm::vec3 _calculateNormal();
		};

		class Polygon : public std::tuple<size_t, size_t, size_t>
		{
			public:
				Polygon(const size_t& i1,
						const size_t& i2,
						const size_t& i3)
					: std::tuple<size_t, size_t, size_t>(i1, i2, i3) {}

				class hash
				{
					public:
						size_t operator()(const Polygon& p) const
						{
							size_t h1 = std::hash<size_t>()(std::get<0>(p));
							size_t h2 = std::hash<size_t>()(std::get<1>(p));
							size_t h3 = std::hash<size_t>()(std::get<2>(p));
							return (h1 ^ h2 ^ h3);
						}
				};
		};

		using Vertices = std::vector<Vertex>;
		using Faces = std::unordered_map<Polygon, Face, Polygon::hash>;

		// Constructors / Destructor.
		Mesh(const std::string& name = "",
			 const MaterialPtr& mat = Mesh::DEFAULT_MATERIAL,
			 const IndexingType& indexType = IndexingType::TRIANGLES);
		Mesh(const Mesh& mesh);
		Mesh(Mesh&& mesh);
		virtual ~Mesh();

		// Operators.
		Mesh& operator=(const Mesh& mesh);
		Mesh& operator=(Mesh&& mesh);

		// Methods.
		const Vertex& getVertex(const size_t& i) const;
		const Face& getFace(const size_t& i1,
							const size_t& i2,
							const size_t& i3) const;

		const Vertices& getVertices() const;
		const Faces& getFaces() const;
		const MaterialPtr& getMaterial() const;
		const IndexingType& getIndexType() const;

		size_t addVertex(const float& x, const float& y, const float& z, const Color& color);
		void addFace(const size_t& i1,
					 const size_t& i2,
					 const size_t& i3);
		void setMaterial(const MaterialPtr& material);

		void recalculateNormals();

		// Methods overriden.
		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	protected:
		// Fields.
		Vertices _vertices;
		Faces _faces;
		MaterialPtr _material;
		IndexingType _indexType;

		// Methods.
		void _reassignDataReferences();
};

using MeshPtr = SharedPointer<Mesh>;


#endif // __MESH_HPP__
