#include "NiebezpiecznikScraper.h"



NiebezpiecznikScraper::NiebezpiecznikScraper()
{
}

std::vector<NewsData> NiebezpiecznikScraper::convert(pugi::xml_node source)
{
	std::vector<NewsData> results;

	auto posts = selectDataByAttribute(source, "class", "post");

	for (auto& post : posts)
	{
		NewsData news;

		auto titleWrapper = post.find_child_by_attribute("class", "title").first_child().first_child();			//real data is inside two outer blocks
		news.title = titleWrapper.attribute("title").as_string();
		news.URL = titleWrapper.attribute("href").as_string();

		auto descriptionWrapper = post.find_child_by_attribute("class", "entry").child("p");
		news.description = descriptionWrapper.first_child().value();

		tidyData(news);
		results.push_back(news);
	}

	return results;
}

NiebezpiecznikScraper::~NiebezpiecznikScraper()
{
}
