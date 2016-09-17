#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include <fstream>
using namespace std;

#ifndef LOADGRAPHICS_cpp
#define LOADGRAPHICS_cpp

#include "../header/LoadParameters.h"

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.0, 1.0, 0.0);	 // оординаты  ()3 перные но пока что видим 2 оси X и Y.
			
		glBegin(GL_LINES); 
			glVertex3f (0,0,0);    //x,y,z
			glVertex3f (0,0,500); //x,y,z
		glEnd();
		glBegin(GL_LINES); 
			glVertex3f (0,0,0);    //x,y,z
			glVertex3f (0,500,0); //x,y,z
		glEnd();
		glBegin(GL_LINES); 
			glVertex3f (0,0,0);    //x,y,z
			glVertex3f (400,0,0); //x,y,z
		glEnd();
		
		glEnable(GL_TEXTURE_2D);     
		

		glPushMatrix();
			for ( int l = 1; l <= World->StackLevel; ++l) 
			{
			glColor3f(1.0, 1.0, 1.0);	// вадрат на который будем нат€гивать текстуру
				for ( int loop = 0; loop < World->Level[l].Area.num_qauds; ++loop) 
				{
				glBindTexture(GL_TEXTURE_2D, texture_id[loop]);
					glBegin(GL_QUADS);
						for ( int vert = 0; vert < 4; ++vert) 
						{
							float X = World->Level[l].Area.elem[loop].vertex[vert].x; 
							float Y = World->Level[l].Area.elem[loop].vertex[vert].y; 
							float Z = World->Level[l].Area.elem[loop].vertex[vert].z; 
							float U = World->Level[l].Area.elem[loop].vertex[vert].u; 
							float V = World->Level[l].Area.elem[loop].vertex[vert].v;  
							glTexCoord2d(U,V); glVertex3d(X,Y,Z);  
						}
					glEnd(); 
				}
			}	
		glPopMatrix();
			
	glDisable(GL_TEXTURE_2D);

glutSwapBuffers();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-450, 450, -525, 525, 1.0, 0.0);
}

void KeyboardFunc (unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
      glutDestroyWindow(windowID); // ESC pressed, exit the application
      exit(0);
    break;

    default:
      break;
  }
}

#endif
