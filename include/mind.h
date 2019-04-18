//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __MIND_H__
#define __MIND_H__ 1

#include <cstdint>
#include <defines.h>
#include <Astar.h>

class Body;
class World;
class Agent;


class Mind {
public:
	Mind() {};
	~Mind() {};
	void init(World* world, Body* body, Agent* type);
	void update(const uint32_t dt);
	//void GetNextPosition(Node &inicio, MathLib::Vec2 &finalPosition, MathLib::Vec2 &newPosition);
	MathLib::Vec2 GetNextPosition(Node &inicio, MathLib::Vec2 &finalPosition);
	World* world_;
private:
	Body* body_;
	Agent* agent_;
	Astar astar;

};

#endif