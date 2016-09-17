##include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include <iostream>
#include <fstream>
using namespace std;

#ifndef LOADPARAM_H
#define LOADPARAM_H

GLuint *texture_id;				//создает место для хранения текстуры. //uint - сокращение от unsigned integer. GLInt = -2147483648...2147483647  /  GLUint = 0...4294967295
int windowID;

class Create;

class bufers			//Временные переменные для буфера
{
protected:
	char Bufer_x[64], Bufer_y[64], Bufer_z[64], Bufer_u[64], Bufer_v[64]; // Буферы
	char *x;			//Указатель
	string Path;
	bufers(){cout << "const bufers"<< endl;};
	~bufers(){cout << "dist bufers"<< endl;};	
};

class TypesForParsers:public bufers
{
protected:
	typedef struct tagTexture			//Для хранения имени файла с текстурой
	{
		char* path;
	}PATH;
	typedef struct tagTexturepack		//Для хранения всех текстур
	{
		PATH* Texture;
	}TEXTUREPACK;

/*----------Тип данных для координат текстур в секторе----------*/	
	typedef struct tagVERTEX        	// Создаём стр-ру нашей вершины
	{
		float x, y, z;    				// x,y,z -координаты одной точки в 3D координаты
		float u, v;           			// Координаты на текстуре
	} VERTEX;                  		// Обзовём это VERTEX
	typedef struct tagTRIANGLE     	// Создаём стр-ру нашего треугольника
	{
		VERTEX vertex[4];         		// Массив четырех таких вершин
	} QUAD;                    			// Обзовём это TRIANGLE
	typedef struct tagSECTOR       		// Создаём структуру нашего сектора
	{
		int num_qauds;					//Количество квадратов текстур в секторе
		QUAD* elem;       				// Ссылка на массив треугольников
	}SECTOR;                     		// Обзовём структуру словом SECTOR 
	typedef struct tagLevels
	{
		SECTOR Area;					//Создаем сектор локации мира.
	}LEVELS;	
public:	
	TypesForParsers(){cout << "const TypesForParsers" << endl;};
	~TypesForParsers(){cout << "dist TypesForParsers"<< endl;};	
};

class Syntax:public TypesForParsers							//параметры связанные с синтаксиссом файла
{
protected:	
	string B_texture;
	string E_texture;
	string B_coord;
	string E_coord;
	string B_Numpoll;
	string E_Numpoll;
	
	string Begin_param;
	string End_param;
	
	Syntax(){cout << "const Syntax" << endl;};
	~Syntax(){cout << "dist Syntax"<< endl;};	
};

class Load:public Syntax				//Класс с параметрами загрузки из файла
{
protected:
	bool error;				//Переменная сигнализирующаая об не правильном параметре завпроса считывания.
	char* what_read;		//Переменная хранить конкретный параметр(что читать)
	char* path_config;		//Хранит путь к файлу конфигурации
	int *PassNumTextur;	// [0]Количество строк до тега, [1]Количество параметров количества текстур,
	int *PassNumCoord;		// [0]Количество строк до тега, [1]Количество параметров количества кооординат текстур,
	int *PassNumPoll;		// [0]Количество строк до тега, [1]Количество параметров количества ????????,	
	int NumLevels;			// Количество уровней
	int NumPollies;			//Количество самих текстур

	int CurrLevel;			//Подсчет локаций
	int CurrLines;			//Подсчет координатных точек к этим локациям (x.y.z.v.u)
	int *Temp_Level_and_Coord;	//Массив хранит количество уровней и количество координатных точек(x.y.z.v.u)
public:	
	Load(char* p);
	~Load();
	void Read(char* read = (char*)"", int ReadStrPar = 0);			//Функция запускающая парсер конфига  на считывание конкретных данных  в зависимости от запроса.					
	
	bool Check_parameter(char* par = (char*)"");		//Проверка введеннного праметра на наличие ошибки
	void Info_error(char* par = (char*)"");			//Выводит информацию об ошибке
	
	int *CheckAndCountPar(ifstream &file);
		
	void LoadParameters(ifstream &file, int*, int p = 1);  // Функция запускающая парсер  и загружающая парамтры
	void SearchBegihTag(ifstream &file, int* );	
	void ParseConfig(ifstream &file, char* x);
	void ParseConfig(ifstream &file, char* x, char* y);
	int* ParseConfig(ifstream &file, char* x, char* y, char* z, char* u, char* v);
		
	TEXTUREPACK Texturepack;	
	LEVELS* level;
	
	friend Create;	
};

class Create:public TypesForParsers
{
	const char* texture_folder;
	int NumTextur;					//Количество текстур
	int NumCoord;					//количество координатных точек (1 точка имеет(x,y,z,u,v) )
	int NumPoll;					//Количество квадратов текстур
	int NumLevels;
	unsigned long image_size;	
	
	bool *Level_load;				//защита от повторной загрузки уровня
	
	
	typedef unsigned char BYTE;		//байт, ну или восьмибитное беззнаковое целое число
	typedef unsigned short int UINT;	//16 битное от 0 до 4294967295
	typedef unsigned long DWORD;		// Двойное слово - 32 бита (разряда)

	//----------------- Стандартная структура формата BMP--------------------- 
	typedef struct tagBITMAPFILEHEADER {	//Заголовок файла растровой графики (14 байт) 
		UINT  bfType;						//определяет тип файла. Здесь он должен быть BM
		DWORD bfSize;						//размер самого файла в байтах. 
		UINT  bfReserved1;					//зарезервирован и должны быть 0. 
		UINT  bfReserved2;					//зарезервирован и должны быть 0. 	
		DWORD bfOffBits;					//показывает, где начинается сам битовый массив относительно начала файла 
	} BITMAPFILEHEADER;

	typedef struct tagBITMAPINFOHEADER {	//Информационный заголовок растрового массива (40 байт) 
		DWORD biSize;						//размер самой структуры. 
		DWORD biWidth;						//ширина изображения в пикселях. 
		DWORD biHeight;					//высота изображения в пикселях.
		UINT  biPlanes;					//количество плоскостей. Пока оно всегда устанавливается в 1. 
		UINT  biBitCount;					//Количество бит на один пиксель
		DWORD biCompression;				//тип сжатия. 
		DWORD biSizeImage;				//размер картинки в байтах
		long biXPelsPerMeter;				//горизонтальное разрешение (в пикселях на метр) конечного устройства
		long biYPelsPerMeter;				//вертикальное разрешение (в пикселях на метр) конечного устройства
		DWORD biClrUsed;					//количество используемых цветов из таблицы
		DWORD biClrImportant;				//Кол-во цветов, необходимые для изображения рисунока.(0 - все важные.)
	} BITMAPINFOHEADER;
	
	typedef struct pixel{		//Тип данных для пикселя
		unsigned char ged;		//красная компонента цвета
		unsigned char green;	//зеленая компонента цвета
		unsigned char blue;	//синяя компонента цвета
	}pixel_type;				// имя пиксельного типа
		
	typedef struct pixel_array{		//Тип данных для массива структур пикселей
		pixel_type *array_of_pixel;	//Двумерный массив для пикселей пиксельного типа
		long height;					//высота изображения
		long width;						//ширина изображения
	}pixel_array_type;				//имя пикселеного массива

	typedef struct texture_package			//Структтура для считанных текстур
	{
		pixel_array_type* pixel_array;	//массив для массивов счетианных пикселе
	} TEXTURES;								//тип данных определяющий массив паксельных массивов
	
	BITMAPFILEHEADER header;			//Заголововчный файл растровой графики (14 байт)
	BITMAPINFOHEADER info_header;	//Информационный заголовок растрового массива (40 байт)	
public:
	int StackLevel;
	
	TEXTURES* texture_array;
	LEVELS* Level;
	
	Create(const Load &);
	~Create();
	void Include(Load::LEVELS* ); 
	void Include(Load::LEVELS*, int ); 
	void parse_texture_file(ifstream &, int);
} *World;


#include "../source/LoadParameters.cpp" 
#include "../source/LoadWorld.cpp" 
#include "../source/LoadGraphics.cpp" 
#endif
