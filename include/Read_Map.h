#ifndef __READ_MAP_H__
#define __READ_MAP_H__ 1


#define MAP_L1_WIDTH 128                //Size of screen in tiles
#define MAP_L1_HEIGHT 128

#include <stdint.h>
#include <defines.h>
#include <../include/SDL/SDL.h>


class Read_Map {
public:
	uint8_t map_l1[MAP_L1_WIDTH][MAP_L1_HEIGHT];
	void loadMap();
private:

};

#endif