#include "Application.h"

#include "SourceDownloader.h"
#include "Ticker.h"

#include "BankierScraper.h"
#include "WPScraper.h"
#include "NiebezpiecznikScraper.h"
#include <winuser.h>

Application::Application() :
	targetFPS(60),
	targetFrameTime(sf::microseconds(double(1000000) / targetFPS)),							//it can be initialized only using microseconds 
	desktop(sf::VideoMode::getDesktopMode()),
	window(sf::VideoMode(desktop.width, 40), "Scraper", sf::Style::None)
{
	curl_global_init(CURL_GLOBAL_ALL);
	window.setFramerateLimit(targetFPS);
	sf::WindowHandle handle = window.getSystemHandle();
	SetWindowPos(handle, HWND_TOPMOST, 0, desktop.height - 40, desktop.width, 40, SWP_NOSIZE);
	/*HRGN region = CreateRectRgn(0, 0, desktop.width-40, 40);
	SetWindowRgn(handle, region, true);*/

	/////////////////////////////////		WP		/////////////////////////////////////

	{
		SourceDownloader wpDownloader;
		wpDownloader.downloadSource("https://www.wp.pl");
		wpDownloader.convertToXML();

		WPScraper wpScraper;
		auto wpData = wpScraper.convert(wpDownloader.getData());

		ticker = std::make_shared<Ticker>(wpData);
	}

	/////////////////////////////////		Bankier		/////////////////////////////////////

	{
		SourceDownloader bankierDownloader;
		bankierDownloader.downloadSource("https://www.bankier.pl");
		bankierDownloader.convertToXML();

		BankierScraper bankierScraper;
		auto bankierData = bankierScraper.convert(bankierDownloader.getData());

		ticker->updateContent(bankierData);
	}

	/////////////////////////////////		Niebezpiecznik		/////////////////////////////////////

	{
		SourceDownloader niebezpiecznikDownloader;
		niebezpiecznikDownloader.downloadSource("https://www.niebezpiecznik.pl");
		niebezpiecznikDownloader.convertToXML();

		NiebezpiecznikScraper niebezpiecznikScraper;
		auto niebezpiecznikData = niebezpiecznikScraper.convert(niebezpiecznikDownloader.getData());

		ticker->updateContent(niebezpiecznikData);
	}

	ticker->setPosition(sf::Vector2f(0, 0));
	ticker->setSize(sf::Vector2f(desktop.width-40, 40));
	ticker->setCharacterSize(16);
	ticker->createBorder(10);
	ticker->init();

	button = std::make_shared<Button>(sf::IntRect(desktop.width - 40, 0, 40, 40), "U");

	newsCycle.loadFromFile("NewsCycle-Regular.ttf");
}

void Application::run()
{
	while (window.isOpen())
	{
		updateTime();
		processInput();
		update();
		draw();
	}
}

Application::~Application()
{
}

void Application::processInput()
{
	sf::Event event;

	if (isWindowMoving)
		window.setPosition(sf::Vector2i(window.getPosition().x, std::min((int)desktop.height - 40, sf::Mouse::getPosition().y-1)));

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if (isWindowMoving)
			{
				isWindowMoving = false;
			}
			else
			{
				if (ticker->isColliding((sf::Vector2f(sf::Mouse::getPosition(window)))))
				{
					ticker->click(sf::Vector2f(sf::Mouse::getPosition(window)));
				}
			}
		}
	}

	button->updateMouse(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Left));

	if (button->clicked())
	{
		isWindowMoving = true;
	}
}

void Application::update()
{
	ticker->update(dt);
}

void Application::draw()
{
	window.clear(sf::Color::Transparent);

	ticker->draw(window);
	button->draw(window);

	window.display();
}

void Application::updateTime()
{
	dt = dtClock.restart();

	if (oneSecondClock.getElapsedTime().asSeconds() >= 1)
	{
		oneSecondClock.restart();
		FPS = 1 / dt.asSeconds();
	}
}