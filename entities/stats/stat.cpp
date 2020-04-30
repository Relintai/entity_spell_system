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

#include "stat.h"

#include "../../singletons/ess.h"
#include "../entity.h"
#include "stat_data_entry.h"

#include "core/version.h"

bool Stat::get_dirty() {
	return _dirty;
}
void Stat::set_dirty(bool value) {
	_dirty = value;
}

float Stat::get_base() {
	return _base;
}
void Stat::set_base(float value) {
	_base = value;

	refresh();
}
void Stat::mod_base(float value) {
	_base += value;

	refresh();
}

float Stat::get_base_calculated() {
	return _base_calculated;
}
void Stat::set_base_calculated(float value) {
	_base_calculated = value;

	refresh();
}

float Stat::get_bonus() {
	return _bonus;
}
void Stat::set_bonus(float value) {
	_bonus = value;

	refresh();
}
void Stat::mod_bonus(float value) {
	_bonus = value;
}

float Stat::get_percent() {
	return _percent;
}
void Stat::set_percent(float value) {
	_percent = value;

	refresh();
}
void Stat::mod_percent(float value) {
	_percent = value;
}

float Stat::gets_current() {
	return _s_current;
}
void Stat::sets_current(float value) {
	_s_current = value;
}

float Stat::getc_current() {
	return _c_current;
}
void Stat::setc_current(float value) {
	//ERR_FAIL_COND(_owner == NULL);

	_c_current = value;

	//_owner->notification_cstat_changed(Ref<Stat>(this));
	emit_signal("c_changed", Ref<Stat>(this));
}

void Stat::refresh() {
	_s_current = (_base + _base_calculated + _bonus) * (_percent / 100.0);

	_dirty = true;

	//_owner->notification_sstat_changed(Ref<Stat>(this));
	emit_signal("s_changed", Ref<Stat>(this));
}

Dictionary Stat::to_dict() {
	return call("_to_dict");
}
void Stat::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary Stat::_to_dict() {
	Dictionary dict;

	dict["dirty"] = _dirty;

	dict["base"] = _base;
	dict["base_calculated"] = _base_calculated;
	dict["bonus"] = _bonus;
	dict["percent"] = _percent;

	dict["current"] = _s_current;

	return dict;
}
void Stat::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_dirty = dict.get("dirty", false);

	_base = dict.get("base", 0);
	_base_calculated = dict.get("base_calculated", 0);
	_bonus = dict.get("bonus", 0);
	_percent = dict.get("percent", 1);

	_s_current = dict.get("current", 0);
	_c_current = _s_current;

	_dirty = true;
}

Stat::Stat() {
	_dirty = true;

	_base = 0;
	_base_calculated = 0;
	_bonus = 0;
	_percent = 0;

	_s_current = 0;
	_c_current = 0;
}

Stat::~Stat() {
}

void Stat::_bind_methods() {
	ADD_SIGNAL(MethodInfo("s_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));
	ADD_SIGNAL(MethodInfo("c_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));

	ClassDB::bind_method(D_METHOD("get_dirty"), &Stat::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &Stat::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_base"), &Stat::get_base);
	ClassDB::bind_method(D_METHOD("set_base", "value"), &Stat::set_base);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base"), "set_base", "get_base");
	ClassDB::bind_method(D_METHOD("mod_base", "value"), &Stat::mod_base);

	ClassDB::bind_method(D_METHOD("get_base_calculated"), &Stat::get_base_calculated);
	ClassDB::bind_method(D_METHOD("set_base_calculated", "value"), &Stat::set_base_calculated);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_calculated"), "set_base_calculated", "get_base_calculated");

	ClassDB::bind_method(D_METHOD("get_bonus"), &Stat::get_bonus);
	ClassDB::bind_method(D_METHOD("set_bonus", "value"), &Stat::set_bonus);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus"), "set_bonus", "get_bonus");
	ClassDB::bind_method(D_METHOD("mod_bonus", "value"), &Stat::mod_bonus);

	ClassDB::bind_method(D_METHOD("get_percent"), &Stat::get_percent);
	ClassDB::bind_method(D_METHOD("set_percent", "value"), &Stat::set_percent);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent"), "set_percent", "get_percent");
	ClassDB::bind_method(D_METHOD("mod_percent", "value"), &Stat::mod_percent);

	ClassDB::bind_method(D_METHOD("gets_current"), &Stat::gets_current);
	ClassDB::bind_method(D_METHOD("sets_current", "value"), &Stat::sets_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scurrent"), "sets_current", "gets_current");

	ClassDB::bind_method(D_METHOD("getc_current"), &Stat::getc_current);
	ClassDB::bind_method(D_METHOD("setc_current", "value"), &Stat::setc_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "ccurrent"), "setc_current", "getc_current");
	ClassDB::bind_method(D_METHOD("refresh"), &Stat::refresh);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Stat::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Stat::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Stat::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Stat::_to_dict);
}
