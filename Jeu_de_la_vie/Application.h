#pragma once

#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "Game.h"
#include <vector>
#include <stack>

class Application
{
public:
	Application(Configuration *config);
	~Application();
	void play();
protected:

	void fps();
	void draw_grid();
	void first_draw();
	void update_draw(std::stack<coord> toUpdate);
	void add_cell(std::vector<sf::Vertex> &vec, size_t i, size_t j, bool alive);

	sf::RenderWindow *window;
	Configuration * m_config;
	Game m_game;
	bool m_paused = true;
	sf::Clock m_clock;
};

