#include "c_standartmatrix.h"
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;
int C_StandartMatrix::Get_Rows() const
{
    return M_Rows;
}

int C_StandartMatrix::Get_Columns() const
{
    return M_Columns;
}
int C_StandartMatrix::Swap_Rows(int i, int j)
{
    double tmp;
    if(i==j || i<0 || j<0 || j>M_Rows || i>M_Rows)
    {
        return 1;
    }
    for (int k=1; k<M_Columns+1; k++)
    {
        tmp = Get_Val(i,k);
        Set_Val(i,k, Get_Val(j,k) );
        Set_Val(j,k,tmp);
    }
    return 0;
}
//adds c*j to i
int C_StandartMatrix::Add_Rows(int i, int j, double c)
{
    double tmp;
    if(i==j || i<0 || j<0 || j>M_Rows || i>M_Rows)
    {
        return 1;
    }
    for (int k=1; k<M_Columns+1; k++)
    {
        tmp = Get_Val(i,k);
        tmp = tmp +(c*(Get_Val(j,k)));
        Set_Val(i,k,tmp);
    }
    return 0;
}
int C_StandartMatrix::Mult_Row(int i, double c)
{

    double tmp;
    for (int k=1; k<M_Columns+1; k++)
    {
        tmp = Get_Val(i,k);
        tmp = c*tmp;
        Set_Val(i,k,tmp);
    }
    return 0;
}



C_StandartMatrix C_StandartMatrix::Gauss(bool commented, ostream & out)
{
    C_StandartMatrix matrix_g;
    matrix_g= *this;
    int rows=matrix_g.Get_Rows();
    int columns=matrix_g.Get_Columns();
    double maximum;
    int maxrow;
    bool ok;
    for(int i=1,j=1; i<=rows && j<=columns; i++,j++)
    {
        ok = false;
        while(!ok && j<=columns)

        {
            maximum = abs(matrix_g.Get_Val(i,j));
            maxrow= i;
            for(int k=i+1; k<=rows; k++)
            {
                if(abs(matrix_g.Get_Val(k,j))>maximum)
                {
                    maximum=  abs(matrix_g.Get_Val(k,j));
                    maxrow=k;
                }
            }
            if(maximum==0)
            {

                j++;



            }
            else
            {
                if(maxrow!=i)
                {
                    if(commented)
                    {
                        matrix_g.Print(out);
                        out<<"Prohazuji "<<maxrow<<" a "<< i<<endl;

                    }

                    matrix_g.Swap_Rows(maxrow,i);
                    if(commented)
                    {
                        matrix_g.Print(out);
                    }
                }

                ok=true;
            }

        }

        if(j>columns)
        {
            break;
        }
        double inverse = matrix_g.Get_Val(i,j);

        if(inverse!=0)
        {
            if(commented)
            {
                matrix_g.Print(out);
                out<<"Nasobim radek "<<i<<" cislem  "<<setprecision(5)<< 1/inverse<<endl;
            }
            matrix_g.Mult_Row(i,1/inverse);
            if(commented)
            {
                matrix_g.Print(out);
            }
        }
        for(int k=i+1; k<=rows; k++)
        {

            double moving = matrix_g.Get_Val(k,j);

            if(moving!=0)
            {
                if(commented)
                {
                    matrix_g.Print(out);
                    out<<"Odecitam od radku "<<k<<" pivot radek krat   "<<setprecision(5)<< -moving<<endl;
                }
                matrix_g.Add_Rows(k, i, -moving);
                if(commented)
                {
                    matrix_g.Print(out);
                }
            }
        }
    }
    matrix_g.Print(out);
    return matrix_g;

}
C_StandartMatrix C_StandartMatrix::Inverse()
{
    C_StandartMatrix matrix_g;

    matrix_g= *this;
    int rows=matrix_g.Get_Rows();
    int columns=matrix_g.Get_Columns();
    C_StandartMatrix inverse_M(rows,rows);
    for(int e = 1; e<=rows; e++)
    {
        inverse_M.Set_Val(e,e,1);
    }
    double maximum;
    int maxrow;
    bool ok;
    for(int i=1,j=1; i<=rows && j<=columns; i++,j++)
    {
        ok = false;
        while(!ok && j<=columns)
        {
            maximum = abs(matrix_g.Get_Val(i,j));
            maxrow= i;
            for(int k=i+1; k<=rows; k++)
            {
                if(abs(matrix_g.Get_Val(k,j))>maximum)
                {
                    maximum=  abs(matrix_g.Get_Val(k,j));
                    maxrow=k;
                }
            }
            if(maximum==0)
            {

                j++;



            }
            else
            {
                if(maxrow!=i)
                {

                    matrix_g.Swap_Rows(maxrow,i);
                    inverse_M.Swap_Rows(maxrow,i);

                }

                ok=true;
            }

        }

        if(j>columns)
        {
            break;
        }
        double inverse = matrix_g.Get_Val(i,j);

        if(inverse!=0)
        {

            matrix_g.Mult_Row(i,1/inverse);
            inverse_M.Mult_Row(i,1/inverse);

        }
        for(int k=i+1; k<=rows; k++)
        {

            double moving = matrix_g.Get_Val(k,j);

            if(moving!=0)
            {


                matrix_g.Add_Rows(k, i, -moving);
                inverse_M.Add_Rows(k, i, -moving);

            }
        }
    }

    for(int k=rows; k>0; k--)
    {
        double c = 1/matrix_g.Get_Val(k,k);
        matrix_g.Mult_Row(k,c);
        inverse_M.Mult_Row(k,c);
        for(int j=k-1; j>0; j--)
        {
            double d = -(matrix_g.Get_Val(j,k));
            matrix_g.Add_Rows(j,k,d);
            inverse_M.Add_Rows(j,k,d);
        }

    }
    return inverse_M;

}

double C_StandartMatrix::Det()
{
    C_StandartMatrix matrix_g;
    matrix_g= *this;
    int rows=matrix_g.Get_Rows();
    int columns=matrix_g.Get_Columns();
    double maximum;
    int maxrow;
    bool ok;
    double det_change=1;
    for(int i=1,j=1; i<=rows && j<=columns; i++,j++)
    {
        ok = false;
        while(!ok && j<=columns)
        {
            maximum = abs(matrix_g.Get_Val(i,j));
            maxrow= i;
            for(int k=i+1; k<=rows; k++)
            {
                if(abs(matrix_g.Get_Val(k,j))>maximum)
                {
                    maximum=  abs(matrix_g.Get_Val(k,j));
                    maxrow=k;
                }
            }
            if(maximum==0)
            {

                j++;



            }
            else
            {
                if(maxrow!=i)
                {

                    matrix_g.Swap_Rows(maxrow,i);
                    det_change= -det_change;

                }

                ok=true;
            }

        }

        if(j>columns)
        {
            break;
        }
        double inverse = matrix_g.Get_Val(i,j);

        if(inverse!=0)
        {

            matrix_g.Mult_Row(i,1/inverse);
            det_change*=inverse;

        }
        for(int k=i+1; k<=rows; k++)
        {

            double moving = matrix_g.Get_Val(k,j);

            if(moving!=0)
            {


                matrix_g.Add_Rows(k, i, -moving);

            }
        }
    }

    double product;
    for( int k=1; k<=rows; k++)
    {
        if(k==1)
        {
            product=matrix_g.Get_Val(k,k);
        }
        else
        {
            product*=matrix_g.Get_Val(k,k);
        }
    }
    return product*det_change;
}
void C_StandartMatrix::operator=(C_StandartMatrix  in)
{
    M_Rows=in.M_Rows;
    M_Columns=in.M_Columns;
    M_Array.clear();
    M_Array=in.M_Array;
}

C_StandartMatrix::C_StandartMatrix(int rows, int columns)
{

    M_Rows=rows;
    M_Columns=columns;
    for (int i =0; i<(rows*columns); i++)
    {
        M_Array.push_back(0);
    }

}
void C_StandartMatrix::Print(ostream & output) const
{
    output<<"------------------"<<endl;
    for(int i = 0; i<M_Rows*M_Columns; i++)
    {
        output<<" "<<setprecision(5)<<M_Array[i];
        if( (i+1)%M_Columns==0)
        {
            output<<endl;
        }
    }
}
void C_StandartMatrix::Set_Val(int row, int column, double value)
{
    int Array_Position =((row-1)*this->M_Columns) + column-1;
    if(row>M_Rows || column>M_Columns || row<0 || column<0)
    {
        return;
    }
    M_Array[Array_Position]=value;

}
double C_StandartMatrix::Get_Val(int row, int column) const
{
    int Array_Position =((row-1)*this->M_Columns) + column-1;
    return M_Array.at(Array_Position);
}
