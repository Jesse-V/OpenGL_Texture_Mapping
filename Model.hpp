#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "Triangle.struct"
#include <GL/glew.h>
#include <string>

class Model
{
	public:
		GLuint getProgram();
		virtual std::vector<Point> getVertices() = 0;
		int getVertexCount();

	protected:
		Model();
		void initializeProgram(const std::string& vertexShader, const std::string& fragmentShader);
		void bindVertices();
		void storeVertices(std::vector<Point> vertices);
		void initVertexPositionAttribute(const GLuint& program);

		GLuint program;
		int vertexCount;
};

#endif
