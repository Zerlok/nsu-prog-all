#include "main.h"

#include "graph.h"


// ---------------- Adjacency Matrix ----------------

AdjacencyMatrix::AdjacencyMatrix(const int width)
	: _matrix(width, std::vector<int>(width))
{
	std::cout << "AdjacencyMatrix created." << std::endl;
}


AdjacencyMatrix::~AdjacencyMatrix()
{
	std::cout << "AdjacencyMatrix destroied." << std::endl;
}


AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& m)
	: _matrix(m._matrix)
{
	std::cout << "AdjacencyMatrix copied." << std::endl;
}


bool AdjacencyMatrix::is_linked(const int v1, const int v2) const
{
	return _matrix[v1][v2];
}


int AdjacencyMatrix::count_edges(const int v_indx) const
{
	int total = 0;

	for (auto x : _matrix)
		for (auto y : x)
			if (y == 1)
				total++;

	return total;
}


const std::vector<int> AdjacencyMatrix::get_nearest(const int v_indx) const
{
	int indx = 0;
	std::vector<int> neighbours;

	for (auto v : _matrix[v_indx])
	{
		if (v == 1)
			neighbours.push_back(indx);

		indx++;
	}

	return neighbours;
}


void AdjacencyMatrix::link(const int v1, const int v2)
{
	if ((v1 >= _matrix.size())
		|| (v2 >= _matrix.size()))
		return;

	_matrix[v1][v2] = 1;
	_matrix[v2][v1] = 1;
}


void AdjacencyMatrix::link(const int v_indx, const std::vector<int>& vertices)
{
	for (auto it : vertices)
		link(v_indx, it);
}


void AdjacencyMatrix::unlink(const int v1, const int v2)
{
	_matrix[v1][v2] = 0;
	_matrix[v2][v1] = 0;
}


void AdjacencyMatrix::unlink(const int v_indx, const std::vector<int>& vertices)
{
	for (auto it : vertices)
		unlink(v_indx, it);
}


void AdjacencyMatrix::show() const
{
	std::cout << "Matrix:" << std::endl;
	for (auto x : _matrix)
	{
		for (auto y : x)
		{
			std::cout << y << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


// ---------------- Incidence Matrix ----------------

IncidenceMatrix::IncidenceMatrix(const int v_num, const int e_num)
	: _matrix(e_num, std::vector<int>(v_num)), _vg(v_num)
{
	std::cout << "IncidenceMatrix created." << std::endl;
}

IncidenceMatrix::~IncidenceMatrix()
{
	std::cout << "AdjacencyMatrix destroied." << std::endl;
}

IncidenceMatrix::IncidenceMatrix(const IncidenceMatrix& m)
	: _matrix(m._matrix)
{
	std::cout << "AdjacencyMatrix copied." << std::endl;
}


bool IncidenceMatrix::is_linked(const int v1, const int v2) const
{
	// std::cout << "Is linked " << v1 << " - " << v2 << std::endl;

	if (_matrix.empty())
		return false;

	for (auto edge : _matrix)
		if ((edge[v1] == 1)
			&& (edge[v2] == 1))
			return true;

	return false;
}


int IncidenceMatrix::count_edges(const int v_indx) const
{
	int total = 0;

	for (auto edge : _matrix)
		if (edge[v_indx] == 1)
			total++;

	return total++;
}


const std::vector<int> IncidenceMatrix::get_nearest(const int v_indx) const
{
	//     0  1  2  3  4  5
	// e1 [0, 0, 0, 1, 0, 1]
	// e2 [1, 0, 1, 0, 0, 0]
	// e3 [0, 0, 0, 1, 1, 0]
	// e4 [0, 1, 0, 0, 0, 1]

	std::vector<int> neighbours;

	for (auto edge : _matrix)
	{
		if (edge[v_indx] == 1)
		{
			int indx = 0;

			for (auto v : edge)
			{
				if ((v != v_indx)
					&& (v == 1))
					neighbours.push_back(indx);

				indx++;
			}
		}
	}

	return neighbours;
}


void IncidenceMatrix::link(const int v1, const int v2)
{
	std::cout << "Linking " << v1 << " - " << v2 << std::endl;

	if (is_linked(v1, v2))
		return;

	std::vector<int> edge(_vg);

	edge[v1] = 1;
	edge[v2] = 1;

	std::cout << "new edge: " << edge << std::endl;

	_matrix.push_back(edge);
}

void IncidenceMatrix::link(const int v_indx, const std::vector<int>& vertices)
{
	for (auto it : vertices)
		link(v_indx, it);
}


void IncidenceMatrix::unlink(const int v1, const int v2)
{
	std::cout << "Unlinking " << v1 << " - " << v2 << std::endl;

	for (auto edge = _matrix.begin();
		edge != _matrix.end();
		edge++)
		if (((*edge)[v1] == 1)
			&& ((*edge)[v2] == 1))
		{
			_matrix.erase(edge);
			break;
		}
}


void IncidenceMatrix::unlink(const int v_indx, const std::vector<int>& vertices)
{
	for (auto it : vertices)
		unlink(v_indx, it);
}


void IncidenceMatrix::show() const
{
	std::cout << "IncidenceMatrix:" << std::endl;

	if (_matrix.empty())
	{
		std::cout << "empty\n" << std::endl;
		return;
	}

	for (auto x : _matrix)
	{
		for (auto y : x)
		{
			std::cout << y << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
