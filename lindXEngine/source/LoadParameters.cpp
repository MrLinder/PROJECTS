
#ifndef LOADPARAMETERS_CPP
#define LOADPARAMETERS_CPP

Bufers::Bufers()
{
	cout<<"Buffers Const"<<endl;
}

Bufers::~Bufers()
{
	cout<<"~Buffers Dist"<<endl;
}	

Base::Base()
{
	cout<<"Base Const"<<endl;
}

Base::~Base()
{
	cout<<"~Base Distr"<<endl;
}

TextureParser::TextureParser()		//инициализация парсера
{
	cout<<"TextureParse Const"<<endl;
	mask = new char[6];
	mask = (char*)"/*.bmp\0";
	count_files = 0;
	Bufer_x[0] = '\0';
	Begin = End = NULL;
	write = false;
}

TextureParser::~TextureParser()				
{
	cout<<"~TextureParse Dist"<<endl;
	
	List* pDel;
	do{ 
		pDel = Begin;
		if(Begin -> next != NULL)
			Begin = Begin -> next;
		delete pDel;
		Begin -> prev = NULL;
	} while (pDel != End );
}

TypesForParsers::TypesForParsers()
{
	cout<<"TypesForParsers Const"<<endl;
}

TypesForParsers::~TypesForParsers()
{
	cout<<"~TypesForParsers Dist"<<endl;
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
		do {
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

void TextureParser::CreateTextureConfig(char* texture_file)
{
	ConfigFile = new char[strlen(texture_file)+1];
	for (unsigned int f = 0; f < strlen(texture_file)+1 ; ++f) 
		ConfigFile[f] = texture_file[f];
	ConfigFile[strlen(texture_file)+1] ='\0';
	
	fstream file((char*)texture_file, ios::in | ios::out | ios::app);			//открываем поток 
	if (!file.is_open()){															//роверка на существование файла
	  cout << "file " << texture_file << "is not exsist!" << endl;				//если нет то создать
	  exit(1);
	}
	
	pList = Begin;																//копируем указатель для дальнейших операций
	
	if (!pList){
	  cout << "There is no one texture file!" << endl;
	  file.close();
	  return;
	}
	else
	{
		List* pList = Begin;		
		do {  																		//цикл прохода по списку прочитанных файлов
				cout << "File: " << pList->key.elem << "\t-available!" <<endl;
				
				if (pList)
					pList = pList->next;
			} while (pList);
	}
	
	file.seekg(0, ios::end);													//перемещаемся в конец файла
	long file_size = file.tellg();											//запрос позиции курсора get
	
	if (file_size == 0 && pList)													//если позиция равна нулю, тогда файл пуст.  и поток закрыт
	{
		write = true;																// исключем дублирование опрерации "проверки и записи"
		fstream file((char*)texture_file, ios::in | ios::out | ios::app);		//открываем поток и скидывам все прочитанное в файл
				
		 do {  																		//цикл прохода по списку прочитанных файлов
				 char *pFlush = pList->key.elem;										
						
				 while(*pFlush)
						file.put(*pFlush++);								//побайтово записываем строку
				 if (pList->next)
					file << '\n';											// и в конец коретку если это не последняя запись
				
				cout << "write: " << pList->key.elem << endl;
				
				if (pList)
					pList = pList->next;
			} while (pList);
	}  	
		
	int NumLines = countElements((char*)texture_file); 
	
	if (!write && pList)													// исключем дублирование опрерации "проверки и записи"
	{
		do{ 
				int i = NumLines;
				file.seekg(0, ios::beg);
				
				 do{  
						parseConfig(file, Bufer_x);		
				
						bool equal = chkEqual(pList->key.elem, Bufer_x);
									
						if ( equal == true)
							break;
								
						if ((i <= 0 && equal == false) )
						{
							char* pFlush = pList->key.elem;
							
							cout << "Add new Files: " << pFlush << endl;
							
							file.seekg(0, ios::end);
			
							if (Bufer_x[NumLines] != '\n')
								file <<'\n';
							 
							 while(*pFlush)
								file.put(*pFlush++);
						} 
					} while (i-- != 0);
				if (pList)
					pList = pList->next;
			} while (pList);
	}	
	file.close();
}

int TextureParser::countElements(char* texture_file)
{
	int count = 0;
	fstream file((char*)texture_file, ios::in | ios::binary);

	do{ 
		parseConfig(file, Bufer_x);
		if(!file.eof())
			count++;
	} while (!file.eof() );
	
	file.close();
	
	return count;
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

void TextureParser::parseConfig(fstream &file, char* x)
{
	do
	{ 
		file >> x;
			if(x[0]=='/' || x[0]=='\n' || x[0]=='\0' )
				file.getline(x, 255, '\n');
	} while (x[0]=='/' || x[0]=='\n' || x[0]=='\0' || x[0]==' ' || x[0]==':');
}

Load::Load(char* p)
{
	cout << "Load Const"<< endl;
	
	error = false;
	NumPollies = 0;
	NumLevels = 0;
	
	config_file = new char[strlen(p)+1];
	memcpy(config_file , p, strlen(p)+1);
	
	/* ------- ‘интаксис файла конфигурации -------*/
	// теги начала и концца парметров с путЯми к текстурам
	B_texture = "Begin_textures";
	E_texture = "End_textures";
	
	// теги начала и концца парметров с координатами текстур
	B_coord = "Begin_coordinates";
	E_coord = "End_coordinates";
	
	B_Numpoll = "Begin_Numpollies";
	E_Numpoll = "End_Numpollies";
	
	PassNumTextur = new int[2];			//Љоличество строк до тега и после до закрывающего 
	PassNumCoord  = new int[2];			//Љоличество строк до тега и после до закрывающего 
	PassNumPoll = new int[2];				//Љоличество строк до тега и после до закрывающего 

	CurrLevel = 0;
	CurrLines = 0;
	
	cout << "%t%t"<< "Name config file: "<< config_file<<endl;
	cout << " \0"<< endl;
}

Load::~Load()
{
	cout << "~Load Dist"<< endl;
	cout << "Distruct load..." << endl;
	cout <<" \0"<< endl;
	delete config_file;
	delete what_read;
}

void Load::Include(char* FileName)
{
	texture_file = new char[strlen(FileName)+1];
	for (unsigned int f = 0; f < strlen(FileName)+1 ; ++f) 
		texture_file[f] = FileName[f];
	texture_file[strlen(FileName)+1] ='\0';
}

void Load::Read(char* read, int ReadStrPar)	//”ункциЯ определЯет какой блок параметров читать и запускает парсинг
{
	what_read = new char(strlen(read)+1);	//‘охранЯем параметр парсинга
	what_read = read;
	if(Check_parameter(what_read)) 			//Џроверка на правильность введенного параметра
	{
		Info_error(what_read);				//‚ывести информацию о возможной ошибке(можно убрать)
		exit(1);		
	}

	char* path_file;							//определЯем какой файл читать (текстуры или конфигурацию мира)
	if(what_read == (char*)"Textures Path")
		path_file = texture_file;
	else
		path_file = config_file;
	
	if(ReadStrPar < 1 || 5 < ReadStrPar)    //проверка на количество читаемых параметров
	{
		cout << "%t%i%t"<< "("<< ReadStrPar<< ")"<< endl;	
		cout <<"-Invalid value for the number of parameters to be read."<< endl;		
		cout <<"Use values from (1) to (5). But this doesn't guarantee the accuracy of reading."<< endl;		
		cout <<"Therefore always check the number of parameters to read in config file:"<< endl;		
		cout <<"%t%t%t"<< "("<< path_file << ")"<<endl;;	
	exit(1);
	}
		
	ifstream file((char*)path_file, ios::in);	//открываем поток
	if(!file.is_open()) 								//проверка на существование файла
	{
		cout <<"file with name: \"" << path_file  <<"\" is not exist or have other name."<<endl;
		cout << "%t%t%t"<< "file with name: \""<< path_file<< "\""<< endl;	
		cout <<"is not exist or have other name."<< endl;
	exit(1);
	}
	
	//Ћпредеоение синтаксиса тегов в соответвии с выбранным параметром парсинга
	if(what_read == (char*)"Textures Path")
	{
		cout << "Textures Path is Reading..."<< endl;
		cout << " \0"<< endl;
		
		Begin_param = B_texture;
		End_param = E_texture;
		PassNumTextur = CheckAndCountPar(file);					//Љоличество текстур
		LoadParameters(file, PassNumTextur, ReadStrPar);		//Џоток, Џараметры поиска и чтениЯ, количество параметров в троке
		
		for ( int j = 0; j < PassNumTextur[1]; ++j) 
			cout << Texturepack.Texture[j].path << endl;;
	}
	if(what_read == (char*)"Textures Numpollies")
	{		
		cout <<" \0"<< endl;
		cout <<"Textures Numpollies is Reading..."<< endl;
		cout <<" \0"<< endl;
		
		Begin_param = B_Numpoll;
		End_param = E_Numpoll;
		PassNumPoll = CheckAndCountPar(file);			//Љоличество параметров
		LoadParameters(file, PassNumPoll, ReadStrPar);	
	}
	if(what_read == (char*)"Textures Coordinates")
	{
		cout << "Textures Coordinates is Reading..."<<endl;
		cout << " \0"<< endl; 
		
		Begin_param = B_coord;
		End_param = E_coord;
		PassNumCoord = CheckAndCountPar(file);		//Љоличество координатных параметров
		
			level = new LEVELS[NumLevels+1];				//выделЯем памЯть длЯ уровней
			Temp_Level_and_Coord = new int[NumLevels+1];		//‚ременнаЯ
	
		LoadParameters(file, PassNumCoord, ReadStrPar);	
	}
	file.close();
}

bool Load::Check_parameter(char* par)			//Џроверка коректности запроса параметров
{
	if(par == (char*)"Textures Path" || par == (char*)"Textures Coordinates" || par == (char*)"Textures Numpollies" )
		return false;
	else if(par == (char*)"")
		return true;
	else
		return true;
}

void Load::Info_error(char* par)				//€нформациЯ об ошибках при запросе параметров
{
	if(par == (char*)"Textures Path" || par == (char*)"Textures Coordinates" || par == (char*)"Textures Numpollies" )
	{
		 cout << "%t%t%t%t" << "\"" << par << "\"" << "is right!"<<endl;
	}
	else if(par == (char*)"")
	{
		cout << "You do not specify any parameters"<<endl;
		error = true;
	}
	else
	{
		cout << "%t%t%t%t"<< "ERROR"<< "Parameter: \""<< par <<"\" is not Exist"<<endl;
		error = true;
	}
	if(error)
		cout << "Use: \"Path Textures\" or \"Coordinates Textures\" or \"Textures Numpollies\""<<endl;
}

int* Load::CheckAndCountPar(ifstream &fcount) 	//Џроверка синтаксисса конфига и подсчет параметров
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
				cout <<"ERROR!: Tag with the name: "<<endl;
				cout <<"%t%t%t"<< "\"#"<< "Begin_param"<< "\"is not found!"<< endl;	
				cout <<"or set isn't correct - it means impossible to determine parameters."<< endl;
				cout <<"Process cannot continue..."<<endl;
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
	
	bool DefEndParam = false; 	//длЯ сообщениЯ об ошибке (достигнут конец файла - закрывающего параметра нет)
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
			level[l].Area.num_qauds = Temp_Level_and_Coord[l]/4;			//Џрисваиваем колво триугольников
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