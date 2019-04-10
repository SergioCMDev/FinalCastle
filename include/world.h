//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __WORLD_H__
#define __WORLD_H__ 1

#include <mathlib/vec2.h>
#include <defines.h>

#include <cstdio>
#include <agent.h>
//#include <body.h>

using MathLib::Vec2;

class World {
public:
	World() {
		for (size_t i = 0; i < MAX_AGENTS; i++)
		{
			soldiers[i].init(this, Body::Type::Autonomous, Agent::Type::Soldier);
			workers[i].init(this, Body::Type::Autonomous, Agent::Type::Worker);
			guards[i].init(this, Body::Type::Autonomous, Agent::Type::Guard);
		}

	};
	~World() {
		for (int i = 0; i < MAX_AGENTS; i++) {

			soldiers[i].shutdown();
			workers[i].shutdown();
			guards[i].shutdown();
		}
	}


	void update(const float dt) {
		for (int i = 0; i < MAX_AGENTS; i++) {

			soldiers[i].update(dt);
			workers[i].update(dt);
			guards[i].update(dt);
		}
	}
	void render() {
		Sprite s;
		s.loadFromFile(MAP);
		s.render();
		for (size_t i = 0; i < MAX_AGENTS; i++)
		{
			soldiers[i].render();
			guards[i].render();
			workers[i].render();
		}
	}
private:
	Agent soldiers[MAX_AGENTS];
	Agent workers[MAX_AGENTS];
	Agent guards[MAX_AGENTS];
};

#endif