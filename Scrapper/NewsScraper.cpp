#include "NewsScraper.h"

#include <queue>

NewsScraper::NewsScraper()
{
}

void NewsScraper::tidyData(NewsData & data)
{
	tidyString(data.title);
	tidyString(data.URL);
	tidyString(data.description);
}

NewsScraper::~NewsScraper()
{
}
