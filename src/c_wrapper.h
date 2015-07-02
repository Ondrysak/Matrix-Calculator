#include "c_dokmatrix.h"
#include "c_standartmatrix.h"
#include <map>
#include <iostream>
#include <string>

using namespace std;
/**
    @brief This class allows user to perform operations with matrixes and wraps the matrix classes in such a way, that its easier to implement any other format of storing the sparse matrixes while having the same functionality.
    You just have to change the class C_DokMatrix to implement its functions for your desired format, wrapper will stay fully functional if implemented right.
    Wrapper stores the matrixes in itself using map container with string keys and matrix values, every matrix has to have an unique name.
    */
class C_Wrapper
{
public:
    /**
    Constructor, you can specify the input and output stram to be used and maximal number of rows and columns.
    */
    C_Wrapper(ostream & output, istream & input, int maximal);
    /**
    Starts the UI of the calculator.
    */
    int Run();
    /**
    Read an integer in the specified range including minimal and maximal from the input specified in constructor.
    */
    int ReadInt(int minimal, int maximal) const;
    /**
    Reads a double from user from the input specified in constructor.
    */
    double ReadDoub() const;
    /**
    Lets the user create an empty matrix in a desired format.
    */
    C_Matrix * Input();
    /**
    Lets the user create standart matrix with a unique name and enter values for every row column pair.
    */
    int Input_Val();
    /**
    Lets the user print a matrix to the output stream specified in the constructor, as always user has to specify the matrix by its unique name.
    */
    int Output();
    /**
    Lets the user print all matrixes available to the output stream.
    */
    int Output_All();
    /**
    Allows saving matrix to a file in the path specified. The format is "rows columns val_1,1 val_1,2 ..... val_rows,columns"
    */
    int Save();
    /**
    Allows loading a matrix from a file in the path specified. The format is "rows columns val_1,1 val_1,2 ..... val_rows,columns"
    */
    int Load();
    /**
    Allows user to change one value in a matrix specified by its name.
    */
    int Change();
    /**
    Allows user to add two matrixes and save the result as another unique matrix.
    */
    int Add();
    /**
     Allows user to substract two matrixes and save the result as another unique matrix.
     */
    int Sub();
    /**
    Allows user to multiply two matrixes and save the result as another unique matrix.
    */
    int Mult();
    /**
    Allows to transpone a specified matrix and save the result as another unique matrix.
    */
    int Trans();
    /**
    Allows user to perform gaussian elimination on a specified matrix and save the result as another matrix.
    */
    int Elim();
    /**
    Allows user find the rank of a matrix specified.
    */
    int Rank();
    /**
    Allows user to find the deteminant of a matrix specified.
    */
    int Determ();
    /**
    Allows user to find inverse matrix of a matrix specified.
    */
    int Inverse();
    /**
    Allows user to delete a matrix.
    */
    int Delete();
private:
    /**
    Method to get a pointer to a matrix that already exists in the program.
    */
    C_Matrix * GetExisting();
    /**
    Method to get a string that is not already used in this instance of the program.
    */
    string GetNonExisting() const;
    ostream & out;
    istream & in;
    //max rows and columns
    int max_rc;
    map<string, C_StandartMatrix> StMap;
    map<string, C_DokMatrix> SparseMap;
};
