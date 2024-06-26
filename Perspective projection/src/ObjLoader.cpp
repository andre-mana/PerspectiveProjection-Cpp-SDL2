#include "ObjLoader.h"

ObjLoader::ObjLoader(const std::string& filename) : objFile(filename) {
	if (!objFile.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
	}
}


bool ObjLoader::load(std::vector<Pvector>& points, std::vector<std::vector<int>>& faces) {
	int slashPos = 0;
	std::string verticeIndex;
	std::stringstream lineStream;

	if (!objFile.is_open()) {
		std::cerr << "File is not open!" << std::endl;
		return false;
	}

	while (std::getline(objFile, line)) {
		//read vertices
		if (line[0] == 'v' && line[1] == ' ') {
			lineStream.clear();
			lineStream.str(line);
			lineStream.ignore(2);
			lineStream >> x >> y >> z;
			points.push_back(Pvector(x, y, z));
		}

		//read polygon 
		if (line[0] == 'f') {
			lineStream.clear();
			lineStream.str(line);
			lineStream.ignore(2);

			while (lineStream >> word) {
				slashPos = word.find('/');
				if (slashPos != std::string::npos) {
					faceIndices.push_back(abs(std::stoi(word.substr(0, slashPos))));
				}
			}

			faces.push_back(faceIndices);
			faceIndices.clear();
		}
	}

	return true;
}

