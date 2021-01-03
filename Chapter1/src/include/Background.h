#pragma once

#include "Sprites.h"
#include <vector>
#include "Math.h"

class BackgroundSpriteComponent : public SpriteComponent {
public:
	BackgroundSpriteComponent(Actor* owner, int drawOrder = 10);
	void update(const float& deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

	void set_BG_Textures(const std::vector<SDL_Texture*>& textures);
	void set_screen_size(const Vec2& size);
	void set_scroll_speed(const float& speed);
	void get_scroll_speed() const {}
private:

	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* _texture;
		Vec2 _offset;
	};

	std::vector<BGTexture> _BGtextures;
	Vec2 _size;
	float _speed;
};