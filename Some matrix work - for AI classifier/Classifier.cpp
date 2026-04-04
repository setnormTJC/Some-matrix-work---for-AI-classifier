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


	//weights.print(10); 

	//int colWidth = 10; 
	//weightMatrix.print(colWidth); 
}

void Classifier::train(float tolerance, float learningRate)
{
	int epoch = 0;
	int maxEpochs = 50'000;

	Matrix targets = dataset.getOneHotTargets(); // 150 x 3
	Matrix X = dataset.features;                  // 150 x numFeatures (last column can be bias)
	Matrix XT = X.getTranspose();                 // numFeatures x 150

	int numRows = X.dims().first;
	int numClasses = targets.dims().second;      // correct number of classes

	float loss = 10'000.0f;

	while (loss > tolerance && epoch < maxEpochs)
	{
		// 1. Compute logits
		Matrix logits = X * weights; // dims = numRows x numClasses

		// 2. Softmax row-wise
		for (int r = 0; r < numRows; ++r)
		{
			float maxLogit = *std::max_element(logits.data[r].begin(), logits.data[r].end());
			float sumExp = 0.0f;
			for (int c = 0; c < numClasses; ++c)
			{
				logits.data[r][c] = std::exp(logits.data[r][c] - maxLogit);
				sumExp += logits.data[r][c];
			}
			for (int c = 0; c < numClasses; ++c)
			{
				logits.data[r][c] /= sumExp;
			}
		}

		// 3. Gradient (softmax + cross-entropy)
		Matrix errors = logits - targets;               // 150 x 3
		Matrix gradient = (XT * errors) * (1.0f / numRows); // numFeatures x 3

		// 4. Update weights
		weights = weights - (gradient * learningRate);

		// 5. Compute cross-entropy loss (optional, for monitoring)
		loss = 0.0f;
		for (int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numClasses; ++c)
			{
				if (targets.data[r][c] > 0)
					loss -= targets.data[r][c] * std::log(logits.data[r][c] + 1e-8f);
			}
		}
		loss /= numRows;

		if (epoch % 1000 == 0)
		{
			std::cout << "Epoch " << epoch << " | Loss: " << loss << std::endl;
		}

		epoch++;
	}

	if (epoch >= maxEpochs)
	{
		std::cout << "Warning: Reached max epochs before reaching tolerance.\n";
	}
}
void Classifier::trainPoorly(float tolerance, float learningRate)
{
	int epoch = 0;
	int maxEpochs = 50'000; //don't go crazy if fails to converge

	float meanSquaredError = 10'000.0f; //over 9000...

	//while (!withinTolerance(tolerances, deltas))
	Matrix targets = dataset.getOneHotTargets(); //150 x 3
	Matrix transposedFeatures = dataset.features.getTranspose(); 
	
	//std::cout << "Row 0 (Setosa) one-hot: " << targets.data.at(0).at(0) << " " << targets.data.at(0).at(1)
	//	<< " " << targets.data.at(0).at(2) << "\n";

	//std::cout << "Row 05 (Versicolor) one-hot: " << targets.data.at(50).at(0) << " " << targets.data.at(50).at(1)
	//	<< " " << targets.data.at(50).at(2) << "\n";

	Matrix bias(targets.data.size(), targets.data.at(0).size()); //dims = 

	bias.randomize(); 

	dataset.targets.print(10);


	while(meanSquaredError > tolerance && epoch < maxEpochs)
	{
		Matrix predictions = (dataset.features * weights); //dims are 150 x 3
		predictions = predictions + bias; 

		int numRows = predictions.dims().first;
		int numClasses = predictions.dims().second;

		Matrix errors = predictions - targets;


		//Matrix gradient = transposedFeatures * errors;  
		Matrix gradient = (transposedFeatures * errors) * (1.0f / static_cast<float>(numRows));
		Matrix biasGradient = errors * (1.0f / numRows);
		
		bias = bias - (biasGradient * learningRate);

		//update weights: 
		/*weights = weights - (gradient * (learningRate/numRows));*/

		weights = weights - (gradient * learningRate);

		meanSquaredError = calculateMeanSquaredError(errors);  

		//std::cout << "Mean squared error so far is: " << meanSquaredError << "\n";
		//std::system("pause"); 

		if (epoch % 1000 == 0)
		{
			std::cout << "Weights[0][0]: " << weights.data[0][0] << " | Error: " << meanSquaredError << std::endl;
		}

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

float Classifier::test()
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
			std::cout << prediction.data.at(0).at(0) << " " << prediction.data.at(0).at(1) << " " << prediction.data.at(0).at(2) << "\n\n";
		}
	}

	float N = dataset.features.data.size();
	std::cout << "Number of incorrect predictions (of " << N << " ): " << incorrectPredictionCount << "\n";

	float accuracy = (N - incorrectPredictionCount) / N; 
	
	std::cout << "Accuracy: " << accuracy << "\n";

	return accuracy; 
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

	float meanSquaredError = squaredError / (numRows*numClasses);

	return meanSquaredError; 
}


