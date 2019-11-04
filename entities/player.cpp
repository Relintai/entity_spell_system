#include "player.h"

#include "../inventory/bag.h"



//Ref<InputProfile> Player::get_input_profile() {
//	return _input_profile;
//}


Player::Player() {
	

	//_input_profile = Ref<InputProfile>(memnew(InputProfile()));

	
}

Player::~Player() {
	//_input_profile.unref();
}

void Player::_bind_methods() {


	//ClassDB::bind_method(D_METHOD("get_input_profile"), &Player::get_input_profile);
}
