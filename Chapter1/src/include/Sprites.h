#pragma once

#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component {
public:

	SpriteComponent(Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void draw(SDL_Renderer* renderer);
	virtual void set_texture(SDL_Texture* texture);

	int get_draw_order() const { return _order; }
	int get_height() const { return _height; }
	int get_width() const { return _width; }

private:
	SDL_Texture* _texture;
	int _order;
	int _width;
	int _height;
};

