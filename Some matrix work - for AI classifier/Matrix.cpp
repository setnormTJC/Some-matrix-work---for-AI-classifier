#include "Matrix.h"

#include<stdexcept>

Matrix::Matrix(int rowCount, int columnCount)
	:
	totalRows(rowCount), totalColumns(columnCount)
{
	//data.reserve;
	
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
	return std::pair<int, int>(totalRows, totalColumns);
}

void Matrix::set(int rowNum, int colNum, float newValue)
{
	if (rowNum >= totalRows) throw std::runtime_error("attempted to set row out of bounds");

	if (colNum >= totalColumns) throw std::runtime_error("attempted to set column out of bounds");

	data[rowNum][colNum] = newValue; 
}

int Matrix::getLargestMagnitude() const
{
	int largestDigitCount{0}; //init to zero

	for (int row = 0; row < totalRows; ++row)
	{
		for (int col = 0; col < totalColumns; ++col)
		{
			float currentValue = data[row][col]; //note that a COPY is made here (don't modify the goods)

			while (currentValue > 0)
			{
				currentValue = currentValue / 10; //shorter alt: currentValue /= 10;
				largestDigitCount++; 
			}
		}
	}

	return largestDigitCount;
}
