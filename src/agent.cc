//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <agent.h>



void Agent::init(World* world, const Body::Type type, const Agent::Type agentType) {
	world_ = world;
	type_ = agentType;

	mind_.init(world, &body_, this);
	body_.init(type, this);
	switch (type_) {
		case Agent::Type::Guard: {

		break; }
		case Agent::Type::Soldier: {

		break; }
		case Agent::Type::Worker: {
			status_ = Agent::Status::Relax;
		break; }

	}
}

void Agent::shutdown() {
	world_ = nullptr;
}

void Agent::update(const uint32_t dt) {
	mind_.update(dt);
	body_.update(dt);
}

void Agent::render() const {
	body_.render();
}