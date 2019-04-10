//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <mind.h>
#include <body.h>
#include <world.h>

void Mind::init(World* world, Body* body, Agent* agent) {
	world_ = world;
	body_ = body;
	agent_ = agent;
}

void Mind::update(const uint32_t dt) {
	switch (agent_->type_) {
	case Agent::Type::Guard: {
		body_->setPosition(body_->getKinematic()->position + MathLib::Vec2(1, 1));
		break;
	}

							 //case Agent::AgentType::Soldier: {

							 //}
							 //case Agent::AgentType::Worker: {

							 //}
	};
}


