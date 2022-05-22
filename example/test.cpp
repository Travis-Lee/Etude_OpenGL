#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <glut/glut.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "OpenGL纹理测试"

//定义两个纹理对象编号
GLuint texGround;
GLuint texWall;

static GLfloat angle = 0.0f;   //旋转角度

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	Mat I = imread(file_name);

	width = I.cols;
	height = I.rows;
	int pixellength = width * height * 3;
	//开辟指针空间
	pixels = new GLubyte[pixellength];
	//图像指针复制
	memcpy(pixels, I.data, pixellength * sizeof(char));

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	delete pixels;
	return texture_ID;
}


void display(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);

	glRotatef(angle, 0.0f, 1.0f, 0.0f); //旋转

	// 绘制底面以及纹理
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	// 绘制立面
	//glBindTexture(GL_TEXTURE_2D, texWall);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-8.0f, 8.0f, 8.0f);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, -8.0f, 8.0f);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	//glEnd();

	//绘制另外一个立面
	//glBegin(GL_QUADS);
	//glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);
	//glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
	//glEnd();

	glutSwapBuffers();
}

void myIdle(void)
{
	angle += 0.1f;
	if (angle >= 360.0f)
		angle = 0.0f;
	display();
}

int main(int argc, char* argv[])
{
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    // 启用纹理
	texGround = load_texture("./data/test.jpg");  //加载纹理
	texWall = load_texture("./data/test.jpg");
	cout << "###" << endl;
	glutDisplayFunc(&display);   //注册函数
	//glutIdleFunc(&myIdle);
	glutMainLoop(); //循环调用
	return 0;
}


