//============================================================================
 // Name         : HelloWorld.cpp
 // Author       : 
 // Version      : 
 // Date         : 
 // License      : 
 // Description  : Hello World in C++
 //============================================================================
 
#include <iostream>
using namespace std;

int main( )
{
    int count = 10;
    int& countRef = count;
    auto myAuto = countRef;

    countRef = 11;
    cout << count << " ";

    myAuto = 12;
    cout << count << endl;
}