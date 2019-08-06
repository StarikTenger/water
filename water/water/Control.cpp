#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
}

Control::~Control() {

}

Vector2d Control::getCursorPos() {
	return geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		
		events();
		drawSys.mouse = mouse;
		
		
		for (int i = 0; i < 2; i++) {
			sys.step();
			if (mouse.state) {
				for (Body* body : sys.bodies) {
					if (geom::distance(mouse.pos, body->pos) < 100 && geom::distance(mouse.pos, body->pos) > 10) {
						body->vel += geom::direction(mouse.pos, body->pos) / geom::distance(mouse.pos, body->pos) * 100*0;
						body->vel += Vector2d(0, -1 / geom::distance(mouse.pos, body->pos) * 100);
					}
				}
			}
		}
		

		drawSys.system = &sys;
		drawSys.draw();
		drawSys.window->display();

		
	}
}
