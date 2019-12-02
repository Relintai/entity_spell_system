#include "xp_data.h"

#include "../entity_enums.h"

int XPData::get_max_level() {
	return EntityEnums::MAX_LEVEL;
}

int XPData::get_xp(int level) {
	ERR_FAIL_INDEX_V(level - 1, EntityEnums::MAX_LEVEL, 9999999);

	return _xps.get(level - 1);
}

void XPData::set_xp(int level, int value) {
	ERR_FAIL_INDEX(level - 1, EntityEnums::MAX_LEVEL);

	_xps.set(level - 1, value);
}

bool XPData::can_level_up(int level) {
	return level < EntityEnums::MAX_LEVEL;
}

XPData::XPData() {
	_xps.resize(EntityEnums::MAX_LEVEL);

	for (int i = 0; i < _xps.size(); ++i) {
		_xps.set(i, 0);
	}
}

XPData::~XPData() {
}

void XPData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_max_level"), &XPData::get_max_level);
	ClassDB::bind_method(D_METHOD("get_xp", "level"), &XPData::get_xp);
	ClassDB::bind_method(D_METHOD("set_xp", "level", "value"), &XPData::set_xp);
	ClassDB::bind_method(D_METHOD("can_level_up", "level"), &XPData::can_level_up);

	ADD_GROUP("Level", "level_");
	for (int i = 1; i <= EntityEnums::MAX_LEVEL; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i)), "set_xp", "get_xp", i);
	}
}
