#include <stdlib.h>
#include<iostream>
using namespace std;
#include <string.h>

#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include<math.h>

int rx=50, ry=25;
int xCenter=100, yCenter=100;


void plotpts(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void render_loop()
{
	

	float x = 0;
	float y = ry;
	float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * (0.25);
	float dx = 2 * (ry * ry) * x;
	float dy = 2 * (rx * rx) * y;
	while (dx < dy)
	{
		plotpts(xCenter + x, yCenter + y);
		plotpts(xCenter - x, yCenter + y);
		plotpts(xCenter + x, yCenter - y);
		plotpts(xCenter - x, yCenter - y);
		if (p1 < 0)
		{
			x = x + 1;
			dx = 2 * (ry * ry) * x;
			p1 = p1 + dx + (ry * ry);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dx = 2 * (ry * ry) * x;
			dy = 2 * (rx * rx) * y;
			p1 = p1 + dx - dy + (ry * ry);
		}
	}
	

	float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);


	while (y > 0)
	{
		
		plotpts(xCenter + x, yCenter + y);
		plotpts(xCenter - x, yCenter + y);
		plotpts(xCenter + x, yCenter - y);
		plotpts(xCenter - x, yCenter - y);     
		if (p2 > 0)
		{
			x = x;
			y = y - 1;
			dy = 2 * (rx * rx) * y;
			p2 = p2 - dy + (rx * rx);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dy = dy - 2 * (rx * rx);
			dx = dx + 2 * (ry * ry);
			p2 = p2 + dx -
				dy + (rx * rx);
		}
	}

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);     
	glColor3f(1.0, 0.0, 0.0);          
	glPointSize(2.0);              


	render_loop();
	glFlush();
}
int main(int argc, char* argv[])
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(400, 400, "LearnOpenGL", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// set up view
	glViewport(0, 0, 400, 400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, 400.0, 0.0, 400.0, 0.0, 1.0); // this creates a canvas you can do 2D drawing on


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Draw gears
		render_loop();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}
