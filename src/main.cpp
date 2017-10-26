#include <SFML/Graphics.hpp>
#include <platformer_character.h>
#include <platform.h>
#include <utility.h>
#include <iostream>

#include <Box2D/Box2D.h>

int main()
{

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World myWorld = b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(framerate);
	

	float32 timeStep = 1 / framerate;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	PlatformerCharacter character(myWorld);
	Platform ground(myWorld);
	
	while (window.isOpen())
	{

		float move = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move += 1.0f;
		}
		myWorld.Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		character.update(move);
		
		window.clear();
		character.draw(window);
		ground.draw(window);
		window.display();
	}

	system("pause");
	return 0;
}