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
	unsigned int ival;		// ���������� ��� ������ ���� int
	double fval;				// ���������� ��� ������ ���� double
	char* chval;				// ���������� ��� ������ ���� char
	int ResultSize;			//������ ��������� �������		
	char* ResultsArr;			//�������������� ������	
	int TempSize;			//���������� ��� �������� ������� ���������� �������
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

