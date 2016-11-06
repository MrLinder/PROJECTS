#include "windows.h"
#include <iostream>
#include <fstream>
using namespace std;
/* 		ЗадачаЖ:
	Прочитать файлы .bmp в каталоге и записать в файл, каждый файл с новой строки.
	Если будут в каталоге появляться новые файлы то записывать их в конец файла.
		Алгоритм:
	Читаем перый файл и сравниваем его .txt базой 
		если файл пустой то записываем его первым и читаем следующий
		если файл не пустой, и имени файла нет, то записываем его в конец.
		если файл такой есть,  то ничего не записываем и читаем дальше.
*/

class Base {									//класс со структурой
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
		Base() {cout<<"Base Const"<<endl;}	
		~Base(){cout<<"Base Distr"<<endl;}
};

class TextureParser:public Base
{
	List* Begin;
	List* End;
	
	char* mask;						//маска искомы файлов	
	char *path;						//директория + маска для поиска файла
	
	WIN32_FIND_DATA FindFileData;	//Структура найденного файла
	HANDLE h;							//дескриптор описывающий файл
	
	void toStack(char*);
public:
	TextureParser(char*);
	~TextureParser();
	void ScanDirectory(char* );
	void show();
};

TextureParser::TextureParser(char* texture_file)		//инициализация парсера
{
	cout << texture_file<<endl;
	
	mask = new char[6];
	mask = (char*)"/*.txt\0";
	
	Begin = End = NULL;
	
	fstream file((char*)texture_file, ios::in | ios::out | ios::app);
	if (!file.is_open())
		exit(1);
	
	file << 10 << " "<<123.23<<endl;
	file << "just text ";
	
		
	
	file.close();
}

TextureParser::~TextureParser()				
{
	
}

void TextureParser::toStack(char* name)
{
	int str_length = strlen(name)+1;
	
	//создаем элемент ни от кого не зависящий и записываем в него поступившее значение
	int i = 0;
	List *Temp = new List();
		Temp->key.elem = new char[str_length];
			for ( ; i < str_length; ++i) 
				Temp->key.elem[i] = name[i];
					Temp->key.elem[i+1] = '\0';
	
	if (Begin == NULL)		//если Указатель начала пуст значит этот элемент будет первым.
	{
		Begin = Temp;
		End = Temp;
	} 
	else					//если нет тогда добавляем в конец списка
	{
		End -> next = Temp;	
		Temp -> prev = End;
		End = End->next;
	}				
}

void TextureParser::ScanDirectory(char* dir)
{
	path = new char[strlen(dir)+strlen(mask)+1];
	strcpy(path, dir);
	strcat(path, mask);
	strcat(path, "\0");
		
	h = FindFirstFile(path, &FindFileData);
	
	if (h != INVALID_HANDLE_VALUE)
	{
		do{
			toStack(FindFileData.cFileName);
		}while (FindNextFile(h,&FindFileData)!=0);
	}
	FindClose(h);
}


void TextureParser::show()
{
	List *p = Begin;
	
	do
	{ 
		int i = 0;
		
		do
		{ 
			  cout << p->key.elem[i];
		} while (p->key.elem[i++] != '\0');
		
		 cout << endl;
		 		 
		 p = p->next;
	} while (p);
}


int main() 
{
	  TextureParser *ScanTexture = new TextureParser((char*)"config_textures.txt");
		ScanTexture -> ScanDirectory((char*)"textures");

		ScanTexture -> show();
		
	  return 0;
}








