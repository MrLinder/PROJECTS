
#ifndef SYSMSG_CPP
#define SYSMSG_CPP

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
	{
		for ( int i = 0; i < UpStackSize; ++i) 
		{
			if(SysMsgBuffer[i])
				delete[]SysMsgBuffer[i];
		}
	}

}

void MsgToDiaplay::Send(char* msg)
{
	len = strlen(msg)+1;

	if(SysMsgBuffer[StackIdx])
		SysMsgBuffer[StackIdx] = NULL;
		
		for (loop = 0; loop < len; ++loop) 
			SysMsgBuffer[StackIdx] = new char[300];
			
			for (loop = 0; loop < len; ++loop) 
				SysMsgBuffer[StackIdx][loop] = msg[loop];
			SysMsgBuffer[StackIdx][len+1] = '\0';

	if(StackIdx != UpStackSize)
		StackIdx++;
	else
		StackIdx=0;
}

char* MsgToDiaplay::Get(int n)
{
	if(!StackIdx){
		StackIdx = 0;
	return '\0';
	}	
		
	return SysMsgBuffer[n] ;
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
		int radix = 10;				//система счисления
		char buffer[1000]; 			//буфер для результата
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




#endif	
	
	
	
	