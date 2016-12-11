#include "grid.hpp"

#include <cmath>


const Grid::Cell Grid::Cell::zero = {0.0, 0.0};
const Grid::Cell Grid::Cell::normal = {1.0, 1.0};


Grid::Grid(const size_t& columns,
		   const size_t& rows,
		   const float& width,
		   const float& height)
	: _columns(columns),
	  _rows(rows),
	  _cell({width, height})
{
}


Grid::~Grid()
{
}


const size_t& Grid::getRows() const
{
	return _rows;
}


const size_t& Grid::getColumns() const
{
	return _columns;
}


const Grid::Cell& Grid::getCell() const
{
	return _cell;
}


void Grid::setCellSize(const float& width,
				   const float& height)
{
	_cell.width = width;
	_cell.height = height;
}


Grid::Cell Grid::getLeftTop(const float& x,
							const float& y) const
{
	if ((x <= 0.0) || (y <= 0.0)
			|| (y > _rows * _cell.height)
			|| (x > _columns * _cell.width))
		return Cell::zero;

	const int xSteps = std::ceil(x / _cell.width) - 1;
	const int ySteps = std::ceil(y / _cell.height) - 1;
	const float w = x - xSteps * _cell.width;
	const float h = y - ySteps * _cell.height;

	return {w, h};
}


Grid::Cell Grid::getRightTop(const float& x,
							 const float& y) const
{
	if ((x < 0.0) || (y <= 0.0)
			|| (x >= _columns * _cell.width)
			|| (y > _rows * _cell.height))
		return Cell::zero;

	const int xSteps = std::floor(x / _cell.width) + 1;
	const int ySteps = std::ceil(y / _cell.height) - 1;
	const float w = xSteps * _cell.width - x;
	const float h = y - ySteps * _cell.height;

	return {w, h};
}


Grid::Cell Grid::getLeftBottom(const float& x,
							   const float& y) const
{
	if ((x <= 0.0) || (y < 0.0)
			|| (x > _columns * _cell.width)
			|| (y >= _rows * _cell.height))
		return Cell::zero;

	const int xSteps = std::ceil(x / _cell.width) - 1;
	const int ySteps = std::floor(y / _cell.height) + 1;
	const float w = x - xSteps * _cell.width;
	const float h = ySteps * _cell.height - y;

	return {w, h};
}


Grid::Cell Grid::getRightBottom(const float& x,
								const float& y) const
{
	if ((x < 0.0) || (y < 0.0)
			|| (x >= _columns * _cell.width)
			|| (y >= _rows * _cell.height))
		return Cell::zero;

	const int xSteps = std::floor(x / _cell.width) + 1;
	const int ySteps = std::floor(y / _cell.height) + 1;
	const float w = xSteps * _cell.width - x;
	const float h = ySteps * _cell.height - y;

	return {w, h};
}


Grid::iterator Grid::begin() const
{
	return {this, 0.0, 0.0};
}


Grid::iterator Grid::end() const
{
	return {this, _columns * _cell.width, _rows * _cell.height};
}


void Grid::resize(const size_t& rows,
				  const size_t& columns)
{
	_rows = rows;
	_columns = columns;
}


void Grid::resizeCellsToOverlay(const Grid& g)
{
	_cell.width = g._cell.width * g._columns / _columns;
	_cell.height = g._cell.height * g._rows / _rows;
}


Grid::LayingIterator Grid::overlay(const Grid& g)
{
	resizeCellsToOverlay(g);

	return LayingIterator(this, &g, 0.0, 0.0);
}


Grid::iterator::iterator(const Grid* g, const float& x, const float& y)
	: _grid(g),
	  _x(x),
	  _y(y)
{
}


Grid::iterator::iterator(const Grid::iterator& it)
	: _grid(it._grid),
	  _x(it._x),
	  _y(it._y)
{
}


Grid::iterator::iterator(Grid::iterator&& it)
	: _grid(it._grid),
	  _x(std::move(it._x)),
	  _y(std::move(it._y))
{
}


Grid::iterator::~iterator()
{
}


Grid::iterator& Grid::iterator::operator=(const Grid::iterator& it)
{
	_grid = it._grid;
	_x = it._x;
	_y = it._y;

	return (*this);
}


Grid::iterator& Grid::iterator::operator=(Grid::iterator&& it)
{
	_grid = it._grid;
	_x = std::move(it._x);
	_y = std::move(it._y);

	return (*this);
}


bool Grid::iterator::operator==(const Grid::iterator& it) const
{
	return (getCell() == it.getCell());
}


bool Grid::iterator::operator!=(const Grid::iterator& it) const
{
	return (!this->operator==(it));
}


Grid::iterator& Grid::iterator::operator++()
{
	_x += _grid->_cell.width;

	if (getCell() == Cell::zero)
	{
		_x = 0.0;
		_y += _grid->_cell.height;

		if (getCell() == Cell::zero)
		{
			_x = _grid->_cell.width * _grid->_columns;
			_y = _grid->_cell.height * _grid->_rows;
		}
	}

	return (*this);
}


Grid::iterator& Grid::iterator::operator--()
{
	_x -= _grid->_cell.width;

	if (getCell() == Cell::zero)
	{
		_x = _grid->_cell.width * _grid->_columns;
		_y -= _grid->_cell.height;

		if (getCell() == Cell::zero)
		{
			_x = 0.0;
			_y = 0.0;
		}
	}

	return (*this);
}


Grid::iterator Grid::iterator::operator++(int)
{
	iterator tmp(*this);
	this->operator++();

	return tmp;
}


Grid::iterator Grid::iterator::operator--(int)
{
	iterator tmp(*this);
	this->operator--();

	return tmp;
}


float Grid::iterator::getX() const
{
	return _x;
}


float Grid::iterator::getY() const
{
	return _y;
}


Grid::Cell Grid::iterator::getCell() const
{
	return _grid->getRightBottom(_x, _y);
}


Grid::LayingIterator::LayingIterator(Grid const* grid1,
									 Grid const* grid2,
									 const float& x,
									 const float& y)
	: _grid1(grid1),
	  _grid2(grid2),
	  _it1(_grid1, x, y),
	  _it2(_grid2, x, y)
{
	if (_grid2->getCell().area() < _grid1->getCell().area())
	{
		std::swap(_grid1, _grid2);
		std::swap(_it1, _it2);
	}
}


Grid::LayingIterator::~LayingIterator()
{
}


Grid::LayingIterator& Grid::LayingIterator::operator++()
{
	const Cell& cell1 = _grid1->_cell;
	const Cell& cell2 = _grid2->_cell;

	float x = _it1.getX() + cell1.width;

	if (x >= (_it2.getX() + cell2.width))
	{
		int xSteps = 0;
		int ySteps = 0;
		float y = _it1.getY() + cell1.height;

		if (y < (_it2.getY() + cell2.height))
		{
			xSteps = std::floor(_it2.getX() / cell1.width);
			x = xSteps * cell1.width;
		}
		else
		{
			++_it2;

			xSteps = std::floor(_it2.getX() / cell1.width);
			ySteps = std::floor(_it2.getY() / cell1.height);
			x = xSteps * cell1.width;
			y = ySteps * cell1.height;
		}

		_it1 = {_grid1, x, y};
	}
	else
		_it1 = {_grid1, x, _it1.getY()};

	return (*this);
}


Grid::Cell Grid::LayingIterator::getCell() const
{
	const Cell& cell1 = _grid1->_cell;
	const Cell& cell2 = _grid2->_cell;

	const float cw = std::min(cell1.width, cell2.width);
	const float ch = std::min(cell1.height, cell2.height);

	const float a = std::max(_it1.getX(), _it2.getX());
	const float b = std::max(_it1.getY(), _it2.getY());
	const float c = std::min(cell1.width + _it1.getX(), cell2.width + _it2.getX());
	const float d = std::min(cell1.height + _it1.getY(), cell2.height + _it2.getY());

	const float w = std::min(c - a, cw);
	const float h = std::min(d - b, ch);

	return {w, h};
}


std::ostream& operator<<(std::ostream& out, const Grid::Cell& cell)
{
	out << '(' << cell.width << " x " << cell.height << ')';
	return out;
}


std::ostream& operator<<(std::ostream& out, const Grid& grid)
{
	out << '[' << grid.getCell() << " * " << grid.getColumns() << " x " << grid.getRows() << ']';
	return out;
}
