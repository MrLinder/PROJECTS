#include "windows.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

class Bufers{			//Временные переменные для буфера
protected:
	char Bufer_x[64], Bufer_y[64], Bufer_z[64], Bufer_u[64], Bufer_v[64]; // Буферы
	char *x;			//Указатель
	string Path;		/// ------------>!!!про
	Bufers();
	~Bufers();
};

class Base{					//класс со списком
	protected:
		struct Data{							//элемент списка с массивом для имен файлов
			char* elem;
		};
		struct List{							//указатели
			Data key;
			List *next;
			List *prev;
			List *temp;
			List(){next=prev=temp=NULL;}		//обнуляем указатели
		};
	public:
		Base();
		~Base();
};

class Syntax{							//параметры свЯзанные с синтаксиссом файла
protected:	
	string B_texture;
	string E_texture;
	string B_coord;
	string E_coord;
	string B_Numpoll;
	string E_Numpoll;
	
	string Begin_param;
	string End_param;

	Syntax();
	~Syntax();	
};

class TextureParser:public Base, public Bufers, public Syntax{
	List* Begin;							//Указатель на начало списка
	List* End;								//Указатель на конец списка
	List* pList;							//Временный указатель для прохода по списку
	
	char* mask;							//маска искомы файлов	
	char* path;							//директория + маска для поиска файла
	int count_files;
	
	WIN32_FIND_DATA FindFileData;		//структура найденного файла
	HANDLE h;								//дескриптор описывающий файл
	
	bool write;
	
	void toStack(char*);						//Внутренняя функция добавления в стек
	int countElements(char*);					//Внутрення функция подсчет элементов файла
	bool chkEqual(char* a, char *b);
	void parseConfig(fstream &, char* );		//парсер файла с текутурами
public:
	TextureParser();
	~TextureParser();
	void ScanDirectory(char* );				//Парсер директории с файлами
	void CreateTextureConfig(char* );				//Файл конфигурационного файла тектур
	char* ConfigFile;
};

class TypesForParsers:public Bufers{
protected:
	typedef struct tagTexture			//„лЯ хранениЯ имени файла с текстурой
	{
		char* path;
	}PATH;
	typedef struct tagTexturepack		//„лЯ хранениЯ всех текстур
	{
		PATH* Texture;
	}TEXTUREPACK;

/*----------’ип данных длЯ координат текстур в секторе----------*/	
	typedef struct tagVERTEX        	// ‘оздаЮм стр-ру нашей вершины
	{
		float x, y, z;    				// x,y,z -координаты одной точки в 3D координаты
		float u, v;           			// Љоординаты на текстуре
	} VERTEX;                  		
	typedef struct tagTRIANGLE     	// ‘оздаЮм стр-ру нашего треугольника
	{
		VERTEX vertex[4];         		// Њассив четырех таких вершин
	} QUAD;                    			
	typedef struct tagSECTOR       	// ‘оздаЮм структуру нашего сектора
	{
		int num_qauds;					//Љоличество квадратов текстур в секторе
		QUAD* elem;       				// ‘сылка на массив треугольников
	}SECTOR;                     		
	typedef struct tagLevels
	{
		SECTOR Area;					//‘оздаем сектор локации мира.
	}LEVELS;	
public:	
	TypesForParsers();
	~TypesForParsers();
};

class Load:public Syntax, public TypesForParsers					//Љласс с параметрами загрузки из файла
{
protected:
	char* texture_file;	//хранит путь к файлу с именами текстур
	char* config_file;		//•ранит путь к файлу конфигурации
	
	char* what_read;		//ЏеременнаЯ хранить конкретный параметр(что читать)
	bool error;				//ЏеременнаЯ сигнализирующааЯ об не правильном параметре завпроса считываниЯ.


	int *PassNumTextur;	// [0]Љоличество строк до тега, [1]Љоличество параметров количества текстур,
	int *PassNumCoord;		// [0]Љоличество строк до тега, [1]Љоличество параметров количества кооординат текстур,
	int *PassNumPoll;		// [0]Љоличество строк до тега, [1]Љоличество параметров количества ????????,	
	int NumLevels;			// Љоличество уровней
	int NumPollies;			//Љоличество самих текстур

	int CurrLevel;			//Џодсчет локаций
	int CurrLines;			//Џодсчет координатных точек к этим локациЯм (x.y.z.v.u)
	int *Temp_Level_and_Coord;	//Њассив хранит количество уровней и количество координатных точек(x.y.z.v.u)
public:	
	Load(char* );
	~Load();
	void Include(char*);
	void Read(char* read = (char*)"", int ReadStrPar = 0);			//”ункциЯ запускающаЯ парсер конфига  на считывание конкретных данных  в зависимости от запроса.					
	bool Check_parameter(char* par = (char*)"");		//Џроверка введеннного праметра на наличие ошибки
	void Info_error(char* par = (char*)"");			//‚ыводит информацию об ошибке
	int *CheckAndCountPar(ifstream &file);
	void LoadParameters(ifstream &file, int*, int p = 1);  // ”ункциЯ запускающаЯ парсер  и загружающаЯ парамтры
	void SearchBegihTag(ifstream &file, int* );	
	void ParseConfig(ifstream &file, char* x);
	void ParseConfig(ifstream &file, char* x, char* y);
	int* ParseConfig(ifstream &file, char* x, char* y, char* z, char* u, char* v);
		
	TEXTUREPACK Texturepack;	
	LEVELS* level;
};



	
	
#endif 

#include "../source/LoadParameters.cpp"