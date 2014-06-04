#include<stdlib.h>
#include<GL\glut.h>
#include<time.h>
#include <iostream>
using namespace  std;
class particle
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat _speed;
	GLfloat xd,zd;
	GLfloat alpha;
	GLfloat angle;
	bool move;
	GLuint display_list;
public:
	particle(){}
	particle(int s,int h){
	}
	GLuint createDL()//雪花列表
	{
		GLuint DL;
		DL = glGenLists(1);
		glNewList(DL,GL_COMPILE); 
		drawSnow();//画雪花
		glEndList();
		return DL;
	}
	void init()//初始化
	{
		display_list = createDL();
		_speed = 0.05;
		alpha = 1;
		angle = 0;
		//age = 40/_speed;
		//srand((unsigned)time(NULL));
		x = rand()%200-100;
		y = 40;
		z= rand()%200-100;
		int fator = 3;
		xd = rand()/(double)(RAND_MAX*10);;
		zd = rand()/(double)(RAND_MAX*10);
		move = true;
	}
	void drawedge()
	{
		//glBegin(GL_QUADS);
		//cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
		/*
		glVertex3f(x, y,z);
		glVertex3f(x+0.2, y,z);
		glVertex3f(x+0.2, y+0.6,z);
		glVertex3f(x, y+0.6,z);
		*/
		glColor3f(0.70f, 0.70f, 1.0f); 
		glBegin(GL_POLYGON); 
		glVertex2f(0.0f, 0.0300f); 
		glVertex2f(0.0f, 00.0f); 
		glVertex2f(0.2600f, 00.0f); 
		glVertex2f(0.2500f, 0.0300f); 
		glEnd(); 
		glPushAttrib(GL_CURRENT_COLOR); 
		glBegin(GL_POLYGON); 
		glVertex2f(0.2100f, 0.0f); 
		glColor3f(1.0f,1.0f,1.0f); 
		glVertex2f(0.3400f, 0.1800f); 
		glVertex2f(0.3700f, 0.1800f); 
		glColor3f(0.70f, 0.70f, 1.0f); 
		glVertex2f(0.2400f, 0.0f); 
		glEnd(); 
		glPopAttrib(); 
		glBegin(GL_POLYGON); 
		glVertex2f(0.2600f, 0.0f); 
		glVertex2f(0.2600f, 0.0300f); 
		glVertex2f(0.4300f, 0.0300f); 
		glVertex2f(0.4000f, 0.0f); 
		glEnd(); 
		glBegin(GL_POLYGON); 
		glVertex2f(0.3800f, 0.0f); 
		glColor3f(1.0f,1.0f,1.0f); 
		glVertex2f(0.4900f, 0.1400f); 
		glVertex2f(0.5200f, 0.1400f); 
		glColor3f(0.70f, 0.70f, 1.0f); 
		glVertex2f(0.4100f, 0.0f); 
		glEnd(); 
		glBegin(GL_POLYGON); 
		glVertex2f(0.4100f, 0.0f); 
		glVertex2f(0.4100f, 0.0300f); 
		glColor3f(1.0f, 1.0f, 1.0f); 
		glVertex2f(0.5800f, 0.030f); 
		glVertex2f(0.7000f, 0.0f); 
		glEnd(); 
		
	}
	void drawSnow(){
		for(int i=0; i<6; i++) 
		{ 
			glRotatef(60,0.0,0.0,1.0); 
			drawedge();
		}
		glScalef(-1.0,1.0,1.0); 
		for(int i=0; i< 6; i++) 
		{ 
			glRotatef(60.0,0.0,0.0,1.0); 
			drawedge();
		} 

	}
	void draw()
	{
		GLfloat diffuse[] = {1, 0, 0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(angle, 10, 0, 10);
		glCallList(display_list);
		glPopMatrix();
	}
	void update()
	{
		
		if(alpha<=0){
			init();
		}
		else{
			if(move){
				angle+=10;
				x +=xd;
				y -= _speed;
				z += zd;
				if(x>100||x<-100) init();
				if(z>100||z<-100) init();
				if(y<=0){
					y = 0;
					move = false;
				}
			}
			else{
				alpha-=0.05;
				//cout<<" alpha:"<<alpha;
				//glColor4f(1,1,1,alpha);
			}
		}
	}
	
};