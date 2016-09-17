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
	float wS;						//WinAPI - ширина мониора
	float hS;						//WinAPI - высота мониора
	float indentWinScrWidth;		//растояние от краев по ширине
	float indentWinScrHight;		//растояние от краев по высоте
public:
	bool fullscreen;
	float SubSysDisplayHight;		//Высота  системного буфера дисплея
	float SubSysDisplayWidth;		//Ширина системного буфера дисплея
	float IndentSubDisplayTop;	//отступ с верху системного буфера дисплея
	float IndentSubDisplayLeft; 	//отступ с с лева системного буфера дисплея
	
	float widthScreen;			//делим  ширину на 2  т.е  не полноэкранный режим
	float hightScreen;			// Вычисляем сотоноение полноэкранного разрешения
};

class Interface:public DisplayParam
{	
public:
	float linearinterval;		//интервал между буквами
	float fontinterval;		//интервал между строками

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