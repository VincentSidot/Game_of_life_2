#pragma once

#include "Configuration.h"
#include <ctime>
#include <stack>
#include <cstdlib>
#include "grid.h"
#include "structure.h"

typedef struct coord
{
	size_t i;
	size_t j;
} coord;

class Game
{
public:
	Game(Configuration *);
	~Game();

	bool alive(size_t i, size_t j) const { return m_current.get(i, j); }
	void setAlive(size_t i, size_t j) { m_current.set(i, j, true); }
	void setDead(size_t i, size_t j) { m_current.set(i, j, false); }
	bool isLicite(size_t i, size_t j) const { return m_current.is_range(i, j); }
	size_t iter() const { return m_iter; }

	void killAll();

	std::stack<coord> next_iter();


	void firstIter(float p);
	void printStruct(structure const &struc, size_t i, size_t j);


protected:
	//alive is true, dead is false
	int count_arround(size_t i, size_t j);

	Configuration * m_config;

	size_t m_iter;

	grid m_current;
	grid m_calcul;

};

