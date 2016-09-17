#include <cstring>
#include <cstdlib>		
#include <iostream>
#include <fstream>
using namespace std;

#ifndef LOADPARAM_Cpp
#define LOADPARAM_Cpp

Load::Load(char* p)		//инициализации
{
	cout << "Const_Load..."<< endl;
	NumPollies = 0;
	NumLevels = 0;
	error = false;
	
	path_config = new char[strlen(p)+1];
	memcpy(path_config, p, strlen(p)+1);
	
	PassNumTextur = new int[2];			//Количество строк до тега и после до закрывающего 
	PassNumCoord  = new int[2];			//Количество строк до тега и после до закрывающего 
	PassNumPoll = new int[2];				//Количество строк до тега и после до закрывающего 

	CurrLevel = 0;
	CurrLines = 0;
	
/* ------- Синтаксис файла конфигурации -------*/
	// теги начала и концца парметров с путями к текстурам
	B_texture = "Begin_textures";
	E_texture = "End_textures";
	
	// теги начала и концца парметров с координатами текстур
	B_coord = "Begin_coordinates";
	E_coord = "End_coordinates";
	
	B_Numpoll = "Begin_Numpollies";
	E_Numpoll = "End_Numpollies";
	
	cout << "\n\n--------- System information ---------" << endl;
	cout << "\nName config file: "<<path_config << endl;
}

Load::~Load()
{
	cout << "Dist_Load..."<< endl;
	//delete path_config;
	//delete what_read;
}

void Load::Read(char* read, int ReadStrPar)	//Функция определяет какой блок параметров читать и запускает парсинг
{
	what_read = new char(strlen(read)+1);	//Сохраняем параметр парсинга
	what_read = read;
	if(Check_parameter(what_read)) 			//Проверка на правильность введенного параметра
	{
		Info_error(what_read);				//Вывести информацию о возможной ошибке(можно убрать)
		exit(1);		
	}
	if(ReadStrPar < 1 || 5 < ReadStrPar)
	{
		cout <<"("<<ReadStrPar<<") -Invalid value for the number of parameters to be read.\n"
		 "Use values from (1) to (5). But this doesn't guarantee the accuracy of reading.\n"
		 "Therefore always check the number of parameters to read in config file:\n("<<path_config<<")\n"<<endl;
		exit(1);
	}	
	ifstream file((char*)path_config, ios::in);	//открываем поток
	if(!file.is_open()) 								//проверка на существование файла
	{
		cout <<"file with name: \"" << path_config  <<"\" is not exist or have other name."<<endl;
		exit(1);
	}
	//Опредеоение синтаксиса тегов в соответвии с выбранным параметром парсинга
	
	if(what_read == (char*)"Textures Path")
	{
		Begin_param = B_texture;
		End_param = E_texture;
		PassNumTextur = CheckAndCountPar(file);		//Количество текстур
		LoadParameters(file, PassNumTextur, ReadStrPar);		//Поток, Параметры поиска и чтения, количество параметров в троке
	}
	if(what_read == (char*)"Textures Numpollies")
	{		
		Begin_param = B_Numpoll;
		End_param = E_Numpoll;
		PassNumPoll = CheckAndCountPar(file);			//Количество параметров
		LoadParameters(file, PassNumPoll, ReadStrPar);	
	}
	if(what_read == (char*)"Textures Coordinates")
	{
		Begin_param = B_coord;
		End_param = E_coord;
		PassNumCoord = CheckAndCountPar(file);		//Количество координатных параметров
		
			level = new LEVELS[NumLevels+1];				//выделяем память для уровней
			Temp_Level_and_Coord = new int[NumLevels+1];		//Временная
	
		LoadParameters(file, PassNumCoord, ReadStrPar);	
	}
	file.close();
}

int* Load::CheckAndCountPar(ifstream &fcount) 	//Проверка синтаксисса конфига и подсчет параметров
{
	unsigned int i;
	int *before_after_tag = new int[2];
	int pass_couter = 0;
	int after_counter = 1;
	
	bool next;
	fcount.seekg(0);	
	do
	{ 
	next = false;	 
		do{ 
			x = new char[64];
				fcount >> x;
						
			if(x[0] !='#')
				fcount.getline(x, 255, '\n');
			else
			{
				pass_couter++;
				break;	
			}				
					
			if(fcount.eof() && x[0] !='#' )
			{
				cout<< "ERROR!: Tag with the name: \"#" << Begin_param << "\" is not found! \n or set isn't correct - it means impossible to determine parameters,\n\t Process cannot continue..." << endl;
			exit(1);
			}
		} while (x[0] !='#');
		
		i = 0;
		do{ 
			if(x[i+1] != Begin_param[i])
			{
				next = true;
				break;
			}
		} while (i++ < Begin_param.length());
	} while (!fcount.eof() && next == true);	
	
	bool DefEndParam = false; 	//для сообщения об ошибке (достигнут конец файла - закрывающего параметра нет)
	do{ 
		after_counter++;
		x = new char[64];	
		fcount.getline(x, 255, '\n');
		if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]=='#' || x[0]==':') 
			after_counter--;
		if(x[0]==':' )
		{
			NumLevels++;
		}	
			
		if(x[0]=='#' )
		{
			DefEndParam = true;
			after_counter--;
		}

		if(fcount.eof() && DefEndParam == false)
		{
			cout << "Opened tag: \"#"<< Begin_param << "\" has not close tag: \"#"<< End_param << "\""<< endl;
			exit(1);
		}
	} while (x[0] !='#');

	i = 0;
	do{ 
		if(x[i+1] != End_param[i])
		{
			cout << "End tag: \"" << x << "\" is Wrong! There must be: \"" << End_param << "\" "<<endl;
			exit(1);
			delete[]x;
		}
	} while (i++ < End_param.length());
	
	before_after_tag[0] = pass_couter;
	before_after_tag[1] = after_counter;

	return before_after_tag;
}

bool Load::Check_parameter(char* par)			//Проверка коректности запроса параметров
{
	if(par == (char*)"Textures Path" || par == (char*)"Textures Coordinates" || par == (char*)"Textures Numpollies" )
		return false;
	else if(par == (char*)"")
		return true;
	else
		return true;
}

void Load::Info_error(char* par)				//Информация об ошибках при запросе параметров
{
	if(par == (char*)"Textures Path" || par == (char*)"Textures Coordinates" || par == (char*)"Textures Numpollies" )
	{
		cout << "\"" << par << "\" is right!" << endl;
	}
	else if(par == (char*)"")
	{
		cout << "\tYou do not specify any parameters"<<endl;
		error = true;
	}
	else
	{
		cout << "\tERROR: \tParameter: \""<< par << "\" is not Exist"<<endl;
		error = true;
	}
	if(error)
		cout << "\t    Use: \"Path Textures\" or\n\t\t \"Coordinates Textures\" or\n\t\t \"Textures Numpollies\"" << endl;
}

void Load::LoadParameters(ifstream &file, int* BegEndTag, int p)
{
	SearchBegihTag(file, BegEndTag);			//ищем начало файла
	
	int j = 0;
	if(p == 1)
	{
		Texturepack.Texture = new PATH[BegEndTag[1]];
		do
		{ 
		ParseConfig(file, Bufer_x);										  
			Path = Bufer_x;
			Texturepack.Texture[j].path = new char[Path.length()+1];
			memcpy(	Texturepack.Texture[j].path, Bufer_x, Path.length()+1);
		}while (++j < BegEndTag[1]);
	}
		
	if(p == 2)
	{
		char NumP[] = "NUMPOLLIES\0";
		char NumL[] = "NUMLEVELS\0";
		bool boolLevel = false;
		bool boolPoll = false;
		unsigned int v = 0;
		do
		{ 	
			ParseConfig(file, Bufer_x, Bufer_y);	
			do{ 
				if(NumP[v] != Bufer_x[v]){
					boolPoll = false;
					break;
				}
					boolPoll = true;
			}while (v++ < strlen(Bufer_x));
			
			v = 0;
			do{ 
				if(NumL[v] != Bufer_x[v]){
					boolLevel = false;
					break;
				}
					boolLevel = true;
			} while (v++ < strlen(Bufer_x));
			
			if(boolPoll == true)
				NumPollies = atoi(Bufer_y);
			if(boolLevel == true)
				NumLevels = atoi(Bufer_y);
		}while (++j < BegEndTag[1] && boolPoll == false && boolLevel == false);	
	}
	
	if(p == 5)
	{
		int* Which_Level_Coord = new int[2];
			
		for ( int loop = 0; loop < NumPollies; ++loop) 
		{
			for ( int vert = 0; vert < 4; ++vert) 
			{
				Which_Level_Coord = ParseConfig(file, Bufer_x, Bufer_y, Bufer_z, Bufer_u, Bufer_v);
				Temp_Level_and_Coord[Which_Level_Coord[0]] = Which_Level_Coord[1];
			}
		}
	
		SearchBegihTag(file, BegEndTag);	
		
		for ( int l = 1; l <= NumLevels; ++l) 
		{
			level[l].Area.num_qauds = Temp_Level_and_Coord[l]/4;			//Присваиваем колво триугольников
			level[l].Area.elem = new QUAD[Temp_Level_and_Coord[l]/4]; 
			
			for ( int loop = 0; loop < level[l].Area.num_qauds; ++loop) 
			{
				for ( int vert = 0; vert < 4; ++vert) 
				{
				ParseConfig(file, Bufer_x, Bufer_y, Bufer_z, Bufer_u, Bufer_v);
					
					level[l].Area.elem[loop].vertex[vert].x = atof(Bufer_x);
					level[l].Area.elem[loop].vertex[vert].y = atof(Bufer_y);
					level[l].Area.elem[loop].vertex[vert].z = atof(Bufer_z);
					level[l].Area.elem[loop].vertex[vert].u = atof(Bufer_u);
					level[l].Area.elem[loop].vertex[vert].v = atof(Bufer_v);
				}
			}
		}
	}
}

void Load::SearchBegihTag(ifstream &file, int* BegEndTag)
{
	int i=0;
	file.seekg(0);
	do   							//находим начало нужного тега
	{ 
	x = new char[64];
	file >> x;
		if(x[0]=='#' )
			i++;
		if(x[0]=='#' || x[0]=='/' )
			file.getline(x, 255, '\n');
	delete[]x;
	} while (	(!file.eof()) && (i != BegEndTag[0]) );
}
		
void Load::ParseConfig(ifstream &file, char* x)
{
	do
	{ 
		file >> x;
		if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' )
				file.getline(x, 255, '\n');
	} while (x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]==' ');
}

void Load::ParseConfig(ifstream &file, char* x, char* y)
{
	do
	{ 
		file >> x;
		if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' )
				file.getline(x, 255, '\n');
		else
			file >> y;
	} while (x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]==' ');
}

int* Load::ParseConfig(ifstream &file, char* x, char* y, char* z, char* u, char* v)
{
	int* LevelLines = new int[2];
	do
	{ 
		file >> x;
		if(x[0]==':' )
		{
			CurrLevel++;
			CurrLines=0;
		}
			
		if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]==':' )
			file.getline(x, 255, '\n');
		else
		{
			file >> y >> z >> u >> v;
			CurrLines ++;
		}	
	} while ( (x[0]==' ') || ((x[0] >='A') && (x[0] <='Z')) || ((x[0] >='a') && (x[0] <='z'))	);
	
	LevelLines[0] = CurrLevel;
	LevelLines[1] = CurrLines;
	
	return LevelLines;
}

#endif