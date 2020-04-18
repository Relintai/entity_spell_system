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

#include "ess_resource_db_folders.h"

#include "../data/auras/aura.h"
#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource_data.h"
#include "../entities/skills/entity_skill_data.h"

bool ESSResourceDBFolders::get_automatic_load() const {
	return _automatic_load;
}
void ESSResourceDBFolders::set_automatic_load(const bool load) {
	_automatic_load = load;
}

bool ESSResourceDBFolders::get_load_folders() const {
	return _load_folders;
}
void ESSResourceDBFolders::set_load_folders(const bool load) {
	_load_folders = load;
}

String ESSResourceDBFolders::get_xp_data_path() {
	return _xp_data_path;
}
void ESSResourceDBFolders::set_xp_data_path(String path) {
	_xp_data_path = path;
}

PoolStringArray ESSResourceDBFolders::get_folders() const {
	return _folders;
}
void ESSResourceDBFolders::set_folders(const PoolStringArray &data) {
	_folders = data;
}

Ref<EntityResourceData> ESSResourceDBFolders::get_entity_resource(int class_id) {
	//ERR_FAIL_COND_V_MSG(!_entity_resource_map.has(class_id), Ref<EntityResourceData>(), "Could not find EntityResourceData! Id:" + String::num(class_id));

	if (!_entity_resource_map.has(class_id)) {
		return Ref<EntityResourceData>();
	}

	return _entity_resource_map.get(class_id);
}
Ref<EntityResourceData> ESSResourceDBFolders::get_entity_resource_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResourceData>(NULL));

	return _entity_resources.get(index);
}
int ESSResourceDBFolders::get_entity_resource_count() {
	return _entity_resources.size();
}
void ESSResourceDBFolders::add_entity_resource(Ref<EntityResourceData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_resources.push_back(cls);
	_entity_resource_map.set(cls->get_id(), cls);
}
Vector<Variant> ESSResourceDBFolders::get_entity_resources() const {
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
void ESSResourceDBFolders::set_entity_resources(const Vector<Variant> &data) {
	_entity_resources.clear();
	_entity_resource_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_resource(d);
	}
}

Ref<EntitySkillData> ESSResourceDBFolders::get_entity_skill(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_skill_map.has(class_id), Ref<EntitySkillData>(), "Could not find EntitySkillData! Id:" + String::num(class_id));

	return _entity_skill_map.get(class_id);
}
Ref<EntitySkillData> ESSResourceDBFolders::get_entity_skill_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_skills.size(), Ref<EntitySkillData>(NULL));

	return _entity_skills.get(index);
}
int ESSResourceDBFolders::get_entity_skill_count() {
	return _entity_skills.size();
}
void ESSResourceDBFolders::add_entity_skill(Ref<EntitySkillData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_skills.push_back(cls);
	_entity_skill_map.set(cls->get_id(), cls);
}
Vector<Variant> ESSResourceDBFolders::get_entity_skills() const {
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
void ESSResourceDBFolders::set_entity_skills(const Vector<Variant> &data) {
	_entity_skills.clear();
	_entity_skill_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySkillData> d = Ref<EntitySkillData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_skill(d);
	}
}

Ref<EntityData> ESSResourceDBFolders::get_entity_data(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_data_map.has(class_id), Ref<EntityData>(), "Could not find EntityData! Id:" + String::num(class_id));

	return _entity_data_map.get(class_id);
}
Ref<EntityData> ESSResourceDBFolders::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}
int ESSResourceDBFolders::get_entity_data_count() {
	return _entity_datas.size();
}
void ESSResourceDBFolders::add_entity_data(Ref<EntityData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_datas.push_back(cls);
	_entity_data_map.set(cls->get_id(), cls);
}
Vector<Variant> ESSResourceDBFolders::get_entity_datas() const {
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
void ESSResourceDBFolders::set_entity_datas(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_data(d);
	}
}

Ref<Spell> ESSResourceDBFolders::get_spell(int spell_id) {
	ERR_FAIL_COND_V_MSG(!_spell_map.has(spell_id), Ref<Spell>(), "Could not find Spell! Id:" + String::num(spell_id));

	return _spell_map.get(spell_id);
}

Ref<Spell> ESSResourceDBFolders::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}
int ESSResourceDBFolders::get_spell_count() {
	return _spells.size();
}
void ESSResourceDBFolders::add_spell(Ref<Spell> spell) {
	ERR_FAIL_COND(!spell.is_valid());

	_spells.push_back(spell);
	_spell_map.set(spell->get_id(), spell);
}
Vector<Variant> ESSResourceDBFolders::get_spells() const {
	Vector<Variant> r;
	for (int i = 0; i < _spells.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_spells[i].get_ref_ptr());
#else
		r.push_back(_spells[i]);
#endif
	}
	return r;
}
void ESSResourceDBFolders::set_spells(const Vector<Variant> &data) {
	_spells.clear();
	_spell_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Spell> d = Ref<Spell>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_spell(d);
	}
}

void ESSResourceDBFolders::add_aura(Ref<Aura> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_auras.push_back(aura);
	_aura_map.set(aura->get_id(), aura);
}

Ref<Aura> ESSResourceDBFolders::get_aura(int aura_id) {
	ERR_FAIL_COND_V_MSG(!_aura_map.has(aura_id), Ref<Aura>(), "Could not find Aura! Id:" + String::num(aura_id));

	return _aura_map.get(aura_id);
}

Ref<Aura> ESSResourceDBFolders::get_aura_index(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras.get(index);
}

int ESSResourceDBFolders::get_aura_count() {
	return _auras.size();
}

Vector<Variant> ESSResourceDBFolders::get_auras() const {
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
void ESSResourceDBFolders::set_auras(const Vector<Variant> &data) {
	_auras.clear();
	_aura_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Aura> d = Ref<Aura>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_aura(d);
	}
}

//Craft Data
void ESSResourceDBFolders::add_craft_recipe(Ref<CraftRecipe> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_recipes.push_back(cda);
	_craft_recipe_map.set(cda->get_id(), cda);
}

Ref<CraftRecipe> ESSResourceDBFolders::get_craft_recipe(int craft_id) {
	ERR_FAIL_COND_V_MSG(!_craft_recipe_map.has(craft_id), Ref<CraftRecipe>(), "Could not find CraftRecipe! Id:" + String::num(craft_id));

	return _craft_recipe_map.get(craft_id);
}

Ref<CraftRecipe> ESSResourceDBFolders::get_craft_recipe_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes.get(index);
}

int ESSResourceDBFolders::get_craft_recipe_count() {
	return _craft_recipes.size();
}

Vector<Variant> ESSResourceDBFolders::get_craft_recipes() const {
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
void ESSResourceDBFolders::set_craft_recipes(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<CraftRecipe> d = Ref<CraftRecipe>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_craft_recipe(d);
	}
}

void ESSResourceDBFolders::add_item_template(Ref<ItemTemplate> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_item_templates.push_back(cda);
	_item_template_map.set(cda->get_id(), cda);
}

Ref<ItemTemplate> ESSResourceDBFolders::get_item_template(int item_id) {
	ERR_FAIL_COND_V_MSG(!_item_template_map.has(item_id), Ref<ItemTemplate>(), "Could not find ItemTemplate! Id:" + String::num(item_id));

	return _item_template_map.get(item_id);
}

Ref<ItemTemplate> ESSResourceDBFolders::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>());

	return _item_templates.get(index);
}

int ESSResourceDBFolders::get_item_template_count() {
	return _item_templates.size();
}
Vector<Variant> ESSResourceDBFolders::get_item_templates() const {
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
void ESSResourceDBFolders::set_item_templates(const Vector<Variant> &data) {
	_item_templates.clear();
	_item_template_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<ItemTemplate> d = Ref<ItemTemplate>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

void ESSResourceDBFolders::add_entity_species_data(Ref<EntitySpeciesData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_entity_species_datas.push_back(cda);
	_entity_species_data_map.set(cda->get_id(), cda);
}
Ref<EntitySpeciesData> ESSResourceDBFolders::get_entity_species_data(int item_id) {
	if (!_entity_species_data_map.has(item_id))
		return Ref<EntitySpeciesData>();

	return _entity_species_data_map.get(item_id);
}
Ref<EntitySpeciesData> ESSResourceDBFolders::get_entity_species_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_species_datas.size(), Ref<EntitySpeciesData>());

	return _entity_species_datas.get(index);
}
int ESSResourceDBFolders::get_entity_species_data_count() {
	return _entity_species_datas.size();
}
Vector<Variant> ESSResourceDBFolders::get_entity_species_datas() const {
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
void ESSResourceDBFolders::set_entity_species_datas(const Vector<Variant> &data) {
	_entity_species_datas.clear();
	_entity_species_data_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySpeciesData> d = Ref<EntitySpeciesData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

void ESSResourceDBFolders::_initialize() {
	load_all();
}

void ESSResourceDBFolders::load_all() {
	load_xp_data();
	load_folders();
}

void ESSResourceDBFolders::load_xp_data() {
	_Directory dir;

	ERR_FAIL_COND(_xp_data_path == "");

	Ref<XPData> d = load_resource(_xp_data_path, "XPData");

	ERR_FAIL_COND(!d.is_valid());

	set_xp_data(d);
}

void ESSResourceDBFolders::load_folders() {
	for (int i = 0; i < _folders.size(); ++i) {
		load_folder(_folders[i]);
	}
}

void ESSResourceDBFolders::load_folder(const String &folder) {
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

void ESSResourceDBFolders::add_resource(const Ref<Resource> &resource) {
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
		set_xp_data(resource);
	}
}

Ref<Resource> ESSResourceDBFolders::load_resource(const String &path, const String &type_hint) {
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

ESSResourceDBFolders::ESSResourceDBFolders() {
	_automatic_load = false;

	_xp_data_path = "";

	if (_automatic_load) {
		call_deferred("load_all");
	}
}

ESSResourceDBFolders::~ESSResourceDBFolders() {
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

void ESSResourceDBFolders::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_automatic_load"), &ESSResourceDBFolders::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &ESSResourceDBFolders::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	//XPData
	ClassDB::bind_method(D_METHOD("get_xp_data_path"), &ESSResourceDBFolders::get_xp_data_path);
	ClassDB::bind_method(D_METHOD("set_xp_data_path", "path"), &ESSResourceDBFolders::set_xp_data_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp_data_path"), "set_xp_data_path", "get_xp_data_path");

	ClassDB::bind_method(D_METHOD("get_folders"), &ESSResourceDBFolders::get_folders);
	ClassDB::bind_method(D_METHOD("set_folders", "recipe"), &ESSResourceDBFolders::set_folders);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "folders"), "set_folders", "get_folders");

	//load
	ClassDB::bind_method(D_METHOD("_initialize"), &ESSResourceDBFolders::_initialize);
	ClassDB::bind_method(D_METHOD("load_all"), &ESSResourceDBFolders::load_all);
	ClassDB::bind_method(D_METHOD("load_xp_data"), &ESSResourceDBFolders::load_xp_data);
	ClassDB::bind_method(D_METHOD("load_folders"), &ESSResourceDBFolders::load_folders);
	ClassDB::bind_method(D_METHOD("load_folder", "folder"), &ESSResourceDBFolders::load_folder);
	ClassDB::bind_method(D_METHOD("add_resource", "resource"), &ESSResourceDBFolders::add_resource);

	ClassDB::bind_method(D_METHOD("load_resource", "path", "type_hint"), &ESSResourceDBFolders::load_resource, DEFVAL(""));
}
