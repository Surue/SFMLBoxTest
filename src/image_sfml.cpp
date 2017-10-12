#include <image_sfml.h>

Image::Image(std::string& filename)
{
	
	if (!texture.loadFromFile(filename))
	{
		// error...
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.1f, 0.1f));
}

Image::~Image()
{

}

void Image::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}