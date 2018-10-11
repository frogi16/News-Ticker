#pragma once
#include "NewsScraper.h"

class NiebezpiecznikScraper :
	public NewsScraper
{
public:
	NiebezpiecznikScraper();
	std::vector<NewsData> convert(pugi::xml_node source);
	~NiebezpiecznikScraper();
};

