#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include <iostream>
#include <fstream>
using namespace std;

#ifndef LOADPARAM_H
#define LOADPARAM_H

GLuint *texture_id;				//������� ����� ��� �������� ��������. //uint - ���������� �� unsigned integer. GLInt = -2147483648...2147483647  /  GLUint = 0...4294967295
int windowID;

class Create;

class TypesForParsers:public bufers
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

/*----------��� ������ ��� ��������� ������� � �������----------*/	
	typedef struct tagVERTEX        	// ������ ���-�� ����� �������
	{
		float x, y, z;    				// x,y,z -���������� ����� ����� � 3D ����������
		float u, v;           			// ���������� �� ��������
	} VERTEX;                  		// ������ ��� VERTEX
	typedef struct tagTRIANGLE     	// ������ ���-�� ������ ������������
	{
		VERTEX vertex[4];         		// ������ ������� ����� ������
	} QUAD;                    			// ������ ��� TRIANGLE
	typedef struct tagSECTOR       	// ������ ��������� ������ �������
	{
		int num_qauds;					//���������� ��������� ������� � �������
		QUAD* elem;       				// ������ �� ������ �������������
	}SECTOR;                     		// ������ ��������� ������ SECTOR 
	typedef struct tagLevels
	{
		SECTOR Area;					//������� ������ ������� ����.
	}LEVELS;	
public:	
	TypesForParsers();
	~TypesForParsers();
};

class Syntax:public TypesForParsers							//��������� ��������� � ������������ �����
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

class Load:public Syntax				//����� � ����������� �������� �� �����
{
protected:
	bool error;				//���������� ���������������� �� �� ���������� ��������� �������� ����������.
	char* what_read;		//���������� ������� ���������� ��������(��� ������)
	char* path_config;		//������ ���� � ����� ������������
	int *PassNumTextur;	// [0]���������� ����� �� ����, [1]���������� ���������� ���������� �������,
	int *PassNumCoord;		// [0]���������� ����� �� ����, [1]���������� ���������� ���������� ���������� �������,
	int *PassNumPoll;		// [0]���������� ����� �� ����, [1]���������� ���������� ���������� ????????,	
	int NumLevels;			// ���������� �������
	int NumPollies;			//���������� ����� �������

	int CurrLevel;			//������� �������
	int CurrLines;			//������� ������������ ����� � ���� �������� (x.y.z.v.u)
	int *Temp_Level_and_Coord;	//������ ������ ���������� ������� � ���������� ������������ �����(x.y.z.v.u)
public:	
	Load(char* p);
	~Load();
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
	
	friend Create;	
};

class Create:public TypesForParsers
{
	const char* texture_folder;
	int NumTextur;					//���������� �������
	int NumCoord;					//���������� ������������ ����� (1 ����� �����(x,y,z,u,v) )
	int NumPoll;					//���������� ��������� �������
	int NumLevels;
	unsigned long image_size;	
	
	bool *Level_load;				//������ �� ��������� �������� ������
	
	
	typedef unsigned char BYTE;		//����, �� ��� ������������ ����������� ����� �����
	typedef unsigned short int UINT;	//16 ������ �� 0 �� 4294967295
	typedef unsigned long DWORD;		// ������� ����� - 32 ���� (�������)

	//----------------- ����������� ��������� ������� BMP--------------------- 
	typedef struct tagBITMAPFILEHEADER {	//��������� ����� ��������� ������� (14 ����) 
		UINT  bfType;						//���������� ��� �����. ����� �� ������ ���� BM
		DWORD bfSize;						//������ ������ ����� � ������. 
		UINT  bfReserved1;					//�������������� � ������ ���� 0. 
		UINT  bfReserved2;					//�������������� � ������ ���� 0. 	
		DWORD bfOffBits;					//����������, ��� ���������� ��� ������� ������ ������������ ������ ����� 
	} BITMAPFILEHEADER;

	typedef struct tagBITMAPINFOHEADER {	//�������������� ��������� ���������� ������� (40 ����) 
		DWORD biSize;						//������ ����� ���������. 
		DWORD biWidth;						//������ ����������� � ��������. 
		DWORD biHeight;					//������ ����������� � ��������.
		UINT  biPlanes;					//���������� ����������. ���� ��� ������ ��������������� � 1. 
		UINT  biBitCount;					//���������� ��� �� ���� �������
		DWORD biCompression;				//��� ������. 
		DWORD biSizeImage;				//������ �������� � ������
		long biXPelsPerMeter;				//�������������� ���������� (� �������� �� ����) ��������� ����������
		long biYPelsPerMeter;				//������������ ���������� (� �������� �� ����) ��������� ����������
		DWORD biClrUsed;					//���������� ������������ ������ �� �������
		DWORD biClrImportant;				//���-�� ������, ����������� ��� ����������� ��������.(0 - ��� ������.)
	} BITMAPINFOHEADER;
	
	typedef struct pixel{		//��� ������ ��� �������
		unsigned char ged;		//������� ���������� �����
		unsigned char green;	//������� ���������� �����
		unsigned char blue;	//����� ���������� �����
	}pixel_type;				// ��� ����������� ����
		
	typedef struct pixel_array{		//��� ������ ��� ������� �������� ��������
		pixel_type *array_of_pixel;	//��������� ������ ��� �������� ����������� ����
		long height;					//������ �����������
		long width;						//������ �����������
	}pixel_array_type;				//��� ����������� �������

	typedef struct texture_package			//���������� ��� ��������� �������
	{
		pixel_array_type* pixel_array;	//������ ��� �������� ���������� �������
	} TEXTURES;								//��� ������ ������������ ������ ���������� ��������
	
	BITMAPFILEHEADER header;			//������������� ���� ��������� ������� (14 ����)
	BITMAPINFOHEADER info_header;	//�������������� ��������� ���������� ������� (40 ����)	
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
#include "../source/DisplayGame.cpp"

#endif
