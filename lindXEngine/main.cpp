#include "windows.h"
#include <iostream>
using namespace std;

template <size_t Len>
void print(char (&arr)[Len])
{
    cout << "len: "<<Len << endl;
	for (size_t i = 0; i < Len; ++i)
        cout << " "[!i] << arr[i];
    cout << endl;
}



void size(char* );

int main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf=FindFirstFile("c:\\*", &FindFileData);
	
	if (hf!=INVALID_HANDLE_VALUE)
	{
		do
		{
			size(FindFileData.cFileName);
		}
		while (FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
	}
}

void size(char* n)
{
	cout << n << endl;
	
	char f[] ="asdasd";
	
	print(f);
	
}











