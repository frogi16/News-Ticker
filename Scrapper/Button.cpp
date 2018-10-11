#include "Button.h"


Button::Button(sf::IntRect dimensions, std::string text) :
	button(sf::Vector2f(dimensions.width, dimensions.height)),
	isGrabbed(false),
	isClicked(false)
{
	font.loadFromFile("NewsCycle-Regular.ttf");

	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setCharacterSize(dimensions.height / 2);

	button.setPosition(dimensions.left, dimensions.top);
	button.setFillColor(sf::Color(232, 25, 10));
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(-5);

	buttonText.setOrigin(buttonText.getLocalBounds().left + buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().top + buttonText.getLocalBounds().height / 2);	//center the origin point
	buttonText.setPosition(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + button.getSize().y / 2);	//set the text's origin's position exactly as box's origin's position
}

Button::~Button()
{
}

void Button::updateMouse(const sf::Mouse & mouse)
{
	updateMouse(mouse.getPosition(), mouse.isButtonPressed(sf::Mouse::Button::Left));
}

void Button::updateMouse(sf::Vector2i mousePosition, bool isLeftPressed)
{
	bool isHovered = (button.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)));
	auto t = button.getGlobalBounds();

	if (isGrabbed && !isLeftPressed)
	{
		isClicked = true;
	}
	else
	{
		isClicked = false;
	}

	if (isHovered && isLeftPressed)
	{
		isGrabbed = true;
	}
	else
	{
		isGrabbed = false;
	}
}

void Button::draw(sf::RenderTarget & target)
{
	if (isGrabbed)
	{
		button.setFillColor(sf::Color(200, 15, 5));
	}
	else
	{
		button.setFillColor(sf::Color(232, 25, 10));
	}
	target.draw(button);
	target.draw(buttonText);
}
