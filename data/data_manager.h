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
class Talent;
class EntityData;
class CraftDataAttribute;
class ItemTemplate;
class MobData;
class PlayerCharacterData;

class DataManager : public Node {
	GDCLASS(DataManager, Node);

public:
	static DataManager *get_instance();

	String get_entity_dataes_folder();
	void set_entity_dataes_folder(String folder);
	Vector<Ref<EntityData> > *get_entity_dataes();
	Ref<EntityData> get_entity_data(int class_id);
	Ref<EntityData> get_entity_data_index(int index);
	int get_entity_data_count();
	void add_entity_data(Ref<EntityData> cls);

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

	String get_talents_folder();
	void set_talents_folder(String folder);
	Vector<Ref<Talent> > *get_talents();
	Ref<Talent> get_talent(int talent_id);
	Ref<Talent> get_talent_index(int index);
	int get_talent_count();
	void add_talent(Ref<Talent> talent);

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
    
    String get_mob_data_folder();
	void set_mob_data_folder(String folder);
	Vector<Ref<MobData> > *get_mob_datas();
	void add_mob_data(Ref<MobData> aura);
	Ref<MobData> get_mob_data(int item_id);
	Ref<MobData> get_mob_data_index(int index);
	int get_mob_data_count();
    
    String get_player_character_data_folder();
	void set_player_character_data_folder(String folder);
	Vector<Ref<PlayerCharacterData> > *get_player_character_datas();
	void add_player_character_data(Ref<PlayerCharacterData> aura);
	Ref<PlayerCharacterData> get_player_character_data(int item_id);
	Ref<PlayerCharacterData> get_player_character_data_index(int index);
	int get_player_character_data_count();

	void load_all();
	void load_spells();
	void load_auras();
	void load_talents();
	void load_characters();
	void load_craft_datas();
	void load_item_templates();
    void load_mob_datas();
    void load_player_character_datas();
    
	void list_characters();
	void list_spells();
	void list_auras();
	void list_talents();
	void list_craft_data();
	void list_item_templates();
    void list_mob_datas();
    void list_player_character_datas();

	bool get_automatic_load() { return _automatic_load; }
	void set_automatic_load(bool load) { _automatic_load = load; }

	DataManager();
	~DataManager();

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	String _entity_dataes_folder;
	Vector<Ref<EntityData> > _entity_dataes;
	HashMap<int, Ref<EntityData> > _entity_data_map;

	String _spells_folder;
	Vector<Ref<Spell> > _spells;
	HashMap<int, Ref<Spell> > _spell_map;

	String _auras_folder;
	Vector<Ref<Aura> > _auras;
	HashMap<int, Ref<Aura> > _aura_map;

	String _talents_folder;
	Vector<Ref<Talent> > _talents;
	HashMap<int, Ref<Talent> > _talent_map;

	String _craft_data_folder;
	Vector<Ref<CraftDataAttribute> > _craft_datas;
	HashMap<int, Ref<CraftDataAttribute> > _craft_data_map;

	String _item_template_folder;
	Vector<Ref<ItemTemplate> > _item_templates;
	HashMap<int, Ref<ItemTemplate> > _item_template_map;
    
    String _mob_data_folder;
	Vector<Ref<MobData> > _mob_datas;
	HashMap<int, Ref<MobData> > _mob_data_map;
    
    String _player_character_data_folder;
	Vector<Ref<PlayerCharacterData> > _player_character_datas;
	HashMap<int, Ref<PlayerCharacterData> > _player_character_data_map;

	static DataManager *instance;

	bool _automatic_load;
};

#endif
