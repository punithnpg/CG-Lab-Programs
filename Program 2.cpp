
#include<GL/glut.h>

GLdouble xmin=200.0,ymin=200.0, xmax=500.0, ymax=500.0, x0=150.0,y0=200.0,
			x1=300.0, y1=600.0;

GLint clip=0, click=0;

void draw_rect()
{
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmin,ymax);
	glVertex2f(xmax,ymax);
	glVertex2f(xmax,ymin);
	glEnd();
	glFlush();
}
void draw_line()
{
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
	glFlush();
}

int clip_test(double p, double q, double *te, double *tl)
{
	double t=q/p;
	if(p<0.0)
	{
		if(t>*te)
			*te=t;
		if(t>*tl)
			return 0;
	}
	else if(p>0.0)
	{
		if(t<*tl)
			*tl=t;
		if(t<*te)
			return 0;
	}
	else if(p==0)
	{
		if(1<0.0)
			return 0;}
	return 1;
}

void LBclip()
{
	double dx=x1-x0, dy=y1-y0, te=0,tl=1;
	if(clip_test(-dx,x0-xmin,&te,&tl)&&
		clip_test(dx,xmax-x0,&te,&tl)&&
		clip_test(-dy,y0-ymin,&te,&tl)&&
		clip_test(dy,ymax-y0,&te,&tl))
	{
		clip=1;
		if(tl<1.0)
		{
			x1=x0+tl*dx;
			y1=y0+tl*dy;
		}
		if(te>0.0)
		{
			x0=x0+te*dx;
			y0=y0+te*dy;
		}
	}
}

void mouse(int button, int state, int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		click=1;
	glutPostRedisplay();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_rect();
	glColor3f(0.0,0.0,1.0);
	draw_line();
	LBclip();
	if(clip && click)
	{
		glColor3f(0.0,1.0,0.0);
		draw_line();
	}
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,800.0,0.0,800.0);
	glMatrixMode(GL_MODELVIEW);
}

void main( int argc, char **argv)
{
	glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(500.0,500.0);
	glutInitWindowPosition(10.0,10.0);
	glutCreateWindow("Liang Barsky Clipping");
		glutMouseFunc(mouse);
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}