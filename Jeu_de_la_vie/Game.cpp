#include "Game.h"



Game::Game(Configuration *config) : m_calcul(config->line(), config->row(), false), m_current(config->line(), config->row(), false)
{
	m_config = config;
}


Game::~Game()
{
}

int Game::count_arround(size_t i, size_t j)
{
	int rep = 0;
	for (int ii = int(i) - 1; ii <= int(i) + 1; ii++)
	{
		for (int jj = int(j) - 1; jj <= int(j) + 1; jj++)
		{
			if (ii != i || jj != j)
			{
				if (m_calcul.is_range(ii, jj))
				{
					if (m_calcul.get(ii, jj))
						rep += 1;
				}
			}
		}
	}
	return rep;
}

void Game::killAll()
{
	for (int i = 0; i < m_config->line(); i++)
	{
		for (int j = 0; j < m_config->row(); j++)
		{
			m_current.set(i, j, false);
		}
	}
}

std::stack<coord> Game::next_iter()
{
	std::stack<coord> coord;
	int n = 0;
	grid::swap_grid(&m_calcul, &m_current);
	for (size_t i = 0; i < m_config->line(); i++)
	{
		for (size_t j = 0; j < m_config->row(); j++)
		{
			n = count_arround(i, j);
			if ((!m_calcul.get(i, j) && n == 3 ) || (m_calcul.get(i, j) && (n==3 || n==2)))
			{
				m_current.set(i, j, true);
				coord.push({ i,j});
			}
			else
			{
				m_current.set(i, j, false);
			}
		}
	}
	return coord;
}

void Game::firstIter(float p)
{
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < m_config->line(); i++)
	{
		for (int j = 0; j < m_config->row(); j++)
		{
			if (rand() < int(p*RAND_MAX))
			{
				m_current.set(i, j,true);
			}
		}
	}
}