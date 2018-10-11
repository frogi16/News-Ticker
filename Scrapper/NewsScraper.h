#pragma once

#include "Scraper.h"
#include "NewsData.h"

class NewsScraper : public Scraper
{
public:
	NewsScraper();
	virtual std::vector<NewsData> convert(pugi::xml_node source) = 0;
	virtual ~NewsScraper();
protected:
	void tidyData(NewsData &data);
};

