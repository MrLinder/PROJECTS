#include "header/SysMessanger.h"
#include "header/LoadParameters.h"
#include "header/DisplayParameters.h"

int main(int argc, char** argv)
{
	SysMsg = new MsgToDiaplay();
	Convert = new ConverterToOneString();
	Display = Dp = new Interface(); 
		
	glutInit(&argc, argv);				
	//инициаaлизация GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);		
	glutInitWindowSize(1,1);
	glutInitWindowPosition(0,0); 
 	windowID = glutCreateWindow("Load Area 3D House in OpenGl");	
		
	Display->SetScreen();     //  () - full Screen ; 4 =  how to divide Minimize Screen
			
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);	
	glutSpecialFunc(SkeyboardFunc);
	glutIdleFunc(Rewrite);
	
	//glutEntryFunc(LeaveArray);					//void glutEntryFunc(void (*func)(int state));
	glutMouseFunc(MousePressed);					//void glutMouseFunc(void (*func)(int button, int state, int x, int y));
	//glutMotionFunc(MouseActiveMovePress);		//void glutMotionFunc(void (*func) (int x,int y));
	glutPassiveMotionFunc(MousePassivMove);		//void glutPassiveMotionFunc(void (*func) (int x, int y));	
		
	
	
	Initialize();
 	
	Load *Config = new Load((char*)"config_world.txt");			//Подключаем конфиг и окрываем поток
			Config->Read((char*)"Textures Path", 1);				//Прочитать и загрузить текстуры
			Config->Read((char*)"Textures Numpollies", 2);		//Проситать и загрузить параметры полей
			Config->Read((char*)"Textures Coordinates", 5);		//Прочитать и загрузить координаты текстур	
		
						 
		World = new Create(*Config);
			World->Include(Config->level, 1);
			World->Include(Config->level, 2);
			World->Include(Config->level, 3);
			World->Include(Config->level, 4);
		
	glutMainLoop();
	
	//delete Config;
	//delete World;

	
	delete Convert;
	delete SysMsg;
	
	return EXIT_SUCCESS;
}




