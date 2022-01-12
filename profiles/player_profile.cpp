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

#include "player_profile.h"

#include "core/version.h"

#include "../defines.h"

const String PlayerProfile::DEFAULT_PROFILE_FILE_NAME = "default.profile";

int PlayerProfile::get_id() {
	return _id;
}

void PlayerProfile::set_id(int value) {
	_id = value;
}

String PlayerProfile::get_profile_name() {
	return _profile_name;
}

void PlayerProfile::set_profile_name(String value) {
	_profile_name = value;
}

int PlayerProfile::get_last_used_character() const {
	return _last_used_character;
}

void PlayerProfile::set_last_used_character(const int value) {
	_last_used_character = value;

	emit_change();
}

int PlayerProfile::get_class_profile_count() const {
	return _class_profiles.size();
}

Ref<ClassProfile> PlayerProfile::get_class_profile_index(const int index) {
	return _class_profiles.get(index);
}

void PlayerProfile::add_class_profile(Ref<ClassProfile> profile) {
	profile->CONNECT("changed", this, PlayerProfile, _on_class_profile_changed);

	_class_profiles.push_back(profile);

	emit_change();
}

void PlayerProfile::clear_class_profiles() {
	for (int i = 0; i < _class_profiles.size(); ++i) {
		_class_profiles.get(i)->DISCONNECT("changed", this, PlayerProfile, _on_class_profile_changed);
	}

	_class_profiles.clear();

	emit_change();
}

void PlayerProfile::remove_class_profile(const int index) {
	_class_profiles.get(index)->DISCONNECT("changed", this, PlayerProfile, _on_class_profile_changed);

	_class_profiles.remove(index);

	emit_change();
}

Vector<Ref<ClassProfile>> &PlayerProfile::get_class_profiles() {
	return _class_profiles;
}

Ref<ClassProfile> PlayerProfile::get_class_profile(const StringName &class_path) {
	for (int i = 0; i < _class_profiles.size(); ++i) {
		if (_class_profiles.get(i)->get_class_path() == class_path) {
			return Ref<ClassProfile>(_class_profiles.get(i));
		}
	}

	Ref<ClassProfile> class_profile = Ref<ClassProfile>(memnew(ClassProfile(class_path)));

	class_profile->load_defaults();

	class_profile->CONNECT("changed", this, PlayerProfile, _on_class_profile_changed);

	_class_profiles.push_back(Ref<ClassProfile>(class_profile));

	emit_change();

	return class_profile;
}

void PlayerProfile::emit_change() {
	emit_signal("changed", Ref<PlayerProfile>(this));
}

Dictionary PlayerProfile::get_custom_data() {
	return _custom_data;
}
void PlayerProfile::set_custom_data(const Dictionary &dict) {
	_custom_data = dict;

	emit_change();
}

Dictionary PlayerProfile::to_dict() const {
	Dictionary dict;

	dict["last_used_character"] = _last_used_character;
	dict["profile_name"] = _profile_name;

	Array arr;

	for (int i = 0; i < _class_profiles.size(); ++i) {
		Dictionary d = _class_profiles[i]->to_dict();

		arr.append(d);
	}

	dict["class_profiles"] = arr;

	dict["custom_data"] = _custom_data;

	return dict;
}
void PlayerProfile::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	clear_class_profiles();

	_last_used_character = dict.get("last_used_character", "");
	_profile_name = dict.get("profile_name", 0);

	Array arr = dict.get("class_profiles", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ClassProfile> c;
		c.instance();

		c->from_dict(arr.get(i));

		c->CONNECT("changed", this, PlayerProfile, _on_class_profile_changed);

		_class_profiles.push_back(c);
	}

	_custom_data = dict.get("custom_data", Dictionary());

	emit_change();
}

PlayerProfile::PlayerProfile() {
	_id = 0;
	_last_used_character = 0;
	_profile_name = DEFAULT_PROFILE_FILE_NAME;
}

PlayerProfile::~PlayerProfile() {
	_custom_data.clear();

	_class_profiles.clear();
}

void PlayerProfile::load_defaults() {
	clear_class_profiles();

	for (int i = 0; i < _class_profiles.size(); ++i) {
		_class_profiles.get(i)->load_defaults();

		_class_profiles.get(i)->CONNECT("changed", this, PlayerProfile, _on_class_profile_changed);
	}

	emit_change();
}

void PlayerProfile::_on_class_profile_changed() {
	emit_change();
}

void PlayerProfile::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "profile", PROPERTY_HINT_RESOURCE_TYPE, "PlayerProfile")));

	ClassDB::bind_method(D_METHOD("get_id"), &PlayerProfile::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &PlayerProfile::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_profile_name"), &PlayerProfile::get_profile_name);
	ClassDB::bind_method(D_METHOD("set_profile_name", "value"), &PlayerProfile::set_profile_name);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "profile_name"), "set_profile_name", "get_profile_name");

	ClassDB::bind_method(D_METHOD("get_last_used_character"), &PlayerProfile::get_last_used_character);
	ClassDB::bind_method(D_METHOD("set_last_used_character", "value"), &PlayerProfile::set_last_used_character);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "set_last_used_character"), "set_last_used_character", "get_last_used_character");

	ClassDB::bind_method(D_METHOD("get_custom_data"), &PlayerProfile::get_custom_data);
	ClassDB::bind_method(D_METHOD("set_custom_data", "value"), &PlayerProfile::set_custom_data);
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "custom_data"), "set_custom_data", "get_custom_data");

	ClassDB::bind_method(D_METHOD("get_class_profile_count"), &PlayerProfile::get_class_profile_count);
	ClassDB::bind_method(D_METHOD("get_class_profile_index", "index"), &PlayerProfile::get_class_profile_index);
	ClassDB::bind_method(D_METHOD("add_class_profile", "profile"), &PlayerProfile::add_class_profile);
	ClassDB::bind_method(D_METHOD("clear_class_profiles"), &PlayerProfile::clear_class_profiles);
	ClassDB::bind_method(D_METHOD("remove_class_profile", "index"), &PlayerProfile::remove_class_profile);

	ClassDB::bind_method(D_METHOD("get_class_profile", "class_id"), &PlayerProfile::get_class_profile);

	ClassDB::bind_method(D_METHOD("load_defaults"), &PlayerProfile::load_defaults);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &PlayerProfile::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &PlayerProfile::to_dict);

	ClassDB::bind_method(D_METHOD("_on_class_profile_changed"), &PlayerProfile::_on_class_profile_changed);

	ClassDB::bind_method(D_METHOD("emit_change"), &PlayerProfile::emit_change);
}
