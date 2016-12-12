#include "grid.hpp"

#include <cmath>


const Grid::Cell Grid::Cell::zero = {0.0, 0.0};
const Grid::Cell Grid::Cell::normal = {1.0, 1.0};


Grid::Grid(
		const size_t& columns,
		const size_t& rows,
		const float& width,
		const float& height,
		const float& x,
		const float& y)
	: _x(x),
	  _y(y),
	  _columns(columns),
	  _rows(rows),
	  _cell({width, height})
{
}


Grid::~Grid()
{
}


const float& Grid::getOffsetX() const
{
	return _x;
}


const float& Grid::getOffsetY() const
{
	return _y;
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


Grid::Cell Grid::getLeftTop(
		const float& x,
		const float& y) const
{
	if ((x <= _x) || (y <= _y)
			|| (x > _columns * _cell.width + _x)
			|| (y > _rows * _cell.height + _y))
		return Cell::zero;

	const int xSteps = std::ceil((x - _x) / _cell.width) - 1;
	const int ySteps = std::ceil((y - _y) / _cell.height) - 1;
	const float w = x - xSteps * _cell.width;
	const float h = y - ySteps * _cell.height;

	return {w, h};
}


Grid::Cell Grid::getRightTop(
		const float& x,
		const float& y) const
{
	if ((x < _x) || (y <= _y)
			|| (x >= _columns * _cell.width + _x)
			|| (y > _rows * _cell.height + _y))
		return Cell::zero;

	const int xSteps = std::floor((x - _x) / _cell.width) + 1;
	const int ySteps = std::ceil((y - _y) / _cell.height) - 1;
	const float w = xSteps * _cell.width - x;
	const float h = y - ySteps * _cell.height;

	return {w, h};
}


Grid::Cell Grid::getLeftBottom(
		const float& x,
		const float& y) const
{
	if ((x <= _x) || (y < _y)
			|| (x > _columns * _cell.width + _x)
			|| (y >= _rows * _cell.height + _y))
		return Cell::zero;

	const int xSteps = std::ceil((x - _x) / _cell.width) - 1;
	const int ySteps = std::floor((y - _y) / _cell.height) + 1;
	const float w = x - xSteps * _cell.width;
	const float h = ySteps * _cell.height - y;

	return {w, h};
}


Grid::Cell Grid::getRightBottom(
		const float& x,
		const float& y) const
{
	if ((x < _x) || (y < _y)
			|| (x >= _columns * _cell.width + _x)
			|| (y >= _rows * _cell.height + _y))
		return Cell::zero;

	const int xSteps = std::floor((x - _x) / _cell.width) + 1;
	const int ySteps = std::floor((y - _y) / _cell.height) + 1;
	const float w = xSteps * _cell.width - x;
	const float h = ySteps * _cell.height - y;

	return {w, h};
}


Grid::iterator Grid::begin() const
{
	return {this, _x, _y};
}


Grid::iterator Grid::end() const
{
	return {this, _columns * _cell.width + _x, _rows * _cell.height + _y};
}


void Grid::setOffset(const float& x, const float& y)
{
	_x = x;
	_y = y;
}


void Grid::setCellSize(
		const float& width,
		const float& height)
{
	_cell.width = width;
	_cell.height = height;
}


void Grid::resize(const size_t& rows,
				  const size_t& columns)
{
	_rows = rows;
	_columns = columns;
}


Grid::iterator::iterator(
		const Grid* g,
		const float& x,
		const float& y)
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
		_x = _grid->_x;
		_y += _grid->_cell.height;

		if (getCell() == Cell::zero)
		{
			_x = _grid->_cell.width * _grid->_columns + _grid->_x;
			_y = _grid->_cell.height * _grid->_rows + _grid->_y;
		}
	}

	return (*this);
}


Grid::iterator& Grid::iterator::operator--()
{
	_x -= _grid->_cell.width;

	if (getCell() == Cell::zero)
	{
		_x = _grid->_cell.width * _grid->_columns + _grid->_x;
		_y -= _grid->_cell.height;

		if (getCell() == Cell::zero)
		{
			_x = _grid->_x;
			_y = _grid->_y;
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


OverlayIterator::OverlayIterator(
		const Grid* grid1,
		const Grid* grid2)
	: _grid1(_getFirstGrid(grid1, grid2)),
	  _grid2(_getSecondGrid(grid1, grid2)),
	  _outterIt(_grid2->begin()),
	  _outterEnd(_grid2->end()),
	  _innerGrid(_calcInnerGrid(_grid1, _grid2, _outterIt)),
	  _innerIt(_innerGrid.begin()),
	  _innerEnd(_innerGrid.end())
{
}


OverlayIterator::~OverlayIterator()
{
}


OverlayIterator& OverlayIterator::operator++()
{
	if (_innerIt != _innerEnd)
		++_innerIt;

	if (_innerIt == _innerEnd)
	{
		if (_outterIt != _outterEnd)
			++_outterIt;

		if (_outterIt != _outterEnd)
		{
			_innerGrid = _calcInnerGrid(_grid1, _grid2, _outterIt);
			_innerIt = _innerGrid.begin();
			_innerEnd = _innerGrid.end();
		}
	}

	return (*this);
}


Grid::Cell OverlayIterator::getCell() const
{
	const Grid::Cell& innerCell = _grid1->getCell();
	const Grid::Cell& outterCell = _grid2->getCell();

	const float a = std::max(_innerIt.getX(), _outterIt.getX());
	const float b = std::max(_innerIt.getY(), _outterIt.getY());
	const float c = std::min(innerCell.width + _innerIt.getX(), outterCell.width + _outterIt.getX());
	const float d = std::min(innerCell.height + _innerIt.getY(), outterCell.height + _outterIt.getY());

	const float w = std::min(c - a, _innerGrid.getCell().width);
	const float h = std::min(d - b, _innerGrid.getCell().height);

	return {w, h};
}


Grid::iterator& OverlayIterator::getInner()
{
	return _innerIt;
}


Grid::iterator& OverlayIterator::getOutter()
{
	return _outterIt;
}


const Grid::iterator& OverlayIterator::getInnerEnd() const
{
	return _innerEnd;
}


const Grid::iterator& OverlayIterator::getOutterEnd() const
{
	return _outterEnd;
}


const Grid* OverlayIterator::_getFirstGrid(
		const Grid* g1,
		const Grid* g2)
{
	if (g1->getCell().width <= g2->getCell().width)
		return g1;
	else
		return g2;
}


const Grid* OverlayIterator::_getSecondGrid(
		const Grid* g1,
		const Grid* g2)
{
	if (g1->getCell().width > g2->getCell().width)
		return g1;
	else
		return g2;
}


Grid OverlayIterator::_calcInnerGrid(const Grid* g1, const Grid* g2, const Grid::iterator& outter)
{
	const Grid::Cell& cell1 = g1->getCell();
	const Grid::Cell& cell2 = g2->getCell();

	const size_t colsToBegin = std::floor((outter.getX() - g1->getOffsetX()) / cell1.width);
	const size_t rowsToBegin = std::floor((outter.getY() - g1->getOffsetY()) / cell1.height);
	const size_t colsToEnd = std::ceil((outter.getX() - g1->getOffsetX() + cell2.width) / cell1.width);
	const size_t rowsToEnd = std::ceil((outter.getY() - g1->getOffsetY() + cell2.height) / cell1.height);

	const float x = colsToBegin * cell1.width + g1->getOffsetX();
	const float y = rowsToBegin * cell1.height + g1->getOffsetY();

	return {
			colsToEnd - colsToBegin,
			rowsToEnd - rowsToBegin,
			std::min(cell1.width, cell2.width),
			std::min(cell1.height, cell2.height),
			x,
			y
	};
}


Grid::iterator OverlayIterator::_calcInnerEnd(
		const Grid* g1,
		const Grid* g2,
		const Grid::iterator& outter)
{
	const Grid::Cell& cell1 = g1->getCell();
	const Grid::Cell& cell2 = g2->getCell();
	const int cols = std::floor((outter.getX() + cell2.width) / cell1.width);
	const int rows = std::floor((outter.getY() + cell2.height) / cell1.height);
	const float x = cols * cell1.width;
	const float y = rows * cell1.height;

	Grid::iterator it {g1, x, y};
	return ++it;
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


OverlayIterator overlay(Grid& g1, const Grid& g2)
{
	g1.setOffset(g2.getOffsetX(), g2.getOffsetY());
	g1.setCellSize(g2.getCell().width * g2.getColumns() / g1.getColumns(),
				   g2.getCell().height * g2.getRows() / g1.getRows());

	return {&g1, &g2};
}
