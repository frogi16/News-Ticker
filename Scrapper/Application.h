#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <curl/curl.h>

#include "Ticker.h"
#include "Button.h"

class Application
{
public:
	Application();
	void run();
	~Application();
private:
	void processInput();
	void update();
	void draw();
	void updateTime();

	size_t targetFPS;

	sf::VideoMode desktop;
	sf::RenderWindow window;
	sf::Clock dtClock, oneSecondClock;
	sf::Time dt, targetFrameTime;
	sf::Font newsCycle;

	std::shared_ptr<Ticker> ticker;
	std::shared_ptr<Button> button;

	int FPS;
	bool isWindowMoving = false;
};

