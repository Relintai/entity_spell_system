#include "data_manager.h"

#include "spell.h"
#include "aura.h"
#include "character.h"
#include "craft_data_attribute.h"

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
    }
    break;
    case NOTIFICATION_EXIT_TREE: {

    } break;
    }
}

Ref<CharacterClass> DataManager::get_character_class(int class_id) {
	ERR_FAIL_COND_V(!_character_class_map->has(class_id), Ref<CharacterClass>(NULL));

    return _character_class_map->get(class_id);
}

Ref<CharacterClass> DataManager::get_character_class_index(int index) {
	ERR_FAIL_INDEX_V(index, _character_classes->size(), Ref<CharacterClass>(NULL));

	return _character_classes->get(index);
}

int DataManager::get_character_class_count() {
	return _character_classes->size();
}

void DataManager::add_character_class(Ref<CharacterClass> cls) {
	ERR_FAIL_COND(!cls.is_valid());

    _character_classes->push_back(cls);
	_character_class_map->set(cls->get_id(), cls);
}

Ref<Spell> DataManager::get_spell(int spell_id) {
	ERR_FAIL_COND_V(!_spell_map->has(spell_id), Ref<Spell>(NULL));

    return _spell_map->get(spell_id);
}

Ref<Spell> DataManager::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells->size(), Ref<Spell>(NULL));

	return _spells->get(index);
}

int DataManager::get_spell_count() {
	return _spells->size();
}

void DataManager::add_spell(Ref<Spell> spell) {
	ERR_FAIL_COND(!spell.is_valid());

    _spells->push_back(spell);
    _spell_map->set(spell->get_spell_id(), spell);
}

void DataManager::add_aura(Ref<Aura> aura) {
	ERR_FAIL_COND(!aura.is_valid());

    _auras->push_back(aura);
	_aura_map->set(aura->get_id(), aura);
}

Ref<Aura> DataManager::get_aura(int aura_id) {
	ERR_FAIL_COND_V(!_aura_map->has(aura_id), Ref<Aura>(NULL));

	return _aura_map->get(aura_id);
}

Ref<Aura> DataManager::get_aura_index(int index) {
	ERR_FAIL_INDEX_V(index, _auras->size(), Ref<Aura>(NULL));

	return _auras->get(index);
}

int DataManager::get_aura_count() {
	return _auras->size();
}

void DataManager::add_craft_data(Ref<CraftDataAttribute> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_datas->push_back(cda);
	_craft_data_map->set(cda->get_id(), cda);
}

Ref<CraftDataAttribute> DataManager::get_craft_data(int craft_id) {
	ERR_FAIL_COND_V(!_craft_data_map->has(craft_id), Ref<CraftDataAttribute>(NULL));

	return _craft_data_map->get(craft_id);
}

Ref<CraftDataAttribute> DataManager::get_craft_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_datas->size(), Ref<CraftDataAttribute>(NULL));

	return _craft_datas->get(index);
}

int DataManager::get_craft_data_count() {
	return _craft_datas->size();
}


void DataManager::load_all() {
    load_spells();
    load_auras();
    load_characters();
}

void DataManager::load_spells() {
    _Directory dir;

    if (dir.open(_spells_folder) == OK) {

        dir.list_dir_begin();

        String filename = dir.get_next();

        while (filename != "") {
            if (!dir.current_is_dir()) {
                String path = _spells_folder + "/" + filename;

                _ResourceLoader *rl = _ResourceLoader::get_singleton();

                Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path);

                resl->wait();

                Ref<Resource> s = resl->get_resource();
                Resource *r = (*s);

                Spell *sp = cast_to<Spell>(r);

                Ref<Spell> spell = Ref<Spell>(sp);

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

    if (dir.open(_auras_folder) == OK) {

        dir.list_dir_begin();

        String filename = dir.get_next();

        while (filename != "") {
            if (!dir.current_is_dir()) {
                String path = _auras_folder + "/" + filename;

                _ResourceLoader *rl = _ResourceLoader::get_singleton();

                Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path);

                resl->wait();

                Ref<Resource> s = resl->get_resource();
                Resource *r = (*s);

                Aura *a = cast_to<Aura>(r);

                Ref<Aura> aura = Ref<Aura>(a);

                add_aura(aura);
            }

            filename = dir.get_next();
        }
    } else {
        print_error("An error occurred when trying to access the path.");
    }
}

void DataManager::load_characters() {
    _Directory dir;

    if (dir.open(_character_classes_folder) == OK) {

        dir.list_dir_begin();

        String filename = dir.get_next();

        while (filename != "") {
            if (!dir.current_is_dir()) {
                String path = _character_classes_folder + "/" + filename;

                _ResourceLoader *rl = _ResourceLoader::get_singleton();

                Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path);

                resl->wait();

                Ref<Resource> s = resl->get_resource();
                Resource *r = (*s);

                CharacterClass *cc = cast_to<CharacterClass>(r);

                Ref<CharacterClass> cls = Ref<CharacterClass>(cc);

                add_character_class(cls);
            }

            filename = dir.get_next();
        }
    } else {
        print_error("An error occurred when trying to access the path.");
    }
}

void DataManager::load_craft_datas() {
	_Directory dir;

	if (dir.open(_craft_data_folder) == OK) {

		dir.list_dir_begin();

		String filename = dir.get_next();

		while (filename != "") {
			if (!dir.current_is_dir()) {
				String path = _craft_data_folder + "/" + filename;

				_ResourceLoader *rl = _ResourceLoader::get_singleton();

				Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path);

				resl->wait();

				Ref<Resource> s = resl->get_resource();
				Resource *r = (*s);

				CraftDataAttribute *cc = cast_to<CraftDataAttribute>(r);

				Ref<CraftDataAttribute> cls = Ref<CraftDataAttribute>(cc);

				add_character_class(cls);
			}

			filename = dir.get_next();
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void DataManager::list_characters() {
    for (int i = 0; i < _character_classes->size(); ++i) {
        print_error(itos(i) + ": " + _character_classes->get(i)->get_character_class_name());
    }
}

void DataManager::list_spells() {
    for (int i = 0; i < _spells->size(); ++i) {
        print_error(itos(i) + ": " + _spells->get(i)->get_spell_name());
    }
}

void DataManager::list_auras() {
    for (int i = 0; i < _auras->size(); ++i) {
        print_error(itos(i) + ": " + _auras->get(i)->get_aura_name());
    }
}

void DataManager::list_craft_data() {
	for (int i = 0; i < _craft_datas->size(); ++i) {
		print_error(itos(i) + ": " + _craft_datas->get(i)->get_name());
	}
}

void DataManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_automatic_load"), &DataManager::get_automatic_load);
    ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &DataManager::set_automatic_load);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

    ClassDB::bind_method(D_METHOD("load_all"), &DataManager::load_all);
    ClassDB::bind_method(D_METHOD("load_spells"), &DataManager::load_spells);
    ClassDB::bind_method(D_METHOD("load_characters"), &DataManager::load_characters);
	ClassDB::bind_method(D_METHOD("load_craft_datas"), &DataManager::load_craft_datas);

    ClassDB::bind_method(D_METHOD("add_character_class", "cls"), &DataManager::add_character_class);
    ClassDB::bind_method(D_METHOD("add_spell", "spell"), &DataManager::add_spell);
    ClassDB::bind_method(D_METHOD("add_aura", "spell"), &DataManager::add_aura);
	ClassDB::bind_method(D_METHOD("add_craft_data", "craft_data"), &DataManager::add_craft_data);

    //CharacterClass
    ClassDB::bind_method(D_METHOD("get_character_classes_folder"), &DataManager::get_character_classes_folder);
    ClassDB::bind_method(D_METHOD("set_character_classes_folder", "folder"), &DataManager::set_character_classes_folder);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "character_classes_folder"), "set_character_classes_folder", "get_character_classes_folder");

    //ClassDB::bind_method(D_METHOD("get_character_classes"), &DataManager::get_character_classes);
    ClassDB::bind_method(D_METHOD("get_character_class", "class_id"), &DataManager::get_character_class);
	ClassDB::bind_method(D_METHOD("get_character_class_index", "index"), &DataManager::get_character_class_index);
	ClassDB::bind_method(D_METHOD("get_character_class_count"), &DataManager::get_character_class_count);

    //Spell
    ClassDB::bind_method(D_METHOD("get_spells_folder"), &DataManager::get_spells_folder);
    ClassDB::bind_method(D_METHOD("set_spells_folder", "folder"), &DataManager::set_spells_folder);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "spells_folder"), "set_spells_folder", "get_spells_folder");

    //ClassDB::bind_method(D_METHOD("get_spells"), &DataManager::get_spells);
    ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &DataManager::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &DataManager::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &DataManager::get_spell_count);

    //Aura
    ClassDB::bind_method(D_METHOD("get_auras_folder"), &DataManager::get_auras_folder);
    ClassDB::bind_method(D_METHOD("set_auras_folder", "folder"), &DataManager::set_auras_folder);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "auras_folder"), "set_auras_folder", "get_auras_folder");

	ClassDB::bind_method(D_METHOD("get_aura", "id"), &DataManager::get_aura);
	ClassDB::bind_method(D_METHOD("get_aura_index", "index"), &DataManager::get_aura_index);
	ClassDB::bind_method(D_METHOD("get_aura_count"), &DataManager::get_aura_count);

	//Craft Data
	ClassDB::bind_method(D_METHOD("get_craft_data_folder"), &DataManager::get_craft_data_folder);
	ClassDB::bind_method(D_METHOD("set_craft_data_folder", "folder"), &DataManager::set_craft_data_folder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "craft_data_folder"), "set_craft_data_folder", "get_craft_data_folder");

	ClassDB::bind_method(D_METHOD("get_craft_data", "id"), &DataManager::get_craft_data);
	ClassDB::bind_method(D_METHOD("get_craft_data_index", "craft_id"), &DataManager::get_craft_data_index);
	ClassDB::bind_method(D_METHOD("get_craft_data_count"), &DataManager::get_craft_data_count);

    //tests
    ClassDB::bind_method(D_METHOD("list_spells"), &DataManager::list_spells);
    ClassDB::bind_method(D_METHOD("list_characters"), &DataManager::list_characters);
    ClassDB::bind_method(D_METHOD("list_auras"), &DataManager::list_auras);
	ClassDB::bind_method(D_METHOD("list_craft_data"), &DataManager::list_craft_data);
}

DataManager::DataManager() {
    instance = this;

    _character_classes = memnew(Vector<Ref<CharacterClass> >());
    _character_class_map = memnew(CharacterClassHashMap());

    _spells = memnew(Vector<Ref<Spell> >());
    _spell_map = memnew(SpellHashMap());

    _auras = memnew(Vector<Ref<Aura> >());
    _aura_map = memnew(AuraHashMap());

    _craft_datas = memnew(Vector<Ref<CraftDataAttribute> >());
	_craft_data_map = memnew(CraftDataHashMap());

    _automatic_load = true;
}

DataManager::~DataManager() {
    instance = NULL;

    _character_classes->clear();
    _character_class_map->clear();
    _spells->clear();
    _spell_map->clear();
    _auras->clear();
    _aura_map->clear();
	_craft_datas->clear();
	_craft_data_map->clear();
    //_spell_scripts->clear();
    //_spell_script_map->clear();

    memdelete(_character_classes);
    memdelete(_character_class_map);

    memdelete(_spells);
    memdelete(_spell_map);

    memdelete(_auras);
    memdelete(_aura_map);

    memdelete(_craft_datas);
	memdelete(_craft_data_map);
}
