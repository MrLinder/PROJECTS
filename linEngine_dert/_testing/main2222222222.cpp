#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdarg.h>
#include <sstream>
#include <iomanip>	
using namespace std;

class ConverterToOneString{
	unsigned int ival;		// ���������� ��� ������ ���� int
	double fval;				// ���������� ��� ������ ���� double
	char* chval;				// ���������� ��� ������ ���� char
	int ResultSize;			//������ ��������� �������		
	char* ResultsArr;			//�������������� ������	
	int TempSize;			//���������� ��� �������� ������� ���������� �������
public:
	ConverterToOneString();
	~ConverterToOneString();	
	char* ToOneStr(char* format, ...);
	void ToResultsArr(char*);
} *Convert;

ConverterToOneString::ConverterToOneString() 
{
	cout << "const" << endl;
}		
	
ConverterToOneString::~ConverterToOneString() 
{
	if(ResultsArr)
		delete[]ResultsArr;
} 	

char* ConverterToOneString::ToOneStr(char* format, ...)
{
	ival = 0;	
	fval = 0;			
	chval = new char();				
	ResultsArr = NULL;	
	
	va_list arg_ptr;				//��������� �� ������ �� ������������ ����������
	va_start(arg_ptr, format);	//arg_ptr �� ������ ������ �������������� ����������, format - ��������� ������������ ��������
	
	char *p=format; 
	do{ 								//��������� ������� �������� �� ���������� ���� ����������.
		int radix = 10;											//������� ���������
		char buffer[10]; 											//����� ��� ����������
		int size = 0;
		
		char* temp;					//��������� ������ ��� float
		std::ostringstream ost;		//�������������� �����
		string result;					//�������������� string ������
		
		if(*p=='%') 													//���� ���������� ������ %
		{
			switch (*++p) 												//�� ����������� ��������� �� ���� ������� ������
			{
				case 'i': ival = va_arg(arg_ptr, unsigned int);		//���� ��� ������ i, �� ������ �������� int
					ToResultsArr( itoa(ival,buffer,radix) );				//��������� �� ���������
				break;	
			
				case 'f': fval = va_arg(arg_ptr, double);				//���� ��� ������ f. �� ������ �������� double
					ost << std::fixed << std::setprecision(5) << fval;	//����������� float  ������������ � string			
					result = ost.str();									//��������� ��������� string
					
					do{} while (result[++size] != '\0');				//��������� ���������� ��������
					
					temp = new char[size];								//� �������� ��������� ������ char
					for ( int i = 0; i < size; ++i) 						//��������� string �  char
						temp[i] = result[i]; 	
										
					ToResultsArr(temp);									//� ���������� � �������������� ������
					delete[]temp;
				break;
				
				case 't': chval = va_arg(arg_ptr, char*);				//���� ��� ������ t. �� ������ �������� cahr*
					ToResultsArr(chval);
				break;
			}	
		}
		else
			ToResultsArr(p);
	}while ( *p++);
return ResultsArr;
}

//������� �������� ������, ���� ������ ��� �� ������ �� ��������� ������ �����,  
//��� ��������� ������� ���������� �������, ������� ������� ������� �������������� �������� ��� � ������
//����� ������� ����� ������������ ������ � ����� � ��� �����.. ���������� ����� ���� ����� ��������.
void ConverterToOneString::ToResultsArr(char* res)
{
	if (ResultsArr == NULL )						//���� ������ �� ���������� �� ������� ��� �������� �����������
	{
		ResultSize = strlen(res);					//������ ����������� �������
		ResultsArr = new char[ResultSize];		//�������� ������ ������������ ����������� �������
		for (int j = 0; j < ResultSize; ++j) 	//�������������� �������������� ������ ����������
			ResultsArr[j] = res[j];
	}
	else											//���� ������ ��� ���������� 
	{
		char* temparr = new char[TempSize = ResultSize];  			//��������� �������������� ������ �� ���������
		for (int i = 0; i < TempSize; ++i) 
			temparr[i] = ResultsArr[i];
		delete[]ResultsArr;												//������� �������������� ������
			
		ResultsArr = new char[ResultSize = TempSize+strlen(res)+1];	//������� �������������� ������ � ����� ��������
		
		int i = 0;
		do 									
		{ 
			ResultsArr[i] = temparr[i];					//���������� ������ ������ � �����
			
			if(i == TempSize-1) 							//��� ������ ������ ����� ���������				
			{
				ResultsArr[i+1] = ' ';					//������ ������ � ��������� ������
			
				int j = i+2;								//�������� ���������� ����� ������
				do 											
				{ 
					 ResultsArr[j] = res[j-i-2]; 			// � ���������� ������� ������ � ������� 
				} while (++j <= ResultSize );
				ResultsArr[j] = '\0';						//��������� ����� �����
			}
		} while (++i < TempSize);
	delete[]temparr;
	}
}

class Base
{
protected:
	struct Data
	{
		bool critical;
		bool warning;
		unsigned char* msg;
		Data(){critical=warning=false;}
	};
			
	struct Node
	{
		Data* key;
		Node* next;
		Node* temp;
		Node* prev;
		Node(){next=prev=temp=NULL;}
	};
	
};

class MsgToDisplay:protected Base
{
private:	
	Node *Begin, *Temp, *End, *PopBgn;
	char* err_critical;
	char* err_warning;
	int first_run;
public:
	void Send(char*, char*);
	bool CheckEqilArr(char*, char*);
	unsigned char *GetDispalyMsg(char*);
	unsigned char *GetCategoryError();
	void show();
	MsgToDisplay();    	
	~MsgToDisplay();	
} *MsgSys;

MsgToDisplay::MsgToDisplay () 
{
	cout << "Const MsgToDisplay" << endl; 
	first_run = 0;
	err_critical = (char*)"critical";
	err_warning = (char*)"warning";
	Begin = Temp = End = NULL; 
}

MsgToDisplay::~MsgToDisplay() 
{
	cout << "Dist MsgToDisplay" << endl;
	if(Begin)
		delete Begin;
	if(Temp)
		delete Temp;
	if(End)
		delete End;
	if(PopBgn)
		delete PopBgn;

} 	

bool MsgToDisplay::CheckEqilArr(char* a, char* b)
{
	if(a == '\0')
		return false;	
	int n = strlen(b);
	int j = 0;
	
	do{ 
		if(a[j] != b[j])
			return false;	
	}while (j++ <= n);
return true;	
}

void MsgToDisplay::Send(char* message='\0', char* error='\0')
{
	int j, n;
	j = n = 0;
	
	if(message != '\0' )
	{
		n = strlen(message)+1;
		
		if(Temp != NULL)
		{
			Temp -> next = new Node();
				Node* Tmp_nx = Temp->next;
					Tmp_nx -> key = new Data();
						Tmp_nx -> key -> msg = new unsigned char[n];
					do{
						Tmp_nx->key->msg[j] = message[j];
					}while (j++ < n);
					Tmp_nx->key->msg[n+1] = '\0';
				Tmp_nx->prev = Temp;
			Temp = End = Tmp_nx;
		}
		
		if(Temp == NULL)
		{
			Temp = Begin = End = new Node();
				Temp->key = new Data();
					Temp->key->msg = new unsigned char[n];
				do{
					Temp->key->msg[j] = message[j];
				}while (j++ < n);
				Temp->key->msg[n+1] = '\0';
			Begin = PopBgn = End = Temp;
		}
		
			if(error != '\0' )
			{	
				n = strlen(error)+1;
				j=0;	
				while(j++ < n)
				{
					if(error[j] != err_critical[j])
					{
						Temp->key->warning = true;
						Temp->key->critical = false;
						break;
					}	
						
					if(error[j] != err_warning[j])
					{
						Temp->key->critical = true;
						Temp->key->warning = false;
						break;
					}	
				};
			}
	}
}

unsigned char *MsgToDisplay::GetDispalyMsg(char* course = '\0')
{
	if(first_run > 0 && PopBgn->next != NULL && CheckEqilArr(course, (char*)"next"))
		PopBgn = PopBgn->next;
	else if(!PopBgn->next)
		return NULL;
	
		first_run++;
	return PopBgn->key->msg;
}
	
unsigned char* MsgToDisplay::GetCategoryError()
{
	if(!PopBgn->next -> key -> critical && !PopBgn->next -> key -> warning)
		return (unsigned char*)" green";
	
	if (PopBgn->next -> key -> warning)
		return  (unsigned char*)" yellow"; 
		
	return (unsigned char*)" red"; 
}
		
int main() 
{
	Convert = new ConverterToOneString();
	MsgSys = new MsgToDisplay();
	
	for ( int i = 0; i < 10; ++i) 
	{
		MsgSys->Send();
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", i, 9.55534, "errerroerroerroerroerroerroerrrroerroerroerroerroerroerroerroor1", 12313123));
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", i, 9.55534, "texterroerroerroerroerroerroerroerroerroerroerroerroerrouring", 12313123));
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "errerroerroerroerroeroerroerroerroerroerroerroerroerroerroerroerroor2", 12313123), (char*)"warning");
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "erroerroerroerroerroerroerroerroerroerroerroerroerroerror3", 12313123), (char*)"critical");
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "errerroerroerroerroerroerroerroor4", 12313123), (char*)"critical");
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "tererroerroerroerroerroerroerroerroerroror5", 12313123), (char*)"critical");	
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "tererroerroerroerrorroerroerroerroerroerroerroerroerroerroerroerroerroerroerroror6", 12313123));
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "ererroerroerroerroerroerroerroerroerroerroerroerroerroerroerroerroror7", 12313123));
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "ererroerroerroerroerroerroerroerroror8", 12313123), (char*)"critical");	
		MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "erroerroerroerroerrorroerroerroerroerroerroerroerroerroerroerroerroerroerroerroerror9", 12313123), (char*)"warning");
	}
	
	/*MsgSys->Send();
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error1", 12313123));
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "texturing", 12313123));
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error2", 12313123), (char*)"warning");
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error3", 12313123), (char*)"critical");
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error4", 12313123), (char*)"critical");
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "terror5", 12313123), (char*)"critical");	
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "terror6", 12313123));
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error7", 12313123));
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error8", 12313123), (char*)"critical");	
	MsgSys->Send(Convert->ToOneStr((char*)"%i%f%t%i", 12345678, 9.55534, "error9", 12313123), (char*)"warning");*/
	
		
		
		/*
	
	do
	{ 
		cout << MsgSys-> GetDispalyMsg((char*)"next") << " " << MsgSys -> GetCategoryError() <<endl;	
	}while(MsgSys->GetDispalyMsg());*/
	
	
	
	/*int numstr = 15;
		
	int len = 1;
	unsigned char** DisplayBuffer = new unsigned char*[15];		//���������� �����
		for (int loop = 0; loop <= 15; ++loop) 
			DisplayBuffer[loop] = new unsigned char[len];
		
		for ( int i = 0; i <= len; ++i) 
			DisplayBuffer[i] = '\0';
				
		
	int mainloop = 0;
	do
	{ 
				
		
		for ( int j = 0; j <= numstr; ++j) 
		{
			unsigned char* str = MsgSys->GetDispalyMsg((char*)"next");
			len = strlen((const char*)MsgSys->GetDispalyMsg());
			
			DisplayBuffer[j] = new unsigned char[len];
			
			for ( int i = 0; i <= len; ++i) 
			{
				DisplayBuffer[j][i] = str[i];	
			}	
		}		
		
		
		system("CLS");
		
		
		for ( int j = 0; j <= numstr; ++j) 
		{
			
				cout << DisplayBuffer[j];	
		
		cout << endl;
		}		
		
		
		
		
		int wait = 0;
		do{ } while (++wait <= 10000000);
	} while (++mainloop <= 1000);*/
	
	

	
		
		
	
	
	
	
	
	
	//delete MsgSys;
	//delete Convert;
	
	return 0;
}

