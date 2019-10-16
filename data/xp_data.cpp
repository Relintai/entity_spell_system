#include "xp_data.h"

int XPData::get_max_level() {
	return _xp_required.size();
}

int XPData::xp_required_for_level(int level) {
	ERR_FAIL_INDEX_V(level, _xp_required.size(), 9999999);

	return _xp_required.get(level);
}

bool XPData::can_level_up(int level) {
	return level < _xp_required.size();
}

PoolIntArray XPData::get_xps() {
	return _xp_required;
}
void XPData::set_xps(const PoolIntArray &xps) {
	_xp_required = xps;
}

XPData::XPData() {
}

XPData::~XPData() {
}

void XPData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_max_level"), &XPData::get_max_level);
	ClassDB::bind_method(D_METHOD("xp_required_for_level", "level"), &XPData::xp_required_for_level);
	ClassDB::bind_method(D_METHOD("can_level_up", "level"), &XPData::can_level_up);

	ClassDB::bind_method(D_METHOD("get_xps"), &XPData::get_xps);
	ClassDB::bind_method(D_METHOD("set_xps", "auras"), &XPData::set_xps);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "xps"), "set_xps", "get_xps");
}
