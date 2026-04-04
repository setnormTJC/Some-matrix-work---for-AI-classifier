#pragma once


#include"Dataset.h"

class Classifier
{
	Matrix weights; 
	Dataset dataset; 

	
	
public: 
	Classifier() = delete; 

	Classifier(const Dataset& dataset);

	/*Alters weightMatrix until its (matrix mult) product with dataset.features == dataset.targets +/- some tolerance*/
	void train(float tolerance = 0.1, float learningRate = 0.001f); 

	/*Gets to about 80% accuracy (which is evidently not particularly good for Iris)*/
	void trainPoorly(float tolerance = 0.1, float learningRate = 0.001f);

	/*@param index-> ex: if 0 is passed in, the data for the first Iris setosa (5.1,3.5,1.4,0.2) will be passed in */
	void test(int index); 


	/*An overload that tests ALL indices from the training set and returns accuracy*/
	float test(); 

private: 

	float calculateMeanSquaredError(const Matrix& errors) const;
};