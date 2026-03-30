// Some matrix work - for AI classifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string> 

#include "Matrix.h"



int main()
{

	Matrix matrix(5, 6);

	try
	{
		matrix.set(0, 0, 1.0f);
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

	matrix.print(); 



}
