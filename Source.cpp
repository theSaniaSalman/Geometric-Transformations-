#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <GL/glut.h>
#include<vector>
using namespace std;

// window size 
#define maxWD 800 
#define maxHT 600 

// rotation speed 
#define thetaSpeed 0.05 

// this creates delay between two actions 
void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}

// this is a basic init for the glut window 
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, maxWD, 0.0, maxHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

// this function just draws a point 
void drawPoint(int x, int y)
{
	glBegin(GL_TRIANGLES);
	glVertex2i(x, y);
	glColor3f(1, 0, 0);
	glVertex2i(x + 150, y + 200);
	glColor3f(0, 0, 1);
	glVertex2i(x + 300, y);
	glColor3f(0, 1, 0);
	glEnd();
}


void point(int x, int y)       // function to draw point
{
	glPointSize(40.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(x, y);
	glEnd();
}

void rotate(int x, int y, int cx, int cy)
{
	float theta = 0.0;
	float newtheta = 0.1;           //new rotation angle
	int type, px, py;
	printf("\n \t 1)rotation around origin \n \t 2)rotation around another point");
	scanf_s("%d", &type);
	switch (type)
	{
	case 1:
		while (true)                                   //infinite loop for constant moving
		{
			glClear(GL_COLOR_BUFFER_BIT);
			theta = theta + newtheta;                   // update angle for rotation 

			px = x* cos(theta) - y *sin(theta);         // new points to move around origin   
			py = x* sin(theta) + y *cos(theta);

			drawPoint(0, 0);
			drawPoint(px, py);
			glFlush();
			delay(50); // pauses for 50 miliseconds
		}
		break;
	case 2:
		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			theta = theta + newtheta;

			px = cx + (int)((float)(x - cx) * cos(theta)) - ((float)(y - cy) * sin(theta));
			py = cy + (int)((float)(x - cx) * sin(theta)) + ((float)(y - cy) * cos(theta));

			drawPoint(cx, cy);
			drawPoint(px, py);
			glFlush();
			delay(50);
		}
		break;
	default:
		exit(0);
	}
}


// this function will translate the point 
void translatePoint(int px, int py, int tx, int ty)
{
	int fx = px, fy = py;
	while (1) {
		glClear(GL_COLOR_BUFFER_BIT);

		// update 
		px = px + tx;
		py = py + ty;

		// check overflow to keep point in screen 
		if (px > maxWD || px < 0 || py > maxHT || py < 0) {
			px = fx;
			py = fy;
		}

		drawPoint(px, py); // drawing the point 
		glFlush();
		// creating a delay 
		// so that the point can be noticed 
		delay(500);
	}
}

// this function draws 
void scalePoint(int px, int py, float sx, float sy)
{
	int fx, fy;
	while (1) {
		glClear(GL_COLOR_BUFFER_BIT);

		// update 
		glBegin(GL_TRIANGLES);
		glVertex2i(px, py);
		glColor3f(1, 0, 0);
		glVertex2i((px + 150)*sx, (py + 200)*sy);
		glColor3f(0, 0, 1);
		glVertex2i((px + 300)*sx, py);
		glColor3f(0, 1, 0);
		glEnd(); // drawing the point 
		glFlush();
		// creating a delay 
		// so that the point can be noticed 
		delay(500);

		glClear(GL_COLOR_BUFFER_BIT);

		// update 
		fx = px;
		fy = py;

		// drawing the point 
		drawPoint(fx, fy);
		glFlush();
		// creating a delay 
		// so that the point can be noticed 
		delay(500);
	}
}
void drawsquare(int x, int y) {
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(x, y, 0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3i(x + 100, y, 0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3i(x + 100, y + 150, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3i(x, y + 150, 0);
	glEnd();

}
void shearPoint(int px, int py, float shx)
{
	int fx, fy;
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// update 
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3i(px, py, 0);
		glColor3f(1.0, 0.0, 1.0);
		glVertex3i(px + 100, py, 0);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3i(px + 100 + (shx*py), py + 150, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3i(px + (shx * py), py + 150, 0);
		glEnd(); // drawing the point 
		glFlush();
		// creating a delay 
		// so that the point can be noticed 
		delay(500);

		glClear(GL_COLOR_BUFFER_BIT);

		// update 
		fx = px;
		fy = py;

		// drawing the point 
		drawsquare(fx, fy);
		glFlush();
		// creating a delay 
		// so that the point can be noticed 
		delay(500);
	}
}

// Actual display function 
void myDisplay(void)
{
	int opt;
	int x, y;
	float s, r;
	printf("\t \t \t \t \t Enter the first vertex:");
	printf("\n \t Enter x coordinate:");
	scanf_s("%d", &x);
	printf("\n \t Enter y coordinate:");
	scanf_s("%d", &y);
	printf("-----");
	printf("\n \t \t \t \t Choose a Transformation");
	printf("\n \t 1- TRANSLATION");
	printf("\n \t 2- ROTATION");
	printf("\n \t 3- SCALING");
	printf("\n \t 4- SHEARING\n");
	scanf_s("%d", &opt);
	printf("\n \t  \t -----");
	switch (opt) {
	case 1:
		printf("\n \t Transformation points");
		printf("\n \t Enter tx:");
		scanf_s("%f", &s);
		printf("\t Enter ty:");
		scanf_s("%f", &r);
		printf("\n \t Go to the window...");
		translatePoint(x, y, s, r);
		break;
	case 2:
		rotate(x, y, 640 / 2, 500 / 1.5);
		// point will circle around 
		// the centre of the window 
		break;
	case 3:
		printf("\n \t Scaling points");
		printf("\n \t Enter sx:");
		scanf_s("%f", &s);
		printf("Enter sy:");
		scanf_s("%f", &r);
		printf("\n \t Go to the window...");
		scalePoint(x, y, s, r);
		break;
	case 4:
		printf("\n \t Enter shearing point");
		scanf_s("%f", &s);
		printf("\n \t Go to the window");
		shearPoint(x, y, s);
		break;

	default:
		printf("\n \t Invalid case");
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(maxWD, maxHT);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Transforming point");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
