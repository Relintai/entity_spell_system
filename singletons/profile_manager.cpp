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

#include "profile_manager.h"
#include "core/io/json.h"
#include "core/os/file_access.h"

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/config/engine.h"
#include "core/config/project_settings.h"
#else
#include "core/engine.h"
#include "core/project_settings.h"
#endif

#include "../defines.h"

ProfileManager *ProfileManager::_instance;

ProfileManager *ProfileManager::get_singleton() {
	return _instance;
}

bool ProfileManager::get_automatic_load() const {
	return _automatic_load;
}
void ProfileManager::set_automatic_load(const bool load) {
	_automatic_load = load;
}

bool ProfileManager::get_automatic_save() const {
	return _automatic_save;
}
void ProfileManager::set_automatic_save(const bool load) {
	_automatic_save = load;
}

String ProfileManager::get_save_file() const {
	return _save_file;
}
void ProfileManager::set_save_file(const String &file) {
	_save_file = file;

	if (_automatic_save)
		save();
}

int ProfileManager::gets_player_profile_count() const {
	return _s_player_profiles.size();
}
Ref<PlayerProfile> ProfileManager::gets_player_profile_index(const int index) {
	return _s_player_profiles.get(index);
}
void ProfileManager::adds_player_profile(const Ref<PlayerProfile> &profile) {
	_s_player_profiles.push_back(profile);
}
void ProfileManager::clears_player_profiles() {
	//for (int i = 0; i < _s_player_profiles.size(); ++i) {
	//	_c_player_profile->disconnect("changed", this, "_on_player_profile_changed");
	//}

	_s_player_profiles.clear();
}
void ProfileManager::removes_player_profile(const int index) {
	_s_player_profiles.remove(index);
}

Ref<PlayerProfile> ProfileManager::getc_player_profile() {
	return _c_player_profile;
}

void ProfileManager::save() {
	call("_save");
}

void ProfileManager::load() {
	call("_load");

	emit_signal("changed");
}

void ProfileManager::_save() {
	Error err;
	FileAccess *f = FileAccess::open(_save_file, FileAccess::WRITE, &err);

	if (!f) {
		ERR_FAIL_MSG("Couldn't open file: " + err);
	}

	f->store_line(JSON::print(to_dict()));
	f->close();
}

void ProfileManager::_load() {
	if (FileAccess::exists(_save_file)) {
		//clears_player_profiles();

		Error err;
		String text = FileAccess::get_file_as_string(_save_file, &err);

		if (err) {
			load_defaults();
			ERR_FAIL_MSG("Couldn't open file: " + err);
		}

		String err_txt;
		int err_line;
		Variant v;
		err = JSON::parse(text, v, err_txt, err_line);

		if (err) {
			load_defaults();
			ERR_FAIL_MSG("Error parsing profile: " + err);
		}

		Dictionary d = v;

		from_dict(d);
	} else {
		load_defaults();
	}
}

void ProfileManager::save_profile(const String &name) {
}

void ProfileManager::load_profile(const String &name) {
	load_defaults();
}

void ProfileManager::load_defaults() {
}

Dictionary ProfileManager::to_dict() const {
	Dictionary dict;

	dict["cplayer_profile"] = _c_player_profile->to_dict();

	Array arr;

	for (int i = 0; i < _s_player_profiles.size(); ++i) {
		Dictionary d = _s_player_profiles[i]->to_dict();

		arr.append(d);
	}

	dict["splayer_profiles"] = arr;

	return dict;
}
void ProfileManager::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	clears_player_profiles();

	_c_player_profile->DISCONNECT("changed", this, ProfileManager, _on_player_profile_changed);
	_c_player_profile->from_dict(dict.get("cplayer_profile", Dictionary()));
	_c_player_profile->CONNECT("changed", this, ProfileManager, _on_player_profile_changed);

	Array arr = dict.get("splayer_profiles", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<PlayerProfile> c;
		c.instance();

		c->from_dict(arr.get(i));

		c->CONNECT("changed", this, ProfileManager, _on_player_profile_changed);

		_s_player_profiles.push_back(c);
	}
}

void ProfileManager::on_keybinds_changed(const StringName &class_path) {
	getc_player_profile()->get_class_profile(class_path)->get_input_profile()->save_from_projectsettings();

	emit_signal("keybinds_changed");
}

ProfileManager::ProfileManager() {
	_instance = this;

	_automatic_load = GLOBAL_DEF("ess/profiles/automatic_load", false);
	_automatic_save = GLOBAL_DEF("ess/profiles/automatic_save", false);
	_save_file = GLOBAL_DEF("ess/profiles/save_file", "user://profile.save");

	_c_player_profile.instance();

	_c_player_profile->CONNECT("changed", this, ProfileManager, _on_player_profile_changed);

	if (!Engine::get_singleton()->is_editor_hint() && _automatic_load)
		call_deferred("load");
}

ProfileManager::~ProfileManager() {
	_instance = NULL;

	_c_player_profile->DISCONNECT("changed", this, ProfileManager, _on_player_profile_changed);

	_s_player_profiles.clear();
}

void ProfileManager::_on_player_profile_changed(Ref<PlayerProfile> profile) {
	if (!Engine::get_singleton()->is_editor_hint() && _automatic_save)
		save();
}

void ProfileManager::_bind_methods() {
	ADD_SIGNAL(MethodInfo("keybinds_changed"));
	ADD_SIGNAL(MethodInfo("changed"));

	BIND_VMETHOD(MethodInfo("_save"));
	BIND_VMETHOD(MethodInfo("_load"));

	ClassDB::bind_method(D_METHOD("_save"), &ProfileManager::_save);
	ClassDB::bind_method(D_METHOD("_load"), &ProfileManager::_load);

	ClassDB::bind_method(D_METHOD("get_automatic_load"), &ProfileManager::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &ProfileManager::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	ClassDB::bind_method(D_METHOD("get_automatic_save"), &ProfileManager::get_automatic_save);
	ClassDB::bind_method(D_METHOD("set_automatic_save", "load"), &ProfileManager::set_automatic_save);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_save"), "set_automatic_save", "get_automatic_save");

	ClassDB::bind_method(D_METHOD("get_save_file"), &ProfileManager::get_save_file);
	ClassDB::bind_method(D_METHOD("set_save_file", "path"), &ProfileManager::set_save_file);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "set_save_file"), "set_save_file", "get_save_file");

	ClassDB::bind_method(D_METHOD("gets_player_profile_count"), &ProfileManager::gets_player_profile_count);
	ClassDB::bind_method(D_METHOD("gets_player_profile_index", "index"), &ProfileManager::gets_player_profile_index);
	ClassDB::bind_method(D_METHOD("adds_player_profile", "profile"), &ProfileManager::adds_player_profile);
	ClassDB::bind_method(D_METHOD("clears_player_profiles"), &ProfileManager::clears_player_profiles);
	ClassDB::bind_method(D_METHOD("removes_player_profile", "index"), &ProfileManager::removes_player_profile);

	ClassDB::bind_method(D_METHOD("getc_player_profile"), &ProfileManager::getc_player_profile);

	ClassDB::bind_method(D_METHOD("save"), &ProfileManager::save);
	ClassDB::bind_method(D_METHOD("load"), &ProfileManager::load);
	ClassDB::bind_method(D_METHOD("save_profile", "name"), &ProfileManager::save_profile);
	ClassDB::bind_method(D_METHOD("load_profile", "name"), &ProfileManager::load_profile);
	ClassDB::bind_method(D_METHOD("load_defaults"), &ProfileManager::load_defaults);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ProfileManager::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ProfileManager::to_dict);

	ClassDB::bind_method(D_METHOD("_on_player_profile_changed", "profile"), &ProfileManager::_on_player_profile_changed);

	ClassDB::bind_method(D_METHOD("on_keybinds_changed", "class_path"), &ProfileManager::on_keybinds_changed);
}
