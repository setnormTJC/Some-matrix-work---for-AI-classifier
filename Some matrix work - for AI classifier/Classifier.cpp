#include "Classifier.h"
#include <iostream>

Classifier::Classifier(const Dataset& dataset)
	:
	weights(0, 0), //dummy temp dimensions
	dataset(dataset)
{
	int numberOfFeatures = dataset.featureNames.size(); 
	int numberOfOutputs = dataset.targetsToNums.size(); 

	weights = Matrix(numberOfFeatures, numberOfOutputs); //reassign the weightMatrix with proper dims

	weights.randomize();

	//int colWidth = 10; 
	//weightMatrix.print(colWidth); 
}

void Classifier::train(float tolerance, float learningRate)
{
	int epoch = 0;
	int maxEpochs = 50'000; //don't go crazy if fails to converge

	float meanSquaredError = 10'000.0f; //over 9000...

	//while (!withinTolerance(tolerances, deltas))
	Matrix targets = dataset.getOneHotTargets(); //150 x 3
	Matrix transposedFeatures = dataset.features.getTranspose(); 
	
	while(meanSquaredError > tolerance && epoch < maxEpochs)
	{
		Matrix predictions = dataset.features * weights; //dims are 150 x 3

		int numRows = predictions.dims().first;
		int numClasses = predictions.dims().second;

		Matrix errors = predictions - targets;


		Matrix gradient = transposedFeatures * errors;  

		//update weights: 
		weights = weights - (gradient * (learningRate/numRows));

		meanSquaredError = calculateMeanSquaredError(errors);  

		//std::cout << "Mean squared error so far is: " << meanSquaredError << "\n";
		//std::system("pause"); 

		epoch++; 
	}

	if (epoch >= maxEpochs) 
	{
		std::cout << "Warning: Reached max epochs before reaching tolerance.\n";
	}

}

void Classifier::test(int index)
{
	Matrix testFeatures =
	{
		{dataset.features.data.at(index)}
	};

	Matrix prediction = testFeatures * weights; 

	int colWidth = 10; 

	prediction.print(colWidth);
}

void Classifier::test()
{
	int numRows = dataset.features.dims().first; 


	auto originalTargets = dataset.getOriginalTargets(); 

	auto numsToTargets = dataset.getNumsToTargets(); 

	int incorrectPredictionCount = 0; 
	
	for (int row = 0; row < numRows; ++row)
	{
		Matrix testFeatures =
		{
			{dataset.features.data.at(row)}
		};

		Matrix prediction = testFeatures * weights;

		//find index with max "score": 
		auto it = std::max_element(prediction.data.at(0).begin(), prediction.data.at(0).end());

		int indexOfMaxScore = std::distance(prediction.data.at(0).begin(), it);

		//compare to what it should be

		auto predictedTarget = numsToTargets.at(indexOfMaxScore); 
		auto actualTarget = originalTargets.at(row);

		if (predictedTarget != actualTarget)
		{
			incorrectPredictionCount++; 
			std::cout << "Actual was: " << actualTarget << ", but predicted: " << predictedTarget << "\n";
		}
	}
	std::cout << "Number of incorrect predictions (of " << dataset.features.data.size() << " ): " << incorrectPredictionCount << "\n";
}

float Classifier::calculateMeanSquaredError(const Matrix& errors) const
{
	float squaredError = 0.0f;

	int numRows = errors.dims().first; 
	int numClasses = errors.dims().second; 

	for (int row = 0; row < numRows; ++row)
	{
		for (int col = 0; col < numClasses; ++col)
		{
			squaredError += errors.data[row][col] * errors.data[row][col];
		}
	}

	float meanSquaredError = squaredError / numRows;

	return meanSquaredError; 
}


