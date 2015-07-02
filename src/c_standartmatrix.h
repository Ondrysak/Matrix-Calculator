using namespace std;
#include "c_matrix.h"
#include <vector>
/**
@brief Class implementing standart matrix format, where all values are stored equally.
This class allows basic operations with standart matrix and operations using gauss-jordan elimination.
All the methods are to be called from the wrapper where input is sanitized.
*/
class C_StandartMatrix: public C_Matrix
{
public:
    /**
    Constructor of a standart matrix you can specify how many rows and columns should the matrix have, default for both is 1.
    */
    C_StandartMatrix(int rows=1, int columns=1);
    /**
    Virtual method, gets the double value on the position in matrix specified by row and column integers.
    */
    virtual double Get_Val(int row, int column) const;
    /**
    Virtual method, sets the double value on the position in matrix specified by row and column integers.
    */
    virtual void Set_Val(int row, int column, double value);
    /**
    Virtual method, prints the matrix on a specified stream.
    */
    virtual void Print(ostream & output) const;
    /**
    Virtual operator=, works as you would expect, except it has no return value.
    */
    virtual void operator=(C_StandartMatrix  in);
    /**
    Virtual method returns number of rows.
    */
    virtual int Get_Rows() const;
    /**
    Virtual method returns number of columns.
    */
    virtual int Get_Columns() const;
    /**
        This method uses gaussian elimination to get the matrix to the echelon form, and than uses it to compute the determinant of the matrix.
        */

    double Det();
    /**
    This method implements Gaussian elimination eliminated matrix is returned.
    */
    C_StandartMatrix Gauss(bool commented, ostream & out);
    /**
    This method computes inverse matrix using gaussian elimination the inversion is returned. Careful, singular matrix doesnot have an inverse.
    */
    C_StandartMatrix Inverse();

private:
    vector<double> M_Array;
    int M_Rows;
    int M_Columns;
    /**
    This method swaps rows i and j in the matrix.
    */
    int Swap_Rows(int i, int j);
    /**
    This method adds row j*c to the row i.
    */
    int Add_Rows(int i, int j, double c);
    /**
    This method multiplies row i by c
    */
    int Mult_Row(int i, double c);

};
