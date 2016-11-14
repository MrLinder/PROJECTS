#include "windows.h"
#include <iostream>
#include <fstream>
using namespace std;

class Bufers			//Временные переменные для буфера
{
protected:
	char Bufer_x[64], Bufer_y[64], Bufer_z[64], Bufer_u[64], Bufer_v[64]; // Буферы
	char *x;			//Указатель
	string Path;		/// ------------>!!!!ывавыавы
	Bufers();
	~Bufers();
};

class Base:public Bufers {					//класс со списком
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

class TextureParser:public Base
{
	List* Begin;							//Указатель на начало списка
	List* End;								//Указатель на конец списка
	List* pList;							//Временный указатель для прохода по списку
	
	char* mask;							//маска искомы файлов	
	char* path;							//директория + маска для поиска файла
	int count_files;
	
	WIN32_FIND_DATA FindFileData;		//Структура найденного файла
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
	void Texture_file(char* );				//Файл конфигурационного файла тектур
};

class TypesForParsers:public TextureParser
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
public:	
	TypesForParsers();
	~TypesForParsers();
};



