/*
Copyright (c) 2019-2021 Péter Magyar

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

#include "ess.h"

#include "../database/ess_resource_db.h"
#include "../spawners/ess_entity_spawner.h"
#include "../utility/entity_create_info.h"

ESS *ESS::instance;

ESS *ESS::get_singleton() {
	return instance;
}

bool ESS::get_use_spell_points() const {
	return _use_spell_points;
}
void ESS::set_use_spell_points(const bool value) {
	_use_spell_points = value;
}

bool ESS::get_scale_spells_by_default() const {
	return _scale_spells_by_default;
}
void ESS::set_scale_spells_by_default(const bool value) {
	_scale_spells_by_default = value;
}

bool ESS::get_automatic_load() const {
	return _automatic_load;
}
void ESS::set_automatic_load(const bool load) {
	_automatic_load = load;
}

bool ESS::get_use_class_xp() const {
	return _use_class_xp;
}
void ESS::set_use_class_xp(const bool value) {
	_use_class_xp = value;
}

bool ESS::get_allow_class_spell_learning() const {
	return _allow_class_spell_learning;
}
void ESS::set_allow_class_spell_learning(const bool value) {
	_allow_class_spell_learning = value;
}

bool ESS::get_allow_class_recipe_learning() const {
	return _allow_class_recipe_learning;
}
void ESS::set_allow_class_recipe_learning(const bool value) {
	_allow_class_recipe_learning = value;
}

int ESS::get_auto_learn_spells() const {
	return _auto_learn_spells;
}
void ESS::set_auto_learn_spells(const int value) {
	_auto_learn_spells = value;
}

Ref<ESSResourceDB> ESS::get_resource_db() {
	return _ess_resource_db;
}
void ESS::set_resource_db(const Ref<ESSResourceDB> &resource_db) {
	_ess_resource_db = resource_db;
}

ESSEntitySpawner *ESS::get_entity_spawner() {
	return _ess_entity_spawner;
}
void ESS::set_entity_spawner(ESSEntitySpawner *spawner) {
	_ess_entity_spawner = spawner;
}

void ESS::set_entity_spawner_bind(Node *spawner) {
	_ess_entity_spawner = Object::cast_to<ESSEntitySpawner>(spawner);
}

String ESS::get_resource_db_path() {
	return _ess_resource_db_path;
}
void ESS::set_resource_db_path(const String &path) {
	_ess_resource_db_path = path;
}

void ESS::request_entity_spawn(Ref<EntityCreateInfo> info) {
	if (_ess_entity_spawner)
		_ess_entity_spawner->request_entity_spawn(info);
}
void ESS::request_entity_spawn_deferred(Ref<EntityCreateInfo> info) {
	if (_ess_entity_spawner)
		_ess_entity_spawner->request_entity_spawn_deferred(info);
}

void ESS::load_resource_db() {
	_Directory dir;

	ERR_FAIL_COND(_ess_resource_db_path == "");

	Ref<ESSResourceDB> d = load_resource(_ess_resource_db_path, "ESSResourceDB");

	ERR_FAIL_COND(!d.is_valid());

	_ess_resource_db = d;
}

Ref<Resource> ESS::load_resource(const String &path, const String &type_hint) {
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

void ESS::load_all() {
	load_resource_db();

	_ess_resource_db->initialize();
}

//Stats
void ESS::stat_set_string(const String &stat_enum_string) {
	_stat_enum_string = stat_enum_string;

	_stat_id_to_name.clear();
	_stat_name_to_id.clear();

	_stat_id_to_property.clear();
	_stat_property_to_id.clear();

	int slicec = stat_enum_string.get_slice_count(",");
	_stat_id_to_name.resize(slicec);
	_stat_id_to_property.resize(slicec);

	for (int i = 0; i < slicec; ++i) {
		String slice = stat_enum_string.get_slicec(',', i);
		StringName s = StringName(slice);

		_stat_id_to_name.set(i, s);
		_stat_name_to_id.set(s, i);

		String st = slice;
		st = st.to_lower();
		st = st.replace(" ", "_");
		StringName stp = StringName(st);

		_stat_id_to_property.set(i, stp);
		_stat_property_to_id.set(stp, i);
	}
}
String ESS::stat_get_string() const {
	return _stat_enum_string;
}

int ESS::stat_get_id(const StringName &name) const {
	ERR_FAIL_COND_V(!_stat_name_to_id.has(name), 0);

	return _stat_name_to_id[name];
}
StringName ESS::stat_get_name(const int id) const {
	ERR_FAIL_INDEX_V(id, _stat_id_to_name.size(), StringName());

	return _stat_id_to_name[id];
}

int ESS::stat_get_property_id(const StringName &name) const {
	ERR_FAIL_COND_V(!_stat_property_to_id.has(name), 0);

	return _stat_property_to_id[name];
}
StringName ESS::stat_get_property_name(const int id) const {
	ERR_FAIL_INDEX_V(id, _stat_id_to_property.size(), StringName());

	return _stat_id_to_property[id];
}
bool ESS::stat_is_property(const StringName &name) const {
	return _stat_property_to_id.has(name);
}

int ESS::stat_get_count() const {
	return _stat_id_to_name.size();
}

PoolStringArray ESS::stats_get() const {
	PoolStringArray arr;
	arr.resize(_stat_id_to_name.size());

	for (int i = 0; i < _stat_id_to_name.size(); ++i) {
		arr.set(i, _stat_id_to_name[i]);
	}

	return arr;
}

void ESS::stats_set(const PoolStringArray &array) {
	_stat_enum_string = "";

	_stat_id_to_name.clear();
	_stat_name_to_id.clear();

	_stat_id_to_property.clear();
	_stat_property_to_id.clear();

	_stat_id_to_name.resize(array.size());
	_stat_id_to_property.resize(array.size());

	if (array.size() > 0)
		_stat_enum_string += array[0];

	for (int i = 0; i < array.size(); ++i) {
		StringName s = StringName(array[i]);

		_stat_id_to_name.set(i, s);
		_stat_name_to_id.set(s, i);

		String st = array[i];
		st = st.to_lower();
		st = st.replace(" ", "_");
		StringName stp = StringName(st);

		_stat_id_to_property.set(i, stp);
		_stat_property_to_id.set(stp, i);

		_stat_enum_string += ",";
		_stat_enum_string += array[i];
	}
}

int ESS::stat_get_main_stat_count() const {
	return _stat_main_stat_count;
}
void ESS::stat_set_main_stat_count(const int index) {
	_stat_main_stat_count = index;
}

//Equipslots
void ESS::equip_slot_set_string(const String &equip_slot_enum_string) {
	_equip_slot_id_to_name.clear();
	_equip_slot_name_to_id.clear();

	_equip_slot_id_to_property.clear();
	_equip_slot_property_to_id.clear();

	int slicec = equip_slot_enum_string.get_slice_count(",");
	_equip_slot_id_to_name.resize(slicec);
	_equip_slot_id_to_property.resize(slicec);

	for (int i = 0; i < slicec; ++i) {
		String slice = equip_slot_enum_string.get_slicec(',', i);
		StringName s = StringName(slice);

		_equip_slot_id_to_name.set(i, s);
		_equip_slot_name_to_id.set(s, i);

		String st = slice;
		st = st.to_lower();
		st = st.replace(" ", "_");
		StringName stp = StringName(st);

		_equip_slot_id_to_property.set(i, stp);
		_equip_slot_property_to_id.set(stp, i);
	}

	_equip_slot_enum_string = equip_slot_enum_string + ",None";
}
String ESS::equip_slot_get_string() const {
	return _equip_slot_enum_string;
}

int ESS::equip_slot_get_id(const StringName &name) const {
	ERR_FAIL_COND_V(!_equip_slot_name_to_id.has(name), 0);

	return _equip_slot_name_to_id[name];
}
StringName ESS::equip_slot_get_name(const int id) const {
	ERR_FAIL_INDEX_V(id, _equip_slot_id_to_name.size(), StringName());

	return _equip_slot_id_to_name[id];
}

int ESS::equip_slot_get_property_id(const StringName &name) const {
	ERR_FAIL_COND_V(!_equip_slot_property_to_id.has(name), 0);

	return _equip_slot_property_to_id[name];
}
StringName ESS::equip_slot_get_property_name(const int id) const {
	ERR_FAIL_INDEX_V(id, _equip_slot_id_to_property.size(), StringName());

	return _equip_slot_id_to_property[id];
}
bool ESS::equip_slot_is_property(const StringName &name) const {
	return _equip_slot_property_to_id.has(name);
}

int ESS::equip_slot_get_count() const {
	return _equip_slot_id_to_name.size();
}

PoolStringArray ESS::equip_slots_get() const {
	PoolStringArray arr;
	arr.resize(_equip_slot_id_to_name.size());

	for (int i = 0; i < _equip_slot_id_to_name.size(); ++i) {
		arr.set(i, _equip_slot_id_to_name[i]);
	}

	return arr;
}

void ESS::equip_slots_set(const PoolStringArray &array) {
	_equip_slot_enum_string = "";

	_equip_slot_id_to_name.clear();
	_equip_slot_name_to_id.clear();

	_equip_slot_id_to_property.clear();
	_equip_slot_property_to_id.clear();

	_equip_slot_id_to_name.resize(array.size());
	_equip_slot_id_to_property.resize(array.size());

	if (array.size() > 0)
		_equip_slot_enum_string += array[0];

	for (int i = 0; i < array.size(); ++i) {
		StringName s = StringName(array[i]);

		_equip_slot_id_to_name.set(i, s);
		_equip_slot_name_to_id.set(s, i);

		String st = array[i];
		st = st.to_lower();
		st = st.replace(" ", "_");
		StringName stp = StringName(st);

		_equip_slot_id_to_property.set(i, stp);
		_equip_slot_property_to_id.set(stp, i);

		_equip_slot_enum_string += ",";
		_equip_slot_enum_string += array[i];
	}
}

//Skeletons
String ESS::entity_types_get() const {
	return _entity_types;
}
void ESS::entity_types_set(const String &value) {
	_entity_types = value;
}

String ESS::skeletons_bones_index_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _skeletons_bones.size(), String());

	return _skeletons_bones[index];
}
int ESS::skeletons_bones_count() {
	return _skeletons_bones.size();
}

PoolStringArray ESS::skeletons_bones_get() const {
	return _skeletons_bones;
}
void ESS::skeletons_bones_set(const PoolStringArray &value) {
	_skeletons_bones = value;
}

String ESS::skeletons_bone_attachment_index_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _skeletons_bone_attachment_points.size(), String());

	return _skeletons_bone_attachment_points[index];
}
int ESS::skeletons_bone_attachments_count() {
	return _skeletons_bone_attachment_points.size();
}

PoolStringArray ESS::skeletons_bone_attachment_points_get() const {
	return _skeletons_bone_attachment_points;
}
void ESS::skeletons_bone_attachment_points_set(const PoolStringArray &value) {
	_skeletons_bone_attachment_points = value;
}

//Other
String ESS::model_visual_groups_get() const {
	return _model_visual_groups;
}
void ESS::model_visual_groups_set(const String &value) {
	_model_visual_groups = value;
}

String ESS::texture_layers_get() const {
	return _texture_layers;
}
void ESS::texture_layers_set(const String &value) {
	_texture_layers = value;
}

//Diminishing Returns
String ESS::dminishing_return_categories_get() const {
	return _dminishing_return_categories;
}
void ESS::dminishing_return_categories_set(const String &value) {
	_dminishing_return_categories = value;
}

float ESS::dminishing_return_length_get() const {
	return _dminishing_return_length;
}
void ESS::dminishing_return_length_set(const float value) {
	_dminishing_return_length = value;
}

int ESS::dminishing_return_steps_get() const {
	return _dminishing_return_steps;
}
void ESS::dminishing_return_steps_set(const int value) {
	_dminishing_return_steps = value;
}

//Levels/XP
int ESS::get_max_character_level() const {
	return _character_xps.size();
}
int ESS::get_max_class_level() const {
	return _class_xps.size();
}

int ESS::get_character_xp(int current_level) {
	current_level -= 1;

	ERR_FAIL_INDEX_V(current_level, _character_xps.size(), 9999999);

	return _character_xps.get(current_level);
}
void ESS::set_character_xp(int current_level, int value) {
	current_level -= 1;

	ERR_FAIL_INDEX(current_level, _character_xps.size());

	_character_xps.set(current_level, value);
}
bool ESS::can_character_level_up(int current_level) {
	current_level -= 1;

	return current_level < _character_xps.size();
}

PoolIntArray ESS::get_character_xp_data() {
	return _character_xps;
}
void ESS::set_character_xp_data(const PoolIntArray &data) {
	_character_xps = data;
}

int ESS::get_class_xp(int current_level) {
	current_level -= 1;

	ERR_FAIL_INDEX_V(current_level, _class_xps.size(), 9999999);

	return _class_xps.get(current_level);
}
void ESS::set_class_xp(int current_level, int value) {
	current_level -= 1;

	ERR_FAIL_INDEX(current_level, _class_xps.size());

	_class_xps.set(current_level, value);
}
bool ESS::can_class_level_up(int level) {
	return level < _class_xps.size();
}

PoolIntArray ESS::get_class_xp_data() {
	return _class_xps;
}
void ESS::set_class_xp_data(const PoolIntArray &data) {
	_class_xps = data;
}

void ESS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_use_spell_points"), &ESS::get_use_spell_points);
	ClassDB::bind_method(D_METHOD("set_use_spell_points", "value"), &ESS::set_use_spell_points);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_spell_points"), "set_use_spell_points", "get_use_spell_points");

	ClassDB::bind_method(D_METHOD("get_scale_spells_by_default"), &ESS::get_scale_spells_by_default);
	ClassDB::bind_method(D_METHOD("set_scale_spells_by_default", "value"), &ESS::set_scale_spells_by_default);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "scale_spells_by_default"), "set_scale_spells_by_default", "get_scale_spells_by_default");

	ClassDB::bind_method(D_METHOD("get_automatic_load"), &ESS::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &ESS::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	ClassDB::bind_method(D_METHOD("get_use_class_xp"), &ESS::get_use_class_xp);
	ClassDB::bind_method(D_METHOD("set_use_class_xp", "value"), &ESS::set_use_class_xp);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_class_xp"), "set_use_class_xp", "get_use_class_xp");

	ClassDB::bind_method(D_METHOD("get_allow_class_spell_learning"), &ESS::get_allow_class_spell_learning);
	ClassDB::bind_method(D_METHOD("set_allow_class_spell_learning", "value"), &ESS::set_allow_class_spell_learning);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "allow_class_spell_learning"), "set_allow_class_spell_learning", "get_allow_class_spell_learning");

	ClassDB::bind_method(D_METHOD("get_allow_class_recipe_learning"), &ESS::get_allow_class_recipe_learning);
	ClassDB::bind_method(D_METHOD("set_allow_class_recipe_learning", "value"), &ESS::set_allow_class_recipe_learning);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "allow_class_recipe_learning"), "set_allow_class_recipe_learning", "get_allow_class_recipe_learning");

	ClassDB::bind_method(D_METHOD("get_auto_learn_spells"), &ESS::get_auto_learn_spells);
	ClassDB::bind_method(D_METHOD("set_auto_learn_spells", "value"), &ESS::set_auto_learn_spells);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "auto_learn_spells"), "set_auto_learn_spells", "get_auto_learn_spells");

	ClassDB::bind_method(D_METHOD("get_resource_db"), &ESS::get_resource_db);
	ClassDB::bind_method(D_METHOD("set_resource_db"), &ESS::set_resource_db);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_db", PROPERTY_HINT_RESOURCE_TYPE, "ESSResourceDB"), "set_resource_db", "get_resource_db");

	ClassDB::bind_method(D_METHOD("get_entity_spawner"), &ESS::get_entity_spawner);
	ClassDB::bind_method(D_METHOD("set_entity_spawner"), &ESS::set_entity_spawner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_spawner", PROPERTY_HINT_RESOURCE_TYPE, "ESSEntitySpawner"), "set_entity_spawner", "get_entity_spawner");

	ClassDB::bind_method(D_METHOD("get_resource_db_path"), &ESS::get_resource_db_path);
	ClassDB::bind_method(D_METHOD("set_resource_db_path", "path"), &ESS::set_resource_db_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "resource_db_path"), "set_resource_db_path", "get_resource_db_path");

	//load
	ClassDB::bind_method(D_METHOD("load_resource_db"), &ESS::load_resource_db);

	ClassDB::bind_method(D_METHOD("load_resource", "path", "type_hint"), &ESS::load_resource, DEFVAL(""));

	ClassDB::bind_method(D_METHOD("request_entity_spawn", "info"), &ESS::request_entity_spawn);
	ClassDB::bind_method(D_METHOD("request_entity_spawn_deferred", "info"), &ESS::request_entity_spawn_deferred);

	ClassDB::bind_method(D_METHOD("load_all"), &ESS::load_all);

	//Stats
	ClassDB::bind_method(D_METHOD("stat_get_string"), &ESS::stat_get_string);
	ClassDB::bind_method(D_METHOD("stat_set_string", "stat_enum_string"), &ESS::stat_set_string);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "stat_string"), "stat_set_string", "stat_get_string");

	ClassDB::bind_method(D_METHOD("stat_get_id", "name"), &ESS::stat_get_id);
	ClassDB::bind_method(D_METHOD("stat_get_name", "id"), &ESS::stat_get_name);

	ClassDB::bind_method(D_METHOD("stat_get_property_id", "name"), &ESS::stat_get_property_id);
	ClassDB::bind_method(D_METHOD("stat_get_property_name", "id"), &ESS::stat_get_property_name);
	ClassDB::bind_method(D_METHOD("stat_is_property", "name"), &ESS::stat_is_property);

	ClassDB::bind_method(D_METHOD("stat_get_count"), &ESS::stat_get_count);

	ClassDB::bind_method(D_METHOD("stats_get"), &ESS::stats_get);
	ClassDB::bind_method(D_METHOD("stats_set", "array"), &ESS::stats_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "stats"), "stats_set", "stats_get");

	ClassDB::bind_method(D_METHOD("stat_get_main_stat_count"), &ESS::stat_get_main_stat_count);
	ClassDB::bind_method(D_METHOD("stat_set_main_stat_count", "index"), &ESS::stat_set_main_stat_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "main_stat_count"), "stat_set_main_stat_count", "stat_get_main_stat_count");

	//Equipslots
	ClassDB::bind_method(D_METHOD("equip_slot_get_string"), &ESS::equip_slot_get_string);
	ClassDB::bind_method(D_METHOD("equip_slot_set_string", "equip_slot_enum_string"), &ESS::equip_slot_set_string);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "equip_slot_string"), "equip_slot_set_string", "equip_slot_get_string");

	ClassDB::bind_method(D_METHOD("equip_slot_get_id", "name"), &ESS::equip_slot_get_id);
	ClassDB::bind_method(D_METHOD("equip_slot_get_name", "id"), &ESS::equip_slot_get_name);

	ClassDB::bind_method(D_METHOD("equip_slot_get_property_id", "name"), &ESS::equip_slot_get_property_id);
	ClassDB::bind_method(D_METHOD("equip_slot_get_property_name", "id"), &ESS::equip_slot_get_property_name);
	ClassDB::bind_method(D_METHOD("equip_slot_is_property", "name"), &ESS::equip_slot_is_property);

	ClassDB::bind_method(D_METHOD("equip_slot_get_count"), &ESS::equip_slot_get_count);

	ClassDB::bind_method(D_METHOD("equip_slots_get"), &ESS::equip_slots_get);
	ClassDB::bind_method(D_METHOD("equip_slots_set", "array"), &ESS::equip_slots_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "equip_slots"), "equip_slots_set", "equip_slots_get");

	//Skeletons
	ClassDB::bind_method(D_METHOD("entity_types_get"), &ESS::entity_types_get);
	ClassDB::bind_method(D_METHOD("entity_types_set", "value"), &ESS::entity_types_set);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_types"), "entity_types_set", "entity_types_get");

	ClassDB::bind_method(D_METHOD("skeletons_bones_index_get", "index"), &ESS::skeletons_bones_index_get);
	ClassDB::bind_method(D_METHOD("skeletons_bones_count"), &ESS::skeletons_bones_count);

	ClassDB::bind_method(D_METHOD("skeletons_bones_get"), &ESS::skeletons_bones_get);
	ClassDB::bind_method(D_METHOD("skeletons_bones_set", "value"), &ESS::skeletons_bones_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "skeletons_bones"), "skeletons_bones_set", "skeletons_bones_get");

	ClassDB::bind_method(D_METHOD("skeletons_bone_attachment_index_get", "index"), &ESS::skeletons_bone_attachment_index_get);
	ClassDB::bind_method(D_METHOD("skeletons_bone_attachments_count"), &ESS::skeletons_bone_attachments_count);

	ClassDB::bind_method(D_METHOD("skeletons_bone_attachment_points_get"), &ESS::skeletons_bone_attachment_points_get);
	ClassDB::bind_method(D_METHOD("skeletons_bone_attachment_points_set", "value"), &ESS::skeletons_bone_attachment_points_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "skeletons_bone_attachment_points"), "skeletons_bone_attachment_points_set", "skeletons_bone_attachment_points_get");

	//Other
	ClassDB::bind_method(D_METHOD("model_visual_groups_get"), &ESS::model_visual_groups_get);
	ClassDB::bind_method(D_METHOD("model_visual_groups_set", "value"), &ESS::model_visual_groups_set);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "model_visual_groups"), "model_visual_groups_set", "model_visual_groups_get");

	ClassDB::bind_method(D_METHOD("texture_layers_get"), &ESS::texture_layers_get);
	ClassDB::bind_method(D_METHOD("texture_layers_set", "value"), &ESS::texture_layers_set);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "texture_layers"), "texture_layers_set", "texture_layers_get");

	//Levels/XP
	ClassDB::bind_method(D_METHOD("get_max_character_level"), &ESS::get_max_character_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_character_level"), "", "get_max_character_level");

	ClassDB::bind_method(D_METHOD("get_max_class_level"), &ESS::get_max_class_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_class_level"), "", "get_max_class_level");

	ClassDB::bind_method(D_METHOD("get_character_xp", "current_level"), &ESS::get_character_xp);
	ClassDB::bind_method(D_METHOD("set_character_xp", "current_level", "value"), &ESS::set_character_xp);
	ClassDB::bind_method(D_METHOD("can_character_level_up", "current_level"), &ESS::can_character_level_up);

	ClassDB::bind_method(D_METHOD("get_character_xp_data"), &ESS::get_character_xp_data);
	ClassDB::bind_method(D_METHOD("set_character_xp_data", "data"), &ESS::set_character_xp_data);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "character_xp_data"), "set_character_xp_data", "get_character_xp_data");

	ClassDB::bind_method(D_METHOD("get_class_xp", "current_level"), &ESS::get_class_xp);
	ClassDB::bind_method(D_METHOD("set_class_xp", "current_level", "value"), &ESS::set_class_xp);
	ClassDB::bind_method(D_METHOD("can_class_level_up", "current_level"), &ESS::can_class_level_up);

	ClassDB::bind_method(D_METHOD("get_class_xp_data"), &ESS::get_class_xp_data);
	ClassDB::bind_method(D_METHOD("set_class_xp_data", "data"), &ESS::set_character_xp_data);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "class_xp_data"), "set_class_xp_data", "get_class_xp_data");
}

ESS::ESS() {
	instance = this;
	_ess_entity_spawner = NULL;

	_use_spell_points = GLOBAL_DEF("ess/spells/use_spell_points", false);
	_scale_spells_by_default = GLOBAL_DEF("ess/spells/scale_spells_by_default", false);
	_allow_class_spell_learning = GLOBAL_DEF("ess/spells/allow_class_spell_learning", false);
	_allow_class_recipe_learning = GLOBAL_DEF("ess/spells/allow_class_recipe_learning", false);

	_use_class_xp = GLOBAL_DEF("ess/level/use_class_xp", false);
	_automatic_class_levelups = GLOBAL_DEF("ess/level/automatic_class_levelups", false);
	_use_global_class_level = GLOBAL_DEF("ess/level/use_global_class_level", false);
	_auto_learn_spells = GLOBAL_DEF("ess/level/auto_learn_spells", true);

	_automatic_load = GLOBAL_DEF("ess/data/automatic_load", false);

	_ess_resource_db_path = GLOBAL_DEF("ess/data/ess_resource_db_path", "");

	stat_set_string(GLOBAL_DEF("ess/enums/stats", "Agility,Strength,Stamina,Intellect,Spirit,Health,Speed,Global Cooldown,Haste"));
	_stat_main_stat_count = GLOBAL_DEF("ess/enums/main_stat_count", 5);

	equip_slot_set_string(GLOBAL_DEF("ess/enums/equip_slots", "Head,Neck,Shoulder,Chest,Gloves,Belt,Legs,Feet,Ring_1,Ring_2,Trinket_1,Trinket_2,Main_Hand,Off_Hand"));

	_entity_types = GLOBAL_DEF("ess/enums/entity_types", "None,Creature,Totem,Idol,Humanoid,Mechanical,Beast,Dragonkin,Elemental,Ghost,Energy,Anomaly,Demon,Object");
	_skeletons_bones = GLOBAL_DEF("ess/enums/skeletons_bones", PoolStringArray());
	_skeletons_bone_attachment_points = GLOBAL_DEF("ess/enums/skeletons_bone_attachment_points", PoolStringArray());

	_model_visual_groups = GLOBAL_DEF("ess/enums/model_visual_groups", "None,Bodypart,Alt Bodypart,Attachment");

	_texture_layers = GLOBAL_DEF("ess/enums/texture_layers", "None,Skin,Underwear,Shirt,Clothes Base,Clothes 1,Clothes 2,Clothes 3,Clothes 4,Clothes 5,Belt,Tabard,Overlay");

	_dminishing_return_categories = GLOBAL_DEF("ess/enums/dminishing_return_categories", "Stun,Sleep,Disorient");
	_dminishing_return_length = GLOBAL_DEF("ess/enums/dminishing_return_length", 15.0);
	_dminishing_return_steps = GLOBAL_DEF("ess/enums/dminishing_return_steps", 4);

	_class_xps = GLOBAL_DEF("ess/xp/class_xps", PoolIntArray());
	_character_xps = GLOBAL_DEF("ess/xp/character_xps", PoolIntArray());

	if (!Engine::get_singleton()->is_editor_hint() && _automatic_load) {
		call_deferred("load_all");
	}
}

ESS::~ESS() {
	instance = NULL;

	_ess_resource_db.unref();
	_ess_entity_spawner = NULL;

	_stat_id_to_name.clear();
	_stat_name_to_id.clear();

	_stat_id_to_property.clear();
	_stat_property_to_id.clear();

	_equip_slot_id_to_name.clear();
	_equip_slot_name_to_id.clear();

	_equip_slot_id_to_property.clear();
	_equip_slot_property_to_id.clear();

	_skeletons_bones.resize(0);

	_class_xps.resize(0);
	_character_xps.resize(0);
}
