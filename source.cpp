#pragma comment(lib, "glaux.lib")
#include <gl\glaux.h>
#include <math.h>             //计算旋转角
#include <GL/glut.h> 
#include <stdlib.h> 
#include "particlesystem.h"
//#include "models.h"
#include <iostream>
using namespace std;
//angle绕y轴的旋转角,允许我们旋转照相机;ratio：窗口宽高比（width/height）
GLuint g_texture = 0;
GLuint t_texture = 1;
GLuint s_texture = 2;
//importModels police;
//importModels jack;
//响应窗口位置、大小改变事件的回调函输
#define size  100
#define speed  5
int c_size = 50;
int height = 40;
int w_height = 15;
int w_width = 3;
int w_length = 18;
int path = 10;
bool first = true;
particleSystem p  ;
bool canWalk[(size+speed)*2+3][(size+speed)*2+3];
static float angle=0.0,ratio;    
//static float x=100,y=20.0f,z=100;    //照相机位置
//static float lx=-10.0f,ly=0.0f,lz=-10;  //一个向量用来指示我们的视线方向
static float x=0.0f,y=w_height,z=5.0f;    //照相机位置
static float lx=0.0f,ly=0.0f,lz=-1.0f;  //一个向量用来指示我们的视线方向
//static GLint snowman_display_list;   //一个雪人的显示列表索引
//int w
GLfloat vertices[][3] = {
	/*{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0}, {1.0,1.0,-1.0},
	{-1.0,1.0,-1.0},  
	{-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
	*/
	//右上
	{path  , 0  , -path},
	{path+c_size,   0  , -path},
	{path+c_size ,  0 , -(path+c_size)},
	{path , 0  , -(path+c_size)},

	{path  , height  , -path},
	{path+c_size,   height  , -path},
	{path+c_size ,  height , -(path+c_size)},
	{path , height  , -(path+c_size)},
	//左上
	{-(path+c_size),   0  , -path},
	{-path  , 0  , -path},
	{-path , 0  , -(path+c_size)},
	{-(path+c_size) ,  0 , -(path+c_size)},

	{-(path+c_size),   height  , -path},
	{-path  , height  , -path},
	{-path , height  , -(path+c_size)},
	{-(path+c_size) ,  height , -(path+c_size)},
	//右下
	{path , 0  ,(path+c_size)},
	{(path+c_size) ,  0 ,(path+c_size)},
	{(path+c_size),   0  , path},
	{path  , 0  , path},

	{path , height  ,(path+c_size)},
	{(path+c_size) ,  height ,(path+c_size)},
	{(path+c_size),   height  , path},
	{path  , height  , path},
	//左下
	{-(path+c_size) ,  0 ,(path+c_size)},
	{-path , 0  ,(path+c_size)},
	{-path  , 0  , path},
	{-(path+c_size),   0  , path},

	{-(path+c_size) ,  height , (path+c_size)},
	{-path , height  , (path+c_size)},
	{-path  , height  , path},
	{-(path+c_size),   height  , path},

	//前外墙
	{-size ,  0 ,-size},
	{size ,  0 ,-size},
	{size ,  0 ,-(size+speed)},
	{-size ,  0 ,-(size+speed)},

	{-size , height ,-size},
	{size ,  height ,-size},
	{size ,  height ,-(size+speed)},
	{-size ,  height ,-(size+speed)},

	//后外墙
	{-size ,  0 ,(size+speed)},
	{size ,  0 ,(size+speed)},
	{size ,  0 ,size},
	{-size ,  0 ,size},

	{-size ,  height ,(size+speed)},
	{size ,  height ,(size+speed)},
	{size ,  height ,size},
	{-size ,  height ,size},

	//左外墙
	{-(size+speed) ,  0 ,(size+speed)},
	{-size ,  0 ,(size+speed)},
	{-size ,  0 ,-(size+speed)},
	{-(size+speed) ,  0 ,-(size+speed)},

	{-(size+speed) ,  height ,(size+speed)},
	{-size ,  height ,(size+speed)},
	{-size ,  height ,-(size+speed)},
	{-(size+speed) ,  height ,-(size+speed)},

	//右外墙
	{size ,  0 ,(size+speed)},
	{(size+speed) ,  0 ,(size+speed)},
	{(size+speed) ,  0 ,-(size+speed)},
	{size ,  0 ,-(size+speed)},

	{size ,  height ,(size+speed)},
	{(size+speed) ,  height ,(size+speed)},
	{(size+speed) ,  height ,-(size+speed)},
	{size ,  height ,-(size+speed)},
};

GLfloat vertices1[][3] = {
	//右墙
	{(size-w_length)  , 0  , w_width},
	{size , 0  , w_width},
	{size  , 0  , -w_width},
	{(size-w_length)  , 0  , -w_width},

	{(size-w_length)  , w_height-5  , w_width},
	{size , w_height  , w_width},
	{size  , w_height  , -w_width},
	{(size-w_length)  , w_height-5  , -w_width},

	//左墙
	{-size , 0  , w_width},
	{-(size-w_length)  , 0  , w_width},
	{-(size-w_length)  , 0  , -w_width},
	{-size  , 0  , -w_width},

	{-size , w_height  , w_width},
	{-(size-w_length)  , w_height-5  , w_width},
	{-(size-w_length)  , w_height-5  , -w_width},
	{-size  , w_height  , -w_width},

	//左上
	{-(path+c_size+w_length) , 0  , -(path+c_size-w_width)},
	{-(path+c_size) , 0  , -(path+c_size-w_width)},
	{-(path+c_size)  , 0  , -(path+c_size)},
	{-(path+c_size+w_length)   , 0  , -(path+c_size)},

	{-(path+c_size+w_length) , w_height  , -(path+c_size-w_width)},
	{-(path+c_size) , w_height  , -(path+c_size-w_width)},
	{-(path+c_size)  , w_height  , -(path+c_size)},
	{-(path+c_size+w_length)   , w_height  , -(path+c_size)},

	//右上
	{(path+c_size) , 0  , -(path+c_size-w_width)},
	{(path+c_size+w_length) , 0  , -(path+c_size-w_width)},
	{(path+c_size+w_length)   , 0  , -(path+c_size)},
	{(path+c_size)  , 0  , -(path+c_size)},

	{(path+c_size) , w_height  , -(path+c_size-w_width)},
	{(path+c_size+w_length) , w_height  , -(path+c_size-w_width)},
	{(path+c_size+w_length)   , w_height  , -(path+c_size)},
	{(path+c_size)  , w_height  , -(path+c_size)},

	//右下
	{(path+c_size)  , 0  , (path+c_size)},
	{(path+c_size+w_length)   , 0  , (path+c_size)},
	{(path+c_size+w_length) , 0  , (path+c_size-w_width)},
	{(path+c_size) , 0  , (path+c_size-w_width)},

	{(path+c_size)  , w_height  ,(path+c_size)},
	{(path+c_size+w_length)   , w_height  ,(path+c_size)},
	{(path+c_size+w_length) , w_height  ,(path+c_size-w_width)},
	{(path+c_size) , w_height  ,(path+c_size-w_width)},

	//左下
	{-(path+c_size+w_length)   , 0  , (path+c_size)},
	{-(path+c_size)  , 0  , (path+c_size)},
	{-(path+c_size) , 0  , (path+c_size-w_width)},
	{-(path+c_size+w_length) , 0  , (path+c_size-w_width)},

	{-(path+c_size+w_length)   , w_height  , (path+c_size)},
	{-(path+c_size)  , w_height  , (path+c_size)},
	{-(path+c_size) , w_height  , (path+c_size-w_width)},
	{-(path+c_size+w_length) , w_height  ,(path+c_size-w_width)},


};
static const GLint index_list[][4] = {

	3, 2, 1, 0,
	7, 6, 5, 4,
	4, 5, 1, 0,
	7, 6, 2, 3,
	7, 4, 0, 3,
	5, 6, 2, 1,

};

void changeSize(int w, int h)         
{          
	// 防止被0除.        
	if(h == 0)                 
		h = 1;          
	ratio = 1.0f * w / h;                
	glMatrixMode(GL_PROJECTION);         
	glLoadIdentity();                  //设置视口为整个窗口大小         
	glViewport(0, 0, w, h);          //设置可视空间         
	gluPerspective(45,ratio,1,1000);         
	glMatrixMode(GL_MODELVIEW);        
	glLoadIdentity();         
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);        
}

int LoadGLTextures(GLuint& unTexture, const char* chFileName)                
{
	AUX_RGBImageRec *TextureImage;                    //保存贴图数据的指针
	TextureImage = auxDIBImageLoad(chFileName);         //载入贴图数据

	glGenTextures(1, &unTexture);                    // 创建一个纹理，unTexture

	glBindTexture(GL_TEXTURE_2D, unTexture);        //绑定纹理，然后对该纹理区添加纹理数据

	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}

	return 1;
}

//绘制1个雪人
void drawSnowMan() 
{          
	glColor3f(1.0f, 1.0f, 1.0f);
	//画身体         
	glTranslatef(0.0f ,0.75f, 0.0f);         
	glutSolidSphere(0.75f,20,20);        //实心圆
	// 画头         
	glTranslatef(0.0f, 1.0f, 0.0f);         
	glutSolidSphere(0.25f,20,20);        //实心圆
	// 画眼睛         
	glPushMatrix();         
	glColor3f(0.0f,0.0f,0.0f);         
	glTranslatef(0.05f, 0.10f, 0.18f);         
	glutSolidSphere(0.05f,path,path);         
	glTranslatef(-0.1f, 0.0f, 0.0f);         
	glutSolidSphere(0.05f,path,path);         
	glPopMatrix();
	// 画鼻子         
	glColor3f(1.0f, 0.5f , 0.5f);         
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);         
	glutSolidCone(0.08f,0.5f,path,2);    //实心圆锥体
} 
//创建绘制雪人的显示列表
GLuint createDL()
{         
	GLuint snowManDL;          
	//生成一个显示列表号         
	snowManDL = glGenLists(1);          // 开始显示列表         
	glNewList(snowManDL,GL_COMPILE);          // call the function that contains          
	// the rendering commands                 
	drawSnowMan();          // endList         
	glEndList();         
	return(snowManDL);
} 



//初始化场景
void initScene() 
{         
	glEnable(GL_DEPTH_TEST);    
	glEnable(GL_TEXTURE_2D);

	LoadGLTextures(g_texture, "wall.bmp");   
	LoadGLTextures(t_texture, "wall1.bmp");   
	LoadGLTextures(s_texture, "sky.bmp");   
	//p=  ParticleSystem(100,size,height);
	//snowman_display_list = createDL();
} 

#define MAX_CHAR  128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if( isFirstCall ) { // 如果是第一次调用，执行初始化
		// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;
		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for(; *str!='\0'; ++str)
		glCallList(lists + *str+1);
}


//绘制地面和36个1雪人
void renderScene(void) 
{         
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	/*
	glPushMatrix(); 
	glTranslatef(80.0, -20.0, -80.0);
	//glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(0.8, 0.8, 0.8);
	police.display();   //显示“Entry”
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef(-80.0, 0.0, -80.0);
	//glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	jack.display();   //显示“Entry”
	glPopMatrix();
	*/
	/*
	glRasterPos2f(0.0f, 0.0f);
	drawString("test");
	*/
	glBindTexture(GL_TEXTURE_2D, g_texture); 
	p.display();	
	glPushMatrix();        //压入变换矩阵
	glBindTexture(GL_TEXTURE_2D, g_texture);        //使用贴图纹理
	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制
	for(int k = 0; k <8;k++){
		for(int i=0; i<6; ++i){         // 有六个面，循环六次
			for(int j=0; j<4; ++j)     // 每个面有四个顶点，循环四次
			{
				if(j==0)
					glTexCoord2f(0.0f, 1.0f);
				else if(j==1)
					glTexCoord2f(1.0f, 1.0f);
				else if(j==2)
					glTexCoord2f(1.0f, 0.0f);
				else
					glTexCoord2f(0.0f, 0.0f);
				glVertex3fv(vertices[index_list[i][j]+k*8]);
			}
		}
		int startX = vertices[k*8][0];
		int endX = vertices[1+k*8][0];
		int startZ = vertices[3+k*8][2];
		int endZ = vertices[k*8][2];
		for(int m = startX-2; m <=endX+2;m++)
			for(int n = startZ-2;n <=endZ+2;n++)
				canWalk[m+size+speed][n+size+speed] =false;
		
	}	
	//
	glEnd();    
	glPopMatrix(); //弹出变换矩阵

	//使用四边形画了一个地面          
	//glColor3f(0.9f, 0.9f, 0.9f); 
	glBindTexture(GL_TEXTURE_2D,g_texture);        //使用贴图纹理
	glBegin(GL_QUADS);            
	glTexCoord2f(0.0f,0.0f); glVertex3f(-size, 0.0f, -size);                 
	glTexCoord2f(1.0f,0.0f);glVertex3f(-size, 0.0f, size);                 
	glTexCoord2f(1.0f,1.0f);glVertex3f( size, 0.0f, size);                 
	glTexCoord2f(0.0f,1.0f);glVertex3f( size, 0.0f, -size);   
	glEnd(); 

	//上三角
	glBegin(GL_TRIANGLES); 
	//glTexCoord2f(0.0f,0.0f); glVertex3f(-path  , 0  , -size),
	//glTexCoord2f(0.0f,1.0f); glVertex3f(path  , 0  , -size),
	//glTexCoord2f(1.0f,1.0f); glVertex3f(0 , 0  , (size-path+c_size)/2),
	glTexCoord2f(0.0f,0.0f); glVertex3f(-path/2  , height  , -size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(path/2  , height , -size);
	glTexCoord2f(1.0f,1.0f); glVertex3f(0 , height , -(size-(size-path-c_size)/3));
	glEnd(); 
	glBegin(GL_QUADS); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(-path/2  , 0  , -size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(-path/2  , height  , -size);
	glTexCoord2f(1.0f,1.0f);  glVertex3f(0 , height ,  -(size-(size-path-c_size)/3));
	glTexCoord2f(1.0f,0.0f); glVertex3f(0 , 0 ,  -(size-(size-path-c_size)/3));

	glTexCoord2f(0.0f,0.0f); glVertex3f(path/2  , 0  , -size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(path/2  , height  , -size);
	glTexCoord2f(1.0f,1.0f);  glVertex3f(0 , height ,  -(size-(size-path-c_size)/3));
	glTexCoord2f(1.0f,0.0f); glVertex3f(0 , 0 ,  -(size-(size-path-c_size)/3));
	glEnd(); 
	int strat_X= -path/2-speed;
	int end_X = path/2+speed;
	int start_Z =-size;
	int end_Z =  -(size-(size-path-c_size)/3)+speed;
	for(int i = strat_X; i <end_X;i++)
	for(int j = start_Z; j <end_Z;j++)
	{
		canWalk[i+size+speed][j+size+speed] =false;
		canWalk[i+size+speed][-j+size+speed] =false;
	}

	//下三角
	glBegin(GL_TRIANGLES); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(-path/2  , height  , size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(path/2  , height , size);
	glTexCoord2f(1.0f,1.0f); glVertex3f(0 , height , (size-(size-path-c_size)/3));
	glEnd(); 
	glBegin(GL_QUADS); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(-path/2  , 0  , size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(-path/2  , height  , size);
	glTexCoord2f(1.0f,1.0f);  glVertex3f(0 , height ,  (size-(size-path-c_size)/3));
	glTexCoord2f(1.0f,0.0f); glVertex3f(0 , 0 ,  (size-(size-path-c_size)/3));

	glTexCoord2f(0.0f,0.0f); glVertex3f(path/2  , 0  , size);
	glTexCoord2f(0.0f,1.0f); glVertex3f(path/2  , height  , size);
	glTexCoord2f(1.0f,1.0f);  glVertex3f(0 , height ,  (size-(size-path-c_size)/3));
	glTexCoord2f(1.0f,0.0f); glVertex3f(0 , 0 ,  (size-(size-path-c_size)/3));
	glEnd(); 

	glBindTexture(GL_TEXTURE_2D, s_texture);        //使用贴图纹理
	glBegin(GL_QUADS);            
	glTexCoord2f(0.0f,0.0f); glVertex3f( -1000, 100, -1000);                  
	glTexCoord2f(1.0f,0.0f);glVertex3f(-1000, 100, 1000);                 
	glTexCoord2f(1.0f,1.0f);glVertex3f(1000, 100, 1000);                 
	glTexCoord2f(0.0f,1.0f);glVertex3f( 1000, 100,-1000 );   
	glEnd(); 

	glBindTexture(GL_TEXTURE_2D, t_texture);        //使用贴图纹理
	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制
	for(int k = 0; k <6;k++){
		for(int i=0; i<6; ++i) {        // 有六个面，循环六次
			for(int j=0; j<4; ++j)     // 每个面有四个顶点，循环四次
			{
				if(j==0){
					glTexCoord2f(0.0f, 0.0f);
				}
				else if(j==1)
					glTexCoord2f(1.0f, 0.0f);
				else if(j==2)
					glTexCoord2f(1.0f, 1.0f);
				else{

					glTexCoord2f(0.0f, 1.0f);
				}
				glVertex3fv(vertices1[index_list[i][j]+k*8]);
			}
		}
		int startX = vertices1[k*8][0];
		int endX = vertices1[1+k*8][0];
		int startZ = vertices1[3+k*8][2];
		int endZ = vertices1[k*8][2];
		for(int m = startX; m <=endX;m++)
			for(int n = startZ;n <=endZ;n++)
				canWalk[m+size+speed][n+size+speed] =false;
	}//
	glEnd(); 
	 
 
	glutSwapBuffers();
}
//计算由于左右键盘操作而改变视点方向，使用左右方向键旋转照相机
void orientMe(float ang) 
{          
	lx = sin(ang);         
	lz = -cos(ang);         
	glLoadIdentity();         
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}
//计算视点由于上下键盘操作而移动的量，上下方向键使照相机沿视线前后移动
void moveMeFlat(int direction) 
{    
	int pre_x = x;
	int pre_z = z;
	x = x + direction*(lx)*0.5;         
	z = z + direction*(lz)*0.5;
	if(!canWalk[int(x+size+speed)][int(z+size+speed)]){
		x = pre_x;
		z =pre_z;
	}
	glLoadIdentity();         
	gluLookAt(x, y, z, x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);
}

void inputKey(int key, int x, int y) 
{          
	switch (key) 
	{
	case GLUT_KEY_LEFT :                           
		angle -= 0.05f;                          
		orientMe(angle);
		break;                 
	case GLUT_KEY_RIGHT :                           
		angle +=0.05f;                          
		orientMe(angle);
		break;                 
	case GLUT_KEY_UP :                           
		moveMeFlat(speed);
		break;                 
	case GLUT_KEY_DOWN :                           
		moveMeFlat(-speed);
		break; 
	}
}


 
int main(int argc, char **argv)
{   
	//police.import("police.obj", "police.mtl");
	//jack.import("jack.obj", "jack.mtl");
	glutInit(&argc, argv);         
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);         
	glutInitWindowPosition(size,size);         
	glutInitWindowSize(640,360);         
	glutCreateWindow("CS-iceworld by YuChen");  
	memset(canWalk,true,sizeof(canWalk));
	initScene();          
	glutSpecialFunc(inputKey);    
	glutDisplayFunc(renderScene);         
	glutIdleFunc(renderScene);          
	glutReshapeFunc(changeSize);  
	//glutIdleFunc(&myIdle);
	glutMainLoop();          
	return(0);
}

