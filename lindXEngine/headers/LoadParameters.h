#include "windows.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

class Bufers			//��������� ���������� ��� ������
{
protected:
	char Bufer_x[64], Bufer_y[64], Bufer_z[64], Bufer_u[64], Bufer_v[64]; // ������
	char *x;			//���������
	string Path;		/// ------------>!!!!��������
	Bufers();
	~Bufers();
};

class Base:public Bufers {					//����� �� �������
	protected:
		struct Data{							//������� ������ � �������� ��� ���� ������
			char* elem;
		};
		struct List{							//���������
			Data key;
			List *next;
			List *prev;
			List *temp;
			List(){next=prev=temp=NULL;}		//�������� ���������
		};
	public:
		Base();
		~Base();
};

class TextureParser:public Base
{
	List* Begin;							//��������� �� ������ ������
	List* End;								//��������� �� ����� ������
	List* pList;							//��������� ��������� ��� ������� �� ������
	
	char* mask;							//����� ������ ������	
	char* path;							//���������� + ����� ��� ������ �����
	int count_files;
	
	WIN32_FIND_DATA FindFileData;		//��������� ���������� �����
	HANDLE h;								//���������� ����������� ����
	
	bool write;
	
	void toStack(char*);						//���������� ������� ���������� � ����
	int countElements(char*);					//��������� ������� ������� ��������� �����
	bool chkEqual(char* a, char *b);
	void parseConfig(fstream &, char* );		//������ ����� � ����������
public:
	TextureParser();
	~TextureParser();
	void ScanDirectory(char* );				//������ ���������� � �������
	void Texture_file(char* );				//���� ����������������� ����� ������
};

class TypesForParsers:public TextureParser
{
protected:
	typedef struct tagTexture			//��� �������� ����� ����� � ���������
	{
		char* path;
	}PATH;
	typedef struct tagTexturepack		//��� �������� ���� �������
	{
		PATH* Texture;
	}TEXTUREPACK;
public:	
	TypesForParsers();
	~TypesForParsers();
};
	
#endif 

#include "../source/LoadParameters.cpp"