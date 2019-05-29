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
class ItemTemplate;

class DataManager : public Node {
	GDCLASS(DataManager, Node);

public:
	static DataManager *get_instance();

	String get_character_classes_folder();
	void set_character_classes_folder(String folder);
	Vector<Ref<CharacterClass> > *get_character_classes();
	Ref<CharacterClass> get_character_class(int class_id);
	Ref<CharacterClass> get_character_class_index(int index);
	int get_character_class_count();
	void add_character_class(Ref<CharacterClass> cls);

	String get_spells_folder();
	void set_spells_folder(String folder);
	Vector<Ref<Spell> > *get_spells();
	Ref<Spell> get_spell(int spell_id);
	Ref<Spell> get_spell_index(int index);
	int get_spell_count();
	void add_spell(Ref<Spell> spell);

	String get_auras_folder();
	void set_auras_folder(String folder);
	Vector<Ref<Aura> > *get_auras();
	Ref<Aura> get_aura(int aura_id);
	Ref<Aura> get_aura_index(int index);
	int get_aura_count();
	void add_aura(Ref<Aura> aura);

	String get_craft_data_folder();
	void set_craft_data_folder(String folder);
	Vector<Ref<CraftDataAttribute> > *get_craft_datas();
	Ref<CraftDataAttribute> get_craft_data(int craft_id);
	Ref<CraftDataAttribute> get_craft_data_index(int index);
	int get_craft_data_count();
	void add_craft_data(Ref<CraftDataAttribute> aura);

	String get_item_template_folder();
	void set_item_template_folder(String folder);
	Vector<Ref<ItemTemplate> > *get_item_templates();
	void add_item_template(Ref<ItemTemplate> aura);
	Ref<ItemTemplate> get_item_template(int item_id);
	Ref<ItemTemplate> get_item_template_index(int index);
	int get_item_template_count();

	void load_all();
	void load_spells();
	void load_auras();
	void load_characters();
	void load_craft_datas();
	void load_item_templates();

	void list_characters();
	void list_spells();
	void list_auras();
	void list_craft_data();
	void list_item_templates();

	bool get_automatic_load() { return _automatic_load; }
	void set_automatic_load(bool load) { _automatic_load = load; }

	DataManager();
	~DataManager();

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	String _character_classes_folder;
	Vector<Ref<CharacterClass> > _character_classes;
	HashMap<int, Ref<CharacterClass> > _character_class_map;

	String _spells_folder;
	Vector<Ref<Spell> > _spells;
	HashMap<int, Ref<Spell> > _spell_map;

	String _auras_folder;
	Vector<Ref<Aura> > _auras;
	HashMap<int, Ref<Aura> > _aura_map;

	String _craft_data_folder;
	Vector<Ref<CraftDataAttribute> > _craft_datas;
	HashMap<int, Ref<CraftDataAttribute> > _craft_data_map;

	String _item_template_folder;
	Vector<Ref<ItemTemplate> > _item_templates;
	HashMap<int, Ref<ItemTemplate> > _item_template_map;

	static DataManager *instance;

	bool _automatic_load;
};

#endif
