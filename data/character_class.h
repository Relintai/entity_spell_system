#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include "core/resource.h"
#include "core/vector.h"
#include "scene/resources/texture.h"

#include "../entities/stats/stat_data.h"
#include "../entity_enums.h"
#include "character_spec.h"

class Aura;
class Spell;
class Entity;
class CharacterSpec;

enum CharacterWeaponDataTypes {
	CHARACTER_WEAPON_DATA_TYPES_NONE,
	CHARACTER_WEAPON_DATA_TYPES_SWORD,
	CHARACTER_WEAPON_DATA_TYPES_BOW
};

VARIANT_ENUM_CAST(CharacterWeaponDataTypes)

class CharacterClass : public Resource {
	GDCLASS(CharacterClass, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_character_class_name();
	void set_character_class_name(String value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	Ref<StatData> get_stat_data();
	void set_stat_data(Ref<StatData> value);

	EntityEnums::PlayerResourceTypes get_player_resource_type();
	void set_player_resource_type(EntityEnums::PlayerResourceTypes value);
	
	int get_num_spells();
	void set_num_spells(int value);

	int get_current_spell_page();
	void set_current_spell_page(int value);

	Ref<Spell> get_spell(int index);
	void set_spell(int index, Ref<Spell> spell);

	int get_num_specs();
	void set_num_specs(int value);

	Ref<CharacterSpec> get_spec(int index) const;
	void set_spec(int index, Ref<CharacterSpec> spec);

	Ref<Aura> get_aura(int index);
	void set_aura(int index, Ref<Aura> aura);

	/*
	Vector<int> get_talent_ids();
	void set_talent_ids(Vector<int> ids);

	Vector<int> get_spec_ids();
	void set_spec_ids(Vector<int> ids);

	Vector<int> get_mob_party_ids();
	void set_mob_party_ids(Vector<int> ids);

	Vector<int> get_mob_dislike_ids();
	void set_mob_dislike_ids(Vector<int> ids);
	*/
	//MobSpellData *getMobSpellData();
	//void setMobSpellData(MobSpellData *value);

	//int get_inspector_max_spells();
	//void set_inspector_max_spells(int value);

	////    Spell System    ////

	void start_casting(int spell_id, Entity *caster, float spellScale);
	void casting_finished(Entity *caster, float spellScale);
	void casting_failed(Entity *caster);
	void spell_hit(Entity *caster, Entity *target, Node *worldSpell, Spell *spell, float spellScale);
	void on_player_move(Entity *caster);
	void c_on_spell_cast_started(Entity *player);
	void c_on_spell_cast_success(Entity *player);
	void c_on_spell_cast_failed(Entity *player);
	void c_on_spell_cast_ended(Entity *player);
	void on_cast_state_changed(Entity *caster);
	String get_name();
	String get_description(int level);

	CharacterClass();
	~CharacterClass();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

public:
	enum {
		MAX_SPELLS = 100,
		MAX_SPECS = 5,
		MAX_AURAS = 5,
		ITEMS_PER_PAGE = 100,
	};

private:
	int _id;
	String _character_class_name;
	Ref<Texture> _icon;

	EntityEnums::PlayerResourceTypes _player_resource_type;

	Ref<StatData> _stat_data;

	int _num_spells;
	int _current_spell_page;
	Ref<Spell> _spells[MAX_SPELLS];

	int _num_specs;
	Ref<CharacterSpec> _specs[MAX_SPECS];

	Ref<Aura> _auras[MAX_AURAS];

	//Vector<int> _mob_party_ids;
	//Vector<int> _mob_dislike_ids;

	//MobSpellData *_mob_spell_data;
};

#endif
