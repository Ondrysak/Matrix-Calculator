/**
*@file
*@brief This file creates an instance of the calculator on standart output and standart input and runs it.
*
*/
#include <iostream>
#include <cstdlib>
#include "c_wrapper.h"
using namespace std;
int main(int argc, char* argv[])
{

    int maximum;
    if(argc!=2)
    {
        cout<<"Musite zadat maximalni rozmer matice jako argv! Napriklad ./nankaond 20."<<endl;
        return 1;
    }
    else
    {
        maximum = atoi(argv[1]);
        if(maximum == 0 || maximum <0){
        cout<<"Musite zadat maximalni rozmer matice jako argv! Napriklad ./nankaond 20."<<endl;
        return 1;
        }
        C_Wrapper moje(cout, cin,maximum);
        moje.Run();
    }
    return 0;
}
