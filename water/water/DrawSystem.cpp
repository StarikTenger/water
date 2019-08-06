#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Water");
	loadTextures();
	
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	fillRect(w / 2, h / 2, w, h, Color(255, 255, 255));
	//line(0, 0, 600, 600, Color(255, 255, 255));
	
	sf::Sprite sprite; sf::Texture tex; tex.loadFromImage(sys.backgroundImage);
	sprite.setTexture(tex);
	//window->draw(sprite);
	for (std::vector<Vector2d>& wall : sys.walls) {
		for (int i = 0; i < wall.size() - 1; i++) {
			line(wall[i].x, wall[i].y, wall[i+1].x, wall[i+1].y, Color(0, 0, 0));
		}
	}
	for (Body* body : system->bodies) {
		Vector2d d(8, 10);
		fillCircle(body->pos.x, body->pos.y, body->r, (body->color*d.x+Color(0,0,255)*d.y)/(d.x+d.y));
		
	}
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
