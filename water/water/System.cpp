#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace geom;
using namespace random;
using namespace std;

System::System(){
	borders = {600, 600};
	g = {0, 10};
	/*walls.push_back(
		{
			{400, 0},
			{400, 550}
		}
	);*/
	for (int x = 0; x < 40; x++) {
		for (int y = 0; y < 40; y++) {
			bodies.push_back(new Body());
			bodies.back()->pos = { 0 + x*8.0 + random::floatRandom(-1, 1, 3), 10 + y*8.0 };
			bodies.back()->r = 4;
		}
	}
	backgroundImage.loadFromFile("background.png");
	
}

System::~System() {
}

void System::fillChunks() {
	
	chunks = {};
	for (int x = 0; x < borders.x / chunkSize + 2; x++) {
		chunks.push_back({});
		for (int y = 0; y < borders.y / chunkSize + 2; y++) {
			chunks[x].push_back({});
		}
	}

	for (Body* body : bodies) {
		chunks[int(body->pos.x / chunkSize)][int(body->pos.y / chunkSize)].push_back(body);
	}
}

std::vector<Body*> System::neighbors(Vector2d pos) {
	std::vector<Body*> arr;
	int posX = int(pos.x / chunkSize);
	int posY = int(pos.y / chunkSize);
	int s = 0;
	for (int x = std::max(0, posX - 1); x <= std::min((int)chunks.size() - 1, posX + 1); x++) {
		for (int y = std::max(0, posY - 1); y <= std::min((int)chunks[0].size() - 1, posY + 1); y++) {
			for (Body* body : chunks[x][y]) {
				arr.push_back(body);
			}
			s = std::max(s, (int)chunks[x][y].size());
		}
	}
	//std::cout << s << "\n";
	return arr;
}
