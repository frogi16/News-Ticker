#pragma once

#include <SFML\System\Time.hpp>
#include <memory>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <pugixml.hpp>

class Renderer
{
public:
	Renderer();
	virtual void draw(sf::RenderTarget &target);
	virtual void update(sf::Time &dt) = 0;
	virtual void init();														//ensure that all required variables are set and prepare renderer to be drawn
	virtual void click(sf::Vector2f &position) = 0;
	virtual void setPosition(sf::Vector2f position);
	virtual void setSize(sf::Vector2f size);
	virtual sf::FloatRect getPosition() { return sprite.getGlobalBounds(); }
	virtual bool isColliding(sf::Vector2f point);								//often used to check mouse collision
	~Renderer();
protected:
	int characterSize;															//each renderer has characters and needs a characterSize (well, 99% of them) but not all of them allow changing it from
																				//outside, so each group of renderers should declare some sort of setCharacterSize() function on their own (see NewsRenderer.h)
	sf::Sprite sprite;
	sf::RenderTexture texture;
};

