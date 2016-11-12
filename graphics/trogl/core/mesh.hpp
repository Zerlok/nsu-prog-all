#ifndef __MESH_HPP__
#define __MESH_HPP__


#include <vector>
#include <list>
#include <unordered_set>
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
			// TODO: write function which returns indicies for IBO by indexing type.
			// TRIANGLES_STRIP = GL_TRIANGLE_STRIP,
		};

		class Polygon;
		class Vertex
		{
			public:
				// Constructors / Destructor.
				Vertex(const size_t& idx,
					   const double& x,
					   const double& y,
					   const double& z,
					   const Color& color,
					   Mesh* mesh);
//				Vertex(const Vertex& v) = delete;
//				Vertex(Vertex&& v) = delete;
				~Vertex();

				// Operators.
//				Vertex& operator=(const Vertex& v) = delete;
//				Vertex& operator=(Vertex&& v) = delete;

				// Methods.
				const size_t& getIndex() const;
				const vec& getPosition() const;
				const vec& getNormal() const;
				const Color& getColor() const;

				void setPosition(const glm::vec3& pos);
				void setColor(const Color& color);

			private:
				// Fields.
				size_t _idx;
				Object::vec _position;
				Object::vec _normal;
				// TODO: move color into material, assign vertices into material groups.
				Color _color;

				// Association link with Mesh.
				Mesh* _linkedMesh;
				friend class Mesh;

				// Aggregation link with Faces.
				std::vector<Polygon*> _linkedPolygons;
				friend class Polygon;

				// Methods.
				void _recalculateNormal();
				void _linkPolygon(Polygon* poly);
				void _unlinkPolygon(Polygon* poly);
		};

		class Polygon
		{
			public:
				// Inner classes.
				class Hash
				{
					public:
						size_t operator()(const Polygon& p) const;
				};

				// Constructors / Destructor.
				Polygon(const size_t& i1,
						const size_t& i2,
						const size_t& i3, Mesh* mesh);
//				Polygon(const Polygon& p) = delete;
				~Polygon();

				// Operators.
//				Polygon& operator=(const Polygon& p) = delete;
//				Polygon& operator=(Polygon&& p) = delete;

				bool operator==(const Polygon& p) const;
				bool operator!=(const Polygon& p) const;
				bool operator<(const Polygon& p) const;

				// Methods.
				const size_t& getIdx1() const;
				const size_t& getIdx2() const;
				const size_t& getIdx3() const;

				const Vertex& getV1() const;
				const Vertex& getV2() const;
				const Vertex& getV3() const;

				Vertex& getV1();
				Vertex& getV2();
				Vertex& getV3();

				vec calculateNormal() const;
				vec calculateCenter() const;
				void flip();

			private:
				// Fields.
				size_t _idx1;
				size_t _idx2;
				size_t _idx3;
				friend class Vertex;

				// Association link with Mesh.
				Mesh* _linkedMesh;
				friend class Mesh;

				void _linkVertices();
				void _unlinkVertices();
		};

		using Vertices = std::vector<Vertex>;
		using Polygons = std::unordered_set<Polygon, Polygon::Hash>;

		// Constructors / Destructor.
		Mesh(const std::string& name = std::string(),
			 const MaterialPtr& mat = Mesh::DEFAULT_MATERIAL,
			 const IndexingType& indexType = IndexingType::TRIANGLES);
		Mesh(const Mesh& mesh);
		Mesh(Mesh&& mesh);
		virtual ~Mesh();

		// Operators.
		Mesh& operator=(const Mesh& mesh);
		Mesh& operator=(Mesh&& mesh);

		// Methods.
		Vertex& getVertex(const size_t& i);
		const Vertex& getVertex(const size_t& i) const;
		const Polygon& getPolygon(const size_t& i1,
								  const size_t& i2,
								  const size_t& i3) const;

		const Vertices& getVertices() const;
		const Polygons& getPolygons() const;
		const MaterialPtr& getMaterial() const;
		const IndexingType& getIndexType() const;

		size_t addVertex(const double& x,
						 const double& y,
						 const double& z,
						 const Color& color);
		void addPolygon(const size_t& i1,
						const size_t& i2,
						const size_t& i3);
		void removeVertex();
		void removePolygon();
		void setMaterial(const MaterialPtr& material);

		void recalculateNormals();

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	protected:
		// Fields.
		Vertices _vertices;
		Polygons _polygons;
		MaterialPtr _material;
		IndexingType _indexType;

		// Methods.
		void _reassignDataLinks();
};

using MeshPtr = SharedPointer<Mesh>;
using Meshes = std::list<MeshPtr>;


#endif // __MESH_HPP__
