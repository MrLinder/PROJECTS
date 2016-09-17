#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdarg.h>
#include <sstream>
#include <iomanip>	
using namespace std;

class ConverterToOneString{
	unsigned int ival;		// переменная для поиска типа int
	double fval;				// переменная для поиска типа double
	char* chval;				// переменная для поиска типа char
	int ResultSize;			//размер итогового массива		
	char* ResultsArr;			//результирующий массив	
	int TempSize;			//переменная для хранения размера временного массива
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
	
	va_list arg_ptr;				//Указатель на список не обязательных параметров
	va_start(arg_ptr, format);	//arg_ptr на начало списка необязательных параметров, format - последний обязательный параметр
	
	char *p=format; 
	do{ 								//Указатель который проходит по параметрам пока существует.
		int radix = 10;											//система счисления
		char buffer[10]; 											//буфер для результата
		int size = 0;
		
		char* temp;					//временный массив для float
		std::ostringstream ost;		//форматирование строк
		string result;					//результирующая string строка
		
		if(*p=='%') 													//Если встретится символ %
		{
			switch (*++p) 												//То анализируем следующий за этим симолом символ
			{
				case 'i': ival = va_arg(arg_ptr, unsigned int);		//Если это символ i, то значит параметр int
					ToResultsArr( itoa(ival,buffer,radix) );				//указатель на результат
				break;	
			
				case 'f': fval = va_arg(arg_ptr, double);				//Если это символ f. то значит параметр double
					ost << std::fixed << std::setprecision(5) << fval;	//прочитанный float  конвертируем в string			
					result = ost.str();									//срхраняем результат string
					
					do{} while (result[++size] != '\0');				//посчитаем количество символов
					
					temp = new char[size];								//и создадим временный массив char
					for ( int i = 0; i < size; ++i) 						//Скопируем string в  char
						temp[i] = result[i]; 	
										
					ToResultsArr(temp);									//и отправляем в результирующий массив
					delete[]temp;
				break;
				
				case 't': chval = va_arg(arg_ptr, char*);				//Если это символ t. то значит параметр cahr*
					ToResultsArr(chval);
				break;
			}	
		}
		else
			ToResultsArr(p);
	}while ( *p++);
return ResultsArr;
}

//Функция получает массив, если массив еще не создан то создается первый масив,  
//при получении каждого следующего массива, функция удаояет текущий предворительно сохранив его в память
//затем создает новый конкатенируя старый и новый и так далее.. получается чтото типа стека массивов.
void ConverterToOneString::ToResultsArr(char* res)
{
	if (ResultsArr == NULL )						//Если массив не существует то создаем его размером полученного
	{
		ResultSize = strlen(res);					//Длинна полученного массива
		ResultsArr = new char[ResultSize];		//выделяем память размерностью полученного массива
		for (int j = 0; j < ResultSize; ++j) 	//инициализируем результирующий массив полученным
			ResultsArr[j] = res[j];
	}
	else											//Если массив уже существует 
	{
		char* temparr = new char[TempSize = ResultSize];  			//Сохраняем результирующий массив во временный
		for (int i = 0; i < TempSize; ++i) 
			temparr[i] = ResultsArr[i];
		delete[]ResultsArr;												//Удаляем результирующий массив
			
		ResultsArr = new char[ResultSize = TempSize+strlen(res)+1];	//Создаем результирующий массив с новым размером
		
		int i = 0;
		do 									
		{ 
			ResultsArr[i] = temparr[i];					//записываем старый массив в новый
			
			if(i == TempSize-1) 							//как только старый масив записался				
			{
				ResultsArr[i+1] = ' ';					//ставим пробел в следующую ячейку
			
				int j = i+2;								//начинаем дописывать через пробел
				do 											
				{ 
					 ResultsArr[j] = res[j-i-2]; 			// и дописываем текущий массив к стураму 
				} while (++j <= ResultSize );
				ResultsArr[j] = '\0';						//завершаем масив нулем
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
	unsigned char** DisplayBuffer = new unsigned char*[15];		//количество строк
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

