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
		MathLib::Vec2 actualPosition = body_->getKinematic()->position;
		if (agent_->status_ == Agent::Status::Relax) {

			if (SamePositions(actualPosition, ZONA_TRABAJO)) {
				getNewPath = true;
				agent_->status_ = Agent::Status::Working;
			}
			else if (DifferentPositions(actualPosition, ZONA_TRABAJO)) {
				body_->destination = ZONA_TRABAJO;

				GoToDestination(actualPosition, body_->destination);
			}
		}
		else if (agent_->status_ == Agent::Status::Working) {
			if (SamePositions(actualPosition, ZONA_TRABAJO)) {
				getNewPath = true;
				body_->destination = ZONA_TRABAJO_FIN_1;
				//body_->destination = ZONA_TRABAJO_FIN_2;
				//body_->destination = ZONA_TRABAJO_FIN_3;
				//agent_->status_ = Agent::Status::Working;

			}
			if (SamePositions(actualPosition, ZONA_TRABAJO_FIN_1)) {
				getNewPath = true;
				body_->destination = ZONA_TRABAJO;
				//body_->destination = ZONA_TRABAJO_FIN_2;
				//body_->destination = ZONA_TRABAJO_FIN_3;
				//agent_->status_ = Agent::Status::Working;

			}
			if (DifferentPositions(actualPosition, body_->destination)) {
				GoToDestination(actualPosition, body_->destination);
			}
			//else {
			//	body_->destination = ZONA_TRABAJO;
			//	//getNewPath = true;

			//}
		}
	};
	}
}

void Mind::GoToDestination(MathLib::Vec2 &actualPosition, const MathLib::Vec2 &destination)
{
	Node inicio = Node(actualPosition.x(), actualPosition.y(), false, false);

	if (astar.listaCerrada.empty() || getNewPath) {
		astar.listaCerrada.clear();
		astar.listaCerrada.push_back(inicio);
		astar.SetValues(actualPosition, destination);
		astar.GetPath();
		getNewPath = false;
	}

	MathLib::Vec2 newPosition = astar.GetNextPosition(inicio);

	MathLib::Vec2 offset = (newPosition - actualPosition);
	body_->setPosition(actualPosition + MathLib::Vec2(offset.x(), offset.y()));
	inicio.~Node();
}




