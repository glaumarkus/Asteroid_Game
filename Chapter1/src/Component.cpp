#include "include/Component.h"


/*
* Component Functions
*/

Component::Component(class Actor* owner, int update_order) :
	_owner(owner),
	_updateOrder(update_order)
{
	_owner->add_component(this);
}

Component::~Component() {
	_owner->remove_component(this);
}

// override
void Component::update(const float& deltaTime) {}
