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

#include "entity_data_manager.h"

#include "../database/ess_resource_db.h"
#include "../utility/entity_create_info.h"

EntityDataManager *EntityDataManager::instance;

EntityDataManager *EntityDataManager::get_instance() {
	return instance;
}

bool EntityDataManager::get_use_spell_points() const {
	return _use_spell_points;
}
void EntityDataManager::set_use_spell_points(const bool value) {
	_use_spell_points = value;
}

bool EntityDataManager::get_scale_spells_by_default() const {
	return _scale_spells_by_default;
}
void EntityDataManager::set_scale_spells_by_default(const bool value) {
	_scale_spells_by_default = value;
}

bool EntityDataManager::get_automatic_load() const {
	return _automatic_load;
}
void EntityDataManager::set_automatic_load(const bool load) {
	_automatic_load = load;
}

bool EntityDataManager::get_use_class_xp() const {
	return _use_class_xp;
}
void EntityDataManager::set_use_class_xp(const bool value) {
	_use_class_xp = value;
}

bool EntityDataManager::get_automatic_class_levelups() const {
	return _automatic_class_levelups;
}
void EntityDataManager::set_automatic_class_levelups(const bool value) {
	_automatic_class_levelups = value;
}

bool EntityDataManager::get_use_global_class_level() const {
	return _use_global_class_level;
}
void EntityDataManager::set_use_global_class_level(const bool value) {
	_use_global_class_level = value;
}

bool EntityDataManager::get_allow_class_spell_learning() const {
	return _allow_class_spell_learning;
}
void EntityDataManager::set_allow_class_spell_learning(const bool value) {
	_allow_class_spell_learning = value;
}

bool EntityDataManager::get_allow_class_recipe_learning() const {
	return _allow_class_recipe_learning;
}
void EntityDataManager::set_allow_class_recipe_learning(const bool value) {
	_allow_class_recipe_learning = value;
}

String EntityDataManager::get_resource_db_path() {
	return _ess_resource_db_path;
}
void EntityDataManager::set_resource_db_path(String path) {
	_ess_resource_db_path = path;
}
Ref<ESSResourceDB> EntityDataManager::get_resource_db() {
	return _ess_resource_db;
}

void EntityDataManager::load_resource_db() {
	_Directory dir;

	ERR_FAIL_COND(_ess_resource_db_path == "");

	Ref<ESSResourceDB> d = load_resource(_ess_resource_db_path, "ESSResourceDB");

	ERR_FAIL_COND(!d.is_valid());

	_ess_resource_db = d;
}

Ref<Resource> EntityDataManager::load_resource(const String &path, const String &type_hint) {
	_ResourceLoader *rl = _ResourceLoader::get_singleton();

#if VERSION_MAJOR < 4
	Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, type_hint);

	ERR_FAIL_COND_V(!resl.is_valid(), Ref<Resource>());

	resl->wait();

	return resl->get_resource();
#else
	return rl->load(path, type_hint);
#endif
}

void EntityDataManager::request_entity_spawn(const Ref<EntityCreateInfo> &info) {
	emit_signal("on_entity_spawn_requested", info);
}
void EntityDataManager::request_entity_spawn_deferred(const Ref<EntityCreateInfo> &info) {
	call_deferred("emit_signal", "on_entity_spawn_requested", info);
}

void EntityDataManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_use_spell_points"), &EntityDataManager::get_use_spell_points);
	ClassDB::bind_method(D_METHOD("set_use_spell_points", "value"), &EntityDataManager::set_use_spell_points);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_spell_points"), "set_use_spell_points", "get_use_spell_points");

	ClassDB::bind_method(D_METHOD("get_scale_spells_by_default"), &EntityDataManager::get_scale_spells_by_default);
	ClassDB::bind_method(D_METHOD("set_scale_spells_by_default", "value"), &EntityDataManager::set_scale_spells_by_default);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "scale_spells_by_default"), "set_scale_spells_by_default", "get_scale_spells_by_default");

	ClassDB::bind_method(D_METHOD("get_automatic_load"), &EntityDataManager::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &EntityDataManager::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	ClassDB::bind_method(D_METHOD("get_automatic_class_levelups"), &EntityDataManager::get_automatic_class_levelups);
	ClassDB::bind_method(D_METHOD("set_automatic_class_levelups", "load"), &EntityDataManager::set_automatic_class_levelups);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_class_levelups"), "set_automatic_class_levelups", "get_automatic_class_levelups");

	ClassDB::bind_method(D_METHOD("get_use_class_xp"), &EntityDataManager::get_use_class_xp);
	ClassDB::bind_method(D_METHOD("set_use_class_xp", "value"), &EntityDataManager::set_use_class_xp);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_class_xp"), "set_use_class_xp", "get_use_class_xp");

	ClassDB::bind_method(D_METHOD("get_use_global_class_level"), &EntityDataManager::get_use_global_class_level);
	ClassDB::bind_method(D_METHOD("set_use_global_class_level", "value"), &EntityDataManager::set_use_global_class_level);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_global_class_level"), "set_use_global_class_level", "get_use_global_class_level");

	ClassDB::bind_method(D_METHOD("get_allow_class_spell_learning"), &EntityDataManager::get_allow_class_spell_learning);
	ClassDB::bind_method(D_METHOD("set_allow_class_spell_learning", "value"), &EntityDataManager::set_allow_class_spell_learning);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "allow_class_spell_learning"), "set_allow_class_spell_learning", "get_allow_class_spell_learning");

	ClassDB::bind_method(D_METHOD("get_allow_class_recipe_learning"), &EntityDataManager::get_allow_class_recipe_learning);
	ClassDB::bind_method(D_METHOD("set_allow_class_recipe_learning", "value"), &EntityDataManager::set_allow_class_recipe_learning);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "allow_class_recipe_learning"), "set_allow_class_recipe_learning", "get_allow_class_recipe_learning");

	//XPData
	ClassDB::bind_method(D_METHOD("get_resource_db_path"), &EntityDataManager::get_resource_db_path);
	ClassDB::bind_method(D_METHOD("set_resource_db_path", "path"), &EntityDataManager::set_resource_db_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "resource_db_path"), "set_resource_db_path", "get_resource_db_path");

	ClassDB::bind_method(D_METHOD("get_resource_db"), &EntityDataManager::get_resource_db);

	//load
	ClassDB::bind_method(D_METHOD("load_resource_db"), &EntityDataManager::load_resource_db);

	ClassDB::bind_method(D_METHOD("load_resource", "path", "type_hint"), &EntityDataManager::load_resource, DEFVAL(""));

	ADD_SIGNAL(MethodInfo("on_entity_spawn_requested", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "EntityCreateInfo")));

	ClassDB::bind_method(D_METHOD("request_entity_spawn", "info"), &EntityDataManager::request_entity_spawn);
	ClassDB::bind_method(D_METHOD("request_entity_spawn_deferred", "info"), &EntityDataManager::request_entity_spawn_deferred);
}

EntityDataManager::EntityDataManager() {
	instance = this;

	_use_spell_points = GLOBAL_DEF("ess/spells/use_spell_points", false);
	_scale_spells_by_default = GLOBAL_DEF("ess/spells/scale_spells_by_default", false);
	_allow_class_spell_learning = GLOBAL_DEF("ess/spells/allow_class_spell_learning", false);
	_allow_class_recipe_learning = GLOBAL_DEF("ess/spells/allow_class_recipe_learning", false);

	_use_class_xp = GLOBAL_DEF("ess/level/use_class_xp", false);
	_automatic_class_levelups = GLOBAL_DEF("ess/level/automatic_class_levelups", false);
	_use_global_class_level = GLOBAL_DEF("ess/level/use_global_class_level", false);

	_automatic_load = GLOBAL_DEF("ess/data/automatic_load", false);

	_ess_resource_db_path = GLOBAL_DEF("ess/data/ess_resource_db_path", "");

	if (_automatic_load) {
		call_deferred("load_all");
	}
}

EntityDataManager::~EntityDataManager() {
	instance = NULL;

	_ess_resource_db.unref();
}
