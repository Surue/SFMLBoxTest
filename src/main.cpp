#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60.f);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(2,56,37));
	float speed = 5.0f;
	Image image(std::string("data/image.png"));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "User pressed SPACE\n";
				}
			}
		}
		sf::Vector2f delta_move;
		//Manage inputs
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			delta_move.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			delta_move.x += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			delta_move.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			delta_move.y += 1.0f;
		}

		shape.setPosition(shape.getPosition() + speed * delta_move);

		window.clear();

		image.draw(window);
		window.draw(shape);
		
		window.display();
	}
	system("pause");
	return 0;
}