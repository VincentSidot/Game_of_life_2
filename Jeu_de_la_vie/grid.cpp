#include "grid.h"



grid::grid(size_t line, size_t row)
{
	m_line = line;
	m_row = row;
	m_grid = new bool[row*line];
}

grid::grid(size_t line, size_t row, bool def)
{
	m_line = line;
	m_row = row;
	m_grid = new bool[row*line];
	for (size_t i = 0; i < line*row; i++)
	{
		m_grid[i] = def;
	}
}

grid::~grid()
{
	if (m_grid != nullptr)
		delete[] m_grid;
}

bool & grid::operator()(size_t i, size_t j)
{
	return m_grid[i * m_row + j];
}

bool grid::is_range(int i, int j) const
{
	if (i < int(m_line) && i >= 0 && j < int(m_row) && j >= 0)
		return true;
	return false;
}

void grid::swap_grid(grid * g1, grid * g2)
{
	bool* tmp;
	tmp = g1->getAddr();
	g1->setAddr(g2->getAddr());
	g2->setAddr(tmp);
}

bool grid::get(size_t i, size_t j) const
{
	return m_grid[i * m_row + j];
}

void grid::set(size_t i, size_t j,bool value)
{
	m_grid[i * m_row + j] = value;
}
