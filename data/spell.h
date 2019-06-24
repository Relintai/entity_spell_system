#ifndef SPELL_H
#define SPELL_H

#include "core/resource.h"
#include "scene/resources/curve.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../spell_enums.h"

#include "../spells/spell_cast_info.h"

#include "../entities/entity.h"

#include "../pipelines/spell_damage_info.h"
#include "../spells/aura_infos.h"

class Entity;
class Aura;
class SpellCastInfo;
class Spell;

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
	int get_spell_id();
	void set_spell_id(int value);

	int get_spell_type();
	void set_spell_type(int value);

	bool get_hide_from_actionbar();
	void set_hide_from_actionbar(bool value);

	float get_cooldown();
	void set_cooldown(float value);

	SpellTargetType get_target_type();
	void set_target_type(SpellTargetType value);

	TargetRelationType get_target_relation_type();
	void set_target_relation_type(TargetRelationType value);

	Ref<Aura> get_caster_aura_apply();
	void set_caster_aura_apply(Ref<Aura> value);

	Ref<Aura> get_caster_aura_apply2();
	void set_caster_aura_apply2(Ref<Aura> value);

	Ref<Aura> get_target_aura_apply();
	void set_target_aura_apply(Ref<Aura> value);

	Ref<Aura> get_target_aura_apply2();
	void set_target_aura_apply2(Ref<Aura> value);

	int get_level();
	void set_level(int value);

	int get_rank();
	void set_rank(int value);

	Ref<Spell> get_next_rank();
	void set_next_rank(Ref<Spell> value);

	int get_item_cost();
	void set_item_cost(int value);

	int get_craft_material_cost();
	void set_craft_material_cost(int value);

	int get_required_item();
	void set_required_item(int value);

	EntityEnums::PlayerResourceTypes get_cost_type();
	void set_cost_type(EntityEnums::PlayerResourceTypes value);

	int get_cost_resource();
	void set_cost_resource(int value);

	EntityEnums::PlayerResourceTypes get_give_resource_type();
	void set_give_resource_type(EntityEnums::PlayerResourceTypes value);

	int get_give_resource();
	void set_give_resource(int value);

	bool has_global_cooldown();
	void set_has_global_cooldown(bool value);

	bool get_is_local_spell();
	void set_is_local_spell(bool value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	String get_name_key();
	void set_name_key(String value);

	String get_spell_name();
	void set_spell_name(String value);

	String get_spell_description();
	void set_spell_description(String value);

	float get_damage_scale_for_level(int level);
	float get_heal_scale_for_level(int level);
	float get_absorb_scale_for_level(int level);

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

	bool has_effect_visual();

	EntityEnums::CharacterSkeletonPoints get_effect_visual_point();
	void set_effect_visual_point(EntityEnums::CharacterSkeletonPoints point);

	Ref<PackedScene> get_effect_visual();
	void set_effect_visual(Ref<PackedScene> value);

	bool has_spell_cast_finish_effect();

	EntityEnums::CharacterSkeletonPoints get_spell_cast_finish_effect_point();
	void set_spell_cast_finish_effect_point(EntityEnums::CharacterSkeletonPoints point);

	Ref<PackedScene> get_spell_cast_finish_effect();
	void set_spell_cast_finish_effect(Ref<PackedScene> value);

	bool has_spell_cast_effect();
	Ref<PackedScene> get_spell_cast_effect();
	void set_spell_cast_effect(Ref<PackedScene> value);

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

	String get_name();
	String get_description(int level);

	/*
	void TriggerGlobalCooldown(Entity *player);
	bool IsCasting(Entity *player);
	bool HasClobalCooldown(Entity *player);
	bool IsStunned(Entity *player);
	bool HasState(StateData::StateType state, Entity *player);
	int GetId(Entity *spell);
	bool IsSpellOnCooldown(int spellId, Entity *player);
	void ApplyAura(int auraId, Entity *caster, float spellScale);
	void ApplyAura(int auraId, Entity *caster, Entity *target, float spellScale);
	void RemoveAura(int auraId, Entity *caster);
	void AddCooldown(Entity *player, int spellId, float cooldown);
	void DoStartCasting(Entity *player, int spellId, String spellName, float castTime, bool addMoveHook, float spellScale);
	void DoCastFail(Entity *player, bool removeHook);
	void AddOnMoveHook(Entity *player);
	void RemoveOnMoveHook(Entity *player);
	Entity *GetTarget(Entity *player);
	void DealDamage(Entity *caster, Entity *target, int damage);
	void DealDamage(Entity *caster, Entity *target, float spellScale);
	void VashDealDamage(Entity *caster, Entity *target, bool increased, float spellScale);
	void Heal(Entity *caster, Entity *target, float spellScale);
	void Heal(Entity *caster, Entity *target, int heal);
	bool checkParry(Entity *caster, Entity *target);


	Node *OldLaunchFollowProjectile(Node *effect, Entity *caster, Entity *target, float speed, float spellScale, float time = (float)0);
	Node *OldLaunchStraightProjectile(Node *effect, Entity *caster, float speed, float time, float range, float spellScale);
	Node *OldLaunchProjectile(Entity *caster, Entity *target, float spellScale);
	WorldSpell *SpawnProjectile(Entity *caster, Entity *target, float spellScale);
	bool isInRange(Entity *target, Entity *player);
	bool CanCast(Entity *caster, int skipCheck = 0);
	bool CanCastTarget(Entity *caster, int skipCheck = 0);
	bool CanCastTargetRange(Entity *caster, int skipCheck = 0);
	bool SpellCostCheckAndRemove(Entity *caster);
	bool SpellCostCheck(Entity *caster);
	void SpellResourceGive(Entity *caster);
	void AddSpellCastEffect(Entity *caster);
	void RemoveSpellCastEffects(Entity *caster);
	void AddEffect(Entity *player, Node *effectPrefab, EffectPoints bodyPart, Quaternion *rotation =);
	void AddWorldEffect(Entity *location, Node *effectPrefab, Vector3 *offset =, Quaternion *rotation =);
	void RemoveEffect(Entity *player, EffectPoints bodyPart);
	String StringifyCooldown(float cooldown);
	void SpellCastSuccess(Entity *caster);
	void PlaySound(String sound);
	void PlayStandardSpellCastFinish();
	void PlayStandardSpellCastFinish(Entity *caster);
	void PlayStandardIceArcherAttackSpellCastFinish(Entity *caster);
	void PlayStandardBerserkerAttackSpellCastFinish(Entity *caster);
	void AnimStop(Entity *player);*/

	Spell();
	~Spell();

protected:
	static void _bind_methods();

private:
	int _spell_id;
	int _spell_type;

	bool _hide_from_actionbar;
	float _cooldown;
	SpellTargetType _target_type;
	TargetRelationType _target_relation_type;

	Ref<Aura> *_caster_aura_apply_ref;
	Ref<Aura> *_caster_aura_apply2_ref;
	Ref<Aura> *_target_aura_apply_ref;
	Ref<Aura> *_target_aura_apply2_ref;

	Aura *_caster_aura_apply;
	Aura *_caster_aura_apply2;
	Aura *_target_aura_apply;
	Aura *_target_aura_apply2;

	int _level;
	int _rank;
	Ref<Spell> _next_rank;
	int _item_cost;
	int _craft_material_cost;
	int _required_item;
	EntityEnums::PlayerResourceTypes _cost_type;
	int _cost_resource;
	EntityEnums::PlayerResourceTypes _give_resource_type;
	int _give_resource;
	bool _has_global_cooldown;
	bool _is_local_spell;
	Ref<Texture> _icon;
	String _name_key;
	String _spell_name;
	String _spell_description;

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

	EntityEnums::CharacterSkeletonPoints _effect_visual_point;
	Ref<PackedScene> _effect_visual;

	EntityEnums::CharacterSkeletonPoints _spell_cast_finish_effect_point;
	Ref<PackedScene> _spell_cast_finish_effect;

	Ref<PackedScene> _spell_cast_effect;

	Ref<PackedScene> _projectile;
	float _projectile_speed;
	float _projectile_time;
	float _projectile_range;
	SpellProjectileType _projectile_type;
	bool _projectile_destroy_on_impact;
	bool _projectile_collision;

	int _spell_cooldown_mainpulation_data_count;
};

#endif
