#include "include/Sprites.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder = 100) :
	Component(owner),
	_texture(nullptr),
	_order(drawOrder),
	_width(0),
	_height(0)
{
	_owner->get_game()->add_sprite(this);
}

SpriteComponent::~SpriteComponent() {
	_owner->get_game()->remove_sprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer){
	if (_texture) {

		SDL_Rect r;
		r.w = static_cast<int>(_width * _owner->get_scale());
		r.h = static_cast<int>(_height * _owner->get_scale());

		Vec2 position = _owner->get_position();
		r.x = static_cast<int>(position.x - r.w / 2);
		r.y = static_cast<int>(position.y - r.h / 2);

		SDL_RenderCopyEx(
			renderer,
			_texture,
			nullptr,
			&r,
			-Math::ToDegrees(_owner->get_rotation()),
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void SpriteComponent::set_texture(SDL_Texture* texture){
	_texture = texture;
	SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height);
}