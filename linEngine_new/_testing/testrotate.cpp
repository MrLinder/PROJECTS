#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
using namespace std;

float rotZ =0.0;
int by=0, cx=0, cy=0;
char N = '\n';
 
float width_display = 1680;
float hight_display = 1050;

double degre_rotate_z = 0;		//начальное положение обьекта

double p_cur_x = 0;		//текущее положение обьекта
double p_new_x = 0;		//новое положение обьекта

double p_cur_y = 0;
double p_new_y = 0;


void object()
{
	glBegin(GL_TRIpS);
			glColor4f(1.0,0.0,1.0,1.0);
		glVertex2f(-0.25, -0.25);
			glColor4f(1.0,1.0,1.0,1.0);
		glVertex2f( 0.0,   0.25);
			glColor4f(1.0,0.0,1.0,1.0);	
		glVertex2f( 0.25,  -0.25);
	glEnd();
}

void coord()
{
	glColor4f(1.0,1.0,1.0,1.0);
		glBegin(GL_LINES);
			glVertex2f(-1.0, 0.0);
			glVertex2f( 1.0, 0.0);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(0.0,-1.0);
			glVertex2f(0.0, 1.0);
		glEnd();
}

void init()
{
	glClearColor(0.2,0.2,0.2,0.2);
	glMatrixMode(GL_PROJECTION);
		glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 0.0);
	
		
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		coord();
		
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			
				glLoadIdentity();
					if(N == 'x')
						glRotatef(degre_rotate_z-90, 0.0,0.0,-1.0);
		
						object();
			
			glPopMatrix();
		
	glutSwapBuffers();
}

void rewrite()
{
	glutptRedisplay();
	
	/*if(degre_rotate_z <= 90)
		degre_rotate_z+=0.5;
	else
		degre_rotate_z = degre_rotate_z;*/
}

void MousePassivMove (int ax, int ay)
{
	N = '\n';
	
	p_new_x = ax/width_display*360;
	p_new_y = ay/hight_display*360;
	
	
	if (p_new_x > p_cur_x)
    {
        N='x';
		glutptRedisplay();
        degre_rotate_z += 1.8;
    }
	
	if (p_new_x < p_cur_x)
    {
        N='x';
		glutptRedisplay();
        degre_rotate_z -= 1.8;
    }
	
	p_cur_x = p_new_x;
  
  /* if (ax<bx)
    {
        N='x';
		glutptRedisplay();
        rotZ+=1.0;
    }*/
 
   /* if (by>ay)
    {
        N='y';
		glutptRedisplay();
        rotZ-=1.0;
    }
    if (by<ay)
    {
         N='y';
		 glutptRedisplay();
         rotZ+=1.0;
    }*/
	
	/*if (rotZ == 360.0)
        by=ay; rotZ-=360;    */
		

  
    //glLoadIdentity();
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowpition(50, 50);
	glutInitWindowSize(900, 900);
	glutCreateWindow("rotate");
		
	init();
	
	glutDisplayFunc(display);
	glutIdleFunc(rewrite);
	glutPassiveMotionFunc(MousePassivMove);
	
	
	glutMainLoop();
}

