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
#include <cmath>
#include <vector>
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
bool generated = false;
bool generatedMorphed = false;
bool morphing = false;
bool vectorsInitialized = false;
bool generatedInterpolation = false;

float morphSphereRadius = 2;

// Using generate points function, we get the info to draw the cube
std::vector<std::vector<float>> FaceFront(25);
std::vector<std::vector<float>> FaceBack(25);

std::vector<std::vector<float>> FaceTop(25);
std::vector<std::vector<float>> FaceBottom(25);

std::vector<std::vector<float>> FaceLeft(25);
std::vector<std::vector<float>> FaceRight(25);

// Using the the morphed points function, we get the info to draw the sphere from the cube
std::vector<std::vector<float>> FaceFrontMorphed(25);
std::vector<std::vector<float>> FaceBackMorphed(25);

std::vector<std::vector<float>> FaceTopMorphed(25);
std::vector<std::vector<float>> FaceBottomMorphed(25);

std::vector<std::vector<float>> FaceLeftMorphed(25);
std::vector<std::vector<float>> FaceRightMorphed(25);

// Using linear interpolation we morph from cube to sphere
std::vector<std::vector<float>> FaceFrontInterpolate(25);
std::vector<std::vector<float>> FaceBackInterpolate(25);

std::vector<std::vector<float>> FaceTopInterpolate(25);
std::vector<std::vector<float>> FaceBottomInterpolate(25);

std::vector<std::vector<float>> FaceLeftInterpolate(25);
std::vector<std::vector<float>> FaceRightInterpolate(25);

//Setting up vectors to hold all faces so it's easier to code
std::vector<std::vector<std::vector<float>>*> Cube(6);
std::vector<std::vector<std::vector<float>>*> Sphere(6);
std::vector<std::vector<std::vector<float>>*> Interpolant(6);

// Reset initial conditions.
void initialize()
{
	//dt = 0.02;
}

//Initialize Cube, Sphere and Interpolant Vectors
void initializeVectors() {
	for (int i = 0; i < 6; i++) {
		switch (i) {
			case 0:
				Cube[i] = &FaceFront;
				Sphere[i] = &FaceFrontMorphed;
				Interpolant[i] = &FaceFrontInterpolate;
				break;
			case 1:
				Cube[i] = &FaceBack;
				Sphere[i] = &FaceBackMorphed;
				Interpolant[i] = &FaceBackInterpolate;
				break;
			case 2:
				Cube[i] = &FaceLeft;
				Sphere[i] = &FaceLeftMorphed;
				Interpolant[i] = &FaceLeftInterpolate;
				break;
			case 3:
				Cube[i] = &FaceRight;
				Sphere[i] = &FaceRightMorphed;
				Interpolant[i] = &FaceRightInterpolate;
				break;
			case 4:
				Cube[i] = &FaceBottom;
				Sphere[i] = &FaceBottomMorphed;
				Interpolant[i] = &FaceBottomInterpolate;
				break;
			case 5:
				Cube[i] = &FaceTop;
				Sphere[i] = &FaceTopMorphed;
				Interpolant[i] = &FaceTopInterpolate;
				break;
		}
	}

	vectorsInitialized = true;
	
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
			FaceFront[index].push_back(x);
			FaceFront[index].push_back(y);
			FaceFront[index].push_back(4);
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
			FaceBack[index].push_back(x);
			FaceBack[index].push_back(y);
			FaceBack[index].push_back(0);
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
			FaceRight[index].push_back(0);
			FaceRight[index].push_back(y);
			FaceRight[index].push_back(x);
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
			FaceLeft[index].push_back(4);
			FaceLeft[index].push_back(y);
			FaceLeft[index].push_back(x);
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
			FaceTop[index].push_back(x);
			FaceTop[index].push_back(4);
			FaceTop[index].push_back(y);
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
			FaceBottom[index].push_back(x);
			FaceBottom[index].push_back(0);
			FaceBottom[index].push_back(y);
			x += 1;
			//cout << "Point index: " << (index) << " with values: (" << x << ", " << " -2.5" << "," << y << ")" << endl;
			index++;
		}
		y += 1;
		x = 0.0;
	}

	generated = true;
}

//Makes the sphere points from the cube points
void generateMorphedPoints() {
	// go through all 6 arrays, and compute new position.

	for (int i = 0; i < Cube.size(); i++) {
		std::vector<std::vector<float>> Face = *Cube[i];
		std::vector<std::vector<float>>& FaceSphere = *Sphere[i];
		for (int j = 0; j < Face.size(); j++) {
	

			float x0, y0, z0;
			float x1, y1, z1;

			x0 = Face[j][0];
			y0 = Face[j][1];
			z0 = Face[j][2];
		
			double d = sqrt((pow(x0, 2) + pow(y0, 2) + pow(z0, 2)));

			//cout << "d/z = " << (d / z) / 100 << endl;
			//double theta = acos((d / z));
			double theta = acos(z0 / d) * 180/PI;

			double phi = atan2(y0, x0) * 180/PI;

			// new values
			x1 = morphSphereRadius * sin(theta) * cos(phi);
			y1 = morphSphereRadius * sin(theta) * sin(phi);
			z1 = morphSphereRadius * cos(theta);

			//cout << "new points at index: " << i << ", X1: " << x1 << ", Y1:" << y1 << ", Z1: " << z1 << endl;

			FaceSphere[j].push_back(x1);
			FaceSphere[j].push_back(y1);
			FaceSphere[j].push_back(z1);
		}
	}

	generatedMorphed = true;
}

//Makes the linear interpolation from sphere and cube info
void generateInterpolation() {
	//Interpolation

	for (int i = 0; i < Cube.size(); i++) {
		std::vector<std::vector<float>> FaceCube = *Cube[i];
		std::vector<std::vector<float>> FaceSphere = *Sphere[i];
		std::vector<std::vector<float>>& FaceInterpolant = *Interpolant[i];

		for (int j = 0; j < FaceCube.size(); j++) {
			FaceInterpolant[j].push_back(FaceSphere[j][0] - FaceCube[j][0]);
			FaceInterpolant[j].push_back(FaceSphere[j][1] - FaceCube[j][1]);
			FaceInterpolant[j].push_back(FaceSphere[j][2] - FaceCube[j][2]);
		}
	}
	
	generatedInterpolation = true;
}

//Morphing the cube into a sphere
void cubeToSphereMorph() {
	for (int i = 0; i < Cube.size(); i++) {
		std::vector<std::vector<float>>& FaceCube = *Cube[i];
		std::vector<std::vector<float>> FaceSphere = *Sphere[i];
		std::vector<std::vector<float>> FaceInterpolant = *Interpolant[i];

		for (int j = 0; j < FaceCube.size(); j++) {
			
			glDisable(GL_LIGHTING);
			glPointSize(5.0f);

			if (i < 2)
				glColor3d(1, 0, 0);
			else if (i < 4)
				glColor3d(1, 1, 1);
			else
				glColor3d(0, 0, 1);

			glBegin(GL_POINTS);
				glVertex3f(FaceCube[j][0], FaceCube[j][1], FaceCube[j][2]);
			glEnd();

			if(FaceCube[j][0] >= FaceSphere[j][0])
				FaceCube[j][0] += FaceInterpolant[j][0] * 0.005;

			if (FaceCube[j][1] >= FaceSphere[j][1])
				FaceCube[j][1] += FaceInterpolant[j][1] * 0.005;

			if (FaceCube[j][2] >= FaceSphere[j][2])
				FaceCube[j][2] += FaceInterpolant[j][2] * 0.005;
			
		}
	}
}

// Update graphics window.
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 5, -10, 0, 0, 10, 0, 1, 0);          // from (x,y,z), look at point (x,y,z), upvector (x,y,z)
	//gluLookAt(-5, 5, -15, 0, 0, 10, 0, 1, 0);          // from (x,y,z), look at point (x,y,z), upvector (x,y,z)
	gluLookAt(-10, 5, -20,
			  0, 0, 10,
			  0, 1, 0);


	if (!vectorsInitialized)
		initializeVectors();
	if (!generated)
		generatePoints(0.2);
	if (!generatedMorphed)
		generateMorphedPoints();
	if (!generatedInterpolation)
		generateInterpolation();
	if(morphing)
		cubeToSphereMorph();

	if (!morphing) {
		//Draw Cube
		glPushMatrix();

		for (int i = 0; i < 6; i++) {
			std::vector<std::vector<float>> Face = *Cube[i];
			for (int j = 0; j < 25; j++) {

				glDisable(GL_LIGHTING);
				glPointSize(5.0f);

				if (i < 2)
					glColor3d(1, 0, 0);
				else if (i < 4)
					glColor3d(1, 1, 1);
				else
					glColor3d(0, 0, 1);

				glBegin(GL_POINTS);
				glVertex3f(Face[j][0], Face[j][1], Face[j][2]);
				glEnd();
			}
		}

		glPopMatrix();
	}

	/*
	//Draw Sphere
	glPushMatrix();

	for (int i = 0; i < 6; i++) {
		std::vector<std::vector<float>> Face = *Sphere[i];
		for (int j = 0; j < 25; j++) {

			glDisable(GL_LIGHTING);
			glPointSize(5.0f);

			if (i < 2)
				glColor3d(1, 0, 0);
			else if (i < 4)
				glColor3d(0, 1, 0);
			else
				glColor3d(0, 0, 1);

			glBegin(GL_POINTS);
			glVertex3f(Face[j][0], Face[j][1], Face[j][2]);
			glEnd();
		}
	}

	glPopMatrix();
	*/

	glutSwapBuffers();
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

	case 'm':
		morphing = true;
		break;

	case 27:
		exit(0);
	}
}

int main(int argc, char** argv)
{
	//display to console controls
	cout <<
		"Assignment 2: Part 1, Morphing" << endl <<
		"Press these keys:" << endl <<
		" 'm'          morph cube" << endl <<
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
