#include "../header/DisplayParameters.h" 


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#ifndef LOADGRAPHICS_cpp
#define LOADGRAPHICS_cpp

/*Declaration */
void PrintInformation();
void print(int, int, char*, int, int);
/* - - - - - -*/

int fontset; 

void BuildWord()
{
	fontset = glGenLists(256); 	//?aca?ae?oai 256 eiai nieneia ioia?a?aiae?.
	
	float cX(0);
	float cY(0);
	
	for ( int loop = 0; loop < 256; ++loop) 
	{
		cX = (loop % 16) /16.0f;
		cY = 1 - ( (loop / 16) / 16.0f );
		
		glNewList(fontset+loop, GL_COMPILE);	//eiiaiau caienuaaai  a niene aac auiieiaie?	
				glBegin(GL_QUADS);
					glTexCoord2f(cX		 , cY-0.0625f); glVertex2f( 0,  0);	 //ie?iee eaaue
					glTexCoord2f(cX+0.0625f, cY-0.0625f); glVertex2f( 0.16, 0);  //ie?iee i?aaue
					glTexCoord2f(cX+0.0625f, cY		  ); glVertex2f( 0.16, 0.16);	 //aa?oiee i?aaue
					glTexCoord2f(cX		 , cY		  ); glVertex2f( 0,  0.16);	 //aa?oiee eaaue
				glEnd();
			glTranslated(Display->linearinterval,0,0);			//—oou naaeaaai ?oi au aoeau noi?ee ??aii
		glEndList();
	}
}

void MainOrtho()									//??iyeoe? ii oiie?aie?
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, 0.5, -0.5, 0.5, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);		//aica?auaai iiaaeuiiaeaiao? i?iyeoe?(ae? oaianoaa)
}

void PolygonMesh(double ih, double iv, double wv)
{
	glPushMatrix();	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1.0, 0, 1.0, 1.0, 0.0);
		
		double wh = wv*(Display->GetRatioOfWidth());

			for ( double v = 0; v <= iv; ++v) 
			{
				for (  double h = 0; h <= ih; ++h) 
				{
					if(h <= ih-1)
					{
						glBegin(GL_LINES);
							glVertex2f(h*wh+wh, v*wv);		glVertex2f(h*wh, v*wv);
						glEnd();
					}
					if(v <= iv-1)
					{
						glBegin(GL_LINES);
							glVertex2f(h*wh, v*wv+wv);		glVertex2f(h*wh, v*wv);
						glEnd();
					}
				}
			}
	glPopMatrix();	
MainOrtho();	
}	

void coord()
{
	glBegin(GL_LINES);
		glVertex2f(-0.5, 0.0);		
		glVertex2f( 0.5, 0.0);
		glVertex2f( 0.0,-0.5);		
		glVertex2f( 0.0, 0.5);
		glVertex3f( 0.0, 0.0, 10.0);		
		glVertex3f( 0.0, 0.0, -10.0);	
	glEnd();
}

void object(double wx, double wy)
{
	double x = wx*Display->GetRatioOfWidth();

		glBegin(GL_POLYGON);
			glVertex2f(-x/2,-wy/2);		
			glVertex2f(-x/2, wy/2);
			glVertex2f( x/2, wy/2);	
			glVertex2f( x/2,-wy/2);
		glEnd();
}

void UserFrontEnd()
{
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
				glOrtho(0.0, Display->widthScreen, 0.0, Display->hightScreen, 1.0, 0.0);
				
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.0, 1.0);	
		glVertex2f(Display->widthScreen-1.0, 1.0);
		glVertex2f(Display->widthScreen-1.0, Display->hightScreen-1.0);
		glVertex2f(1.0, Display->hightScreen-1.0);
	glEnd();
	
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
				glTranslatef(Display->IndentSubDisplayLeft, Display->IndentSubDisplayTop, 0);
	
		glBegin(GL_LINE_LOOP);
			glVertex2f(1.0, 1.0);	
			glVertex2f(Display->SubSysDisplayWidth, 1.0);
			glVertex2f(Display->SubSysDisplayWidth, Display->SubSysDisplayHight);
			glVertex2f(1.0, Display->SubSysDisplayHight);
		glEnd();
	
	PrintInformation();
	
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void PrintInformation()
{
	glEnable(GL_TEXTURE_2D);

		
		print(90,90,(char*)"OpenGL os the best library of the world", 0, 10);
		
			glColor4f(1.0, 1.0, 1.0, 1.0);
				for ( int i = 0; i < SysMsg->StackIdx; ++i) 
				{
					print(Display->IndentSubDisplayLeft, Display->IndentSubDisplayTop+1000-i*Display->fontinterval, (char*)SysMsg->Get(i), 0, 10);
				}
	glDisable(GL_TEXTURE_2D);
	
}

void print(int x, int y, char* str, int set=0, int fontsize=10)
{
	int FonrSizeHight = Display->hightScreen/100*fontsize;
	int FonrSizeWidth = Display->widthScreen/135*fontsize;
	
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	
	glEnable(GL_BLEND); 				//‚ee??aai niaoeaaiea 
	glDisable(GL_DEPTH_TEST);			//‚u?oaaai oano aeoaeiu
	
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
				glOrtho(0,Display->widthScreen, 0, Display->hightScreen, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
				glTranslated(x,y,0);
				glScalef(FonrSizeWidth, FonrSizeHight, 0);
				glListBase(fontset-32+(128*set));         // ‚uae?aai iaai? neiaieia (0 eee 1)
				glCallLists(strlen(str),GL_BYTE,str); // ?enoai oaeno ia ye?aia

		glMatrixMode(GL_PROJECTION);		
	glPopMatrix();
	
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glDisable(GL_BLEND);  		//‚u?oaaai niaoeaaiea
	glEnable(GL_DEPTH_TEST);		//‚ee??aai oano aeoaeiu
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (70, 1, 1, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Display->xTrans, Display->yTrans, Display->zLook, Display->xTrans, Display->yTrans, 0, 0, 1, 0);
	
	glColor4f(1.0, 1.0, 1.0, 1.0);
	PolygonMesh(10,10,0.15);
		
	glColor4f(0.0, 1.0, 0.0, 1.0);
	coord();
	
	glTranslatef(Display->xTrans, Display->yTrans, 0);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glDisable(GL_DEPTH_TEST);
	object(0.2,0.2);
	
	glTranslatef(Display->xTrans, Display->yTrans, 0);	
	glColor4f(1.0, 0.0, 0.0, 1.0);
	UserFrontEnd();
		
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	Display->widthScreen = w;
	Display->hightScreen = w*Display->GetRatioOfWidth();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,Display->widthScreen,Display->hightScreen);
	
	MainOrtho();
}

void initialize()
{
	BuildWord();
	glClearColor(0.1, 0.1, 0.1, 1.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);   // Ciaoeaaie? ae? iai?ic?a?iinoe, aace?o?ua?n? ia cia?aiee aeuou.
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,Display->widthScreen,Display->hightScreen);
	
	MainOrtho();
}

void KeyboardFunc(unsigned char key, int x, int y)
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

void SkeyboardFunc(int key, int x, int y)
{
	switch(key) 
	{
		case GLUT_KEY_UP:		Display->yTrans+=0.005; break;
		case GLUT_KEY_DOWN:	Display->yTrans-=0.005; break;	
		case GLUT_KEY_LEFT:	Display->xTrans-=0.005; break;
		case GLUT_KEY_RIGHT:	Display->xTrans+=0.005; break;	
	}
	glutPostRedisplay(); 	
}

	








#endif
Status API Training Shop Blog About
© 2016 GitHub, Inc. Terms Privacy Security Contact Help
