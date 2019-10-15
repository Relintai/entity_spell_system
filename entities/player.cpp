#include "player.h"

#include "../inventory/bag.h"

int Player::gets_seed() {
	return _s_seed;
}
void Player::sets_seed(int value) {
	_s_seed = value;

	SEND_RPC(rpc("setc_seed", value), setc_seed(value));
}

int Player::getc_seed() {
	return _c_seed;
}
void Player::setc_seed(int value) {
	_c_seed = value;
}

//Ref<InputProfile> Player::get_input_profile() {
//	return _input_profile;
//}

void Player::_setup() {
	Entity::_setup();

	if (!gets_entity_data().is_valid())
		return;

	if (is_deserialized()) {

		return;
	}

	ProfileManager *pm = ProfileManager::get_instance();

	if (pm != NULL) {
		Ref<ClassProfile> cp = pm->get_class_profile(gets_entity_data()->get_id());

		if (cp.is_valid()) {
			set_actionbar_locked(cp->get_actionbar_locked());

			get_action_bar_profile()->clear_action_bars();

			Ref<ActionBarProfile> abp = cp->get_action_bar_profile();

			get_action_bar_profile()->from_actionbar_profile(abp);
		}
	}

	if (!gets_bag().is_valid()) {

		Ref<Bag> bag;
		bag.instance();

		bag->set_size(gets_entity_data()->get_bag_size());

		sets_bag(bag);
	}
}

Dictionary Player::_to_dict() {
	Dictionary dict = Entity::_to_dict();

	dict["seed"] = _s_seed;

	return dict;
}

void Player::_from_dict(const Dictionary &dict) {
	Entity::_from_dict(dict);

	sets_seed(dict.get("seed", _s_seed));
}

Player::Player() {
	//_seed = 0; don't it will be random by default like this
	_c_seed = _s_seed;

	//_input_profile = Ref<InputProfile>(memnew(InputProfile()));
}

Player::~Player() {
	//_input_profile.unref();
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("gets_seed"), &Player::gets_seed);
	ClassDB::bind_method(D_METHOD("sets_seed", "value"), &Player::sets_seed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sseed"), "sets_seed", "gets_seed");

	ClassDB::bind_method(D_METHOD("getc_seed"), &Player::getc_seed);
	ClassDB::bind_method(D_METHOD("setc_seed", "value"), &Player::setc_seed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cseed"), "setc_seed", "getc_seed");

	//ClassDB::bind_method(D_METHOD("get_input_profile"), &Player::get_input_profile);
}
