#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
void draw_pixel(GLint cx,GLint cy)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(cx,cy);
	glEnd();
}

void plotpixels(GLint h, GLint k,GLint x, GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);draw_pixel(x+h,-y+k);
}

void circle_draw(GLint h,GLint k, GLint r)
{
	GLint d=r-1, x=0,y=r;
	while(y>x)
	{
		plotpixels(h,k,x,y);
	if(d<0)
		d+=2*x+3;
	else
	{
		d+=2*(x-y)+5;
		--y;
	}
	++x;
	}
	plotpixels(h,k,x,y);
}

void cylinder_draw()
{
	GLint xc=100, yc=100, r=50;
	GLint i,n=80;
	for(i=0;i<n; i=i+3)
	{
		circle_draw(xc,yc+i,r);
	}
	
}

void parallelpiped(int x1, int x2, int y1, int y2, int y3, int y4)
{
	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x2,y3);
	glVertex2i(x2,y4);
	glVertex2i(x1,y2);
	glEnd();
}
void parallelpiped_draw()
{
	int x1=200,x2=300,y1=100,y2=175,y3=100,y4=175;
	GLint i,n=50;
	for(i=0;i<n;i+=2)
	{
		parallelpiped(x1+i,x2+i, y1+i,y2+i,y3+i,y4+i);
	}

}
void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,400.0,0.0,300.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	cylinder_draw();
	parallelpiped_draw();
	glFlush();
}
void main(int argc,char **argv)
{
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0.0,0.0);
	glutInitWindowSize(800.0,800.0);
	glutCreateWindow("CYLINDER AND PARELELOPIPED");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}

