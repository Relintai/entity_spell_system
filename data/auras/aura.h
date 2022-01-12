/*
Copyright (c) 2019-2021 Péter Magyar

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

#ifndef AURA_H
#define AURA_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

#include "scene/resources/curve.h"
#include "scene/resources/texture.h"

#include "aura_group.h"

#include "../../entity_enums.h"
#include "../../spell_enums.h"

#include "../../entities/entity.h"
#include "../../infos/aura_infos.h"

#include "../../entities/auras/aura_data.h"
#include "../../infos/spell_cast_info.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../spells/spell_effect_visual.h"

class AuraApplyInfo;
class AuraScript;
class Entity;
class SpellCastInfo;
class EntityResourceCostData;

class Spell;

class Aura : public Resource {
	GDCLASS(Aura, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int get_rank() const;
	void set_rank(const int value);

	Ref<Texture> get_icon();
	void set_icon(const Ref<Texture> &value);

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
	Ref<Aura> aura_get_talent_required_talent() const;
	void aura_set_talent_required_talent(const Ref<Aura> rank);

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

	////    SpellSystem    ////

	//Commands, c++ only
	void aura_sapply_simple(Entity *caster, Entity *target, float spell_scale);

	//Commands
	void aura_sapply(Ref<AuraApplyInfo> info);
	void aura_sdeapply(Ref<AuraData> info);
	void aura_sadd(Ref<AuraData> aura);
	void aura_sremove(Ref<AuraData> aura);
	void aura_removes_expired(Ref<AuraData> aura);
	void aura_removes_dispell(Ref<AuraData> aura);
	void aura_supdate(Ref<AuraData> aura, float delta);

	//EventHandlers
	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_scast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
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

	void son_physics_process(Ref<AuraData> data);

	void notification_sxp_gained(Ref<AuraData> data, int value);
	void notification_slevel_up(Ref<AuraData> data, int value);

	void notification_sentity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

	//Clientside Event Handlers
	void notification_caura(int what, Ref<AuraData> data);
	void notification_cheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_ccast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
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
	void setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	void aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	void aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info);
	void aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info);

	void aura_sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	void aura_sapply_passives_heal_deal(Ref<SpellHealInfo> info);
	void aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info);

	_FORCE_INLINE_ bool aura_is_talent() const { return _aura_type == SpellEnums::AURA_TYPE_TALENT; }

	String aura_get_name_translated() const;
	String aura_get_description(const int class_level, const int character_level);
	String _aura_get_description(const int class_level, const int character_level);

	Aura();
	~Aura();

protected:
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

	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

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
	int _rank;
	Ref<Texture> _icon;

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
	Ref<Aura> _aura_talent_required_talent;
	Ref<Spell> _aura_talent_required_spell;
};

#endif
