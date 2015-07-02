#ifndef C_MATRIX_H
#define C_MATRIX_H
using namespace std;
#include <iostream>
/**
@brief Abstract class, to be inherited by classes for standart and sparse matrixes
This class has the essential methods, for working with any format of matrix.
*/
class C_Matrix
{
private:
    /**
    Variables in which number of rows and columns is stored.
    */
    int M_Rows, M_Columns;
public:
    /**
    Pure virtual method, returns number of rows.
    */
    virtual int Get_Rows() const =0;
    /**
    Pure virtual method, returns number of columns.
    */
    virtual int Get_Columns() const =0;
    /**
    Pure virtual method, returns double value on the position specified by row, column integers.
    */
    virtual double Get_Val(int row, int column) const =0;
    /**
    Pure virtual method, sets the double value on the position in matrix specified by row, columns integers.
    */
    virtual void Set_Val(int row, int column, double value)=0;
    /**
    Pure virtual method, prints the matrix to the specified
    */
    virtual void Print(ostream & output) const =0;
};
#endif /*C_MATRIX*/
