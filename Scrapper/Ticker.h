#pragma once

#include "Renderer.h"

#include "NewsRenderer.h"
#include <SFML\System\Time.hpp>
#include <memory>

class Ticker : public Renderer
{
public:
	Ticker(std::vector<NewsData> &data);
	Ticker(const Ticker &);

	void draw(sf::RenderTarget &target);
	void update(sf::Time &dt);
	void init();		//ensure that all required variables are set and prepare renderer to be drawn
	void updateContent(std::vector<NewsData> &data);
	void click(sf::Vector2f &position);
	void setSize(sf::Vector2f size);
	void createBorder(int size);
	void setCharacterSize(int size);
	~Ticker();
private:
	std::vector<std::unique_ptr<NewsRenderer>> feed;
	const int speedPerSecond = 50;
	int borderSize = 0;
	int lastNewsIndex;
	sf::RectangleShape border;
};

