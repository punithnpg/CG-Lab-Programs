
#include<stdio.h>
#include<GL/glut.h>
typedef float point[3];
point v[] = {
	{ 0.0, 0.0, 1.0 }, { 0.0, 0.942809, -0.333333 },
	{ -0.816497, -0.471405, -0.333333 },
	{ 0.816497, -0.471405, -0.333333 }
};
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
int n;
void triangle(point a, point b, point c)
{
	glBegin(GL_POLYGON);
	
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void divide_triangle(point a, point b, point c, int m)
{
	point v1, v2, v3;
	int j;
	//repeat 'm' no of times as specified by user
	if (m>0)
	{
		for (j = 0; j<3; j++)
			// get midpoint of first edge
			v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j<3; j++)
			// get midpoint of second edge
			v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j<3; j++)
			// get midpoint of third edge
			v3[j] = (b[j] + c[j]) / 2;
		// consider midpoints as vertex and divide bigger triangle
		// to 3 parts recursively
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
	}
	//draw the sub divided traingles
	else
	{
		(triangle(a, b, c));
	}
}
// tetrahedron has 4 faces. each face is traingle. we send each
// face of tetrahedron and divide each faces/triangles into 3
// triangles recursively 'm' times
void tetrahedron(int m)
{
	glColor3f(1.0, 0.0, 0.0);
	divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0.0, 1.0, 0.0);
	divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[0], v[3], v[1], m);
	glColor3f(0.0, 0.0, 0.0);
	divide_triangle(v[0], v[2], v[3], m);
}
//this is called everytime the display is refreshed. Here it draw a tetrahedron.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
}
// This function is executed when the window size is changed.
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0*(GLfloat)h / (GLfloat)w, 2.0*(GLfloat)h / (GLfloat)w, -10.0, 10.0); 
	else
		glOrtho(-2.0*(GLfloat)w / (GLfloat)h, 2.0*(GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	printf("no. of divisions \n");
	scanf_s("%d", &n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3DGasket"); //window with a title
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();
}