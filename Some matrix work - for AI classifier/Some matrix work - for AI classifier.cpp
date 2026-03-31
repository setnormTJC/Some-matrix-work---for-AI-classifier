// Some matrix work - for AI classifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random> 
#include<string> 

#include "Matrix.h"



int main()
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
	const int maxDimension = 10; 
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
		a.print(); 

		int bj = aj; //required for matrix multiplication 
		int bk = dimensionDistribution(rng); 

		Matrix b(bj, bk);

		b.randomize(minMatrixValue, maxMatrixValue); 

		std::cout << "B is:\n";
		b.print(); 

		std::cout << "Side by side:\n";
		a.print(b); 

		std::cout << "Product is: \n";
		//a.set(0, 0, 1.0f);
		Matrix c = a * b; 

		c.print();
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}



}
