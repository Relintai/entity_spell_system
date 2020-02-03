/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "xp_data.h"

#include "../../entity_enums.h"

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
