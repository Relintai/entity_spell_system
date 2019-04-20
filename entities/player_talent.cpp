#include "player_talent.h"

int PlayerTalent::get_talent_id() {
	return _talent_id;
}

void PlayerTalent::set_talent_id(int value) {
	_talent_id = value;
}

int PlayerTalent::get_rank() {
	return _rank;
}

void PlayerTalent::set_rank(int value) {
	_rank = value;
}

PlayerTalent::PlayerTalent() {
	_rank = (int)(0);
	_talent_id = (int)(0);
}

PlayerTalent::PlayerTalent(int talentID) {
	set_talent_id(talentID);
}

void PlayerTalent::_bind_methods() {

}
