#include "BankierScraper.h"

BankierScraper::BankierScraper()
{
}

std::vector<NewsData> BankierScraper::convert(pugi::xml_node source)
{
	std::vector<NewsData> result;

	std::vector<pugi::xml_node> selected = selectDataByAttribute(source, "class", "box300 left");

	if (selected.size() == 1)															//there should be only one box matching this criteria
	{
		pugi::xml_node list;
		list = selected[0].first_child().next_sibling().first_child();					//ul which contains many li nodes - each one is a separate news

		for (auto i = list.first_child().next_sibling(); i; i = i.next_sibling())		//first child has to be handled separately because it is built different TODO: handle separately
		{
			auto newsWrapper = i.first_child();

			NewsData news;

			news.title = newsWrapper.first_child().value();

			std::string url = newsWrapper.attribute("href").as_string();
			if (url.size() > 0 && url[0] == '/')										//internal links starts with '/' and don't have "https://www.bankier.pl" prefix, so I have to merge it manually
			{
				news.URL = "https://www.bankier.pl" + url;
			}
			else
			{
				news.URL = url;
			}

			tidyData(news);
			result.push_back(news);
		}
	}
	else
	{
		throw "Bankier.pl: class=\"box300 left\" filtering returned more results than expected.";
	}

	return result;
}


BankierScraper::~BankierScraper()
{
}
