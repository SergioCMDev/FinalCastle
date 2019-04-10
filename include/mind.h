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
//#include <agent.h>

class Body;
class World;
class Agent;


class Mind {
public:
	Mind() {};
	~Mind() {};
	void init(World* world, Body* body, Agent* type);
	void update(const uint32_t dt);
	World* world_;
private:
	Body* body_;
	Agent* agent_;
};

#endif