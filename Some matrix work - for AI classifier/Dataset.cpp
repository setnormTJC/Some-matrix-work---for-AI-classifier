#include "Dataset.h"
#include <iostream>

Dataset::Dataset(const std::string& url)
	:
	features(1, 2), target(3, 4) //dummy TEMP values
{

	cpr::Response r = cpr::Get(cpr::Url{ url });

	if (r.status_code == 200) //"OK" HTTP status code
	{
		std::string text = r.text;
		std::cout << text << "\n";
	}

	else
	{
		std::cout << "Error " << r.status_code << " - " << r.error.message << "\n";
	}
	
}

void Dataset::parseCSVText(const std::string& csvText)
{
}
