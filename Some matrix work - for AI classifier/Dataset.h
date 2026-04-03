#pragma once

#include<cpr/cpr.h>
#include <string>
#include "Matrix.h"
#include <map>


class Dataset
{
private: 
	std::vector<std::string> featureNames; 
	std::string targetName; 

	Matrix features;
	Matrix target; 
public: 
	Dataset() = delete; 
	/*parses a CSV file*/
	Dataset(const std::string& url);

	//std::vector<std::string> featureNames();

private: 
	/*helper that is called by Dataset constructor*/
	void parseCSVText(const std::string& csvText);

};