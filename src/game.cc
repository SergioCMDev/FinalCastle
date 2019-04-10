//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <game.h>
#include <window.h>
#include <body.h>
#include <defines.h>
#include <debug_draw.h>


#include <cstdio>

void Game::init() {
	font_ = TTF_OpenFont(FONT_FILE, FPS_FONT_SIZE);
	if (!font_) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	fps_sprite_.setVisible(false);
	for (size_t i = 0; i < MAX_AGENTS; i++)
	{

		//soldiers[i].init(&world_, Body::Type::Autonomous);
		//workers[i].init(&world_, Body::Type::Autonomous);
		//guards[i].init(&world_, Body::Type::Autonomous);
		soldiers[i].init(&world_, Body::Type::Autonomous, Agent::Type::Soldier);
		workers[i].init(&world_, Body::Type::Autonomous, Agent::Type::Worker);
		guards[i].init(&world_, Body::Type::Autonomous, Agent::Type::Guard);
	}

	//world_.target()->getKinematic()->position = MathLib::Vec2(0.0f, 0.0f);
}

void Game::start() {
	uint32_t fps_time{ 0 };
	uint32_t fps_time_acc{ 0 };

	uint32_t next_game_tick = SDL_GetTicks();
	uint32_t update_loops = 0;
	uint32_t render_loops = 0;

	const uint32_t skip_ticks = 1000 / TICKS_PER_SECOND;

	while (!quit_) {
		uint32_t loops = 0;
		while ((SDL_GetTicks() > next_game_tick) && (loops < MAX_FRAME_SKIP)) {
			handleInput();
			update(skip_ticks);
			updateAgents();

			next_game_tick += skip_ticks;
			++loops;
			++update_loops;
		}
		render();

		uint32_t c_time = SDL_GetTicks();
		fps_time_acc += (c_time - fps_time);
		fps_time = c_time;
		++render_loops;
		if (render_loops > 100) {        //show stats each 100 frames
			const float fps = 1000.0f / (fps_time_acc / 100.0f);
			const float ratio = (float)render_loops / (float)update_loops;
			char text[255];
			sprintf_s(text, "%d RFPS      %d UFPS", (uint32_t)fps, (uint32_t)(fps / ratio));
			fps_sprite_.loadFromRenderedText(text, SDL_Color FOREGROUND_COLOR, font_, true);
			fps_sprite_.setVisible(true);

			render_loops = 0;
			update_loops = 0;
			fps_time_acc = 0;
		}
	}
}


void Game::updateAgents() {
	for (size_t i = 0; i < MAX_AGENTS; i++)
	{
		//soldiers[i].update();
		//guards[i].render();
		//workers[i].render();
	}
}

void Game::shutdown() {}

void Game::handleInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit_ = true;
		}

		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			if (!astar.loading) {

				if (e.type == SDL_MOUSEBUTTONUP) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (destinoX > 0 && destinoY > 0) {
						origenX = -1;
						origenY = -1;
						destinoX = -1;
						destinoY = -1;
					}
					if (origenX < 0 && origenY < 0) {
						origenX = x;
						origenY = y;
					}
					else {
						destinoX = x;
						destinoY = y;
						astar = Astar(origenX, origenY, destinoX, destinoY);
						astar.GetPath();
						render();
					}

					//world_.target()->getKinematic()->position = Vec2(x, y);


				}
			}
		}
	}
}


void Game::update(const uint32_t dt) {
	render();

	world_.update(dt / slo_mo_);
}

void Game::render() {
	SDL_Renderer* renderer = Window::instance().getRenderer();
	SDL_SetRenderDrawColor(renderer, 0xD0, 0xD0, 0xD0, 0xFF);
	SDL_RenderClear(renderer);
	fps_sprite_.render();
	Sprite s;
	s.loadFromFile(MAP);
	s.render();
	world_.render();

	for (size_t i = 0; i < MAX_AGENTS; i++)
	{
		soldiers[i].render();
		guards[i].render();
		workers[i].render();
	}

	DebugDraw::render();

	SDL_RenderPresent(renderer);
}