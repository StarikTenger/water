#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <math.h>

void System::step() {
	for (Body* body : bodies) {
		body->vel += g * dt;
	}
	
	

	fillChunks();

	//collision balls
	for (Body* a : bodies) {
		for (Body* b : neighbors(a->pos)) {
			if (a == b)
				continue;
			if (geom::distance(a->pos, b->pos) < a->r + b->r) {
				Vector2d r = geom::direction(a->pos, b->pos);
				double k = (a->r + b->r - geom::distance(a->pos, b->pos))*1000;
				double ang = geom::angle(b->pos - a->pos);
				if (geom::rotate(a->vel, -ang).x < geom::rotate(b->vel, -ang).x) {
					k *= 0.0001;
				}
				if (geom::distance({}, a->vel) < 1) {
					//k = 6000;
				}
				//std::cout << k << "\n";
				Vector2d v = (a->vel*a->m + b->vel*b->m) / (a->m + b->m);
				a->vel += r * k / a->m *dt;
				b->vel -= r * k / b->m *dt;
			}
		}
	}

	//borders collision
	for (Body* body : bodies) {
		if (body->pos.x - body->r < 0 && body->vel.x < 0 || body->pos.x + body->r > borders.x && body->vel.x > 0) {
			body->vel.x *= -bounce;
		}
		if (body->pos.y - body->r < 0 && body->vel.y < 0 || body->pos.y + body->r > borders.y && body->vel.y > 0) {
			body->vel.y *= -bounce;
		}
	}

	//wall collision
	for (Body* body : bodies) {
		for (std::vector<Vector2d>& wall : walls) {
			for (int i = 0; i < wall.size()-1; i++) {
				Vector2d pos = body->pos + body->vel * dt;
				double a = geom::angle(wall[i] - wall[i + 1]);
				Vector2d r = geom::rotate(Vector2d(body->r, 0), a - M_PI/2);
				if (geom::rotate(wall[i]-body->pos, a).y > 0) {
					r = geom::rotate(Vector2d(body->r, 0), a + M_PI / 2);
				}
				if (geom::isCross(body->pos, pos, wall[i] + r, wall[i + 1] + r)) {
					//std::cout << "a\n";
					
					Vector2d vel = geom::rotate(body->vel, -a);
					vel.y *= -bounce;
					body->vel = geom::rotate(vel, a);
				}
			}
		}
	}


	
	//color management
	for (Body* body : bodies) {
		double k = 0.1*10;
		sf::Color sfCol = backgroundImage.getPixel(body->pos.x, body->pos.y);
		Color col(sfCol.r, sfCol.g, sfCol.b);
		body->color = body->color + (col - body->color) *k*dt;
		//std::cout << ((col - body->color) * k * dt).r;
	}

	//wet friction
	for (Body* body : bodies) {
		//body->color = {};
		double k = 0;
		body->vel -= body->vel * k * dt;
	}

	for (Body* body : bodies) {
		body->pos += body->vel * dt;
	}
}