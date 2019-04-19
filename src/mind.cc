//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <mind.h>
#include <body.h>
#include <world.h>
#include <defines.h>
#include <iterator>

void Mind::init(World* world, Body* body, Agent* agent) {
	world_ = world;
	body_ = body;
	agent_ = agent;
	astar = Astar();
}

void Mind::update(const uint32_t dt) {
	switch (agent_->type_) {
	case Agent::Type::Guard: {
		body_->setPosition(body_->getKinematic()->position + MathLib::Vec2(1, 1));
		break;
	}

	case Agent::Type::Soldier: {
		break;

	}
	case Agent::Type::Worker: {
		if (!agent_->working) {
			//agent_->working = !agent_->working;
			MathLib::Vec2 actualPosition = body_->getKinematic()->position;
			if (DifferentPositions(actualPosition, ENTRADA_ZONA_DESCANSO)) {
				if (astar.listaCerrada.empty()) {
					astar.SetValues(actualPosition, ENTRADA_ZONA_DESCANSO);
					astar.GetPath();
				}
				MathLib::Vec2 finalPosition = astar.nodoDestino.GetPosition();
				Node inicio = Node(actualPosition.x(), actualPosition.y(), false, false, NULL);

				MathLib::Vec2 newPosition =	astar.GetNextPosition(inicio);
				MathLib::Vec2 offset = (newPosition - actualPosition);
				body_->setPosition(actualPosition + MathLib::Vec2(offset.x(), offset.y()));
			}

		}
		else {
			//agent_->working = !agent_->working;

		}
		break;
	}
	};
}




