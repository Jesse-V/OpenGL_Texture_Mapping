
#include "Cube.hpp"


std::vector<std::shared_ptr<DataBuffer>> Cube::getDataBuffers()
{
	std::vector<std::shared_ptr<DataBuffer>> buffers;

	auto vBuffer = std::make_shared<VertexBuffer>(getMesh());
	buffers.push_back(vBuffer);

	auto tBuffer = getTextureBuffer();
	buffers.push_back(tBuffer);

	return buffers;
}



std::shared_ptr<Mesh> Cube::getMesh()
{
	auto mesh = std::make_shared<Mesh>();

	addVertices(mesh);
	addIndices(mesh);
	mesh->calcNormalsMWE();

	return mesh;
}



//make a cube, centered at the origin, sides aligned with axes
void Cube::addVertices(std::shared_ptr<Mesh>& mesh)
{
	mesh->vertices.push_back(glm::vec3(-0.5, -0.5,  0.5));
	mesh->vertices.push_back(glm::vec3(-0.5,  0.5,  0.5));
	mesh->vertices.push_back(glm::vec3( 0.5,  0.5,  0.5));
	mesh->vertices.push_back(glm::vec3( 0.5, -0.5,  0.5));
	mesh->vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
	mesh->vertices.push_back(glm::vec3(-0.5,  0.5, -0.5));
	mesh->vertices.push_back(glm::vec3( 0.5,  0.5, -0.5));
	mesh->vertices.push_back(glm::vec3( 0.5, -0.5, -0.5));
}



void Cube::addIndices(std::shared_ptr<Mesh>& mesh)
{
	int indices[36];

	//front side
	indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
	indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

	//Back side
	indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
	indices[9]  = 4; indices[10] = 7; indices[11] = 6;

	//Left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	//Right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	//top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	//bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	for (int j = 0; j < 36; j += 3)
		mesh->triangles.push_back(Triangle(indices[j], indices[j + 1], indices[j + 2]));
}



std::shared_ptr<TextureBuffer> Cube::getTextureBuffer()
{
	auto texture = std::make_shared<TextureBuffer>();

	/*
	for (int j = 0; j < 6; j++)
	{
		texture->tex_coords[j * 6 + 0] = glm::vec2(0, 0);
		texture->tex_coords[j * 6 + 1] = glm::vec2(0, 1);
		texture->tex_coords[j * 6 + 2] = glm::vec2(1, 1);
		texture->tex_coords[j * 6 + 3] = glm::vec2(0, 0);
		texture->tex_coords[j * 6 + 4] = glm::vec2(1, 1);
		texture->tex_coords[j * 6 + 5] = glm::vec2(1, 0);
	}*/

	for (int j = 0; j < 64; j++)
	{
		for (int k = 0; k < 64; k++)
		{
			GLubyte c = (((j & 0x8) == 0) ^ ((k & 0x8) == 0)) * 255;
			texture->image[j][k][0] = texture->image[j][k][1] = texture->image[j][k][2] = c;
		}
	}

	//for (int j = 0; j < 36; j++)
	//	texture->tex_coords[j] = glm::vec2(0, 0);

	/*int index = 0;

	quad(1, 0, 3, 2, index, texture);
	quad(2, 3, 7, 6, index, texture);
	quad(3, 0, 4, 7, index, texture);
	quad(6, 5, 1, 2, index, texture);
	quad(4, 5, 6, 7, index, texture);
	quad(5, 4, 0, 1, index, texture);*/

	//quad(1, 2, 3, 4, index, texture);
	//quad(5, 6, 7, 8, index, texture);
	//quad(2, 3, 7, 6, index, texture);
	//quad(2, 3, 7, 6, index, texture);
	//quad(2, 3, 7, 6, index, texture);

	return texture;
}

/*
void Cube::quad(int a, int b, int c, int d, int& index, std::shared_ptr<Mesh>& mesh)
{
	mesh->tex_coords[index++] = glm::vec2(0, 0);
	mesh->tex_coords[index++] = glm::vec2(0, 1);
	mesh->tex_coords[index++] = glm::vec2(1, 1);
	mesh->tex_coords[index++] = glm::vec2(0, 0);
	mesh->tex_coords[index++] = glm::vec2(1, 1);
	mesh->tex_coords[index++] = glm::vec2(1, 0);
}
*/
