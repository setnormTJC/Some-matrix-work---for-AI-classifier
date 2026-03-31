#pragma once

#include<vector> 

using table = std::vector<std::vector<float>>;

class Matrix
{
private: 
	
	table data; 

public: 
	Matrix() = delete;
	/*initializes all elements to 0.0
	* @param rowCount -> throws if <= 0
	*/
	Matrix(int rowCount, int columnCount);

	/*pass 'er in with an initializer list*/
	Matrix(table data); 

	/*@returns the number of rows and columns of the matrix*/
	std::pair<int, int> dims() const;

	/*
	* @param rowNum -> THROWS exception if rowNum > rowCount
	*/
	void set(int rowNum, int colNum, float newValue);

	void print(bool displayInScientificNotation = false) const;

	/*An overload that prints matrices side by side (for ease of visualization of multiplication, for example)*/
	void print(const Matrix& rhs) const; 

	/*fills the matrix with values between min and max (inclusive)*/
	void randomize(int min, int max); 

	/*
	* @param rhs -> throws if rhs.totalRows != this->totalColumns
	*/
	Matrix operator * (const Matrix& rhs) const; 

private: 
	int determineMaxDigitCount() const; 
};
