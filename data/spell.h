#ifndef SPELL_H
#define SPELL_H

#include "core/resource.h"
#include "scene/resources/curve.h"
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
	TARGET_SELF,
	TARGET_ENEMY,
	TARGET_TARGET
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
	int get_spell_id() { return _spell_id; }
	void set_spell_id(int value) { _spell_id = value; }

	int get_spell_type() { return _spell_type; }
	void set_spell_type(int value) { _spell_type = value; }

	bool get_hide_from_actionbar() { return _hide_from_actionbar; }
	void set_hide_from_actionbar(bool value) { _hide_from_actionbar = value; }

	float get_cooldown() { return _cooldown; }
	void set_cooldown(float value) { _cooldown = value; }

	SpellTargetType get_target_type() { return _target_type; }
	void set_target_type(SpellTargetType value) { _target_type = value; }

	Ref<Aura> get_caster_aura_apply();
	void set_caster_aura_apply(Ref<Aura> value);

	Ref<Aura> get_caster_aura_apply2();
	void set_caster_aura_apply2(Ref<Aura> value);

	Ref<Aura> get_target_aura_apply();
	void set_target_aura_apply(Ref<Aura> value);

	Ref<Aura> get_target_aura_apply2();
	void set_target_aura_apply2(Ref<Aura> value);

	int get_level() { return _level; }
	void set_level(int value) { _level = value; }

	int get_item_cost() { return _item_cost; }
	void set_item_cost(int value) { _item_cost = value; }

	int get_craft_material_cost() { return _craft_material_cost; }
	void set_craft_material_cost(int value) { _craft_material_cost = value; }

	int get_required_item() { return _required_item; }
	void set_required_item(int value) { _required_item = value; }

	EntityEnums::PlayerResourceTypes get_cost_type() { return _cost_type; }
	void set_cost_type(EntityEnums::PlayerResourceTypes value) { _cost_type = value; }

	int get_cost_resource() { return _cost_resource; }
	void set_cost_resource(int value) { _cost_resource = value; }

	EntityEnums::PlayerResourceTypes get_give_resource_type() { return _give_resource_type; }
	void set_give_resource_type(EntityEnums::PlayerResourceTypes value) { _give_resource_type = value; }

	int get_give_resource() { return _give_resource; }
	void set_give_resource(int value) { _give_resource = value; }

	bool has_global_cooldown() { return _has_global_cooldown; }
	void set_has_global_cooldown(bool value) { _has_global_cooldown = value; }

	bool get_is_local_spell() { return _is_local_spell; }
	void set_is_local_spell(bool value) { _is_local_spell = value; }

	Ref<Texture> get_icon() { return _icon; }
	void set_icon(Ref<Texture> value) { _icon = Ref<Texture>(value); }

	String get_name_key() { return _name_key; }
	void set_name_key(String value) { _name_key = value; }

	String get_spell_name() { return _spell_name; }
	void set_spell_name(String value) { _spell_name = value; }

	String get_spell_description() { return _spell_description; }
	void set_spell_description(String value) { _spell_description = value; }

	float get_damage_scale_for_level(int level);
	float get_heal_scale_for_level(int level);
	float get_absorb_scale_for_level(int level);

	bool get_has_range() { return _has_range; }
	void set_has_range(bool value) { _has_range = value; }

	float get_range() { return _range; }
	void set_range(float value) { _range = value; }

	bool get_has_cast_time() { return _has_cast_time; }
	void set_has_cast_time(bool value) { _has_cast_time = value; }

	float get_cast_time() { return _cast_time; }
	void set_cast_time(float value) { _cast_time = value; }

	bool get_has_damage() { return _has_damage; }
	void set_has_damage(bool value) { _has_damage = value; }

	int get_damage_type() { return _damage_type; }
	void set_damage_type(int value) { _damage_type = value; }

	int get_damage_min() { return _damage_min; }
	void set_damage_min(int value) { _damage_min = value; }

	int get_damage_max() { return _damage_max; }
	void set_damage_max(int value) { _damage_max = value; }

	Ref<Curve> get_damage_scaling_curve() { return _damage_scaling_curve; }
	void set_damage_scaling_curve(Ref<Curve> curve) { _damage_scaling_curve = curve; }

	bool get_has_heal() { return _has_heal; }
	void set_has_heal(bool value) { _has_heal = value; }

	int get_heal_min() { return _heal_min; }
	void set_heal_min(int value) { _heal_min = value; }

	int get_heal_max() { return _heal_max; }
	void set_heal_max(int value) { _heal_max = value; }

	Ref<Curve> get_heal_scaling_curve() { return _heal_scaling_curve; }
	void set_heal_scaling_curve(Ref<Curve> curve) { _heal_scaling_curve = curve; }

	bool get_needs_target() { return _needs_target; }
	void set_needs_target(bool value) { _needs_target = value; }

	bool get_can_move_while_casting() { return _can_move_while_casting; }
	void set_can_move_while_casting(bool value) { _can_move_while_casting = value; }

	bool get_is_interrupt() { return _is_interrupt; }
	void set_is_interrupt(bool value) { _is_interrupt = value; }

	float get_interrupt_time() { return _interrupt_time; }
	void set_interrupt_time(float value) { _interrupt_time = value; }

	bool get_is_aoe() { return _is_aoe; }
	void set_is_aoe(bool value) { _is_aoe = value; }

	SpellAOETargetType get_aoe_target_type() { return _aoe_targetType; }
	void set_aoe_target_type(SpellAOETargetType value) { _aoe_targetType = value; }

	SpellAOEMovementType get_aoe_movement_type() { return _aoe_movementType; }
	void set_aoe_movement_type(SpellAOEMovementType value) { _aoe_movementType = value; }

	SpellAOEColliderType get_aoe_collider_type() { return _aoe_colliderType; }
	void set_aoe_collider_type(SpellAOEColliderType value) { _aoe_colliderType = value; }

	Vector3 get_aoe_half_extents() { return _aoe_half_extents; }
	void set_aoe_half_extents(Vector3 value) { _aoe_half_extents = value; }

	bool get_has_effect() { return _has_effect; }
	void set_has_effect(bool value) { _has_effect = value; }

	int get_effect_id() { return _effect_id; }
	void set_effect_id(int value) { _effect_id = value; }

	bool get_has_spell_cast_finish_effect() { return _has_spell_cast_finish_effect; }
	void set_has_spell_cast_finish_effect(bool value) { _has_spell_cast_finish_effect = value; }

	int get_spell_cast_finish_effect_id() { return _spell_cast_finish_effect_id; }
	void set_spell_cast_finish_effect_id(int value) { _spell_cast_finish_effect_id = value; }

	bool get_has_spell_cast_effect() { return _has_spell_cast_effect; }
	void set_has_spell_cast_effect(bool value) { _has_spell_cast_effect = value; }

	int get_spell_cast_effect_id() { return _spell_cast_effect_id; }
	void set_spell_cast_effect_id(int value) { _spell_cast_effect_id = value; }

	int get_projectile_id() { return _projectile_id; }
	void set_projectile_id(int value) { _projectile_id = value; }

	bool get_has_projectile() { return _has_projectile; }
	void set_has_projectile(bool value) { _has_projectile = value; }

	float get_projectile_speed() { return _projectile_speed; }
	void set_projectile_speed(float value) { _projectile_speed = value; }

	float get_projectile_time() { return _projectile_time; }
	void set_projectile_time(float value) { _projectile_time = value; }

	float get_projectile_range() { return _projectile_range; }
	void set_projectile_range(float value) { _projectile_range = value; }

	bool get_has_projectile_collision() { return _projectile_collision; }
	void set_has_projectile_collision(bool value) { _projectile_collision = value; }

	SpellProjectileType get_projectile_type() { return _projectile_type; }
	void set_projectile_type(SpellProjectileType value) { _projectile_type = value; }

	bool get_has_projectile_destroy_on_impact() { return _projectile_destroy_on_impact; }
	void set_has_projectile_destroy_on_impact(bool value) { _projectile_destroy_on_impact = value; }

	int get_spell_cooldown_mainpulation_data_count() { return _spell_cooldown_mainpulation_data_count; }
	void set_spell_cooldown_mainpulation_data_count(int value) { _spell_cooldown_mainpulation_data_count = value; }

	//AuraApplyData *getAuraApplyData() { return auraApplyData; }
	//void setAuraApplyData(AuraApplyData *value) { auraApplyData = value; }

	/*
	void Set(int _spell_id, SpellType _spell_type, int p_damage_min, int _damage_max, bool _hideFrom_actionbar, float _cast_time,
		float cooldown, int casterAuraApply, int casterAuraApply2, int targetAuraApply, int targetAuraApply2,
		int level, int itemCost, int crafMaterialCost, int requiredItem, String *costTypeString, int costResource,
		String *giveResourceTypeString, int giveResource, bool hasGlobalCooldown, bool isLocalSpell, String *iconBundle,
		String *iconFile, Vector2i *iconAtlasPosition, String *nameKey, String *spellName, String *spellDescription);

	void Set(bool needsTarget, bool canMoveWhileCasting);
		*/

	////    Spell Script    ////

	float PLAYER_HIT_RADIUS;

	void start_casting_simple(Entity *caster, float spell_scale);
	void casting_failed_simple(Entity *caster);
	void start_casting_triggered_simple(Entity *caster);

	virtual void _start_casting(Ref<SpellCastInfo> info);

	virtual void start_casting(Ref<SpellCastInfo> info);
	virtual void casting_finished(Ref<SpellCastInfo> info);
	virtual void casting_failed(Ref<SpellCastInfo> info);
	virtual void start_casting_triggered(Ref<SpellCastInfo> info);

	//SpellHitInfo
	virtual void spell_hit(Entity *caster, Entity *target, Node *worldSpell, Spell *spell, float spellScale);
	virtual void on_player_move(Entity *caster);
	virtual void c_on_spell_cast_started(Entity *player);
	virtual void c_on_spell_cast_success(Entity *player);
	virtual void c_on_spell_cast_failed(Entity *player);
	virtual void c_on_spell_cast_ended(Entity *player);
	virtual void on_cast_state_changed(Entity *caster);

	virtual void calculate_initial_damage(Ref<SpellDamageInfo> data);
	virtual void handle_spell_damage(Ref<SpellDamageInfo> data);

	virtual String get_name();
	virtual String get_description(int level);

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
	//AuraApplyData *_aura_apply_data;

	Ref<Aura> *_caster_aura_apply_ref;
	Ref<Aura> *_caster_aura_apply2_ref;
	Ref<Aura> *_target_aura_apply_ref;
	Ref<Aura> *_target_aura_apply2_ref;

	Aura *_caster_aura_apply;
	Aura *_caster_aura_apply2;
	Aura *_target_aura_apply;
	Aura *_target_aura_apply2;

	int _level;
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

	bool _has_effect;
	int _effect_id;

	bool _has_spell_cast_finish_effect;
	int _spell_cast_finish_effect_id;

	bool _has_spell_cast_effect;
	int _spell_cast_effect_id;

	bool _has_projectile;
	int _projectile_id;
	float _projectile_speed;
	float _projectile_time;
	float _projectile_range;
	SpellProjectileType _projectile_type;
	bool _projectile_destroy_on_impact;
	bool _projectile_collision;

	int _spell_cooldown_mainpulation_data_count;
};

#endif
