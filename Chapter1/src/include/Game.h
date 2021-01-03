#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "Math.h"
#include "GameInfo.h"

#include "Actor.h"

#include "Sprites.h"

#include <string>
#include <unordered_map>



class Game {
public:

	Game();

	bool init();
	void GameLoop();
	void Shutdown();

	void add_actor(Actor* actor);
	void remove_actor(Actor* actor);

	void add_sprite(SpriteComponent* sprite);
	void remove_sprite(SpriteComponent* sprite);

	SDL_Texture* load_texture(const char* filename);

	

private:

	game_status status;
	game_info info;

	Uint32 _ticks;

	std::unordered_map<std::string, SDL_Texture*> _textures;
	std::vector<Actor*> _actors;
	std::vector<Actor*> _pending_actors;
	std::vector<SpriteComponent*> _sprites;

	void get_input();
	void update_world();
	void manage_output();

	void load_data();
	void unload_data();

};

