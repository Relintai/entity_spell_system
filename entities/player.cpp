#include "player.h"

#include "../inventory/bag.h"

void Player::_setup() {
	Entity::_setup();

	if (gets_entity_data().is_valid()) {
		Ref<Bag> bag;
		bag.instance();

		bag->set_size(gets_entity_data()->get_bag_size());

		sets_bag(bag);
	}
}

Player::Player() {
}

void Player::_bind_methods() {
}
