#pragma once

#include "Actor.h"

class Component {
public:

	Component(class Actor* owner, int update_order = 100);

	virtual ~Component();

	virtual void update(const float& deltaTime);
	int get_update_order() const { return _updateOrder; }

protected:
	class Actor* _owner;
	int _updateOrder;
};
