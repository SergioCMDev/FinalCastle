//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __DEFINES_H__
#define __DEFINES_H__ 1

#include <algorithm>
#include <mathlib/vec2.h>
#include <corecrt_math_defines.h>

#define NOMINMAX

#define GAME_NAME "Final Castle"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define TICKS_PER_SECOND 30
#define MAX_FRAME_SKIP 10

#define FOREGROUND_COLOR { 0, 0, 0, 255 }
#define SHADOW_COLOR {160, 160, 160, 255}

#define FONT_FILE "../media/8bit.ttf"
#define AGENT_WORKER "../media/slave.bmp"
#define AGENT_SOLDIER "../media/soldier.bmp"
#define AGENT_GUARD "../media/guard.bmp"
#define MAP "../media/mapa.bmp"
#define MAP_COSTES "../media/costes.bmp"

#define MAX_AGENTS 1
#define FPS_FONT_SIZE 12

const MathLib::Vec2 ENTRADA_ZONA_DESCANSO(144, 468);

const int HORIZONTAL_COST = 1;
const int VERTICAL_COST = 2;


struct KinematicSteering {
	MathLib::Vec2 velocity{ 0.0f, 0.0f };
	float rotation{ 0.0f };
};

struct Steering {
	MathLib::Vec2 linear{ 0.0f, 0.0f }; //linear acceleration
	float angular{ 0.0f }; //angular acceleration
};

struct KinematicStatus {
	MathLib::Vec2 position{ 0.0f, 0.0f };
	float orientation{ 0.0f };
	MathLib::Vec2 velocity{ 0.0f, 0.0f };  //linear velocity
	float rotation{ 0.0f };               //angular velocity
	float speed{ 0.0f };
};

template <typename T>
inline T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

inline MathLib::Vec2 rotate2D(const MathLib::Vec2& pivot, const MathLib::Vec2& point, const float angle) {
	const float s = sin(angle);
	const float c = cos(angle);

	return MathLib::Vec2(c * (point.x() - pivot.x()) - s * (point.y() - pivot.y()) + pivot.x(),
		s * (point.x() - pivot.x()) + c * (point.y() - pivot.y()) + pivot.y());
}

inline int GetRandomInt(int min, int max) {
	//return (rand() % max + 1); //Desde 1 a Max
	return ((rand() % (max - min)) + min); //Desde 0 a Max
}

//random value between two numbers
inline float randomFloat(float a, float b) {
	const float random = ((float)rand()) / (float)RAND_MAX;
	return a + (random * (b - a));
}

//wrap an angle between [-PI, PI)
inline float wrapAnglePI(double x) {
	x = fmod(x + M_PI, M_PI * 2.0f);
	if (x < 0) x += M_PI * 2.0f;
	return x - M_PI;
}

//returns (-1, 0 , 1), the sign of the number
template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

inline bool DifferentPositions(const MathLib::Vec2 pos1, const MathLib::Vec2 pos2 ) {
	return pos1.x() != pos2.x() || pos1.y() != pos2.y();
}

#endif