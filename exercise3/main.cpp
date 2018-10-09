/*
* TPG4162 Exercise 3 framework
* Author: Einar Baumann
*
* Based on a Lighthouse3D tutorial:
*  http://www.lighthouse3d.com/tutorials/glut-tutorial/the-code-so-far-v/
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

using namespace std;


/*
*|------------------------------------------------------|
*| Adjust the camera and Draw the desired shape.        |
*| This function is called by the renderScene function. |
*| THIS IS THE ONLY FUNCTION YOU NEED TO EDIT TO        |
*| COMPLETE EXERCISE 3                                  |
*|------------------------------------------------------|
*/
float colorList[4][3] =
{
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f}
};

float* getColorFromTemperature(int const temperature){
    int min = 0;
    int max = 100;
    int n = 4;
    if(temperature < min){
        return colorList[0];
    }else if(temperature > max){
        return colorList[n-1];
    }
    int i = (n-1) * (temperature - min) / (max - min);
    return colorList[i];
}

void drawShape() {
    /*
        1: Adust the camera to center the shape and make it fill the window
    */
	gluLookAt(	0.0f, 1.0f, 6.0f,   // Eye position (x, y, z)
			    0.0f, 1.0f, 0.0f,   // Look at position (x, y, z)
			    0.0f, 1.0f, 0.0f);  // Up-vector (x, y, z)

    /*
        2: Specify the type of shape to draw: glBegin(SHAPE_TYPE). GL_POINTS is just
           a placeholder and needs to be changed.
        3: Specify the vertices with glVertex3f() and colors with glColor3f()
    */

    float vertexcoords[6][3] =		// set up 4 vertices
	{
		{-0.8f,	-0.8f,  0.0f},
        { 0.0f, -0.8f,  0.0f},
        { 0.0f,  0.8f,  0.0f},
		{-0.8f,  0.8f,  0.0f},
        { 0.8f, -0.8f,  0.0f},		// quad upper right corner
		{ 0.8f,  0.8f,  0.0f}
	};

	int vertexcolors[6] = {10, 50, 100, 50, 10, 50};

	glBegin(GL_QUADS);
	//Polygon 1
    for (int i = 0; i < 4; i++){
        glColor3fv(getColorFromTemperature(vertexcolors[i]));
        glVertex3fv(vertexcoords[i]);
    }
    glEnd();

    glBegin(GL_QUADS);
    int polygon2vertices[4] = {2, 5, 6, 3};
    int index;
    for (int i = 0; i < 4; i++){
        index = polygon2vertices[i]-1;
        glColor3fv(getColorFromTemperature(vertexcolors[index]));
        glVertex3fv(vertexcoords[index]);
    }
	glEnd();
}


/*
*|----------------------------------------------------------|
*| Called by glut to display/redisplay stuff in the window. |
*| It is registered as a callback in the main function.     |
*|----------------------------------------------------------|
*/
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Color and Depth Buffers
	glLoadIdentity(); // Reset transformations
    drawShape();                 // Draw the wanted shape
	glMatrixMode(GL_MODELVIEW);  // get back to modelview mode
	glutSwapBuffers();           // Display our matrix (i.e. the figure)
}


/*
*|----------------------------------------------------------|
*| Called by glut to whenever the window is resized         |
*| It is registered as a callback in the main function.     |
*|----------------------------------------------------------|
*/
void changeSize(int w, int h) {

	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
	glLoadIdentity(); // Reset Matrix
	glViewport(0, 0, w, h); // Set the viewport to be the entire window
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // Set the correct perspective.
	glMatrixMode(GL_MODELVIEW); // Get Back to the Modelview
}


/*
*|---------------|
*| Main function |
*|---------------|
*/
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Exercise 3");

	// register glut callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// OpenGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
