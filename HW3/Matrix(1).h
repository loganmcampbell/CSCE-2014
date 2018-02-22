// Purpose: PF2 - Matrix class
// Author:  Logan Campbell
// Date:

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
template <typename T> class Matrix
{
  public:
    // Constructors / Destructors
    Matrix ();
    Matrix ( const int rows, const int cols );
    Matrix ( const Matrix<T>& orig );
    ~Matrix ();

    // Display
    void print () const;

    // Size modification
    void addRow ();
    void addCol ();
    void resize ( const int rows, const int cols );

    // Element access
    T getCell ( const int r, const int c ) const;
    void setCell ( const int r, const int c, const T& value );
    void fill ( const T& value );

    // Operator Access
    T& operator() ( const int r, const int c )
    {
        return mData[r * mCols + c];
    }
    const T& operator() ( const int r, const int c ) const
    {
        return mData[r * mCols + c];
    }

    // Statistics - Window [(r1, c1), (r2, c2)]
    T sum ( const int r1, const int c1, const int r2, const int c2 ) const;
    T product ( const int r1, const int c1, const int r2, const int c2 ) const;
    T max ( const int r1, const int c1, const int r2, const int c2 ) const;
    double mean ( const int r1, const int c1, const int r2, const int c2 ) const;

    // Statistics - Complete Matrix
    T sum () const;
    T product () const;
    T max () const;
    double mean () const;

    // Getters / Setters
    int getRows () const;
    int getCols () const;

  private:
    T* mData;
    int mRows, mCols;
};

template <typename T> Matrix<T>::Matrix ()
{
    // D E F A U L T     S T A T E
    mRows = 0;
    mCols = 0;
    mData = NULL;
}

template <typename T> Matrix<T>::Matrix ( const int rows, const int cols )
{
    // N O N      D E F A U L T      S T A T E
    mRows = rows;
    mCols = cols;
    if ( ( mRows != 0 ) && ( mCols != 0 ) )
    {
        T* arrayI = new T[mRows * mCols];

        if ( mData != NULL )
        {
            for ( int x = 0; x < ( mRows * mCols ); x++ )
            {
                arrayI[x] = mData[x];
                arrayI[x] = 0;
            }
        }
        mData = arrayI;
    }
    else
    {
        mData = NULL;
    }
}

template <typename T> Matrix<T>::Matrix ( const Matrix<T>& orig )
{
    // C O P Y       C O N S T R U C T O R
    mRows = 0;
    mCols = 0;
    mData = NULL;

    if ( orig.mRows > 0 && orig.mCols > 0 )
    {
        resize ( orig.mRows, orig.mCols );

        for ( int i = 0; i < mRows * mCols; ++i )
            mData[i] = orig.mData[i];
    }
}

template <typename T> Matrix<T>::~Matrix ()
{
    // D E C O N S T R U C T O R
    delete[] mData;
    mData = NULL;
}

template <typename T> void Matrix<T>::print () const
{
    // P R I N T    M A T R I X
    for ( int r = 0; r < mRows; ++r )
    {
        for ( int c = 0; c < mCols; ++c )
        {
            cout << setw ( 5 ) << mData[r * mCols + c] << " ";
        }
        cout << endl;
    }
}

template <typename T> void Matrix<T>::addRow ()
{
    // A D D  R O W   W I T H    R E S I Z E
    resize ( mRows + 1, mCols );
}

template <typename T> void Matrix<T>::addCol ()
{
    // A D D  C O L   W I T H    R E S I Z E
    resize ( mRows, mCols + 1 );
}

template <typename T> void Matrix<T>::resize ( const int rows, const int cols )
{
    // R E S I Z E : NEW  ARRAY : COPY DATA : DELETE : SET
    if ( rows == mRows && cols == mCols )
        return;

    T* data = new T[rows * cols]();

    for ( int r = 0; r < min ( rows, mRows ); ++r )
    {
        for ( int c = 0; c < min ( cols, mCols ); ++c )
        {
            data[r * cols + c] = mData[r * mCols + c];
        }
    }

    delete[] mData;
    mData = data;
    mRows = rows;
    mCols = cols;
}

template <typename T> T Matrix<T>::getCell ( const int r, const int c ) const
{
    // G E T C E L L : SET BOUND : R E T U R N   C E L L
    if ( ( r < mRows ) && ( c < mCols ) && ( r >= 0 ) && ( c >= 0 ) )
    {
        return mData[r * mCols + c];
    }
    else

        return 0;
}

template <typename T> void Matrix<T>::setCell ( const int r, const int c, const T& value )
{
    // S E T C E L L : C H E C K B O U N D : A S S I G N V A L U E
    if ( ( r < mRows ) && ( c < mCols ) && ( r >= 0 ) && ( c >= 0 ) )
    {
        mData[r * mCols + c] = value;
    }
    else
    {
        // Nothing.
    }
}

template <typename T> void Matrix<T>::fill ( const T& value )
{
    // F I L L : L O O P : F I L L
    for ( int f = 0; f < ( mRows * mCols ); f++ )
    {
        mData[f] = value;
    }
}

template <typename T> T Matrix<T>::sum ( const int r1, const int c1, const int r2, const int c2 ) const
{
    // S U M (WINDOW) : L O O P : C O L L E C T : R E T U R N
    if ( r1 >= 0 && c1 >= 0 && r2 >= 0 && c2 >= 0 )
    {
        T sum1;
        // L O O P : USE MIN TO END ON THE LAST INDEX OF THE WINDOW
        for ( int r = r1; r < min ( r2, mRows ); ++r )
        {
            for ( int c = c1; c < min ( c2, mCols ); ++c )
            {
                sum1 += mData[r * mCols + c];
            }
        }
        return sum1;
    }
    else
        return 0;
}

template <typename T> T Matrix<T>::product ( const int r1, const int c1, const int r2, const int c2 ) const
{
    // M U L T I P L Y  (WINDOW) : L O O P : C O L L E C T : R E T U R N
    T product1 = 1;
    // L O O P : USE MIN TO END ON THE LAST INDEX OF THE WINDOW
    for ( int r = r1; r < min ( r2, mRows ); r++ )
    {
        for ( int c = c1; c < min ( c2, mCols ); c++ )
        {
            product1 *= mData[r * mCols + c];
        }
    }

    return product1;
}

template <typename T> T Matrix<T>::max ( const int r1, const int c1, const int r2, const int c2 ) const
{
    // M A X (WINDOW) : L O O P : C O M P A R E : S E T : R E T U R N
    if ( r1 >= 0 && c1 >= 0 && r2 >= 0 && c2 >= 0 )
    {
        T max = 0;
        for ( int r = r1; r < min ( r2, mRows ); r++ )
        {
            for ( int c = c1; c < min ( c2, mCols ); c++ )
            {
                if ( mData[r * mCols + c] > max )
                    max = mData[r * mCols + c];
            }
        }

        return max;
    }
    else
        return 0;
}

template <typename T> double Matrix<T>::mean ( const int r1, const int c1, const int r2, const int c2 ) const
{
    // A V E R A G E  (WINDOW) : PARAMETERS : COUNT : CALL : RETURN
    if ( r1 >= 0 && c1 >= 0 && r2 >= 0 && c2 >= 0 )
    {
        int parameters = ( r1 * r2 + c1 * c2 ) - ( c1 * c2 - r1 * r2 );
        int count = 0;

        for ( int x = 0; x < parameters; x++ )
        {
            count = count + 1;
        }
        double average = 0.0;

        return average = sum ( r1, c1, r2, c2 ) / double( count );
    }

    else
        return 0;
}

template <typename T> T Matrix<T>::sum () const
{
    // SUM (ALL) : L O O P : C O L L E C T : R E T U R N
    int total = 0;
    for ( int x = 0; x < ( mRows * mCols ); x++ )
    {
        total += mData[x];
    }
    return total;
}

template <typename T> T Matrix<T>::product () const
{
    // M U L T I P L Y (ALL) : L O O P : C O L L E C T : R E T U R N
    int prod = 1;
    for ( int x = 0; x < ( mRows * mCols ); x++ )
    {
        prod *= mData[x];
    }
    return prod;
}

template <typename T> T Matrix<T>::max () const
{
    // M A X (ALL) : L O O P : C O M P A R E : R E T U R N
    int largest = 0;
    for ( int x = 0; x < ( mRows * mCols ); x++ )
    {
        if ( mData[x] > largest )
            largest = mData[x];
    }

    return largest;
}

template <typename T> double Matrix<T>::mean () const
{
    // A V E R A G E (ALL) : B O U N D S : C A L L : R E T U R N
    if ( ( mRows > 0 ) && ( mCols > 0 ) )
    {
        return sum () / (double)( mRows * mCols );
    }
    else
        return 0;
}

template <typename T> int Matrix<T>::getCols () const
{
    // G E T C O L U M N S : R E T U R N
    return mCols;
}

template <typename T> int Matrix<T>::getRows () const
{
    // G E T R O W S : R E T U R N
    return mRows;
}

#endif