#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include<math.h>

void plotpoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(50 + x, y + 50);
    glVertex2i(50 + x, 50 - y);
    glVertex2i(50 + y, x + 50);
    glVertex2i(50 + y, 50 - x);
    glVertex2i(50 - x, 50 - y);
    glVertex2i(50 - y, 50 - x);
    glVertex2i(50 - x, y + 50);
    glVertex2i(50 - y, x + 50);
    glEnd();

}

void render_loop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(2);
    //glLineWidth(2.5);
    glColor3f(1.f, 0.f, 0.f);
    int r = 50;
    float P;
    P = 5/4 - r;
    int x = 0, y = 0;

    y = r;
    int xi = x, yi = y;

    float pi=P;
    //glBegin(GL_POINTS);
    //glVertex2i(x + 50, y + 50);
    //glEnd();


    int count = 1;
    while (xi < y) {
        if (pi <= 0) {
            pi = pi + 2 * xi + 3;
            yi = yi;
            xi = xi + 1;
        }
        else if (pi>0){
            pi = pi + 2 * (xi - yi) + 5;
            yi = yi - 1;
            xi = xi + 1;
        }
        plotpoints(xi, yi);
    }


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