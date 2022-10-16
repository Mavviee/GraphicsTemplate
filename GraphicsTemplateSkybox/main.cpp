
#include "core.h"
#include <math.h>
#include "cMesh.h"
#include "cCamera.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

using namespace std;
using namespace glm;


/////////////////////////////////////////////////////////////////////////////////////
// global variables
/////////////////////////////////////////////////////////////////////////////////////
cScene Scene;

unsigned int initWidth = 800;
unsigned int initHeight = 800;



/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

/////////////////////////////////////////////////////////////////////////////////////
// sets up keyboard controls and camera movement
/////////////////////////////////////////////////////////////////////////////////////
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	// ignore key up (key release) events
	if (action == GLFW_RELEASE) 
		return;	

	cCamera* pCamera = &Scene.m_Camera[Scene.m_cameraId];

	// process keyboard inputs here..
	switch (key)
	{
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_X:
			glfwSetWindowShouldClose(window, true);
		break;


		// very simple camera controls to help navigate the scene
		case GLFW_KEY_A:
		{
			// rotate camera about y-axis
			pCamera->m_rot.y += 1.0f;
		}break;

		case GLFW_KEY_D:
		{
			// rotate camera about y-axis
			pCamera->m_rot.y -= 1.0f;
		}break;

		case GLFW_KEY_W:
		{
			// rotate camera about x-axis
			pCamera->m_rot.x -= 1.0f;
		}break;

		case GLFW_KEY_S:
		{
			// rotate camera about x-axis
			pCamera->m_rot.x += 1.0f;
		}break;

		case GLFW_KEY_UP:
		{
			// zoom out along z-axis
			if (pCamera->m_pos.z > 2.0f)
			{
				Scene.m_Mesh[0].m_transform.m_pos.z -= 0.25f;
				pCamera->m_pos.z -= 0.25f;
			}
			if (Scene.m_cameraId == 1) // this light postioned at the light source 
				Scene.m_Light[Scene.m_lightId].m_pos.z = pCamera->m_pos.z;
		}break;

		case GLFW_KEY_DOWN:
		{
			// zoom in along z-axis
			if (pCamera->m_pos.z < 14.0f)

			{
				Scene.m_Mesh[0].m_transform.m_pos.z += 0.25f;
				pCamera->m_pos.z += 0.25f;
			}

			if (Scene.m_cameraId == 1) // this light is positioned at the light source, so moves the light and camera together 
				Scene.m_Light[Scene.m_lightId].m_pos.z = pCamera->m_pos.z;

		}break;
		// this key allows the the player to toggle on and off wire frame
		case GLFW_KEY_E:
		{
			// zoom in along z-axis
			if (pCamera->m_pos.z < 14.0f)

			{
				if (!Scene.isWireframe) {
					Scene.isWireframe = true;
				}
				else {
					Scene.isWireframe = false;
				}
			}

		}break;

		default:
		{
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// renderScene
/////////////////////////////////////////////////////////////////////////////////////
void renderScene()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	////////////////////////////////////////////////////////////////////////////////
	// Render mesh objects here..
	////////////////////////////////////////////////////////////////////////////////
	Scene.render();
	
	
	glBindVertexArray(0);       	
}

/////////////////////////////////////////////////////////////////////////////////////
// printDebugInfo() - print version info to console
/////////////////////////////////////////////////////////////////////////////////////
void printDebugInfo()
{
	// Print info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

#ifdef GL_SHADING_LANGUAGE_VERSION
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

	printf("Using GLEW version %s.\n", glewGetString(GLEW_VERSION));
	printf("------------------------------\n");
	printf("Press ESCAPE or 'X' or 'x' to exit.\n");
}

/////////////////////////////////////////////////////////////////////////////////////
// DebugOutput
// Used to output openGL debug info
// KHR_debug runs on all systems running openGL4.3 or later
/////////////////////////////////////////////////////////////////////////////////////
void DebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	cout << "debug call: " << msg << endl;
}

/////////////////////////////////////////////////////////////////////////////////////
// main()
/////////////////////////////////////////////////////////////////////////////////////
int main() 
{
	// initialise glfw
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "GraphicsTemplate", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stdout, "Failed to create GLFW window!\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	
	// initialise glew
	glewInit();

	// print version info 
	printDebugInfo();

	glDebugMessageCallback(DebugOutput, NULL);

	// Set callback function for resizing the window
	glfwSetFramebufferSizeCallback(window, resize);

	// Set callback for keyboard events
	glfwSetKeyCallback(window, keyboard);

	resize(window, initWidth, initHeight);

	////////////////////////////////////////////////////
	// initialise scene - geometry and shaders etc
	////////////////////////////////////////////////////
	Scene.init();

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
//		glfwWaitEvents();					// Use this if no animation.
		//glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();				// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}

