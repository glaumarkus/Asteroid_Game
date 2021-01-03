#include "include/Game.h"


/*
* Constructor
*/
Game::Game() :
	_ticks(0)
{}

/*
* Init
*/
bool Game::init() {

	// SDL Video
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to init Video: %s", SDL_GetError());
		return false;
	}

	// SDL Audio
	int sdlAudioResult = SDL_Init(SDL_INIT_AUDIO);
	if (sdlAudioResult != 0) {
		SDL_Log("Unable to init Audio: %s", SDL_GetError());
		return false;
	}

	// SDL Window 

	info.game_window = SDL_CreateWindow(
		"Pong",
		100, 20,
		1024, 768,
		0
	);

	if (!info.game_window) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	// SDL Image Files

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	// Renderer

	info.game_renderer = SDL_CreateRenderer(
		info.game_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!info.game_renderer) {
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		return false;
	}

	load_data();

	_ticks = SDL_GetTicks();

	return true;
}

/*
* Load Texture
*/

SDL_Texture* Game::load_texture(const char* filename) {

	SDL_Surface* surface = IMG_Load(filename);
	if (!surface) {
		SDL_Log("Unable to load Texture: %s", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* text = SDL_CreateTextureFromSurface(info.game_renderer, surface);
	SDL_FreeSurface(surface);
	if (!text) {
		SDL_Log("Unable to convert Texture: %s", SDL_GetError());
		return nullptr;
	}
	return text;
}

/*
* Load Data
*/

void Game::load_data() {

	// load background
	SDL_Texture* background = load_texture("assets/background.png");
	//background_actor = new GameUtility::Actor(this);

	//_actors.emplace_back()



	// load ship
	SDL_Texture* ship = load_texture("assets/ship.png");

	// load asteroid
	SDL_Texture* asteroid = load_texture("assets/asteroid.png");

}

/*
* Actors
*/

void Game::add_actor(Actor* actor) {
	_actors.emplace_back(actor);
}

void Game::remove_actor(Actor* actor) {
	for (auto a : _actors) {
		if (a == actor)
			delete a;
	}
}

/*
* Exit
*/
void Game::Shutdown() {

	while (!_actors.empty()) delete _actors.back();

	SDL_DestroyRenderer(info.game_renderer);
	SDL_DestroyWindow(info.game_window);
	SDL_Quit();
}

/*
* Gameloop
*/
void Game::GameLoop() {

	while (status.running) {
		get_input();
		update_world();
		manage_output();
	}
}

/*
* Input
*/
void Game::get_input() {


	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			status.running = false;
			break;
		}
	}

	// Keyboard State
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		status.running = false;
	}


	/*
	_ship->ProcessKeyboard(state);

	// movement commands
	if (keyboard_state[SDL_SCANCODE_W]) {
			
	}
	if (keyboard_state[SDL_SCANCODE_A]) {
			
	}
	if (keyboard_state[SDL_SCANCODE_S]) {
			
	}
	if (keyboard_state[SDL_SCANCODE_D]) {
			
	}

	if (keyboard_state[SDL_SCANCODE_SPACE]) {

	}

	*/

}


/*
* Update
*/
void Game::update_world() {

	// capped at 60 FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticks + 16));

	float deltaTime = (SDL_GetTicks() - _ticks) / 1000.0f;
	_ticks = SDL_GetTicks();

	if (deltaTime > 0.05f) deltaTime = 0.05f;


	// update actors
	status.update_actors = true;

	for (auto actor : _actors)
		actor->update(deltaTime);

	status.update_actors = false;

	// add pending actors
	for (auto pending : _pending_actors)
		_actors.emplace_back(pending);

	_pending_actors.clear();


	// remove dead actors
	std::vector<Actor*> dead_actors;

	for (auto actor : _actors)
		if (actor->get_state() == Actor::State::dead) {
			dead_actors.emplace_back(actor);
		}

	for (auto actor : dead_actors)
		delete actor;

}


/*
* Output
*/
void Game::manage_output() {

	// render background
	SDL_SetRenderDrawColor(
		info.game_renderer,
		0,
		0,
		0,
		255
	);
	// clear back buffer
	SDL_RenderClear(info.game_renderer);

	for (auto sprite : _sprites) sprite->draw(info.game_renderer);

	SDL_RenderPresent(info.game_renderer);

}
