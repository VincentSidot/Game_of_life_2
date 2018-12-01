#include "Application.h"




Application::Application(Configuration * config) : m_game(config)
{
	if (!config->fullscreen())
	{

		window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(config->width()),static_cast<unsigned int>(config->height())), "Jeu de la vie");
	}
	else
	{
		window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(config->width()), static_cast<unsigned int>(config->height())), "Jeu de la vie", sf::Style::Fullscreen);
	}
	window->setVerticalSyncEnabled(true);
	m_config = config;
}

Application::~Application()
{
	delete window;
}

void Application::fps()
{
	size_t fps = size_t(1 / m_clock.getElapsedTime().asSeconds());
	m_clock.restart();
	sf::Font m_font;
	m_font.loadFromFile("arial.ttf");
	sf::Text m_fps_text;
	m_fps_text.setFont(m_font);
	m_fps_text.setCharacterSize(m_config->char_size());
	m_fps_text.setFillColor(m_config->text_color());
	m_fps_text.setString(std::to_string(fps));
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);//to change
	rect.setPosition(m_fps_text.getPosition());
	rect.setSize({ 1.2f*m_fps_text.getLocalBounds().width,1.2f*m_fps_text.getLocalBounds().height });
	window->draw(rect);
	window->draw(m_fps_text);
}

void Application::draw_grid()
{
	if (!m_config->grid())
		return;
	std::vector<sf::Vertex>	vertices2;
	float ni, nj;
	for (size_t i = 0; i < m_config->line(); i++)
	{
		ni = m_config->height()*i / float(m_config->line());
		vertices2.push_back(sf::Vertex(sf::Vector2f(0, ni), m_config->color_line()));
		vertices2.push_back(sf::Vertex(sf::Vector2f(float(m_config->width()), ni), m_config->color_line()));
	}
	for (size_t j = 0; j < m_config->row(); j++)
	{
		nj = m_config->width()*j / float(m_config->row());
		vertices2.push_back(sf::Vertex(sf::Vector2f(nj, 0), m_config->color_line()));
		vertices2.push_back(sf::Vertex(sf::Vector2f(nj, float(m_config->height())), m_config->color_line()));
	}
	window->draw(&vertices2[0], vertices2.size(), sf::Lines);
}

void Application::first_draw()
{
	//On poses les cellules
	std::vector<sf::Vertex>	vertices;
	window->clear(m_config->color_dead());
	for (size_t i = 0; i < m_config->line(); i++)
	{
		for (size_t j = 0; j < m_config->row(); j++)
		{
			if (m_game.alive(i, j))
			{
				add_cell(vertices, i, j, true);
			}
		}
		window->draw(&vertices[0], vertices.size(), sf::Quads);
	}
}

void Application::update_draw(std::stack<coord> toUpdate)
{
	window->clear(m_config->color_dead());
	std::vector<sf::Vertex>	vertices;
	while (!toUpdate.empty())
	{
		coord c = toUpdate.top();
		add_cell(vertices, c.i, c.j,true);
		toUpdate.pop();
	}
	window->draw(&vertices[0], vertices.size(), sf::Quads);
}

void Application::add_cell(std::vector<sf::Vertex>& vertices, size_t i, size_t j, bool alive)
{
	float taille_x = float(m_config->width()) / float(m_config->row());
	float taille_y = float(m_config->height()) / float(m_config->line());
	float ni, nj;
	ni = m_config->height()*i / float(m_config->line());
	nj = m_config->width()*j / float(m_config->row());
	vertices.push_back(sf::Vertex(sf::Vector2f(nj, ni), (alive)?m_config->color_alive():m_config->color_dead()));
	vertices.push_back(sf::Vertex(sf::Vector2f(nj, ni + taille_y), (alive) ? m_config->color_alive() : m_config->color_dead()));
	vertices.push_back(sf::Vertex(sf::Vector2f(nj + taille_x, ni + taille_y), (alive) ? m_config->color_alive() : m_config->color_dead()));
	vertices.push_back(sf::Vertex(sf::Vector2f(nj + taille_x, ni), (alive) ? m_config->color_alive() : m_config->color_dead()));
}

void Application::play()
{
	m_game.firstIter(0.1f);
	m_clock.restart();
	this->first_draw();
	this->draw_grid();
	window->display();
	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::Resized)
			{
				m_config->setWindowSize({ event.size.width, event.size.height });
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Escape:
					window->close();
					break;
				case sf::Keyboard::Key::Space:
					m_paused = !m_paused;
					m_clock.restart();
					break;
				case sf::Keyboard::Key::K:
					m_game.killAll();
					break;
				case sf::Keyboard::Key::G:
					m_config->setGrid(!m_config->grid());
					break;
				default:
					break;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
			int i = localPosition.y*m_config->line() / m_config->height();
			int j = localPosition.x*m_config->row() / m_config->width();
			
			if (m_game.isLicite(i, j))
			{
				m_game.setAlive(i, j);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
			int i = localPosition.y*m_config->line() / m_config->height();
			int j = localPosition.x*m_config->row() / m_config->width();
			if (m_game.isLicite(i, j))
			{
				m_game.setDead(i, j);
			}
		}

		if (m_paused) this->first_draw();
		else this->update_draw(this->m_game.next_iter());
		this->draw_grid();
		this->fps();
		window->display();
	}
}