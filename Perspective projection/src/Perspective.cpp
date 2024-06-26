#include "Perspective.h"
#include "Settings.h"
#include "Pvector.h"
#include "ObjLoader.h"

Perspective::Perspective()
	: window(nullptr), renderer(nullptr),
	distanceToModel(130), angleZ(0), angleY(0), angleX(3.14) {
}

Perspective::~Perspective() {
	clean();
}

bool Perspective::init(const char* title) {
	ObjLoader objLoader("Models/model.obj");

	if (!objLoader.load(points, faces)) {
		std::cerr << "Failed to load OBJ file!" << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	isRunning = true;

	return true;
}

void Perspective::handleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				angleY += 0.05;
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				angleY -= 0.05;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				angleX += 0.05;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				angleX -= 0.05;
			}
		}

		if (event.type == SDL_MOUSEWHEEL) {
			if (event.wheel.y > 0) {
				distanceToModel -= 5;
				if (distanceToModel < 0.01) {
					distanceToModel = 0.01;
				}
			}
			else if (event.wheel.y < 0) {
				distanceToModel += 5;
			}
		}
	}
}

Pvector Perspective::matrixMultiplication(const std::vector<std::vector<float>>& mat1, const Pvector& vec) {
	float x = mat1[0][0] * vec.x + mat1[0][1] * vec.y + mat1[0][2] * vec.z;
	float y = mat1[1][0] * vec.x + mat1[1][1] * vec.y + mat1[1][2] * vec.z;
	float z = mat1[2][0] * vec.x + mat1[2][1] * vec.y + mat1[2][2] * vec.z;

	return Pvector(x, y, z);
}

void Perspective::rotate() {
	angleY += 0.0125;
	angleY = fmod(angleY, 2 * M_PI);
	angleX = fmod(angleX, 2 * M_PI);
	angleZ = fmod(angleZ, 2 * M_PI);

	rotationYMatrix = {
		{ cos(angleY), 0, sin(angleY) },
		{0,1, 0},
		{-sin(angleY),0,cos(angleY)},
	};

	rotationZMatrix = {
		{ cos(angleZ), -sin(angleZ), 0 },
		{sin(angleZ), cos(angleZ), 0},
		{0, 0, 1},
	};

	rotationXMatrix = {
		{ 1, 0, 0 },
		{0, cos(angleX), -sin(angleX)},
		{0, sin(angleX), cos(angleX)},
	};
}

void Perspective::perspectiveProjection() {
	for (int i = 0; i < points.size(); i++) {
		rotatedPoint = matrixMultiplication(rotationYMatrix, points[i]);
		rotatedPoint = matrixMultiplication(rotationZMatrix, rotatedPoint);
		rotatedPoint = matrixMultiplication(rotationXMatrix, rotatedPoint);

		depthFactor = 1.0f / (distanceToModel - rotatedPoint.z);
		aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

		projection = {
			{ depthFactor / aspectRatio, 0, 0},
			{0, depthFactor, 0},
			{0, 0, 1}
		};

		screenPosition = matrixMultiplication(projection, rotatedPoint);
		screenPosition.x = screenPosition.x * SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2;
		screenPosition.y = screenPosition.y * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2;
		screenPointsList.push_back(screenPosition);
	}
}

void Perspective::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < faces.size();i++) {
		for (int j = 0; j < faces[i].size(); j++) {
			currentVertexIndex = faces[i][j] - 1;
			nextVertexIndex = faces[i][(j + 1) % faces[i].size()] - 1;
			SDL_RenderDrawLine(renderer, screenPointsList[currentVertexIndex].x, screenPointsList[currentVertexIndex].y, screenPointsList[nextVertexIndex].x, screenPointsList[nextVertexIndex].y);
		}
	}

	SDL_RenderPresent(renderer);
	screenPointsList.clear();
}

void Perspective::update() {
	rotate();
	perspectiveProjection();
	draw();
}

void Perspective::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Perspective::running() {
	return isRunning;
}
