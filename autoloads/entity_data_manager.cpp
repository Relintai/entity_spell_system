#include "entity_data_manager.h"

#include "../entities/data/entity_data.h"
#include "../data/aura.h"
#include "../data/craft_recipe.h"
#include "../data/spell.h"
#include "../entities/resources/entity_resource_data.h"
#include "../entities/skills/entity_skill_data.h"

EntityDataManager *EntityDataManager::instance;

EntityDataManager *EntityDataManager::get_instance() {
	return instance;
}

void EntityDataManager::_notification(int p_what) {

	switch (p_what) {

		case NOTIFICATION_ENTER_TREE: {
			if (get_automatic_load()) {
				load_all();
			}
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}
}

Ref<Aura> EntityDataManager::get_skill_for_armor_type(int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::ARMOR_TYPE_MAX, Ref<Aura>());

	return _armor_type_skills[index];
}
void EntityDataManager::set_skill_for_armor_type(int index, Ref<Aura> aura) {
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
	if (!_entity_resource_map.has(class_id))
		return Ref<EntityResourceData>(NULL);

	return _entity_resource_map.get(class_id);
}
Ref<EntityResourceData> EntityDataManager::get_entity_resource_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResourceData>(NULL));

	return _entity_resources.get(index);
}
int EntityDataManager::get_entity_resource_count() {
	return _entity_resources.size();
}
void EntityDataManager::add_entity_resource(Ref<EntityResourceData> cls) {
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
	if (!_entity_skill_map.has(class_id))
		return Ref<EntitySkillData>(NULL);

	return _entity_skill_map.get(class_id);
}
Ref<EntitySkillData> EntityDataManager::get_entity_skill_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_skills.size(), Ref<EntitySkillData>(NULL));

	return _entity_skills.get(index);
}
int EntityDataManager::get_entity_skill_count() {
	return _entity_skills.size();
}
void EntityDataManager::add_entity_skill(Ref<EntitySkillData> cls) {
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
	if (!_entity_data_map.has(class_id))
		return Ref<EntityData>(NULL);

	return _entity_data_map.get(class_id);
}
Ref<EntityData> EntityDataManager::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}
int EntityDataManager::get_entity_data_count() {
	return _entity_datas.size();
}
void EntityDataManager::add_entity_data(Ref<EntityData> cls) {
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
	ERR_FAIL_COND_V(!_spell_map.has(spell_id), Ref<Spell>(NULL));

	return _spell_map.get(spell_id);
}

Ref<Spell> EntityDataManager::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}

int EntityDataManager::get_spell_count() {
	return _spells.size();
}

void EntityDataManager::add_spell(Ref<Spell> spell) {
	ERR_FAIL_COND(!spell.is_valid());

	_spells.push_back(spell);
	_spell_map.set(spell->get_id(), spell);
}

void EntityDataManager::add_aura(Ref<Aura> aura) {
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
	ERR_FAIL_COND_V(!_aura_map.has(aura_id), Ref<Aura>(NULL));

	return _aura_map.get(aura_id);
}

Ref<Aura> EntityDataManager::get_aura_index(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>(NULL));

	return _auras.get(index);
}

int EntityDataManager::get_aura_count() {
	return _auras.size();
}

//Craft Data
void EntityDataManager::add_craft_data(Ref<CraftRecipe> cda) {
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
	ERR_FAIL_COND_V(!_craft_data_map.has(craft_id), Ref<CraftRecipe>(NULL));

	return _craft_data_map.get(craft_id);
}

Ref<CraftRecipe> EntityDataManager::get_craft_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_datas.size(), Ref<CraftRecipe>(NULL));

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

void EntityDataManager::add_item_template(Ref<ItemTemplate> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_item_templates.push_back(cda);
	_item_template_map.set(cda->get_id(), cda);
}

Ref<ItemTemplate> EntityDataManager::get_item_template(int item_id) {
	ERR_FAIL_COND_V(!_item_template_map.has(item_id), Ref<ItemTemplate>(NULL));

	return _item_template_map.get(item_id);
}

Ref<ItemTemplate> EntityDataManager::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>(NULL));

	return _item_templates.get(index);
}

int EntityDataManager::get_item_template_count() {
	return _item_templates.size();
}

String EntityDataManager::get_mob_data_folder() {
	return _mob_data_folder;
}
void EntityDataManager::set_mob_data_folder(String folder) {
	_mob_data_folder = folder;
}
Vector<Ref<EntityData> > *EntityDataManager::get_mob_datas() {
	return &_mob_datas;
}

void EntityDataManager::add_mob_data(Ref<EntityData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_mob_datas.push_back(cda);
	_mob_data_map.set(cda->get_id(), cda);
}

Ref<EntityData> EntityDataManager::get_mob_data(int item_id) {
	ERR_FAIL_COND_V(!_mob_data_map.has(item_id), Ref<EntityData>(NULL));

	return _mob_data_map.get(item_id);
}

Ref<EntityData> EntityDataManager::get_mob_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _mob_datas.size(), Ref<EntityData>(NULL));

	return _mob_datas.get(index);
}

int EntityDataManager::get_mob_data_count() {
	return _mob_datas.size();
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

void EntityDataManager::add_player_character_data(Ref<EntityData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_player_character_datas.push_back(cda);
	_player_character_data_map.set(cda->get_id(), cda);
}

Ref<EntityData> EntityDataManager::get_player_character_data(int item_id) {
	ERR_FAIL_COND_V(!_player_character_data_map.has(item_id), Ref<EntityData>(NULL));

	return _player_character_data_map.get(item_id);
}

Ref<EntityData> EntityDataManager::get_player_character_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _player_character_datas.size(), Ref<EntityData>(NULL));

	return _player_character_datas.get(index);
}

int EntityDataManager::get_player_character_data_count() {
	return _player_character_datas.size();
}

void EntityDataManager::load_all() {
	load_xp_data();
	load_spells();
	load_auras();
	load_characters();
	load_craft_datas();
	load_item_templates();
	load_mob_datas();
	load_player_character_datas();
}

void EntityDataManager::load_xp_data() {
	_Directory dir;

	ERR_FAIL_COND(_xp_data_path == "");

	_ResourceLoader *rl = _ResourceLoader::get_singleton();

	Ref<ResourceInteractiveLoader> resl = rl->load_interactive(_xp_data_path, "XPData");

	resl->wait();

	Ref<Resource> s = resl->get_resource();

	ERR_FAIL_COND(!s.is_valid());

	Ref<XPData> d = s;

	ERR_FAIL_COND(!d.is_valid());

	_xp_data = d;
}

void EntityDataManager::load_spells() {
	_Directory dir;

	ERR_FAIL_COND(_spells_folder.ends_with("/"));

	if (dir.open(_spells_folder) == OK) {

		dir.list_dir_begin();

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _spells_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "Spell");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<Spell> spell = s;

				ERR_CONTINUE(!spell.is_valid());

				add_spell(spell);
			}

			filename = dir.get_next();
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

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _auras_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "Aura");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<Aura> aura = s;

				ERR_CONTINUE(!aura.is_valid());

				add_aura(aura);
			}

			filename = dir.get_next();
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

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _entity_datas_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "EntityData");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<EntityData> cls = s;

				ERR_CONTINUE(!cls.is_valid());

				add_entity_data(cls);
			}

			filename = dir.get_next();
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

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _craft_data_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "CraftRecipe");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<CraftRecipe> cda = s;

				ERR_CONTINUE(!cda.is_valid());

				add_craft_data(cda);
			}

			filename = dir.get_next();
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

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _item_template_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "ItemTemplate");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<ItemTemplate> it = s;

				ERR_CONTINUE(!it.is_valid());

				add_item_template(it);
			}

			filename = dir.get_next();
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::load_mob_datas() {
	_Directory dir;

	ERR_FAIL_COND(_mob_data_folder.ends_with("/"));

	if (dir.open(_mob_data_folder) == OK) {

		dir.list_dir_begin();

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _mob_data_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "EntityData");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<EntityData> mob_data = s;

				ERR_CONTINUE(!mob_data.is_valid());

				add_mob_data(mob_data);
			}

			filename = dir.get_next();
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

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _player_character_data_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "EntityData");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<EntityData> pcd = s;

				ERR_CONTINUE(!pcd.is_valid());

				add_player_character_data(pcd);
			}

			filename = dir.get_next();
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void EntityDataManager::list_characters() {
	for (int i = 0; i < _entity_datas.size(); ++i) {
		print_error(itos(i) + ": " + _entity_datas.get(i)->get_name());
	}
}

void EntityDataManager::list_spells() {
	for (int i = 0; i < _spells.size(); ++i) {
		print_error(itos(i) + ": " + _spells.get(i)->get_name());
	}
}

void EntityDataManager::list_auras() {
	for (int i = 0; i < _auras.size(); ++i) {
		print_error(itos(i) + ": " + _auras.get(i)->get_name());
	}
}

void EntityDataManager::list_craft_data() {
	for (int i = 0; i < _craft_datas.size(); ++i) {
		print_error(itos(i) + ": " + _craft_datas.get(i)->get_name());
	}
}

void EntityDataManager::list_item_templates() {
	for (int i = 0; i < _item_templates.size(); ++i) {
		print_error(itos(i) + ": " + _item_templates.get(i)->get_name());
	}
}

void EntityDataManager::list_mob_datas() {
	for (int i = 0; i < _mob_datas.size(); ++i) {
		print_error(itos(i) + ": " + _mob_datas.get(i)->get_name());
	}
}

void EntityDataManager::list_player_character_datas() {
	for (int i = 0; i < _player_character_datas.size(); ++i) {
		print_error(itos(i) + ": " + _player_character_datas.get(i)->get_name());
	}
}

void EntityDataManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_skill_for_armor_type", "index"), &EntityDataManager::get_skill_for_armor_type);
	ClassDB::bind_method(D_METHOD("set_skill_for_armor_type", "index", "aura"), &EntityDataManager::set_skill_for_armor_type);

	for (int i = 0; i < ItemEnums::ARMOR_TYPE_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "skill_for_armor_type_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_skill_for_armor_type", "get_skill_for_armor_type", i);
	}

	ClassDB::bind_method(D_METHOD("get_automatic_load"), &EntityDataManager::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &EntityDataManager::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

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

	//Mob Data
	ClassDB::bind_method(D_METHOD("get_mob_data_folder"), &EntityDataManager::get_mob_data_folder);
	ClassDB::bind_method(D_METHOD("set_mob_data_folder", "folder"), &EntityDataManager::set_mob_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "mob_data_folder"), "set_mob_data_folder", "get_mob_data_folder");

	ClassDB::bind_method(D_METHOD("add_mob_data", "mob_data"), &EntityDataManager::add_mob_data);
	ClassDB::bind_method(D_METHOD("get_mob_data", "mob_data_id"), &EntityDataManager::get_mob_data);
	ClassDB::bind_method(D_METHOD("get_mob_data_index", "index"), &EntityDataManager::get_mob_data_index);
	ClassDB::bind_method(D_METHOD("get_mob_data_count"), &EntityDataManager::get_mob_data_count);

	//Player Character Data
	ClassDB::bind_method(D_METHOD("get_player_character_data_folder"), &EntityDataManager::get_player_character_data_folder);
	ClassDB::bind_method(D_METHOD("set_player_character_data_folder", "folder"), &EntityDataManager::set_player_character_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_character_data_folder"), "set_player_character_data_folder", "get_player_character_data_folder");

	ClassDB::bind_method(D_METHOD("add_player_character_data", "pcd"), &EntityDataManager::add_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data", "pcd_id"), &EntityDataManager::get_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data_index", "index"), &EntityDataManager::get_player_character_data_index);
	ClassDB::bind_method(D_METHOD("get_player_character_data_count"), &EntityDataManager::get_player_character_data_count);

	//load
	ClassDB::bind_method(D_METHOD("load_all"), &EntityDataManager::load_all);
	ClassDB::bind_method(D_METHOD("load_xp_data"), &EntityDataManager::load_xp_data);
	ClassDB::bind_method(D_METHOD("load_spells"), &EntityDataManager::load_spells);
	ClassDB::bind_method(D_METHOD("load_auras"), &EntityDataManager::load_auras);
	ClassDB::bind_method(D_METHOD("load_characters"), &EntityDataManager::load_characters);
	ClassDB::bind_method(D_METHOD("load_craft_datas"), &EntityDataManager::load_craft_datas);
	ClassDB::bind_method(D_METHOD("load_item_templates"), &EntityDataManager::load_item_templates);
	ClassDB::bind_method(D_METHOD("load_mob_datas"), &EntityDataManager::load_mob_datas);
	ClassDB::bind_method(D_METHOD("load_player_character_datas"), &EntityDataManager::load_player_character_datas);

	//tests
	ClassDB::bind_method(D_METHOD("list_characters"), &EntityDataManager::list_characters);
	ClassDB::bind_method(D_METHOD("list_spells"), &EntityDataManager::list_spells);
	ClassDB::bind_method(D_METHOD("list_auras"), &EntityDataManager::list_auras);
	ClassDB::bind_method(D_METHOD("list_craft_data"), &EntityDataManager::list_craft_data);
	ClassDB::bind_method(D_METHOD("list_item_templates"), &EntityDataManager::list_item_templates);
	ClassDB::bind_method(D_METHOD("list_mob_datas"), &EntityDataManager::list_mob_datas);
	ClassDB::bind_method(D_METHOD("list_player_character_datas"), &EntityDataManager::list_player_character_datas);
}

EntityDataManager::EntityDataManager() {
	instance = this;

	_automatic_load = true;
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

	_mob_datas.clear();
	_mob_data_map.clear();

	_player_character_datas.clear();
	_player_character_data_map.clear();
}
