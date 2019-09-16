#ifndef ENTITY_CLASS_DATA_H
#define ENTITY_CLASS_DATA_H

#include "core/resource.h"
#include "core/vector.h"
#include "core/ustring.h"
#include "scene/resources/texture.h"

#include "../../entities/stats/stat_data.h"
#include "../../entity_enums.h"

#include "../../entities/auras/aura_data.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../utility/cooldown.h"
#include "../../utility/category_cooldown.h"

class Aura;
class Spell;
class Entity;
class CharacterSpec;
class Entity;
class SpellCastInfo;
class AIAction;

enum CharacterWeaponDataTypes {
	CHARACTER_WEAPON_DATA_TYPES_NONE,
	CHARACTER_WEAPON_DATA_TYPES_SWORD,
	CHARACTER_WEAPON_DATA_TYPES_BOW
};

VARIANT_ENUM_CAST(CharacterWeaponDataTypes)

class EntityClassData : public Resource {
	GDCLASS(EntityClassData, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_entity_class_name();
	void set_entity_class_name(String value);

	Ref<EntityClassData> get_inherits();
	void set_inherits(Ref<EntityClassData> value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	Ref<StatData> get_stat_data();
	void set_stat_data(Ref<StatData> value);

	int get_player_resource_type();
	void set_player_resource_type(int value);

	int get_stat_points_per_level();
	void set_stat_points_per_level(int value);

    //Specs
	int get_num_specs();
	void set_num_specs(int value);

	Ref<CharacterSpec> get_spec(int index) const;
	void set_spec(int index, Ref<CharacterSpec> spec);

	Vector<Variant> get_specs();
	void set_specs(const Vector<Variant> &specs);

    //Spells
	int get_num_spells();
	void set_num_spells(int value);

	Ref<Spell> get_spell(int index);
	void set_spell(int index, Ref<Spell> spell);

	Vector<Variant> get_spells();
	void set_spells(const Vector<Variant> &spells);
    
    //Auras
	int get_num_auras();
	void set_num_auras(int value);

	Ref<Aura> get_aura(int index);
	void set_aura(int index, Ref<Aura> aura);

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	//AI Actions
	int get_num_ai_actions();
	void set_num_ai_actions(int value);

	Ref<AIAction> get_ai_action(int index);
	void set_ai_action(int index, Ref<AIAction> aura);

	Vector<Variant> get_ai_actions();
	void set_ai_actions(const Vector<Variant> &ai_actions);
    
	//Setup
	void setup_resources(Entity *entity);
	//void _setup_resources(Entity *entity);

	////    Spell System    ////

	void start_casting(int spell_id, Entity *caster, float spellScale);

    void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<SpellCastInfo> info);
	void son_cast_started(Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<SpellCastInfo> info);
    
    void son_before_damage_hit(Ref<SpellDamageInfo> data);
	void son_hit(Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<SpellDamageInfo> data);

    void son_before_heal_hit(Ref<SpellHealInfo> data);
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
	
	void son_gcd_started(Entity *entity, float gcd);
	void son_gcd_finished(Entity *entity);
	void son_gcd_started_bind(Node *entity, float gcd);
	void son_gcd_finished_bind(Node *entity);

	void son_xp_gained(Entity *entity, int value);
	void son_xp_gained_bind(Node *entity, int value);
	void son_level_up(Entity *entity, int value);
	void son_level_up_bind(Node *entity, int value);

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
	
	void con_gcd_started(Entity *entity, float gcd);
	void con_gcd_finished(Entity *entity);
	void con_gcd_started_bind(Node *entity, float gcd);
	void con_gcd_finished_bind(Node *entity);

	void con_xp_gained(Entity *entity, int value);
	void con_xp_gained_bind(Node *entity, int value);
	void con_level_up(Entity *entity, int value);
	void con_level_up_bind(Node *entity, int value);

    //    AI    //
	void sai_follow(Entity *entity);
	void sai_rest(Entity *entity);
	void sai_regenerate(Entity *entity);
	void sai_attack(Entity *entity);

	void sai_follow_bind(Node *entity);
	void sai_rest_bind(Node *entity);
	void sai_regenerate_bind(Node *entity);
	void sai_attack_bind(Node *entity);

	EntityClassData();
	~EntityClassData();

protected:
	static void _bind_methods();

private:
	int _id;

	String _entity_class_name;

	Ref<EntityClassData> _inherits;

	Ref<Texture> _icon;

	int _player_resource_type;

	int _stat_points_per_level;

	Ref<StatData> _stat_data;

	Vector<Ref<Spell> > _spells;
	Vector<Ref<CharacterSpec> > _specs;
	Vector<Ref<Aura> > _auras;
	Vector<Ref<AIAction> > _ai_actions;
};

#endif
