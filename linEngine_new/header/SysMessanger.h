#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdarg.h>
#include <sstream>
#include <iomanip>	
using namespace std;


#ifndef SYSMSG_H
#define SYSMSG_H

class ConverterToOneString{
	unsigned int ival;		// переменная для поиска типа int
	double fval;				// переменная для поиска типа double
	char* chval;				// переменная для поиска типа char
	int ResultSize;			//размер итогового массива		
	char* ResultsArr;			//результирующий массив	
	int TempSize;			//переменная для хранения размера временного массива
public:
	ConverterToOneString();
	~ConverterToOneString();	
	char* ToOneStr(char* format, ...);
	void ToResultsArr(char*);
} *Convert;

class MsgToDiaplay
{
	char **SysMsgBuffer;
	int loop;
	int UpStackSize;
	int len;
public:	
	int StackIdx;
	MsgToDiaplay();
	~MsgToDiaplay();
	void Send(char*);
	char* Get(int);        
} *SysMsg;


#include "../source/SysMessanger.cpp" 
#endif

