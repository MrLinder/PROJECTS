#include "windows.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

class Bufers{			//��������� ���������� ��� ������
protected:
	char Bufer_x[64], Bufer_y[64], Bufer_z[64], Bufer_u[64], Bufer_v[64]; // ������
	char *x;			//���������
	string Path;		/// ------------>!!!���
	Bufers();
	~Bufers();
};

class Base{					//����� �� �������
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

class TextureParser:public Base, public Bufers{
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
	void CreateTextureConfig(char* );				//���� ����������������� ����� ������
	char* ConfigFile;
};

class TypesForParsers:public Bufers{
protected:
	typedef struct tagTexture			//��� �������� ����� ����� � ���������
	{
		char* path;
	}PATH;
	typedef struct tagTexturepack		//��� �������� ���� �������
	{
		PATH* Texture;
	}TEXTUREPACK;

/*----------��� ������ ��� ��������� ������� � �������----------*/	
	typedef struct tagVERTEX        	// ������� ���-�� ����� �������
	{
		float x, y, z;    				// x,y,z -���������� ����� ����� � 3D ����������
		float u, v;           			// ���������� �� ��������
	} VERTEX;                  		
	typedef struct tagTRIANGLE     	// ������� ���-�� ������ ������������
	{
		VERTEX vertex[4];         		// ������ ������� ����� ������
	} QUAD;                    			
	typedef struct tagSECTOR       	// ������� ��������� ������ �������
	{
		int num_qauds;					//���������� ��������� ������� � �������
		QUAD* elem;       				// ������ �� ������ �������������
	}SECTOR;                     		
	typedef struct tagLevels
	{
		SECTOR Area;					//������� ������ ������� ����.
	}LEVELS;	
public:	
	TypesForParsers();
	~TypesForParsers();
};

class Syntax{							//��������� ��������� � ������������ �����
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

class Load:public Syntax, public TypesForParsers					//����� � ����������� �������� �� �����
{
protected:
	char* texture_file;	//������ ���� � ����� � ������� �������
	char* config_file;		//������ ���� � ����� ������������
	
	char* what_read;		//���������� ������� ���������� ��������(��� ������)
	bool error;				//���������� ���������������� �� �� ���������� ��������� �������� ����������.


	int *PassNumTextur;	// [0]���������� ����� �� ����, [1]���������� ���������� ���������� �������,
	int *PassNumCoord;		// [0]���������� ����� �� ����, [1]���������� ���������� ���������� ���������� �������,
	int *PassNumPoll;		// [0]���������� ����� �� ����, [1]���������� ���������� ���������� ????????,	
	int NumLevels;			// ���������� �������
	int NumPollies;			//���������� ����� �������

	int CurrLevel;			//������� �������
	int CurrLines;			//������� ������������ ����� � ���� �������� (x.y.z.v.u)
	int *Temp_Level_and_Coord;	//������ ������ ���������� ������� � ���������� ������������ �����(x.y.z.v.u)
public:	
	Load(char* );
	~Load();
	void Include(char*);
	void Read(char* read = (char*)"", int ReadStrPar = 0);			//������� ����������� ������ �������  �� ���������� ���������� ������  � ����������� �� �������.					
	bool Check_parameter(char* par = (char*)"");		//�������� ����������� �������� �� ������� ������
	void Info_error(char* par = (char*)"");			//������� ���������� �� ������
	int *CheckAndCountPar(ifstream &file);
	void LoadParameters(ifstream &file, int*, int p = 1);  // ������� ����������� ������  � ����������� ��������
	void SearchBegihTag(ifstream &file, int* );	
	void ParseConfig(ifstream &file, char* x);
	void ParseConfig(ifstream &file, char* x, char* y);
	int* ParseConfig(ifstream &file, char* x, char* y, char* z, char* u, char* v);
		
	TEXTUREPACK Texturepack;	
	LEVELS* level;
};



	
	
#endif 

#include "../source/LoadParameters.cpp"