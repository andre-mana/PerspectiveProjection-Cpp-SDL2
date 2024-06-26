#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Pvector.h"

class ObjLoader {
public:
	ObjLoader(const std::string& filename);
	bool load(std::vector<Pvector>& points, std::vector<std::vector<int>>& faces);

private:
	std::vector<int> faceIndices;
	std::ifstream objFile;
	std::string line;
	std::string word;
	float x;
	float y;
	float z;
};

#endif

