#include "c_dokmatrix.h"
#include <iomanip>
#include <iostream>
C_DokMatrix::C_DokMatrix(int rows, int columns)
{
    M_Rows=rows;
    M_Columns=columns;
}
double C_DokMatrix::Get_Val(int row, int column) const
{
    if(DokMap.find(row)!=DokMap.end())
    {
        if(DokMap.at(row).find(column)!=DokMap.at(row).end())
        {
            return DokMap.at(row).at(column);
        }
    }
    return 0;
}
void C_DokMatrix::Set_Val(int row, int column, double value)
{
    if(value!=0)
    {
        DokMap[row][column]=value;
    }
    else if (DokMap.find(row)!= DokMap.end())
    {
        if(DokMap[row].find(column)!=DokMap[row].end() )
        {
            DokMap[row].erase(column);
        }

    }
}
void C_DokMatrix::Print(ostream & output) const
{

    for(int i = 1; i<=M_Rows; i++)
    {
        for(int j = 1; j<=M_Columns; j++)
        {
            if(DokMap.find(i)!=DokMap.end())
            {
                if(DokMap.at(i).find(j)!=DokMap.at(i).end())
                {
                    double val;
                    val =DokMap.at(i).at(j);
                    output<<" "<<setprecision(5)<<val;
                }
                else
                {
                    output<<" "<<0;
                }
            }
            else
            {
                output<<" "<<0;
            }
        }
        output<<endl;

    }
}
int C_DokMatrix::Get_Rows() const
{
    return M_Rows;
}
int C_DokMatrix::Get_Columns() const
{
    return M_Columns;
}
void C_DokMatrix::operator=(C_DokMatrix  in)
{
    DokMap.clear();
    M_Rows=in.M_Rows;
    M_Columns=in.M_Columns;
    DokMap.insert(in.DokMap.begin(),in.DokMap.end() );
}

///////
