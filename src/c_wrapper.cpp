#include "c_wrapper.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <limits>
#include <iostream>
#include <iomanip>
using namespace std;
string C_Wrapper::GetNonExisting() const
{
    string user_input;
    in>>user_input;
    ///We ask user to enter a matrix id until he enters one that is not already used.
    while(StMap.find(user_input)!= StMap.end() ||  SparseMap.find(user_input)!= SparseMap.end())
    {
        out<<"Matice s timto jmenem uz existuje, zadejte jine jmeno:";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        in>>user_input;
    }
    return user_input;
}
C_Wrapper::C_Wrapper(ostream & output, istream & input, int maximal):out(output), in(input), max_rc(maximal)
{

}
int C_Wrapper::ReadInt(int minimal, int maximal) const
{
    int num;
    bool ok = false;
    while(!ok)
    {
        ///If the int is read succesfully
        if(in>>num)
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            ///We check if it is in the desired range
            if(!(num<minimal || num>maximal))
            {
                ///the number is in the desired range we set ok to true and the while cycle ends;
                ok=true;
            }
            else
            {
                out<<"Spatne zadane cislo!"<<endl;
                out<<"Zadejte cislo ktere je validni:";
            }
        }
        else
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            out<<"Tohle ani neni cislo!"<<endl;
            out<<"Zadejte cislo ktere je validni:";
        }

    }
    return num;
}
double C_Wrapper::ReadDoub() const
{
    double num;
    bool ok = false;
    ///Very similar to the way the int was read, only difference is that we are now trying to read a double
    while(!ok)
    {

        if(in>>num)
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            ok=true;
        }
        else
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            out<<"Tohle ani neni cislo!"<<endl;
            out<<"Zadejte cislo ktere je validni:";
        }

    }
    return num;
}
int C_Wrapper::Run()
{
    out<<"Vitejte v Matrix Calculator 1.0"<<endl;
    out<<"Upozorneni! K reprezentaci hodnot v matici se pouziva datovy typ double, muze tedy pri nekterych operacich dojit ke ztrate presnosti!"<<endl;
    out<<"Jedna se predevsim o operace vyuzivajici Gaussovu eliminacni metodu, tedy urceni hodnosti, determinantu, inverzni matice a samozrejme eliminaci samotnou!"<<endl;
    bool end= false;
    int num;
    while(!end)
    {
        out<<"==========================================="<<endl;
        out<<"Co chcete provest?"<<endl;
        out<<"1. Zalozit matici"<<endl;
        out<<"2. Zalozit matici a zadat hodnoty"<<endl;
        out<<"3. Smazat matici"<<endl;
        out<<"4. Nacist matici ze souboru"<<endl;
        out<<"5. Ulozit matici do souboru"<<endl;
        out<<"6. Vypsat matici"<<endl;
        out<<"7. Zmenit prvek matice"<<endl;
        out<<"8. Secist dve matice"<<endl;
        out<<"9. Odecist dve matice"<<endl;
        out<<"10. Vynasobit matice"<<endl;
        out<<"11. Gaussova eliminace na matici"<<endl;
        out<<"12. Zjistit hodnost matice"<<endl;
        out<<"13. Zjistit determinant matice"<<endl;
        out<<"14. Transponovat matici"<<endl;
        out<<"15. Nalezt inverzni matici"<<endl;
        out<<"16. Vypsat vsechny dostupne matice"<<endl;
        out<<"17. Ukoncit"<<endl;
        out<<"Zadejte cislo prikazu ktery se ma provest:";
        num=ReadInt(1,17);
        ///Checking what option user chose.
        if(num==1)
        {
            this->Input();

        }
        if(num==2)
        {
            this->Input_Val();
        }
        if(num==3)
        {
            this->Delete();
        }
        if(num==4)
        {
            this->Load();

        }
        if(num==5)
        {
            this->Save();
        }
        if(num==6)
        {
            this->Output();

        }
        if(num==7)
        {
            this->Change();

        }
        if(num==8)
        {
            this->Add();

        }
        if(num==9)
        {
            this->Sub();

        }
        if(num==10)
        {
            this->Mult();


        }
        if(num==11)
        {
            this->Elim();

        }
        if(num==12)
        {
            this->Rank();

        }
        if(num==13)
        {
            this->Determ();

        }
        if(num==14)
        {
            this->Trans();

        }
        if(num==15)
        {
            this->Inverse();

        }
        if(num==16)
        {
            this->Output_All();

        }
        if(num==17)
        {
            out<<"Dekuji, ze jste pouzili Matrix Calculator!"<<endl;
            end = true;

        }

    }
    return 0;
}
C_Matrix * C_Wrapper::Input()
{
    string user_input;
    C_Matrix * returning;
    int rows,columns,user_opt;
    out<<"1. Pouzit standartni format"<<endl;
    out<<"2. Pouzit dok format"<<endl;
    out<<"Ktery format chcete pro ulozeni pouzit:";
    user_opt=ReadInt(1,2);
    if(user_opt==1)
    {
        out<<"Zadejte jmeno pod kterym chcete matici ulozit:";
        user_input=GetNonExisting();
        out<<"Zadejte pozadovany pocet radek matice:";
        rows=ReadInt(1,max_rc);
        out<<"Zadejte pozadovany pocet sloupcu matice:";
        columns=ReadInt(1,max_rc);
        C_StandartMatrix nova(rows, columns);
        StMap[user_input]=nova;
        out<<"Matice "<<user_input<<" zalozena a inicializovana nulami!"<<endl;
        returning  = &StMap[user_input];
    }
    if(user_opt==2)
    {
        out<<"Zadejte jmeno pod kterym chcete matici ulozit:";
        user_input=GetNonExisting();
        out<<"Zadejte pozadovany pocet radek matice:";
        rows=ReadInt(1,max_rc);
        out<<"Zadejte pozadovany pocet sloupcu matice:";
        columns=ReadInt(1,max_rc);
        C_DokMatrix nova(rows, columns);
        SparseMap[user_input]=nova;
        out<<"Matice "<<user_input<<" zalozena a inicializovana nulami!"<<endl;
        returning  = &SparseMap[user_input];
    }
    ///We return pointer to the matrix we inicialized
    return returning;
}
C_Matrix * C_Wrapper::GetExisting()
{
    string user_input;
    C_Matrix * returning;
    in>>user_input;
    int i = 0;
    /// Reading strings from user until we get a string that matches a matrix that already exist
    while(StMap.find(user_input)== StMap.end() && SparseMap.find(user_input)== SparseMap.end())
    {
        if(i>3)
        {
            out<<"Dostupne jsou pouze matice s temito jmeny!"<<endl;
            for(auto it= StMap.begin(); it!=StMap.end(); it++)
            {
                out<<it->first<<endl;
            }
            for(auto it= SparseMap.begin(); it!=SparseMap.end(); it++)
            {
                out<<it->first<<endl;
            }
        }
        out<<"Matice s timto jmenem neexistuje, zadejte jine jmeno:";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        i++;

        in>>user_input;
    }
    if(StMap.find(user_input)!= StMap.end())
    {
        returning  = &StMap.at(user_input);
    }
    else
    {
        returning  = &SparseMap.at(user_input);
    }
    ///we return pointer to the matrix we got from user
    return returning;
}
int C_Wrapper::Input_Val()
{
    C_Matrix * matrix_pointer;
    ///we use Input method to incialize the matrix
    matrix_pointer = Input();
    int rows, columns;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    for(int i = 1; i<=rows; i++)
    {
        for(int j = 1; j<=columns; j++)
        {
            double val;
            out<<"zadejte hodnotu prvku "<<i<<","<<j<<":";
            val =  ReadDoub();
            matrix_pointer->Set_Val(i,j,val);

        }

    }
    return 0;
}
int C_Wrapper::Output()
{
    C_Matrix * matrix_pointer;
    out<<"Zadejte jmeno matice kterou chcete vypsat:";
    matrix_pointer = GetExisting();
    matrix_pointer->Print(out);
    return 0;
}
int C_Wrapper::Output_All()
{
    out<<"Dostupne standartni matice:"<<endl;
    for(auto it= StMap.begin(); it!=StMap.end(); it++)
    {
        out<<it->first<<" "<<(it->second).Get_Rows()<<"x"<<(it->second).Get_Columns()<<endl;
    }
    out<<"Dostupne DOK matice:"<<endl;
    for(auto it= SparseMap.begin(); it!=SparseMap.end(); it++)
    {
        out<<it->first<<" "<<(it->second).Get_Rows()<<"x"<<(it->second).Get_Columns()<<endl;
    }
    return 0;
}
int C_Wrapper::Save()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix * matrix_pointer;
    out<<"Zadejte jmeno matice kterou chcete ulozit do souboru:";
    matrix_pointer = GetExisting();
    int rows, columns;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    ofstream myfile;
    string user_input;
    out<<"Zadejte jmeno souboru do ktereho chcete matici ulozit:";
    in>>user_input;

    myfile.open (user_input, ios::trunc);
    if( !(myfile.is_open()) )
    {
        out<<"Soubor se nepodarilo otevrit!"<<endl;
    }
    myfile<<rows<<" "<<columns<<" ";
    for(int i = 1; i<=rows; i++ )
    {
        for(int j =1 ; j<=columns; j++)
        {
            double val;
            val = matrix_pointer->Get_Val(i,j);
            myfile<<setprecision(numeric_limits<double>::digits10)<<val<<" ";
        }

    }
    myfile.close();
    return 0;
}
int C_Wrapper::Load()
{

    string user_input;
    out<<"Zadejte jmeno souboru ze ktereho chcete matici nacist:";
    in>>user_input;
    ifstream myfile;
    myfile.open(user_input);
    int rows, columns;
    if( !(myfile>>rows && myfile>>columns) )
    {

    }
    if(rows<1 || columns <1 || rows>max_rc || columns>max_rc)
    {
        out<<"Soubor ma spatny format nebo neexistuje!"<<endl;
        return 1;
    }
    int user_opt;
    out<<"1. Pouzit standartni format"<<endl;
    out<<"2. Pouzit dok format"<<endl;
    out<<"Ktery format chcete pro ulozeni pouzit:";
    user_opt=ReadInt(1,2);
    if(user_opt==1)
    {
        C_StandartMatrix temp(rows,columns);
        for(int i = 1; i<=rows; i++ )
        {
            for(int j =1 ; j<=columns; j++)
            {
                double val;
                if(myfile>>val)
                {
                    temp.Set_Val(i,j,val);
                }
                else
                {
                    out<<"Soubor ma spatny format nebo neexistuje!"<<endl;
                    return 1;
                }
            }

        }
        myfile.close();
        out<<"Zadejte pod kterym jmenem chcete matici ulozit:";
        string user_input_2;
        user_input_2=GetNonExisting();
        StMap[user_input_2]= temp;
        temp.Print(out);
    }
    if(user_opt==2)
    {
        C_DokMatrix temp(rows,columns);
        for(int i = 1; i<=rows; i++ )
        {
            for(int j =1 ; j<=columns; j++)
            {
                double val;
                if(myfile>>val)
                {
                    temp.Set_Val(i,j,val);
                }
                else
                {
                    out<<"Soubor ma spatny format nebo neexistuje!"<<endl;
                    return 1;
                }
            }

        }
        myfile.close();
        out<<"Zadejte pod kterym jmenem chcete matici ulozit:";
        string user_input_2;
        user_input_2=GetNonExisting();
        SparseMap[user_input_2]= temp;
        temp.Print(out);
    }
    return 0;
}
int C_Wrapper::Determ()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix * matrix_pointer;
    out<<"Zadejte jmeno matice pro kterou chcete zjistit determinant:";
    matrix_pointer = GetExisting();
    if(matrix_pointer->Get_Columns()!=matrix_pointer->Get_Rows())
    {
        out<<"Determinant lze definovat pouze na ctvercove matici!"<<endl;
    }
    else
    {
        int rows, columns;
        rows = matrix_pointer->Get_Rows();
        columns = matrix_pointer->Get_Columns();
        C_StandartMatrix temp(rows,columns);
        for(int i = 1; i<=rows; i++)
        {
            for(int j = 1; j<=columns; j++)
            {

                temp.Set_Val(i,j, matrix_pointer->Get_Val(i,j));

            }

        }
        /// Using Det method of the standart matrix class
        out<<"Matice ma determinant "<<temp.Det()<<" !"<<endl;
    }
    return 0;
}

int C_Wrapper::Change()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix * matrix_pointer;
    out<<"Zadejte jmeno matice kterou chcete zmenit:";
    matrix_pointer = GetExisting();
    int rows, columns,user_row,user_col;
    double user_val;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    out<<"Matice "<<rows<<"x"<<columns<<"!"<<endl;
    matrix_pointer->Print(out);
    out<<"Ktery radek:";
    user_row=ReadInt(1,rows);
    out<<endl;
    out<<"Ktery sloupec:";
    user_col=ReadInt(1,columns);
    out<<endl;
    out<<"Hodnota:";
    user_val=ReadDoub();
    /// using set_val method to modify the matrix
    matrix_pointer->Set_Val(user_row,user_col,user_val);
    matrix_pointer->Print(out);
    return 0;


}
int C_Wrapper::Add()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    string user_input_A,user_input_B;
    out<<"Tato volba umoznuje provest s maticemi operaci A+B=C! Zadejte jmeno matice A:";
    C_Matrix * matrix_pointer_A;
    C_Matrix * matrix_pointer_B;
    matrix_pointer_A = GetExisting();
    out<<"Zadejte jmeno matice B:";
    matrix_pointer_B = GetExisting();

    int A_Rows,A_Cols,B_Rows,B_Cols;
    A_Rows = matrix_pointer_A->Get_Rows();
    A_Cols = matrix_pointer_A->Get_Columns();
    B_Rows = matrix_pointer_B->Get_Rows();
    B_Cols = matrix_pointer_B->Get_Columns();
    string user_input_C;
    if(A_Rows==B_Rows && A_Cols==B_Cols)
    {
        out<<"Matice maji shodne rozmery, zadejte jmeno matice C:";
        user_input_C=GetNonExisting();

    }
    else
    {
        out<<"Matice nemaji shodne rozmery, secteni nelze provest!"<<endl;
        return 1;
    }
    C_StandartMatrix temp(A_Rows,A_Cols);
    for(int i = 1; i<=A_Rows; i++)
    {
        for(int j = 1; j<=A_Cols; j++)
        {
            ///Constructing the matrix which is sum of the two specified
            double val;
            val =  matrix_pointer_A->Get_Val(i,j)+matrix_pointer_B->Get_Val(i,j);
            temp.Set_Val(i,j,val);

        }

    }
    StMap[user_input_C] = temp;
    temp.Print(out);
    out<<"Matice C=A+B se jmenem "<<user_input_C<<" je nyni k dispozici!"<<endl;
    return 0;
}
int C_Wrapper::Sub()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    string user_input_A,user_input_B;
    out<<"Tato volba umoznuje provest s maticemi operaci A+B=C! Zadejte jmeno matice A:";
    C_Matrix * matrix_pointer_A;
    C_Matrix * matrix_pointer_B;
    matrix_pointer_A = GetExisting();
    out<<"Zadejte jmeno matice B:";
    matrix_pointer_B = GetExisting();

    int A_Rows,A_Cols,B_Rows,B_Cols;
    A_Rows = matrix_pointer_A->Get_Rows();
    A_Cols = matrix_pointer_A->Get_Columns();
    B_Rows = matrix_pointer_B->Get_Rows();
    B_Cols = matrix_pointer_B->Get_Columns();
    string user_input_C;
    if(A_Rows==B_Rows && A_Cols==B_Cols)
    {
        out<<"Matice maji shodne rozmery, zadejte jmeno matice C:";
        user_input_C=GetNonExisting();

    }
    else
    {
        out<<"Matice nemaji shodne rozmery, odecteni nelze provest!"<<endl;
        return 1;
    }
    C_StandartMatrix temp(A_Rows,A_Cols);
    for(int i = 1; i<=A_Rows; i++)
    {
        for(int j = 1; j<=A_Cols; j++)
        {
            ///Constructing the matrix which is difference of the two specified
            double val;
            val =  matrix_pointer_A->Get_Val(i,j)-matrix_pointer_B->Get_Val(i,j);
            temp.Set_Val(i,j,val);

        }

    }

    StMap[user_input_C] = temp;
    temp.Print(out);
    out<<"Matice C=A-B se jmenem "<<user_input_C<<" je nyni k dispozici!"<<endl;
    return 0;
}
int C_Wrapper::Trans()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix * matrix_pointer;
    out<<"Zadejte jmeno matice kterou chcete transponovat:";
    matrix_pointer = GetExisting();
    string user_input_B;
    out<<"Zadejte jmeno pod kterym chcete transponovanou matici ulozit:";
    user_input_B=GetNonExisting();
    int rows, columns;
    rows=matrix_pointer->Get_Rows();
    columns=matrix_pointer->Get_Columns();
    C_StandartMatrix temp(columns, rows);
    for(int i = 1; i<=rows; i++)
    {
        for(int j = 1; j<=columns; j++)
        {
            ///constructing the matrix so its the transposition of the matrix specified
            double val;
            val =  matrix_pointer->Get_Val(i,j);
            temp.Set_Val(j,i,val);

        }

    }
    temp.Print(out);
    out<<"Transponovana matice se jmenem "<<user_input_B<<" je nyni k dispozici!"<<endl;
    StMap[user_input_B]= temp;
    return 0;

}
int C_Wrapper::Elim()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix *  matrix_pointer;
    out<<"Zadejte jmeno matice kterou chcete zeliminovat:";
    matrix_pointer = GetExisting();
    int rows, columns;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    ///Temp standart matrix which has gauss elimination implemented
    C_StandartMatrix temp(rows,columns);
    for(int i = 1; i<=rows; i++)
    {
        for(int j = 1; j<=columns; j++)
        {

            temp.Set_Val(i,j, matrix_pointer->Get_Val(i,j));

        }

    }
    string user_input_B;
    out<<"Zadejte jmeno pod kterym chcete zeliminovanou matici ulozit:";
    user_input_B=GetNonExisting();
    out<<"Pokud chcete videt kroky eliminace zadejte 1, pokud ne zadejte 2:";
    int commented;
    commented=ReadInt(1,2);
    C_StandartMatrix elimini;
    if(commented==1)
    {
        elimini = temp.Gauss(true,out);
    }
    else
    {
        elimini = temp.Gauss(false,out);
    }
    out<<"Eliminovana matice se jmenem "<<user_input_B<<" je nyni k dispozici!"<<endl;
    StMap[user_input_B]= elimini;
    return 0;
}

int C_Wrapper::Rank()
{

    out<<"Zadejte jmeno matice pro kterou chcete zjistit hodnost:";
    C_Matrix *  matrix_pointer;
    matrix_pointer = GetExisting();
    int rows, columns;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    C_StandartMatrix temp(rows,columns);
    for(int i = 1; i<=rows; i++)
    {
        for(int j = 1; j<=columns; j++)
        {

            temp.Set_Val(i,j, matrix_pointer->Get_Val(i,j));

        }

    }
    C_StandartMatrix elimini;
    elimini = temp.Gauss(false,out);
    rows=elimini.Get_Rows();
    columns=elimini.Get_Columns();
    int zero_rows=0;
    for(int i = 1; i<=rows; i++)
    {
        bool is_zero = true;
        for(int j = 1; j<=columns; j++)
        {
            if(elimini.Get_Val(i,j)!=0)
            {
                is_zero=false;
            }
        }
        if(is_zero==true)
        {
            zero_rows++;
        }
    }
    int matrix_rank = rows-zero_rows;
    out<<"Tato matice ma hodnost "<<matrix_rank<<"!"<<endl;
    return 0;
}
int C_Wrapper::Inverse()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    C_Matrix *  matrix_pointer;
    out<<"Zadejte jmeno matice pro kterou chcete nalezt inverzi:";
    matrix_pointer = GetExisting();
    int rows, columns;
    rows = matrix_pointer->Get_Rows();
    columns = matrix_pointer->Get_Columns();
    if(rows!=columns)
    {
        out<<"Takova matice nema inverzi, neni ctvercova!"<<endl;
        return 1;
    }
    C_StandartMatrix temp(rows,columns);
    for(int i = 1; i<=rows; i++)
    {
        for(int j = 1; j<=columns; j++)
        {

            temp.Set_Val(i,j, matrix_pointer->Get_Val(i,j));

        }

    }
    if(temp.Det()==0)
    {
        out<<"Takova matice nema inverzi, neni regularni!"<<endl;
        return 1;

    }
    string user_input_B;
    out<<"Zadejte jmeno pod kterym chcete inverzni matici ulozit:";
    user_input_B=GetNonExisting();
    C_StandartMatrix inverse_M;
    inverse_M = temp.Inverse();
    inverse_M.Print(out);
    out<<"Inverzni matice se jmenem"<<user_input_B<<" je nyni k dispozici!"<<endl;
    StMap[user_input_B]= inverse_M;
    return 0;
}

int C_Wrapper::Mult()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    string user_input_A,user_input_B;
    out<<"Tato volba umoznuje provest s maticemi operaci AB=C! Zadejte jmeno matice A:";
    C_Matrix * matrix_pointer_A;
    C_Matrix * matrix_pointer_B;
    matrix_pointer_A = GetExisting();
    out<<"Zadejte jmeno matice B:";
    matrix_pointer_B = GetExisting();

    int A_Rows,A_Cols,B_Rows,B_Cols;
    A_Rows = matrix_pointer_A->Get_Rows();
    A_Cols = matrix_pointer_A->Get_Columns();
    B_Rows = matrix_pointer_B->Get_Rows();
    B_Cols = matrix_pointer_B->Get_Columns();
    string user_input_C;
    if(A_Cols==B_Rows)
    {
        out<<"Matice maji odpovidajici rozmery, zadejte jmeno matice C:";
        user_input_C=GetNonExisting();

    }
    else
    {
        out<<"Matice nemaji odpovidajici rozmery, pro matice UxJ  a IxK musi platit J==I pro nasobeni (UxJ)(IxK), nasobeni matic neni komutativni!"<<endl;
        return 1;
    }
    C_StandartMatrix temp(A_Rows,B_Cols);
    for(int i = 1; i<=A_Rows; i++)
    {
        for(int j = 1; j<=B_Cols; j++)
        {
            double val;
            val = 0;
            for(int k=1; k<=A_Cols; k++)
            {

                val+=matrix_pointer_A->Get_Val(i,k)*matrix_pointer_B->Get_Val(k,j);
            }
            temp.Set_Val(i,j,val);
        }

    }

    StMap[user_input_C] = temp;
    temp.Print(out);
    out<<"Matice C=AB se jmenem "<<user_input_C<<" je nyni k dispozici!"<<endl;
    return 0;
}
int C_Wrapper::Delete()
{
    if(StMap.empty() && SparseMap.empty())
    {
        out<<"Nejdrive zalozte nejake matice!"<<endl;
        return 1;
    }
    string user_input;
    out<<"Zadejte jmeno matice kterou chcete smazat:";
    in>>user_input;
    while(StMap.find(user_input)== StMap.end() && SparseMap.find(user_input)== SparseMap.end())
    {
        out<<"Matice s timto jmenem neexistuje, zadejte jine jmeno:";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        in>>user_input;
    }
    if(StMap.find(user_input)!= StMap.end())
    {
        StMap.erase(user_input);

    }
    else
    {
        SparseMap.erase(user_input);
    }
    return 0;
}
