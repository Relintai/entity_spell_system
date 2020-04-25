/*
Copyright (c) 2019-2020 Péter Magyar

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

#include "core/resource.h"
#include "scene/resources/curve.h"
#include "scene/resources/texture.h"

#include "aura_group.h"

#include "../../entity_enums.h"
#include "../../spell_enums.h"

#include "../../entities/entity.h"
#include "../../entities/stats/stat.h"
#include "../../infos/aura_infos.h"

#include "aura_stat_attribute.h"
#include "aura_trigger_data.h"

#include "../../entities/auras/aura_data.h"
#include "../../infos/spell_cast_info.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../utility/category_cooldown.h"
#include "../../utility/cooldown.h"

#include "../spells/spell_effect_visual.h"

class AuraApplyInfo;
class AuraScript;
class Entity;
class SpellCastInfo;
class EntityResourceCostData;

class Aura : public Resource {
	GDCLASS(Aura, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	Ref<Texture> get_icon();
	void set_icon(const Ref<Texture> &value);

	float get_time() const;
	void set_time(const float value);

	Ref<AuraGroup> get_aura_group();
	void set_aura_group(const Ref<AuraGroup> &value);

	bool get_is_debuff() const;
	void set_is_debuff(const bool value);

	float get_tick() const;
	void set_tick(const float value);

	SpellEnums::AuraType get_aura_type() const;
	void set_aura_type(const SpellEnums::AuraType value);

	int get_rank() const;
	void set_rank(const int value);

	bool get_scale_with_level() const;
	void set_scale_with_level(const bool value);

	String get_text_translation_key() const;
	void set_text_translation_key(const String &value);

	String get_text_description() const;
	void set_text_description(const String description);

	bool get_hide() const;
	void set_hide(const bool value);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(const Ref<SpellEffectVisual> &value);

	int get_ability_scale_data_id() const;
	void set_ability_scale_data_id(const int value);

	float get_damage_scale_for_level(int level) const;
	float get_heal_scale_for_level(int level) const;
	float get_absorb_scale_for_level(int level) const;

	Ref<Spell> get_teaches_spell();
	void set_teaches_spell(const Ref<Spell> &spell);

	//Damage
	bool get_damage_enabled() const;
	void set_damage_enabled(const bool value);

	int get_damage_type() const;

	void set_damage_type(const int value);

	int get_damage_min() const;
	void set_damage_min(const int value);

	int get_damage_max() const;
	void set_damage_max(const int value);

	bool get_damage_can_crit() const;
	void set_damage_can_crit(const bool value);

	void set_damage(const int min, const int max, const bool can_crit);

	//Absorb
	bool get_absorb_enabled() const;
	void set_absorb_enabled(const bool value);

	int get_absorb_damage_type() const;

	void set_absorb_damage_type(const int value);

	int get_absorb_min() const;
	void set_absorb_min(const int value);

	int get_absorb_max() const;
	void set_absorb_max(const int value);

	//Heal
	bool get_heal_enabled() const;
	void set_heal_enabled(const bool value);

	int get_heal_min() const;
	void set_heal_min(const int value);

	int get_heal_max() const;
	void set_heal_max(const int value);

	bool get_heal_can_crit() const;
	void set_heal_can_crit(const bool value);

	void set_heal(const int min, const int max, const bool can_crit);

	//Dispells
	bool get_dispell_enabled() const;
	void set_dispell_enabled(const bool value);

	int get_dispell_count_min() const;
	void set_dispell_count_min(const int value);

	int get_dispell_count_max() const;
	void set_dispell_count_max(const int value);

	int get_dispell_aura_types() const;
	void set_dispell_aura_types(const int value);

	//Resources
	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(const Ref<EntityResourceCostData> &value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(const Ref<EntityResourceCostData> &value);

	Ref<Curve> get_damage_scaling_curve() { return _damage_scaling_curve; }
	void set_damage_scaling_curve(const Ref<Curve> &curve) { _damage_scaling_curve = curve; }

	Ref<Curve> get_heal_scaling_curve() { return _heal_scaling_curve; }
	void set_heal_scaling_curve(const Ref<Curve> &curve) { _heal_scaling_curve = curve; }

	Ref<Curve> get_absorb_scaling_curve() { return _absorb_scaling_curve; }
	void set_absorb_scaling_curve(const Ref<Curve> &curve) { _absorb_scaling_curve = curve; }

	//states
	int get_add_states() const { return _add_states; }
	void set_add_states(const int value) { _add_states = value; }

	int get_remove_effects_with_states() const { return _remove_effects_with_states; }
	void set_remove_effects_with_states(const int value) { _remove_effects_with_states = value; }

	int get_supress_states() const { return _supress_states; }
	void set_supress_states(const int value) { _supress_states = value; }

	//DiminishingReturns
	SpellEnums::DiminishingReturnCategory get_diminishing_category() const;
	void set_diminishing_category(const SpellEnums::DiminishingReturnCategory diminishingCategory);

	//Triggers
	int get_trigger_count() const;
	void set_trigger_count(int count);

	SpellEnums::TriggerEvents get_trigger_event(int index) const;
	void set_trigger_event(int index, const SpellEnums::TriggerEvents value);

	Ref<Aura> get_trigger_aura(int index) const;
	void set_trigger_aura(int index, const Ref<Aura> value);

	Ref<Spell> get_trigger_spell(int index) const;
	void set_trigger_spell(int index, const Ref<Spell> value);

	//Talent
	Ref<Aura> get_talent_required_talent() const;
	void set_talent_required_talent(const Ref<Aura> rank);

	Ref<Spell> get_talent_required_spell() const;
	void set_talent_required_spell(const Ref<Spell> spell);

	//AuraStatAttributes
	int get_aura_stat_attribute_count() const;
	void set_aura_stat_attribute_count(int count);

	int get_aura_stat_attribute_stat(int index) const;
	void set_aura_stat_attribute_stat(int index, const int value);

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
	void removes_expired(Ref<AuraData> aura);
	void removes_dispell(Ref<AuraData> aura);
	void supdate(Ref<AuraData> aura, float delta);

	//EventHandlers
	void son_before_cast(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_started(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void son_spell_cast_success(Ref<AuraData> aura, Ref<SpellCastInfo> info);

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
	void son_class_level_up(Ref<AuraData> data, int value);
	void son_character_level_up(Ref<AuraData> data, int value);

	void son_entity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void son_entity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

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
	void con_class_level_up(Ref<AuraData> data, int value);
	void con_character_level_up(Ref<AuraData> data, int value);

	void con_entity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void con_entity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

	//Equipment
	bool should_deny_equip(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);

	void son_equip_success(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void son_equip_fail(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void con_equip_success(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void con_equip_fail(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	//Calculations / Queries
	void setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	void sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> info);
	void calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info);

	void sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	void sapply_passives_heal_deal(Ref<SpellHealInfo> info);
	void calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	void handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info);

	_FORCE_INLINE_ bool is_talent() const { return _aura_type == SpellEnums::AURA_TYPE_TALENT; }

	String get_name_translated() const;
	String get_description(const int class_level, const int character_level);
	String _get_description(const int class_level, const int character_level);

	Aura();
	~Aura();

protected:
	virtual void _sapply(Ref<AuraApplyInfo> info);
	virtual void _sdeapply(Ref<AuraData> info);
	virtual void _sadd(Ref<AuraData> aura);
	virtual void _sremove(Ref<AuraData> aura);
	virtual void _removes_expired(Ref<AuraData> aura);
	virtual void _removes_dispell(Ref<AuraData> aura);
	virtual void _supdate(Ref<AuraData> aura, float delta);

	virtual void _setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info);

	virtual void _sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	virtual void _sapply_passives_damage_deal(Ref<SpellDamageInfo> info);
	virtual void _calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info);

	virtual void _sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	virtual void _sapply_passives_heal_deal(Ref<SpellHealInfo> info);
	virtual void _calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info);
	virtual void _handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info);

	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_AURA_STATS = 5, //Increase if necessary, should be enough for now
		MAX_TRIGGER_DATA = 5,
	};

	int _id;
	float _time;
	float _tick;
	Ref<AuraGroup> _aura_group;
	Ref<Texture> _icon;
	SpellEnums::AuraType _aura_type;
	bool _is_debuff;
	bool _hide;
	Ref<Spell> _teaches_spell;

	String _text_translation_key;
	String _text_description;
	int ability_scale_data_id;
	int _rank;
	bool _scale_with_level;

	Ref<SpellEffectVisual> _visual_spell_effects;

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

	bool _dispell_enabled;
	int _dispell_count_min;
	int _dispell_count_max;
	int _dispell_aura_types;

	Ref<EntityResourceCostData> _resource_cost;
	Ref<EntityResourceCostData> _resource_give;

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

	//Talent
	Ref<Aura> _talent_required_talent;
	Ref<Spell> _talent_required_spell;
};

#endif
