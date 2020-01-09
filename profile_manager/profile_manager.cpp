#include "profile_manager.h"

const String ProfileManager::DEFAULT_PROFILE_FILE_NAME = "default.profile";

ProfileManager *ProfileManager::_instance;

ProfileManager *ProfileManager::get_instance() {
	return _instance;
}

int ProfileManager::get_last_used_class() {
	return _last_used_class;
}

void ProfileManager::set_last_used_class(int value) {
	_last_used_class = value;
}

int ProfileManager::get_class_profile_count() {
	return _class_profiles.size();
}

Ref<ClassProfile> ProfileManager::get_class_profile_index(int index) {
	return _class_profiles.get(index);
}

void ProfileManager::add_class_profile(Ref<ClassProfile> profile) {
	_class_profiles.push_back(profile);
}

void ProfileManager::clear_class_profiles() {
	_class_profiles.clear();
}

void ProfileManager::remove_class_profile(int index) {
	_class_profiles.remove(index);
}

Vector<Ref<ClassProfile> > &ProfileManager::get_class_profiles() {
	return _class_profiles;
}

Ref<ClassProfile> ProfileManager::get_class_profile(int class_id) {
	for (int i = 0; i < _class_profiles.size(); ++i) {
		if (_class_profiles.get(i)->get_class_id() == class_id) {
			return Ref<ClassProfile>(_class_profiles.get(i));
		}
	}

	Ref<ClassProfile> class_profile = Ref<ClassProfile>(memnew(ClassProfile(class_id)));

	class_profile->load_defaults();

	_class_profiles.push_back(Ref<ClassProfile>(class_profile));

	emit_signal("changed");

	return Ref<ClassProfile>(class_profile);
}

void ProfileManager::save() {
	if (has_method("_save")) {
		call("_save");
	}
}

void ProfileManager::load() {
	if (has_method("_load")) {
		call("_load");
	} //else {
	//load_defaults();
	//}
}

void ProfileManager::save_profile(String name) {
}

void ProfileManager::load_profile(String name) {
	load_defaults();
}

int _last_used_class;

String _profile_name;

Vector<Ref<ClassProfile> > _class_profiles;

void ProfileManager::load_defaults() {
	_class_profiles.clear();

	_class_profiles.push_back(memnew(ClassProfile("Naturalist", 1, 1, 0, false, true)));
	_class_profiles.push_back(memnew(ClassProfile("Berserker", 3, 1, 0, false, true)));
	_class_profiles.push_back(memnew(ClassProfile("IceArcher", 4, 1, 0, false, true)));
	_class_profiles.push_back(memnew(ClassProfile("Chronomancer", 6, 1, 0, false, true)));

	for (int i = 0; i < _class_profiles.size(); ++i) {
		_class_profiles.get(i)->load_defaults();
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

	_last_used_class = dict.get("last_used_class", "");
	_profile_name = dict.get("profile_name", 0);

	Array arr = dict.get("class_profiles", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ClassProfile> c;
		c.instance();

		c->from_dict(arr.get(i));

		_class_profiles.push_back(c);
	}
}

ProfileManager::ProfileManager() {
	_instance = this;
	_last_used_class = 0;

	_profile_name = ProfileManager::DEFAULT_PROFILE_FILE_NAME;
}

ProfileManager::~ProfileManager() {
	_instance = NULL;

	_class_profiles.clear();
}

void ProfileManager::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	BIND_VMETHOD(MethodInfo("_save"));
	BIND_VMETHOD(MethodInfo("_load"));

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
}
