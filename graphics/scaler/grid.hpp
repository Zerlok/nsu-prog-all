#ifndef __GRID_HPP__
#define __GRID_HPP__


#include <iostream>


class Grid
{
	public:
		struct Cell
		{
			static const Cell zero;
			static const Cell normal;

			Cell(const float& w, const float& h) : width(w), height(h) {}
			Cell(const Cell& c) : width(c.width), height(c.height) {}
			Cell(Cell&& c) : width(std::move(c.width)), height(std::move(c.height)) {}
			~Cell() {}

			Cell& operator=(const Cell& c) { width = c.width; height = c.height; return (*this); }
			Cell& operator=(Cell&& c) { width = std::move(c.width); height = std::move(c.height); return (*this); }

			bool operator==(const Cell& c) const { return ((width == c.width) && (height == c.height)); }
			bool operator!=(const Cell& c) const { return (!this->operator==(c)); }

			float area() const { return (width * height); }

			float width;
			float height;
		};

		class iterator
		{
			public:
				iterator(const Grid* g,
						 const float& x = 0.0,
						 const float& y = 0.0);
				iterator(const iterator& it);
				iterator(iterator&& it);
				~iterator();

				iterator& operator=(const iterator& it);
				iterator& operator=(iterator&& it);

				bool operator==(const iterator& it) const;
				bool operator!=(const iterator& it) const;

				iterator& operator++();
				iterator& operator--();
				iterator operator++(int);
				iterator operator--(int);

				float getX() const;
				float getY() const;
				Cell getCell() const;

			private:
				Grid const* _grid;
				float _x;
				float _y;
		};

		Grid(const size_t& columns = 0,
			 const size_t& rows = 0,
			 const float& width = Cell::normal.width,
			 const float& height = Cell::normal.height,
			 const float& x = 0.0f,
			 const float& y = 0.0f);
		~Grid();

		bool hasInside(const iterator& it) const;

		const float& getOffsetX() const;
		const float& getOffsetY() const;
		const size_t& getRows() const;
		const size_t& getColumns() const;
		const Cell& getCell() const;

		Cell getLeftTop(const float& x, const float& y) const;
		Cell getRightTop(const float& x, const float& y) const;
		Cell getLeftBottom(const float& x, const float& y) const;
		Cell getRightBottom(const float& x, const float& y) const;

		iterator begin() const;
		iterator end() const;

		void setOffset(const float& x, const float& y);
		void setCellSize(const float& width, const float& height);
		void resize(const size_t& rows, const size_t& columns);

	private:
		float _x;
		float _y;
		size_t _columns;
		size_t _rows;
		Cell _cell;
};


class OverlayIterator
{
	public:
		OverlayIterator(const Grid* grid1,
						   const Grid* grid2);
		OverlayIterator(const OverlayIterator& it);
		OverlayIterator(OverlayIterator&& it);
		~OverlayIterator();

		OverlayIterator& operator=(const OverlayIterator& it);
		OverlayIterator& operator=(OverlayIterator&& it);

		OverlayIterator& operator++();

		bool isInnerEnd() const;
		bool isOutterEnd() const;
		Grid::Cell getCell() const;

		const Grid& getInnerGrid() const;

		Grid::iterator& getInner();
		Grid::iterator& getOutter();

	private:
		static const Grid* _getFirstGrid(const Grid* g1,
								   const Grid* g2);
		static const Grid* _getSecondGrid(const Grid* g1,
									const Grid* g2);
		static Grid _calcInnerGrid(const Grid* g1, const Grid* g2, const Grid::iterator& outter);

		const Grid* _grid1;
		const Grid* _grid2;

		Grid::iterator _outter;
		Grid _innerGrid;
		Grid::iterator _inner;
};


OverlayIterator overlay(Grid& layWhich, const Grid& layOnto);


std::ostream& operator<<(std::ostream& out, const Grid::Cell& cell);
std::ostream& operator<<(std::ostream& out, const Grid& grid);


#endif // __GRID_HPP__
