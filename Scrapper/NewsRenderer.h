#pragma once

#include <iostream>

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include "NewsData.h"

#include "Renderer.h"

class NewsRenderer : public Renderer
{
public:
	NewsRenderer();
	NewsRenderer(NewsData data);

	virtual void init();								//ensure that all required variables are set and prepare renderer to be drawn
	virtual void update(sf::Time &dt);
	virtual void setSize(sf::Vector2f size);			//if any dimension is 0 it will calculated in init() function depending on the text properties - character size, length etc.
														//It allows to set constant height and dynamically adjust width (and vice versa).
	virtual void click(sf::Vector2f &position);
	virtual sf::Vector2f getSize()
	{ return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height); }
	
	virtual sf::FloatRect getPosition() { return sprite.getGlobalBounds(); }
	virtual void setCharacterSize(int size);
	virtual void open();
	void createBorder(int size);
	~NewsRenderer();
protected:
	sf::Font font;
	sf::Text title;
	std::string mTitle, mURL, mDescription;
private:
	sf::Vector2f tempSize;
	int borderSize=0;
	sf::RectangleShape border;
};

