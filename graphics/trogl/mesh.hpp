#ifndef __MESH_H__
#define __MESH_H__


#include "common/point.hpp"
#include "common/color.hpp"

#include <vector>

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
				Vertex(const Point& pos,
					   const Color& color = Color::black);
				Vertex(const Vertex& v);
				Vertex(Vertex&& v);
				~Vertex();

				const Point& getPosition() const;
				void setPosition(const Point& point);

				const Color& getColor() const;
				void setColor(const Color& color);

				const size_t& getIndex() const;

			private:
				Point _position;
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
				Face(const std::initializer_list<size_t>& lsit);
				Face(const Face& f);
				Face(Face&& f);
				~Face();

				const size_t& getFirstIndex() const;
				const size_t& getSecondIndex() const;
				const size_t& getThirdIndex() const;

				const Point getNormal() const;
				void flip();

			protected:
				size_t _first;
				size_t _second;
				size_t _third;

				Mesh* _mesh;
				friend class Mesh;
		};
		using Faces = std::vector<Face>;

		Mesh(const Point& pos = Point::zero,
			 const Point& rot = Point::zero,
			 const Point& sca = Point::one);
		virtual ~Mesh();

		const Vertex& getVertex(const size_t& i);
		const Vertices& getVertices() const;
		void addVertex(const Vertex& vertex);

		const Face& getFace(const size_t& i);
		const Faces& getFaces() const;
		void addFace(const Face& face);

		const Material& getMaterial() const;
		void setMaterial(const Material& material);

	protected:
		Vertices _vertices;
		Faces _faces;
		Material _material;
};


#endif // __MESH_H__
