#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "core/array.h"
#include "core/hash_map.h"
#include "core/io/json.h"
#include "core/variant.h"
#include "core/vector.h"

#include "core/resource.h"
#include "core/ustring.h"
#include "scene/main/node.h"

#include "core/bind/core_bind.h"

class Aura;
class Spell;
class CharacterClass;
class CraftDataAttribute;

typedef HashMap<int, Ref<CharacterClass> > CharacterClassHashMap;
typedef HashMap<int, Ref<Spell> > SpellHashMap;
typedef HashMap<int, Ref<Aura> > AuraHashMap;
typedef HashMap<int, Ref<CraftDataAttribute> > CraftDataHashMap;
//typedef HashMap<int, Ref<SpellScript> > SpellScriptHashMap;

class DataManager : public Node {
	GDCLASS(DataManager, Node);

public:
	static DataManager *get_instance();

	String get_character_classes_folder() { return _character_classes_folder; }
	void set_character_classes_folder(String folder) { _character_classes_folder = folder; }
	Vector<Ref<CharacterClass> > *get_character_classes() { return _character_classes; }
	Ref<CharacterClass> get_character_class(int id);
	void add_character_class(Ref<CharacterClass> cls);

	String get_spells_folder() { return _spells_folder; }
	void set_spells_folder(String folder) { _spells_folder = folder; }
	Vector<Ref<Spell> > *get_spells() { return _spells; }
	Ref<Spell> get_spell(int id);
	void add_spell(Ref<Spell> spell);

	String get_auras_folder() { return _auras_folder; }
	void set_auras_folder(String folder) { _auras_folder = folder; }
	Vector<Ref<Aura> > *get_auras() { return _auras; }
	Ref<Aura> get_aura(int id);
	void add_aura(Ref<Aura> aura);

	String get_craft_data_folder() { return _craft_data_folder; }
	void set_craft_data_folder(String folder) { _craft_data_folder = folder; }
	Vector<Ref<CraftDataAttribute> > *get_craft_datas() { return _craft_datas; }
	Ref<CraftDataAttribute> get_craft_data(int id);
	void add_craft_data(Ref<CraftDataAttribute> aura);
	/*
	Vector<Ref<SpellScript> > *get_spell_scripts() { return _spell_scripts; }
	Ref<SpellScript> get_spell_script(int id);
	void add_spell_script(int id, Ref<SpellScript> script);*/

	void load_all();
	//void load_spell_scripts();
	void load_spells();
	void load_auras();
	void load_characters();
	void load_craft_datas();

	void list_characters();
	void list_spells();
	void list_auras();
	void list_craft_data();

	bool get_automatic_load() { return _automatic_load; }
	void set_automatic_load(bool load) { _automatic_load = load; }

	DataManager();
	~DataManager();

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	String _character_classes_folder;
	Vector<Ref<CharacterClass> > *_character_classes;
	CharacterClassHashMap *_character_class_map;

	String _spells_folder;
	Vector<Ref<Spell> > *_spells;
	SpellHashMap *_spell_map;

	String _auras_folder;
	Vector<Ref<Aura> > *_auras;
	AuraHashMap *_aura_map;

	String _craft_data_folder;
	Vector<Ref<CraftDataAttribute> > *_craft_datas;
	CraftDataHashMap *_craft_data_map;

	/*
	Vector<Ref<SpellScript> > *_spell_scripts;
	SpellScriptHashMap *_spell_script_map;*/

	static DataManager *instance;

	bool _automatic_load;
};

#endif
