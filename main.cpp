
#include "World/Scene.hpp"
#include "World/Camera.hpp"
#include <iostream>


Scene scene;


void onDisplay()
{
	// Clear the background as black
	glClearColor(.39f, 0.58f, 0.93f, 0.0f);	//nice blue background
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// render the scene
	scene.render();

	// Display the newly rendered image to the screen
	glutSwapBuffers();
}



void onKey(unsigned char key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case 'w':  camera->moveY( 0.01);  break;
		case 's':  camera->moveY(-0.01);  break;
		case 'a':  camera->moveX(-0.01);  break;
		case 'd':  camera->moveX( 0.01);  break;
		case 'q':  camera->moveZ( 0.01);  break;
		case 'e':  camera->moveZ(-0.01);  break;
	}

	glutPostRedisplay();
}



void onSpecialKey(int key, int, int)
{
	std::shared_ptr<Camera> camera = scene.getCamera();

	switch(key)
	{
		case GLUT_KEY_UP:        camera->pitch( 1.0); break;
		case GLUT_KEY_DOWN:      camera->pitch(-1.0); break;
		case GLUT_KEY_LEFT:      camera->yaw( 1.0);   break;
		case GLUT_KEY_RIGHT:     camera->yaw(-1.0);   break;
		case GLUT_KEY_PAGE_UP:   camera->roll(-1.0);  break;
		case GLUT_KEY_PAGE_DOWN: camera->roll( 1.0);  break;
	}

	glutPostRedisplay();
}



int main(int argc, char **argv)
{
	// Glut-related initialising functions
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("hw2");


	// Extension wrangler initialising
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

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		scene.init();
		scene.loadCubeModel();

		std::shared_ptr<Camera> camera = std::make_shared<Camera>();
		camera->lookAt(glm::vec3(0, -0.2, -1));
		camera->setPosition(glm::vec3(0, 0.03, 2));
		scene.setCamera(camera);

		glutMainLoop();

	}
	catch (std::exception& e)
	{
		std::cerr << std::endl << std::endl;
		std::cerr << e.what();
		std::cerr << std::endl << std::endl;
	}

	return EXIT_SUCCESS;
}
