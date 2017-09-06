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

class MsgToDiaplay
{
	char **SysMsgBuffer;
	int loop;
	int StackIdx;
	int UpStackSize;
	int len;
public:	
	MsgToDiaplay();
	~MsgToDiaplay();
	void Send(char*);
	char* Get();
} *SysMsg;

MsgToDiaplay::MsgToDiaplay()
{
	UpStackSize = 1000;
	StackIdx = 0;
	loop = 0;
		
	if(SysMsgBuffer)
		SysMsgBuffer = NULL;
	
	SysMsgBuffer = new char*[UpStackSize];
}

MsgToDiaplay::~MsgToDiaplay()
{
	if(SysMsgBuffer)
		delete[]SysMsgBuffer;
}

void MsgToDiaplay::Send(char* msg)
{
	len = strlen(msg)+1;

	if(SysMsgBuffer[StackIdx])
		SysMsgBuffer[StackIdx] = NULL;
		
		for (loop = 0; loop < len; ++loop) 
			SysMsgBuffer[StackIdx] = new char[len];
			
			for (loop = 0; loop < len; ++loop) 
				SysMsgBuffer[StackIdx][loop] = msg[loop];
			SysMsgBuffer[StackIdx][len] = '\0';

	if(StackIdx != UpStackSize)
		StackIdx++;
	else
		StackIdx=0;
}

char* MsgToDiaplay::Get()
{
	if(!StackIdx){
		StackIdx = 0;
	return '\0';
	}	
		
	return SysMsgBuffer[--StackIdx] ;
}

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


int main()
{
	Convert = new ConverterToOneString();
	SysMsg = new MsgToDiaplay();
	 
	
	/*int s = 1;
	
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s*4, 9.11111, "111231221111111111error1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.22222, "err1112312312321321311111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err1112312312321321111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s*3, 9.55534, "err1112312312321321311111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err1112312312321321111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "erro11123123123213213111111111111r1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s*3, 9.55534, "err1112312312321321311111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err11123123123213213111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err111231231232132113111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "er11123123123213213211111111111ror1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "er111231231232132132111111111111ror1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s*2, 9.55534, "er11123123123213213211111111111ror1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err111231231232132133111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err111231231232132133111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.55534, "err11123123123213213111111111111or1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s, 9.88888, "er111231231232132132111111111111ror1", 12313123));
		SysMsg->Send(Convert->ToOneStr((char*)"%i%f%t%i", s*2, 9.99999, "er111231231232132132111111111111ror1", 12313123));
	*/
	

	
	/*cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;
	cout << SysMsg->Get() << endl;;*/
   
		
		
	for ( int i = 0; i < 100; ++i) 
	{
		SysMsg->Send((char*)"1_11231221111111111error1");
		SysMsg->Send((char*)"2_22222222111111error1");
		SysMsg->Send((char*)"3_werwerewrw3");
		SysMsg->Send((char*)"4_werewew");
		SysMsg->Send((char*)"5_11123dsfsdfsdfsdfsdfsdfdsfsdf1221111111111error1");
		SysMsg->Send((char*)"6_111231221111111111error1");
		SysMsg->Send((char*)"7_111231221111111111error1");
		SysMsg->Send((char*)"8_11123sdfsdfsdfsdfsdfsdf1221111111111error1");
		SysMsg->Send((char*)"9_1112312sdfsdfsdfsdfsdfsdf21111111111error1");
		SysMsg->Send((char*)"10_111231221111111111error1");
		SysMsg->Send((char*)"11_222222222111111error1");
		SysMsg->Send((char*)"12_3werwerewrw3");
		SysMsg->Send((char*)"13_1werewew");
		SysMsg->Send((char*)"14_11123dsfsdfsdfsdfsdfsdfdsfsdf1221111111111error1");
		SysMsg->Send((char*)"15_111231221111111111error1");
	}
		
		
		
		
		
		
	
	char DisplayBuffer[15][1000];	
	int mainloop = 0;
	int i, j;
	
	
	do
	{ 
	int len;
		
		for (i = 0; i < 15; ++i) 
		{
			char *str = SysMsg->Get();
			len = strlen(str)+1;	
			
			for (j = 0; j < len; ++j) 
			{
				DisplayBuffer[i][j] = str[j];
			} 
		} 
		
		
		
		
		
		system("CLS");
		for ( int y = 0; y <15; ++y) 
		{
			for ( int x = 0; x < len; ++x) 
			{
			cout << DisplayBuffer[y][x];
			}
			cout << endl;
		}
		
	

	int wait=0;
		do{ } while (++wait < 100000000);
	} while (++mainloop <= 1000);
	
		
		
		
		
		
		
		
		
		
   
	delete Convert;
	delete SysMsg;
	
 

    return 0;
}
