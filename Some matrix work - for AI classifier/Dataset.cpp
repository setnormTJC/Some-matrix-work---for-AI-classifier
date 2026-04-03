#include "Dataset.h"
#include<iomanip>
#include <iostream>
#include<sstream> 
#include<string> 

Dataset::Dataset(const std::string& url)
	:
	features(0, 0), targets(0, 0) //dummy TEMP values
{

	cpr::Response r = cpr::Get(cpr::Url{ url });

	if (r.status_code == 200) //"OK" HTTP status code
	{
		std::string text = r.text;
		//std::cout << text << "\n";

		parseCSVText(text); 

		determineColumnWidth(); 
	}

	else
	{
		std::cout << "Error " << r.status_code << " - " << r.error.message << "\n";
	}
	
}

void Dataset::printFeatureNames() const
{


	for (const std::string& currentFeatureName : featureNames)
	{
		std::cout << std::left << std::setw(colWidth) << currentFeatureName + " | ";
	}
	std::cout << "\n";
}

void Dataset::printFeatures() const
{
	auto it = std::max_element(featureNames.begin(), featureNames.end(),
		[](const std::string& a, const std::string& b)
		{
			return a.length() < b.length();
		});

	int maxFeatureNameLength = it._Ptr->length();
	int padding = 5;
	int colWidth = maxFeatureNameLength + padding;

	features.print(colWidth); 
}

int Dataset::featuresRowCount() const
{
	return features.dims().first; 
}

int Dataset::targetsColCount() const
{
	return targets.dims().second;  
}

Matrix Dataset::getOneHotTargets() const
{
	int numRows = targets.data.size(); 
	int numClasses = targetsToNums.size(); 

	Matrix oneHotTargets(numRows, numClasses);

	for (int i = 0; i < targets.data.size(); ++i)
	{
		//if(targets.data.at(i) == )
		int classID = targets.data.at(i).at(0); 

		oneHotTargets.set(i, classID, 1.0f);
	}

	return oneHotTargets; 
}

std::map<int, std::string> Dataset::getNumsToTargets() const
{
	if (targetsToNums.size() == 0) throw std::runtime_error("Cannot invert an empty map");

	std::map<int, std::string> numsToTargets; 

	for (const auto& [target, num] : targetsToNums)
	{
		numsToTargets.insert({ num, target });
	}

	return numsToTargets;
}

std::vector<std::string> Dataset::getOriginalTargets() const
{
	std::vector<std::string> originalTargets; 

	auto numsToTargets = getNumsToTargets(); 
	
	for (int row = 0; row < targets.data.size(); ++row)
	{
		float target = targets.data.at(row).at(0); 

		std::string originalTarget = numsToTargets.at(target); 

		originalTargets.push_back(originalTarget);
	}

	return originalTargets;
}





void Dataset::parseCSVText(std::string& csvText)
{
	loadHeaderRow(csvText); 

	loadDataRows(csvText); 
}

void Dataset::loadHeaderRow(std::string& csvText)
{
	//assume first line contains column headers (metadata): 
	std::string firstLine = csvText.substr(0, csvText.find('\n'));

	csvText.erase(0, firstLine.size() + 1); //get rid of the first line now that we've a copy

	auto returnLoc = std::find(firstLine.begin(), firstLine.end(), '\r'); //iris dataset from given link contains \r\n 
	if (returnLoc != firstLine.end()) firstLine.erase(returnLoc);

	std::stringstream header(firstLine); //getline can function as a "csv splitter", but it needs to split a STREAM - can't work on a string
	//stringstreams, not surprisingly, can be instantiated with a string 

	std::string currentFeatureName;
	while (std::getline(header, currentFeatureName, ','))
	{
		featureNames.push_back(currentFeatureName);
	}

	//the last featureName is actually the target (in "typical" classification-oriented datasets)
	targetName = featureNames.back();
	featureNames.pop_back();

}


std::vector<std::string> Dataset::getDataRows(std::string& tableText)
{
	std::stringstream data(tableText);
	std::string row;

	std::vector<std::string> rows; 
	
	while (std::getline(data, row, '\n'))
	{
		auto returnLoc = std::find(row.begin(), row.end(), '\r'); //again, iris dataset from given link contains \r\n 
		if (returnLoc != row.end()) row.erase(returnLoc);

		//now split the row by commas
		//std::cout << row << "\n\n";
		//std::stringstream ss(row);

		rows.push_back(row); 
	}
	return rows; 


}

void Dataset::loadDataRows(std::string& tableText)
{

	std::vector<std::string> dataRows = getDataRows(tableText);

	for (std::string& s : dataRows)
	{
		int currentFeatureCount = 0;
		std::string currentFeature;
		std::vector<float> currentFeatureRow;
		std::vector<float> currentTargetRow;

		std::stringstream ss(s); 
		while (std::getline(ss, currentFeature, ','))
		{
			currentFeatureCount++;

			if (currentFeatureCount <= featureNames.size())
			{
				currentFeatureRow.push_back(std::stof(currentFeature)); //convert string to float
			}

			else //we are in the last column
			{
				std::string currentTarget = currentFeature; //the "feature" is actually a target 
				if (targetsToNums.find(currentTarget) == targetsToNums.end())
				{
					targetsToNums[currentTarget] = targetsToNums.size();
				}

				currentTargetRow.push_back(targetsToNums.at(currentTarget));
			}
		}

		features.data.push_back(currentFeatureRow);
		targets.data.push_back(currentTargetRow);
	}

}

void Dataset::determineColumnWidth()
{
	auto it = std::max_element(featureNames.begin(), featureNames.end(),
		[](const std::string& a, const std::string& b)
		{
			return a.length() < b.length();
		});

	int maxFeatureNameLength = it._Ptr->length();
	int padding = 5;
	colWidth = maxFeatureNameLength + padding;
}
