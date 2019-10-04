#include "data_manager.h"

#include "../entities/data/entity_data.h"
#include "aura.h"
#include "craft_data_attribute.h"
#include "spell.h"
#include "talent.h"

DataManager *DataManager::instance;

DataManager *DataManager::get_instance() {
	return instance;
}

void DataManager::_notification(int p_what) {

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

String DataManager::get_xp_data_path() {
	return _xp_data_path;
}
void DataManager::set_xp_data_path(String path) {
	_xp_data_path = path;
}
Ref<XPData> DataManager::get_xp_data() {
	return _xp_data;
}

String DataManager::get_entity_datas_folder() {
	return _entity_datas_folder;
}

void DataManager::set_entity_datas_folder(String folder) {
	_entity_datas_folder = folder;
}

Vector<Ref<EntityData> > *DataManager::get_entity_datas() {
	return &_entity_datas;
}

Ref<EntityData> DataManager::get_entity_data(int class_id) {
	if (!_entity_data_map.has(class_id))
		return Ref<EntityData>(NULL);

	return _entity_data_map.get(class_id);
}

Ref<EntityData> DataManager::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}

int DataManager::get_entity_data_count() {
	return _entity_datas.size();
}

void DataManager::add_entity_data(Ref<EntityData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_datas.push_back(cls);
	_entity_data_map.set(cls->get_id(), cls);
}

String DataManager::get_spells_folder() {
	return _spells_folder;
}
void DataManager::set_spells_folder(String folder) {
	_spells_folder = folder;
}
Vector<Ref<Spell> > *DataManager::get_spells() {
	return &_spells;
}

Ref<Spell> DataManager::get_spell(int spell_id) {
	ERR_FAIL_COND_V(!_spell_map.has(spell_id), Ref<Spell>(NULL));

	return _spell_map.get(spell_id);
}

Ref<Spell> DataManager::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}

int DataManager::get_spell_count() {
	return _spells.size();
}

void DataManager::add_spell(Ref<Spell> spell) {
	ERR_FAIL_COND(!spell.is_valid());

	_spells.push_back(spell);
	_spell_map.set(spell->get_spell_id(), spell);
}

void DataManager::add_aura(Ref<Aura> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_auras.push_back(aura);
	_aura_map.set(aura->get_id(), aura);
}

String DataManager::get_auras_folder() {
	return _auras_folder;
}
void DataManager::set_auras_folder(String folder) {
	_auras_folder = folder;
}
Vector<Ref<Aura> > *DataManager::get_auras() {
	return &_auras;
}

Ref<Aura> DataManager::get_aura(int aura_id) {
	ERR_FAIL_COND_V(!_aura_map.has(aura_id), Ref<Aura>(NULL));

	return _aura_map.get(aura_id);
}

Ref<Aura> DataManager::get_aura_index(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>(NULL));

	return _auras.get(index);
}

int DataManager::get_aura_count() {
	return _auras.size();
}

//Talents
void DataManager::add_talent(Ref<Talent> talent) {
	ERR_FAIL_COND(!talent.is_valid());

	_talents.push_back(talent);
	_talent_map.set(talent->get_id(), talent);
}

String DataManager::get_talents_folder() {
	return _talents_folder;
}
void DataManager::set_talents_folder(String folder) {
	_talents_folder = folder;
}
Vector<Ref<Talent> > *DataManager::get_talents() {
	return &_talents;
}

Ref<Talent> DataManager::get_talent(int talent_id) {
	ERR_FAIL_COND_V(!_talent_map.has(talent_id), Ref<Talent>(NULL));

	return _talent_map.get(talent_id);
}

Ref<Talent> DataManager::get_talent_index(int index) {
	ERR_FAIL_INDEX_V(index, _talents.size(), Ref<Talent>(NULL));

	return _talents.get(index);
}

int DataManager::get_talent_count() {
	return _talents.size();
}

//Craft Data
void DataManager::add_craft_data(Ref<CraftDataAttribute> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_datas.push_back(cda);
	_craft_data_map.set(cda->get_id(), cda);
}

String DataManager::get_craft_data_folder() {
	return _craft_data_folder;
}
void DataManager::set_craft_data_folder(String folder) {
	_craft_data_folder = folder;
}
Vector<Ref<CraftDataAttribute> > *DataManager::get_craft_datas() {
	return &_craft_datas;
}

Ref<CraftDataAttribute> DataManager::get_craft_data(int craft_id) {
	ERR_FAIL_COND_V(!_craft_data_map.has(craft_id), Ref<CraftDataAttribute>(NULL));

	return _craft_data_map.get(craft_id);
}

Ref<CraftDataAttribute> DataManager::get_craft_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_datas.size(), Ref<CraftDataAttribute>(NULL));

	return _craft_datas.get(index);
}

int DataManager::get_craft_data_count() {
	return _craft_datas.size();
}

String DataManager::get_item_template_folder() {
	return _item_template_folder;
}
void DataManager::set_item_template_folder(String folder) {
	_item_template_folder = folder;
}
Vector<Ref<ItemTemplate> > *DataManager::get_item_templates() {
	return &_item_templates;
}

void DataManager::add_item_template(Ref<ItemTemplate> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_item_templates.push_back(cda);
	_item_template_map.set(cda->get_id(), cda);
}

Ref<ItemTemplate> DataManager::get_item_template(int item_id) {
	ERR_FAIL_COND_V(!_item_template_map.has(item_id), Ref<ItemTemplate>(NULL));

	return _item_template_map.get(item_id);
}

Ref<ItemTemplate> DataManager::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>(NULL));

	return _item_templates.get(index);
}

int DataManager::get_item_template_count() {
	return _item_templates.size();
}

String DataManager::get_mob_data_folder() {
	return _mob_data_folder;
}
void DataManager::set_mob_data_folder(String folder) {
	_mob_data_folder = folder;
}
Vector<Ref<EntityData> > *DataManager::get_mob_datas() {
	return &_mob_datas;
}

void DataManager::add_mob_data(Ref<EntityData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_mob_datas.push_back(cda);
	_mob_data_map.set(cda->get_id(), cda);
}

Ref<EntityData> DataManager::get_mob_data(int item_id) {
	ERR_FAIL_COND_V(!_mob_data_map.has(item_id), Ref<EntityData>(NULL));

	return _mob_data_map.get(item_id);
}

Ref<EntityData> DataManager::get_mob_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _mob_datas.size(), Ref<EntityData>(NULL));

	return _mob_datas.get(index);
}

int DataManager::get_mob_data_count() {
	return _mob_datas.size();
}

String DataManager::get_player_character_data_folder() {
	return _player_character_data_folder;
}
void DataManager::set_player_character_data_folder(String folder) {
	_player_character_data_folder = folder;
}
Vector<Ref<EntityData> > *DataManager::get_player_character_datas() {
	return &_player_character_datas;
}

void DataManager::add_player_character_data(Ref<EntityData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_player_character_datas.push_back(cda);
	_player_character_data_map.set(cda->get_id(), cda);
}

Ref<EntityData> DataManager::get_player_character_data(int item_id) {
	ERR_FAIL_COND_V(!_player_character_data_map.has(item_id), Ref<EntityData>(NULL));

	return _player_character_data_map.get(item_id);
}

Ref<EntityData> DataManager::get_player_character_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _player_character_datas.size(), Ref<EntityData>(NULL));

	return _player_character_datas.get(index);
}

int DataManager::get_player_character_data_count() {
	return _player_character_datas.size();
}

void DataManager::load_all() {
	load_xp_data();
	load_spells();
	load_auras();
	load_talents();
	load_characters();
	load_craft_datas();
	load_item_templates();
	load_mob_datas();
	load_player_character_datas();
}

void DataManager::load_xp_data() {
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

void DataManager::load_spells() {
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

void DataManager::load_auras() {
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

void DataManager::load_talents() {
	_Directory dir;

	ERR_FAIL_COND(_talents_folder.ends_with("/"));

	if (dir.open(_talents_folder) == OK) {

		dir.list_dir_begin();

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _talents_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "Aura");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<Talent> talent = s;

				ERR_CONTINUE(!talent.is_valid());

				add_talent(talent);
			}

			filename = dir.get_next();
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void DataManager::load_characters() {
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

void DataManager::load_craft_datas() {
	_Directory dir;

	ERR_FAIL_COND(_craft_data_folder.ends_with("/"));

	if (dir.open(_craft_data_folder) == OK) {

		dir.list_dir_begin();

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _craft_data_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, "CraftDataAttribute");

				resl->wait();

				Ref<Resource> s = resl->get_resource();

				ERR_CONTINUE(!s.is_valid());

				Ref<CraftDataAttribute> cda = s;

				ERR_CONTINUE(!cda.is_valid());

				add_craft_data(cda);
			}

			filename = dir.get_next();
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void DataManager::load_item_templates() {
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

void DataManager::load_mob_datas() {
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

void DataManager::load_player_character_datas() {
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

void DataManager::list_characters() {
	for (int i = 0; i < _entity_datas.size(); ++i) {
		print_error(itos(i) + ": " + _entity_datas.get(i)->get_entity_name());
	}
}

void DataManager::list_spells() {
	for (int i = 0; i < _spells.size(); ++i) {
		print_error(itos(i) + ": " + _spells.get(i)->get_spell_name());
	}
}

void DataManager::list_auras() {
	for (int i = 0; i < _auras.size(); ++i) {
		print_error(itos(i) + ": " + _auras.get(i)->get_aura_name());
	}
}

void DataManager::list_talents() {
	for (int i = 0; i < _talents.size(); ++i) {
		print_error(itos(i) + ": " + _talents.get(i)->get_aura_name());
	}
}

void DataManager::list_craft_data() {
	for (int i = 0; i < _craft_datas.size(); ++i) {
		print_error(itos(i) + ": " + _craft_datas.get(i)->get_name());
	}
}

void DataManager::list_item_templates() {
	for (int i = 0; i < _item_templates.size(); ++i) {
		print_error(itos(i) + ": " + _item_templates.get(i)->get_name());
	}
}

void DataManager::list_mob_datas() {
	for (int i = 0; i < _mob_datas.size(); ++i) {
		print_error(itos(i) + ": " + _mob_datas.get(i)->get_name());
	}
}

void DataManager::list_player_character_datas() {
	for (int i = 0; i < _player_character_datas.size(); ++i) {
		print_error(itos(i) + ": " + _player_character_datas.get(i)->get_name());
	}
}

void DataManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_automatic_load"), &DataManager::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &DataManager::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	//XPData
	ClassDB::bind_method(D_METHOD("get_xp_data_path"), &DataManager::get_xp_data_path);
	ClassDB::bind_method(D_METHOD("set_xp_data_path", "path"), &DataManager::set_xp_data_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp_data_path"), "set_xp_data_path", "get_xp_data_path");

	ClassDB::bind_method(D_METHOD("get_xp_data"), &DataManager::get_xp_data);

	//EntityData
	ClassDB::bind_method(D_METHOD("get_entity_datas_folder"), &DataManager::get_entity_datas_folder);
	ClassDB::bind_method(D_METHOD("set_entity_datas_folder", "folder"), &DataManager::set_entity_datas_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_datas_folder"), "set_entity_datas_folder", "get_entity_datas_folder");

	ClassDB::bind_method(D_METHOD("add_entity_data", "cls"), &DataManager::add_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data", "class_id"), &DataManager::get_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data_index", "index"), &DataManager::get_entity_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_data_count"), &DataManager::get_entity_data_count);

	//Spell
	ClassDB::bind_method(D_METHOD("get_spells_folder"), &DataManager::get_spells_folder);
	ClassDB::bind_method(D_METHOD("set_spells_folder", "folder"), &DataManager::set_spells_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "spells_folder"), "set_spells_folder", "get_spells_folder");

	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &DataManager::add_spell);
	ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &DataManager::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &DataManager::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &DataManager::get_spell_count);

	//Aura
	ClassDB::bind_method(D_METHOD("get_auras_folder"), &DataManager::get_auras_folder);
	ClassDB::bind_method(D_METHOD("set_auras_folder", "folder"), &DataManager::set_auras_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "auras_folder"), "set_auras_folder", "get_auras_folder");

	ClassDB::bind_method(D_METHOD("add_aura", "spell"), &DataManager::add_aura);
	ClassDB::bind_method(D_METHOD("get_aura", "id"), &DataManager::get_aura);
	ClassDB::bind_method(D_METHOD("get_aura_index", "index"), &DataManager::get_aura_index);
	ClassDB::bind_method(D_METHOD("get_aura_count"), &DataManager::get_aura_count);

	//Talent
	ClassDB::bind_method(D_METHOD("get_talents_folder"), &DataManager::get_talents_folder);
	ClassDB::bind_method(D_METHOD("set_talents_folder", "folder"), &DataManager::set_talents_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "talents_folder"), "set_talents_folder", "get_talents_folder");

	ClassDB::bind_method(D_METHOD("add_talent", "spell"), &DataManager::add_talent);
	ClassDB::bind_method(D_METHOD("get_talent", "id"), &DataManager::get_talent);
	ClassDB::bind_method(D_METHOD("get_talent_index", "index"), &DataManager::get_talent_index);
	ClassDB::bind_method(D_METHOD("get_talent_count"), &DataManager::get_talent_count);

	//Craft Data
	ClassDB::bind_method(D_METHOD("get_craft_data_folder"), &DataManager::get_craft_data_folder);
	ClassDB::bind_method(D_METHOD("set_craft_data_folder", "folder"), &DataManager::set_craft_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "craft_data_folder"), "set_craft_data_folder", "get_craft_data_folder");

	ClassDB::bind_method(D_METHOD("add_craft_data", "craft_data"), &DataManager::add_craft_data);
	ClassDB::bind_method(D_METHOD("get_craft_data", "craft_data_id"), &DataManager::get_craft_data);
	ClassDB::bind_method(D_METHOD("get_craft_data_index", "index"), &DataManager::get_craft_data_index);
	ClassDB::bind_method(D_METHOD("get_craft_data_count"), &DataManager::get_craft_data_count);

	//Item Templates
	ClassDB::bind_method(D_METHOD("get_item_template_folder"), &DataManager::get_item_template_folder);
	ClassDB::bind_method(D_METHOD("set_item_template_folder", "folder"), &DataManager::set_item_template_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "item_template_folder"), "set_item_template_folder", "get_item_template_folder");

	ClassDB::bind_method(D_METHOD("add_item_template", "item_template"), &DataManager::add_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template", "item_template_id"), &DataManager::get_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template_index", "index"), &DataManager::get_item_template_index);
	ClassDB::bind_method(D_METHOD("get_item_template_count"), &DataManager::get_item_template_count);

	//Mob Data
	ClassDB::bind_method(D_METHOD("get_mob_data_folder"), &DataManager::get_mob_data_folder);
	ClassDB::bind_method(D_METHOD("set_mob_data_folder", "folder"), &DataManager::set_mob_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "mob_data_folder"), "set_mob_data_folder", "get_mob_data_folder");

	ClassDB::bind_method(D_METHOD("add_mob_data", "mob_data"), &DataManager::add_mob_data);
	ClassDB::bind_method(D_METHOD("get_mob_data", "mob_data_id"), &DataManager::get_mob_data);
	ClassDB::bind_method(D_METHOD("get_mob_data_index", "index"), &DataManager::get_mob_data_index);
	ClassDB::bind_method(D_METHOD("get_mob_data_count"), &DataManager::get_mob_data_count);

	//Player Character Data
	ClassDB::bind_method(D_METHOD("get_player_character_data_folder"), &DataManager::get_player_character_data_folder);
	ClassDB::bind_method(D_METHOD("set_player_character_data_folder", "folder"), &DataManager::set_player_character_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_character_data_folder"), "set_player_character_data_folder", "get_player_character_data_folder");

	ClassDB::bind_method(D_METHOD("add_player_character_data", "pcd"), &DataManager::add_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data", "pcd_id"), &DataManager::get_player_character_data);
	ClassDB::bind_method(D_METHOD("get_player_character_data_index", "index"), &DataManager::get_player_character_data_index);
	ClassDB::bind_method(D_METHOD("get_player_character_data_count"), &DataManager::get_player_character_data_count);

	//load
	ClassDB::bind_method(D_METHOD("load_all"), &DataManager::load_all);
	ClassDB::bind_method(D_METHOD("load_xp_data"), &DataManager::load_xp_data);
	ClassDB::bind_method(D_METHOD("load_spells"), &DataManager::load_spells);
	ClassDB::bind_method(D_METHOD("load_auras"), &DataManager::load_auras);
	ClassDB::bind_method(D_METHOD("load_talents"), &DataManager::load_talents);
	ClassDB::bind_method(D_METHOD("load_characters"), &DataManager::load_characters);
	ClassDB::bind_method(D_METHOD("load_craft_datas"), &DataManager::load_craft_datas);
	ClassDB::bind_method(D_METHOD("load_item_templates"), &DataManager::load_item_templates);
	ClassDB::bind_method(D_METHOD("load_mob_datas"), &DataManager::load_mob_datas);
	ClassDB::bind_method(D_METHOD("load_player_character_datas"), &DataManager::load_player_character_datas);

	//tests
	ClassDB::bind_method(D_METHOD("list_characters"), &DataManager::list_characters);
	ClassDB::bind_method(D_METHOD("list_spells"), &DataManager::list_spells);
	ClassDB::bind_method(D_METHOD("list_auras"), &DataManager::list_auras);
	ClassDB::bind_method(D_METHOD("list_talents"), &DataManager::list_talents);
	ClassDB::bind_method(D_METHOD("list_craft_data"), &DataManager::list_craft_data);
	ClassDB::bind_method(D_METHOD("list_item_templates"), &DataManager::list_item_templates);
	ClassDB::bind_method(D_METHOD("list_mob_datas"), &DataManager::list_mob_datas);
	ClassDB::bind_method(D_METHOD("list_player_character_datas"), &DataManager::list_player_character_datas);
}

DataManager::DataManager() {
	instance = this;

	_automatic_load = true;
}

DataManager::~DataManager() {
	instance = NULL;

	_entity_datas.clear();
	_entity_data_map.clear();

	_spells.clear();
	_spell_map.clear();

	_auras.clear();
	_aura_map.clear();

	_talents.clear();
	_talent_map.clear();

	_craft_datas.clear();
	_craft_data_map.clear();

	_item_templates.clear();
	_item_template_map.clear();

	_mob_datas.clear();
	_mob_data_map.clear();

	_player_character_datas.clear();
	_player_character_data_map.clear();
}
