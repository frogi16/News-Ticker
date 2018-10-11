#pragma once
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Event.hpp>

struct Informations
{
	bool updateMouse, updateKeyboard;
};

class GUIElement
{
public:
	GUIElement();
	virtual void draw(sf::RenderTarget& target) = 0;
	virtual void updateMouse(const sf::Mouse& mouse) {};
	virtual void updateKeyboard(sf::Event& event) {};
	virtual void eraseCharacter() {};
	virtual Informations getInformations() = 0;
};

