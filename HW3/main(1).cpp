// Purpose: PF2 - Driver for Matrix class
// Name:    Jon C. Hammer
// Date:    6/24/17

#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
    // Default constructor
    cout << "Testing Default Constructor" << endl;
    Matrix<double> m1;
    cout << m1.getRows() << " " << m1.getCols() << endl;
    m1.print();
    cout << endl;
    
    // Non-default constructor
    cout << "Testing Non-default Constructor" << endl;
    Matrix<int> m2(4, 5);
    cout << m2.getRows() << " " << m2.getCols() << endl;
    m2.print();
    cout << endl;
    
    // fill()
    cout << "Testing fill()" << endl;
    m2.fill(5);
    m2.print();
    cout << endl;
    
    // setCell()
    cout << "Testing setCell()" << endl;
    for (int i = 0; i < m2.getRows(); ++i)
    {
        for (int j = 0; j < m2.getCols(); ++j)
        {
            m2.setCell(i, j, i - j);
        }
    }
    for (int i = 0; i < m2.getRows(); ++i)
        m2.setCell(i, i, (2 * i + 1));
    
    m2.setCell(0, 5, 32);
    m2.print();
    cout << endl;
    
    // getCell()
    cout << "Testing getCell()" << endl;
    cout << m2.getCell(3, 4)    << endl;
    cout << m2.getCell(-1, 0)   << endl;
    cout << m2.getCell(0, -1)   << endl;
    cout << m2.getCell(4, 3)    << endl;
    cout << m2.getCell(3, 5)    << endl;
    cout << endl;
    
    // Matrix Statistics
    cout << "Testing Matrix Statistics" << endl;
    cout << "Sum:     " << m2.sum()     << endl;
    cout << "Product: " << m2.product() << endl;
    cout << "Max:     " << m2.max()     << endl;
    cout << "Mean:    " << m2.mean()    << endl;
    cout << endl;
    
    // Resize()
    cout << "Testing resize()" << endl;
    m2.resize(6, 7);
    m2.print();
    cout << endl;
    
    // addRow() / addCol()
    cout << "Testing addRow() / addCol()" << endl;
    m2.addRow();
    m2.addCol();
    m2.print();
    cout << endl;
    
    // Window Statistics
    cout << "Testing Window Statistics" << endl;
    cout << "Sum:     " << m2.sum(2, 2, 5, 6)     << endl;
    cout << "Product: " << m2.product(2, 2, 5, 6) << endl;
    cout << "Max:     " << m2.max(2, 2, 5, 6)     << endl;
    cout << "Mean:    " << m2.mean(2, 2, 5, 6)    << endl;
    cout << endl;
    
    // Copy Constructor
    cout << "Testing Copy Constructor" << endl;
    Matrix<int> m3(m2);
    cout << " - Original: " << endl;
    m2.print();
    cout << endl;
    cout << " - Copy: " << endl;
    m3.print();
    cout << endl;
    cout << " - After Modification - Original: " << endl;
    m3(0, 0) = 87;
    m2.print();
    cout << endl;
    cout << " - After Modification - Copy: " << endl;
    m3.print();
    cout << endl;
        
    return 0;
}