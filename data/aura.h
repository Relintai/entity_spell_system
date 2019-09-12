#ifndef AURA_H
#define AURA_H

#include "core/resource.h"
#include "scene/resources/curve.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../spell_enums.h"

#include "../entities/entity.h"
#include "../entities/stats/stat.h"
#include "../infos/aura_infos.h"

#include "aura_stat_attribute.h"
#include "aura_trigger_data.h"

#include "../entities/auras/aura_data.h"
#include "../pipelines/spell_damage_info.h"
#include "../pipelines/spell_heal_info.h"
#include "../infos/spell_cast_info.h"

#include "../utility/cooldown.h"
#include "../utility/category_cooldown.h"

#include "spell_effect_visual.h"
#include "spell_projectile_data.h"
#include "world_effect_data.h"

class AuraApplyInfo;
class AuraScript;
class Entity;
class SpellCastInfo;

class Aura : public Resource {
	GDCLASS(Aura, Resource);

public:
	int get_id();
	void set_id(int value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	float get_time();
	void set_time(float value);

	int get_aura_group();
	void set_aura_group(int value);

	bool get_is_debuff();
	void set_is_debuff(bool value);

	float get_tick();
	void set_tick(float value);

	SpellEnums::AuraType get_aura_type();
	void set_aura_type(SpellEnums::AuraType value);

	String get_aura_name();
	void set_aura_name(String name);

	bool get_hide();
	void set_hide(bool value);

	String get_aura_description();
	void set_aura_description(String description);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(Ref<SpellEffectVisual> value);

	Ref<SpellProjectileData> get_spell_projectile_data();
	void set_spell_projectile_data(Ref<SpellProjectileData> value);

	Ref<WorldEffectData> get_world_effect_data();
	void set_world_effect_data(Ref<WorldEffectData> value);

	int get_ability_scale_data_id();
	void set_ability_scale_data_id(int value);

	float get_damage_scale_for_level(int level);
	float get_heal_scale_for_level(int level);
	float get_absorb_scale_for_level(int level);
	void set(int id, float time, int auraGroup);

	//   AnimationCurve* getDamageLevelScaling();
	//  AnimationCurve* getAbsorbLevelScaling();
	//   AnimationCurve* getHealLevelScaling();

	//  void SetScalingData(AbilityScalingData* scalingData);

	// static void FromJSON(Aura* ada, JsonReader* r);
	//  static void ToJSON(Aura* ada, JsonWriter* w);

	//Damage
	bool is_damage_enabled();
	void set_damage_enabled(bool value);

	int get_damage_type();

	void set_damage_type(int value);

	int get_damage_min();
	void set_damage_min(int value);

	int get_damage_max();
	void set_damage_max(int value);

	bool get_damage_can_crit();
	void set_damage_can_crit(bool value);

	void set_damage(int min, int max, bool can_crit);

	//Absorb
	bool is_absorb_enabled();
	void set_absorb_enabled(bool value);

	int get_absorb_damage_type();

	void set_absorb_damage_type(int value);

	int get_absorb_min();
	void set_absorb_min(int value);

	int get_absorb_max();
	void set_absorb_max(int value);

	//Heal
	bool is_heal_enabled();
	void set_heal_enabled(bool value);

	int get_heal_min();
	void set_heal_min(int value);

	int get_heal_max();
	void set_heal_max(int value);

	bool get_heal_can_crit();
	void set_heal_can_crit(bool value);

	void set_heal(int min, int max, bool can_crit);

	Ref<Curve> get_damage_scaling_curve() { return _damage_scaling_curve; }
	void set_damage_scaling_curve(Ref<Curve> curve) { _damage_scaling_curve = curve; }

	Ref<Curve> get_heal_scaling_curve() { return _heal_scaling_curve; }
	void set_heal_scaling_curve(Ref<Curve> curve) { _heal_scaling_curve = curve; }

	Ref<Curve> get_absorb_scaling_curve() { return _absorb_scaling_curve; }
	void set_absorb_scaling_curve(Ref<Curve> curve) { _absorb_scaling_curve = curve; }

	//states
	int get_add_states() { return _add_states; }
	void set_add_states(int value) { _add_states = value; }

	int get_remove_effects_with_states() { return _remove_effects_with_states; }
	void set_remove_effects_with_states(int value) { _remove_effects_with_states = value; }

	int get_supress_states() { return _supress_states; }
	void set_supress_states(int value) { _supress_states = value; }

	//DiminishingReturns
	SpellEnums::DiminishingReturnCategory get_diminishing_category();
	void set_diminishing_category(SpellEnums::DiminishingReturnCategory diminishingCategory);

	//Triggers
	int get_trigger_count() const;
	void set_trigger_count(int count);

	SpellEnums::TriggerEvents get_trigger_event(int index) const;
	void set_trigger_event(int index, const SpellEnums::TriggerEvents value);

	Ref<Aura> get_trigger_aura(int index) const;
	void set_trigger_aura(int index, const Ref<Aura> value);

	Ref<Spell> get_trigger_spell(int index) const;
	void set_trigger_spell(int index, const Ref<Spell> value);

	//AuraStatAttributes
	int get_aura_stat_attribute_count() const;
	void set_aura_stat_attribute_count(int count);

	Stat::StatId get_aura_stat_attribute_stat(int index) const;
	void set_aura_stat_attribute_stat(int index, const Stat::StatId value);

	float get_aura_stat_attribute_base_mod(int index) const;
	void set_aura_stat_attribute_base_mod(int index, float value);

	float get_aura_stat_attribute_bonus_mod(int index) const;
	void set_aura_stat_attribute_bonus_mod(int index, float value);

	float get_aura_stat_attribute_percent_mod(int index) const;
	void set_aura_stat_attribute_percent_mod(int index, float value);

	Ref<AuraStatAttribute> get_aura_stat_attribute(int index) { return _aura_stat_attributes[index]; }

	////    SpellSystem    ////

	//Commands, c++ only
	void sapply_simple(Entity *caster, Entity *target, float spell_scale);

	//Commands
	void sapply(Ref<AuraApplyInfo> info);
	void sdeapply(Ref<AuraData> info);
	void sadd(Ref<AuraData> aura);
	void sremove(Ref<AuraData> aura);
	void sremove_expired(Ref<AuraData> aura);
	void sremove_dispell(Ref<AuraData> aura);
	void supdate(Ref<AuraData> aura, float delta);

	virtual void _sapply(Ref<AuraApplyInfo> info);
	virtual void _sdeapply(Ref<AuraData> info);
	virtual void _sadd(Ref<AuraData> aura);
	virtual void _sremove(Ref<AuraData> aura);
	virtual void _sremove_expired(Ref<AuraData> aura);
	virtual void _supdate(Ref<AuraData> aura, float delta);
	virtual void _sremove_dispell(Ref<AuraData> aura);

	//EventHandlers
	void son_before_cast(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_started(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<AuraData> aura, Ref<SpellCastInfo> info);

    void son_before_damage_hit(Ref<AuraData> aura, Ref<SpellDamageInfo> data);
	void son_hit(Ref<AuraData> aura, Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<AuraData> aura, Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<AuraData> aura, Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<AuraData> aura, Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<AuraData> aura, Ref<SpellDamageInfo> data);

    void son_before_heal_hit(Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void son_before_heal(Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void son_heal_receive(Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void son_dealt_heal(Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void son_heal_dealt(Ref<AuraData> aura, Ref<SpellHealInfo> data);

	void son_remove(Ref<AuraData> aura);
	void son_remove_expired(Ref<AuraData> aura);
	void son_remove_dispell(Ref<AuraData> aura);

	void son_before_aura_applied(Ref<AuraData> data);
	void son_after_aura_applied(Ref<AuraData> data);
    
    void son_death(Ref<AuraData> data);
	
	void son_cooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void son_cooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown);
	
	void son_category_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);
	void son_category_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);

	void son_gcd_started(Ref<AuraData> data, float gcd);
	void son_gcd_finished(Ref<AuraData> data);
    
    void son_physics_process(Ref<AuraData> data);

	void son_xp_gained(Ref<AuraData> data, int value);
	void son_level_up(Ref<AuraData> data, int value);
	
	//Clientside Event Handlers
	void con_cast_failed(Ref<AuraData> data, Ref<SpellCastInfo> info);
	void con_cast_started(Ref<AuraData> data, Ref<SpellCastInfo> info);
	void con_cast_state_changed(Ref<AuraData> data, Ref<SpellCastInfo> info);
	void con_cast_finished(Ref<AuraData> data, Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<AuraData> data, Ref<SpellCastInfo> info);
	
    void con_death(Ref<AuraData> data);
	
	void con_cooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void con_cooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void con_category_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);
	void con_category_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);
    
	void con_aura_added(Ref<AuraData> data);
	void con_aura_removed(Ref<AuraData> data);
	void con_aura_refresh(Ref<AuraData> data);
	
	void con_damage_dealt(Ref<AuraData> data, Ref<SpellDamageInfo> info);
	void con_dealt_damage(Ref<AuraData> data, Ref<SpellDamageInfo> info);
	void con_heal_dealt(Ref<AuraData> data, Ref<SpellHealInfo> info);
	void con_dealt_heal(Ref<AuraData> data, Ref<SpellHealInfo> info);
	
	void con_gcd_started(Ref<AuraData> data, float gcd);
	void con_gcd_finished(Ref<AuraData> data);

	void con_xp_gained(Ref<AuraData> data, int value);
	void con_level_up(Ref<AuraData> data, int value);

	//Calculations / Queries
	void setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	virtual void _setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	void sapply_passives_damage_receive(Ref<SpellDamageInfo> data);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> data);
	void calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> data);

	virtual void _sapply_passives_damage_receive(Ref<SpellDamageInfo> data);
	virtual void _sapply_passives_damage_deal(Ref<SpellDamageInfo> data);
	virtual void _calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> data);

	void sapply_passives_heal_receive(Ref<SpellHealInfo> data);
	void sapply_passives_heal_deal(Ref<SpellHealInfo> data);
	void calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> data);

	virtual void _sapply_passives_heal_receive(Ref<SpellHealInfo> data);
	virtual void _sapply_passives_heal_deal(Ref<SpellHealInfo> data);
	virtual void _calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> data);

	_FORCE_INLINE_ bool is_talent() const { return _aura_type == SpellEnums::AURA_TYPE_TALENT; }

	Aura();
	~Aura();

		/*
	void RemoveAura(WorldEntity *caster);
	bool ShouldApplyModifiers(WorldEntity *target);
	bool BasicAuraUpdate(WorldEntity *target, AuraData *data);
	bool ShouldApplyModifiers(WorldEntity *target, float refreshTo);
	bool ShouldApplyModifiers(WorldEntity *target, float refreshTo, WorldEntity *caster, float spellScale);
	bool ShouldRemoveModifiers(WorldEntity *target);
	void RefreshDamageCountAuraDiminished(WorldEntity *target, float refreshTo, WorldEntity *caster, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, DamageCountAuraData *aura);
	void AddAuraDataToTarget(WorldEntity *target, AuraData *data);
	void AddAuraDataToTarget(WorldEntity *target, WorldEntity *caster, float duration, float spellScale);
	void AddOrRefreshDamageAuraDataToTarget(WorldEntity *target, WorldEntity *caster, float spellScale, float duration, float tick, int damage);
	void AddOrRefreshHealAuraDataToTarget(WorldEntity *target, WorldEntity *caster, float spellScale, float duration, float tick, int heal);
	void AddOrRefreshShieldAuraDataToTarget(WorldEntity *target, WorldEntity *caster, float spellScale, float duration, int absorb);
	void AddOrRefreshDiminishingReturnAura(WorldEntity *target, DiminishingReturnAuraData::DiminishingReturnCategory diminishingCategory);
	void AddStatModifier(WorldEntity *target, int stat, float maxMod, float percentMod);
	void RemoveStatModifier(WorldEntity *target, int stat);
	void AddState(WorldEntity *target, StateData::StateType state);
	void RemoveState(WorldEntity *target, StateData::StateType state);
	void RemovethisAura(WorldEntity *target);
	AuraData *TargetHasCastersAura(WorldEntity *target, WorldEntity *caster);
	AuraData *TargetHasAura(WorldEntity *target);
	int CalculateDamage(WorldEntity *caster, WorldEntity *target, float spellScale);
	int CalculateHeal(WorldEntity *caster, WorldEntity *target, float spellScale);
	int CalculateAbsorb(WorldEntity *caster, WorldEntity *target, float spellScale);
	void UpdateDamageCountAura(WorldEntity *target, AuraData *aura, int damage, float breakHealthPercent);
	bool UpdateDamageAura(WorldEntity *target, AuraData *data);
	bool UpdateDamageAuraTickBool(WorldEntity *target, AuraData *data);
	bool UpdateHealAura(WorldEntity *target, AuraData *data);
	void AbsorbPOnBeforeDamage(SpellDamageInfo *data, AuraData *aura);
	void DealDamage(WorldEntity *target, DamageAuraData *data);
	void DealDamage(WorldEntity *target, DamageAuraData *data, int damage);
	void DealDamage(WorldEntity *target, WorldEntity *caster, int damage);
	void DealDamageWithoutOnHit(WorldEntity *target, WorldEntity *caster, int damage);
	void Heal(WorldEntity *target, HealAuraData *data);
	void Heal(WorldEntity *target, HealAuraData *data, int heal);
	void Heal(WorldEntity *target, AuraData *data, int heal);
	DiminishingReturnAuraData *GetDiminishingReturnAuraDataFor(WorldEntity *target, DiminishingReturnAuraData::DiminishingReturnCategory type);
	float GetDiminishedTime(WorldEntity *target, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, float time);
	void AddEffect(WorldEntity *player, EffectPoints bodyPart, Quaternion *rotation =);
	void AddEffect(WorldEntity *player, GameObject *effectPrefab, EffectPoints bodyPart, Quaternion *rotation =);
	void RemoveEffect(WorldEntity *player, EffectPoints bodyPart);
	void RemoveActiveGroupAuras(WorldEntity *target);
	float GetDiminishedTime(WorldEntity *target, DiminishingReturnAuraData *aura, float time);
	int GetAuraIdForDiminishingReturn(DiminishingReturnAuraData::DiminishingReturnCategory type);
	AuraData *getAuraData(WorldEntity *target, int pAuraId);
	void ApplyAura(int auraId, WorldEntity *caster, WorldEntity *target, float spellScale);
	bool IsZero(float x);*/

	//generic
	// void ApplyEffect(Entity* target);
	// void RemoveEffect(Entity* target);
	// void ApplyModifiers(Entity* target);
	// void RemoveModifiers(Entity* target);
	// bool hasModifiers;

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_AURA_STATS = 5, //Increase if necessary, should be enough for now
		MAX_TRIGGER_DATA = 5,
	};

	int id;
	float time;
	float _tick;
	int aura_group;
	Ref<Texture> _icon;
	SpellEnums::AuraType _aura_type;
	bool _is_debuff;
	bool _hide;

	String _aura_name;
	String _aura_description;
	int ability_scale_data_id;

	Ref<SpellEffectVisual> _visual_spell_effects;
	Ref<SpellProjectileData> _spell_projectile_data;
	Ref<WorldEffectData> _world_effect_data;
	
	bool _damage_enabled;
	int _damage_type;
	int _damage_min;
	int _damage_max;
	bool _damage_can_crit;
	Ref<Curve> _damage_scaling_curve;

	bool _absorb_enabled;
	int _absorb_damage_type;
	int _absorb_min;
	int _absorb_max;
	Ref<Curve> _absorb_scaling_curve;

	bool _heal_enabled;
	int _heal_min;
	int _heal_max;
	bool _heal_can_crit;
	Ref<Curve> _heal_scaling_curve;

	int _add_states;
	int _remove_effects_with_states;
	int _supress_states;

	int _trigger_count;
	Ref<AuraTriggerData> _trigger_datas[MAX_TRIGGER_DATA];

	int _aura_stat_attribute_count;
	Ref<AuraStatAttribute> _aura_stat_attributes[MAX_AURA_STATS];

	SpellEnums::DiminishingReturnCategory _diminishing_category;

	static const int DIMINISHING_RETURN_ROOT_AURA_ID = 1;
	static const int DIMINISHING_RETURN_TIME = 15;
};

#endif
