#include "Matrix.h"


#include<iomanip>
#include<iostream> 
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

void Matrix::print() const
{
	constexpr int COL_WIDTH = 5; 
	for (int row = 0; row < totalRows; ++row)
	{
		for (int col = 0; col < totalColumns; ++col)
		{
			std::cout << std::left << std::setw(COL_WIDTH) << data[row][col]; 
		}
		std::cout << "\n";
	}
}

Matrix& Matrix::operator*(const Matrix& rhs) const
{
	/*Column count of LHS (this) must match row count of RHS*/
	if (this->totalColumns != rhs.totalRows) throw std::runtime_error("columns of lefthand matrix do not match rows of righthand matrix");



}

