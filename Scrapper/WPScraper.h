#pragma once
#include "NewsScraper.h"

class WPScraper :
	public NewsScraper
{
public:
	WPScraper();
	std::vector<NewsData> convert(pugi::xml_node source);
	~WPScraper();
};

