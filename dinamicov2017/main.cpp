#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "chai3d.h"
 
const int WINDOW_SIZE_W = 800;
const int WINDOW_SIZE_H = 600;

void resizeWindow(int w, int h);
void keySelect(unsigned char key, int x, int y);
void updateGraphics(void);

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WINDOW_SIZE_W) / 2, 
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_SIZE_H) / 2
	);
	glutInitWindowSize(WINDOW_SIZE_W, WINDOW_SIZE_H);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(updateGraphics);
	glutKeyboardFunc(keySelect);
	glutReshapeFunc(resizeWindow);
	glutSetWindowTitle("Piston Haptics");

	glutMainLoop();
	return 0;
}

void updateGraphics(void) {
	// Swap buffers
	glutSwapBuffers();

	// check for any OpenGL errors
	GLenum err;
	err = glGetError();
	if (err != GL_NO_ERROR) printf("Error:  %s\n", gluErrorString(err));

	glutPostRedisplay();
}
void keySelect(unsigned char key, int x, int y) {
	if ((key == 27) || (key == 'x')) {
		exit(0);
	}
}
void resizeWindow(int w, int h) {
	glViewport(0, 0, w, h);
}
