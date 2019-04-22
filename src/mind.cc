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

			if (SamePositions(actualPosition, ENTRADA_ZONA_DESCANSO)) {
				getNewPath = true;
				agent_->status_ = Agent::Status::TimeToWork;

			}
			else if (DifferentPositions(actualPosition, ENTRADA_ZONA_DESCANSO)) {
				if (astar.listaCerrada.empty() || getNewPath) {
					astar.listaCerrada.clear();

					astar.SetValues(actualPosition, ENTRADA_ZONA_DESCANSO);
					astar.GetPath();
					getNewPath = false;
				}
				Node inicio = Node(actualPosition.x(), actualPosition.y(), false, false);

				MathLib::Vec2 newPosition = astar.GetNextPosition(inicio);
				if (!SamePositions(newPosition, MathLib::Vec2(0, 0))) {

					MathLib::Vec2 offset = (newPosition - actualPosition);
					body_->setPosition(actualPosition + MathLib::Vec2(offset.x(), offset.y()));
				}
				inicio.~Node();
			}

		}
		else if (agent_->status_ == Agent::Status::TimeToWork) {
			if (SamePositions(actualPosition, ZONA_TRABAJO)) {
				getNewPath = true;
				agent_->status_ = Agent::Status::Working;

			}
			if (DifferentPositions(actualPosition, ZONA_TRABAJO)) {
				Node inicio = Node(actualPosition.x(), actualPosition.y(), false, false);

				if (astar.listaCerrada.empty() || getNewPath) {
					astar.listaCerrada.clear();
					astar.listaCerrada.push_back(inicio);
					astar.SetValues(actualPosition, ZONA_TRABAJO);
					astar.GetPath();
					getNewPath = false;
				}

				MathLib::Vec2 newPosition = astar.GetNextPosition(inicio);

				MathLib::Vec2 offset = (newPosition - actualPosition);
				body_->setPosition(actualPosition + MathLib::Vec2(offset.x(), offset.y()));
				inicio.~Node();
			}
			else {
				agent_->status_ == Agent::Status::Working;
				getNewPath = true;

			}

		}
		else if (agent_->status_ == Agent::Status::Working) {
			if (SamePositions(actualPosition, ZONA_TRABAJO_FIN)) {
				getNewPath = true;
				agent_->status_ = Agent::Status::Working;

			}
			if (DifferentPositions(actualPosition, ZONA_TRABAJO_FIN)) {
				Node inicio = Node(actualPosition.x(), actualPosition.y(), false, false);

				if (astar.listaCerrada.empty() || getNewPath) {
					astar.listaCerrada.clear();
					astar.listaCerrada.push_back(inicio);
					astar.SetValues(actualPosition, ZONA_TRABAJO_FIN);
					astar.GetPath();
					getNewPath = false;
				}

				MathLib::Vec2 newPosition = astar.GetNextPosition(inicio);

				MathLib::Vec2 offset = (newPosition - actualPosition);
				body_->setPosition(actualPosition + MathLib::Vec2(offset.x(), offset.y()));
				inicio.~Node();
			}
			else {
				agent_->status_ == Agent::Status::Working;
				getNewPath = true;

			}
		}
	};
	}
}




