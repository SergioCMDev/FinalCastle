//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <body.h>
#include <agent.h>
#include <debug_draw.h>



void Body::init(const Type type, Agent* agent) {
	type_ = type;
	target_ = agent;

	switch (agent->type_) {
	case Agent::Type::Guard: {
		sprite_.loadFromFile(AGENT_GUARD);
		int randomValueX = rand();
		int randomValueY = rand();
		setPosition(MathLib::Vec2(229, 393));

		//getKinematic()->position = MathLib::Vec2(0, 0);
		break; }
	case Agent::Type::Soldier: {
		sprite_.loadFromFile(AGENT_SOLDIER);
		int x = GetRandomInt(1, 10);
		if (x % 2 == 0) {
			setPosition(MathLib::Vec2(849, 985));
		}
		else {
			setPosition(MathLib::Vec2(971, 850));
		}
		break; }
	case Agent::Type::Worker: {
		sprite_.loadFromFile(AGENT_WORKER);
		int x = GetRandomInt(50, 80);
		int y = GetRandomInt(490, 890);
		setPosition(MathLib::Vec2(x, y));
		break; }

	}
	//steering_mode_ = SteeringMode::Kinematic_Seek;
}
void Body::setPosition(const MathLib::Vec2& position) {
	this->getKinematic()->position = position;
	sprite_.setPosition(position.x(), position.y());
}


void Body::update(const uint32_t dt) {
	if (type_ == Type::Autonomous) {
		switch (steering_mode_)
		{
		case SteeringMode::Kinematic_Seek: {
			KinematicSteering steer;
			k_seek_.calculate(state_, target_->getKinematic(), &steer);
			//updateKinematic(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Kinematic_Flee: {
			KinematicSteering steer;
			k_flee_.calculate(state_, target_->getKinematic(), &steer);
			updateKinematic(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Kinematic_Arrive: {
			KinematicSteering steer;
			k_arrive.calculate(state_, target_->getKinematic(), &steer);
			updateKinematic(dt, steer);
			break;
		}
		case SteeringMode::Kinematic_Wander: {
			KinematicSteering steer;
			k_wander_.calculate(state_, target_->getKinematic(), &steer);
			updateKinematic(dt, steer);
			break;
		}
		case SteeringMode::Seek: {
			Steering steer;
			Steering steer2;
			seek_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Flee: {
			Steering steer;
			flee_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Arrive: {
			Steering steer;
			arrive_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Align: {
			Steering steer;
			align_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			break;
		}
		case SteeringMode::Velocity_Matching: {
			Steering steer;
			vel_matching_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Pursue: {
			Steering steer;
			pursue_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;
		}
		case SteeringMode::Face: {
			Steering steer;
			face_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			break;
		}
		case SteeringMode::LookGoing: {
			Steering steer;
			look_going_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			break;
		}
		case SteeringMode::Wander: {
			Steering steer;
			wander_.calculate(state_, target_->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);
			break;	}
		case SteeringMode::Cohesion: {
			Steering steer;

			flee_.calculate(state_, _agentToFlee, &steer);

			updateSteering(dt, steer);
			setOrientation(state_.velocity);

			break;	}
		case SteeringMode::Alignment: {
			Steering steer;

			align_.calculate(state_, _leader->getKinematic(), &steer);
			updateSteering(dt, steer);
			break;		}
		case SteeringMode::SeekLeader: {
			Steering steer;

			seek_.calculate(state_, _leader->getKinematic(), &steer);
			updateSteering(dt, steer);
			setOrientation(state_.velocity);

			break;		}

		}
	}
	else {
		updateManual(dt);
	}

	sprite_.setPosition(state_.position.x(), state_.position.y());
	sprite_.setRotation(state_.orientation);
}

void Body::updateKinematic(const uint32_t dt, const KinematicSteering steering) {
	float time = dt * 0.001f;

	state_.velocity = steering.velocity;
	state_.position += steering.velocity * time;

	state_.rotation = steering.rotation;
	state_.orientation += steering.rotation * time;
}

void Body::updateSteering(const uint32_t dt, const Steering steering) {
	float time = dt * 0.001f;
	state_.velocity += steering.linear;
	state_.position += state_.velocity * time;

	state_.rotation += steering.angular;
	state_.orientation += state_.rotation * time;

	keepInSpeed();
	keepInBounds();
	dd.green.pos = state_.position;
	dd.green.v = state_.velocity;
}

void Body::render() const {
	sprite_.render();

	DebugDraw::drawVector(dd.red.pos, dd.red.v, 0xFF, 0x00, 0x00, 0xFF);
	DebugDraw::drawVector(dd.green.pos, dd.green.v, 0x00, 0x50, 0x00, 0xFF);
	DebugDraw::drawVector(dd.blue.pos, dd.blue.v, 0x00, 0x00, 0xFF, 0xFF);
	DebugDraw::drawPositionHist(state_.position);
}

void Body::setTarget(Agent* target) {
	target_ = target;
}


void Body::updateManual(const uint32_t dt) {
	float time = dt * 0.001f;             //dt comes in miliseconds

	MathLib::Vec2 orientation;
	orientation.fromPolar(1.0f, state_.orientation);
	state_.velocity = orientation.normalized() * state_.speed;
	state_.position += state_.velocity * time;

	keepInSpeed();
	keepInBounds();

	dd.green.pos = state_.position;
	dd.green.v = state_.velocity;
}

void Body::setOrientation(const Vec2& velocity) {
	if (velocity.length2() > 0) {
		state_.orientation = atan2(velocity.y(), velocity.x());
	}
}

void Body::keepInBounds() {
	if (state_.position.x() > WINDOW_WIDTH) state_.position.x() = 0.0f;
	if (state_.position.x() < 0.0f) state_.position.x() = WINDOW_WIDTH;
	if (state_.position.y() > WINDOW_HEIGHT) state_.position.y() = 0.0f;
	if (state_.position.y() < 0.0f) state_.position.y() = WINDOW_HEIGHT;
}

void Body::keepInSpeed() {
	if (state_.velocity.length() > max_speed_) {
		state_.velocity = state_.velocity.normalized() * max_speed_;
	}
}