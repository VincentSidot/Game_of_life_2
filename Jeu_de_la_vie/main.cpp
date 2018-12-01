#include "Application.h"
#include "Configuration.h"


int main()
{
	int col = 200;
	int ligne = 100;
	Configuration config(1920, 1080, col, ligne, sf::Color::Magenta, sf::Color::White,sf::Color::Black,false,true);
	Application app(&config);
	app.play();
	return 0;
}