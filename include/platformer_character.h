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
	void update(bool jump_button);
	void draw(sf::RenderWindow&);
	void touch_ground(bool);
	void leave_ground(bool);
private:
	int foot = 0;
	int wallJumping_speed = 10000;
	bool isWalled = false;
	b2Body* body;
	sf::RectangleShape rect;
	sf::Vector2f center_position = sf::Vector2f(400.f, 300.f);
	sf::Vector2f size = sf::Vector2f(64.f,64.f);
	const float walk_speed = 5.0f;
	const float jump_speed = 10.f;
	ContactData contactData;
	ContactData contactDataWall;
};

#endif // !PLATFORMER_CHAR_H
