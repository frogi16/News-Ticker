#include "NewsRenderer.h"
#include <windows.h>
#include <exception>
#include <fstream>

NewsRenderer::NewsRenderer()
{
}

NewsRenderer::NewsRenderer(NewsData data) : mTitle(data.title + " * "), mURL(data.URL), mDescription(data.description)
{
	std::ofstream myfile;
	myfile.open("output.txt", std::ios::app);
	myfile << data.title <<"\n" << data.URL << "\n" << data.description << "\n\n";
}


void NewsRenderer::init()
{
	if (!font.loadFromFile("NewsCycle-Regular.ttf"))
	{
		std::cout << "FUCK ";
	}

	title.setFont(font);
	title.setCharacterSize(characterSize);
	sf::String temp = sf::String::fromUtf8(mTitle.begin(), mTitle.end());
	title.setString(temp);
	title.setFillColor(sf::Color::White);
	
	if (tempSize.x == 0)																//computing real size if any of the dimensions was left zero
	{
		texture.create(title.getLocalBounds().width + 2 * borderSize, tempSize.y);
	}
	else if (tempSize.y == 0)
	{
		texture.create(tempSize.x, title.getLocalBounds().height + 2 * borderSize);
	}
	else
	{
		texture.create(tempSize.x, tempSize.y);
	}

	title.setPosition(borderSize, (texture.getSize().y - title.getLocalBounds().height) / 2.f);
	border.setSize(sf::Vector2f(texture.getSize().x - borderSize, texture.getSize().y - borderSize));
	texture.clear(sf::Color(232, 25, 10));
	if(borderSize)
		texture.draw(border);
	texture.draw(title);
	texture.display();
	sprite.setTexture(texture.getTexture());
}

void NewsRenderer::update(sf::Time & dt)
{
}

void NewsRenderer::setSize(sf::Vector2f size)
{
	if (size.x == 0 && size.y == 0)
	{
		throw "At least one dimension of NewsRenderer must be specified";
	}
	else
	{
		tempSize = size;
	}
}

void NewsRenderer::click(sf::Vector2f & position)
{
	if (isColliding(position))
	{
		open();
	}
}

void NewsRenderer::setCharacterSize(int size)
{
	characterSize = size;
}

void NewsRenderer::open()
{
	std::wstring temp(mURL.begin(), mURL.end());
	ShellExecute(0, 0, temp.c_str(), 0, 0, SW_SHOW);
}

NewsRenderer::~NewsRenderer()
{

}

void NewsRenderer::createBorder(int size)
{
	borderSize = size;

	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(borderSize);
	border.setPosition(borderSize / 2, borderSize / 2);
}