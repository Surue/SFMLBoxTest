#ifndef PLATFORMER_CHAR_H
#define PLATFORMER_CHAR_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <utility.h>

class PlatformerCharacter
{
public:
	PlatformerCharacter(b2World&);
	~PlatformerCharacter();
	void update(float move, bool jump);
	void draw(sf::RenderWindow&);
	void touch_ground();
	void leave_ground();
private:
	int foot = 0;
	b2Body* body;
	sf::RectangleShape rect;
	sf::Vector2f center_position = sf::Vector2f(400.f, 300.f);
	sf::Vector2f size = sf::Vector2f(64.f,64.f);
	float walk_speed = 5.0f;

	ContactData contactData;
};

#endif // !PLATFORMER_CHAR_H
