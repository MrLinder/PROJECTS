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

TextureParser::TextureParser()		//������������� �������
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
		cout << Begin->key.elem << endl;
}

TypesForParsers::TypesForParsers() 
{ 
	cout<<"TypesForParsers Const"<<endl;
};

TypesForParsers::~TypesForParsers() 
{
	cout<<"~TypesForParsers Dist"<<endl;
};

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
	
	//������� ������� �� �� ���� �� ��������� � ���������� � ���� ����������� ��������
	int i = 0;
	List *Temp = new List();
		Temp->key.elem = new char[str_length];
			for ( ; i < str_length; ++i) 
				Temp->key.elem[i] = name[i];
					Temp->key.elem[i+1] = '\0';
	
	if (Begin == NULL)		//���� ��������� ������ ���� ������ ���� ������� ����� ������.
	{
		Begin = Temp;
		End = Temp;
	} 
	else					//���� ��� ����� ��������� � ����� ������
	{
		End -> next = Temp;	
		Temp -> prev = End;
		End = End->next;
	}				
}

void TextureParser::Texture_file(char* texture_file)
{
	fstream file((char*)texture_file, ios::in | ios::out | ios::app);			//��������� ����� 
	if (!file.is_open()){															//������� �� ������������� �����
	  cout << "file " << texture_file << "is not exsist!" << endl;				//���� ��� �� �������
	  exit(1);
	}
	
	pList = Begin;																//�������� ��������� ��� ���������� ��������
	
	if (!pList){
	  cout << "There is no one texture file!" << endl;
	  file.close();
	  return;
	}
	else
	{
		List* pList = Begin;		
		do {  																		//���� ������� �� ������ ����������� ������
				cout << "File: " << pList->key.elem << "\t-available!" <<endl;
				
				if (pList)
					pList = pList->next;
			} while (pList);
	}
	
	file.seekg(0, ios::end);													//������������ � ����� �����
	long file_size = file.tellg();											//������ ������� ������� get
	
	if (file_size == 0 && pList)													//���� ������� ����� ����, ����� ���� ����.  � ����� ������
	{
		write = true;																// �������� ������������ ��������� "�������� � ������"
		fstream file((char*)texture_file, ios::in | ios::out | ios::app);		//��������� ����� � �������� ��� ����������� � ����
				
		 do {  																		//���� ������� �� ������ ����������� ������
				 char *pFlush = pList->key.elem;										
						
				 while(*pFlush)
						file.put(*pFlush++);								//��������� ���������� ������
				 if (pList->next)
					file << '\n';											// � � ����� ������� ���� ��� �� ��������� ������
				
				cout << "write: " << pList->key.elem << endl;
				
				if (pList)
					pList = pList->next;
			} while (pList);
	}  	
		
	int NumLines = countElements((char*)texture_file); 
	
	if (!write && pList)													// �������� ������������ ��������� "�������� � ������"
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

#endif