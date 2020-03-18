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

#include "profile_manager.h"
#include "core/io/json.h"
#include "core/os/file_access.h"
#include "core/project_settings.h"

const String ProfileManager::DEFAULT_PROFILE_FILE_NAME = "default.profile";

ProfileManager *ProfileManager::_instance;

ProfileManager *ProfileManager::get_instance() {
	return _instance;
}

String ProfileManager::get_save_file() const {
	return _save_file;
}
void ProfileManager::set_save_file(const String &file) {
	_save_file = file;

	if (_automatic_save)
		save();
}

int ProfileManager::get_last_used_class() const {
	return _last_used_class;
}

void ProfileManager::set_last_used_class(const int value) {
	_last_used_class = value;

	if (_automatic_save)
		save();
}

int ProfileManager::get_class_profile_count() const {
	return _class_profiles.size();
}

Ref<ClassProfile> ProfileManager::get_class_profile_index(const int index) {
	return _class_profiles.get(index);
}

void ProfileManager::add_class_profile(Ref<ClassProfile> profile) {
	profile->connect("changed", this, "_on_class_profile_changed");

	_class_profiles.push_back(profile);

	if (_automatic_save)
		save();
}

void ProfileManager::clear_class_profiles() {
	for (int i = 0; i < _class_profiles.size(); ++i) {
		_class_profiles.get(i)->disconnect("changed", this, "_on_class_profile_changed");
	}

	_class_profiles.clear();

	if (_automatic_save)
		save();
}

void ProfileManager::remove_class_profile(const int index) {
	_class_profiles.get(index)->disconnect("changed", this, "_on_class_profile_changed");

	_class_profiles.remove(index);

	if (_automatic_save)
		save();
}

Vector<Ref<ClassProfile> > &ProfileManager::get_class_profiles() {
	return _class_profiles;
}

Ref<ClassProfile> ProfileManager::get_class_profile(const int class_id) {
	for (int i = 0; i < _class_profiles.size(); ++i) {
		if (_class_profiles.get(i)->get_class_id() == class_id) {
			return Ref<ClassProfile>(_class_profiles.get(i));
		}
	}

	Ref<ClassProfile> class_profile = Ref<ClassProfile>(memnew(ClassProfile(class_id)));

	class_profile->load_defaults();
	class_profile->connect("changed", this, "_on_class_profile_changed");

	_class_profiles.push_back(Ref<ClassProfile>(class_profile));

	emit_signal("changed");

	return class_profile;
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
		clear_class_profiles();

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
	clear_class_profiles();

	_class_profiles.push_back(memnew(ClassProfile("Naturalist", 1, 1, 0, false)));
	_class_profiles.push_back(memnew(ClassProfile("Berserker", 3, 1, 0, false)));
	_class_profiles.push_back(memnew(ClassProfile("IceArcher", 4, 1, 0, false)));
	_class_profiles.push_back(memnew(ClassProfile("Chronomancer", 6, 1, 0, false)));

	for (int i = 0; i < _class_profiles.size(); ++i) {
		_class_profiles.get(i)->load_defaults();
		_class_profiles.get(i)->connect("changed", this, "_on_class_profile_changed");
	}

	emit_signal("changed");
}

Dictionary ProfileManager::to_dict() const {
	Dictionary dict;

	dict["last_used_class"] = _last_used_class;
	dict["profile_name"] = _profile_name;

	Array arr;

	for (int i = 0; i < _class_profiles.size(); ++i) {
		Dictionary d = _class_profiles[i]->to_dict();

		arr.append(d);
	}

	dict["class_profiles"] = arr;

	return dict;
}
void ProfileManager::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	clear_class_profiles();

	_last_used_class = dict.get("last_used_class", "");
	_profile_name = dict.get("profile_name", 0);

	Array arr = dict.get("class_profiles", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ClassProfile> c;
		c.instance();

		c->from_dict(arr.get(i));
		c->connect("changed", this, "_on_class_profile_changed");

		_class_profiles.push_back(c);
	}
}

ProfileManager::ProfileManager() {
	_instance = this;
	_last_used_class = 0;

	_profile_name = ProfileManager::DEFAULT_PROFILE_FILE_NAME;

	_automatic_load = GLOBAL_DEF("ess/profiles/automatic_load", false);
	_automatic_save = GLOBAL_DEF("ess/profiles/automatic_save", false);
	_save_file = GLOBAL_DEF("ess/profiles/save_file", "user://profile.save");

	if (_automatic_load)
		call_deferred("load");
}

ProfileManager::~ProfileManager() {
	_instance = NULL;

	_class_profiles.clear();
}

void ProfileManager::_on_class_profile_changed(Ref<ClassProfile> profile) {
	if (_automatic_save)
		save();
}

void ProfileManager::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	BIND_VMETHOD(MethodInfo("_save"));
	BIND_VMETHOD(MethodInfo("_load"));

	ClassDB::bind_method(D_METHOD("_save"), &ProfileManager::_save);
	ClassDB::bind_method(D_METHOD("_load"), &ProfileManager::_load);

	ClassDB::bind_method(D_METHOD("get_automatic_load"), &ProfileManager::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &ProfileManager::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	ClassDB::bind_method(D_METHOD("get_save_file"), &ProfileManager::get_save_file);
	ClassDB::bind_method(D_METHOD("set_save_file", "path"), &ProfileManager::set_save_file);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "set_save_file"), "set_save_file", "get_save_file");

	ClassDB::bind_method(D_METHOD("get_last_used_class"), &ProfileManager::get_last_used_class);
	ClassDB::bind_method(D_METHOD("set_last_used_class", "value"), &ProfileManager::set_last_used_class);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "last_used_class"), "set_last_used_class", "get_last_used_class");

	ClassDB::bind_method(D_METHOD("get_class_profile_count"), &ProfileManager::get_class_profile_count);
	ClassDB::bind_method(D_METHOD("get_class_profile_index", "index"), &ProfileManager::get_class_profile_index);
	ClassDB::bind_method(D_METHOD("add_class_profile", "profile"), &ProfileManager::add_class_profile);
	ClassDB::bind_method(D_METHOD("clear_class_profiles"), &ProfileManager::clear_class_profiles);
	ClassDB::bind_method(D_METHOD("remove_class_profile", "index"), &ProfileManager::remove_class_profile);

	ClassDB::bind_method(D_METHOD("get_class_profile", "class_id"), &ProfileManager::get_class_profile);
	ClassDB::bind_method(D_METHOD("save"), &ProfileManager::save);
	ClassDB::bind_method(D_METHOD("load"), &ProfileManager::load);
	ClassDB::bind_method(D_METHOD("save_profile", "name"), &ProfileManager::save_profile);
	ClassDB::bind_method(D_METHOD("load_profile", "name"), &ProfileManager::load_profile);
	ClassDB::bind_method(D_METHOD("load_defaults"), &ProfileManager::load_defaults);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ProfileManager::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ProfileManager::to_dict);

	ClassDB::bind_method(D_METHOD("_on_class_profile_changed", "profile"), &ProfileManager::_on_class_profile_changed);
}
