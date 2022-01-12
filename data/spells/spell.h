/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef SPELL_H
#define SPELL_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

#include "scene/resources/texture.h"

#include "../../entities/entity.h"
#include "../../entity_enums.h"
#include "../../infos/aura_infos.h"
#include "../../infos/spell_cast_info.h"
#include "../../spell_enums.h"

#include "spell_effect_visual.h"

class Entity;
class SpellCastInfo;
class Spell;
class CraftRecipe;
class EntityResourceCostData;
class EntitySkillData;
class SpellDamageInfo;
class SpellHealInfo;
class AuraData;
class AuraGroup;
class AuraApplyInfo;
class EntityResource;

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

enum SpellAOETargetType {
	SPELL_AOE_TARGET_TYPE_CASTER,
	SPELL_AOE_TARGET_TYPE_TARGET,
	SPELL_AOE_TARGET_TYPE_GOUND_TARGET_SELECTION,
	SPELL_AOE_TARGET_TYPE_RANDOM
};

VARIANT_ENUM_CAST(SpellAOETargetType);

class Spell : public Resource {
	GDCLASS(Spell, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int spell_type_get() const;
	void spell_type_set(const int value);

	SpellEnums::SpellCategory get_spell_category() const;
	void set_spell_category(const SpellEnums::SpellCategory value);

	bool get_hide_from_actionbar() const;
	void set_hide_from_actionbar(const bool value);

	float get_cooldown() const;
	void set_cooldown(const float value);

	SpellTargetType get_target_type() const;
	void set_target_type(const SpellTargetType value);

	TargetRelationType get_target_relation_type() const;
	void set_target_relation_type(const TargetRelationType value);

	int get_level() const;
	void set_level(const int value);

	int get_rank() const;
	void set_rank(const int value);

	bool get_scale_with_level() const;
	void set_scale_with_level(const bool value);

	Ref<ItemTemplate> get_item_cost();
	void set_item_cost(const Ref<ItemTemplate> &value);

	Ref<ItemTemplate> get_required_item();
	void set_required_item(const Ref<ItemTemplate> &value);

	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(const Ref<EntityResourceCostData> &value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(const Ref<EntityResourceCostData> &value);

	bool get_global_cooldown_enabled() const;
	void set_global_cooldown_enabled(const bool value);

	bool get_is_local_spell() const;
	void set_is_local_spell(const bool value);

	Ref<Texture> get_icon();
	void set_icon(const Ref<Texture> &value);

	String get_text_translation_key() const;
	void set_text_translation_key(const String &value);

	String get_text_description() const;
	void set_text_description(const String &value);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(const Ref<SpellEffectVisual> &value);

	Ref<CraftRecipe> get_teaches_craft_recipe();
	void set_teaches_craft_recipe(const Ref<CraftRecipe> &value);

	//Spells cast on caster
	int spells_cast_on_caster_num_get() const;
	void spells_cast_on_caster_num_set(const int value);

	Ref<Spell> spell_cast_on_caster_get(const int index);
	void spell_cast_on_caster_set(const int index, const Ref<Spell> &spell);

	Vector<Variant> spells_cast_on_caster_get();
	void spells_cast_on_caster_set(const Vector<Variant> &spells);

	//Spells cast on target
	int spells_cast_on_target_num_get() const;
	void spells_cast_on_target_num_set(const int value);

	Ref<Spell> spell_cast_on_target_get(const int index);
	void spell_cast_on_target_set(const int index, const Ref<Spell> &spell);

	Vector<Variant> spells_cast_on_target_get();
	void spells_cast_on_target_set(const Vector<Variant> &target_aura_applys);

	//Spells cast On Learn
	int on_learn_cast_spells_num_get() const;
	void on_learn_cast_spells_num_set(const int value);

	Ref<Spell> spell_cast_on_learn_get(const int index);
	void spell_cast_on_learn_set(const int index, const Ref<Spell> &spell);

	Vector<Variant> spells_cast_on_learn_get();
	void spells_cast_on_learn_set(const Vector<Variant> &spells);

	//Range
	bool range_get_enabled() const;
	void range_set_enabled(const bool value);

	float range_get() const;
	void range_set(const float value);

	bool cast_time_get_enabled() const;
	void cast_time_set_enabled(const bool value);

	float cast_time_get() const;
	void cast_time_set(const float value);

	//Delay
	bool projectile_get_use_time() const;
	void projectile_set_use_time(const bool value);

	float projectile_get_time() const;
	void projectile_set_time(const float value);

	bool projectile_get_use_speed() const;
	void projectile_set_use_speed(const bool value);

	float projectile_get_speed() const;
	void projectile_set_speed(const float value);

	Ref<PackedScene> projectile_get_scene() const;
	void projectile_set_scene(const Ref<PackedScene> &value);

	//Damage
	bool damage_get_enabled() const;
	void damage_set_enabled(const bool value);

	int damage_get_type() const;
	void damage_set_type(const int value);

	int damage_get_min() const;
	void damage_set_min(const int value);

	int damage_get_max() const;
	void damage_set_max(const int value);

	int damage_get_scale_stat() const;
	void damage_set_scale_stat(const int value);

	float damage_get_scale_coeff() const;
	void damage_set_scale_coeff(const float value);

	bool heal_get_enabled() const;
	void heal_set_enabled(const bool value);

	int heal_get_min() const;
	void heal_set_min(const int value);

	int heal_get_max() const;
	void heal_set_max(const int value);

	int heal_get_scale_stat() const;
	void heal_set_scale_stat(const int value);

	float heal_get_scale_coeff() const;
	void heal_set_scale_coeff(const float value);

	//Dispells
	bool dispell_get_enabled() const;
	void dispell_set_enabled(const bool value);

	int dispell_get_count_min() const;
	void dispell_set_count_min(const int value);

	int dispell_get_count_max() const;
	void dispell_set_count_max(const int value);

	int dispell_get_aura_types() const;
	void dispell_set_aura_types(const int value);

	//Target
	bool get_needs_target() const;
	void set_needs_target(const bool value);

	bool get_can_move_while_casting() const;
	void set_can_move_while_casting(const bool value);

	bool get_interrupt_enabled() const;
	void set_interrupt_enabled(const bool value);

	float get_interrupt_time() const;
	void set_interrupt_time(const float value);

	//AOE
	bool get_is_aoe() const;
	void set_is_aoe(const bool value);

	SpellAOETargetType get_aoe_target_type() const;
	void set_aoe_target_type(const SpellAOETargetType value);

	SpellEnums::ColliderType get_aoe_collider_type() const;
	void set_aoe_collider_type(const SpellEnums::ColliderType value);

	float get_aoe_radius() const;
	void set_aoe_radius(const float value);

	Vector3 get_aoe_box_extents() const;
	void set_aoe_box_extents(const Vector3 value);

	int get_spell_cooldown_mainpulation_data_count() const;
	void set_spell_cooldown_mainpulation_data_count(const int value);

	int get_training_cost() const;
	void set_training_cost(int value);

	Ref<Spell> get_training_required_spell();
	void set_training_required_spell(const Ref<Spell> &spell);

	Ref<EntitySkillData> get_training_required_skill();
	void set_training_required_skill(const Ref<EntitySkillData> &skill);

	int get_training_required_skill_level() const;
	void set_training_required_skill_level(const int value);

	//Auras
	bool aura_get_permanent() const;
	void aura_set_permanent(const bool value);

	float aura_get_time() const;
	void aura_set_time(const float value);

	Ref<AuraGroup> aura_get_aura_group();
	void aura_set_aura_group(const Ref<AuraGroup> &value);

	bool aura_get_is_debuff() const;
	void aura_set_is_debuff(const bool value);

	float aura_get_tick() const;
	void aura_set_tick(const float value);

	SpellEnums::AuraType aura_get_aura_type() const;
	void aura_set_aura_type(const SpellEnums::AuraType value);

	bool aura_get_scale_with_level() const;
	void aura_set_scale_with_level(const bool value);

	String aura_get_text_translation_key() const;
	void aura_set_text_translation_key(const String &value);

	String aura_get_text_description() const;
	void aura_set_text_description(const String description);

	bool aura_get_hide() const;
	void aura_set_hide(const bool value);

	Ref<SpellEffectVisual> aura_get_visual_spell_effects();
	void aura_set_visual_spell_effects(const Ref<SpellEffectVisual> &value);

	int aura_get_ability_scale_data_id() const;
	void aura_set_ability_scale_data_id(const int value);

	float aura_damage_get_scale_for_level(int level) const;
	float aura_heal_get_scale_for_level(int level) const;
	float aura_absorb_get_scale_for_level(int level) const;

	Ref<Spell> aura_get_teaches_spell();
	void aura_set_teaches_spell(const Ref<Spell> &spell);

	//Damage
	bool aura_damage_get_enabled() const;
	void aura_damage_set_enabled(const bool value);

	int aura_damage_get_type() const;

	void aura_damage_set_type(const int value);

	int aura_damage_get_min() const;
	void aura_damage_set_min(const int value);

	int aura_damage_get_max() const;
	void aura_damage_set_max(const int value);

	bool aura_damage_get_can_crit() const;
	void aura_damage_set_can_crit(const bool value);

	void aura_damage_set(const int min, const int max, const bool can_crit);

	//Absorb
	bool aura_absorb_get_enabled() const;
	void aura_absorb_set_enabled(const bool value);

	int aura_absorb_damage_get_type() const;
	void aura_absorb_damage_set_type(const int value);

	int aura_absorb_get_min() const;
	void aura_absorb_set_min(const int value);

	int aura_absorb_get_max() const;
	void aura_absorb_set_max(const int value);

	//Heal
	bool aura_heal_get_enabled() const;
	void aura_heal_set_enabled(const bool value);

	int aura_heal_get_min() const;
	void aura_heal_set_min(const int value);

	int aura_heal_get_max() const;
	void aura_heal_set_max(const int value);

	bool aura_heal_get_can_crit() const;
	void aura_heal_set_can_crit(const bool value);

	void aura_heal_set(const int min, const int max, const bool can_crit);

	//Dispells
	bool aura_dispell_get_enabled() const;
	void aura_dispell_set_enabled(const bool value);

	int aura_dispell_get_count_min() const;
	void aura_dispell_set_count_min(const int value);

	int aura_dispell_get_count_max() const;
	void aura_dispell_set_count_max(const int value);

	int aura_dispell_get_aura_types() const;
	void aura_dispell_set_aura_types(const int value);

	//Resources
	Ref<EntityResourceCostData> aura_get_resource_cost();
	void aura_set_resource_cost(const Ref<EntityResourceCostData> &value);

	Ref<EntityResourceCostData> aura_get_resource_give();
	void aura_set_resource_give(const Ref<EntityResourceCostData> &value);

	Ref<Curve> aura_damage_get_scaling_curve() { return _aura_damage_scaling_curve; }
	void aura_damage_set_scaling_curve(const Ref<Curve> &curve) { _aura_damage_scaling_curve = curve; }

	Ref<Curve> aura_heal_get_scaling_curve() { return _aura_heal_scaling_curve; }
	void aura_heal_set_scaling_curve(const Ref<Curve> &curve) { _aura_heal_scaling_curve = curve; }

	Ref<Curve> aura_absorb_get_scaling_curve() { return _aura_absorb_scaling_curve; }
	void aura_absorb_set_scaling_curve(const Ref<Curve> &curve) { _aura_absorb_scaling_curve = curve; }

	//states
	int aura_get_add_states() const { return _aura_add_states; }
	void aura_set_add_states(const int value) { _aura_add_states = value; }

	int aura_get_remove_effects_with_states() const { return _aura_remove_effects_with_states; }
	void aura_set_remove_effects_with_states(const int value) { _aura_remove_effects_with_states = value; }

	int aura_get_supress_states() const { return _aura_supress_states; }
	void aura_set_supress_states(const int value) { _aura_supress_states = value; }

	//DiminishingReturns
	bool aura_diminishing_return_enabled_get() const;
	void aura_diminishing_return_enabled_set(const bool value);

	int aura_diminishing_return_category_get() const;
	void aura_diminishing_return_category_set(const int value);

	//Triggers
	int aura_trigger_get_count() const;
	void aura_trigger_set_count(const int count);

	SpellEnums::TriggerNotificationType aura_trigger_get_notification_type(const int index) const;
	void aura_trigger_set_notification_type(const int index, const SpellEnums::TriggerNotificationType value);

	int aura_trigger_get_notification_data(const int index) const;
	void aura_trigger_set_notification_data(const int index, const int value);

	SpellEnums::TriggerType aura_trigger_get_trigger_type(const int index) const;
	void aura_trigger_set_trigger_type(const int index, const SpellEnums::TriggerType value);

	float aura_trigger_get_trigger_type_data(const int index) const;
	void aura_trigger_set_trigger_type_data(const int index, const float value);

	Ref<Spell> aura_trigger_get_spell(const int index) const;
	void aura_trigger_set_spell(const int index, const Ref<Spell> &value);

	//Talent
	Ref<Spell> aura_get_talent_required_talent() const;
	void aura_set_talent_required_talent(const Ref<Spell> rank);

	Ref<Spell> aura_get_talent_required_spell() const;
	void aura_set_talent_required_spell(const Ref<Spell> spell);

	//AuraStatAttributes
	int aura_stat_attribute_get_count() const;
	void aura_stat_attribute_set_count(int count);

	int aura_stat_attribute_get_stat(int index) const;
	void aura_stat_attribute_set_stat(int index, const int value);

	float aura_stat_attribute_get_base_mod(int index) const;
	void aura_stat_attribute_set_base_mod(int index, float value);

	float aura_stat_attribute_get_bonus_mod(int index) const;
	void aura_stat_attribute_set_bonus_mod(int index, float value);

	float aura_stat_attribute_get_percent_mod(int index) const;
	void aura_stat_attribute_set_percent_mod(int index, float value);

	////    Spell Script    ////

	float PLAYER_HIT_RADIUS;

	//Commands, c++ only
	void cast_starts_simple(Entity *caster, float spell_scale);
	void cast_interrupts_simple(Entity *caster);
	void cast_starts_triggered_simple(Entity *caster);
	void aura_sapply_simple(Entity *caster, Entity *target, float spell_scale);

	//Commands
	void cast_starts(Ref<SpellCastInfo> info);
	void cast_starts_triggered(Ref<SpellCastInfo> info);
	void cast_interrupts(Ref<SpellCastInfo> info);
	void cast_finishs(Ref<SpellCastInfo> info);

	void aura_sapply(Ref<AuraApplyInfo> info);
	void aura_sdeapply(Ref<AuraData> info);
	void aura_sadd(Ref<AuraData> aura);
	void aura_sremove(Ref<AuraData> aura);
	void aura_removes_expired(Ref<AuraData> aura);
	void aura_removes_dispell(Ref<AuraData> aura);
	void aura_supdate(Ref<AuraData> aura, float delta);

	//eventhandlers
	void son_cast_player_moved(Ref<SpellCastInfo> info);
	void son_cast_damage_received(Ref<SpellCastInfo> info);
	void son_spell_hit(Ref<SpellCastInfo> info);
	void son_physics_process(Ref<SpellCastInfo> info, float delta);

	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_aura_scast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void notification_sdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data);

	void son_remove(Ref<AuraData> aura);
	void son_remove_expired(Ref<AuraData> aura);
	void son_remove_dispell(Ref<AuraData> aura);

	void notification_sdeath(Ref<AuraData> data);

	void notification_scooldown_added(Ref<AuraData> data, int id, float value);
	void notification_scooldown_removed(Ref<AuraData> data, int id, float value);

	void notification_scategory_cooldown_added(Ref<AuraData> data, int id, float value);
	void notification_scategory_cooldown_removed(Ref<AuraData> data, int id, float value);

	void notification_sgcd_started(Ref<AuraData> data, float gcd);
	void notification_sgcd_finished(Ref<AuraData> data);

	void son_physics_process_aura(Ref<AuraData> data);

	void notification_sxp_gained(Ref<AuraData> data, int value);
	void notification_slevel_up(Ref<AuraData> data, int value);

	void notification_sentity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

	//Clientside Event Handlers
	void notification_scast(int what, Ref<SpellCastInfo> info);
	void notification_ccast(int what, Ref<SpellCastInfo> info);

	void notification_caura(int what, Ref<AuraData> data);
	void notification_cheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_aura_ccast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void notification_cdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data);

	void notification_cdeath(Ref<AuraData> data);

	void notification_ccooldown_added(Ref<AuraData> data, int id, float value);
	void notification_ccooldown_removed(Ref<AuraData> data, int id, float value);
	void notification_ccategory_cooldown_added(Ref<AuraData> data, int id, float value);
	void notification_ccategory_cooldown_removed(Ref<AuraData> data, int id, float value);

	void notification_cgcd_started(Ref<AuraData> data, float gcd);
	void notification_cgcd_finished(Ref<AuraData> data);

	void notification_cxp_gained(Ref<AuraData> data, int value);
	void notification_clevel_up(Ref<AuraData> data, int value);

	void notification_centity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void notification_centity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

	//Equipment
	bool equip_should_deny(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item);

	void equip_son_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void equip_con_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	//Calculations / Queries
	void calculate_initial_damage(Ref<SpellDamageInfo> data);
	void handle_spell_damage(Ref<SpellDamageInfo> data);

	void calculate_initial_heal(Ref<SpellHealInfo> data);
	void handle_spell_heal(Ref<SpellHealInfo> data);

	void handle_projectile(Ref<SpellCastInfo> info);
	void handle_effect(Ref<SpellCastInfo> info);

	void handle_gcd(Ref<SpellCastInfo> info);
	void handle_cooldown(Ref<SpellCastInfo> info);

	void setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	void aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	void aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info);
	void aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info);

	void aura_sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	void aura_sapply_passives_heal_deal(Ref<SpellHealInfo> info);
	void aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info);

	_FORCE_INLINE_ bool is_aura() const { return _aura_permanent || (_aura_time > CMP_EPSILON); }
	_FORCE_INLINE_ bool aura_is_talent() const { return _aura_type == SpellEnums::AURA_TYPE_TALENT; }

	String get_name_translated() const;
	String get_description(const int class_level, const int character_level);
	String _get_description(const int class_level, const int character_level);

	String aura_get_name_translated() const;
	String aura_get_description(const int class_level, const int character_level);
	String _aura_get_description(const int class_level, const int character_level);

	Spell();
	~Spell();

protected:
	virtual void _cast_starts(Ref<SpellCastInfo> info);
	virtual void _cast_finishs(Ref<SpellCastInfo> info);

	virtual void _son_cast_player_moved(Ref<SpellCastInfo> info);
	virtual void _son_spell_hit(Ref<SpellCastInfo> info);

	virtual void _calculate_initial_damage(Ref<SpellDamageInfo> data);
	virtual void _handle_spell_damage(Ref<SpellDamageInfo> data);

	virtual void _calculate_initial_heal(Ref<SpellHealInfo> data);
	virtual void _handle_spell_heal(Ref<SpellHealInfo> data);

	virtual void _handle_projectile(Ref<SpellCastInfo> info);
	virtual void _handle_effect(Ref<SpellCastInfo> info);

	virtual void _aura_sapply(Ref<AuraApplyInfo> info);
	virtual void _aura_sdeapply(Ref<AuraData> info);
	virtual void _aura_sadd(Ref<AuraData> aura);
	virtual void _aura_sremove(Ref<AuraData> aura);
	virtual void _aura_removes_expired(Ref<AuraData> aura);
	virtual void _aura_removes_dispell(Ref<AuraData> aura);
	virtual void _aura_supdate(Ref<AuraData> aura, float delta);

	virtual void _setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	virtual void _aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	virtual void _aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info);
	virtual void _aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info);

	virtual void _aura_sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	virtual void _aura_sapply_passives_heal_deal(Ref<SpellHealInfo> info);
	virtual void _aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info);

	void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

protected:
	struct AuraTriggerData {
		SpellEnums::TriggerNotificationType notification_type;
		int notification_data;
		SpellEnums::TriggerType trigger_type;
		float trigger_type_data;
		Ref<Spell> spell;

		AuraTriggerData() {
			notification_type = SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA;
			trigger_type = SpellEnums::TRIGGER_TYPE_NONE;
			notification_data = 0;
			trigger_type_data = 0;
		}
	};

	struct AuraStatAttribute {
		int stat;
		float base_mod;
		float bonus_mod;
		float percent_mod;

		AuraStatAttribute() {
			stat = 0;
			base_mod = 0;
			bonus_mod = 0;
			percent_mod = 0;
		}
	};

private:
	enum {
		MAX_AURA_STATS = 5, //Increase if necessary, should be enough for now
		MAX_TRIGGER_DATA = 5,
	};

	int _id;
	int _spell_type;
	SpellEnums::SpellCategory _spell_category;

	bool _hide_from_actionbar;
	float _cooldown;
	SpellTargetType _target_type;
	TargetRelationType _target_relation_type;

	Vector<Ref<Spell>> _spells_cast_on_caster;
	Vector<Ref<Spell>> _spells_cast_on_target;
	Vector<Ref<Spell>> _on_learn_cast_spells;

	int _level;
	int _rank;

	bool _scale_with_level;

	Ref<ItemTemplate> _item_cost;
	Ref<ItemTemplate> _required_item;

	Ref<EntityResourceCostData> _resource_cost;
	Ref<EntityResourceCostData> _resource_give;

	bool _global_cooldown_enabled;
	bool _is_local_spell;
	Ref<Texture> _icon;

	String _text_translation_key;
	String _text_description;

	Ref<SpellEffectVisual> _visual_spell_effects;

	Ref<CraftRecipe> _teaches_craft_recipe;

	bool _range_enabled;
	float _range;

	//Delay
	bool _projectile_use_time;
	float _projectile_time;
	bool _projectile_use_speed;
	float _projectile_speed;
	Ref<PackedScene> _projectile_scene;

	bool _damage_enabled;
	int _damage_type;
	int _damage_min;
	int _damage_max;
	int _damage_scale_stat;
	float _damage_scale_coeff;

	bool _heal_enabled;
	int _heal_min;
	int _heal_max;
	int _heal_scale_stat;
	float _heal_scale_coeff;

	bool _dispell_enabled;
	int _dispell_count_min;
	int _dispell_count_max;
	int _dispell_aura_types;

	bool _cast_time_enabled;
	float _cast_time;

	bool _needs_target;
	bool _can_move_while_casting;

	bool _interrupt_enabled;
	float _interrupt_time;

	bool _is_aoe;
	SpellAOETargetType _aoe_targetType;
	SpellEnums::ColliderType _aoe_colliderType;
	float _aoe_radius;
	Vector3 _aoe_box_extents;

	int _spell_cooldown_mainpulation_data_count;

	int _training_cost;
	Ref<Spell> _training_required_spell;
	Ref<EntitySkillData> _training_required_skill;
	int _training_required_skill_level;

	//Aura
	bool _aura_permanent;
	float _aura_time;
	float _aura_tick;
	Ref<AuraGroup> _aura_group;

	SpellEnums::AuraType _aura_type;
	bool _aura_is_debuff;
	bool _aura_hide;
	Ref<Spell> _aura_teaches_spell;

	String _aura_text_translation_key;
	String _aura_text_description;
	int _aura_ability_scale_data_id;

	bool _aura_scale_with_level;

	Ref<SpellEffectVisual> _aura_visual_spell_effects;

	bool _aura_damage_enabled;
	int _aura_damage_type;
	int _aura_damage_min;
	int _aura_damage_max;
	bool _aura_damage_can_crit;
	Ref<Curve> _aura_damage_scaling_curve;

	bool _aura_absorb_enabled;
	int _aura_absorb_damage_type;
	int _aura_absorb_min;
	int _aura_absorb_max;
	Ref<Curve> _aura_absorb_scaling_curve;

	bool _aura_heal_enabled;
	int _aura_heal_min;
	int _aura_heal_max;
	bool _aura_heal_can_crit;
	Ref<Curve> _aura_heal_scaling_curve;

	bool _aura_dispell_enabled;
	int _aura_dispell_count_min;
	int _aura_dispell_count_max;
	int _aura_dispell_aura_types;

	Ref<EntityResourceCostData> _aura_resource_cost;
	Ref<EntityResourceCostData> _aura_resource_give;

	int _aura_add_states;
	int _aura_remove_effects_with_states;
	int _aura_supress_states;

	int _aura_trigger_count;
	AuraTriggerData _aura_trigger_datas[MAX_TRIGGER_DATA];

	int _aura_stat_attribute_count;
	AuraStatAttribute _aura_stat_attributes[MAX_AURA_STATS];

	bool _aura_diminishing_return_enabled;
	int _aura_diminishing_return_category;

	//Talent
	Ref<Spell> _aura_talent_required_talent;
	Ref<Spell> _aura_talent_required_spell;
};

#endif
