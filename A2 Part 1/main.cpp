/*
COmp 477 assignment 2, Part 1
Ayush Kharade, ID: 40042388, group submission
*/
#define GLUT_DISABLE_ATEXIT_HACK

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include<cmath>
#include <GL/glut.h>
#include "cugl.h"


using namespace std;
using namespace cugl;


// Initial size of graphics window.
const int WIDTH = 900;
const int HEIGHT = 600;

// Current size of window.
int width = WIDTH;
int height = HEIGHT;

// Viewing frustum.
double nearPlane = 5;
double farPlane = 150;
double distance = 10;
double fovy = 40.0;

// Lighting and shadow.
GLfloat AMBIENT[] = { 0.4f, 0.4f, 0.4f, 1 };
GLfloat LIGHT_POSITION[] = { 10, 15, 1, 1 };
Plane SHADOW_PLANE = Plane(0, 1, 0, -0.01);
Matrix shadowMat(LIGHT_POSITION, SHADOW_PLANE);

double dt;


// so that it doesnt keep calling generatePoints()
bool generated;
bool morphed;




//

// using generation function
Point *FaceFront[25];
Point *FaceBack[25];

Point *FaceTop[25];
Point *FaceBottom[25];


Point *FaceLeft[25];
Point *FaceRight[25];


// Reset initial conditions.
void initialize()
{
	
	//dt = 0.02;
}


// make a function that generates the points.

void generatePoints(int distance)
{
	//distance is distance between the points.
	//each face has 25 points
	// z stays constant for each face, y changes every 5 lines, x changes every line
	
	// generate face 1: front (25 point objects)
	

// point generation values
	float x = 0.0, y = 0.0;
	int index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceFront[index] = new Point(x,y,4);
			x += 1;
			//cout<<"Point index: "<<(index)<<" with values: ("<<x<<", "<<y<< ",0.5)"<<endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}



	//generate face 2: back
	x = 0.0, y = 0.0; 
	index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceBack[index] = new Point(x, y, 0);
			x += 1;
			//cout<<"Point index: "<<(index)<<" with values: ("<<x<<", "<<y<< ",0.5)"<<endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}


	//generate face 3: Right, x value is constant
	x = 0.0, y = 0.0;
	index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceRight[index] = new Point(0, y, x);
			x += 1;
			//cout<<"Point index: "<<(index)<<" with values: ("<<x<<", "<<y<< ",0.5)"<<endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}

	//generate face 4: left
	x = 0.0, y = 0.0;
	index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceLeft[index] = new Point(4, y, x);
			x += 1;
			//cout<<"Point index: "<<(index)<<" with values: ("<<x<<", "<<y<< ",0.5)"<<endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}






	//generate face 5: top
	// y will be constant and x and z will vary
	x = 0.0, y = 0.0; 
	index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceTop[index] = new Point(x, 4, y);
			x += 1;
			//cout<<"Point index: "<<(index)<<" with values: ("<<x<<", "<<" 2.5"<< ","<<y<<")"<<endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}

	//generate face 6: bottom
	x = 0.0, y = 0.0;
	index = 0;
	for (int i = 1; i <= 5; i++)         // for every row of y
	{
		for (int j = 1; j <= 5; j++)     // for every row of x
		{
			FaceBottom[index] = new Point(x, 0, y);
			x += 1;
			//cout << "Point index: " << (index) << " with values: (" << x << ", " << " -2.5" << "," << y << ")" << endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}





	generated = true;
}


// Update graphics window.
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 5, -10, 0, 0, 10, 0, 1, 0);          // from (x,y,z), look at point (x,y,z), upvector (x,y,z)
	gluLookAt(-5, 5, -15, 0, 0, 10, 0, 1, 0);          // from (x,y,z), look at point (x,y,z), upvector (x,y,z)


	glPushMatrix();
	
	

	// front and back set of points in red
	glDisable(GL_LIGHTING);
	glColor3d(1, 0, 0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);

	

	if(!generated)
		generatePoints(0.2);

	for (int i = 0; i < 25; i++)
	{
		FaceFront[i]->draw();
		FaceBack[i]->draw();
		//cout<<FaceFront[i]<<endl;
	}

	glEnd();
	
	//left & right set of points in blue
	glDisable(GL_LIGHTING);
	glColor3d(0, 0, 1);
	glPointSize(5.0f);
	glBegin(GL_POINTS);

	for (int i = 0; i < 25; i++)
	{
		FaceLeft[i]->draw();
		FaceRight[i]->draw();
	}
	glEnd();






	//top&bottom set of points in blue
	glDisable(GL_LIGHTING);
	glColor3d(0, 1, 0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);

	for (int i = 0; i < 25; i++)
	{
		FaceTop[i]->draw();
		FaceBottom[i]->draw();
	}
	glEnd();

	
	glPopMatrix();

	//
	glutSwapBuffers();
}








// Inverse inertia tensor for a cube
//const GLfloat DIAG = 5.0 / 22.0;
//const GLfloat OFFD = 3.0 / 22.0;

const GLfloat DIAG = 1.0 / 6.0;
const GLfloat OFFD = 0.0;
Matrix mi(
	DIAG, OFFD, OFFD, 0.0f,
	OFFD, DIAG, OFFD, 0.0f,
	OFFD, OFFD, DIAG, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);

Matrix invmi = mi.inv();

void report()
{

}

// Background calculations.
void idle()  // does math in background
{
	
	glutPostRedisplay();
}

// Callback for reshaping graphics window.
void reshapeMainWindow(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}

// Respond to graphic keys.
void graphicKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		initialize();
		break;
	case '+':
		dt *= 1.1;
		break;
	case '-':
		dt /= 1.1;
		break;
	

	case 27:
		exit(0);
	}
}



int main(int argc, char **argv)
{
	//display to console controls
	cout <<
		"Assignment 2: Part 1, Morphing" << endl <<
		"Press these keys:" << endl <<
		" ' ' (space)  restore initial conditions" << endl <<
		" '+'          speed up" << endl <<
		" '-'          slow down" << endl <<
		" ESC          quit" << endl;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(800, 0); // where it starts
	glutCreateWindow("Cube morphing");
	glutDisplayFunc(display);                       // tell glut what is our display function
	glutReshapeFunc(reshapeMainWindow);             // for fullscreening & resizing
	glutKeyboardFunc(graphicKeys);                  // turn on/off gravity , kinematic, etc
	glutIdleFunc(idle);                             // idle function for
	glClearColor(0.6, 0.6, 1, 1);
	

	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, AMBIENT);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	initialize();
	glutMainLoop();
	
	return 0;
}
