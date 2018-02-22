// Purpose: PF2 - Matrix class
// Author:  [Your name here]
// Date:    [Enter date here]

// Header guards - Used to ensure this file doesn't get copied
// into the final executable multiple times. Generally, ALL
// header files should have guards around the content to guard
// against this possibility.
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
using namespace std;

// This class represents a generic resizable 2D matrix. It supports
// element access and several statistics calculations.
template <class T>
class Matrix
{
public:

    // Constructors / Destructors
    Matrix();
    Matrix(const int rows, const int cols);
    Matrix(const Matrix<T>& orig);
    ~Matrix();
    
    // Display
    void print() const;
    
    // Size modification
    void addRow();
    void addCol();
    void resize(const int rows, const int cols);
    
    // Element access
    T getCell(const int r, const int c) const;
    void setCell(const int r, const int c, const T& value);
    void fill(const T& value);
    
    // Operator Access
    T& operator()(const int r, const int c)             { return mData[r * mCols + c]; }
    const T& operator()(const int r, const int c) const { return mData[r * mCols + c]; }
    
    // Statistics - Window [(r1, c1), (r2, c2)]
    T sum(const int r1, const int c1, const int r2, const int c2)       const;
    T product(const int r1, const int c1, const int r2, const int c2)   const;
    T max(const int r1, const int c1, const int r2, const int c2)       const;
    double mean(const int r1, const int c1, const int r2, const int c2) const;
    
    // Statistics - Complete Matrix
    T sum()       const;
    T product()   const;
    T max()       const;
    double mean() const;
    
    // Getters / Setters
    int getRows() const;
    int getCols() const;
    
private:
    T* mData;
    int mRows, mCols;
};

// [Your implementations go here]

#endif