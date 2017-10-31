#include <platformer_character.h>
#include <iostream>

PlatformerCharacter::PlatformerCharacter(b2World & world)
{
	//Create the rectangle
	rect.setPosition(center_position - size / 2.f);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Green);
	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = pixel2meter(center_position);
	myBodyDef.fixedRotation = true;
	body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(
		pixel2meter(size.x) / 2.f, pixel2meter(size.y) / 2.f);
	box.shape = &box_shape;
	box.friction = 0.00f;

	//Create foot sensor
	b2FixtureDef foot;
	b2PolygonShape foot_shape;
	foot.isSensor = true;
	foot_shape.SetAsBox(
		pixel2meter(size.x - 4.f) / 2.f, pixel2meter(2.0f) / 2.f,
		b2Vec2(0.f, pixel2meter(size.y) / 2),
		0.f);
	foot.shape = &foot_shape;
	contactData.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactData.data = this;
	foot.userData = &contactData;

	//Create side sensor
	b2FixtureDef side_sensor;
	side_sensor.isSensor = true;
	std::cout << "size.x = " << size.x << "\n";
	b2PolygonShape side_shape;
	side_shape.SetAsBox(pixel2meter(size.x) / 1.8f, pixel2meter(1.0f) / 2.f);
	side_sensor.shape = &side_shape;
	contactDataWall.contactDataType = ContactDataType::WALL_CHARACTER;
	contactDataWall.data = this;
	side_sensor.friction = 0.f;
	side_sensor.userData = &contactDataWall;


	body->CreateFixture(&box);
	body->CreateFixture(&foot);
	body->CreateFixture(&side_sensor);
}

PlatformerCharacter::~PlatformerCharacter()
{
}

void PlatformerCharacter::update(bool jump_button)
{

	/* manage movements */
	float move_axis = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move_axis += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move_axis -= 1.0f;
	}

	body->SetLinearVelocity(b2Vec2(walk_speed*move_axis, body->GetLinearVelocity().y));

	/* manage vertical mouvements if on the wall */
	if (isWalled 
		&& !jump_button 
		&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		if (body->GetLinearVelocity().y > 0) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.01f));
		}
		else 
		{
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, body->GetLinearVelocity().y / 1.1f));
		}
	}

	/* manage jumps*/
	if (jump_button && foot > 0)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jump_speed));
	}

	center_position = meter2pixel(body->GetPosition());
	rect.setPosition(center_position - size / 2.f);
}

void PlatformerCharacter::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void PlatformerCharacter::touch_ground(bool isWalled)
{
	this->isWalled = isWalled;
	std::cout << "Touch ground\n";
	foot++;
}

void PlatformerCharacter::leave_ground(bool isWalled)
{
	if (isWalled)
	{
		this->isWalled = isWalled;
	}
	else 
	{
		this->isWalled = isWalled;
	}
	std::cout << "Leave ground\n";
	foot--;
}
