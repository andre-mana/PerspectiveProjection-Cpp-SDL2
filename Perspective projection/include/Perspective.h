#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Pvector.h"

class Perspective {
public:
	Perspective();
	~Perspective();

	bool init(const char* title);
	void handleEvents();
	void rotate();
	void perspectiveProjection();
	void draw();
	void update();
	void clean();
	bool running();
	Pvector matrixMultiplication(const std::vector<std::vector<float>>& mat1, const Pvector& vec);

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	std::vector<Pvector> points;
	std::vector<std::vector<int>> faces;
	Pvector rotatedPoint;
	float aspectRatio;
	float distanceToModel;
	float angleZ;
	float angleY;
	float angleX;
	float depthFactor;
	Pvector screenPosition;
	std::vector<std::vector<float>>  rotationXMatrix;
	std::vector<std::vector<float>>  rotationYMatrix;
	std::vector<std::vector<float>>  rotationZMatrix;
	int nextVertexIndex;
	int currentVertexIndex;
	std::vector<std::vector<float>> projection;
	std::vector<Pvector> screenPointsList;
};

#endif

