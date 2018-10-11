#include "Ticker.h"

Ticker::Ticker(std::vector<NewsData> &data)
{
	for (auto &element : data)
	{
		feed.push_back(std::make_unique<NewsRenderer>(element));
		lastNewsIndex = feed.size() - 1;
	}
}

void Ticker::updateContent(std::vector<NewsData> &data)
{
	for (auto &element : data)
	{
		feed.push_back(std::make_unique<NewsRenderer>(element));
		lastNewsIndex = feed.size() - 1;
	}
}

Ticker::Ticker(const Ticker &)
{
}

void Ticker::draw(sf::RenderTarget & target)
{
	for (auto &element : feed)
	{
		element->draw(texture);
	}

	texture.draw(border);
	texture.display();
	sprite.setTexture(texture.getTexture());
	target.draw(sprite);
}

void Ticker::update(sf::Time & dt)
{
	for (auto &element : feed)												//move all news
	{
		element->setPosition(sf::Vector2f(element->getPosition().left - speedPerSecond * dt.asSeconds(), element->getPosition().top));
	}

	for (size_t i = 0; i < feed.size(); i++)
	{
		auto &news = feed[i];
		
		if (news->getPosition().left + news->getPosition().width < 0)		//if any of them completely moved beyond the screen place it behind the last one
		{
			news->setPosition(sf::Vector2f(feed[lastNewsIndex]->getPosition().left + feed[lastNewsIndex]->getPosition().width, feed[lastNewsIndex]->getPosition().top));
			lastNewsIndex = i;
		}
	}
}

void Ticker::init()
{
	std::random_shuffle(feed.begin(), feed.end());

	for (auto &element : feed)
	{
		element->init();
	}

	int i = 0;
	for (auto &element : feed)
	{
		if (i == 0)
			element->setPosition(sf::Vector2f(0, 0));
		else
		{
			element->setPosition(sf::Vector2f(feed[i - 1]->getPosition().left + feed[i - 1]->getPosition().width, feed[i - 1]->getPosition().top));
		}
		i++;
	}

	border.setSize(sf::Vector2f(texture.getSize().x - borderSize, texture.getSize().y - borderSize));
	texture.draw(border);
	texture.display();
	sprite.setTexture(texture.getTexture());
}

void Ticker::click(sf::Vector2f &position)
{
	if (isColliding(position))
	{
		for (auto &element : feed)
		{
			/*if (element->isColliding(position-sprite.getPosition()))
			{*/
			element->click(position - sprite.getPosition());
			//}
		}
	}
}

Ticker::~Ticker()
{
}

void Ticker::setSize(sf::Vector2f size)
{
	if (size.x == 0 || size.y == 0)
	{
		throw "Ticker can't have any dimension equal zero";
	}
	else
	{
		texture.create(size.x, size.y);

		for (auto &element : feed)
		{
			element->setSize(sf::Vector2f(0, size.y));
		}
	}
}

void Ticker::createBorder(int size)
{
	borderSize = size;

	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(borderSize);
	border.setPosition(borderSize / 2, borderSize / 2);
}

void Ticker::setCharacterSize(int size)
{
	characterSize = size;

	for (auto &element : feed)
	{
		element->setCharacterSize(22);
	}
}
