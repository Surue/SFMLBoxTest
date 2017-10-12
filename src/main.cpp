#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

#include <Box2D/Box2D.h>

int main()
{

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60.f);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(2, 56, 37));
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(0, 0); //set the starting position
	b2Body* dynamicBody = myWorld->CreateBody(&myBodyDef);

	float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	

	float speed = 5.0f;
	Image image(std::string("data/image.png"));
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
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
		

		shape.setPosition(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);

		window.clear();

		image.draw(window);
		window.draw(shape);
		
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}