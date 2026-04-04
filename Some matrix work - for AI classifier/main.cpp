// Some matrix work - for AI classifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random> 
#include<string> 

#include"Classifier.h"

int main()
{

	std::vector<std::vector<float>> matrix =
	{
		{1.0f, 2.0f},
		{3.0f, 4.0f}, 
		{5.0f, 6.0f}
	};


	Matrix m(matrix);

	auto mT = m.getTranspose(); 

	/*A lil catalog*/
	const std::string IRIS_URL = "https://raw.githubusercontent.com/plotly/datasets/refs/heads/master/iris-data.csv";
	const std::string TITANIC_URL = "https://raw.githubusercontent.com/pandas-dev/pandas/master/doc/data/titanic.csv";
	const std::string WINE_URL = "https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data";

	//possible good resource: https://github.com/plotly/datasets/tree/master
	const std::string ANIMAL_SHELTER_URL = "https://raw.githubusercontent.com/plotly/datasets/refs/heads/master/Kaggle%20Austin%20Animal%20Shelter%20Outcomes.csv";


	Dataset dataset(IRIS_URL);

	Classifier classifier(dataset);

	float tolerance = 0.05f; 
	float learningRate = 1.0f; 
	
	float accuracy = 0.0f; 
	while (accuracy < 0.85f)
	{
		classifier.train(tolerance, learningRate);  

		accuracy = classifier.test(); 
	}


}
