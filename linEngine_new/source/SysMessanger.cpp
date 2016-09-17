
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
	
	va_list arg_ptr;				//��������� �� ������ �� ������������ ����������
	va_start(arg_ptr, format);	//arg_ptr �� ������ ������ �������������� ����������, format - ��������� ������������ ��������
	
	char *p=format; 
	do{ 								//��������� ������� �������� �� ���������� ���� ����������.
		int radix = 10;				//������� ���������
		char buffer[1000]; 			//����� ��� ����������
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




#endif	
	
	
	
	