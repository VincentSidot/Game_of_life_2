#pragma once

#include <vector>
#include "grid.h"

class structure : public grid
{
public:
	structure(size_t line, size_t row) : grid(line, row)
	{}
	~structure()
	{}

	structure(std::vector<std::vector<bool>> const &entry) : grid(entry.size(), entry[0].size())
	{
		for (size_t i = 0; i < m_line; i++)
		{
			for (size_t j = 0; j < m_row; j++)
			{
				this->set(i, j, entry[i][j]);
			}
		}
	}

	void setLine(size_t line) {
		this->m_line = line;
	}
	void setRow(size_t row) {
		this->m_row = row;
	}

	size_t line() const { return m_line; }
	size_t row() const { return m_row; }

protected:

};



structure planeur();