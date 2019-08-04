#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include "core/resource.h"
#include "core/vector.h"
#include "scene/resources/texture.h"

#include "../entities/stats/stat_data.h"
#include "../entity_enums.h"
#include "character_spec.h"

#include "../entities/auras/aura_data.h"
#include "../pipelines/spell_damage_info.h"
#include "../pipelines/spell_heal_info.h"
#include "../infos/spell_cast_info.h"

#include "../utility/cooldown.h"
#include "../utility/category_cooldown.h"

class Aura;
class Spell;
class Entity;
class CharacterSpec;
class Entity;

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

    void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<SpellCastInfo> info);
	void son_cast_started(Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<SpellCastInfo> info);
    
	void son_hit(Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<SpellDamageInfo> data);

	void son_before_heal(Ref<SpellHealInfo> data);
	void son_heal_receive(Ref<SpellHealInfo> data);
	void son_dealt_heal(Ref<SpellHealInfo> data);
	void son_heal_dealt(Ref<SpellHealInfo> data);

    void son_before_aura_applied(Ref<AuraData> data);
	void son_after_aura_applied(Ref<AuraData> data);
    
    void son_death(Entity *entity);
    void son_death_bind(Node *entity);
    
	void son_cooldown_added(Ref<Cooldown> cooldown);
	void son_cooldown_removed(Ref<Cooldown> cooldown);
	
	void son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);
	
    //Clientside Event Handlers
	void con_cast_failed(Ref<SpellCastInfo> info);
	void con_cast_started(Ref<SpellCastInfo> info);
	void con_cast_state_changed(Ref<SpellCastInfo> info);
	void con_cast_finished(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);
	
	void con_death(Entity *entity);
    void con_death_bind(Node *entity);
	
	void con_cooldown_added(Ref<Cooldown> cooldown);
	void con_cooldown_removed(Ref<Cooldown> cooldown);
	void con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);
	
	void con_aura_added(Ref<AuraData> data);
	void con_aura_removed(Ref<AuraData> data);
	void con_aura_refresh(Ref<AuraData> data);
	
	void con_damage_dealt(Ref<SpellDamageInfo> info);
	void con_dealt_damage(Ref<SpellDamageInfo> info);
	void con_heal_dealt(Ref<SpellHealInfo> info);
	void con_dealt_heal(Ref<SpellHealInfo> info);
    
    //    AI    //
	void sai_follow(Entity *entity);
	void sai_rest(Entity *entity);
	void sai_regenerate(Entity *entity);
	void sai_attack(Entity *entity);

	void sai_follow_bind(Node *entity);
	void sai_rest_bind(Node *entity);
	void sai_regenerate_bind(Node *entity);
	void sai_attack_bind(Node *entity);

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
