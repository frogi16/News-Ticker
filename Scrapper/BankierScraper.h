#pragma once
#include "NewsScraper.h"

class BankierScraper :
	public NewsScraper
{
public:
	BankierScraper();
	virtual std::vector<NewsData> convert(pugi::xml_node source);
	virtual ~BankierScraper();
};

