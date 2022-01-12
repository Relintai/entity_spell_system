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

#include "spell.h"

#include "../../entities/auras/aura_data.h"
#include "../../entities/resources/entity_resource_cost_data.h"
#include "../../entities/skills/entity_skill_data.h"
#include "../items/craft_recipe.h"

#include "../../entities/auras/aura_data.h"
#include "../../entities/data/entity_data.h"
#include "../../infos/aura_infos.h"
#include "../auras/aura_group.h"

#include "../../singletons/ess.h"

#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../defines.h"

int Spell::get_id() const {
	return _id;
}
void Spell::set_id(const int value) {
	_id = value;
}

int Spell::spell_type_get() const {
	return _spell_type;
}
void Spell::spell_type_set(int value) {
	_spell_type = value;
}

SpellEnums::SpellCategory Spell::get_spell_category() const {
	return _spell_category;
}
void Spell::set_spell_category(SpellEnums::SpellCategory value) {
	_spell_category = value;
}

bool Spell::get_hide_from_actionbar() const {
	return _hide_from_actionbar;
}
void Spell::set_hide_from_actionbar(const bool value) {
	_hide_from_actionbar = value;
}

float Spell::get_cooldown() const {
	return _cooldown;
}
void Spell::set_cooldown(const float value) {
	_cooldown = value;
}

SpellTargetType Spell::get_target_type() const {
	return _target_type;
}
void Spell::set_target_type(const SpellTargetType value) {
	_target_type = value;
}

TargetRelationType Spell::get_target_relation_type() const {
	return _target_relation_type;
}
void Spell::set_target_relation_type(const TargetRelationType value) {
	_target_relation_type = value;
}

int Spell::get_level() const {
	return _level;
}
void Spell::set_level(const int value) {
	_level = value;
}

int Spell::get_rank() const {
	return _rank;
}
void Spell::set_rank(const int value) {
	_rank = value;
}

bool Spell::get_scale_with_level() const {
	return _scale_with_level;
}
void Spell::set_scale_with_level(const bool value) {
	_scale_with_level = value;
}

Ref<ItemTemplate> Spell::get_item_cost() {
	return _item_cost;
}
void Spell::set_item_cost(const Ref<ItemTemplate> &value) {
	_item_cost = value;
}

Ref<ItemTemplate> Spell::get_required_item() {
	return _required_item;
}
void Spell::set_required_item(const Ref<ItemTemplate> &value) {
	_required_item = value;
}

Ref<EntityResourceCostData> Spell::get_resource_cost() {
	return _resource_cost;
}
void Spell::set_resource_cost(const Ref<EntityResourceCostData> &value) {
	_resource_cost = value;
}

Ref<EntityResourceCostData> Spell::get_resource_give() {
	return _resource_give;
}
void Spell::set_resource_give(const Ref<EntityResourceCostData> &value) {
	_resource_give = value;
}

bool Spell::get_global_cooldown_enabled() const {
	return _global_cooldown_enabled;
}
void Spell::set_global_cooldown_enabled(const bool value) {
	_global_cooldown_enabled = value;
}

bool Spell::get_is_local_spell() const {
	return _is_local_spell;
}
void Spell::set_is_local_spell(const bool value) {
	_is_local_spell = value;
}

Ref<Texture> Spell::get_icon() {
	return _icon;
}
void Spell::set_icon(const Ref<Texture> &value) {
	_icon = Ref<Texture>(value);
}

String Spell::get_text_translation_key() const {
	return _text_translation_key;
}
void Spell::set_text_translation_key(const String &value) {
	_text_translation_key = value;
}

String Spell::get_text_description() const {
	return _text_description;
}
void Spell::set_text_description(const String &value) {
	_text_description = value;
}

Ref<SpellEffectVisual> Spell::get_visual_spell_effects() {
	return _visual_spell_effects;
}
void Spell::set_visual_spell_effects(const Ref<SpellEffectVisual> &value) {
	_visual_spell_effects = value;
}

Ref<CraftRecipe> Spell::get_teaches_craft_recipe() {
	return _teaches_craft_recipe;
}
void Spell::set_teaches_craft_recipe(const Ref<CraftRecipe> &value) {
	_teaches_craft_recipe = value;
}

////    Caster Aura Apply    ////

int Spell::spells_cast_on_caster_num_get() const {
	return _spells_cast_on_caster.size();
}
void Spell::spells_cast_on_caster_num_set(const int value) {
	_spells_cast_on_caster.resize(value);
}

Ref<Spell> Spell::spell_cast_on_caster_get(const int index) {
	ERR_FAIL_INDEX_V(index, _spells_cast_on_caster.size(), Ref<Spell>());

	return _spells_cast_on_caster[index];
}
void Spell::spell_cast_on_caster_set(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _spells_cast_on_caster.size());

	_spells_cast_on_caster.set(index, Ref<Spell>(spell));
}

Vector<Variant> Spell::spells_cast_on_caster_get() {
	VARIANT_ARRAY_GET(_spells_cast_on_caster);
}
void Spell::spells_cast_on_caster_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _spells_cast_on_caster, Spell);
}

////    Target Aura Apply    ////

int Spell::spells_cast_on_target_num_get() const {
	return _spells_cast_on_target.size();
}
void Spell::spells_cast_on_target_num_set(const int value) {
	_spells_cast_on_target.resize(value);
}

Ref<Spell> Spell::spell_cast_on_target_get(const int index) {
	ERR_FAIL_INDEX_V(index, _spells_cast_on_target.size(), Ref<Spell>());

	return _spells_cast_on_target[index];
}
void Spell::spell_cast_on_target_set(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _spells_cast_on_target.size());

	_spells_cast_on_target.set(index, Ref<Spell>(spell));
}

Vector<Variant> Spell::spells_cast_on_target_get() {
	VARIANT_ARRAY_GET(_spells_cast_on_target);
}
void Spell::spells_cast_on_target_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _spells_cast_on_target, Spell);
}

////    Apply Auras On Learn    ////

int Spell::on_learn_cast_spells_num_get() const {
	return _on_learn_cast_spells.size();
}
void Spell::on_learn_cast_spells_num_set(const int value) {
	_on_learn_cast_spells.resize(value);
}

Ref<Spell> Spell::spell_cast_on_learn_get(int index) {
	ERR_FAIL_INDEX_V(index, _on_learn_cast_spells.size(), Ref<Spell>());

	return _on_learn_cast_spells[index];
}
void Spell::spell_cast_on_learn_set(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _on_learn_cast_spells.size());

	_on_learn_cast_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> Spell::spells_cast_on_learn_get() {
	VARIANT_ARRAY_GET(_on_learn_cast_spells);
}
void Spell::spells_cast_on_learn_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _on_learn_cast_spells, Spell);
}

////    Range    ////

bool Spell::range_get_enabled() const {
	return _range_enabled;
}
void Spell::range_set_enabled(const bool value) {
	_range_enabled = value;
}

float Spell::range_get() const {
	return _range;
}
void Spell::range_set(const float value) {
	_range = value;
}

bool Spell::cast_time_get_enabled() const {
	return _cast_time_enabled;
}
void Spell::cast_time_set_enabled(const bool value) {
	_cast_time_enabled = value;
}

float Spell::cast_time_get() const {
	return _cast_time;
}
void Spell::cast_time_set(const float value) {
	_cast_time = value;
}

bool Spell::projectile_get_use_time() const {
	return _projectile_use_time;
}
void Spell::projectile_set_use_time(const bool value) {
	_projectile_use_time = value;
}

float Spell::projectile_get_time() const {
	return _projectile_time;
}
void Spell::projectile_set_time(const float value) {
	_projectile_time = value;
}

bool Spell::projectile_get_use_speed() const {
	return _projectile_use_speed;
}
void Spell::projectile_set_use_speed(const bool value) {
	_projectile_use_speed = value;
}

float Spell::projectile_get_speed() const {
	return _projectile_speed;
}
void Spell::projectile_set_speed(const float value) {
	_projectile_speed = value;
}

Ref<PackedScene> Spell::projectile_get_scene() const {
	return _projectile_scene;
}
void Spell::projectile_set_scene(const Ref<PackedScene> &value) {
	_projectile_scene = value;
}

bool Spell::damage_get_enabled() const {
	return _damage_enabled;
}
void Spell::damage_set_enabled(const bool value) {
	_damage_enabled = value;
}

int Spell::damage_get_type() const {
	return _damage_type;
}
void Spell::damage_set_type(const int value) {
	_damage_type = value;
}

int Spell::damage_get_min() const {
	return _damage_min;
}
void Spell::damage_set_min(const int value) {
	_damage_min = value;
}

int Spell::damage_get_max() const {
	return _damage_max;
}
void Spell::damage_set_max(const int value) {
	_damage_max = value;
}

int Spell::damage_get_scale_stat() const {
	return _damage_scale_stat;
}
void Spell::damage_set_scale_stat(const int value) {
	_damage_scale_stat = value;
}

float Spell::damage_get_scale_coeff() const {
	return _damage_scale_coeff;
}
void Spell::damage_set_scale_coeff(const float value) {
	_damage_scale_coeff = value;
}

bool Spell::heal_get_enabled() const {
	return _heal_enabled;
}
void Spell::heal_set_enabled(const bool value) {
	_heal_enabled = value;
}

int Spell::heal_get_min() const {
	return _heal_min;
}
void Spell::heal_set_min(const int value) {
	_heal_min = value;
}

int Spell::heal_get_max() const {
	return _heal_max;
}
void Spell::heal_set_max(const int value) {
	_heal_max = value;
}

int Spell::heal_get_scale_stat() const {
	return _heal_scale_stat;
}
void Spell::heal_set_scale_stat(const int value) {
	_heal_scale_stat = value;
}

float Spell::heal_get_scale_coeff() const {
	return _heal_scale_coeff;
}
void Spell::heal_set_scale_coeff(const float value) {
	_heal_scale_coeff = value;
}

bool Spell::dispell_get_enabled() const {
	return _dispell_enabled;
}
void Spell::dispell_set_enabled(const bool value) {
	_dispell_enabled = value;
}

int Spell::dispell_get_count_min() const {
	return _dispell_count_min;
}
void Spell::dispell_set_count_min(const int value) {
	_dispell_count_min = value;
}

int Spell::dispell_get_count_max() const {
	return _dispell_count_max;
}
void Spell::dispell_set_count_max(const int value) {
	_dispell_count_max = value;
}

int Spell::dispell_get_aura_types() const {
	return _dispell_aura_types;
}
void Spell::dispell_set_aura_types(const int value) {
	_dispell_aura_types = value;
}

bool Spell::get_needs_target() const {
	return _needs_target;
}
void Spell::set_needs_target(const bool value) {
	_needs_target = value;
}

bool Spell::get_can_move_while_casting() const {
	return _can_move_while_casting;
}
void Spell::set_can_move_while_casting(const bool value) {
	_can_move_while_casting = value;
}

bool Spell::get_interrupt_enabled() const {
	return _interrupt_enabled;
}
void Spell::set_interrupt_enabled(const bool value) {
	_interrupt_enabled = value;
}

float Spell::get_interrupt_time() const {
	return _interrupt_time;
}
void Spell::set_interrupt_time(const float value) {
	_interrupt_time = value;
}

bool Spell::get_is_aoe() const {
	return _is_aoe;
}
void Spell::set_is_aoe(const bool value) {
	_is_aoe = value;
}

SpellAOETargetType Spell::get_aoe_target_type() const {
	return _aoe_targetType;
}
void Spell::set_aoe_target_type(const SpellAOETargetType value) {
	_aoe_targetType = value;
}

SpellEnums::ColliderType Spell::get_aoe_collider_type() const {
	return _aoe_colliderType;
}
void Spell::set_aoe_collider_type(const SpellEnums::ColliderType value) {
	_aoe_colliderType = value;
}

float Spell::get_aoe_radius() const {
	return _aoe_radius;
}
void Spell::set_aoe_radius(float value) {
	_aoe_radius = value;
}

Vector3 Spell::get_aoe_box_extents() const {
	return _aoe_box_extents;
}
void Spell::set_aoe_box_extents(Vector3 value) {
	_aoe_box_extents = value;
}

int Spell::get_spell_cooldown_mainpulation_data_count() const {
	return _spell_cooldown_mainpulation_data_count;
}
void Spell::set_spell_cooldown_mainpulation_data_count(int value) {
	_spell_cooldown_mainpulation_data_count = value;
}

int Spell::get_training_cost() const {
	return _training_cost;
}
void Spell::set_training_cost(const int value) {
	_training_cost = value;
}

Ref<Spell> Spell::get_training_required_spell() {
	return _training_required_spell;
}
void Spell::set_training_required_spell(const Ref<Spell> &spell) {
	_training_required_spell = spell;
}

Ref<EntitySkillData> Spell::get_training_required_skill() {
	return _training_required_skill;
}
void Spell::set_training_required_skill(const Ref<EntitySkillData> &skill) {
	_training_required_skill = skill;
}

int Spell::get_training_required_skill_level() const {
	return _training_required_skill_level;
}
void Spell::set_training_required_skill_level(const int value) {
	_training_required_skill_level = value;
}

// Aura

bool Spell::aura_get_permanent() const {
	return _aura_permanent;
}
void Spell::aura_set_permanent(const bool value) {
	_aura_permanent = value;
}

float Spell::aura_get_time() const {
	return _aura_time;
}
void Spell::aura_set_time(const float value) {
	_aura_time = value;
}

float Spell::aura_get_tick() const {
	return _aura_tick;
}
void Spell::aura_set_tick(const float value) {
	_aura_tick = value;
}

Ref<AuraGroup> Spell::aura_get_aura_group() {
	return _aura_group;
}
void Spell::aura_set_aura_group(const Ref<AuraGroup> &value) {
	_aura_group = value;
}

bool Spell::aura_get_is_debuff() const {
	return _aura_is_debuff;
}
void Spell::aura_set_is_debuff(const bool value) {
	_aura_is_debuff = value;
}

SpellEnums::AuraType Spell::aura_get_aura_type() const {
	return _aura_type;
}
void Spell::aura_set_aura_type(SpellEnums::AuraType value) {
	_aura_type = value;
}

bool Spell::aura_get_scale_with_level() const {
	return _aura_scale_with_level;
}
void Spell::aura_set_scale_with_level(const bool value) {
	_aura_scale_with_level = value;
}

String Spell::aura_get_text_translation_key() const {
	return _aura_text_translation_key;
}
void Spell::aura_set_text_translation_key(const String &value) {
	_aura_text_translation_key = value;
}

String Spell::aura_get_text_description() const {
	return _aura_text_description;
}
void Spell::aura_set_text_description(const String description) {
	_aura_text_description = description;
}

bool Spell::aura_get_hide() const {
	return _aura_hide;
}
void Spell::aura_set_hide(const bool value) {
	_aura_hide = value;
}

Ref<SpellEffectVisual> Spell::aura_get_visual_spell_effects() {
	return _aura_visual_spell_effects;
}
void Spell::aura_set_visual_spell_effects(const Ref<SpellEffectVisual> &value) {
	_aura_visual_spell_effects = value;
}

int Spell::aura_get_ability_scale_data_id() const {
	return _aura_ability_scale_data_id;
}
void Spell::aura_set_ability_scale_data_id(const int value) {
	_aura_ability_scale_data_id = value;
}

float Spell::aura_damage_get_scale_for_level(const int level) const {
	//return this->getDamageLevelScaling()->Evaluate((float)(level));
	return 1;
}
float Spell::aura_heal_get_scale_for_level(const int level) const {
	//return this->getHealLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Spell::aura_absorb_get_scale_for_level(const int level) const {
	//return this->getAbsorbLevelScaling()->Evaluate((float)(level));
	return 1;
}

bool Spell::aura_diminishing_return_enabled_get() const {
	return _aura_diminishing_return_enabled;
}
void Spell::aura_diminishing_return_enabled_set(const bool value) {
	_aura_diminishing_return_enabled = value;
}

int Spell::aura_diminishing_return_category_get() const {
	return _aura_diminishing_return_category;
}
void Spell::aura_diminishing_return_category_set(const int value) {
	_aura_diminishing_return_category = value;
}

Ref<Spell> Spell::aura_get_teaches_spell() {
	return _aura_teaches_spell;
}
void Spell::aura_set_teaches_spell(const Ref<Spell> &spell) {
	_aura_teaches_spell = spell;
}

/*
void Spell::SetScalingData(AbilityScalingData *scalingData) {
scalingData->getDamageCurve();
scalingData->getAbsorbCurve();
scalingData->getHealingCurve();
}*/
/*
void Spell::OnAuraAbilityScalingDataLoaded(AbilityScalingDataLoaderHelper *h) {
this->SetScalingData(h->getData());
}
*/

//Damage
bool Spell::aura_damage_get_enabled() const {
	return _aura_damage_enabled;
}
void Spell::aura_damage_set_enabled(const bool value) {
	_aura_damage_enabled = value;
}

int Spell::aura_damage_get_type() const {
	return _aura_damage_type;
}

void Spell::aura_damage_set_type(const int value) {
	_aura_damage_type = value;
}

int Spell::aura_damage_get_min() const {
	return _aura_damage_min;
}
void Spell::aura_damage_set_min(const int value) {
	_aura_damage_min = value;
}

int Spell::aura_damage_get_max() const {
	return _aura_damage_max;
}
void Spell::aura_damage_set_max(const int value) {
	_aura_damage_max = value;
}

bool Spell::aura_damage_get_can_crit() const {
	return _aura_damage_can_crit;
}
void Spell::aura_damage_set_can_crit(const bool value) {
	_aura_damage_can_crit = value;
}

void Spell::aura_damage_set(const int min, const int max, const bool can_crit) {
	aura_damage_set_enabled(true);
	aura_damage_set_min(min);
	aura_damage_set_max(max);
	aura_damage_set_can_crit(can_crit);
}

//Absorb
bool Spell::aura_absorb_get_enabled() const {
	return _aura_absorb_enabled;
}
void Spell::aura_absorb_set_enabled(const bool value) {
	_aura_absorb_enabled = value;
}

int Spell::aura_absorb_damage_get_type() const {
	return _aura_absorb_damage_type;
}

void Spell::aura_absorb_damage_set_type(const int value) {
	_aura_absorb_damage_type = value;
}

int Spell::aura_absorb_get_min() const {
	return _aura_absorb_min;
}
void Spell::aura_absorb_set_min(const int value) {
	_aura_absorb_min = value;
}

int Spell::aura_absorb_get_max() const {
	return _aura_absorb_max;
}
void Spell::aura_absorb_set_max(const int value) {
	_aura_absorb_max = value;
}

//Heal
bool Spell::aura_heal_get_enabled() const {
	return _aura_heal_enabled;
}
void Spell::aura_heal_set_enabled(const bool value) {
	_aura_heal_enabled = value;
}

int Spell::aura_heal_get_min() const {
	return _aura_heal_min;
}
void Spell::aura_heal_set_min(const int value) {
	_aura_heal_min = value;
}

int Spell::aura_heal_get_max() const {
	return _aura_heal_max;
}
void Spell::aura_heal_set_max(const int value) {
	_aura_heal_max = value;
}

bool Spell::aura_heal_get_can_crit() const {
	return _aura_heal_can_crit;
}
void Spell::aura_heal_set_can_crit(const bool value) {
	_aura_heal_can_crit = value;
}

void Spell::aura_heal_set(const int min, const int max, const bool can_crit) {
	aura_heal_set_enabled(true);
	aura_heal_set_min(min);
	aura_heal_set_max(max);
	aura_heal_set_can_crit(can_crit);
}

//Dispell
bool Spell::aura_dispell_get_enabled() const {
	return _aura_dispell_enabled;
}
void Spell::aura_dispell_set_enabled(const bool value) {
	_aura_dispell_enabled = value;
}

int Spell::aura_dispell_get_count_min() const {
	return _aura_dispell_count_min;
}
void Spell::aura_dispell_set_count_min(const int value) {
	_aura_dispell_count_min = value;
}

int Spell::aura_dispell_get_count_max() const {
	return _aura_dispell_count_max;
}
void Spell::aura_dispell_set_count_max(const int value) {
	_aura_dispell_count_max = value;
}

int Spell::aura_dispell_get_aura_types() const {
	return _aura_dispell_aura_types;
}
void Spell::aura_dispell_set_aura_types(const int value) {
	_aura_dispell_aura_types = value;
}

Ref<EntityResourceCostData> Spell::aura_get_resource_cost() {
	return _aura_resource_cost;
}
void Spell::aura_set_resource_cost(const Ref<EntityResourceCostData> &value) {
	_aura_resource_cost = value;
}

Ref<EntityResourceCostData> Spell::aura_get_resource_give() {
	return _aura_resource_give;
}
void Spell::aura_set_resource_give(const Ref<EntityResourceCostData> &value) {
	_aura_resource_give = value;
}

//////     Triggers      ///////

int Spell::aura_trigger_get_count() const {
	return _aura_trigger_count;
}

void Spell::aura_trigger_set_count(const int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_TRIGGER_DATA);

	_aura_trigger_count = count;
}

SpellEnums::TriggerNotificationType Spell::aura_trigger_get_notification_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA);

	return _aura_trigger_datas[index].notification_type;
}

void Spell::aura_trigger_set_notification_type(const int index, const SpellEnums::TriggerNotificationType value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].notification_type = value;
}

int Spell::aura_trigger_get_notification_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, 0);

	return _aura_trigger_datas[index].notification_data;
}

void Spell::aura_trigger_set_notification_data(const int index, const int value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].notification_data = value;
}

SpellEnums::TriggerType Spell::aura_trigger_get_trigger_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, SpellEnums::TRIGGER_TYPE_NONE);

	return _aura_trigger_datas[index].trigger_type;
}

void Spell::aura_trigger_set_trigger_type(const int index, const SpellEnums::TriggerType value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].trigger_type = value;
}

float Spell::aura_trigger_get_trigger_type_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, 0);

	return _aura_trigger_datas[index].trigger_type_data;
}

void Spell::aura_trigger_set_trigger_type_data(const int index, const float value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].trigger_type_data = value;
}

Ref<Spell> Spell::aura_trigger_get_spell(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, Ref<Spell>());

	return _aura_trigger_datas[index].spell;
}

void Spell::aura_trigger_set_spell(const int index, const Ref<Spell> &value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].spell = value;
}

////    Talent    ////
Ref<Spell> Spell::aura_get_talent_required_talent() const {
	return _aura_talent_required_talent;
}
void Spell::aura_set_talent_required_talent(const Ref<Spell> rank) {
	_aura_talent_required_talent = rank;
}

Ref<Spell> Spell::aura_get_talent_required_spell() const {
	return _aura_talent_required_talent;
}
void Spell::aura_set_talent_required_spell(const Ref<Spell> spell) {
	_aura_talent_required_spell = spell;
}

////// Aura Stat Attributes //////

int Spell::aura_stat_attribute_get_count() const {
	return _aura_stat_attribute_count;
}
void Spell::aura_stat_attribute_set_count(int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_AURA_STATS);

	_aura_stat_attribute_count = count;
}

int Spell::aura_stat_attribute_get_stat(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].stat;
}
void Spell::aura_stat_attribute_set_stat(int index, const int value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].stat = value;
}

float Spell::aura_stat_attribute_get_base_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].base_mod;
}
void Spell::aura_stat_attribute_set_base_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].base_mod = value;
}

float Spell::aura_stat_attribute_get_bonus_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].bonus_mod;
}
void Spell::aura_stat_attribute_set_bonus_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].bonus_mod = value;
}

float Spell::aura_stat_attribute_get_percent_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].percent_mod;
}
void Spell::aura_stat_attribute_set_percent_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].percent_mod = value;
}

////    Spell System    ////

void Spell::cast_starts_simple(Entity *caster, float spell_scale) {
	ERR_FAIL_COND(!caster || !INSTANCE_VALIDATE(caster));

	Ref<SpellCastInfo> info = Ref<SpellCastInfo>(memnew(SpellCastInfo()));

	info->caster_set(caster);
	info->target_set(caster->gets_target());
	info->has_cast_time_set(cast_time_get_enabled());
	info->cast_time_set(cast_time_get());
	info->spell_scale_set(spell_scale);
	info->set_spell(Ref<Spell>(this));

	cast_starts(info);
}

void Spell::cast_interrupts_simple(Entity *caster) {
	ERR_FAIL_COND(!caster || !INSTANCE_VALIDATE(caster));

	Ref<SpellCastInfo> info(memnew(SpellCastInfo()));

	info->caster_set(caster);
	info->set_spell(Ref<Spell>(this));

	cast_interrupts(info);
}

void Spell::cast_starts_triggered_simple(Entity *caster) {
	ERR_FAIL_COND(!caster || !INSTANCE_VALIDATE(caster));

	Ref<SpellCastInfo> info(memnew(SpellCastInfo()));

	info->caster_set(caster);
	info->set_spell(Ref<Spell>(this));

	cast_starts_triggered(info);
}

void Spell::aura_sapply_simple(Entity *caster, Entity *target, float spell_scale) {
	ERR_FAIL_COND(caster == NULL || target == NULL);

	Ref<AuraApplyInfo> info(memnew(AuraApplyInfo(caster, target, spell_scale, this)));

	aura_sapply(info);
}

//Script methods

void Spell::cast_starts(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//Auto self cast. Note: Remove needs_target, and skip this if spell should only target enemies.
	if (info->target_get() == NULL) {
		info->target_set(info->caster_get());
	}

	if (has_method("_cast_starts")) {
		call("_cast_starts", info);
	}
}

void Spell::cast_starts_triggered(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_cast_starts_triggered")) {
		call("_cast_starts_triggered", info);
	}
}

void Spell::cast_interrupts(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_cast_interrupts")) {
		call("_cast_interrupts", info);
	}
}

void Spell::cast_finishs(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_cast_finishs")) {
		call("_cast_finishs", info);
	}
}

void Spell::aura_sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply", info);
}

void Spell::aura_sdeapply(Ref<AuraData> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sdeapply", info);
}

void Spell::aura_sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_sadd", aura);
}

void Spell::aura_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_sremove", aura);
}

void Spell::aura_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_removes_expired", aura);
}

void Spell::aura_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_removes_dispell", aura);
}

void Spell::aura_supdate(Ref<AuraData> aura, float delta) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_supdate", aura, delta);
}

//eventhandlers

void Spell::son_cast_player_moved(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_player_moved")) {
		call("_son_cast_player_moved", info);
	}
}

void Spell::son_cast_damage_received(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_damage_received")) {
		call("_son_cast_damage_received", info);
	}
}

void Spell::son_spell_hit(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_spell_hit")) {
		call("_son_spell_hit", info);
	}
}

void Spell::son_physics_process(Ref<SpellCastInfo> info, float delta) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_physics_process")) {
		call("_son_physics_process", info, delta);
	}
}

void Spell::notification_scast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_scast")) {
		call("_notification_scast", what, info);
	}
}

void Spell::notification_ccast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_ccast")) {
		call("_notification_ccast", what, info);
	}
}

void Spell::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);
}
void Spell::notification_sheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, aura, data);
}
void Spell::notification_aura_scast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_aura_scast"))
		call("_notification_aura_scast", what, aura, info);
}
void Spell::notification_sdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, aura, data);
}

void Spell::son_remove_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove_expired"))
		call("_son_remove_expired", aura);
}

void Spell::son_remove(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove"))
		call("_son_remove", aura);
}

void Spell::son_remove_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove_dispell"))
		call("_son_remove_dispell", aura);
}

void Spell::notification_sdeath(Ref<AuraData> data) {
	if (has_method("_notification_sdeath"))
		call("_notification_sdeath", data);
}

void Spell::notification_scooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scooldown_added"))
		call("_notification_scooldown_added", data, id, value);
}
void Spell::notification_scooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scooldown_removed"))
		call("_notification_scooldown_removed", data, id, value);
}

void Spell::notification_scategory_cooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scategory_cooldown_added"))
		call("_notification_scategory_cooldown_added", data, id, value);
}
void Spell::notification_scategory_cooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scategory_cooldown_removed"))
		call("_notification_scategory_cooldown_removed", data, id, value);
}

void Spell::notification_sgcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sgcd_started"))
		call("_notification_sgcd_started", data, gcd);
}
void Spell::notification_sgcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", data);
}

void Spell::son_physics_process_aura(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_physics_process_aura"))
		call("_son_physics_process_aura", data);
}

void Spell::notification_sxp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sxp_gained"))
		call("_notification_sxp_gained", data, value);
}

void Spell::notification_slevel_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_slevel_up"))
		call("_notification_slevel_up", data, value);
}

void Spell::notification_sentity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_sentity_resource_added"))
		call("_notification_sentity_resource_added", data, resource);
}
void Spell::notification_sentity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_sentity_resource_removed"))
		call("_notification_sentity_resource_removed", data, resource);
}

void Spell::notification_caura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_caura"))
		call("_notification_caura", what, data);
}
void Spell::notification_cheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cheal"))
		call("_notification_cheal", what, aura, data);
}
void Spell::notification_aura_ccast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_aura_ccast"))
		call("_notification_aura_ccast", what, aura, info);
}
void Spell::notification_cdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cdamage"))
		call("_notification_cdamage", what, aura, data);
}

void Spell::notification_cdeath(Ref<AuraData> data) {
	if (has_method("_notification_cdeath"))
		call("_notification_cdeath", data);
}

void Spell::notification_ccooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccooldown_added"))
		call("_notification_ccooldown_added", data, id, value);
}
void Spell::notification_ccooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccooldown_removed"))
		call("_notification_ccooldown_removed", data, id, value);
}
void Spell::notification_ccategory_cooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccategory_cooldown_added"))
		call("_notification_ccategory_cooldown_added", data, id, value);
}
void Spell::notification_ccategory_cooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccategory_cooldown_removed"))
		call("_notification_ccategory_cooldown_removed", data, id, value);
}

void Spell::notification_cgcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cgcd_started"))
		call("_notification_cgcd_started", data, gcd);
}
void Spell::notification_cgcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cgcd_finished"))
		call("_notification_cgcd_finished", data);
}

void Spell::notification_cxp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cxp_gained"))
		call("_notification_cxp_gained", data, value);
}

void Spell::notification_clevel_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_clevel_up"))
		call("_notification_clevel_up", data, value);
}

void Spell::notification_centity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_centity_resource_added"))
		call("_notification_centity_resource_added", data, resource);
}
void Spell::notification_centity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_centity_resource_removed"))
		call("_notification_centity_resource_removed", data, resource);
}

//Equipment

bool Spell::equip_should_deny(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!data.is_valid(), false);

	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", data, equip_slot, item))
			return true;

	return false;
}

void Spell::equip_son_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_son_success"))
		call("_equip_son_success", data, equip_slot, item, old_item, bag_slot);
}
void Spell::equip_son_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", data, equip_slot, item, old_item, bag_slot);
}

void Spell::equip_con_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_con_success"))
		call("_equip_con_success", data, equip_slot, item, old_item, bag_slot);
}
void Spell::equip_con_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", data, equip_slot, item, old_item, bag_slot);
}

//Calculations / Queries

void Spell::calculate_initial_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->receiver_get() == NULL);

	call("_calculate_initial_damage", data);
}

void Spell::handle_spell_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->receiver_get() == NULL);

	call("_handle_spell_damage", data);
}

void Spell::calculate_initial_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->receiver_get() == NULL);

	call("_calculate_initial_heal", data);
}

void Spell::handle_spell_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->receiver_get() == NULL);

	call("_handle_spell_heal", data);
}

void Spell::handle_projectile(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	call("_handle_projectile", info);
}

void Spell::handle_effect(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	call("_handle_effect", info);
}

void Spell::handle_gcd(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_global_cooldown_enabled && _cast_time_enabled) {
		float gcd = info->caster_get()->stat_gets_current(ESS::get_singleton()->stat_get_id("Global Cooldown"));

		info->caster_get()->gcd_starts(gcd);
	}
}
void Spell::handle_cooldown(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_cooldown > 0.00001) {
		info->caster_get()->cooldown_adds(_id, _cooldown);
	}
}

void Spell::setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!data.is_valid() || !info.is_valid());

	//always exists
	call("_setup_aura_data", data, info);
}

void Spell::aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply_passives_damage_receive", info);
}

void Spell::aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply_passives_damage_deal", info);
}

void Spell::aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_aura_calculate_initial_damage", aura_data, info);
}

void Spell::handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_handle_aura_damage", aura_data, info);
}

void Spell::aura_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_aura_sapply_passives_heal_receive", data);
}

void Spell::aura_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_aura_sapply_passives_heal_deal", data);
}

void Spell::aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_aura_calculate_initial_heal", aura_data, info);
}

void Spell::handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura_data.is_valid() || !data.is_valid());

	//always exists
	call("_handle_aura_heal", aura_data, data);
}

String Spell::get_name_translated() const {
	if (_text_translation_key != "") {
		return tr(_text_translation_key);
	}

	return get_name();
}

String Spell::get_description(const int class_level, const int character_level) {
	return call("_get_description", class_level, character_level);
}

String Spell::_get_description(const int class_level, const int character_level) {
	String str;

	if (_text_translation_key != "") {
		str = tr(_text_translation_key + "_DESC");
	}

	str = _text_description;

	int pos = str.find_char('%');

	while (pos > 0) {
		if (pos == str.size() - 1)
			break;

#if GODOT4
		char32_t o = str[pos + 1];
#else
		CharType o = str[pos + 1];
#endif

		if (o == '#' || o == '$' || o == '%') {
			int nsp = str.find_char(' ', pos + 1);

			if (pos < 0)
				break;

			String prop = str.substr(pos + 2, nsp - pos - 2);
			StringName psm = prop;
			bool valid = false;
			Variant value = get(psm, &valid);

			if (valid) {
				if (o == '#') {
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, class_level / static_cast<float>(ESS::get_singleton()->get_max_class_level()));

					value = static_cast<int>(value);
				}

				if (o == '$') {
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, character_level / static_cast<float>(ESS::get_singleton()->get_max_character_level()));

					value = static_cast<int>(value);
				}

				str = str.replace(str.substr(pos, nsp - pos) + " ", value);
			}
		}

		pos = str.find_char('%', pos + 1);
	}

	return str;
}

String Spell::aura_get_name_translated() const {
	if (_aura_text_translation_key != "") {
		return tr(_aura_text_translation_key);
	}

	return get_name();
}

String Spell::aura_get_description(const int class_level, const int character_level) {
	return call("_aura_get_description", class_level, character_level);
}

String Spell::_aura_get_description(const int class_level, const int character_level) {
	String str;

	if (_aura_text_translation_key != "") {
		str = tr(_aura_text_translation_key + "_DESC");
	}

	str = _aura_text_description;

	int pos = str.find_char('%');

	while (pos > 0) {
		if (pos == str.size() - 1)
			break;

#if GODOT4
		char32_t o = str[pos + 1];
#else
		CharType o = str[pos + 1];
#endif

		if (o == '#' || o == '$' || o == '%') {
			int nsp = str.find_char(' ', pos + 1);

			if (pos < 0)
				break;

			String prop = str.substr(pos + 2, nsp - pos - 2);
			StringName psm = prop;
			bool valid = false;
			Variant value = get(psm, &valid);

			if (valid) {
				if (o == '#') {
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, class_level / static_cast<float>(ESS::get_singleton()->get_max_class_level()));

					value = static_cast<int>(value);
				}

				if (o == '$') {
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, character_level / static_cast<float>(ESS::get_singleton()->get_max_character_level()));

					value = static_cast<int>(value);
				}

				str = str.replace(str.substr(pos, nsp - pos) + " ", value);
			}
		}

		pos = str.find_char('%', pos + 1);
	}

	return str;
}

Spell::Spell() {
	PLAYER_HIT_RADIUS = (float)0.5;

	_id = 1;
	_spell_type = SpellEnums::SPELL_TYPE_NONE;
	_spell_category = SpellEnums::SPELL_CATEGORY_NORMAL;

	_hide_from_actionbar = false;

	_cooldown = 0;
	_cast_time = 0;

	_target_type = SpellTargetType::SPELL_TARGET_TYPE_TARGET;
	_target_relation_type = TargetRelationType::TARGET_ENEMY;

	_level = 1;
	_rank = 0;
	_scale_with_level = ESS::get_singleton()->get_scale_spells_by_default();

	_global_cooldown_enabled = true;
	_is_local_spell = false;

	_range_enabled = false;
	_range = 0;

	_damage_enabled = false;
	_damage_type = 0;
	_damage_min = 0;
	_damage_max = 0;
	_damage_scale_stat = 0;
	_damage_scale_coeff = 0;

	_heal_enabled = false;
	_heal_min = 0;
	_heal_max = 0;
	_heal_scale_stat = 0;
	_heal_scale_coeff = 0;

	_dispell_enabled = false;
	_dispell_count_min = 0;
	_dispell_count_max = 0;
	_dispell_aura_types = 0;

	_cast_time_enabled = false;
	_cast_time = 0;

	_needs_target = false;
	_can_move_while_casting = false;

	_interrupt_enabled = false;
	_interrupt_time = 0;

	_is_aoe = false;
	_aoe_targetType = SpellAOETargetType::SPELL_AOE_TARGET_TYPE_CASTER;
	_aoe_colliderType = SpellEnums::COLLIDER_TYPE_NONE;
	_aoe_radius = 0;

	_spell_cooldown_mainpulation_data_count = 0;

	_training_cost = 0;
	_training_required_skill_level = 0;

	_projectile_use_time = false;
	_projectile_time = 0;
	_projectile_use_speed = false;
	_projectile_speed = 0;

	_aura_permanent = false;
	_aura_ability_scale_data_id = 1;
	_aura_time = 0;
	_aura_tick = 0;
	_aura_type = SpellEnums::AURA_TYPE_NONE;
	_aura_is_debuff = false;
	_aura_hide = false;

	_aura_scale_with_level = ESS::get_singleton()->get_scale_spells_by_default();

	_aura_damage_enabled = false;
	_aura_damage_type = 0;
	_aura_damage_min = 0;
	_aura_damage_max = 0;
	_aura_damage_can_crit = false;

	_aura_absorb_enabled = false;
	_aura_absorb_damage_type = 0;
	_aura_absorb_min = 0;
	_aura_absorb_max = 0;

	_aura_heal_enabled = false;
	_aura_heal_min = 0;
	_aura_heal_max = 0;

	_aura_heal_can_crit = false;

	_aura_dispell_enabled = false;
	_aura_dispell_count_min = 0;
	_aura_dispell_count_max = 0;
	_aura_dispell_aura_types = 0;

	_aura_add_states = 0;
	_aura_remove_effects_with_states = 0;
	_aura_supress_states = 0;

	_aura_stat_attribute_count = 0;
	_aura_trigger_count = 0;

	_aura_diminishing_return_enabled = false;
	_aura_diminishing_return_category = 0;
}

Spell::~Spell() {
	_spells_cast_on_caster.clear();
	_spells_cast_on_target.clear();
	_on_learn_cast_spells.clear();

	_item_cost.unref();
	_required_item.unref();

	_resource_cost.unref();
	_resource_give.unref();

	_icon.unref();

	_visual_spell_effects.unref();

	_teaches_craft_recipe.unref();
	_training_required_spell.unref();
	_training_required_skill.unref();

	_projectile_scene.unref();

	_aura_teaches_spell.unref();

	_aura_visual_spell_effects.unref();

	_aura_damage_scaling_curve.unref();
	_aura_absorb_scaling_curve.unref();
	_aura_heal_scaling_curve.unref();

	for (int i = 0; i < MAX_TRIGGER_DATA; ++i) {
		_aura_trigger_datas[i].spell.unref();
	}

	_aura_talent_required_talent.unref();
	_aura_talent_required_spell.unref();
}

void Spell::_cast_starts(Ref<SpellCastInfo> info) {
	if (info->caster_get()->cast_is_castings()) {
		return;
	}

	if ((get_global_cooldown_enabled() && info->caster_get()->gcd_hass()) ||
			info->caster_get()->category_cooldown_hass(spell_type_get()) ||
			info->caster_get()->cooldown_hass(get_id())) {
		return;
	}

	if (!info->caster_get()->spell_hass_id(get_id())) {
		return;
	}

	if (cast_time_get_enabled()) {
		info->caster_get()->cast_starts(info);
		return;
	}

	info->caster_get()->cast_spell_successs(info);

	info->target_get()->notification_scast(SpellEnums::NOTIFICATION_CAST_FINISHED_TARGET, info);

	//if (get_projectile().is_valid()) {
	//	handle_projectile(info);
	//} else {
	//	handle_effect(info);
	//}

	handle_cooldown(info);

	handle_gcd(info);
}

void Spell::_cast_finishs(Ref<SpellCastInfo> info) {
	info->caster_get()->notification_scast(SpellEnums::NOTIFICATION_CAST_FINISHED, info);
	info->caster_get()->cast_spell_successs(info);

	if (INSTANCE_VALIDATE(info->target_get())) {
		info->target_get()->notification_scast(SpellEnums::NOTIFICATION_CAST_FINISHED_TARGET, info);
	}

	//if (get_projectile().is_valid()) {
	//	handle_projectile(info);
	//} else {
	//	handle_effect(info);
	//}

	handle_cooldown(info);
}

void Spell::_son_cast_player_moved(Ref<SpellCastInfo> info) {
	if (get_can_move_while_casting()) {
		info->caster_get()->cast_fails();
	}
}

void Spell::_son_spell_hit(Ref<SpellCastInfo> info) {
	handle_effect(info);
}

void Spell::_calculate_initial_damage(Ref<SpellDamageInfo> data) {
	Math::randomize();

	data->damage_set(damage_get_min() + (damage_get_max() - damage_get_min()) * Math::randf());
}

void Spell::_handle_spell_damage(Ref<SpellDamageInfo> data) {
	calculate_initial_damage(data);

	data->dealer_get()->sdeal_damage_to(data);
}

void Spell::_calculate_initial_heal(Ref<SpellHealInfo> data) {
	Math::randomize();

	data->heal_set(heal_get_min() + (heal_get_max() - heal_get_min()) * Math::randf());
}

void Spell::_handle_spell_heal(Ref<SpellHealInfo> data) {
	calculate_initial_heal(data);

	data->dealer_get()->sdeal_heal_to(data);
}

void Spell::_handle_projectile(Ref<SpellCastInfo> info) {
	if (_projectile_scene.is_valid()) {
		Node *projectile = _projectile_scene->instance();

		Node *p = info->caster_get()->get_parent();

		ERR_FAIL_COND(!INSTANCE_VALIDATE(p));

		p->add_child(projectile);

		if (projectile->has_method("setup_projectile"))
			projectile->call("setup_projectile", info);
	}
}

void Spell::_handle_effect(Ref<SpellCastInfo> info) {
	/*
#		var ok : bool = false

#		if (target_relation_type & TARGET_SELF):
#			ok = true

#		if not ok and (target_relation_type & TARGET_ENEMY and info.target is Entity):
#			ok = true
#
#		if not ok and (target_relation_type & TARGET_FRIENDLY and info.target is Player):
#			ok = true

#		if not ok:
#			return
			*/

	bool has_target = INSTANCE_VALIDATE(info->target_get());

	if (_target_type == SPELL_TARGET_TYPE_TARGET) {
		if (!has_target)
			return;
	} else if (_target_type == SPELL_TARGET_TYPE_SELF) {
		info->target_set(info->caster_get());
	}

	if (_damage_enabled && has_target) {
		Ref<SpellDamageInfo> sdi;
		sdi.instance();

		sdi->spell_source_set(Ref<Spell>(this));
		sdi->dealer_set(info->caster_get());
		sdi->receiver_set(info->target_get());

		handle_spell_damage(sdi);
	}

	if (is_aura()) {
		Ref<AuraData> ad;

		if (aura_get_aura_group().is_valid()) {
			ad = info->target_get()->aura_gets_with_group_by_bind(info->caster_get(), aura_get_aura_group());
		} else {
			ad = info->target_get()->aura_gets_by(info->caster_get(), get_id());
		}

		if (ad.is_valid()) {
			info->target_get()->aura_removes_exact(ad);
		}

		Ref<AuraApplyInfo> aai;
		aai.instance();

		aai->caster_set(info->caster_get());
		aai->target_set(info->target_get());
		aai->spell_scale_set(1);
		aai->set_aura(Ref<Spell>(this));

		aura_sapply(aai);
	}

	for (int i = 0; i < _spells_cast_on_caster.size(); ++i) {
		Ref<Spell> spell = _spells_cast_on_caster.get(i);

		if (!spell.is_valid()) {
			continue;
		}

		Ref<SpellCastInfo> sci;
		sci.instance();

		sci->caster_set(info->caster_get());
		sci->target_set(info->caster_get());
		sci->has_cast_time_set(spell->cast_time_get_enabled());
		sci->cast_time_set(spell->cast_time_get());
		sci->spell_scale_set(info->spell_scale_get());
		sci->set_spell(spell);

		spell->cast_starts(sci);
	}

	if (has_target) {
		for (int i = 0; i < _spells_cast_on_target.size(); ++i) {
			Ref<Spell> spell = _spells_cast_on_target.get(i);

			if (!spell.is_valid()) {
				continue;
			}

			Ref<SpellCastInfo> sci;
			sci.instance();

			sci->caster_set(info->caster_get());
			sci->target_set(info->target_get());
			sci->has_cast_time_set(spell->cast_time_get_enabled());
			sci->cast_time_set(spell->cast_time_get());
			sci->spell_scale_set(info->spell_scale_get());
			sci->set_spell(spell);

			spell->cast_starts(sci);
		}
	}
}

void Spell::_aura_sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(info->target_get() == NULL || info->caster_get() == NULL || !info->get_aura().is_valid());

	Ref<AuraData> ad = info->target_get()->aura_gets_by(info->caster_get(), _id);

	if (!ad.is_valid()) {
		ad.instance();

		setup_aura_data(ad, info);

		Entity *owner = ad->get_owner();

		for (int i = 0; i < _aura_stat_attribute_count; ++i) {
			owner->stat_mod(_aura_stat_attributes[i].stat, _aura_stat_attributes[i].base_mod, _aura_stat_attributes[i].bonus_mod, _aura_stat_attributes[i].percent_mod);
		}

		if (_aura_add_states != 0) {
			for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
				int t = 1 << i;

				if ((_aura_add_states & t) != 0) {
					info->target_get()->adds_state_ref(i);
				}
			}
		}

		info->target_get()->aura_adds(ad);
	} else {
		ad->set_remaining_time(_aura_time);
	}
}

void Spell::_aura_sdeapply(Ref<AuraData> data) {
	ERR_FAIL_COND(data->get_owner() == NULL || data->caster_get() == NULL || !data->get_aura().is_valid());

	Entity *owner = data->get_owner();

	for (int i = 0; i < _aura_stat_attribute_count; ++i) {
		owner->stat_mod(_aura_stat_attributes[i].stat, -_aura_stat_attributes[i].base_mod, -_aura_stat_attributes[i].bonus_mod, -_aura_stat_attributes[i].percent_mod);
	}

	if (_aura_add_states != 0) {
		for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
			int t = 1 << i;

			if ((_aura_add_states & t) != 0) {
				data->get_owner()->removes_state_ref(i);
			}
		}
	}
}

void Spell::_aura_sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	//sapply(aura);

	aura->get_owner()->aura_removes(aura);
	aura->get_owner()->aura_adds(aura);
}

void Spell::_aura_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes(aura);
}

void Spell::_aura_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes_expired(aura);
}

void Spell::_aura_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes_dispelled(aura);
}

void Spell::_aura_supdate(Ref<AuraData> aura, float delta) {
	bool remove = false;

	remove = aura->update(delta);

	//ontick
	while (aura->get_unhandled_ticks() > 0) {
		if (aura->damage_get() != 0) {
			Ref<SpellDamageInfo> dpd = Ref<SpellDamageInfo>(memnew(SpellDamageInfo()));

			dpd->aura_source_set(Ref<Spell>(this));
			dpd->dealer_set(aura->caster_get());
			dpd->receiver_set(aura->get_owner());

			handle_aura_damage(aura, dpd);
		}

		if (aura->heal_get() != 0) {
			Ref<SpellHealInfo> shi = Ref<SpellHealInfo>(memnew(SpellHealInfo()));

			shi->aura_source_set(Ref<Spell>(this));
			shi->dealer_set(aura->caster_get());
			shi->receiver_set(aura->get_owner());

			handle_aura_heal(aura, shi);
		}

		aura->set_unhandled_ticks(aura->get_unhandled_ticks() - 1);
	}

	if (remove) {
		aura_removes_expired(aura);
	}
}

void Spell::_setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(info->caster_get()));

	data->set_aura(Ref<Spell>(this));
	data->set_aura_id(get_id());
	data->set_owner(info->target_get());
	data->caster_set(info->caster_get());
	data->set_tick(info->get_aura()->aura_get_tick());

	if (aura_get_time() > 0.2) {
		data->set_is_timed(true);
		data->set_remaining_time(aura_get_time());

	} else {
		data->set_is_timed(false);
	}

	if (aura_damage_get_enabled()) {
		aura_calculate_initial_damage(data, info);
	}

	if (aura_heal_get_enabled()) {
		aura_calculate_initial_heal(data, info);
	}
}

void Spell::_aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
}

void Spell::_aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
}

void Spell::_aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_damage = aura_damage_get_min();
	int max_damage = aura_damage_get_max();

	Math::randomize();
	int damage = min_damage + Math::rand() % (max_damage - min_damage);

	if (aura_get_scale_with_level()) {
		damage = static_cast<int>(damage * static_cast<float>(info->caster_get()->gets_level()) / static_cast<float>(ESS::get_singleton()->get_max_character_level()));
	}

	aura_data->damage_set(damage);
}

void Spell::_handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	if (info->dealer_get() && !INSTANCE_VALIDATE(info->dealer_get())) {
		info->dealer_set(NULL);
	}

	info->damage_set(aura_data->damage_get());
	info->aura_source_set(Ref<Spell>(this));

	if (info->dealer_get()) {
		info->dealer_get()->sdeal_damage_to(info);
	} else {
		info->receiver_get()->stake_damage(info);
	}
}

void Spell::_aura_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Spell::_aura_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Spell::_aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_heal = aura_heal_get_min();
	int max_heal = aura_heal_get_max();

	Math::randomize();
	int heal = min_heal + Math::rand() % (max_heal - min_heal);

	if (aura_get_scale_with_level()) {
		heal = static_cast<int>(heal * static_cast<float>(info->caster_get()->gets_level()) / static_cast<float>(ESS::get_singleton()->get_max_character_level()));
	}

	aura_data->heal_set(heal);
}

void Spell::_handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info) {
	if (info->dealer_get() && !INSTANCE_VALIDATE(info->dealer_get())) {
		info->dealer_set(NULL);
	}

	info->heal_set(aura_data->heal_get());

	if (info->dealer_get()) {
		info->dealer_get()->sdeal_heal_to(info);
	} else {
		info->receiver_get()->stake_heal(info);
	}
}

void Spell::_validate_property(PropertyInfo &property) const {
	String prop = property.name;

	if (prop.begins_with("aura_stat_attribute_")) {
		if (prop.ends_with("count"))
			return;

		int frame = prop.get_slicec('/', 0).get_slicec('_', 2).to_int();
		if (frame >= _aura_stat_attribute_count) {
			property.usage = 0;
		}

		if (property.name.ends_with("stat"))
			property.hint_string = ESS::get_singleton()->stat_get_string();
	} else if (prop == "diminishing_return_category") {
		property.hint_string = ESS::get_singleton()->dminishing_return_categories_get();
	} else if (prop.begins_with("aura_trigger_")) {
		if (prop.ends_with("count"))
			return;

		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _aura_trigger_count) {
			property.usage = 0;
		} else {
			if (prop.ends_with("notification_data")) {
				switch (_aura_trigger_datas[frame].notification_type) {
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA:
						property.hint = PROPERTY_HINT_ENUM;
						property.hint_string = SpellEnums::BINDING_STRING_NOTIFICATION_AURAS;
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_DAMAGE:
						property.hint = PROPERTY_HINT_ENUM;
						property.hint_string = SpellEnums::BINDING_STRING_NOTIFICATION_DAMAGES;
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_HEAL:
						property.hint = PROPERTY_HINT_ENUM;
						property.hint_string = SpellEnums::BINDING_STRING_NOTIFICATION_HEALS;
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CAST:
						property.hint = PROPERTY_HINT_ENUM;
						property.hint_string = SpellEnums::BINDING_STRING_NOTIFICATION_CASTS;
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_DEATH:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_COOLDOWN_ADDED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_COOLDOWN_REMOVED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CATEGORY_COOLDOWN_ADDED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CATEGORY_COOLDOWN_REMOVED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_GCD_STARTED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_GCD_FINISHED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_XP_GAINED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CLASS_LEVELUP:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CHARACTER_LEVELUP:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_ENTITY_RESOURCE_ADDED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_ENTITY_RESOURCE_REMOVED:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;

					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA_CUSTOM:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_DAMAGE_CUSTOM:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_HEAL_CUSTOM:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CAST_CUSTOM:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					case SpellEnums::TRIGGER_NOTIFICATION_TYPE_CUSTOM:
						property.hint = PROPERTY_HINT_NONE;
						property.hint_string = "";
						break;
					default:
						break;
				}
			}
		}
	} else if (property.name.ends_with("_stat")) {
		property.hint_string = ESS::get_singleton()->stat_get_string();
	}
}

void Spell::_bind_methods() {
	//Commands
	ClassDB::bind_method(D_METHOD("cast_starts", "info"), &Spell::cast_starts);
	ClassDB::bind_method(D_METHOD("cast_starts_triggered", "info"), &Spell::cast_starts_triggered);
	ClassDB::bind_method(D_METHOD("cast_interrupts", "info"), &Spell::cast_interrupts);
	ClassDB::bind_method(D_METHOD("cast_finishs", "info"), &Spell::cast_finishs);

	BIND_VMETHOD(MethodInfo("_cast_starts", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_cast_starts_triggered", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_cast_interrupts", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_cast_finishs", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	//Aura Commands
	ClassDB::bind_method(D_METHOD("aura_sapply", "info"), &Spell::aura_sapply);
	ClassDB::bind_method(D_METHOD("aura_sdeapply", "aura"), &Spell::aura_sdeapply);
	ClassDB::bind_method(D_METHOD("aura_sadd", "aura"), &Spell::aura_sadd);
	ClassDB::bind_method(D_METHOD("aura_sremove", "aura"), &Spell::aura_sremove);
	ClassDB::bind_method(D_METHOD("aura_removes_expired", "aura"), &Spell::aura_removes_expired);
	ClassDB::bind_method(D_METHOD("aura_removes_dispell", "aura"), &Spell::aura_removes_dispell);
	ClassDB::bind_method(D_METHOD("aura_supdate", "aura", "delta"), &Spell::aura_supdate);

	BIND_VMETHOD(MethodInfo("_aura_sapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sdeapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_sadd", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_sremove", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_removes_expired", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_removes_dispell", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_supdate", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("_aura_sapply", "info"), &Spell::_aura_sapply);
	ClassDB::bind_method(D_METHOD("_aura_sdeapply", "aura"), &Spell::_aura_sdeapply);
	ClassDB::bind_method(D_METHOD("_aura_sadd", "aura"), &Spell::_aura_sadd);
	ClassDB::bind_method(D_METHOD("_aura_sremove", "aura"), &Spell::_aura_sremove);
	ClassDB::bind_method(D_METHOD("_aura_removes_expired", "aura"), &Spell::_aura_removes_expired);
	ClassDB::bind_method(D_METHOD("_aura_removes_dispell", "aura"), &Spell::_aura_removes_dispell);
	ClassDB::bind_method(D_METHOD("_aura_supdate", "aura", "delta"), &Spell::_aura_supdate);

	//Eventhandlers
	ClassDB::bind_method(D_METHOD("son_cast_player_moved", "info"), &Spell::son_cast_player_moved);
	ClassDB::bind_method(D_METHOD("son_cast_damage_received", "info"), &Spell::son_cast_damage_received);
	ClassDB::bind_method(D_METHOD("son_spell_hit", "info"), &Spell::son_spell_hit);
	ClassDB::bind_method(D_METHOD("son_physics_process", "info", "delta"), &Spell::son_physics_process);

	BIND_VMETHOD(MethodInfo("_son_cast_player_moved", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_damage_received", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_spell_hit", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_physics_process", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo"), PropertyInfo(Variant::REAL, "delta")));

	//Clientside Event Handlers
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "info"), &Spell::notification_scast);

	BIND_VMETHOD(MethodInfo("_notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "info"), &Spell::notification_ccast);

	//Aura EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_aura_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &Spell::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "aura", "info"), &Spell::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_aura_scast", "what", "aura", "info"), &Spell::notification_aura_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "aura", "info"), &Spell::notification_sdamage);

	ClassDB::bind_method(D_METHOD("son_remove", "aura"), &Spell::son_remove);
	ClassDB::bind_method(D_METHOD("son_remove_expired", "aura"), &Spell::son_remove_expired);
	ClassDB::bind_method(D_METHOD("son_remove_dispell", "aura"), &Spell::son_remove_dispell);

	ClassDB::bind_method(D_METHOD("notification_sdeath", "data"), &Spell::notification_sdeath);

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "data", "cooldown"), &Spell::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "data", "cooldown"), &Spell::notification_scooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "data", "category_cooldown"), &Spell::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "data", "category_cooldown"), &Spell::notification_scategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started", "data", "gcd"), &Spell::notification_sgcd_started);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished", "data"), &Spell::notification_sgcd_finished);

	ClassDB::bind_method(D_METHOD("son_physics_process_aura", "data"), &Spell::son_physics_process_aura);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "data", "value"), &Spell::notification_sxp_gained);
	ClassDB::bind_method(D_METHOD("notification_slevel_up", "data", "value"), &Spell::notification_slevel_up);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "data", "value"), &Spell::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "data", "value"), &Spell::notification_sentity_resource_removed);

	BIND_VMETHOD(MethodInfo("_son_remove", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_remove_expired", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_remove_dispell", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_sdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_scooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sgcd_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_sgcd_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_physics_process_aura", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_slevel_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	//Aura Clientside Event Handlers
	BIND_VMETHOD(MethodInfo("_notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_aura_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_caura", "what", "data"), &Spell::notification_caura);
	ClassDB::bind_method(D_METHOD("notification_cheal", "what", "aura", "info"), &Spell::notification_cheal);
	ClassDB::bind_method(D_METHOD("notification_aura_ccast", "what", "aura", "info"), &Spell::notification_aura_ccast);
	ClassDB::bind_method(D_METHOD("notification_cdamage", "what", "aura", "info"), &Spell::notification_cdamage);

	ClassDB::bind_method(D_METHOD("notification_cdeath", "data"), &Spell::notification_cdeath);

	ClassDB::bind_method(D_METHOD("notification_ccooldown_added", "data", "info"), &Spell::notification_ccooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccooldown_removed", "data", "info"), &Spell::notification_ccooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_added", "data", "info"), &Spell::notification_ccategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_removed", "data", "info"), &Spell::notification_ccategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_cgcd_started", "data", "info"), &Spell::notification_cgcd_started);
	ClassDB::bind_method(D_METHOD("notification_cgcd_finished", "data"), &Spell::notification_cgcd_finished);

	ClassDB::bind_method(D_METHOD("notification_cxp_gained", "data", "value"), &Spell::notification_cxp_gained);
	ClassDB::bind_method(D_METHOD("notification_clevel_up", "data", "value"), &Spell::notification_clevel_up);

	ClassDB::bind_method(D_METHOD("notification_centity_resource_added", "data", "value"), &Spell::notification_centity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_centity_resource_removed", "data", "value"), &Spell::notification_centity_resource_removed);

	BIND_VMETHOD(MethodInfo("_con_cast_failed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_state_changed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_notification_cdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_ccooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_ccooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_ccategory_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_ccategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_con_aura_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_refresh", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_con_damage_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_heal_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_notification_cgcd_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_cgcd_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_cxp_gained", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_clevel_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_centity_resource_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_centity_resource_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	//Equipment

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_equip_should_deny", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_equip_son_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_son_fail", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_fail", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("equip_should_deny", "data", "equip_slot", "item"), &Spell::equip_should_deny);

	ClassDB::bind_method(D_METHOD("equip_son_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Spell::equip_son_success);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Spell::equip_son_fail);
	ClassDB::bind_method(D_METHOD("equip_con_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Spell::equip_con_success);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Spell::equip_con_fail);

	//Calculations / Queries
	ClassDB::bind_method(D_METHOD("calculate_initial_damage", "data"), &Spell::calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("handle_spell_damage", "data"), &Spell::handle_spell_damage);

	BIND_VMETHOD(MethodInfo("_calculate_initial_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_handle_spell_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("calculate_initial_heal", "data"), &Spell::calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("handle_spell_heal", "data"), &Spell::handle_spell_heal);

	BIND_VMETHOD(MethodInfo("_calculate_initial_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_handle_spell_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ClassDB::bind_method(D_METHOD("handle_projectile", "info"), &Spell::handle_projectile);
	ClassDB::bind_method(D_METHOD("handle_effect", "info"), &Spell::handle_effect);

	BIND_VMETHOD(MethodInfo("_handle_projectile", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_handle_effect", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	ClassDB::bind_method(D_METHOD("handle_gcd", "info"), &Spell::handle_gcd);
	ClassDB::bind_method(D_METHOD("handle_cooldown", "info"), &Spell::handle_cooldown);

	//Implementations
	ClassDB::bind_method(D_METHOD("_cast_starts", "info"), &Spell::_cast_starts);
	ClassDB::bind_method(D_METHOD("_cast_finishs", "info"), &Spell::_cast_finishs);

	ClassDB::bind_method(D_METHOD("_son_cast_player_moved", "info"), &Spell::_son_cast_player_moved);
	ClassDB::bind_method(D_METHOD("_son_spell_hit", "info"), &Spell::_son_spell_hit);

	ClassDB::bind_method(D_METHOD("_calculate_initial_damage", "info"), &Spell::_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("_handle_spell_damage", "info"), &Spell::_handle_spell_damage);

	ClassDB::bind_method(D_METHOD("_calculate_initial_heal", "info"), &Spell::_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("_handle_spell_heal", "info"), &Spell::_handle_spell_heal);

	ClassDB::bind_method(D_METHOD("_handle_projectile", "info"), &Spell::_handle_projectile);
	ClassDB::bind_method(D_METHOD("_handle_effect", "info"), &Spell::_handle_effect);

	//Aura Calculations / Queries
	ClassDB::bind_method(D_METHOD("setup_aura_data", "data", "info"), &Spell::setup_aura_data);

	BIND_VMETHOD(MethodInfo("_setup_aura_data", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));

	ClassDB::bind_method(D_METHOD("_setup_aura_data", "data", "info"), &Spell::_setup_aura_data);

	//damage
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_damage_receive", "data"), &Spell::aura_sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_damage_deal", "data"), &Spell::aura_sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("aura_calculate_initial_damage", "aura_data", "info"), &Spell::aura_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("handle_aura_damage", "aura_data", "data"), &Spell::handle_aura_damage);

	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_damage_deal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_calculate_initial_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_damage_receive", "info"), &Spell::_aura_sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_damage_deal", "info"), &Spell::_aura_sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("_aura_calculate_initial_damage", "aura_data", "info"), &Spell::_aura_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("_handle_aura_damage", "aura_data", "info"), &Spell::_handle_aura_damage);

	//heal
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_heal_receive", "data"), &Spell::aura_sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_heal_deal", "data"), &Spell::aura_sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("aura_calculate_initial_heal", "aura_data", "info"), &Spell::aura_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("handle_aura_heal", "aura_data", "data"), &Spell::handle_aura_heal);

	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_heal_receive", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_heal_deal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_calculate_initial_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "spell_heal_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_heal_receive", "info"), &Spell::_aura_sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_heal_deal", "info"), &Spell::_aura_sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("_aura_calculate_initial_heal", "aura_data", "info"), &Spell::_aura_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("_handle_aura_heal", "aura_data", "info"), &Spell::_handle_aura_heal);

	//Properties
	ClassDB::bind_method(D_METHOD("get_id"), &Spell::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &Spell::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("spell_type_get"), &Spell::spell_type_get);
	ClassDB::bind_method(D_METHOD("spell_type_set", "value"), &Spell::spell_type_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_SPELL_TYPES), "spell_type_set", "spell_type_get");

	ClassDB::bind_method(D_METHOD("get_spell_category"), &Spell::get_spell_category);
	ClassDB::bind_method(D_METHOD("set_spell_category", "value"), &Spell::set_spell_category);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_category", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_SPELL_CATEGORY), "set_spell_category", "get_spell_category");

	ClassDB::bind_method(D_METHOD("get_hide_from_actionbar"), &Spell::get_hide_from_actionbar);
	ClassDB::bind_method(D_METHOD("set_hide_from_actionbar", "value"), &Spell::set_hide_from_actionbar);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hide_from_actionbar"), "set_hide_from_actionbar", "get_hide_from_actionbar");

	ClassDB::bind_method(D_METHOD("get_target_type"), &Spell::get_target_type);
	ClassDB::bind_method(D_METHOD("set_target_type", "value"), &Spell::set_target_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_type", PROPERTY_HINT_ENUM, "Self, Target, Around, Front, Around Target"), "set_target_type", "get_target_type");

	ClassDB::bind_method(D_METHOD("get_target_relation_type"), &Spell::get_target_relation_type);
	ClassDB::bind_method(D_METHOD("set_target_relation_type", "value"), &Spell::set_target_relation_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_relation_type", PROPERTY_HINT_FLAGS, "Self, Enemy, Friendly"), "set_target_relation_type", "get_target_relation_type");

	ClassDB::bind_method(D_METHOD("get_level"), &Spell::get_level);
	ClassDB::bind_method(D_METHOD("set_level", "value"), &Spell::set_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "level"), "set_level", "get_level");

	ClassDB::bind_method(D_METHOD("get_rank"), &Spell::get_rank);
	ClassDB::bind_method(D_METHOD("set_rank", "value"), &Spell::set_rank);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rank"), "set_rank", "get_rank");

	ClassDB::bind_method(D_METHOD("get_is_local_spell"), &Spell::get_is_local_spell);
	ClassDB::bind_method(D_METHOD("set_is_local_spell", "value"), &Spell::set_is_local_spell);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_local_spell"), "set_is_local_spell", "get_is_local_spell");

	ClassDB::bind_method(D_METHOD("get_icon"), &Spell::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &Spell::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_needs_target"), &Spell::get_needs_target);
	ClassDB::bind_method(D_METHOD("set_needs_target", "value"), &Spell::set_needs_target);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "needs_target"), "set_needs_target", "get_needs_target");

	ClassDB::bind_method(D_METHOD("get_scale_with_level"), &Spell::get_scale_with_level);
	ClassDB::bind_method(D_METHOD("set_scale_with_level", "value"), &Spell::set_scale_with_level);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "scale_with_level"), "set_scale_with_level", "get_scale_with_level");

	ClassDB::bind_method(D_METHOD("get_visual_spell_effects"), &Spell::get_visual_spell_effects);
	ClassDB::bind_method(D_METHOD("set_visual_spell_effects", "value"), &Spell::set_visual_spell_effects);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "visual_spell_effects", PROPERTY_HINT_RESOURCE_TYPE, "SpellEffectVisual"), "set_visual_spell_effects", "get_visual_spell_effects");

	ClassDB::bind_method(D_METHOD("get_teaches_craft_recipe"), &Spell::get_teaches_craft_recipe);
	ClassDB::bind_method(D_METHOD("set_teaches_craft_recipe", "value"), &Spell::set_teaches_craft_recipe);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "teaches_craft_recipe", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipe"), "set_teaches_craft_recipe", "get_teaches_craft_recipe");

	ADD_GROUP("Spells Cast", "spells_cast_");

	//ADD_GROUP("Caster Aura Applys", "caster_aura_applys");
	ClassDB::bind_method(D_METHOD("spells_cast_on_caster_num_get"), &Spell::spells_cast_on_caster_num_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_caster_num_set", "value"), &Spell::spells_cast_on_caster_num_set);

	ClassDB::bind_method(D_METHOD("spell_cast_on_caster_get", "index"), &Spell::spell_cast_on_caster_get);
	ClassDB::bind_method(D_METHOD("spell_cast_on_caster_set", "index", "spell"), &Spell::spell_cast_on_caster_set);

	ClassDB::bind_method(D_METHOD("spells_cast_on_caster_get"), &Spell::spells_cast_on_caster_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_caster_set", "caster_aura_applys"), &Spell::spells_cast_on_caster_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_caster", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "spells_cast_on_caster_set", "spells_cast_on_caster_get");

	//ADD_GROUP("Target Aura Apply", "target_aura_applys");
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_num_get"), &Spell::spells_cast_on_target_num_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_num_set", "value"), &Spell::spells_cast_on_target_num_set);

	ClassDB::bind_method(D_METHOD("spell_cast_on_target_get", "index"), &Spell::spell_cast_on_target_get);
	ClassDB::bind_method(D_METHOD("spell_cast_on_target_set", "index", "spell"), &Spell::spell_cast_on_target_set);

	ClassDB::bind_method(D_METHOD("spells_cast_on_target_get"), &Spell::spells_cast_on_target_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_set", "target_aura_applys"), &Spell::spells_cast_on_target_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_target", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "spells_cast_on_target_set", "spells_cast_on_target_get");

	//ADD_GROUP("Apply Auras On Learn", "on_learn_auras");
	ClassDB::bind_method(D_METHOD("on_learn_cast_spells_num_get"), &Spell::on_learn_cast_spells_num_get);
	ClassDB::bind_method(D_METHOD("on_learn_cast_spells_num_set", "value"), &Spell::on_learn_cast_spells_num_set);

	ClassDB::bind_method(D_METHOD("spell_cast_on_learn_get", "index"), &Spell::spell_cast_on_learn_get);
	ClassDB::bind_method(D_METHOD("spell_cast_on_learn_set", "index", "spell"), &Spell::spell_cast_on_learn_set);

	ClassDB::bind_method(D_METHOD("spells_cast_on_learn_get"), &Spell::spells_cast_on_learn_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_learn_set", "spells"), &Spell::spells_cast_on_learn_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_learn", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "spells_cast_on_learn_set", "spells_cast_on_learn_get");

	ADD_GROUP("Texts", "text");
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_get_description", PropertyInfo(Variant::INT, "class_level"), PropertyInfo(Variant::INT, "character_level")));

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_translation_key"), &Spell::get_text_translation_key);
	ClassDB::bind_method(D_METHOD("set_text_translation_key", "value"), &Spell::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_translation_key"), "set_text_translation_key", "get_text_translation_key");

	ClassDB::bind_method(D_METHOD("get_text_description"), &Spell::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &Spell::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description", PROPERTY_HINT_MULTILINE_TEXT), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_name_translated"), &Spell::get_name_translated);
	ClassDB::bind_method(D_METHOD("get_description", "class_level", "character_level"), &Spell::get_description);
	ClassDB::bind_method(D_METHOD("_get_description", "class_level", "character_level"), &Spell::_get_description);

	ADD_GROUP("Cooldown", "cooldown");
	ClassDB::bind_method(D_METHOD("get_cooldown"), &Spell::get_cooldown);
	ClassDB::bind_method(D_METHOD("set_cooldown", "value"), &Spell::set_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cooldown_cooldown"), "set_cooldown", "get_cooldown");

	ClassDB::bind_method(D_METHOD("get_global_cooldown_enabled"), &Spell::get_global_cooldown_enabled);
	ClassDB::bind_method(D_METHOD("set_global_cooldown_enabled", "value"), &Spell::set_global_cooldown_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cooldown_global_cooldown_enabled"), "set_global_cooldown_enabled", "get_global_cooldown_enabled");

	ADD_GROUP("Range", "range");
	ClassDB::bind_method(D_METHOD("range_get_enabled"), &Spell::range_get_enabled);
	ClassDB::bind_method(D_METHOD("range_set_enabled", "value"), &Spell::range_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "range_enabled"), "range_set_enabled", "range_get_enabled");

	ClassDB::bind_method(D_METHOD("range_get"), &Spell::range_get);
	ClassDB::bind_method(D_METHOD("range_set", "value"), &Spell::range_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "range_range"), "range_set", "range_get");

	ADD_GROUP("Cast", "cast");
	ClassDB::bind_method(D_METHOD("cast_time_get_enabled"), &Spell::cast_time_get_enabled);
	ClassDB::bind_method(D_METHOD("cast_time_set_enabled", "value"), &Spell::cast_time_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast_enabled"), "cast_time_set_enabled", "cast_time_get_enabled");

	ClassDB::bind_method(D_METHOD("cast_time_get"), &Spell::cast_time_get);
	ClassDB::bind_method(D_METHOD("cast_time_set", "value"), &Spell::cast_time_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cast_cast_time"), "cast_time_set", "cast_time_get");

	ClassDB::bind_method(D_METHOD("get_can_move_while_casting"), &Spell::get_can_move_while_casting);
	ClassDB::bind_method(D_METHOD("set_can_move_while_casting", "value"), &Spell::set_can_move_while_casting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast_can_move_while_casting"), "set_can_move_while_casting", "get_can_move_while_casting");

	ADD_GROUP("Projectile", "projectile");
	ClassDB::bind_method(D_METHOD("projectile_get_use_time"), &Spell::projectile_get_use_time);
	ClassDB::bind_method(D_METHOD("projectile_set_use_time", "value"), &Spell::projectile_set_use_time);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "projectile_use_time"), "projectile_set_use_time", "projectile_get_use_time");

	ClassDB::bind_method(D_METHOD("projectile_get_time"), &Spell::projectile_get_time);
	ClassDB::bind_method(D_METHOD("projectile_set_time", "value"), &Spell::projectile_set_time);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "projectile_time"), "projectile_set_time", "projectile_get_time");

	ClassDB::bind_method(D_METHOD("projectile_get_use_speed"), &Spell::projectile_get_use_speed);
	ClassDB::bind_method(D_METHOD("projectile_set_use_speed", "value"), &Spell::projectile_set_use_speed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "projectile_use_speed"), "projectile_set_use_speed", "projectile_get_use_speed");

	ClassDB::bind_method(D_METHOD("projectile_get_speed"), &Spell::projectile_get_speed);
	ClassDB::bind_method(D_METHOD("projectile_set_speed", "value"), &Spell::projectile_set_speed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "projectile_speed"), "projectile_set_speed", "projectile_get_speed");

	ClassDB::bind_method(D_METHOD("projectile_get_scene"), &Spell::projectile_get_scene);
	ClassDB::bind_method(D_METHOD("projectile_set_scene", "value"), &Spell::projectile_set_scene);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "projectile_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "projectile_set_scene", "projectile_get_scene");

	ADD_GROUP("Damage", "damage");
	ClassDB::bind_method(D_METHOD("damage_get_enabled"), &Spell::damage_get_enabled);
	ClassDB::bind_method(D_METHOD("damage_set_enabled", "value"), &Spell::damage_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_enabled"), "damage_set_enabled", "damage_get_enabled");

	ClassDB::bind_method(D_METHOD("damage_get_type"), &Spell::damage_get_type);
	ClassDB::bind_method(D_METHOD("damage_set_type", "value"), &Spell::damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "damage_set_type", "damage_get_type");

	ClassDB::bind_method(D_METHOD("damage_get_min"), &Spell::damage_get_min);
	ClassDB::bind_method(D_METHOD("damage_set_min", "value"), &Spell::damage_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_min"), "damage_set_min", "damage_get_min");

	ClassDB::bind_method(D_METHOD("damage_get_max"), &Spell::damage_get_max);
	ClassDB::bind_method(D_METHOD("damage_set_max", "value"), &Spell::damage_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_max"), "damage_set_max", "damage_get_max");

	ClassDB::bind_method(D_METHOD("damage_get_scale_stat"), &Spell::damage_get_scale_stat);
	ClassDB::bind_method(D_METHOD("damage_set_scale_stat", "value"), &Spell::damage_set_scale_stat);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_scale_stat", PROPERTY_HINT_ENUM, ""), "damage_set_scale_stat", "damage_get_scale_stat");

	ClassDB::bind_method(D_METHOD("damage_get_scale_coeff"), &Spell::damage_get_scale_coeff);
	ClassDB::bind_method(D_METHOD("damage_set_scale_coeff", "value"), &Spell::damage_set_scale_coeff);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "damage_scale_coeff"), "damage_set_scale_coeff", "damage_get_scale_coeff");

	ADD_GROUP("Heal", "heal");
	ClassDB::bind_method(D_METHOD("heal_get_enabled"), &Spell::heal_get_enabled);
	ClassDB::bind_method(D_METHOD("heal_set_enabled", "value"), &Spell::heal_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_enabled"), "heal_set_enabled", "heal_get_enabled");

	ClassDB::bind_method(D_METHOD("heal_get_min"), &Spell::heal_get_min);
	ClassDB::bind_method(D_METHOD("heal_set_min", "value"), &Spell::heal_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_min"), "heal_set_min", "heal_get_min");

	ClassDB::bind_method(D_METHOD("heal_get_max"), &Spell::heal_get_max);
	ClassDB::bind_method(D_METHOD("heal_set_max", "value"), &Spell::heal_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_max"), "heal_set_max", "heal_get_max");

	ClassDB::bind_method(D_METHOD("heal_get_scale_stat"), &Spell::heal_get_scale_stat);
	ClassDB::bind_method(D_METHOD("heal_set_scale_stat", "value"), &Spell::heal_set_scale_stat);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_scale_stat", PROPERTY_HINT_ENUM, ""), "heal_set_scale_stat", "heal_get_scale_stat");

	ClassDB::bind_method(D_METHOD("heal_get_scale_coeff"), &Spell::heal_get_scale_coeff);
	ClassDB::bind_method(D_METHOD("heal_set_scale_coeff", "value"), &Spell::heal_set_scale_coeff);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "heal_scale_coeff"), "heal_set_scale_coeff", "heal_get_scale_coeff");

	ADD_GROUP("Dispell", "dispell");
	ClassDB::bind_method(D_METHOD("dispell_get_enabled"), &Spell::dispell_get_enabled);
	ClassDB::bind_method(D_METHOD("dispell_set_enabled", "value"), &Spell::dispell_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dispell_enabled"), "dispell_set_enabled", "dispell_get_enabled");

	ClassDB::bind_method(D_METHOD("dispell_get_count_min"), &Spell::dispell_get_count_min);
	ClassDB::bind_method(D_METHOD("dispell_set_count_min", "value"), &Spell::dispell_set_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_min"), "dispell_set_count_min", "dispell_get_count_min");

	ClassDB::bind_method(D_METHOD("dispell_get_count_max"), &Spell::dispell_get_count_max);
	ClassDB::bind_method(D_METHOD("dispell_set_count_max", "value"), &Spell::dispell_set_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_max"), "dispell_set_count_max", "dispell_get_count_max");

	ClassDB::bind_method(D_METHOD("dispell_get_aura_types"), &Spell::dispell_get_aura_types);
	ClassDB::bind_method(D_METHOD("dispell_set_aura_types", "value"), &Spell::dispell_set_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "dispell_set_aura_types", "dispell_get_aura_types");

	ADD_GROUP("Interrupt", "interrupt");
	ClassDB::bind_method(D_METHOD("get_interrupt_enabled"), &Spell::get_interrupt_enabled);
	ClassDB::bind_method(D_METHOD("set_interrupt_enabled", "value"), &Spell::set_interrupt_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "interrupt_enabled"), "set_interrupt_enabled", "get_interrupt_enabled");

	ClassDB::bind_method(D_METHOD("get_interrupt_time"), &Spell::get_interrupt_time);
	ClassDB::bind_method(D_METHOD("set_interrupt_time", "value"), &Spell::set_interrupt_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "interrupt_time"), "set_interrupt_time", "get_interrupt_time");

	ADD_GROUP("Cost", "cost");
	ClassDB::bind_method(D_METHOD("get_item_cost"), &Spell::get_item_cost);
	ClassDB::bind_method(D_METHOD("set_item_cost", "value"), &Spell::set_item_cost);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cost_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item_cost", "get_item_cost");

	ClassDB::bind_method(D_METHOD("get_required_item"), &Spell::get_required_item);
	ClassDB::bind_method(D_METHOD("set_required_item", "value"), &Spell::set_required_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cost_required_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_required_item", "get_required_item");

	ADD_GROUP("Resources", "resource");
	ClassDB::bind_method(D_METHOD("get_resource_cost"), &Spell::get_resource_cost);
	ClassDB::bind_method(D_METHOD("set_resource_cost", "value"), &Spell::set_resource_cost);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_cost", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "set_resource_cost", "get_resource_cost");

	ClassDB::bind_method(D_METHOD("get_resource_give"), &Spell::get_resource_give);
	ClassDB::bind_method(D_METHOD("set_resource_give", "value"), &Spell::set_resource_give);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_give", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "set_resource_give", "get_resource_give");

	ADD_GROUP("AOE", "aoe");
	ClassDB::bind_method(D_METHOD("get_is_aoe"), &Spell::get_is_aoe);
	ClassDB::bind_method(D_METHOD("set_is_aoe", "value"), &Spell::set_is_aoe);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aoe"), "set_is_aoe", "get_is_aoe");

	ClassDB::bind_method(D_METHOD("get_aoe_target_type"), &Spell::get_aoe_target_type);
	ClassDB::bind_method(D_METHOD("set_aoe_target_type", "value"), &Spell::set_aoe_target_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aoe_targetType", PROPERTY_HINT_ENUM, "Caster, Target, Ground Target Selection, Random"), "set_aoe_target_type", "get_aoe_target_type");

	ClassDB::bind_method(D_METHOD("get_aoe_collider_type"), &Spell::get_aoe_collider_type);
	ClassDB::bind_method(D_METHOD("set_aoe_collider_type", "value"), &Spell::set_aoe_collider_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aoe_colliderType", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_COLLIDER_TYPE), "set_aoe_collider_type", "get_aoe_collider_type");

	ClassDB::bind_method(D_METHOD("get_aoe_radius"), &Spell::get_aoe_radius);
	ClassDB::bind_method(D_METHOD("set_aoe_radius", "value"), &Spell::set_aoe_radius);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "aoe_radius"), "set_aoe_radius", "get_aoe_radius");

	ClassDB::bind_method(D_METHOD("get_aoe_box_extents"), &Spell::get_aoe_box_extents);
	ClassDB::bind_method(D_METHOD("set_aoe_box_extents", "value"), &Spell::set_aoe_box_extents);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "aoe_box_extents"), "set_aoe_box_extents", "get_aoe_box_extents");

	ADD_GROUP("Spell Cooldown Mainpulation", "spell_cooldown_mainpulation");
	ClassDB::bind_method(D_METHOD("get_spell_cooldown_mainpulation_data_count"), &Spell::get_spell_cooldown_mainpulation_data_count);
	ClassDB::bind_method(D_METHOD("set_spell_cooldown_mainpulation_data_count", "value"), &Spell::set_spell_cooldown_mainpulation_data_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_cooldown_mainpulation_data_count"), "set_spell_cooldown_mainpulation_data_count", "get_spell_cooldown_mainpulation_data_count");

	ADD_GROUP("Training", "training");
	ClassDB::bind_method(D_METHOD("get_training_cost"), &Spell::get_training_cost);
	ClassDB::bind_method(D_METHOD("set_training_cost", "value"), &Spell::set_training_cost);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "training_cost"), "set_training_cost", "get_training_cost");

	ClassDB::bind_method(D_METHOD("get_training_required_spell"), &Spell::get_training_required_spell);
	ClassDB::bind_method(D_METHOD("set_training_required_spell", "curspellve"), &Spell::set_training_required_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "training_required_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_training_required_spell", "get_training_required_spell");

	ClassDB::bind_method(D_METHOD("get_training_required_skill"), &Spell::get_training_required_skill);
	ClassDB::bind_method(D_METHOD("set_training_required_skill", "curve"), &Spell::set_training_required_skill);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "training_required_skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkillData"), "set_training_required_skill", "get_training_required_skill");

	ClassDB::bind_method(D_METHOD("get_training_required_skill_level"), &Spell::get_training_required_skill_level);
	ClassDB::bind_method(D_METHOD("set_training_required_skill_level", "value"), &Spell::set_training_required_skill_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "training_required_skill_level"), "set_training_required_skill_level", "get_training_required_skill_level");

	ADD_GROUP("Aura", "aura");
	ClassDB::bind_method(D_METHOD("aura_get_permanent"), &Spell::aura_get_permanent);
	ClassDB::bind_method(D_METHOD("aura_set_permanent", "value"), &Spell::aura_set_permanent);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_permanent"), "aura_set_permanent", "aura_get_permanent");

	ClassDB::bind_method(D_METHOD("aura_get_time"), &Spell::aura_get_time);
	ClassDB::bind_method(D_METHOD("aura_set_time", "value"), &Spell::aura_set_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "aura_time"), "aura_set_time", "aura_get_time");

	ClassDB::bind_method(D_METHOD("aura_get_tick"), &Spell::aura_get_tick);
	ClassDB::bind_method(D_METHOD("aura_set_tick", "value"), &Spell::aura_set_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "aura_tick"), "aura_set_tick", "aura_get_tick");

	ClassDB::bind_method(D_METHOD("aura_get_is_debuff"), &Spell::aura_get_is_debuff);
	ClassDB::bind_method(D_METHOD("aura_set_is_debuff", "value"), &Spell::aura_set_is_debuff);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_debuff"), "aura_set_is_debuff", "aura_get_is_debuff");

	ClassDB::bind_method(D_METHOD("aura_get_scale_with_level"), &Spell::aura_get_scale_with_level);
	ClassDB::bind_method(D_METHOD("aura_set_scale_with_level", "value"), &Spell::aura_set_scale_with_level);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_scale_with_level"), "aura_set_scale_with_level", "aura_get_scale_with_level");

	ClassDB::bind_method(D_METHOD("aura_get_aura_type"), &Spell::aura_get_aura_type);
	ClassDB::bind_method(D_METHOD("aura_set_aura_type", "value"), &Spell::aura_set_aura_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_AURA_TYPES), "aura_set_aura_type", "aura_get_aura_type");

	ClassDB::bind_method(D_METHOD("aura_get_aura_group"), &Spell::aura_get_aura_group);
	ClassDB::bind_method(D_METHOD("aura_set_aura_group", "value"), &Spell::aura_set_aura_group);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_group", PROPERTY_HINT_RESOURCE_TYPE, "AuraGroup"), "aura_set_aura_group", "aura_get_aura_group");

	ClassDB::bind_method(D_METHOD("aura_get_hide"), &Spell::aura_get_hide);
	ClassDB::bind_method(D_METHOD("aura_set_hide", "value"), &Spell::aura_set_hide);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_hide"), "aura_set_hide", "aura_get_hide");

	ClassDB::bind_method(D_METHOD("aura_get_ability_scale_data_id"), &Spell::aura_get_ability_scale_data_id);
	ClassDB::bind_method(D_METHOD("aura_set_ability_scale_data_id", "value"), &Spell::aura_set_ability_scale_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_ability_scale_data_id"), "aura_set_ability_scale_data_id", "aura_get_ability_scale_data_id");

	ClassDB::bind_method(D_METHOD("aura_get_visual_spell_effects"), &Spell::aura_get_visual_spell_effects);
	ClassDB::bind_method(D_METHOD("aura_set_visual_spell_effects", "value"), &Spell::aura_set_visual_spell_effects);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_visual_spell_effects", PROPERTY_HINT_RESOURCE_TYPE, "SpellEffectVisual"), "aura_set_visual_spell_effects", "aura_get_visual_spell_effects");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_aura_get_description", PropertyInfo(Variant::INT, "class_level"), PropertyInfo(Variant::INT, "character_level")));

	ADD_GROUP("Aura Texts", "aura_text");
	ClassDB::bind_method(D_METHOD("aura_get_text_translation_key"), &Spell::aura_get_text_translation_key);
	ClassDB::bind_method(D_METHOD("aura_set_text_translation_key", "value"), &Spell::aura_set_text_translation_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "aura_text_translation_key"), "aura_set_text_translation_key", "aura_get_text_translation_key");

	ClassDB::bind_method(D_METHOD("aura_get_text_description"), &Spell::aura_get_text_description);
	ClassDB::bind_method(D_METHOD("aura_set_text_description", "value"), &Spell::aura_set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "aura_text_description", PROPERTY_HINT_MULTILINE_TEXT), "aura_set_text_description", "aura_get_text_description");

	ClassDB::bind_method(D_METHOD("aura_get_name_translated"), &Spell::aura_get_name_translated);
	ClassDB::bind_method(D_METHOD("aura_get_description", "class_level", "character_level"), &Spell::aura_get_description);
	ClassDB::bind_method(D_METHOD("_aura_get_description", "class_level", "character_level"), &Spell::_aura_get_description);

	ADD_GROUP("Aura Damage", "aura_damage");
	//Damage
	ClassDB::bind_method(D_METHOD("aura_damage_get_enabled"), &Spell::aura_damage_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_damage_set_enabled", "value"), &Spell::aura_damage_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_damage_enabled"), "aura_damage_set_enabled", "aura_damage_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_damage_get_type"), &Spell::aura_damage_get_type);
	ClassDB::bind_method(D_METHOD("aura_damage_set_type", "value"), &Spell::aura_damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "aura_damage_set_type", "aura_damage_get_type");

	ClassDB::bind_method(D_METHOD("aura_damage_get_min"), &Spell::aura_damage_get_min);
	ClassDB::bind_method(D_METHOD("aura_damage_set_min", "value"), &Spell::aura_damage_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_min"), "aura_damage_set_min", "aura_damage_get_min");

	ClassDB::bind_method(D_METHOD("aura_damage_get_max"), &Spell::aura_damage_get_max);
	ClassDB::bind_method(D_METHOD("aura_damage_set_max", "value"), &Spell::aura_damage_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_max"), "aura_damage_set_max", "aura_damage_get_max");

	ClassDB::bind_method(D_METHOD("aura_damage_get_can_crit"), &Spell::aura_damage_get_can_crit);
	ClassDB::bind_method(D_METHOD("aura_damage_set_can_crit", "value"), &Spell::aura_damage_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_damage_can_crit"), "aura_damage_set_can_crit", "aura_damage_get_can_crit");

	ClassDB::bind_method(D_METHOD("aura_damage_set", "min", "max", "can_crit"), &Spell::aura_damage_set);

	ClassDB::bind_method(D_METHOD("aura_damage_get_scaling_curve"), &Spell::aura_damage_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_damage_set_scaling_curve", "curve"), &Spell::aura_damage_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_damage_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_damage_set_scaling_curve", "aura_damage_get_scaling_curve");

	ADD_GROUP("Aura Absorb", "aura_absorb");
	//Absorb
	ClassDB::bind_method(D_METHOD("aura_absorb_get_enabled"), &Spell::aura_absorb_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_enabled", "value"), &Spell::aura_absorb_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_absorb_enabled"), "aura_absorb_set_enabled", "aura_absorb_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_absorb_damage_get_type"), &Spell::aura_absorb_damage_get_type);
	ClassDB::bind_method(D_METHOD("aura_absorb_damage_set_type", "value"), &Spell::aura_absorb_damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "aura_absorb_damage_set_type", "aura_absorb_damage_get_type");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_min"), &Spell::aura_absorb_get_min);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_min", "value"), &Spell::aura_absorb_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_min"), "aura_absorb_set_min", "aura_absorb_get_min");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_max"), &Spell::aura_absorb_get_max);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_max", "value"), &Spell::aura_absorb_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_max"), "aura_absorb_set_max", "aura_absorb_get_max");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_scaling_curve"), &Spell::aura_absorb_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_scaling_curve", "curve"), &Spell::aura_absorb_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_absorb_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_absorb_set_scaling_curve", "aura_absorb_get_scaling_curve");

	ADD_GROUP("Aura Heal", "aura_heal");
	//Heal
	ClassDB::bind_method(D_METHOD("aura_heal_get_enabled"), &Spell::aura_heal_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_heal_set_enabled", "value"), &Spell::aura_heal_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_heal_enabled"), "aura_heal_set_enabled", "aura_heal_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_heal_get_min"), &Spell::aura_heal_get_min);
	ClassDB::bind_method(D_METHOD("aura_heal_set_min", "value"), &Spell::aura_heal_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_heal_min"), "aura_heal_set_min", "aura_heal_get_min");

	ClassDB::bind_method(D_METHOD("aura_heal_get_max"), &Spell::aura_heal_get_max);
	ClassDB::bind_method(D_METHOD("aura_heal_set_max", "value"), &Spell::aura_heal_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_heal_max"), "aura_heal_set_max", "aura_heal_get_max");

	ClassDB::bind_method(D_METHOD("aura_heal_get_can_crit"), &Spell::aura_heal_get_can_crit);
	ClassDB::bind_method(D_METHOD("aura_heal_set_can_crit", "value"), &Spell::aura_heal_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_heal_can_crit"), "aura_heal_set_can_crit", "aura_heal_get_can_crit");

	ClassDB::bind_method(D_METHOD("aura_heal_set", "min", "max", "can_crit"), &Spell::aura_heal_set);

	ClassDB::bind_method(D_METHOD("aura_heal_get_scaling_curve"), &Spell::aura_heal_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_heal_set_scaling_curve", "curve"), &Spell::aura_heal_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_heal_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_heal_set_scaling_curve", "aura_heal_get_scaling_curve");

	ADD_GROUP("Aura Dispell", "aura_dispell");
	ClassDB::bind_method(D_METHOD("aura_dispell_get_enabled"), &Spell::aura_dispell_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_enabled", "value"), &Spell::aura_dispell_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_dispell_enabled"), "aura_dispell_set_enabled", "aura_dispell_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_count_min"), &Spell::aura_dispell_get_count_min);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_count_min", "value"), &Spell::aura_dispell_set_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_count_min"), "aura_dispell_set_count_min", "aura_dispell_get_count_min");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_count_max"), &Spell::aura_dispell_get_count_max);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_count_max", "value"), &Spell::aura_dispell_set_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_count_max"), "aura_dispell_set_count_max", "aura_dispell_get_count_max");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_aura_types"), &Spell::aura_dispell_get_aura_types);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_aura_types", "value"), &Spell::aura_dispell_set_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "aura_dispell_set_aura_types", "aura_dispell_get_aura_types");

	//Resources
	ADD_GROUP("Aura Resources", "aura_resource");
	ClassDB::bind_method(D_METHOD("aura_get_resource_cost"), &Spell::aura_get_resource_cost);
	ClassDB::bind_method(D_METHOD("aura_set_resource_cost", "value"), &Spell::aura_set_resource_cost);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_resource_cost", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "aura_set_resource_cost", "aura_get_resource_cost");

	ClassDB::bind_method(D_METHOD("aura_get_resource_give"), &Spell::aura_get_resource_give);
	ClassDB::bind_method(D_METHOD("aura_set_resource_give", "value"), &Spell::aura_set_resource_give);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_resource_give", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "aura_set_resource_give", "aura_get_resource_give");

	ADD_GROUP("Aura States", "aura_states");
	ClassDB::bind_method(D_METHOD("aura_get_add_states"), &Spell::aura_get_add_states);
	ClassDB::bind_method(D_METHOD("aura_set_add_states", "value"), &Spell::aura_set_add_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_add", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_add_states", "aura_get_add_states");

	ClassDB::bind_method(D_METHOD("aura_get_remove_effects_with_states"), &Spell::aura_get_remove_effects_with_states);
	ClassDB::bind_method(D_METHOD("aura_set_remove_effects_with_states", "value"), &Spell::aura_set_remove_effects_with_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_remove_effects", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_remove_effects_with_states", "aura_get_remove_effects_with_states");

	ClassDB::bind_method(D_METHOD("aura_get_supress_states"), &Spell::aura_get_supress_states);
	ClassDB::bind_method(D_METHOD("aura_set_supress_states", "value"), &Spell::aura_set_supress_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_supress", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_supress_states", "aura_get_supress_states");

	//Diminishing Returns
	ADD_GROUP("Aura Diminishing Returns", "aura_diminishing_return");
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_enabled_get"), &Spell::aura_diminishing_return_enabled_get);
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_enabled_set", "value"), &Spell::aura_diminishing_return_enabled_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_diminishing_return_enabled"), "aura_diminishing_return_enabled_set", "aura_diminishing_return_enabled_get");

	ClassDB::bind_method(D_METHOD("aura_diminishing_return_category_get"), &Spell::aura_diminishing_return_category_get);
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_category_set", "value"), &Spell::aura_diminishing_return_category_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_diminishing_return_category", PROPERTY_HINT_ENUM, ""), "aura_diminishing_return_category_set", "aura_diminishing_return_category_get");

	////    Talents    ////
	ADD_GROUP("Aura Talent", "aura_talent");
	ClassDB::bind_method(D_METHOD("aura_get_talent_required_talent"), &Spell::aura_get_talent_required_talent);
	ClassDB::bind_method(D_METHOD("aura_set_talent_required_talent", "next_rank"), &Spell::aura_set_talent_required_talent);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_talent_required_talent", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "aura_set_talent_required_talent", "aura_get_talent_required_talent");

	ClassDB::bind_method(D_METHOD("aura_get_talent_required_spell"), &Spell::aura_get_talent_required_spell);
	ClassDB::bind_method(D_METHOD("aura_set_talent_required_spell", "next_rank"), &Spell::aura_set_talent_required_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_talent_required_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "aura_set_talent_required_spell", "aura_get_talent_required_spell");

	ADD_GROUP("Aura Teaches", "aura_teaches");
	ClassDB::bind_method(D_METHOD("aura_get_teaches_spell"), &Spell::aura_get_teaches_spell);
	ClassDB::bind_method(D_METHOD("aura_set_teaches_spell", "next_rank"), &Spell::aura_set_teaches_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_teaches_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "aura_set_teaches_spell", "aura_get_teaches_spell");

	////    Triggers    ////
	ADD_GROUP("Aura Triggers", "aura_trigger");
	ClassDB::bind_method(D_METHOD("aura_trigger_get_count"), &Spell::aura_trigger_get_count);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_count", "count"), &Spell::aura_trigger_set_count);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_notification_type", "index"), &Spell::aura_trigger_get_notification_type);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_notification_type", "index", "value"), &Spell::aura_trigger_set_notification_type);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_notification_data", "index"), &Spell::aura_trigger_get_notification_data);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_notification_data", "index", "value"), &Spell::aura_trigger_set_notification_data);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_trigger_type", "index"), &Spell::aura_trigger_get_trigger_type);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_trigger_type", "index", "value"), &Spell::aura_trigger_set_trigger_type);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_trigger_type_data", "index"), &Spell::aura_trigger_get_trigger_type_data);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_trigger_type_data", "index", "value"), &Spell::aura_trigger_set_trigger_type_data);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_spell", "index"), &Spell::aura_trigger_get_spell);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_spell", "index", "value"), &Spell::aura_trigger_set_spell);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_trigger_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_TRIGGER_DATA), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "aura_trigger_set_count", "aura_trigger_get_count");

	for (int i = 0; i < MAX_TRIGGER_DATA; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "aura_trigger_" + itos(i) + "/notification_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_NOTIFICATION_TYPE, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "aura_trigger_set_notification_type", "aura_trigger_get_notification_type", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "aura_trigger_" + itos(i) + "/notification_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_trigger_set_notification_data", "aura_trigger_get_notification_data", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "aura_trigger_" + itos(i) + "/trigger_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_TYPE, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_trigger_set_trigger_type", "aura_trigger_get_trigger_type", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_trigger_" + itos(i) + "/trigger_type_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_trigger_set_trigger_type_data", "aura_trigger_get_trigger_type_data", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "aura_trigger_" + itos(i) + "/spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_trigger_set_spell", "aura_trigger_get_spell", i);
	}

	ADD_GROUP("Aura Stat Attributes", "aura_stat_attribute");
	//AuraStatAttributes
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_count"), &Spell::aura_stat_attribute_get_count);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_count", "count"), &Spell::aura_stat_attribute_set_count);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_stat", "index"), &Spell::aura_stat_attribute_get_stat);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_stat", "index", "value"), &Spell::aura_stat_attribute_set_stat);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_base_mod", "index"), &Spell::aura_stat_attribute_get_base_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_base_mod", "index", "value"), &Spell::aura_stat_attribute_set_base_mod);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_bonus_mod", "index"), &Spell::aura_stat_attribute_get_bonus_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_bonus_mod", "index", "value"), &Spell::aura_stat_attribute_set_bonus_mod);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_percent_mod", "index"), &Spell::aura_stat_attribute_get_percent_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_percent_mod", "index", "value"), &Spell::aura_stat_attribute_set_percent_mod);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_stat_attribute_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_AURA_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "aura_stat_attribute_set_count", "aura_stat_attribute_get_count");

	for (int i = 0; i < MAX_AURA_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "aura_stat_attribute_" + itos(i) + "/stat", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_stat", "aura_stat_attribute_get_stat", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_base_mod", "aura_stat_attribute_get_base_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_bonus_mod", "aura_stat_attribute_get_bonus_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_percent_mod", "aura_stat_attribute_get_percent_mod", i);
	}

	ClassDB::bind_method(D_METHOD("is_aura"), &Spell::is_aura);
	ClassDB::bind_method(D_METHOD("aura_is_talent"), &Spell::aura_is_talent);

	BIND_ENUM_CONSTANT(TARGET_SELF);
	BIND_ENUM_CONSTANT(TARGET_ENEMY);
	BIND_ENUM_CONSTANT(TARGET_FRIENDLY);

	BIND_ENUM_CONSTANT(SPELL_TARGET_TYPE_SELF);
	BIND_ENUM_CONSTANT(SPELL_TARGET_TYPE_TARGET);
	BIND_ENUM_CONSTANT(SPELL_TARGET_TYPE_AROUND);
	BIND_ENUM_CONSTANT(SPELL_TARGET_TYPE_FRONT);
	BIND_ENUM_CONSTANT(SPELL_TARGET_TYPE_AROUND_TARGET);

	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_CASTER);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_TARGET);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_GOUND_TARGET_SELECTION);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_RANDOM);

	BIND_CONSTANT(MAX_AURA_STATS);
	BIND_CONSTANT(MAX_TRIGGER_DATA);
}
