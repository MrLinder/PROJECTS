
#include  "header/LoadParameters.h"


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	Load *Config = new Load((char*)"config_world.txt");	//���������� ������ � �������� �����
			Config->Read((char*)"Textures Path", 1);				//��������� � ��������� ��������
			Config->Read((char*)"Textures Numpollies", 2);		//��������� � ��������� ��������� �����
			Config->Read((char*)"Textures Coordinates", 5);		//��������� � ��������� ���������� �������
	
	glutInit(&argc, argv);											//������������� GLUT
		
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);		
	glutInitWindowSize(950, 937);
	glutInitWindowPosition(150,0);
 	windowID = glutCreateWindow("Load Area 3D House in OpenGl");	
	
	glutFullScreen(); 
	
		World = new Create(*Config);
			World->Include(Config->level, 1);
			//World->Include(Config->level, 2);
			//World->Include(Config->level, 3);
			//World->Include(Config->level, 4);
	
	glutDisplayFunc(Display);  
	glutKeyboardFunc(KeyboardFunc);	
	
	Init();
	
	glutMainLoop();

	delete Config;
	delete World;
	return EXIT_SUCCESS;
}




