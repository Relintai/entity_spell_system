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
#include "../../infos/aura_infos.h"

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

class Spell;

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

	float damage_get_scale_for_level(int level) const;
	float heal_get_scale_for_level(int level) const;
	float absorb_get_scale_for_level(int level) const;

	Ref<Spell> get_teaches_spell();
	void set_teaches_spell(const Ref<Spell> &spell);

	//Damage
	bool damage_get_enabled() const;
	void damage_set_enabled(const bool value);

	int damage_get_type() const;

	void damage_set_type(const int value);

	int damage_get_min() const;
	void damage_set_min(const int value);

	int damage_get_max() const;
	void damage_set_max(const int value);

	bool damage_get_can_crit() const;
	void damage_set_can_crit(const bool value);

	void damage_set(const int min, const int max, const bool can_crit);

	//Absorb
	bool absorb_get_enabled() const;
	void absorb_set_enabled(const bool value);

	int absorb_damage_get_type() const;
	void absorb_damage_set_type(const int value);

	int absorb_get_min() const;
	void absorb_set_min(const int value);

	int absorb_get_max() const;
	void absorb_set_max(const int value);

	//Heal
	bool heal_get_enabled() const;
	void heal_set_enabled(const bool value);

	int heal_get_min() const;
	void heal_set_min(const int value);

	int heal_get_max() const;
	void heal_set_max(const int value);

	bool heal_get_can_crit() const;
	void heal_set_can_crit(const bool value);

	void heal_set(const int min, const int max, const bool can_crit);

	//Dispells
	bool dispell_get_enabled() const;
	void dispell_set_enabled(const bool value);

	int dispell_get_count_min() const;
	void dispell_set_count_min(const int value);

	int dispell_get_count_max() const;
	void dispell_set_count_max(const int value);

	int dispell_get_aura_types() const;
	void dispell_set_aura_types(const int value);

	//Resources
	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(const Ref<EntityResourceCostData> &value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(const Ref<EntityResourceCostData> &value);

	Ref<Curve> damage_get_scaling_curve() { return _damage_scaling_curve; }
	void damage_set_scaling_curve(const Ref<Curve> &curve) { _damage_scaling_curve = curve; }

	Ref<Curve> heal_get_scaling_curve() { return _heal_scaling_curve; }
	void heal_set_scaling_curve(const Ref<Curve> &curve) { _heal_scaling_curve = curve; }

	Ref<Curve> absorb_get_scaling_curve() { return _absorb_scaling_curve; }
	void absorb_set_scaling_curve(const Ref<Curve> &curve) { _absorb_scaling_curve = curve; }

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
	int trigger_get_count() const;
	void trigger_set_count(const int count);

	SpellEnums::TriggerNotificationType trigger_get_notification_type(const int index) const;
	void trigger_set_notification_type(const int index, const SpellEnums::TriggerNotificationType value);

	int trigger_get_notification_data(const int index) const;
	void trigger_set_notification_data(const int index, const int value);

	SpellEnums::TriggerType trigger_get_trigger_type(const int index) const;
	void trigger_set_trigger_type(const int index, const SpellEnums::TriggerType value);

	float trigger_get_trigger_type_data(const int index) const;
	void trigger_set_trigger_type_data(const int index, const float value);

	Ref<Spell> trigger_get_spell(const int index) const;
	void trigger_set_spell(const int index, const Ref<Spell> &value);

	//Talent
	Ref<Aura> get_talent_required_talent() const;
	void set_talent_required_talent(const Ref<Aura> rank);

	Ref<Spell> get_talent_required_spell() const;
	void set_talent_required_spell(const Ref<Spell> spell);

	//AuraStatAttributes
	int stat_attribute_get_count() const;
	void stat_attribute_set_count(int count);

	int stat_attribute_get_stat(int index) const;
	void stat_attribute_set_stat(int index, const int value);

	float stat_attribute_get_base_mod(int index) const;
	void stat_attribute_set_base_mod(int index, float value);

	float stat_attribute_get_bonus_mod(int index) const;
	void stat_attribute_set_bonus_mod(int index, float value);

	float stat_attribute_get_percent_mod(int index) const;
	void stat_attribute_set_percent_mod(int index, float value);

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
	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_scast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void notification_sdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data);

	void son_remove(Ref<AuraData> aura);
	void son_remove_expired(Ref<AuraData> aura);
	void son_remove_dispell(Ref<AuraData> aura);

	void notification_sdeath(Ref<AuraData> data);

	void notification_scooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void notification_scooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown);

	void notification_scategory_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);
	void notification_scategory_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);

	void notification_sgcd_started(Ref<AuraData> data, float gcd);
	void notification_sgcd_finished(Ref<AuraData> data);

	void son_physics_process(Ref<AuraData> data);

	void notification_sxp_gained(Ref<AuraData> data, int value);
	void notification_sclass_level_up(Ref<AuraData> data, int value);
	void notification_scharacter_level_up(Ref<AuraData> data, int value);

	void notification_sentity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource);

	//Clientside Event Handlers
	void notification_caura(int what, Ref<AuraData> data);
	void notification_cheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data);
	void notification_ccast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info);
	void notification_cdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data);

	void notification_cdeath(Ref<AuraData> data);

	void notification_ccooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void notification_ccooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown);
	void notification_ccategory_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);
	void notification_ccategory_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown);

	void notification_cgcd_started(Ref<AuraData> data, float gcd);
	void notification_cgcd_finished(Ref<AuraData> data);

	void notification_cxp_gained(Ref<AuraData> data, int value);
	void notification_cclass_level_up(Ref<AuraData> data, int value);
	void notification_ccharacter_level_up(Ref<AuraData> data, int value);

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
	AuraTriggerData _trigger_datas[MAX_TRIGGER_DATA];

	int _aura_stat_attribute_count;
	AuraStatAttribute _aura_stat_attributes[MAX_AURA_STATS];

	SpellEnums::DiminishingReturnCategory _diminishing_category;

	static const int DIMINISHING_RETURN_ROOT_AURA_ID = 1;
	static const int DIMINISHING_RETURN_TIME = 15;

	//Talent
	Ref<Aura> _talent_required_talent;
	Ref<Spell> _talent_required_spell;
};

#endif
