//============================================================================
 // Name         : HelloWorld.cpp
 // Author       : 
 // Version      : 
 // Date         : 
 // License      : 
 // Description  : Hello World in C++
 //============================================================================
 
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string str = "kakaha";
	
	for ( int i = 0; str[i] != '\0' ; ++i) 
	{
		if (str[i] == '\0' )
			cout << "END!" << endl;
		cout << str[i];
	}

}
