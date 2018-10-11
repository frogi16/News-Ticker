#include "WPScraper.h"

#include <algorithm>

WPScraper::WPScraper()
{
}

std::vector<NewsData> WPScraper::convert(pugi::xml_node source)
{
	std::vector<NewsData> result;
	std::vector<pugi::xml_node> nodes = selectDataByAttribute(source, "class", "_1IrxhB");

	for (size_t i = 0; i < std::min(nodes.size(), (size_t)20); i++)								//first 20 or so news are on the "main" main screen, the rest is inside categories like fashion, so...
	{
		NewsData news;
		news.title = nodes[i].attribute("title").as_string();
		news.URL = nodes[i].attribute("href").as_string();

		tidyData(news);
		result.push_back(news);
	}

	return result;
}

WPScraper::~WPScraper()
{
}
