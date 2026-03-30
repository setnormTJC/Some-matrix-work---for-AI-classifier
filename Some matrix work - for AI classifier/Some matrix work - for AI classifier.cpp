// Some matrix work - for AI classifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


#include<string> 

#include "Matrix.h"


class Car
{
public: 

	int miles; 
	std::string makeName; //ex: Ford

	void printThis()
	{
		std::cout << "This is " << this << "\n";
	}


	/*What does 5 > 6 "evaluate to"? */
	bool operator > (Car rightHandSideCar)
	{
		if (this->miles > rightHandSideCar.miles)
		{
			return true; 
		}

		else
		{
			return false; 
		}
	}
};

int main()
{
	Car myCar = { 2'000, "Honda" };
	Car joesCar = { 90'000, "Subaru"};


	//myCar.printThis(); 

	//std::cout << "The ADDRESS OF myCar is: " << &myCar << "\n";

	//when the ampersand is used in this way (as a UNARY operator)
	// 
	// 
	
	if (myCar > joesCar)
	{
		std::cout << "My car has more miles on it than Joe's\n";
	}


	std::string firstName = "Seth"; 
	std::string lastName = "Norman"; 

	std::string fullName = firstName + lastName; 

	//Matrix m1(
	//	{ 1, 2 },
	//	{ 3, 4 }
	//);


	//Matrix m2(
	//	{ 5, 6 },
	//	{ 7, 8 }
	//);

	//m1* m2; 


	Matrix matrix(2, 3);

	try
	{
		matrix.set(0, 0, 1.0f);
	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}



}
