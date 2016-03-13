#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
GLdouble xmin = 200.0, ymin = 200.0, xmax = 500.0, ymax = 500.0, x0 = 150.0, y0 = 300.0, x1 = 500.0, y1 = 600.0;
GLint accept = 0, done = 0, click = 0;
const int top = 8;
const int bottom = 4;
const int right = 2;
const int left = 1;

void draw_rect()
{
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin, ymax);
	glVertex2f(xmax, ymax);
	glVertex2f(xmax, ymin);
	glEnd();
	glFlush();
}

void draw_line()
{
	glBegin(GL_LINES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glEnd();
	glFlush();
}

int computecode(double x, double y)
{
	int code = 0;
	if (y>ymax)
		code |= top;
	else if (y<ymin)
		code |= bottom;
	if (x>xmax)
		code |= right;
	else if (x<xmin)
		code |= left;
	return code;
}

void csclip()
{
	int code0, code1, outcode;
	code0 = computecode(x0, y0);
	code1 = computecode(x1, y1);
	do
	{
		if (!(code0 | code1))
		{
			accept = 1;
			done = 1;
		}
		else if (code0&code1)
			done = 1;
		else
		{
			double x, y;
			outcode = code0 ? code0 : code1;
			if (outcode&top)
			{
				x = x0 + (x1 - x0)*(ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (outcode&bottom)
			{
				x = x0 + (x1 - x0)*(ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (outcode&right)
			{
				y = y0 + (y1 - y0)*(xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0)*(xmin - x0) / (x1 - x0);
				x = xmin;
			}
			if (outcode == code0)
			{
				x0 = x;
				y0 = y;
				code0 = computecode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				code1 = computecode(x1, y1);
			}
		}
	} while (!done);
}

void mouse(int button, int state, int a, int b)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		click = 1;
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_rect();
	glColor3f(0.0, 0.0, 1.0);
	draw_line();
	csclip();
	if (accept&&click)
	{
		glColor3f(0.0, 1.0, 0.0);
		draw_line();
	}
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 800.0);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500.0, 500.0);
	glutInitWindowPosition(10.0, 10.0);
	glutCreateWindow("Cohen-Sutherland Clipping line");
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}

