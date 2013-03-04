#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "Triangle.struct"
#include <GL/glew.h>

class Model
{
	public:
		Model();
		GLuint getProgram();
		virtual std::vector<Point> getVertices() = 0;

	protected:
		GLuint program;
		
		void initializeProgram();
		void bindVertices();
		void storeVertices(std::vector<Point> vertices);
		void initVertexPositionAttribute(const GLuint& program);
};

#endif