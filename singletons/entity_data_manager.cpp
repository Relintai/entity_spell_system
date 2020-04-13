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

String EntityDataManager::get_entity_resources_folder() {
	return _entity_resources_folder;
}
void EntityDataManager::set_entity_resources_folder(String folder) {
	_entity_resources_folder = folder;
}
Vector<Ref<EntityResourceData> > *EntityDataManager::get_entity_resources() {
	return &_entity_resources;
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

String EntityDataManager::get_entity_skills_folder() {
	return _entity_skills_folder;
}
void EntityDataManager::set_entity_skills_folder(String folder) {
	_entity_skills_folder = folder;
}
Vector<Ref<EntitySkillData> > *EntityDataManager::get_entity_skills() {
	return &_entity_skills;
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

String EntityDataManager::get_entity_datas_folder() {
	return _entity_datas_folder;
}
void EntityDataManager::set_entity_datas_folder(String folder) {
	_entity_datas_folder = folder;
}
Vector<Ref<EntityData> > *EntityDataManager::get_entity_datas() {
	return &_entity_datas;
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

String EntityDataManager::get_spells_folder() {
	return _spells_folder;
}
void EntityDataManager::set_spells_folder(String folder) {
	_spells_folder = folder;
}
Vector<Ref<Spell> > *EntityDataManager::get_spells() {
	return &_spells;
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

void EntityDataManager::add_aura(const Ref<Aura> &aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_auras.push_back(aura);
	_aura_map.set(aura->get_id(), aura);
}

String EntityDataManager::get_auras_folder() {
	return _auras_folder;
}
void EntityDataManager::set_auras_folder(String folder) {
	_auras_folder = folder;
}
Vector<Ref<Aura> > *EntityDataManager::get_auras() {
	return &_auras;
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

//Craft Data
void EntityDataManager::add_craft_data(const Ref<CraftRecipe> &cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_datas.push_back(cda);
	_craft_data_map.set(cda->get_id(), cda);
}

String EntityDataManager::get_craft_data_folder() {
	return _craft_data_folder;
}
void EntityDataManager::set_craft_data_folder(String folder) {
	_craft_data_folder = folder;
}
Vector<Ref<CraftRecipe> > *EntityDataManager::get_craft_datas() {
	return &_craft_datas;
}

Ref<CraftRecipe> EntityDataManager::get_craft_data(int craft_id) {
	ERR_FAIL_COND_V_MSG(!_craft_data_map.has(craft_id), Ref<CraftRecipe>(), "Could not find CraftRecipe! Id:" + String::num(craft_id));

	return _craft_data_map.get(craft_id);
}

Ref<CraftRecipe> EntityDataManager::get_craft_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_datas.size(), Ref<CraftRecipe>());

	return _craft_datas.get(index);
}

int EntityDataManager::get_craft_data_count() {
	return _craft_datas.size();
}

String EntityDataManager::get_item_template_folder() {
	return _item_template_folder;
}
void EntityDataManager::set_item_template_folder(String folder) {
	_item_template_folder = folder;
}
Vector<Ref<ItemTemplate> > *EntityDataManager::get_item_templates() {
	return &_item_templates;
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

String EntityDataManager::get_player_character_data_folder() {
	return _player_character_data_folder;
}
void EntityDataManager::set_player_character_data_folder(String folder) {
	_player_character_data_folder = folder;
}
Vector<Ref<EntityData> > *EntityDataManager::get_player_character_datas() {
	return &_player_character_datas;
}
void EntityDataManager::add_player_character_data(const Ref<EntityData> &cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_player_character_datas.push_back(cda);
	_player_character_data_map.set(cda->get_id(), cda);
}
Ref<EntityData> EntityDataManager::get_player_character_data(int item_id) {
	ERR_FAIL_COND_V_MSG(!_player_character_data_map.has(item_id), Ref<EntityData>(), "Could not find EntityData! Id:" + String::num(item_id));

	return _player_character_data_map.get(item_id);
}
Ref<EntityData> EntityDataManager::get_player_character_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _player_character_datas.size(), Ref<EntityData>());

	return _player_character_datas.get(index);
}
int EntityDataManager::get_player_character_data_count() {
	return _player_character_datas.size();
}

String EntityDataManager::get_entity_species_data_folder() {
	return _entity_species_data_folder;
}
void EntityDataManager::set_entity_species_data_folder(String folder) {
	_entity_species_data_folder = folder;
}
Vector<Ref<EntitySpeciesData> > *EntityDataManager::get_entity_species_datas() {
	return &_entity_species_datas;
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

void EntityDataManager::load_all() {
	load_xp_data();
	load_entity_resources();
	load_entity_skills();
	load_spells();
	load_auras();
	load_characters();
	load_craft_datas();
	load_item_templates();
	load_player_character_datas();
	load_entity_species_datas();
}

void EntityDataManager::load_xp_data() {
	_Directory dir;

	ERR_FAIL_COND(_xp_data_path == "");

	Ref<XPData> d = load_resource(_xp_data_path, "XPData");

	ERR_FAIL_COND(!d.is_valid());

	_xp_data = d;
}

void EntityDataManager::load_entity_resources() {
	_Directory dir;

	ERR_FAIL_COND(_entity_resources_folder.ends_with("/"));

	if (dir.open(_entity_resources_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _entity_resources_folder + "/" + filename;

				Ref<EntityResourceData> eresd = load_resource(path, "EntityResourceData");

				ERR_CONTINUE(!eresd.is_valid());

				add_entity_resource(eresd);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_entity_skills() {
	_Directory dir;

	ERR_FAIL_COND(_entity_skills_folder.ends_with("/"));

	if (dir.open(_entity_skills_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _entity_skills_folder + "/" + filename;

				Ref<EntitySkillData> eskilld = load_resource(path, "EntitySkillData");

				ERR_CONTINUE(!eskilld.is_valid());

				add_entity_skill(eskilld);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_spells() {
	_Directory dir;

	ERR_FAIL_COND(_spells_folder.ends_with("/"));

	if (dir.open(_spells_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _spells_folder + "/" + filename;

				Ref<Spell> spell = load_resource(path, "Spell");

				ERR_CONTINUE(!spell.is_valid());

				add_spell(spell);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_auras() {
	_Directory dir;

	ERR_FAIL_COND(_auras_folder.ends_with("/"));

	if (dir.open(_auras_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _auras_folder + "/" + filename;

				Ref<Aura> aura = load_resource(path, "Aura");

				ERR_CONTINUE(!aura.is_valid());

				add_aura(aura);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_characters() {
	_Directory dir;

	ERR_FAIL_COND(_entity_datas_folder.ends_with("/"));

	if (dir.open(_entity_datas_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _entity_datas_folder + "/" + filename;

				Ref<EntityData> cls = load_resource(path, "EntityData");

				ERR_CONTINUE(!cls.is_valid());

				add_entity_data(cls);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_craft_datas() {
	_Directory dir;

	ERR_FAIL_COND(_craft_data_folder.ends_with("/"));

	if (dir.open(_craft_data_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _craft_data_folder + "/" + filename;

				Ref<CraftRecipe> cda = load_resource(path, "CraftRecipe");

				ERR_CONTINUE(!cda.is_valid());

				add_craft_data(cda);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_item_templates() {
	_Directory dir;

	ERR_FAIL_COND(_item_template_folder.ends_with("/"));

	if (dir.open(_item_template_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _item_template_folder + "/" + filename;

				Ref<ItemTemplate> it = load_resource(path, "ItemTemplate");

				ERR_CONTINUE(!it.is_valid());

				add_item_template(it);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_player_character_datas() {
	_Directory dir;

	ERR_FAIL_COND(_player_character_data_folder.ends_with("/"));

	if (dir.open(_player_character_data_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _player_character_data_folder + "/" + filename;

				Ref<EntityData> pcd = load_resource(path, "EntityData");

				ERR_CONTINUE(!pcd.is_valid());

				add_player_character_data(pcd);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_entity_species_datas() {
	_Directory dir;

	ERR_FAIL_COND(_entity_species_data_folder.ends_with("/"));

	if (dir.open(_entity_species_data_folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path = _entity_species_data_folder + "/" + filename;

				Ref<EntitySpeciesData> pcd = load_resource(path, "EntitySpeciesData");

				ERR_CONTINUE(!pcd.is_valid());

				add_entity_species_data(pcd);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
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
	ClassDB::bind_method(D_METHOD("get_entity_resources_folder"), &EntityDataManager::get_entity_resources_folder);
	ClassDB::bind_method(D_METHOD("set_entity_resources_folder", "folder"), &EntityDataManager::set_entity_resources_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_resources_folder"), "set_entity_resources_folder", "get_entity_resources_folder");

	ClassDB::bind_method(D_METHOD("add_entity_resource", "cls"), &EntityDataManager::add_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource", "class_id"), &EntityDataManager::get_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource_index", "index"), &EntityDataManager::get_entity_resource_index);
	ClassDB::bind_method(D_METHOD("get_entity_resource_count"), &EntityDataManager::get_entity_resource_count);

	//EntitySkills
	ClassDB::bind_method(D_METHOD("get_entity_skills_folder"), &EntityDataManager::get_entity_skills_folder);
	ClassDB::bind_method(D_METHOD("set_entity_skills_folder", "folder"), &EntityDataManager::set_entity_skills_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_skills_folder"), "set_entity_skills_folder", "get_entity_skills_folder");

	ClassDB::bind_method(D_METHOD("add_entity_skill", "cls"), &EntityDataManager::add_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill", "class_id"), &EntityDataManager::get_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill_index", "index"), &EntityDataManager::get_entity_skill_index);
	ClassDB::bind_method(D_METHOD("get_entity_skill_count"), &EntityDataManager::get_entity_skill_count);

	//EntityData
	ClassDB::bind_method(D_METHOD("get_entity_datas_folder"), &EntityDataManager::get_entity_datas_folder);
	ClassDB::bind_method(D_METHOD("set_entity_datas_folder", "folder"), &EntityDataManager::set_entity_datas_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_datas_folder"), "set_entity_datas_folder", "get_entity_datas_folder");

	ClassDB::bind_method(D_METHOD("add_entity_data", "cls"), &EntityDataManager::add_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data", "class_id"), &EntityDataManager::get_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data_index", "index"), &EntityDataManager::get_entity_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_data_count"), &EntityDataManager::get_entity_data_count);

	//Spell
	ClassDB::bind_method(D_METHOD("get_spells_folder"), &EntityDataManager::get_spells_folder);
	ClassDB::bind_method(D_METHOD("set_spells_folder", "folder"), &EntityDataManager::set_spells_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "spells_folder"), "set_spells_folder", "get_spells_folder");

	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &EntityDataManager::add_spell);
	ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &EntityDataManager::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &EntityDataManager::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &EntityDataManager::get_spell_count);

	//Aura
	ClassDB::bind_method(D_METHOD("get_auras_folder"), &EntityDataManager::get_auras_folder);
	ClassDB::bind_method(D_METHOD("set_auras_folder", "folder"), &EntityDataManager::set_auras_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "auras_folder"), "set_auras_folder", "get_auras_folder");

	ClassDB::bind_method(D_METHOD("add_aura", "spell"), &EntityDataManager::add_aura);
	ClassDB::bind_method(D_METHOD("get_aura", "id"), &EntityDataManager::get_aura);
	ClassDB::bind_method(D_METHOD("get_aura_index", "index"), &EntityDataManager::get_aura_index);
	ClassDB::bind_method(D_METHOD("get_aura_count"), &EntityDataManager::get_aura_count);

	//Craft Data
	ClassDB::bind_method(D_METHOD("get_craft_data_folder"), &EntityDataManager::get_craft_data_folder);
	ClassDB::bind_method(D_METHOD("set_craft_data_folder", "folder"), &EntityDataManager::set_craft_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "craft_data_folder"), "set_craft_data_folder", "get_craft_data_folder");

	ClassDB::bind_method(D_METHOD("add_craft_data", "craft_data"), &EntityDataManager::add_craft_data);
	ClassDB::bind_method(D_METHOD("get_craft_data", "craft_data_id"), &EntityDataManager::get_craft_data);
	ClassDB::bind_method(D_METHOD("get_craft_data_index", "index"), &EntityDataManager::get_craft_data_index);
	ClassDB::bind_method(D_METHOD("get_craft_data_count"), &EntityDataManager::get_craft_data_count);

	//Item Templates
	ClassDB::bind_method(D_METHOD("get_item_template_folder"), &EntityDataManager::get_item_template_folder);
	ClassDB::bind_method(D_METHOD("set_item_template_folder", "folder"), &EntityDataManager::set_item_template_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "item_template_folder"), "set_item_template_folder", "get_item_template_folder");

	ClassDB::bind_method(D_METHOD("add_item_template", "item_template"), &EntityDataManager::add_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template", "item_template_id"), &EntityDataManager::get_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template_index", "index"), &EntityDataManager::get_item_template_index);
	ClassDB::bind_method(D_METHOD("get_item_template_count"), &EntityDataManager::get_item_template_count);

	//Player Character Data
	ClassDB::bind_method(D_METHOD("get_player_character_data_folder"), &EntityDataManager::get_player_character_data_folder);
	ClassDB::bind_method(D_METHOD("set_player_character_data_folder", "folder"), &EntityDataManager::set_player_character_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_character_data_folder"), "set_player_character_data_folder", "get_player_character_data_folder");

	ClassDB::bind_method(D_METHOD("add_player_character_data", "pcd"), &EntityDataManager::add_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data", "pcd_id"), &EntityDataManager::get_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data_index", "index"), &EntityDataManager::get_player_character_data_index);
	ClassDB::bind_method(D_METHOD("get_player_character_data_count"), &EntityDataManager::get_player_character_data_count);

	//Player Character Data
	ClassDB::bind_method(D_METHOD("get_entity_species_data_folder"), &EntityDataManager::get_entity_species_data_folder);
	ClassDB::bind_method(D_METHOD("set_entity_species_data_folder", "folder"), &EntityDataManager::set_entity_species_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_species_data_folder"), "set_entity_species_data_folder", "get_entity_species_data_folder");

	ClassDB::bind_method(D_METHOD("add_entity_species_data", "pcd"), &EntityDataManager::add_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data", "pcd_id"), &EntityDataManager::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_index", "index"), &EntityDataManager::get_entity_species_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_count"), &EntityDataManager::get_entity_species_data_count);

	//load
	ClassDB::bind_method(D_METHOD("load_all"), &EntityDataManager::load_all);
	ClassDB::bind_method(D_METHOD("load_entity_resources"), &EntityDataManager::load_entity_resources);
	ClassDB::bind_method(D_METHOD("load_entity_skills"), &EntityDataManager::load_entity_skills);
	ClassDB::bind_method(D_METHOD("load_xp_data"), &EntityDataManager::load_xp_data);
	ClassDB::bind_method(D_METHOD("load_spells"), &EntityDataManager::load_spells);
	ClassDB::bind_method(D_METHOD("load_auras"), &EntityDataManager::load_auras);
	ClassDB::bind_method(D_METHOD("load_characters"), &EntityDataManager::load_characters);
	ClassDB::bind_method(D_METHOD("load_craft_datas"), &EntityDataManager::load_craft_datas);
	ClassDB::bind_method(D_METHOD("load_item_templates"), &EntityDataManager::load_item_templates);
	ClassDB::bind_method(D_METHOD("load_player_character_datas"), &EntityDataManager::load_player_character_datas);
	ClassDB::bind_method(D_METHOD("load_entity_species_datas"), &EntityDataManager::load_entity_species_datas);

	ClassDB::bind_method(D_METHOD("load_resource", "path", "type_hint"), &EntityDataManager::load_resource);

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
	_entity_resources_folder = GLOBAL_DEF("ess/data/entity_resources_folder", "");
	_entity_skills_folder = GLOBAL_DEF("ess/data/entity_skills_folder", "");
	_entity_datas_folder = GLOBAL_DEF("ess/data/entity_datas_folder", "");
	_spells_folder = GLOBAL_DEF("ess/data/spells_folder", "");
	_auras_folder = GLOBAL_DEF("ess/data/auras_folder", "");
	_craft_data_folder = GLOBAL_DEF("ess/data/craft_data_folder", "");
	_item_template_folder = GLOBAL_DEF("ess/data/item_template_folder", "");
	_player_character_data_folder = GLOBAL_DEF("ess/data/player_character_data_folder", "");
	_entity_species_data_folder = GLOBAL_DEF("ess/data/entity_species_data_folder", "");

	if (_automatic_load) {
		call_deferred("load_all");
	}
}

EntityDataManager::~EntityDataManager() {
	instance = NULL;

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

	_craft_datas.clear();
	_craft_data_map.clear();

	_item_templates.clear();
	_item_template_map.clear();

	_player_character_datas.clear();
	_player_character_data_map.clear();

	_entity_species_datas.clear();
	_entity_species_data_map.clear();
}
