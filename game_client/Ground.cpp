#include "Ground.h"
#include <iostream>

Ground::Ground(int x, int y, float size,  int padX, int padY, uint shader)
{
	tilesX = x;
	tilesY = y;
	this->padX = padX;
	this->padY = padY;
	totalX = (x + (2 * padX));
	totalY = (y + (2 * padY));
	tileSize = size;

	int gridsize = totalX * totalY;

	grid = new TILE_TYPE[gridsize];


	for (int i = 0; i < NUM_TILES; i++) {
		Model * temp = new Model(shader);
		glm::vec3 color = getColor((TILE_TYPE)i);
		glm::vec3 min(0, 0, 0);
		glm::vec3 max(size, 0, size);
		temp->makeTile(min, max, color, getTexture((TILE_TYPE)i));
		tiles.push_back(temp);
	}

	setPadding(TILE_TYPE::BLANK);
}

Ground::~Ground()
{
	delete grid;
	for (Model* tile : tiles) {
		delete tile;
	}
}

Ground::TILE_TYPE Ground::getLoc(int x, int y)
{
	return grid[((padX+x)*totalY) + y + padY];
}

void Ground::setLoc(int x, int y, TILE_TYPE type)
{
	grid[((padX + x) * totalY) + y + padY] = type;
}

void Ground::update(SceneNode * node)
{
	
}

void Ground::draw(SceneNode& node, const glm::mat4& viewProjMtx)
{
	glm::mat4 tileMat = node.transform;
	for (int i = 0; i < totalX; i++) {
		tileMat[3][2] = node.transform[3][2];
		tileMat[3][0] += tileSize;
		for (int j = 0; j < totalY; j++) {
			tileMat[3][2] += tileSize;
			SceneNode temp(NULL, std::string(""), 0);
			temp.transform = tileMat;
			tiles[( (int)grid[(i*totalY) + j] )]->draw(temp, viewProjMtx);
		}
	}
}

void Ground::setPadding(TILE_TYPE type) {
	/*for (int i = 0; i < totalX; i++) {
		for (int j = 0; j < padY; j++) {
			grid[(i * totalY) + j] = type;
		}
	}

	for (int i = 0; i < totalX; i++) {
		for (int j = tilesY+padY; j < totalY; j++) {
			grid[(i * totalY) + j] = type;
		}
	}

	for (int i = 0; i < padX; i++) {
		for (int j = padY; j < tilesY+padY; j++) {
			grid[(i * totalY) + j] = type;
		}
	}

	for (int i = padX+tilesX; i < totalX; i++) {
		for (int j = padY; j < tilesY+padY; j++) {
			grid[(i * totalY) + j] = type;
		}
	}*/

	for (int i = 0; i < totalX; i++) {
		for (int j = 0; j < totalY; j++) {
			grid[(i * totalY) + j] = type;
		}
	}
}

int Ground::getX() {
	return tilesX;
}

int Ground::getY() {
	return tilesY;
}

glm::vec3 Ground::getColor(TILE_TYPE type)
{
	switch (type) {
	case TILE_TYPE::PATH:
		return glm::vec3(.5,.12,.12);
	case TILE_TYPE::TILLED:
		return glm::vec3(.4, .25, .1);
	case TILE_TYPE::NORMAL:
		return glm::vec3(.12, .8, .12);
	case TILE_TYPE::WATER:
		return glm::vec3(.12, .12, .8);
	case TILE_TYPE::BLANK:
		return glm::vec3(1.0);
	}
	return glm::vec3(0);
}

const char* Ground::getTexture(TILE_TYPE type)
{
	switch (type) {
	case TILE_TYPE::PATH:
		return NO_TEXTURE;
	case TILE_TYPE::TILLED:
		return NO_TEXTURE;
	case TILE_TYPE::NORMAL:
		return GRASS_TEXTURE;
	case TILE_TYPE::WATER:
		return WATER_TEXTURE;
	case TILE_TYPE::BLANK:
		return NO_TEXTURE;
	}
	return NULL;
}

Ground * Ground::ground0(uint shader)
{
	int x = 24;
	int y = 20;
	float size = 0.5;
	int padX = 2;
	int padY = 2;

	Ground * ground0 = new Ground(x, y, size, padX, padY, shader);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (i < 2 || i > x-3 || j > y-3) {
				ground0->setLoc(i, j, TILE_TYPE::PATH);
			}
			else if (i > 9 && i < 13 && j > 9 && j < 13) {
				ground0->setLoc(i,j,TILE_TYPE::WATER);
			}
			else {
				ground0->setLoc(i,j,TILE_TYPE::NORMAL);
			}
		}
	}
	return ground0;
}
