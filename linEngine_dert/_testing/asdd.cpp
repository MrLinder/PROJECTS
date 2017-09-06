#include "iostream"
#include "windows.h"
#include <GL/glut.h>
#include <GL/glaux.h>
using namespace std;
 
float WinW = 400.0;
float WinH = 400.0;
float rotX = 0.0;
float rotY = 0.0;
int bx=0, by=0, cx=0, cy=0;
char N = '\n';					//будем выбирать что вращать
 

void object()
{
	  glutWireTeapot(20);
			glTranslatef(40.0, 0.0, -100.0);
		   glutWireTeapot(20);
}

void Draw ()
{
   // glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_DEPTH_BITS);
   
		  if (N=='x')
				glRotatef(rotX, 0.0, 1.0, 0.0);
		  
		  if (N=='y')
				glRotatef(rotY, 1.0, 0.0, 0.0);
		   
		  object();
    
		//glDisable(GL_DEPTH_BITS);
    glutSwapBuffers();
}
 
void Timer (int)
{
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 0);
}
 
void MouseMovePressed (int ax, int ay)
{
    cout << ax << " " << ay << endl;
    N='\n';
    if (ax>bx)
    {
        N='x';
        Draw();
        rotX+=1.0;
    }
    if (ax<bx)
    {
        N='x';
        Draw();
        rotX-=1.0;
    }
 
    if (by>ay)
    {
        N='y';
        Draw();
        rotY-=1.0;
    }
    if (by<ay)
    {
         N='y';
         Draw();
         rotY+=1.0;
     }
  if (rotX == 360.0)
       rotX-=360;
   if (rotY == 360.0)
      rotY-=360;
    bx=ax;
    by=ay;
    glLoadIdentity();
}
 
 
void Initialize ()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0 ,400.0);
    glMatrixMode(GL_MODELVIEW);
 
}
 
 
 
int main(int argc, char* argv[])
    {
        glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
        glutInitWindowSize(WinW, WinH);
        glutInitWindowPosition(100, 200);
    glutCreateWindow("GLRect");
    glutDisplayFunc(Draw);
//  glutTimerFunc(500, Timer, 0);
    glutMotionFunc(MouseMovePressed);
    Initialize();
    glutMainLoop();
 
        return 0;
    }