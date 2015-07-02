#include "c_matrix.h"
#include <map>
using namespace std;
/**
@brief Class implementing sparse matrix format Dictionary Of Keys.
*
*This class allows basic operations with a sparse matrix, using  map < int , map<int, double> > to store the nonzero values.
*Changes to the sparsity structure are efficient as is random access to the nonzero values. This format is good when sparsity structure is not known apriori.
*If the sparsity structure is known its better to choose format more suited for your problem.
*All the methods are to be called from wrapper where input is sanitized.
*/
class C_DokMatrix: public C_Matrix
{
public:
    /**
    Constructor of a sparse matrix you can specify how many rows and columns should the matrix have, default for both is 1.
    */
    C_DokMatrix(int rows=1, int columns=1);
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
    virtual void operator=(C_DokMatrix  in);
    /**
    Virtual method, gets the number of rows.
    */
    virtual int Get_Rows() const;
    /**
    Virtual method, gets the number of columns.
    */
    virtual int Get_Columns() const;
private:
    map < int , map<int, double> > DokMap;
    int M_Rows;
    int M_Columns;
};
