//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __BODY_H__
#define __BODY_H__ 1

#include <sprite.h>
#include <defines.h>
#include <mathlib/vec2.h>
#include<Kinematics/KinematicArrive.h>
#include<Kinematics/KinematicFlee.h>
#include<Kinematics/kinematicSeek.h>
#include<Kinematics/KinematicWander.h>
#include<Steering/Flee.h>
#include<Steering/Arrive.h>
#include<Steering/Align.h>
#include<Steering/Seek.h>
#include<Steering/Cohesion.h>
#include<Steering/Separation.h>
#include<Steering/Delegated/Wander.h>
#include<Steering/Delegated/Pursue.h>
#include<Steering/Delegated/Face.h>
#include<Steering/Delegated/LookGoing.h>
#include<Steering/VelocityMatching.h>
#include<Steering/Delegated/Flocking.h>

class Agent;

class Body {
public:
	enum class Type {
		Autonomous,
		Manual,
	};


	enum class SteeringMode {
		Kinematic_Seek,         //1       Kinematics
		Kinematic_Flee,         //2
		Kinematic_Arrive,       //3
		Kinematic_Wander,       //4
		Seek,                   //q       Steering Basics
		Flee,                   //w
		Arrive,                 //e
		Align,                  //r
		Velocity_Matching,      //t
		Pursue,                 //a       Steering Delegated
		Face,                   //s
		LookGoing,              //d
		Wander,                 //f
		Cohesion,				//g
		Flocking,				//h
		Separation,				//i
		Alignment,			//j
		SeekLeader				//j

	};

	Body() {};
	~Body() {};
	void init(const Type type, Agent* agent);
	void update(const uint32_t dt);
	void render() const;

	void setTarget(Agent* target);
	void setSteering(const SteeringMode mode) { steering_mode_ = mode; };
	const KinematicStatus* getKinematic() const { return &state_; }
	KinematicStatus* getKinematic() { return &state_; }
	Agent* target_;
	void setPosition(const MathLib::Vec2& position);
	void updateSteering(const uint32_t dt, const Steering steering);
	void updateKinematic(const uint32_t dt, const KinematicSteering steering);
	void setOrientation(const MathLib::Vec2& velocity);
	KinematicStatus state_;
	MathLib::Vec2 destination;
private:
	KinematicStatus* _agentToFlee;
	Agent* _leader;
	void updateManual(const uint32_t);
	void keepInSpeed();
	void keepInBounds();
	Sprite sprite_;
	Type type_;
	SteeringMode steering_mode_;

	const float max_speed_ = 100.0f;

	struct {
		struct {
			MathLib::Vec2 pos;
			MathLib::Vec2 v;
		} green, red, blue;
	} dd;

	KinematicSeek k_seek_;
	KinematicFlee k_flee_;
	KinematicArrive k_arrive;
	KinematicWander k_wander_;

	Seek seek_;
	Flee flee_;
	Arrive arrive_;
	Align align_;
	VelocityMatching vel_matching_;

	Pursue pursue_;
	Face face_;
	LookGoing look_going_;
	Wander wander_;

	Flocking flocking_;
	Cohesion cohesion_;
};

#endif