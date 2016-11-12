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
	List* Begin;				//Указатель на начало списка
	List* End;					//Указатель на конец списка
	List* pList;				//Временный указатель для прохода по списку
	
	char* mask;						//маска искомы файлов	
	char* path;						//директория + маска для поиска файла
	int count_files;
	
	WIN32_FIND_DATA FindFileData;	//Структура найденного файла
	HANDLE h;							//дескриптор описывающий файл
	
	char Bufer_x[256];
	
	bool write;
	
	void toStack(char*);				//Внутренняя функция добавления в стек
	int countElements(char*);			//Внутрення функция подсчет элементов файла
	bool chkEqual(char* a, char *b);
public:
	TextureParser();
	~TextureParser();
	void ScanDirectory(char* );				//Парсер директории с файлами
	void Texture_file(char* );				//Файл конфигурационного файла тектур
	void ParseConfig(fstream &, char* );	//парсер файла с текутурами
};

TextureParser::TextureParser()		//инициализация парсера
{
	mask = new char[6];
	mask = (char*)"/*.txt\0";
	count_files = 0;
	
	Begin = End = NULL;
	
	 write = false;
}

TextureParser::~TextureParser()				
{
	
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
			count_files++;
			toStack(FindFileData.cFileName);
		}while (FindNextFile(h,&FindFileData)!=0);
	}
	FindClose(h);
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

int TextureParser::countElements(char* texture_file)
{
	int count = 0;
	fstream file((char*)texture_file, ios::in | ios::binary);

	do{ 
		ParseConfig(file, Bufer_x);
		if(!file.eof())
			count++;
	} while (!file.eof() );
	
	file.close();
	
	return count;
	
}

void TextureParser::Texture_file(char* texture_file)
{
	fstream file((char*)texture_file, ios::in | ios::out | ios::app);
	if (!file.is_open())
	{
	  cout << "file " << texture_file << "is not exsist" << endl;
	  exit(1);
	} 
			
	int NumLines = countElements((char*)texture_file); 
	
	pList = Begin;
		
	do
	{ 
		int i = NumLines;
		
		file.seekg(0, ios::beg);
				
		do
		{  
			ParseConfig(file, Bufer_x);		
								
			bool equal = chkEqual(pList->key.elem, Bufer_x);
						
			if ( equal == true)
				break;
					
			if (i <= 0 && equal == false)
			{
				char* p = pList->key.elem;
				
				cout << "Add new Files: " << p << endl;
				
				file.seekg(0, ios::end);
								
				if (Bufer_x[NumLines] != '\n')
					file <<'\n';
							
				 while(*p)
					file.put(*p++);
			} 
		} while (i-- != 0);
						
		if (pList)
		pList = pList->next;
	
	} while (pList);
		
	file.close();
}

bool TextureParser::chkEqual(char* a, char *b)
{
	bool equal = false;

		int j = 0;
		do
		{ 
			if ( ((a[j] != '\0') || (a[j] != ' ') ) && (b[j] != '\0' ) )
			{
			 	if ( (a[j] != b[j]) )
				{
					equal = false;
					break;
				} 
				
				equal = true;
			} 
		} while ( (a[j++] != '\0') && (b[j] != '\0') );
	return equal;			
}

void TextureParser::ParseConfig(fstream &file, char* x)
{
	do
	{ 
		file >> x;
		if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' )
				file.getline(x, 255, '\n');
	} while (x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]==' ');
}



int main() 
{
	  TextureParser *ScanTexture = new TextureParser();
		ScanTexture -> ScanDirectory((char*)"textures");
		ScanTexture -> Texture_file((char*)"config_textures.txt");
		
		
	  return 0;
}











