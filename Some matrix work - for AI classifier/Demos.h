#pragma once
#include <random>
#include "Matrix.h"
#include <iostream>
#include "Dataset.h"


/*Generates two matrices of random dimensions subject to the constraint that they are "multiplicable" (Aij -> Bjk)
* Also calculates the product and prints the product (this was a form of robustness testing in prep for AI classifier application)
*/
void demoRNGMatrices()
{
	//Matrix a({
//	{1.0f, 2.0f},
//	{3.0f, 4.0f}
//});

//Matrix b({
//	{5.0f, 6.0f, 7.0f},
//	{8.0f, 9.0f, 10.0f}
//});

	std::mt19937 rng(std::random_device{}());

	const int minDimension = 1;
	const int maxDimension = 1000;
	std::uniform_int_distribution<int> dimensionDistribution(minDimension, maxDimension);

	try
	{
		int ai = dimensionDistribution(rng);
		int aj = dimensionDistribution(rng);

		Matrix a(ai, aj);

		int minMatrixValue = 1;
		int maxMatrixValue = 100;

		a.randomize(minMatrixValue, maxMatrixValue);

		std::cout << "A is:\n";
		const int colWidth = 5; 

		a.print(colWidth);

		int bj = aj; //required for matrix multiplication 
		int bk = dimensionDistribution(rng);

		Matrix b(bj, bk);

		b.randomize(minMatrixValue, maxMatrixValue);

		std::cout << "B is:\n";
		b.print(colWidth);

		std::cout << "Side by side:\n";
		a.print(b);

		std::cout << "Product is: \n";
		//a.set(0, 0, 1.0f);
		Matrix c = a * b;

		c.print(colWidth);
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
}

/*Set a breakpoint and inspect the string `text`*/
void demoReadingURL_WithCPRLibrary()
{
	Dataset dataset("https://raw.githubusercontent.com/pandas-dev/pandas/master/doc/data/titanic.csv");
}