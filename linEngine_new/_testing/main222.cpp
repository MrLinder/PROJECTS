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
