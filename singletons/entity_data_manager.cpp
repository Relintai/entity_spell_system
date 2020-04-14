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

#include "../data/auras/aura.h"
#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource_data.h"
#include "../entities/skills/entity_skill_data.h"

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

bool EntityDataManager::get_load_folders() const {
	return _load_folders;
}
void EntityDataManager::set_load_folders(const bool load) {
	_load_folders = load;
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

Ref<Aura> EntityDataManager::get_skill_for_armor_type(const int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::ARMOR_TYPE_MAX, Ref<Aura>());

	return _armor_type_skills[index];
}
void EntityDataManager::set_skill_for_armor_type(const int index, const Ref<Aura> &aura) {
	ERR_FAIL_INDEX(index, ItemEnums::ARMOR_TYPE_MAX);

	_armor_type_skills[index] = aura;
}

String EntityDataManager::get_xp_data_path() {
	return _xp_data_path;
}
void EntityDataManager::set_xp_data_path(String path) {
	_xp_data_path = path;
}
Ref<XPData> EntityDataManager::get_xp_data() {
	return _xp_data;
}

Ref<EntityResourceData> EntityDataManager::get_entity_resource(int class_id) {
	//ERR_FAIL_COND_V_MSG(!_entity_resource_map.has(class_id), Ref<EntityResourceData>(), "Could not find EntityResourceData! Id:" + String::num(class_id));

	if (!_entity_resource_map.has(class_id)) {
		return Ref<EntityResourceData>();
	}

	return _entity_resource_map.get(class_id);
}
Ref<EntityResourceData> EntityDataManager::get_entity_resource_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResourceData>(NULL));

	return _entity_resources.get(index);
}
int EntityDataManager::get_entity_resource_count() {
	return _entity_resources.size();
}
void EntityDataManager::add_entity_resource(const Ref<EntityResourceData> &cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_resources.push_back(cls);
	_entity_resource_map.set(cls->get_id(), cls);
}
Vector<Variant> EntityDataManager::get_entity_resources() const {
	Vector<Variant> r;
	for (int i = 0; i < _entity_resources.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_entity_resources[i].get_ref_ptr());
#else
		r.push_back(_entity_resources[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_entity_resources(const Vector<Variant> &data) {
	_entity_resources.clear();
	_entity_resource_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_resource(d);
	}
}

Ref<EntitySkillData> EntityDataManager::get_entity_skill(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_skill_map.has(class_id), Ref<EntitySkillData>(), "Could not find EntitySkillData! Id:" + String::num(class_id));

	return _entity_skill_map.get(class_id);
}
Ref<EntitySkillData> EntityDataManager::get_entity_skill_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_skills.size(), Ref<EntitySkillData>(NULL));

	return _entity_skills.get(index);
}
int EntityDataManager::get_entity_skill_count() {
	return _entity_skills.size();
}
void EntityDataManager::add_entity_skill(const Ref<EntitySkillData> &cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_skills.push_back(cls);
	_entity_skill_map.set(cls->get_id(), cls);
}
Vector<Variant> EntityDataManager::get_entity_skills() const {
	Vector<Variant> r;
	for (int i = 0; i < _entity_skills.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_entity_skills[i].get_ref_ptr());
#else
		r.push_back(_entity_skills[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_entity_skills(const Vector<Variant> &data) {
	_entity_skills.clear();
	_entity_skill_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySkillData> d = Ref<EntitySkillData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_skill(d);
	}
}

Ref<EntityData> EntityDataManager::get_entity_data(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_data_map.has(class_id), Ref<EntityData>(), "Could not find EntityData! Id:" + String::num(class_id));

	return _entity_data_map.get(class_id);
}
Ref<EntityData> EntityDataManager::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}
int EntityDataManager::get_entity_data_count() {
	return _entity_datas.size();
}
void EntityDataManager::add_entity_data(const Ref<EntityData> &cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_datas.push_back(cls);
	_entity_data_map.set(cls->get_id(), cls);
}
Vector<Variant> EntityDataManager::get_entity_datas() const {
	Vector<Variant> r;
	for (int i = 0; i < _entity_datas.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_entity_datas[i].get_ref_ptr());
#else
		r.push_back(_entity_datas[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_entity_datas(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_data(d);
	}
}

Ref<Spell> EntityDataManager::get_spell(int spell_id) {
	ERR_FAIL_COND_V_MSG(!_spell_map.has(spell_id), Ref<Spell>(), "Could not find Spell! Id:" + String::num(spell_id));

	return _spell_map.get(spell_id);
}

Ref<Spell> EntityDataManager::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}
int EntityDataManager::get_spell_count() {
	return _spells.size();
}
void EntityDataManager::add_spell(const Ref<Spell> &spell) {
	ERR_FAIL_COND(!spell.is_valid());

	_spells.push_back(spell);
	_spell_map.set(spell->get_id(), spell);
}
Vector<Variant> EntityDataManager::get_spells() const {
	Vector<Variant> r;
	for (int i = 0; i < _craft_recipes.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_craft_recipes[i].get_ref_ptr());
#else
		r.push_back(_craft_recipes[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_spells(const Vector<Variant> &data) {
	_spells.clear();
	_spell_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Spell> d = Ref<Spell>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_spell(d);
	}
}

void EntityDataManager::add_aura(const Ref<Aura> &aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_auras.push_back(aura);
	_aura_map.set(aura->get_id(), aura);
}

Ref<Aura> EntityDataManager::get_aura(int aura_id) {
	ERR_FAIL_COND_V_MSG(!_aura_map.has(aura_id), Ref<Aura>(), "Could not find Aura! Id:" + String::num(aura_id));

	return _aura_map.get(aura_id);
}

Ref<Aura> EntityDataManager::get_aura_index(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras.get(index);
}

int EntityDataManager::get_aura_count() {
	return _auras.size();
}

Vector<Variant> EntityDataManager::get_auras() const {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_auras[i].get_ref_ptr());
#else
		r.push_back(_auras[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_auras(const Vector<Variant> &data) {
	_auras.clear();
	_aura_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Aura> d = Ref<Aura>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_aura(d);
	}
}

//Craft Data
void EntityDataManager::add_craft_recipe(const Ref<CraftRecipe> &cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_recipes.push_back(cda);
	_craft_recipe_map.set(cda->get_id(), cda);
}

Ref<CraftRecipe> EntityDataManager::get_craft_recipe(int craft_id) {
	ERR_FAIL_COND_V_MSG(!_craft_recipe_map.has(craft_id), Ref<CraftRecipe>(), "Could not find CraftRecipe! Id:" + String::num(craft_id));

	return _craft_recipe_map.get(craft_id);
}

Ref<CraftRecipe> EntityDataManager::get_craft_recipe_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes.get(index);
}

int EntityDataManager::get_craft_recipe_count() {
	return _craft_recipes.size();
}

Vector<Variant> EntityDataManager::get_craft_recipes() const {
	Vector<Variant> r;
	for (int i = 0; i < _craft_recipes.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_craft_recipes[i].get_ref_ptr());
#else
		r.push_back(_craft_recipes[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_craft_recipes(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<CraftRecipe> d = Ref<CraftRecipe>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_craft_recipe(d);
	}
}

void EntityDataManager::add_item_template(const Ref<ItemTemplate> &cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_item_templates.push_back(cda);
	_item_template_map.set(cda->get_id(), cda);
}

Ref<ItemTemplate> EntityDataManager::get_item_template(int item_id) {
	ERR_FAIL_COND_V_MSG(!_item_template_map.has(item_id), Ref<ItemTemplate>(), "Could not find ItemTemplate! Id:" + String::num(item_id));

	return _item_template_map.get(item_id);
}

Ref<ItemTemplate> EntityDataManager::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>());

	return _item_templates.get(index);
}

int EntityDataManager::get_item_template_count() {
	return _item_templates.size();
}
Vector<Variant> EntityDataManager::get_item_templates() const {
	Vector<Variant> r;
	for (int i = 0; i < _item_templates.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_item_templates[i].get_ref_ptr());
#else
		r.push_back(_item_templates[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_item_templates(const Vector<Variant> &data) {
	_item_templates.clear();
	_item_template_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<ItemTemplate> d = Ref<ItemTemplate>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

void EntityDataManager::add_entity_species_data(const Ref<EntitySpeciesData> &cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_entity_species_datas.push_back(cda);
	_entity_species_data_map.set(cda->get_id(), cda);
}
Ref<EntitySpeciesData> EntityDataManager::get_entity_species_data(int item_id) {
	if (!_entity_species_data_map.has(item_id))
		return Ref<EntitySpeciesData>();

	return _entity_species_data_map.get(item_id);
}
Ref<EntitySpeciesData> EntityDataManager::get_entity_species_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_species_datas.size(), Ref<EntitySpeciesData>());

	return _entity_species_datas.get(index);
}
int EntityDataManager::get_entity_species_data_count() {
	return _entity_species_datas.size();
}
Vector<Variant> EntityDataManager::get_entity_species_datas() const {
	Vector<Variant> r;
	for (int i = 0; i < _entity_species_datas.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_entity_species_datas[i].get_ref_ptr());
#else
		r.push_back(_entity_species_datas[i]);
#endif
	}
	return r;
}
void EntityDataManager::set_entity_species_datas(const Vector<Variant> &data) {
	_entity_species_datas.clear();
	_entity_species_data_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySpeciesData> d = Ref<EntitySpeciesData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

void EntityDataManager::load_all() {
	load_xp_data();
	load_folders();
}

void EntityDataManager::load_xp_data() {
	_Directory dir;

	ERR_FAIL_COND(_xp_data_path == "");

	Ref<XPData> d = load_resource(_xp_data_path, "XPData");

	ERR_FAIL_COND(!d.is_valid());

	_xp_data = d;
}

void EntityDataManager::load_folders() {
	for (int i = 0; i < _folders.size(); ++i) {
		load_folder(_folders[i]);
	}
}

void EntityDataManager::load_folder(const String &folder) {
	_Directory dir;

	bool ew = folder.ends_with("/");

	if (dir.open(folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path;

				if (ew)
					path = folder + filename;
				else
					path = folder + "/" + filename;

				Ref<Resource> res = load_resource(path);

				ERR_CONTINUE(!res.is_valid());

				add_resource(res);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::add_resource(const Ref<Resource> &resource) {
	StringName cls = resource->get_class_name();

	if (cls == "EntityResourceData") {
		add_entity_resource(resource);
	} else if (cls == "EntitySkillData") {
		add_entity_skill(resource);
	} else if (cls == "EntityData") {
		add_entity_data(resource);
	} else if (cls == "Spell") {
		add_spell(resource);
	} else if (cls == "Aura") {
		add_aura(resource);
	} else if (cls == "CraftRecipe") {
		add_craft_recipe(resource);
	} else if (cls == "ItemTemplate") {
		add_item_template(resource);
	} else if (cls == "EntitySpeciesData") {
		add_entity_species_data(resource);
	} else if (cls == "XPData") {
		_xp_data = resource;
	}
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

	ClassDB::bind_method(D_METHOD("get_skill_for_armor_type", "index"), &EntityDataManager::get_skill_for_armor_type);
	ClassDB::bind_method(D_METHOD("set_skill_for_armor_type", "index", "aura"), &EntityDataManager::set_skill_for_armor_type);

	for (int i = 0; i < ItemEnums::ARMOR_TYPE_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "skill_for_armor_type_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_skill_for_armor_type", "get_skill_for_armor_type", i);
	}

	//XPData
	ClassDB::bind_method(D_METHOD("get_xp_data_path"), &EntityDataManager::get_xp_data_path);
	ClassDB::bind_method(D_METHOD("set_xp_data_path", "path"), &EntityDataManager::set_xp_data_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp_data_path"), "set_xp_data_path", "get_xp_data_path");

	ClassDB::bind_method(D_METHOD("get_xp_data"), &EntityDataManager::get_xp_data);

	//EntityResourceData
	ClassDB::bind_method(D_METHOD("add_entity_resource", "cls"), &EntityDataManager::add_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource", "class_id"), &EntityDataManager::get_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource_index", "index"), &EntityDataManager::get_entity_resource_index);
	ClassDB::bind_method(D_METHOD("get_entity_resource_count"), &EntityDataManager::get_entity_resource_count);
	ClassDB::bind_method(D_METHOD("get_entity_resources"), &EntityDataManager::get_entity_resources);
	ClassDB::bind_method(D_METHOD("set_entity_resources", "recipe"), &EntityDataManager::set_entity_resources);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_resources", PROPERTY_HINT_NONE, "17/17:EntityResourceData", PROPERTY_USAGE_DEFAULT, "EntityResourceData"), "set_entity_resources", "get_entity_resources");

	//EntitySkills
	ClassDB::bind_method(D_METHOD("add_entity_skill", "cls"), &EntityDataManager::add_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill", "class_id"), &EntityDataManager::get_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill_index", "index"), &EntityDataManager::get_entity_skill_index);
	ClassDB::bind_method(D_METHOD("get_entity_skill_count"), &EntityDataManager::get_entity_skill_count);
	ClassDB::bind_method(D_METHOD("get_craft_recipes"), &EntityDataManager::get_craft_recipes);
	ClassDB::bind_method(D_METHOD("set_craft_recipes", "recipe"), &EntityDataManager::set_craft_recipes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "craft_recipes", PROPERTY_HINT_NONE, "17/17:CraftRecipe", PROPERTY_USAGE_DEFAULT, "CraftRecipe"), "set_craft_recipes", "get_craft_recipes");

	//EntityData
	ClassDB::bind_method(D_METHOD("add_entity_data", "cls"), &EntityDataManager::add_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data", "class_id"), &EntityDataManager::get_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data_index", "index"), &EntityDataManager::get_entity_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_data_count"), &EntityDataManager::get_entity_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_skills"), &EntityDataManager::get_entity_skills);
	ClassDB::bind_method(D_METHOD("set_entity_skills", "recipe"), &EntityDataManager::set_entity_skills);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_skills", PROPERTY_HINT_NONE, "17/17:EntitySkillData", PROPERTY_USAGE_DEFAULT, "EntitySkillData"), "set_entity_skills", "get_entity_skills");

	//Spell
	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &EntityDataManager::add_spell);
	ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &EntityDataManager::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &EntityDataManager::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &EntityDataManager::get_spell_count);
	ClassDB::bind_method(D_METHOD("get_spells"), &EntityDataManager::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "recipe"), &EntityDataManager::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	//Aura
	ClassDB::bind_method(D_METHOD("add_aura", "spell"), &EntityDataManager::add_aura);
	ClassDB::bind_method(D_METHOD("get_aura", "id"), &EntityDataManager::get_aura);
	ClassDB::bind_method(D_METHOD("get_aura_index", "index"), &EntityDataManager::get_aura_index);
	ClassDB::bind_method(D_METHOD("get_aura_count"), &EntityDataManager::get_aura_count);
	ClassDB::bind_method(D_METHOD("get_auras"), &EntityDataManager::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "recipe"), &EntityDataManager::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	//Craft Data
	ClassDB::bind_method(D_METHOD("add_craft_recipe", "craft_recipe"), &EntityDataManager::add_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe", "craft_recipe_id"), &EntityDataManager::get_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_index", "index"), &EntityDataManager::get_craft_recipe_index);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_count"), &EntityDataManager::get_craft_recipe_count);
	ClassDB::bind_method(D_METHOD("get_craft_recipes"), &EntityDataManager::get_craft_recipes);
	ClassDB::bind_method(D_METHOD("set_craft_recipes", "recipe"), &EntityDataManager::set_craft_recipes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "craft_recipes", PROPERTY_HINT_NONE, "17/17:CraftRecipe", PROPERTY_USAGE_DEFAULT, "CraftRecipe"), "set_craft_recipes", "get_craft_recipes");

	//Item Templates
	ClassDB::bind_method(D_METHOD("add_item_template", "item_template"), &EntityDataManager::add_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template", "item_template_id"), &EntityDataManager::get_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template_index", "index"), &EntityDataManager::get_item_template_index);
	ClassDB::bind_method(D_METHOD("get_item_template_count"), &EntityDataManager::get_item_template_count);
	ClassDB::bind_method(D_METHOD("get_item_templates"), &EntityDataManager::get_item_templates);
	ClassDB::bind_method(D_METHOD("set_item_templates", "recipe"), &EntityDataManager::set_item_templates);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "item_templates", PROPERTY_HINT_NONE, "17/17:ItemTemplate", PROPERTY_USAGE_DEFAULT, "ItemTemplate"), "set_item_templates", "get_item_templates");

	//Player Character Data
	ClassDB::bind_method(D_METHOD("add_entity_species_data", "pcd"), &EntityDataManager::add_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data", "pcd_id"), &EntityDataManager::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_index", "index"), &EntityDataManager::get_entity_species_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_count"), &EntityDataManager::get_entity_species_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_species_datas"), &EntityDataManager::get_entity_species_datas);
	ClassDB::bind_method(D_METHOD("set_entity_species_datas", "recipe"), &EntityDataManager::set_entity_species_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_species_datas", PROPERTY_HINT_NONE, "17/17:EntitySpeciesData", PROPERTY_USAGE_DEFAULT, "EntitySpeciesData"), "set_entity_species_datas", "get_entity_species_datas");

	//load
	ClassDB::bind_method(D_METHOD("load_all"), &EntityDataManager::load_all);
	ClassDB::bind_method(D_METHOD("load_xp_data"), &EntityDataManager::load_xp_data);
	ClassDB::bind_method(D_METHOD("load_folders"), &EntityDataManager::load_folders);
	ClassDB::bind_method(D_METHOD("load_folder", "folder"), &EntityDataManager::load_folder);
	ClassDB::bind_method(D_METHOD("add_resource", "resource"), &EntityDataManager::add_resource);

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

	_xp_data_path = GLOBAL_DEF("ess/data/xp_data_path", "");

	if (_automatic_load) {
		call_deferred("load_all");
	}
}

EntityDataManager::~EntityDataManager() {
	instance = NULL;

	_folders.clear();

	_entity_resources.clear();
	_entity_resource_map.clear();

	_entity_skills.clear();
	_entity_skill_map.clear();

	_entity_datas.clear();
	_entity_data_map.clear();

	_spells.clear();
	_spell_map.clear();

	_auras.clear();
	_aura_map.clear();

	_craft_recipes.clear();
	_craft_recipe_map.clear();

	_item_templates.clear();
	_item_template_map.clear();

	_entity_species_datas.clear();
	_entity_species_data_map.clear();
}
