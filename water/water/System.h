#pragma once
#include <vector>
#include <fstream>
#include "Vector2d.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Body.h"


class System{
public:
	double dt = 0.02;

	std::vector<Body*> bodies;
	std::vector<std::vector<Vector2d> > walls;
	Vector2d g;
	Vector2d borders;
	double chunkSize = 10;
	double bounce = 0.1;
	std::vector<std::vector<std::vector<Body*> > > chunks;
	sf::Image backgroundImage;
	System();
	~System();

	void step();
	void fillChunks();
	std::vector<Body*> neighbors(Vector2d pos);
};