//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __GAME_H__
#define __GAME_H__ 1



#include <defines.h>
#include <world.h>
#include <sprite.h>
#include <Node.h>
#include <Astar.h>

class Game {
  public:
    Game() {};
    ~Game() {};

    void init();
    void start();
    void shutdown();
	std::vector<Node> listaCerrada;
	Astar astar;

  private:
    void handleInput();
    void update(const uint32_t dt);
    void render();
	int origenX = -1, origenY = -1, destinoX = -1, destinoY = -1;
    bool quit_ = false;
    Sprite fps_sprite_;
    TTF_Font* font_ = nullptr;

    World world_;

    int8_t slo_mo_ = 1;
};

#endif