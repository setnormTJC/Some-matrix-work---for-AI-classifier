#pragma once

#include<cpr/cpr.h>
#include <string>
#include "Matrix.h"
#include <map>
#include <sstream>

class Classifier;//forward declaration for giving friendship 

class Dataset
{
private: 
	std::vector<std::string> featureNames; 
	std::string targetName; 

	Matrix features;
	Matrix targets; 

	//int featureCount{}; 
	
	/*Maps, for example, 0 to "Setosa" (Setosa comes first in the Iris dataset)*/
	std::map<std::string, int> targetsToNums; 

	/*This is set by the feature with the longest name (ex: "petal_width" for Iris) -> equispaced columns maybe look nice?*/
	int colWidth; 

public: 
	Dataset() = delete; 
	/**/
	Dataset(const std::string& url);

	void printFeatureNames() const;

	void printFeatures() const;  

	/*returns the number of rows in the table of features (so that Classifier::weightMatrix can set its dimensions accordingly)*/
	int featuresRowCount() const;  

	int targetsColCount() const;

	Matrix getOneHotTargets() const; 

	std::map<int, std::string> getNumsToTargets() const; 

	/*"Original" means the format the targets were in before numeric mapping (ex: Iris-setosa instead of 0.0f)*/
	std::vector<std::string> getOriginalTargets() const; 

private: 
	/*helper that is called by `Dataset` constructor*/
	void parseCSVText(std::string& csvText);

	void loadHeaderRow(std::string& csvText);

	//void convertTargetsToNums(std::string& tableText); 
	std::vector< std::string> getDataRows(std::string& tableText);

	void loadDataRows(std::string& tableText);

	/*Called at the end of the object construction*/
	void determineColumnWidth(); 


	void normalizeFeatures();

	/*Adds a new column of data to features for "biasing"*/
	void addBias(); 

	void shuffle(); 

	friend class Classifier; 
};