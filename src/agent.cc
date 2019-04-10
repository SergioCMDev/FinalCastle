//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <agent.h>



void Agent::init(World* world, const Body::Type type, const Agent::Type agentType) {
	//void Agent::init(World* world, const Body::Type type) {
	world_ = world;
	type_ = agentType;
	//body_.init(type, this, agentType);
	//mind_.init(world, &body_, agentType);
	body_.init(type, this);
	//mind_.init(world, &body_);
}

void Agent::shutdown() {
	world_ = nullptr;
}

void Agent::update(const uint32_t dt) {
	//mind_.update(dt);
	body_.update(dt);
}

void Agent::render() const {
	body_.render();
}