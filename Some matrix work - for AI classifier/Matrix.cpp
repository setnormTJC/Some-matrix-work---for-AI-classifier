#include "Matrix.h"


#include<iomanip>
#include<iostream> 
#include<random> 
#include<stdexcept>



Matrix::Matrix(int rowCount, int columnCount)
{
	//data.reserve;
	
	if (rowCount <= 0 || columnCount <= 0) throw std::runtime_error("Cannot have rowCount <= 0 or columnCount <= 0");

	data.resize(rowCount, std::vector<float>(columnCount)); 

	//for (int currRow = 0; currRow < rowCount; ++currRow)
	//{
	//	for (int currCol = 0; currCol < columnCount; ++currCol)
	//	{
	//		data[currRow][currCol] = 0.0f; //std::vector::resize takes care of this
	//	}
	//}
}

Matrix::Matrix(table data)
	:
	data(data)
{
}

std::pair<int, int> Matrix::dims() const
{
	//return std::pair<int, int>(totalRows, totalColumns);

	return std::pair<int, int>(data.size(), data.at(0).size());
}

void Matrix::set(int rowNum, int colNum, float newValue)
{
	if (rowNum >= data.size()) throw std::runtime_error("attempted to set row out of bounds");

	if (colNum >= data.at(0).size()) throw std::runtime_error("attempted to set column out of bounds");

	data[rowNum][colNum] = newValue; 
}

void Matrix::print(bool displayInScientificNotation) const
{
	int columnWidth{};

	if (displayInScientificNotation)
	{
		columnWidth = 5; 
	}

	else
	{
		int padding = 2; 
		columnWidth = determineMaxDigitCount() + padding;
	}



	std::cout << "Dimensions (rows x cols): " << data.size() << " x " << data.at(0).size() << "\n";
	for (int row = 0; row < data.size(); ++row)
	{
		for (int col = 0; col < data.at(0).size(); ++col)
		{
			std::cout << std::left << std::setw(columnWidth) << data[row][col]; 
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Matrix::print(const Matrix& rhs) const
{
	int padding = 2;
	
	int maxDigitCountLHS = determineMaxDigitCount();
	int maxDigitCountRHS = rhs.determineMaxDigitCount();
	

	for (int row = 0; row < data.size(); ++row)
	{
		for (int col = 0; col < data.at(0).size(); ++col)
		{
			std::cout << std::left << std::setw(maxDigitCountLHS + padding) << data[row][col]; 
		}

		if (row < rhs.data.size())
		{
			std::cout << " | ";
			for (int col = 0; col < rhs.data.at(0).size(); ++col)
			{
				std::cout << std::left << std::setw(maxDigitCountRHS + padding) << rhs.data[row][col];
			}
		}

		std::cout << "\n";
	}

	/*print remaining rows for RHS, if any*/
	if (data.size() < rhs.data.size())
	{
		int LHSWidth = (maxDigitCountLHS + padding)* data.at(0).size(); 
		for (int row = data.size(); row < rhs.data.size(); ++row)
		{
			std::cout << std::string(LHSWidth, ' ');
			std::cout << " | ";

			for (int col = 0; col < rhs.data.at(0).size(); ++col)
			{
				std::cout << std::left << std::setw(maxDigitCountRHS + padding) << rhs.data[row][col]; 
			}
			std::cout << "\n";
		}
	}
}

void Matrix::randomize(int min, int max)
{
	std::mt19937 rng(std::random_device{}());

	std::uniform_int_distribution<int> dist(min, max); 

	for (int row = 0; row < data.size(); ++row)
	{
		for (int col = 0; col < data.at(0).size(); ++col)
		{
			data[row][col] = dist(rng); 
		}
	}
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	/*Column count of LHS (this) must match row count of RHS*/
	if (this->data.at(0).size() != rhs.data.size()) throw std::runtime_error("columns of lefthand matrix do not match rows of righthand matrix");


	Matrix product(this->data.size(), rhs.data.at(0).size());
	//Suppose Matrix A ("this") has i rows and j columns. And Matrix B has dimensions j x k
	//Then the Matrix C = A x B has dims: i x k

	int opCount = 0; 

	/*O(i * j * k) complexity -> more commonly described as O(N^3)*/
	for (int i = 0; i < this->data.size(); ++i)
	{
		for (int j = 0; j < this->data.at(0).size(); ++j) //equivalently: j < rhs.totalColumns
		{
			for (int k = 0; k < rhs.data.at(0).size(); ++k)
			{
				float aij = this->data[i][j];  
				float bjk = rhs.data[j][k]; 

				product.data[i][k] += aij * bjk; 

				opCount++; 
			}
		}
	}

	return product; 

}

int Matrix::determineMaxDigitCount() const
{
	int maxDigitCount = 0; 
	for (int row = 0; row < data.size(); ++row)
	{
		for (int col = 0; col < data.at(0).size(); ++col)
		{
			float value = data[row][col]; //note the copy

			int currentDigitCount{};
			while (value > 1)
			{
				value = value / 10; 
				currentDigitCount++; 
			}

			if (currentDigitCount > maxDigitCount)
			{
				maxDigitCount = currentDigitCount;
			}
		}
	}

	return maxDigitCount; 
}

