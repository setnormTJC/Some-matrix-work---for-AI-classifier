#pragma once

#include<vector> 

using table = std::vector<std::vector<float>>;

class Matrix
{
private: 
	int totalRows;
	int totalColumns; 
	
	table data; 

public: 
	Matrix() = delete;
	/*initializes all elements to 0.0*/
	Matrix(int rowCount, int columnCount);

	/*pass 'er in with an initializer list*/
	Matrix(table data); 

	/*@returns the number of rows and columns of the matrix*/
	std::pair<int, int> dims() const;

	/*
	* @param rowNum -> THROWS exception if rowNum > rowCount
	*/
	void set(int rowNum, int colNum, float newValue);

	void print() const;

	Matrix& operator * (const Matrix& rhs) const; 

};
