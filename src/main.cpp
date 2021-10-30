#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(__APPLE__)
#include <Opengl/gl.h>
#define GL_SILENCE_DEPRECATION
#else
#include <GL/gl.h>
#endif

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[]) {
	GLFWwindow *window;

	printf("Initializing...\n");

	/* Initialize the library */
	if (!glfwInit()) {
		printf("Unable to init GLFW!\n");
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Test window", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		printf("Unable to create window!\n");
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK) {
		printf("Unable to init GLEW!\n");
	}

	printf("Info:\n");
	printf("\tOpenGL version: %s\n", glGetString(GL_VERSION));
	printf("\tGPU vendor: %s\n", glGetString(GL_VENDOR));
	printf("\tRenderer: %s\n", glGetString(GL_RENDERER));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	printf("Closing window...\n");

	return 0;
}