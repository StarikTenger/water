#pragma once
#include "Vector2d.h"
#include "Color.h"

class Body {
public:
	Vector2d pos;
	Vector2d vel;
	double m = 1;
	double r = 1;
	Color color;

	Body();
	~Body();
};

