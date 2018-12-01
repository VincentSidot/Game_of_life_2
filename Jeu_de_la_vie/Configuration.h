#pragma once
#include <SFML/Graphics.hpp>

typedef unsigned long long ulong;

class Configuration
{
public:
	Configuration(ulong width, ulong height, ulong row, ulong line, sf::Color color_alive, sf::Color color_dead, sf::Color color_line,bool grid = true, bool fullscreen = true)
	{
		m_width = width;
		m_height = height;
		m_color_alive = color_alive;
		m_color_dead = color_dead;
		m_color_line = color_line;
		m_fullscreen = fullscreen;
		m_row = row;
		m_line = line;
		m_grid = grid;
		//m_font.loadFromFile("arial.ttf");
	}
	~Configuration();

	ulong width() const { return m_width; }
	ulong height() const { return m_height; }
	ulong line() const { return m_line; }
	ulong row() const { return m_row; }
	sf::Color color_alive() const { return m_color_alive; }
	sf::Color color_dead() const { return m_color_dead; }
	sf::Color color_line() const { return m_color_line; }
	bool fullscreen() const { return m_fullscreen; }
	bool grid() const { return m_grid; }
	//sf::Font font() const { return m_font; }
	size_t char_size() const { return m_char_size; }
	sf::Color text_color() const { return m_text_color; }

	void setWindowSize(sf::Vector2u wsize) { m_width = wsize.x; m_height = wsize.y; }
	void setGrid(bool value) { m_grid = value; }

protected:
	bool m_fullscreen;
	bool m_grid;
	ulong m_width;
	ulong m_height;
	sf::Color m_color_alive;
	sf::Color m_color_dead;
	sf::Color m_color_line;
	ulong m_row;
	ulong m_line;
	//sf::Font m_font;
	size_t m_char_size = 20;
	sf::Color m_text_color = sf::Color::Red;
};

