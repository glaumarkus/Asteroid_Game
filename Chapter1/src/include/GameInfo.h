#pragma once

#include "SDL.h"
#include "Math.h"


struct game_status {

	bool running;
	bool update_actors;

	game_status() :
		running(true),
		update_actors(false)
	{}
};

struct game_info {

	SDL_Window* game_window;
	SDL_Renderer* game_renderer;

	Vec2 window_dimensions;
	Vec2 window_origin;

	game_info() :
		game_window(nullptr),
		game_renderer(nullptr),
		window_dimensions(1024, 768),
		window_origin(100, 20)
	{}
};
