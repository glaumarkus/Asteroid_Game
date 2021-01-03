#pragma once

#include <vector>

#include "Component.h"
#include "Game.h"
#include "Math.h"

class Actor {
public:

	enum class State {
		active,
		paused,
		dead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void update(const float& deltaTime);
	void update_components(const float& deltaTime);
	virtual void update_actor(const float& deltaTime);

	void add_component(class Component* component);
	void remove_component(class Component* component);

	Vec2 get_position() { return _position; }
	State get_state() { return _state; }
	float get_scale() { return _scale; }
	float get_rotation() { return _rotation; }

	Game* get_game() { return _game; }

private:

	State _state;
	Vec2 _position;
	float _scale;
	float _rotation;
	std::vector<class Component*> _components;
	class Game* _game;
	

	//class Ship* _ship;

};