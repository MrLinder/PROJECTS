#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdarg.h>
#include <sstream>
#include <iomanip>	
using namespace std;

#ifndef HEADER_H
#define HEADER_H

const int num_coord = 10;

class DisplayParam
{
protected:
	float divideSize;  			//
	float wS;						//WinAPI - ������ �������
	float hS;						//WinAPI - ������ �������
	float indentWinScrWidth;		//��������� �� ����� �� ������
	float indentWinScrHight;		//��������� �� ����� �� ������
public:
	bool fullscreen;
	float SubSysDisplayHight;		//������  ���������� ������ �������
	float SubSysDisplayWidth;		//������ ���������� ������ �������
	float IndentSubDisplayTop;	//������ � ����� ���������� ������ �������
	float IndentSubDisplayLeft; 	//������ � � ���� ���������� ������ �������
	
	float widthScreen;			//�����  ������ �� 2  �.�  �� ������������� �����
	float hightScreen;			// ��������� ���������� �������������� ����������
};

class Interface:public DisplayParam
{	
public:
	float linearinterval;		//�������� ����� �������
	float fontinterval;		//�������� ����� ��������

	//float StepMoving;
	float xTrans;
	float yTrans;
	float zTrans;

	float xLook;
	float yLook;
	float zLook;
	
	Interface();
	~Interface();
	void SetScreen(double );
} *Display, *Dp;

class coord
{
	float n;
public:	
	float set(float);
	float get();
} x0[num_coord], 
  y0[num_coord], 
  z0[num_coord], 
  x[num_coord], 
  z[num_coord];

class y_coord:public DisplayParam
{
	float n;
public:	
	y_coord();
	float set(float);
	float get(float);
} y[num_coord];


#include "../source/DisplayInterface.cpp" 

#endif