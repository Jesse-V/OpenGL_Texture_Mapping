
#include "World/Scene.hpp"
#include "World/Camera.hpp"
#include "Modeling/Cube.hpp"
#include <iostream>
#include <thread>

const float ROTATION_SPEED = 0.015;
const float TRANSLATION_SPEED = 1.1;
const float LIGHT_MOVEMENT_SPEED = 0.007f;

Scene scene;
std::shared_ptr<Light> light = std::make_shared<Light>();


/*	Causes the current thread to sleep for the specified number of milliseconds */
void sleep(int milliseconds)
{
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration); //forget time.h or windows.h, this is the real way to sleep!
}



void onDisplay()
{
	glClearColor(.39f, 0.58f, 0.93f, 0.0f);	//nice blue background
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	scene.render();

	glm::vec3 lightPos = light->getPosition();
	lightPos.x += LIGHT_MOVEMENT_SPEED;
	lightPos.y += LIGHT_MOVEMENT_SPEED;
	lightPos.z += LIGHT_MOVEMENT_SPEED;
	light->setPosition(lightPos);

	glutSwapBuffers();
	sleep(50); //20 fps
	glutPostRedisplay();
}



void onKey(unsigned char key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case 'w':
			camera->moveY(ROTATION_SPEED);
			break;

		case 's':
			camera->moveY(-ROTATION_SPEED);
			break;

		case 'a':
			camera->moveX(-ROTATION_SPEED);
			break;

		case 'd':
			camera->moveX(ROTATION_SPEED);
			break;

		case 'q':
			camera->moveZ(ROTATION_SPEED);
			break;

		case 'e':
			camera->moveZ(-ROTATION_SPEED);
			break;
	}
}



void onSpecialKey(int key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case GLUT_KEY_UP:
			camera->pitch(TRANSLATION_SPEED);
			break;

		case GLUT_KEY_DOWN:
			camera->pitch(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_LEFT:
			camera->yaw(TRANSLATION_SPEED);
			break;

		case GLUT_KEY_RIGHT:
			camera->yaw(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_PAGE_UP:
			camera->roll(-TRANSLATION_SPEED);
			break;

		case GLUT_KEY_PAGE_DOWN:
			camera->roll(TRANSLATION_SPEED);
			break;
	}
}



/* Initializes glut. Sets the window size and title to the specified values */
void initializeGlutWindow(int width, int height, const std::string& windowTitle)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());
}



void initializeApplication()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	scene.init();

	Cube cube;
	RenderableObject cubeObj(scene.getProgram()->getHandle(), cube.getDataBuffers());
	cubeObj.setModelMatrix(glm::translate(glm::mat4(), glm::vec3(0.0, -0.1, 0.0)));
	scene.addModel(cubeObj);

	scene.setAmbientLight(glm::vec3(0.3, 0, 0));
	light->setPosition(glm::vec3(0.3f, -1.7f, -0.5f));
	scene.addLight(light); //todo: send light color and power to GPU

	auto camera = std::make_shared<Camera>();
	camera->lookAt(glm::vec3(0.72, 0.49, 0.49), glm::vec3(0.54, 0.72, 0.42));
	camera->setPosition(glm::vec3(1.56, 1.23, 1.144));
	scene.setCamera(camera);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	initializeGlutWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), "Lighting and Texture Mapping in OpenGL - Jesse Victors");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	try
	{
		glutDisplayFunc(onDisplay);
		glutKeyboardFunc(onKey);
		glutSpecialFunc(onSpecialKey);

		initializeApplication();
		glutMainLoop();

	}
	catch (std::exception& e)
	{
		std::cerr << std::endl;
		std::cerr << e.what();
		std::cerr << std::endl;
	}

	return EXIT_SUCCESS;
}
