/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "entity_resource.h"

#include "core/version.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"
#include "../entity.h"

#include "../../defines.h"

int EntityResource::get_id() const {
	return _id;
}
void EntityResource::set_id(const int value) {
	_id = value;
}

String EntityResource::get_text_name() const {
	return _text_name;
}
void EntityResource::set_text_name(const String value) {
	_text_name = value;
}

bool EntityResource::get_dirty() const {
	return _dirty;
}
void EntityResource::set_dirty(const bool value) {
	_dirty = value;
}

bool EntityResource::get_should_process() const {
	return _should_process;
}
void EntityResource::set_should_process(const bool value) {
	_should_process = value;
}

int EntityResource::get_current_value() const {
	return _current;
}
void EntityResource::set_current_value(const int value) {
	_current = value;

	_dirty = true;

	emit_changed();
}

int EntityResource::get_max_value() const {
	return _max;
}
void EntityResource::set_max_value(const int value) {
	_max = value;

	_dirty = true;

	emit_changed();
}

Entity *EntityResource::get_owner() {
	return _owner;
}
void EntityResource::set_owner(Entity *value) {
	_owner = value;
}
void EntityResource::set_owner_bind(Node *owner) {
	if (!owner) {
		return;
	}

	Entity *e = cast_to<Entity>(owner);

	if (!e) {
		return;
	}

	_owner = e;
}

void EntityResource::ons_added(Entity *owner) {
	_owner = owner;

	if (has_method("_ons_added"))
		call("_ons_added", owner);
}
void EntityResource::onc_added(Entity *owner) {
	_owner = owner;

	if (has_method("_onc_added"))
		call("_onc_added", owner);
}

void EntityResource::notification_sstat_changed(const int statid, const float current) {
	if (has_method("_notification_sstat_changed"))
		call("_notification_sstat_changed", statid, current);
}
void EntityResource::notification_cstat_changed(const int statid, const float current) {
	if (has_method("_notification_cstat_changed"))
		call("_notification_cstat_changed", statid, current);
}

void EntityResource::ons_target_changed(Entity *entity, Entity *old_target) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity, old_target);
}
void EntityResource::onc_target_changed(Entity *entity, Entity *old_target) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity, old_target);
}

void EntityResource::process_server(const float delta) {
	call("_process_server", delta);
}
void EntityResource::_process_server(const float delta) {
}

void EntityResource::process_client(const float delta) {
	call("_process_client", delta);
}
void EntityResource::_process_client(const float delta) {
}

void EntityResource::receivec_update(const int current) {
	_current = current;
}
void EntityResource::receivec_update_full(const int current, const int max) {
	_current = current;
	_max = max;

	emit_changed();
}
void EntityResource::receivec_update_string(const String str) {
	if (has_method("_receivec_update_string"))
		call("_receivec_update_string", str);
}

PoolRealArray EntityResource::get_stacking_mods() {
	return _stacking_mods;
}
void EntityResource::set_stacking_mods(const PoolRealArray &mods) {
	_stacking_mods.resize(0);

	_stacking_mods.append_array(mods);
}

void EntityResource::add_stacking_mod(const float value) {
	_stacking_mods.push_back(value);

	call("_stacking_mod_added", value);
}
void EntityResource::remove_stacking_mod(const float value) {
	for (int i = 0; i < _stacking_mods.size(); ++i) {
		if (Math::is_equal_approx(_stacking_mods[i], value)) {
			_stacking_mods.remove(i);
			call("_stacking_mod_removed", value);
			return;
		}
	}
}

void EntityResource::add_non_stacking_mod(const float value) {
	_non_stacking_mods.push_back(value);

	call("_non_stacking_mod_added", value);
}
void EntityResource::remove_non_stacking_mod(const float value) {
	for (int i = 0; i < _non_stacking_mods.size(); ++i) {
		if (Math::is_equal_approx(_non_stacking_mods[i], value)) {
			_non_stacking_mods.remove(i);
			call("_non_stacking_mod_removed", value);
			return;
		}
	}
}

float EntityResource::get_current_stacking_mod_value() const {
	return _current_stacking_mod_value;
}
float EntityResource::get_current_positive_non_stacking_mod_value() const {
	return _current_positive_non_stacking_mod_value;
}
float EntityResource::get_current_negative_non_stacking_mod_value() const {
	return _current_negative_non_stacking_mod_value;
}

void EntityResource::refresh_current_stacking_mod_value() {
	_current_stacking_mod_value = 0;

	for (int i = 0; i < _non_stacking_mods.size(); ++i) {
	}
}
void EntityResource::refresh_current_non_stacking_mod_values() {
	_current_positive_non_stacking_mod_value = 0;
	_current_negative_non_stacking_mod_value = 0;

	for (int i = 0; i < _non_stacking_mods.size(); ++i) {
		float v = _non_stacking_mods[i];
		if (v >= 0) {
			if (v > _current_positive_non_stacking_mod_value) {
				_current_positive_non_stacking_mod_value = v;
			}
		} else {
			if (v < _current_negative_non_stacking_mod_value) {
				_current_negative_non_stacking_mod_value = v;
			}
		}
	}

	mods_changed();
}

void EntityResource::mods_changed() {
	call("_mods_changed");
}

PoolRealArray EntityResource::get_non_stacking_mods() {
	return _non_stacking_mods;
}
void EntityResource::set_non_stacking_mods(const PoolRealArray &mods) {
	_non_stacking_mods.resize(0);

	_non_stacking_mods.append_array(mods);
}

Dictionary EntityResource::to_dict() {
	return call("_to_dict");
}
void EntityResource::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary EntityResource::_to_dict() {
	Dictionary dict;

	dict["data_path"] = ESS::get_singleton()->get_resource_db()->get_entity_resource(_id)->get_path();

	dict["dirty"] = _dirty;
	dict["should_process"] = _should_process;

	//dict["data_id"] = _data_id;
	//dict["data_path"] = _data_path;

	dict["current"] = _current;

	dict["max"] = _max;

	Array sa;
	sa.resize(_stacking_mods.size());
	for (int i = 0; i < _stacking_mods.size(); ++i) {
		sa.set(i, _stacking_mods[i]);
	}

	dict["stacking_mods"] = sa;

	Array nsa;
	nsa.resize(_non_stacking_mods.size());
	for (int i = 0; i < _non_stacking_mods.size(); ++i) {
		nsa.set(i, _non_stacking_mods[i]);
	}

	dict["non_stacking_mods"] = nsa;

	return dict;
}
void EntityResource::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_dirty = dict.get("dirty", false);
	_should_process = dict.get("should_process", false);

	//_data_path = dict.get("data_path", "");
	//_data_id = ESS::get_singleton()->get_resource_db()->entity_data_path_to_id(_data_path);

	//_data_id = dict.get("data_id", 0);
	_current = dict.get("current", 0);
	_max = dict.get("max", 0);

	Array sa = dict.get("stacking_mods", 0);
	_stacking_mods.resize(sa.size());
	for (int i = 0; i < sa.size(); ++i) {
		_stacking_mods.set(i, sa[i]);
	}

	Array nsa = dict.get("non_stacking_mods", 0);
	_stacking_mods.resize(nsa.size());
	for (int i = 0; i < nsa.size(); ++i) {
		_stacking_mods.set(i, nsa[i]);
	}

	emit_changed();
}

EntityResource::EntityResource() {
	_id = 0;

	_server_side = false;
	_dirty = false;

	_owner = NULL;

	_should_process = has_method("_process");

	_current = 0;
	_max = 0;

	_current_stacking_mod_value = 0;
	_current_positive_non_stacking_mod_value = 0;
	_current_negative_non_stacking_mod_value = 0;
}

EntityResource::~EntityResource() {
	_owner = NULL;
}

void EntityResource::_stacking_mod_added(const float value) {
	_current_stacking_mod_value += value;

	mods_changed();
}
void EntityResource::_stacking_mod_removed(const float value) {
	_current_stacking_mod_value -= value;

	mods_changed();
}

void EntityResource::_non_stacking_mod_added(const float value) {
	if (value >= 0) {
		if (value > _current_positive_non_stacking_mod_value) {
			_current_positive_non_stacking_mod_value = value;
			mods_changed();
		}
	} else {
		if (value < _current_negative_non_stacking_mod_value) {
			_current_negative_non_stacking_mod_value = value;
			mods_changed();
		}
	}
}
void EntityResource::_non_stacking_mod_removed(const float value) {
	if (value >= 0) {
		if (Math::is_equal_approx(value, _current_positive_non_stacking_mod_value)) {
			refresh_current_non_stacking_mod_values();
		}
	} else {
		if (Math::is_equal_approx(value, _current_negative_non_stacking_mod_value)) {
			refresh_current_non_stacking_mod_values();
		}
	}
}

void EntityResource::_mods_changed() {
	float m = 100.0 + _current_stacking_mod_value + _current_positive_non_stacking_mod_value + _current_negative_non_stacking_mod_value;
	m /= 100.0;
	m = static_cast<float>(_max) * m;

	set_current_value(static_cast<int>(m));
}

void EntityResource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &EntityResource::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityResource::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_text_name"), &EntityResource::get_text_name);
	ClassDB::bind_method(D_METHOD("set_text_name", "value"), &EntityResource::set_text_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_text_name", "get_text_name");

	ClassDB::bind_method(D_METHOD("get_dirty"), &EntityResource::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &EntityResource::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty", PROPERTY_HINT_NONE, "", 0), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_should_process"), &EntityResource::get_should_process);
	ClassDB::bind_method(D_METHOD("set_should_process", "value"), &EntityResource::set_should_process);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "should_process", PROPERTY_HINT_NONE, "", 0), "set_should_process", "get_should_process");

	ClassDB::bind_method(D_METHOD("get_current_value"), &EntityResource::get_current_value);
	ClassDB::bind_method(D_METHOD("set_current_value", "value"), &EntityResource::set_current_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_value"), "set_current_value", "get_current_value");

	ClassDB::bind_method(D_METHOD("get_max_value"), &EntityResource::get_max_value);
	ClassDB::bind_method(D_METHOD("set_max_value", "value"), &EntityResource::set_max_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_value"), "set_max_value", "get_max_value");

	ClassDB::bind_method(D_METHOD("get_owner"), &EntityResource::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "value"), &EntityResource::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_stacking_mods"), &EntityResource::get_stacking_mods);
	ClassDB::bind_method(D_METHOD("set_stacking_mods", "value"), &EntityResource::set_stacking_mods);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "stacking_mods"), "set_stacking_mods", "get_stacking_mods");

	ClassDB::bind_method(D_METHOD("add_stacking_mod", "value"), &EntityResource::add_stacking_mod);
	ClassDB::bind_method(D_METHOD("remove_stacking_mod", "value"), &EntityResource::remove_stacking_mod);

	ClassDB::bind_method(D_METHOD("get_non_stacking_mods"), &EntityResource::get_non_stacking_mods);
	ClassDB::bind_method(D_METHOD("set_non_stacking_mods", "value"), &EntityResource::set_non_stacking_mods);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_REAL_ARRAY, "non_stacking_mods"), "set_non_stacking_mods", "get_non_stacking_mods");

	ClassDB::bind_method(D_METHOD("add_non_stacking_mod", "value"), &EntityResource::add_non_stacking_mod);
	ClassDB::bind_method(D_METHOD("remove_non_stacking_mod", "value"), &EntityResource::remove_non_stacking_mod);

	ClassDB::bind_method(D_METHOD("get_current_stacking_mod_value"), &EntityResource::get_current_stacking_mod_value);
	ClassDB::bind_method(D_METHOD("get_current_positive_non_stacking_mod_value"), &EntityResource::get_current_positive_non_stacking_mod_value);
	ClassDB::bind_method(D_METHOD("get_current_negative_non_stacking_mod_value"), &EntityResource::get_current_negative_non_stacking_mod_value);

	ClassDB::bind_method(D_METHOD("refresh_current_stacking_mod_value"), &EntityResource::refresh_current_stacking_mod_value);
	ClassDB::bind_method(D_METHOD("refresh_current_non_stacking_mod_values"), &EntityResource::refresh_current_non_stacking_mod_values);

	ClassDB::bind_method(D_METHOD("mods_changed"), &EntityResource::mods_changed);

	BIND_VMETHOD(MethodInfo("_notification_sstat_changed", PropertyInfo(Variant::INT, "statid"), PropertyInfo(Variant::REAL, "curent")));
	BIND_VMETHOD(MethodInfo("_notification_cstat_changed", PropertyInfo(Variant::INT, "statid"), PropertyInfo(Variant::REAL, "curent")));

	BIND_VMETHOD(MethodInfo("_ons_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_ons_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_process_server", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_process_client", PropertyInfo(Variant::REAL, "delta")));

	BIND_VMETHOD(MethodInfo("_stacking_mod_added", PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_stacking_mod_removed", PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_non_stacking_mod_added", PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_non_stacking_mod_removed", PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_mods_changed"));

	ClassDB::bind_method(D_METHOD("process_server", "delta"), &EntityResource::process_server);
	ClassDB::bind_method(D_METHOD("_process_server", "delta"), &EntityResource::_process_server);

	ClassDB::bind_method(D_METHOD("process_client", "delta"), &EntityResource::process_client);
	ClassDB::bind_method(D_METHOD("_process_client", "delta"), &EntityResource::_process_client);

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "str"), "_gets_update_string"));
	BIND_VMETHOD(MethodInfo("_receivec_update_string", PropertyInfo(Variant::STRING, "str")));

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &EntityResource::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &EntityResource::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &EntityResource::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &EntityResource::_to_dict);

	ClassDB::bind_method(D_METHOD("_stacking_mod_added", "value"), &EntityResource::_stacking_mod_added);
	ClassDB::bind_method(D_METHOD("_stacking_mod_removed", "value"), &EntityResource::_stacking_mod_removed);

	ClassDB::bind_method(D_METHOD("_non_stacking_mod_added", "value"), &EntityResource::_non_stacking_mod_added);
	ClassDB::bind_method(D_METHOD("_non_stacking_mod_removed", "value"), &EntityResource::_non_stacking_mod_removed);

	ClassDB::bind_method(D_METHOD("_mods_changed"), &EntityResource::_mods_changed);
}
