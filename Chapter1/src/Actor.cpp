#include "include/Actor.h"


/*
* Actor Functions
*/
Actor::Actor(Game* game) :
	_state(Actor::State::active),
	_game(game),
	_position(Templates::Zero),
	_scale(1.0f),
	_rotation(0.0f)
{
	_game->add_actor(this);
}

Actor::~Actor() {
	_game->remove_actor(this);
	while (!_components.empty()) delete _components.back();
}


/*
* Update functions
*/
void Actor::update(const float& deltaTime) {
	if (_state == Actor::State::active) {
		update_components(deltaTime);
		update_actor(deltaTime);
	}
}

void Actor::update_components(const float& deltaTime) {
	for (auto comp : _components)
		comp->update(deltaTime);
}

// virtual override
void Actor::update_actor(const float& deltaTime) {}


void Actor::add_component(class Component* component) {

	int c_order = component->get_update_order();
	auto it = _components.begin();
	for (auto it = _components.begin(); it != _components.end(); it++) {
		if (c_order < (*it)->get_update_order()) break;
	}
	_components.insert(it, component);
}

void Actor::remove_component(class Component* component) {
	auto it = std::find(_components.begin(), _components.end(), component);
	if (it != _components.end()) _components.erase(it);
}
