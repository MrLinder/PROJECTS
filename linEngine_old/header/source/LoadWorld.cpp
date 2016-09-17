
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include <cstring>
#include <cstdlib>	
#include <iostream>
#include <fstream>
using namespace std;

#ifndef LOADWORLD_Cpp
#define LOADWORLD_Cpp

Create::Create(const Load &config)
{
	cout << "constr Create" << endl;
	texture_folder = new char[9];
	texture_folder = "textures";
	
	NumLevels = config.NumLevels;
	NumPoll = config.NumPollies;
	NumTextur = config.PassNumTextur[1];	
	NumCoord = config.PassNumCoord[1];
	
	Level_load = new bool[NumLevels+1];
		for ( int i = 0; i <= NumLevels; ++i) 		//Уровни не загружены
			Level_load[i] = false;
		
	cout << "Distr Create" << endl;
	cout << "NumTextur: " << NumTextur<<endl;
	cout << "NumPoll: " << NumPoll<<endl;
	cout << "NumCoord: " << NumCoord<<endl;
	cout << "NumLevels: " << NumLevels<<endl;
	
	for ( int i = 1; i <= NumLevels; ++i) 
		cout << "level: " << i <<" = "<< config.level[i].Area.num_qauds <<" Status: "<< Level_load[i]<<endl;

	image_size = 0;	
// - - - - - - - - - - - - - Важный кусок инициализации структуры с ппикселями- - - - - - - - - - - - - 	
	texture_array = new TEXTURES[NumTextur];  // Выдяляем память для массива паксельных массивов(текстуры.)
		
	for ( int i = 0; i < NumTextur; ++i) 			//Инициализация и обнудение всего содержимого струтктуры
	{
		texture_array[i].pixel_array = new pixel_array_type;
		texture_array[i].pixel_array->array_of_pixel = NULL;
		texture_array[i].pixel_array->height = 0;
		texture_array[i].pixel_array->width = 0;
	}
	
	StackLevel = 0;
	Level = new LEVELS[NumLevels+1];
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	texture_id = new GLuint[NumTextur];			 //создаеv место для хранения текстуры. 
	
	int LenFol = strlen(texture_folder);
	int j=0;
	do
	{ 
		int LenAll = (strlen(texture_folder) + strlen(config.Texturepack.Texture[j].path)+1);
		char* temp_full_path = new char[LenAll+1];
		int i = 0;
		do{ 
			if (i < LenFol )
				temp_full_path[i] = texture_folder[i];
			else if(i == LenFol )
				temp_full_path[i] = '/';
			else
				temp_full_path[i] = config.Texturepack.Texture[j].path[i-LenFol-1];
		}while (i++ < LenAll);
	
		ifstream bmp_file;
		bmp_file.open((char*)temp_full_path, ios::in | ios::binary);
		if(!bmp_file.is_open())
		{
			cout<<"Can't open \"" <<temp_full_path<<"\" - is not exist or have other name." << endl;
			exit(1);
		}
		
		parse_texture_file(bmp_file, j); //Поток подключенный к файлу, индекс для данной текстуры
		cout<<"\t"<<temp_full_path<<endl;;
	} while (j++ < NumTextur-1);	
}

Create::~Create()
{
	cout << "distr Create"<< endl;
}

void Create::parse_texture_file(ifstream &bmp_file, int which_texture)
{	
	cout << which_texture;
	// Читаем первую структуру (BITMAPFILEHEADER)	
	bmp_file.read((char*)&header.bfType, sizeof(header.bfType));
	bmp_file.read((char*)&header.bfSize, sizeof(header.bfSize));
	bmp_file.read((char*)&header.bfReserved1, sizeof(header.bfReserved1));
	bmp_file.read((char*)&header.bfReserved2, sizeof(header.bfReserved2));
	bmp_file.read((char*)&header.bfOffBits, sizeof(header.bfOffBits));
	
	// Читаем вторую структуру (BITMAPINFOHEADER) чтобы узнать размер буфера пикселей
	bmp_file.read((char*)&info_header, sizeof(info_header));
	
	if(info_header.biSizeImage == 0)  //размер картинки в байтах. Если изображение несжато, то здесь должен быть ноль. 
	{		// считаем вручную
		image_size = info_header.biWidth * 3 + info_header.biWidth % 4;
		image_size *= info_header.biHeight; 		// считаем вручную
	}
	else	// иначе - берем как есть
		image_size = info_header.biSizeImage; 	
	
	bmp_file.seekg(header.bfOffBits, ios::beg);		//Смещаемся к буферу пикселей (header.bfOffBits байтов, считая от начала файла ios::beg) Смещение, с которого начинается само изображение (растр).

	//Присваиваем значения размеров изображения	
	texture_array[which_texture].pixel_array->height = info_header.biHeight;	//присваиваем значения из biHeight
	texture_array[which_texture].pixel_array->width = info_header.biWidth;	//присваиваем значения из biWidth	

	// Создаем  массив под структуры пикселя
	texture_array[which_texture].pixel_array->array_of_pixel = new pixel_type[texture_array[which_texture].pixel_array->height * texture_array[which_texture].pixel_array->width];  //выделяем память строк

	int length_str = (3 * texture_array[which_texture].pixel_array->width + 3) & (-4); 	// длина строки в файле, включая округление вверх до кратного 4
	int n = length_str - texture_array[which_texture].pixel_array->width * 3; 			 	// количество байтов выравнивания в строке
	
	//присваиваем значения массиву		
	for ( int j = 0; j < texture_array[which_texture].pixel_array->height * texture_array[which_texture].pixel_array->width; ++j) 
	{
		bmp_file.read((char*)&texture_array[which_texture].pixel_array->array_of_pixel[j], sizeof(pixel_type));

		for (int k = 0; k < n; ++k) 				// пропуск байтов выравнивания
			bmp_file.get();
	}
	bmp_file.close();	

	glGenTextures(which_texture, &texture_id[which_texture]);  //генерирует уникальные имена для текстур
	glBindTexture(GL_TEXTURE_2D, texture_id[which_texture]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture_array[which_texture].pixel_array->width, texture_array[which_texture].pixel_array->height, GL_BGR, GL_UNSIGNED_BYTE, texture_array[which_texture].pixel_array->array_of_pixel);

}

void Create::Include(Load::LEVELS *level )
{	
	for ( int l = 1; l <= NumLevels; ++l) 
	{
		if(Level_load[l])
			return;
		Level[l].Area.num_qauds = level[l].Area.num_qauds;			//Присваиваем колво триугольников
		Level[l].Area.elem = new QUAD[level[l].Area.num_qauds]; 
	
		for ( int loop = 0; loop < level[l].Area.num_qauds; ++loop) 
		{
			Level_load[l] = true;
			for ( int vert = 0; vert < 4; ++vert) 
			{
				Level[l].Area.elem[loop].vertex[vert].x = level[l].Area.elem[loop].vertex[vert].x;
				Level[l].Area.elem[loop].vertex[vert].y = level[l].Area.elem[loop].vertex[vert].y;
				Level[l].Area.elem[loop].vertex[vert].z = level[l].Area.elem[loop].vertex[vert].z;
				Level[l].Area.elem[loop].vertex[vert].u = level[l].Area.elem[loop].vertex[vert].u;
				Level[l].Area.elem[loop].vertex[vert].v = level[l].Area.elem[loop].vertex[vert].v;
			}
		}
	}
}

void Create::Include(Load::LEVELS *level, int Num )
{
	if(Level_load[Num] || Num == 0 )
		return;
	
	StackLevel++;
	cout << "level: " << Num << " Loaded as: " << StackLevel << endl;
	
	Level[StackLevel].Area.num_qauds = level[Num].Area.num_qauds;			//Присваиваем колво триугольников
	Level[StackLevel].Area.elem = new QUAD[level[Num].Area.num_qauds]; 
		
	for ( int loop = 0; loop < level[Num].Area.num_qauds; ++loop) 
	{
		Level_load[Num] = true;
		for ( int vert = 0; vert < 4; ++vert) 
		{
			Level[StackLevel].Area.elem[loop].vertex[vert].x = level[Num].Area.elem[loop].vertex[vert].x;
			Level[StackLevel].Area.elem[loop].vertex[vert].y = level[Num].Area.elem[loop].vertex[vert].y;
			Level[StackLevel].Area.elem[loop].vertex[vert].z = level[Num].Area.elem[loop].vertex[vert].z;
			Level[StackLevel].Area.elem[loop].vertex[vert].u = level[Num].Area.elem[loop].vertex[vert].u;
			Level[StackLevel].Area.elem[loop].vertex[vert].v = level[Num].Area.elem[loop].vertex[vert].v;
		}
	}
}	

#endif