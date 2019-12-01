#ifndef SPELL_H
#define SPELL_H

#include "core/resource.h"
#include "scene/resources/curve.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../spell_enums.h"

#include "../infos/spell_cast_info.h"

#include "../entities/entity.h"

#include "../pipelines/spell_damage_info.h"
#include "../infos/aura_infos.h"

#include "spell_effect_visual.h"
#include "../world_spells/spell_projectile_data.h"
#include "../world_spells/world_effect_data.h"

class Entity;
class Aura;
class SpellCastInfo;
class Spell;
class CraftRecipe;
class EntityResourceCostData;
class EntitySkillData;

enum TargetRelationType {
	TARGET_SELF = 1 << 0,
	TARGET_ENEMY = 1 << 1,
	TARGET_FRIENDLY = 1 << 2
};

VARIANT_ENUM_CAST(TargetRelationType);

enum SpellTargetType {
	SPELL_TARGET_TYPE_SELF,
	SPELL_TARGET_TYPE_TARGET,
	SPELL_TARGET_TYPE_AROUND,
	SPELL_TARGET_TYPE_FRONT,
	SPELL_TARGET_TYPE_AROUND_TARGET
};

VARIANT_ENUM_CAST(SpellTargetType);

enum SpellAOEColliderType {
	SPELL_AOE_COLLIDER_TYPE_SPHERE,
	SPELL_AOE_COLLIDER_TYPE_BOX,
	SPELL_AOE_COLLIDER_TYPE_BOX_NON_UNIFORM
};

VARIANT_ENUM_CAST(SpellAOEColliderType);

enum SpellAOEMovementType {
	SPELL_AOE_MOVEMENT_TYPE_STATIC,
	SPELL_AOE_MOVEMENT_TYPE_MOVING_TO_TARGET,
	SPELL_AOE_MOVEMENT_TYPE_MOVING_RANDOM_DIRECTION,
	SPELL_AOE_MOVEMENT_TYPE_MOVING_RANDOMLY,
	SPELL_AOE_MOVEMENT_TYPE_MOVING_CASTER_FACING,
	SPELL_AOE_MOVEMENT_TYPE_MOVING
};

VARIANT_ENUM_CAST(SpellAOEMovementType);

enum SpellAOETargetType {
	SPELL_AOE_TARGET_TYPE_CASTER,
	SPELL_AOE_TARGET_TYPE_TARGET,
	SPELL_AOE_TARGET_TYPE_GOUND_TARGET_SELECTION,
	SPELL_AOE_TARGET_TYPE_RANDOM
};

VARIANT_ENUM_CAST(SpellAOETargetType);

enum SpellProjectileType {
	SPELL_PROJECTILE_TYPE_FOLLOW,
	SPELL_PROJECTILE_TYPE_STRAIGHT,
	SPELL_PROJECTILE_TYPE_STATIONARY
};

VARIANT_ENUM_CAST(SpellProjectileType);

class Spell : public Resource {
	GDCLASS(Spell, Resource);

public:
	int get_id();
	void set_id(int value);

	int get_spell_type();
	void set_spell_type(int value);

	SpellEnums::SpellCategory get_spell_category();
	void set_spell_category(SpellEnums::SpellCategory value);

	bool get_hide_from_actionbar();
	void set_hide_from_actionbar(bool value);

	float get_cooldown();
	void set_cooldown(float value);

	SpellTargetType get_target_type();
	void set_target_type(SpellTargetType value);

	TargetRelationType get_target_relation_type();
	void set_target_relation_type(TargetRelationType value);

	int get_level();
	void set_level(int value);

	int get_rank();
	void set_rank(int value);

	int get_item_cost();
	void set_item_cost(int value);

	int get_craft_material_cost();
	void set_craft_material_cost(int value);

	int get_required_item();
	void set_required_item(int value);

	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(Ref<EntityResourceCostData> value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(Ref<EntityResourceCostData> value);

	bool has_global_cooldown();
	void set_has_global_cooldown(bool value);

	bool get_is_local_spell();
	void set_is_local_spell(bool value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	String get_text_description();
	void set_text_description(String value);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(Ref<SpellEffectVisual> value);

	Ref<SpellProjectileData> get_spell_projectile_data();
	void set_spell_projectile_data(Ref<SpellProjectileData> value);

	Ref<WorldEffectData> get_world_effect_data();
	void set_world_effect_data(Ref<WorldEffectData> value);

	Ref<CraftRecipe> get_teaches_craft_recipe();
	void set_teaches_craft_recipe(Ref<CraftRecipe> value);

	float get_damage_scale_for_level(int level);
	float get_heal_scale_for_level(int level);
	float get_absorb_scale_for_level(int level);

	//Caster Aura Apply
	int get_num_caster_aura_applys();
	void set_num_caster_aura_applys(int value);

	Ref<Aura> get_caster_aura_apply(int index) const;
	void set_caster_aura_apply(int index, Ref<Aura> caster_aura_apply);

	Vector<Variant> get_caster_aura_applys();
	void set_caster_aura_applys(const Vector<Variant> &caster_aura_applys);

	//Target Aura Apply
	int get_num_target_aura_applys();
	void set_num_target_aura_applys(int value);

	Ref<Aura> get_target_aura_apply(int index) const;
	void set_target_aura_apply(int index, Ref<Aura> target_aura_apply);

	Vector<Variant> get_target_aura_applys();
	void set_target_aura_applys(const Vector<Variant> &target_aura_applys);

	//Apply Auras On Learn
	int get_num_on_learn_auras();
	void set_num_on_learn_auras(int value);

	Ref<Aura> get_on_learn_aura(int index) const;
	void set_on_learn_aura(int index, Ref<Aura> on_learn_aura);

	Vector<Variant> get_on_learn_auras();
	void set_on_learn_auras(const Vector<Variant> &on_learn_auras);

	//Range
	bool get_has_range();
	void set_has_range(bool value);

	float get_range();
	void set_range(float value);

	bool get_has_cast_time();
	void set_has_cast_time(bool value);

	float get_cast_time();
	void set_cast_time(float value);

	bool get_has_damage();
	void set_has_damage(bool value);

	int get_damage_type();
	void set_damage_type(int value);

	int get_damage_min();
	void set_damage_min(int value);

	int get_damage_max();
	void set_damage_max(int value);

	Ref<Curve> get_damage_scaling_curve();
	void set_damage_scaling_curve(Ref<Curve> curve);

	bool get_has_heal();
	void set_has_heal(bool value);

	int get_heal_min();
	void set_heal_min(int value);

	int get_heal_max();
	void set_heal_max(int value);

	Ref<Curve> get_heal_scaling_curve();
	void set_heal_scaling_curve(Ref<Curve> curve);

	bool get_needs_target();
	void set_needs_target(bool value);

	bool get_can_move_while_casting();
	void set_can_move_while_casting(bool value);

	bool get_is_interrupt();
	void set_is_interrupt(bool value);

	float get_interrupt_time();
	void set_interrupt_time(float value);

	bool get_is_aoe();
	void set_is_aoe(bool value);

	SpellAOETargetType get_aoe_target_type();
	void set_aoe_target_type(SpellAOETargetType value);

	SpellAOEMovementType get_aoe_movement_type();
	void set_aoe_movement_type(SpellAOEMovementType value);

	SpellAOEColliderType get_aoe_collider_type();
	void set_aoe_collider_type(SpellAOEColliderType value);

	Vector3 get_aoe_half_extents();
	void set_aoe_half_extents(Vector3 value);

	Ref<PackedScene> get_projectile();
	void set_projectile(Ref<PackedScene> value);

	bool has_projectile();
	float get_projectile_speed();
	void set_projectile_speed(float value);

	float get_projectile_time();
	void set_projectile_time(float value);

	float get_projectile_range();
	void set_projectile_range(float value);

	bool get_has_projectile_collision();
	void set_has_projectile_collision(bool value);

	SpellProjectileType get_projectile_type();
	void set_projectile_type(SpellProjectileType value);

	bool get_has_projectile_destroy_on_impact();
	void set_has_projectile_destroy_on_impact(bool value);

	int get_spell_cooldown_mainpulation_data_count();
	void set_spell_cooldown_mainpulation_data_count(int value);

	int get_training_cost();
	void set_training_cost(int value);

	Ref<Spell> get_training_required_spell();
	void set_training_required_spell(Ref<Spell> spell);

	Ref<EntitySkillData> get_training_required_skill();
	void set_training_required_skill(Ref<EntitySkillData> skill);

	int get_training_required_skill_level();
	void set_training_required_skill_level(int value);

	////    Spell Script    ////

	float PLAYER_HIT_RADIUS;

	//Commands, c++ only
	void sstart_casting_simple(Entity *caster, float spell_scale);
	void sinterrupt_cast_simple(Entity *caster);
	void sstart_casting_triggered_simple(Entity *caster);

	//Commands
	void sstart_casting(Ref<SpellCastInfo> info);
	void sstart_casting_triggered(Ref<SpellCastInfo> info);
	void sinterrupt_cast(Ref<SpellCastInfo> info);
	void sfinish_cast(Ref<SpellCastInfo> info);

	virtual void _sstart_casting(Ref<SpellCastInfo> info);

	//eventhandlers
	void son_cast_player_moved(Ref<SpellCastInfo> info);
	void son_cast_damage_received(Ref<SpellCastInfo> info);
	void son_spell_hit(Ref<SpellCastInfo> info);

	//Clientside Event Handlers
	void con_spell_cast_started(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);
	void con_spell_cast_failed(Ref<SpellCastInfo> info);
	void con_spell_cast_ended(Ref<SpellCastInfo> info);
	void con_spell_cast_interrupted(Ref<SpellCastInfo> info);

	//Calculations / Queries
	void calculate_initial_damage(Ref<SpellDamageInfo> data);
	void handle_spell_damage(Ref<SpellDamageInfo> data);

	virtual void _calculate_initial_damage(Ref<SpellDamageInfo> data);
	virtual void _handle_spell_damage(Ref<SpellDamageInfo> data);

	String get_description(int level);

	Spell();
	~Spell();

protected:
	static void _bind_methods();

private:
	int _id;
	int _spell_type;
	SpellEnums::SpellCategory _spell_category;

	bool _hide_from_actionbar;
	float _cooldown;
	SpellTargetType _target_type;
	TargetRelationType _target_relation_type;

	Vector<Ref<Aura> > _caster_aura_applys;
	Vector<Ref<Aura> > _target_aura_applys;
	Vector<Ref<Aura> > _on_learn_auras;

	int _level;
	int _rank;
	int _item_cost;
	int _craft_material_cost;
	int _required_item;

	Ref<EntityResourceCostData> _resource_cost;
	Ref<EntityResourceCostData> _resource_give;

	bool _has_global_cooldown;
	bool _is_local_spell;
	Ref<Texture> _icon;

	String _text_description;

	Ref<SpellEffectVisual> _visual_spell_effects;
	Ref<SpellProjectileData> _spell_projectile_data;
	Ref<WorldEffectData> _world_effect_data;
	Ref<CraftRecipe> _teaches_craft_recipe;

	bool _has_range;
	float _range;

	bool _has_damage;
	int _damage_type;
	int _damage_min;
	int _damage_max;
	Ref<Curve> _damage_scaling_curve;

	bool _has_heal;
	int _heal_min;
	int _heal_max;
	Ref<Curve> _heal_scaling_curve;

	bool _has_cast_time;
	float _cast_time;

	bool _needs_target;
	bool _can_move_while_casting;

	bool _is_interrupt;
	float _interrupt_time;

	bool _is_aoe;
	SpellAOETargetType _aoe_targetType;
	SpellAOEMovementType _aoe_movementType;
	SpellAOEColliderType _aoe_colliderType;
	Vector3 _aoe_half_extents;

	Ref<PackedScene> _projectile;
	float _projectile_speed;
	float _projectile_time;
	float _projectile_range;
	SpellProjectileType _projectile_type;
	bool _projectile_destroy_on_impact;
	bool _projectile_collision;

	int _spell_cooldown_mainpulation_data_count;

	int _training_cost;
	Ref<Spell> _training_required_spell;
	Ref<EntitySkillData> _training_required_skill;
	int _training_required_skill_level;
};

#endif
