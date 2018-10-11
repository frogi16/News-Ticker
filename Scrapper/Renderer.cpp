#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::draw(sf::RenderTarget & target)
{
	texture.display();
	sprite.setTexture(texture.getTexture());
	target.draw(sprite);
}

void Renderer::init()
{
	texture.display();
	sprite.setTexture(texture.getTexture());
}

void Renderer::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Renderer::setSize(sf::Vector2f size)
{
	if (size.x == 0 || size.y == 0)
	{
		throw "Renderer can't have any dimension equal zero";
	}
	else
	{
		texture.create(size.x, size.y);
	}
}

bool Renderer::isColliding(sf::Vector2f point)
{
	return sprite.getGlobalBounds().contains(point);
}
