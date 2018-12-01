#pragma once

class grid
{
public:
	grid(size_t line,size_t row);
	grid(size_t line, size_t row, bool def);
	~grid();

	bool& operator()(size_t i, size_t j);

	bool is_range(int i, int j) const;
	static void swap_grid(grid* g1, grid* g2);

	bool get(size_t i, size_t j) const;
	void set(size_t i, size_t j,bool value);

	bool* getAddr() const { return m_grid; }
	void setAddr(bool *addr) { m_grid = addr; }

protected:
	size_t m_line;
	size_t m_row;
	bool *m_grid;
};
