
#include "World.hpp"
#include "Model.hpp"
#include <GL/glew.h>
#include <algorithm>
#include <iostream>


World::World()
{
	setViewAngle(0, 0, 0);
}



void World::addModel(const std::shared_ptr<Model>& model)
{
	models.push_back(model);
}



void World::render()
{
	int totalVertexCount = 0;

	for_each (models.begin(), models.end(), 
		[&](const std::shared_ptr<Model>& model)
		{
			GLuint cameraAngle = glGetUniformLocation(model->getProgram(), "cameraAngle");
			glUniform3fv(cameraAngle, 1, rotation); //apply view angle
			totalVertexCount += model->getVertexCount();
		});

	glDrawArrays(GL_POINTS, 0, totalVertexCount);
}



void World::setViewAngle(float x, float y, float z)
{
	rotation[X_AXIS] = x;
	rotation[Y_AXIS] = y;
	rotation[Z_AXIS] = z;
}
	


void World::rotateCameraX(float theta)
{
	rotation[X_AXIS] += theta;
	ensureRotationRange(rotation[X_AXIS]);
}



void World::rotateCameraY(float theta)
{
	rotation[Y_AXIS] += theta;
	ensureRotationRange(rotation[Y_AXIS]);
}



void World::rotateCameraZ(float theta)
{
	rotation[Z_AXIS] += theta;
	ensureRotationRange(rotation[Z_AXIS]);
}



/* Ensures that 'value' is in the range of [0, 360) */
void World::ensureRotationRange(float& value)
{
	while (value >= 360.0f)
		value -= 360.0f;

	while (value < 0)
		value += 360.0f;
}
