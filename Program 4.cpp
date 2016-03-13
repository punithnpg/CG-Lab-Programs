#include<GL/glut.h>
#define maxx 30
#define maxy 30
#define dx 10
#define dy 10
int x0 = 90, y0 = 90;
float x[maxx], y[maxy];

void display()
{
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT);
	for (i = 0; i<maxx; i++)
		x[i] = x0 + i*dx;
	for (j = 0; j<maxy; j++)
		y[j] = y0 + j*dy;
	for (i = 0; i<maxx - 1; i++)
		for (j = 0; j<maxy - 1; j++)
		{
			glLineWidth(3.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(x[i], y[j]);
			glVertex2f(x[i], y[j + 1]);
			glVertex2f(x[i + 1], y[j + 1]);
			glVertex2f(x[i + 1], y[j]);
			glEnd();
			glFlush();
		}
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0.1, 0.2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rectangular Mesh");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}


