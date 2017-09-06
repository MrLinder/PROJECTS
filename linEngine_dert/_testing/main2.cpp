#include <GL/glew.h>
#include <GL/freeglut.h>

int window_id;

float xtrans = 0;
float ytrans = 0;
float ztrans = 1;

float xLook = 0;
float yLook = 0;
float zLook = 1;

float pers = 0;

float rotZ = 0.0;



void coord()
{
	glBegin(GL_LINES);
			glColor4f(1.0, 0.0, 1.0, 0.0);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
			glColor4f(1.0, 0.0, 0.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
}

void MainOrtho()
{
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
			glOrtho(-1.0,  1.0, -1.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);	
}


void PolygonMesh(float ih, float iv, float is)		//	ih - horizontal , 		iv - vertical,   	   is - size mesh
{
				for ( int h = 0; h <= ih; ++h) 
				{
					for ( int v = 0; v <= iv; ++v) 
					{
						if(h < ih)
						{
							glBegin(GL_LINES);
								glVertex3f(h*is, v*is, 0.0);		glVertex3f(h*is+is,v*is, 0.0);			//	__	__	__	
							glEnd();
						}
										
						if(v < iv)
						{
							glBegin(GL_LINES);
								glVertex3f(h*is, v*is, 0.0);		glVertex3f(h*is, v*is+is, 0.0);		//	|	|	|
							glEnd();
						}
					}
				}
}

void object(float wx, float wy)
{
	glBegin(GL_POLYGON);
		glVertex3f(-wx, -wy, 0.0);
		glVertex3f(-wx,  wy, 0.0);
		glVertex3f( wx,  wy, 0.0);
		glVertex3f( wx, -wy, 0.0);
	glEnd();
	
	glColor4f(1.0,0.0,1.0,1.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-wx, -wy, 0.0);
		glVertex3f( 0.0, wy, 0.0);
		glVertex3f( wx, -wy, 0.0);
	glEnd();
}

void meshes_before()
{
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
				glTranslatef( -1.0, -1.0, 0);
				gluLookAt(xtrans, ytrans, ztrans+1, xtrans, ytrans, 1, 0, 1, 0);
			
			glMatrixMode(GL_PROJECTION);
				glPushMatrix();
					glLoadIdentity();
						gluPerspective (70+pers, 1, 1, 0);
							glOrtho(-0.5, 0.5, -0.5, 0.5, 1.0, 0.0);
									
							glColor4f(0.0, 1.0, 0.0, 1.0);
							PolygonMesh(30,30,0.1);		
						
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}


void meshes_after()
{
	
}


void display()	
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
			gluPerspective (70+pers, 1, 1, 0);
	
		meshes();	
		
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
					gluLookAt(xtrans, ytrans, ztrans+1, xtrans, ytrans, 1, 0, 1, 0);
					glTranslatef(xtrans, ytrans, 1);
					glColor4f(1.0, 1.0, 1.0, 1.0);
					object(0.09,0.09);
			glPopMatrix();
		
		
		
		glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
					gluPerspective (70+pers, 1, 1, 0);
					glOrtho(0.0, 1.0, 0.0, 1.0, 0.5, 0.1);
		
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
					
					gluLookAt(xtrans, ytrans, 1, xtrans, ytrans, 0, 0, 1, 0);
					
			
		glColor4f(1.0, 0.0, 0.0, 1.0);		
		PolygonMesh(10,10,0.05);		
		
		glBegin(GL_LINES);
			glVertex3f(-1.0,-1.0,0.0);
			glVertex3f(1.0,1.0,0.0);
		glEnd();
		
		
				glMatrixMode(GL_PROJECTION);	
			glPopMatrix();
									
		glMatrixMode(GL_MODELVIEW);		
	glPopMatrix();
	
			
		
		
	glutSwapBuffers();	
}

void keyboard(unsigned char key, int x , int y)
{

	switch (key) 
	{
		case 't' :		yLook+=1; break;
		case 'g' :  	yLook-=1; break;
		case 'h' :  	xLook+=1; break;
		case 'f' :  	xLook-=1; break;
		case 'r' : 	zLook+=1; break;
		case 'y' :  	zLook-=1; break;
		
		case 'a': xtrans-=0.1;			break;
		case 'd': xtrans+=0.1;			break;
		case 'w': ytrans+=0.1;			break; 
		case 's': ytrans-=0.1;			break;
		case 'q': ztrans+=0.1;			break; 
		case 'e': ztrans-=0.1;			break;
		
		case 27: glutDestroyWindow(window_id);			break;
		case 'p': pers+=10;			break;	
		case 'P': pers-=10;			break;		
			
		default:
			break;
	}
	glutPostRedisplay();
}

void Rewrite()
{
	glutPostRedisplay();
	rotZ-=0.5;
}

void init()
{
	MainOrtho();
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(200,0);
	window_id = glutCreateWindow("test");
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(Rewrite);
	
	
	init();
	
	
	 glutMainLoop(); 
	  return 0;
}