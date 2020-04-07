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

#include "aura.h"

#include "../../entities/resources/entity_resource_cost_data.h"
#include "../../singletons/entity_data_manager.h"

int Aura::get_id() const {
	return _id;
}
void Aura::set_id(const int value) {
	_id = value;
}

Ref<Texture> Aura::get_icon() {
	return _icon;
}
void Aura::set_icon(const Ref<Texture> &value) {
	_icon = value;
}

float Aura::get_time() const {
	return _time;
}
void Aura::set_time(const float value) {
	_time = value;
}

float Aura::get_tick() const {
	return _tick;
}
void Aura::set_tick(const float value) {
	_tick = value;
}

Ref<AuraGroup> Aura::get_aura_group() {
	return _aura_group;
}
void Aura::set_aura_group(const Ref<AuraGroup> &value) {
	_aura_group = value;
}

bool Aura::get_is_debuff() const {
	return _is_debuff;
}
void Aura::set_is_debuff(const bool value) {
	_is_debuff = value;
}

SpellEnums::AuraType Aura::get_aura_type() const {
	return _aura_type;
}
void Aura::set_aura_type(SpellEnums::AuraType value) {
	_aura_type = value;
}

int Aura::get_rank() const {
	return _rank;
}
void Aura::set_rank(const int value) {
	_rank = value;
}

bool Aura::get_scale_with_level() const {
	return _scale_with_level;
}
void Aura::set_scale_with_level(const bool value) {
	_scale_with_level = value;
}

String Aura::get_text_translation_key() const {
	return _text_translation_key;
}
void Aura::set_text_translation_key(const String &value) {
	_text_translation_key = value;
}

String Aura::get_text_description() const {
	return _text_description;
}
void Aura::set_text_description(const String description) {
	_text_description = description;
}

bool Aura::get_hide() const {
	return _hide;
}
void Aura::set_hide(const bool value) {
	_hide = value;
}

Ref<SpellEffectVisual> Aura::get_visual_spell_effects() {
	return _visual_spell_effects;
}
void Aura::set_visual_spell_effects(const Ref<SpellEffectVisual> &value) {
	_visual_spell_effects = value;
}

int Aura::get_ability_scale_data_id() const {
	return ability_scale_data_id;
}
void Aura::set_ability_scale_data_id(const int value) {
	ability_scale_data_id = value;
}

float Aura::get_damage_scale_for_level(const int level) const {
	//return this->getDamageLevelScaling()->Evaluate((float)(level));
	return 1;
}
float Aura::get_heal_scale_for_level(const int level) const {
	//return this->getHealLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Aura::get_absorb_scale_for_level(const int level) const {
	//return this->getAbsorbLevelScaling()->Evaluate((float)(level));
	return 1;
}

SpellEnums::DiminishingReturnCategory Aura::get_diminishing_category() const {
	return _diminishing_category;
}

void Aura::set_diminishing_category(SpellEnums::DiminishingReturnCategory diminishingCategory) {
	_diminishing_category = diminishingCategory;
}

Ref<Spell> Aura::get_teaches_spell() {
	return _teaches_spell;
}
void Aura::set_teaches_spell(const Ref<Spell> &spell) {
	_teaches_spell = spell;
}

/*
void Aura::SetScalingData(AbilityScalingData *scalingData) {
scalingData->getDamageCurve();
scalingData->getAbsorbCurve();
scalingData->getHealingCurve();
}*/
/*
void Aura::OnAuraAbilityScalingDataLoaded(AbilityScalingDataLoaderHelper *h) {
this->SetScalingData(h->getData());
}
*/

//Damage
bool Aura::get_damage_enabled() const {
	return _damage_enabled;
}
void Aura::set_damage_enabled(const bool value) {
	_damage_enabled = value;
}

int Aura::get_damage_type() const {
	return _damage_type;
}

void Aura::set_damage_type(const int value) {
	_damage_type = value;
}

int Aura::get_damage_min() const {
	return _damage_min;
}
void Aura::set_damage_min(const int value) {
	_damage_min = value;
}

int Aura::get_damage_max() const {
	return _damage_max;
}
void Aura::set_damage_max(const int value) {
	_damage_max = value;
}

bool Aura::get_damage_can_crit() const {
	return _damage_can_crit;
}
void Aura::set_damage_can_crit(const bool value) {
	_damage_can_crit = value;
}

void Aura::set_damage(const int min, const int max, const bool can_crit) {
	set_damage_enabled(true);
	set_damage_min(min);
	set_damage_max(max);
	set_damage_can_crit(can_crit);
}

//Absorb
bool Aura::get_absorb_enabled() const {
	return _absorb_enabled;
}
void Aura::set_absorb_enabled(const bool value) {
	_absorb_enabled = value;
}

int Aura::get_absorb_damage_type() const {
	return _absorb_damage_type;
}

void Aura::set_absorb_damage_type(const int value) {
	_absorb_damage_type = value;
}

int Aura::get_absorb_min() const {
	return _absorb_min;
}
void Aura::set_absorb_min(const int value) {
	_absorb_min = value;
}

int Aura::get_absorb_max() const {
	return _absorb_max;
}
void Aura::set_absorb_max(const int value) {
	_absorb_max = value;
}

//Heal
bool Aura::get_heal_enabled() const {
	return _heal_enabled;
}
void Aura::set_heal_enabled(const bool value) {
	_heal_enabled = value;
}

int Aura::get_heal_min() const {
	return _heal_min;
}
void Aura::set_heal_min(const int value) {
	_heal_min = value;
}

int Aura::get_heal_max() const {
	return _heal_max;
}
void Aura::set_heal_max(const int value) {
	_heal_max = value;
}

bool Aura::get_heal_can_crit() const {
	return _heal_can_crit;
}
void Aura::set_heal_can_crit(const bool value) {
	_heal_can_crit = value;
}

void Aura::set_heal(const int min, const int max, const bool can_crit) {
	set_heal_enabled(true);
	set_heal_min(min);
	set_heal_max(max);
	set_heal_can_crit(can_crit);
}

//Dispell
bool Aura::get_dispell_enabled() const {
	return _dispell_enabled;
}
void Aura::set_dispell_enabled(const bool value) {
	_dispell_enabled = value;
}

int Aura::get_dispell_count_min() const {
	return _dispell_count_min;
}
void Aura::set_dispell_count_min(const int value) {
	_dispell_count_min = value;
}

int Aura::get_dispell_count_max() const {
	return _dispell_count_max;
}
void Aura::set_dispell_count_max(const int value) {
	_dispell_count_max = value;
}

int Aura::get_dispell_aura_types() const {
	return _dispell_aura_types;
}
void Aura::set_dispell_aura_types(const int value) {
	_dispell_aura_types = value;
}

Ref<EntityResourceCostData> Aura::get_resource_cost() {
	return _resource_cost;
}
void Aura::set_resource_cost(const Ref<EntityResourceCostData> &value) {
	_resource_cost = value;
}

Ref<EntityResourceCostData> Aura::get_resource_give() {
	return _resource_give;
}
void Aura::set_resource_give(const Ref<EntityResourceCostData> &value) {
	_resource_give = value;
}

Aura::Aura() {
	ability_scale_data_id = 1;
	_id = 0;
	_time = 0;
	_tick = 0;
	_aura_type = SpellEnums::AURA_TYPE_NONE;
	_is_debuff = false;
	_hide = false;
	_rank = 0;
	_scale_with_level = EntityDataManager::get_instance()->get_scale_spells_by_default();

	_damage_enabled = false;
	_damage_type = 0;
	_damage_min = 0;
	_damage_max = 0;
	_damage_can_crit = false;

	_absorb_enabled = false;
	_absorb_damage_type = 0;
	_absorb_min = 0;
	_absorb_max = 0;

	_heal_enabled = false;
	_heal_min = 0;
	_heal_max = 0;

	_heal_can_crit = false;

	_dispell_enabled = false;
	_dispell_count_min = 0;
	_dispell_count_max = 0;
	_dispell_aura_types = 0;

	_add_states = 0;
	_remove_effects_with_states = 0;
	_supress_states = 0;

	_aura_stat_attribute_count = 0;
	for (int i = 0; i < MAX_AURA_STATS; ++i) {
		_aura_stat_attributes[i] = Ref<AuraStatAttribute>(memnew(AuraStatAttribute()));
	}

	_trigger_count = 0;
	for (int i = 0; i < MAX_TRIGGER_DATA; ++i) {
		_trigger_datas[i] = Ref<AuraTriggerData>(memnew(AuraTriggerData()));
	}
}

Aura::~Aura() {
	_icon.unref();

	_teaches_spell.unref();

	_visual_spell_effects.unref();

	_damage_scaling_curve.unref();
	_absorb_scaling_curve.unref();
	_heal_scaling_curve.unref();

	for (int i = 0; i < MAX_TRIGGER_DATA; ++i) {
		_trigger_datas[i].unref();
	}

	for (int i = 0; i < MAX_AURA_STATS; ++i) {
		_aura_stat_attributes[i].unref();
	}

	_talent_required_talent.unref();
	_talent_required_spell.unref();
}

//////     Triggers      ///////

int Aura::get_trigger_count() const {
	return _trigger_count;
}

void Aura::set_trigger_count(int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_TRIGGER_DATA);

	_trigger_count = count;
}

SpellEnums::TriggerEvents Aura::get_trigger_event(int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, SpellEnums::TRIGGER_NONE);

	return _trigger_datas[index]->get_trigger_event();
}

void Aura::set_trigger_event(int index, const SpellEnums::TriggerEvents value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index]->set_trigger_event(value);
}

Ref<Aura> Aura::get_trigger_aura(int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, Ref<Aura>(NULL));

	return _trigger_datas[index]->get_aura();
}

void Aura::set_trigger_aura(int index, const Ref<Aura> value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index]->set_aura(value);
}

Ref<Spell> Aura::get_trigger_spell(int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, Ref<Spell>(NULL));

	return _trigger_datas[index]->get_spell();
}

void Aura::set_trigger_spell(int index, const Ref<Spell> value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index]->set_spell(value);
}

////    Talent    ////
Ref<Aura> Aura::get_talent_required_talent() const {
	return _talent_required_talent;
}
void Aura::set_talent_required_talent(const Ref<Aura> rank) {
	_talent_required_talent = rank;
}

Ref<Spell> Aura::get_talent_required_spell() const {
	return _talent_required_talent;
}
void Aura::set_talent_required_spell(const Ref<Spell> spell) {
	_talent_required_spell = spell;
}

////// Aura Stat Attributes //////

int Aura::get_aura_stat_attribute_count() const {
	return _aura_stat_attribute_count;
}
void Aura::set_aura_stat_attribute_count(int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_AURA_STATS);

	_aura_stat_attribute_count = count;
}

Stat::StatId Aura::get_aura_stat_attribute_stat(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, Stat::STAT_ID_NONE);

	return _aura_stat_attributes[index]->get_stat();
}
void Aura::set_aura_stat_attribute_stat(int index, const Stat::StatId value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index]->set_stat(value);
}

float Aura::get_aura_stat_attribute_base_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index]->get_base_mod();
}
void Aura::set_aura_stat_attribute_base_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index]->set_base_mod(value);
}

float Aura::get_aura_stat_attribute_bonus_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index]->get_bonus_mod();
}
void Aura::set_aura_stat_attribute_bonus_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index]->set_bonus_mod(value);
}

float Aura::get_aura_stat_attribute_percent_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index]->get_percent_mod();
}
void Aura::set_aura_stat_attribute_percent_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index]->set_percent_mod(value);
}

void Aura::sapply_simple(Entity *caster, Entity *target, float spell_scale) {
	ERR_FAIL_COND(caster == NULL || target == NULL);

	Ref<AuraApplyInfo> info(memnew(AuraApplyInfo(caster, target, spell_scale, this)));

	sapply(info);
}

void Aura::sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_sapply", info);
}

void Aura::sdeapply(Ref<AuraData> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_sdeapply", info);
}

void Aura::sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_sadd", aura);
}

void Aura::sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_sremove", aura);
}

void Aura::removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_removes_expired", aura);
}

void Aura::removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_removes_dispell", aura);
}

void Aura::supdate(Ref<AuraData> aura, float delta) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_supdate", aura, delta);
}

void Aura::son_before_cast(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast"))
		call("_son_before_cast", aura, info);
}

void Aura::son_before_cast_target(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", aura, info);
}

void Aura::son_cast_finished(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", aura, info);
}

void Aura::son_cast_started(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_started"))
		call("_son_cast_started", aura, info);
}

void Aura::son_cast_failed(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", aura, info);
}

void Aura::son_cast_finished_target(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", aura, info);
}

void Aura::son_spell_cast_success(Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_spell_cast_success"))
		call("_son_spell_cast_success", aura, info);
}

void Aura::son_before_damage_hit(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage_hit"))
		call("_son_before_damage_hit", aura, data);
}

void Aura::son_hit(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_hit"))
		call("_son_hit", aura, data);
}

void Aura::son_before_damage(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage"))
		call("_son_before_damage", aura, data);
}

void Aura::son_damage_receive(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", aura, data);
}

void Aura::son_dealt_damage(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", aura, data);
}

void Aura::son_damage_dealt(Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", aura, data);
}

void Aura::son_before_heal_hit(Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal_hit"))
		call("_son_before_heal_hit", aura, data);
}

void Aura::son_before_heal(Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal"))
		call("_son_before_heal", aura, data);
}

void Aura::son_heal_receive(Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", aura, data);
}

void Aura::son_dealt_heal(Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", aura, data);
}

void Aura::son_heal_dealt(Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", aura, data);
}

void Aura::son_remove_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove_expired"))
		call("_son_remove_expired", aura);
}

void Aura::son_remove(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove"))
		call("_son_remove", aura);
}

void Aura::son_remove_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	if (has_method("_son_remove_dispell"))
		call("_son_remove_dispell", aura);
}

void Aura::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);
}

void Aura::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);
}

void Aura::son_death(Ref<AuraData> data) {
	if (has_method("_son_death"))
		call("_son_death", data);
}

void Aura::son_cooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_added"))
		call("_son_cooldown_added", data, cooldown);
}
void Aura::son_cooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", data, cooldown);
}

void Aura::son_category_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", data, category_cooldown);
}
void Aura::son_category_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", data, category_cooldown);
}

void Aura::son_gcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", data, gcd);
}
void Aura::son_gcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished", data);
}

void Aura::son_physics_process(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished", data);
}

void Aura::son_xp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_xp_gained"))
		call("_son_xp_gained", data, value);
}

void Aura::son_class_level_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_class_level_up"))
		call("_son_class_level_up", data, value);
}

void Aura::son_character_level_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_character_level_up"))
		call("_son_character_level_up", data, value);
}
void Aura::son_entity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_son_entity_resource_added"))
		call("_son_entity_resource_added", data, resource);
}
void Aura::son_entity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_son_entity_resource_removed"))
		call("_son_entity_resource_removed", data, resource);
}
void Aura::con_cast_failed(Ref<AuraData> data, Ref<SpellCastInfo> info) {
	if (has_method("_con_cast_failed"))
		call("_con_cast_failed", data, info);
}
void Aura::con_cast_started(Ref<AuraData> data, Ref<SpellCastInfo> info) {
	if (has_method("_con_cast_started"))
		call("_con_cast_started", data, info);
}
void Aura::con_cast_state_changed(Ref<AuraData> data, Ref<SpellCastInfo> info) {
	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed", data, info);
}
void Aura::con_cast_finished(Ref<AuraData> data, Ref<SpellCastInfo> info) {
	if (has_method("_con_cast_finished"))
		call("_con_cast_finished", data, info);
}
void Aura::con_spell_cast_success(Ref<AuraData> data, Ref<SpellCastInfo> info) {
	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success", data, info);
}

void Aura::con_death(Ref<AuraData> data) {
	if (has_method("_con_death"))
		call("_con_death", data);
}

void Aura::con_cooldown_added(Ref<AuraData> data, Ref<Cooldown> cooldown) {
	if (has_method("_con_cooldown_added"))
		call("_con_cooldown_added", data, cooldown);
}
void Aura::con_cooldown_removed(Ref<AuraData> data, Ref<Cooldown> cooldown) {
	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed", data, cooldown);
}
void Aura::con_category_cooldown_added(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added", data, category_cooldown);
}
void Aura::con_category_cooldown_removed(Ref<AuraData> data, Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed", data, category_cooldown);
}

void Aura::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_added"))
		call("_con_aura_added", data);
}

void Aura::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", data);
}

void Aura::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh", data);
}

void Aura::con_damage_dealt(Ref<AuraData> data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", data, info);
}

void Aura::con_dealt_damage(Ref<AuraData> data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", data, info);
}

void Aura::con_heal_dealt(Ref<AuraData> data, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", data, info);
}

void Aura::con_dealt_heal(Ref<AuraData> data, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", data, info);
}

void Aura::con_gcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", data, gcd);
}
void Aura::con_gcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_gcd_finished"))
		call("_con_gcd_finished", data);
}

void Aura::con_xp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_xp_gained"))
		call("_con_xp_gained", data, value);
}

void Aura::con_class_level_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_class_level_up"))
		call("_con_class_level_up", data, value);
}

void Aura::con_character_level_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_character_level_up"))
		call("_con_character_level_up", data, value);
}

void Aura::con_entity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_con_entity_resource_added"))
		call("_con_entity_resource_added", data, resource);
}
void Aura::con_entity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_con_entity_resource_removed"))
		call("_con_entity_resource_removed", data, resource);
}

//Equipment

bool Aura::should_deny_equip(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!data.is_valid(), false);

	if (has_method("_should_deny_equip"))
		if (call("_should_deny_equip", data, equip_slot, item))
			return true;

	return false;
}

void Aura::son_equip_success(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_equip_success"))
		call("_son_equip_success", data, equip_slot, item, old_item, bag_slot);
}
void Aura::son_equip_fail(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_equip_fail"))
		call("_son_equip_fail", data, equip_slot, item, old_item, bag_slot);
}

void Aura::con_equip_success(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_equip_success"))
		call("_con_equip_success", data, equip_slot, item, old_item, bag_slot);
}
void Aura::con_equip_fail(Ref<AuraData> data, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_equip_fail"))
		call("_con_equip_fail", data, equip_slot, item, old_item, bag_slot);
}

void Aura::setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!data.is_valid() || !info.is_valid());

	//always exists
	call("_setup_aura_data", data, info);
}

void Aura::sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_sapply_passives_damage_receive", info);
}

void Aura::sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_sapply_passives_damage_deal", info);
}

void Aura::calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_calculate_initial_damage", aura_data, info);
}

void Aura::handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_handle_aura_damage", aura_data, info);
}

void Aura::sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_sapply_passives_heal_receive", data);
}

void Aura::sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_sapply_passives_heal_deal", data);
}

void Aura::calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_calculate_initial_heal", aura_data, info);
}

void Aura::handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura_data.is_valid() || !data.is_valid());

	//always exists
	call("_handle_aura_heal", aura_data, data);
}

String Aura::get_name_translated() const {
	if (_text_translation_key != "") {
		return tr(_text_translation_key);
	}

	return get_name();
}

String Aura::get_description(const int class_level, const int character_level) {
	return call("_get_description", class_level, character_level);
}

String Aura::_get_description(const int class_level, const int character_level) {
	String str;

	if (_text_translation_key != "") {
		str = tr(_text_translation_key + "_DESC");
	}

	str = _text_description;

	int pos = str.find_char('%');

	while (pos > 0) {
		if (pos == str.size() - 1)
			break;

		CharType o = str[pos + 1];

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
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, class_level / static_cast<float>(EntityEnums::MAX_CLASS_LEVEL));

					value = static_cast<int>(value);
				}

				if (o == '$') {
					value = Variant::evaluate(Variant::OP_MULTIPLY, value, character_level / static_cast<float>(EntityEnums::MAX_CHARACTER_LEVEL));

					value = static_cast<int>(value);
				}

				str = str.replace(str.substr(pos, nsp - pos) + " ", value);
			}
		}

		pos = str.find_char('%', pos + 1);
	}

	return str;
}

void Aura::_sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(info->get_target() == NULL || info->get_caster() == NULL || !info->get_aura().is_valid());

	Ref<Aura> aura = info->get_aura();

	Ref<AuraData> ad = info->get_target()->gets_aura_by(info->get_caster(), _id);

	if (!ad.is_valid()) {
		ad.instance();

		setup_aura_data(ad, info);

		for (int i = 0; i < _aura_stat_attribute_count; ++i) {
			Ref<AuraStatAttribute> stat_attribute = _aura_stat_attributes[i];

			Ref<Stat> stat = info->get_target()->get_stat_enum(stat_attribute->get_stat());
			stat->add_modifier(_id, stat_attribute->get_base_mod(), stat_attribute->get_bonus_mod(), stat_attribute->get_percent_mod());
		}

		if (_add_states != 0) {
			for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
				int t = 1 << i;

				if ((_add_states & t) != 0) {
					info->get_target()->adds_state_ref(i);
				}
			}
		}

		info->get_target()->adds_aura(ad);
	} else {
		ad->set_remaining_time(_time);
	}
}

void Aura::_sdeapply(Ref<AuraData> data) {
	ERR_FAIL_COND(data->get_owner() == NULL || data->get_caster() == NULL || !data->get_aura().is_valid());

	for (int i = 0; i < _aura_stat_attribute_count; ++i) {
		Ref<AuraStatAttribute> stat_attribute = _aura_stat_attributes[i];

		Ref<Stat> stat = data->get_owner()->get_stat_enum(stat_attribute->get_stat());
		stat->remove_modifier(_id);
	}

	if (_add_states != 0) {
		for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
			int t = 1 << i;

			if ((_add_states & t) != 0) {
				data->get_owner()->removes_state_ref(i);
			}
		}
	}
}

void Aura::_sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	//sapply(aura);

	aura->get_owner()->removes_aura(aura);
	aura->get_owner()->adds_aura(aura);
}

void Aura::_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->removes_aura(aura);
}

void Aura::_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->removes_aura_expired(aura);
}

void Aura::_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->removes_aura_dispelled(aura);
}

void Aura::_supdate(Ref<AuraData> aura, float delta) {

	bool remove = false;

	remove = aura->update(delta);

	//ontick
	while (aura->get_unhandled_ticks() > 0) {

		if (aura->get_damage() != 0) {
			Ref<SpellDamageInfo> dpd = Ref<SpellDamageInfo>(memnew(SpellDamageInfo()));

			dpd->set_aura_damage_source(Ref<Aura>(this));
			dpd->set_dealer(aura->get_caster());
			dpd->set_receiver(aura->get_owner());

			handle_aura_damage(aura, dpd);
		}

		if (aura->get_heal() != 0) {
			Ref<SpellHealInfo> shi = Ref<SpellHealInfo>(memnew(SpellHealInfo()));

			shi->set_aura_heal_source(Ref<Aura>(this));
			shi->set_dealer(aura->get_caster());
			shi->set_receiver(aura->get_owner());

			handle_aura_heal(aura, shi);
		}

		aura->set_unhandled_ticks(aura->get_unhandled_ticks() - 1);
	}

	if (remove) {
		removes_expired(aura);
	}
}

void Aura::_setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(info->get_caster()));

	data->set_aura(Ref<Aura>(this));
	data->set_aura_id(get_id());
	data->set_owner(info->get_target());
	data->set_caster(info->get_caster());
	data->set_tick(info->get_aura()->get_tick());

	if (get_time() > 0.2) {
		data->set_is_timed(true);
		data->set_remaining_time(get_time());

	} else {
		data->set_is_timed(false);
	}

	if (get_damage_enabled()) {
		calculate_initial_damage(data, info);
	}

	if (get_heal_enabled()) {
		calculate_initial_heal(data, info);
	}
}

void Aura::_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
}

void Aura::_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
}

void Aura::_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	aura_data->set_damage(info->get_aura()->get_damage_min());
}

void Aura::_handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(info->get_dealer()));

	Math::randomize();

	info->set_damage(_damage_min + (Math::rand() % (_damage_max = _damage_min)));
	info->set_damage_source_type(SpellDamageInfo::DAMAGE_SOURCE_AURA);

	ERR_FAIL_COND(!ObjectDB::instance_validate(info->get_dealer()));

	info->get_dealer()->sdeal_damage_to(info);
}

void Aura::_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	aura_data->set_heal(info->get_aura()->get_heal_min());
}

void Aura::_handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(info->get_dealer()));

	Math::randomize();

	info->set_heal(_heal_min + (Math::rand() % (_heal_max = _heal_min)));
	info->set_heal_source_type(SpellHealInfo::HEAL_SOURCE_AURA);

	ERR_FAIL_COND(!ObjectDB::instance_validate(info->get_dealer()));

	info->get_dealer()->sdeal_heal_to(info);
}

void Aura::_validate_property(PropertyInfo &property) const {

	String prop = property.name;
	if (prop.begins_with("StatModAttribute_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _aura_stat_attribute_count) {
			property.usage = 0;
		}
	} else if (prop.begins_with("Trigger_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _trigger_count) {
			property.usage = 0;
		}
	}
}

void Aura::_bind_methods() {
	//Commands
	ClassDB::bind_method(D_METHOD("sapply", "info"), &Aura::sapply);
	ClassDB::bind_method(D_METHOD("sdeapply", "aura"), &Aura::sdeapply);
	ClassDB::bind_method(D_METHOD("sadd", "aura"), &Aura::sadd);
	ClassDB::bind_method(D_METHOD("sremove", "aura"), &Aura::sremove);
	ClassDB::bind_method(D_METHOD("removes_expired", "aura"), &Aura::removes_expired);
	ClassDB::bind_method(D_METHOD("removes_dispell", "aura"), &Aura::removes_dispell);
	ClassDB::bind_method(D_METHOD("supdate", "aura", "delta"), &Aura::supdate);

	BIND_VMETHOD(MethodInfo("_sapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_sdeapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_sadd", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_sremove", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_removes_expired", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_removes_dispell", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_supdate", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("_sapply", "info"), &Aura::_sapply);
	ClassDB::bind_method(D_METHOD("_sdeapply", "aura"), &Aura::_sdeapply);
	ClassDB::bind_method(D_METHOD("_sadd", "aura"), &Aura::_sadd);
	ClassDB::bind_method(D_METHOD("_sremove", "aura"), &Aura::_sremove);
	ClassDB::bind_method(D_METHOD("_removes_expired", "aura"), &Aura::_removes_expired);
	ClassDB::bind_method(D_METHOD("_removes_dispell", "aura"), &Aura::_removes_dispell);
	ClassDB::bind_method(D_METHOD("_supdate", "aura", "delta"), &Aura::_supdate);

	//EventHandlers
	ClassDB::bind_method(D_METHOD("son_before_cast", "aura", "info"), &Aura::son_before_cast);
	ClassDB::bind_method(D_METHOD("son_before_cast_target", "aura", "info"), &Aura::son_before_cast_target);
	ClassDB::bind_method(D_METHOD("son_cast_started", "aura", "info"), &Aura::son_cast_started);
	ClassDB::bind_method(D_METHOD("son_cast_failed", "aura", "info"), &Aura::son_cast_failed);
	ClassDB::bind_method(D_METHOD("son_cast_finished", "aura", "info"), &Aura::son_cast_finished);
	ClassDB::bind_method(D_METHOD("son_cast_finished_target", "aura", "info"), &Aura::son_cast_finished_target);
	ClassDB::bind_method(D_METHOD("son_spell_cast_success", "aura", "info"), &Aura::son_spell_cast_success);

	ClassDB::bind_method(D_METHOD("son_before_damage_hit", "aura", "data"), &Aura::son_before_damage_hit);
	ClassDB::bind_method(D_METHOD("son_hit", "aura", "data"), &Aura::son_hit);
	ClassDB::bind_method(D_METHOD("son_before_damage", "aura", "data"), &Aura::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_damage_receive", "aura", "data"), &Aura::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_damage", "aura", "data"), &Aura::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "aura", "data"), &Aura::son_damage_dealt);

	ClassDB::bind_method(D_METHOD("son_before_heal_hit", "aura", "data"), &Aura::son_before_heal_hit);
	ClassDB::bind_method(D_METHOD("son_before_heal", "aura", "data"), &Aura::son_before_heal);
	ClassDB::bind_method(D_METHOD("son_heal_receive", "aura", "data"), &Aura::son_heal_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_heal", "aura", "data"), &Aura::son_dealt_heal);
	ClassDB::bind_method(D_METHOD("son_heal_dealt", "aura", "data"), &Aura::son_heal_dealt);

	ClassDB::bind_method(D_METHOD("son_remove", "aura"), &Aura::son_remove);
	ClassDB::bind_method(D_METHOD("son_remove_expired", "aura"), &Aura::son_remove_expired);
	ClassDB::bind_method(D_METHOD("son_remove_dispell", "aura"), &Aura::son_remove_dispell);

	ClassDB::bind_method(D_METHOD("son_before_aura_applied", "data"), &Aura::son_before_aura_applied);
	ClassDB::bind_method(D_METHOD("son_after_aura_applied", "data"), &Aura::son_after_aura_applied);

	ClassDB::bind_method(D_METHOD("son_death", "data"), &Aura::son_death);

	ClassDB::bind_method(D_METHOD("son_cooldown_added", "data", "cooldown"), &Aura::son_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_cooldown_removed", "data", "cooldown"), &Aura::son_cooldown_removed);

	ClassDB::bind_method(D_METHOD("son_category_cooldown_added", "data", "category_cooldown"), &Aura::son_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_category_cooldown_removed", "data", "category_cooldown"), &Aura::son_category_cooldown_removed);

	ClassDB::bind_method(D_METHOD("son_gcd_started", "data", "gcd"), &Aura::son_gcd_started);
	ClassDB::bind_method(D_METHOD("son_gcd_finished", "data"), &Aura::son_gcd_finished);

	ClassDB::bind_method(D_METHOD("son_physics_process", "data"), &Aura::son_physics_process);

	ClassDB::bind_method(D_METHOD("son_xp_gained", "data", "value"), &Aura::son_xp_gained);
	ClassDB::bind_method(D_METHOD("son_class_level_up", "data", "value"), &Aura::son_class_level_up);
	ClassDB::bind_method(D_METHOD("son_character_level_up", "data", "value"), &Aura::son_character_level_up);

	ClassDB::bind_method(D_METHOD("son_entity_resource_added", "data", "value"), &Aura::son_entity_resource_added);
	ClassDB::bind_method(D_METHOD("son_entity_resource_removed", "data", "value"), &Aura::son_entity_resource_removed);

	BIND_VMETHOD(MethodInfo("_son_before_cast", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_cast_target", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_failed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished_target", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_spell_cast_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_damage_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_heal_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_son_remove", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_remove_expired", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_remove_dispell", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_before_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_after_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_death", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_son_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_son_category_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_son_category_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_son_gcd_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_son_gcd_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_physics_process", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_xp_gained", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_son_class_level_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_son_character_level_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_son_entity_resource_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_son_entity_resource_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	//Clientside Event Handlers
	ClassDB::bind_method(D_METHOD("con_cast_failed", "data", "info"), &Aura::con_cast_failed);
	ClassDB::bind_method(D_METHOD("con_cast_started", "data", "info"), &Aura::con_cast_started);
	ClassDB::bind_method(D_METHOD("con_cast_state_changed", "data", "info"), &Aura::con_cast_state_changed);
	ClassDB::bind_method(D_METHOD("con_cast_finished", "data", "info"), &Aura::con_cast_finished);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "data", "info"), &Aura::con_spell_cast_success);

	ClassDB::bind_method(D_METHOD("con_death", "data"), &Aura::con_death);

	ClassDB::bind_method(D_METHOD("con_cooldown_added", "data", "info"), &Aura::con_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_cooldown_removed", "data", "info"), &Aura::con_cooldown_removed);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_added", "data", "info"), &Aura::con_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_removed", "data", "info"), &Aura::con_category_cooldown_removed);

	ClassDB::bind_method(D_METHOD("con_aura_added", "data"), &Aura::con_aura_added);
	ClassDB::bind_method(D_METHOD("con_aura_removed", "data"), &Aura::con_aura_removed);
	ClassDB::bind_method(D_METHOD("con_aura_refresh", "data"), &Aura::con_aura_refresh);

	ClassDB::bind_method(D_METHOD("con_damage_dealt", "data", "info"), &Aura::con_damage_dealt);
	ClassDB::bind_method(D_METHOD("con_dealt_damage", "data", "info"), &Aura::con_dealt_damage);
	ClassDB::bind_method(D_METHOD("con_heal_dealt", "data", "info"), &Aura::con_heal_dealt);
	ClassDB::bind_method(D_METHOD("con_dealt_heal", "data", "info"), &Aura::con_dealt_heal);

	ClassDB::bind_method(D_METHOD("con_gcd_started", "data", "info"), &Aura::con_gcd_started);
	ClassDB::bind_method(D_METHOD("con_gcd_finished", "data"), &Aura::con_gcd_finished);

	ClassDB::bind_method(D_METHOD("con_xp_gained", "data", "value"), &Aura::con_xp_gained);
	ClassDB::bind_method(D_METHOD("con_class_level_up", "data", "value"), &Aura::con_class_level_up);
	ClassDB::bind_method(D_METHOD("con_character_level_up", "data", "value"), &Aura::con_character_level_up);

	ClassDB::bind_method(D_METHOD("con_entity_resource_added", "data", "value"), &Aura::con_entity_resource_added);
	ClassDB::bind_method(D_METHOD("con_entity_resource_removed", "data", "value"), &Aura::con_entity_resource_removed);

	BIND_VMETHOD(MethodInfo("_con_cast_failed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_state_changed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_con_death", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_con_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_con_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_con_category_cooldown_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_con_category_cooldown_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_con_aura_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_refresh", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_con_damage_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_heal_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_con_gcd_started", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_con_gcd_finished", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_con_xp_gained", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_con_class_level_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_con_character_level_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_con_entity_resource_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_con_entity_resource_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	//Equipment

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_should_deny_equip", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_son_equip_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_son_equip_fail", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_con_equip_success", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_con_equip_fail", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("should_deny_equip", "data", "equip_slot", "item"), &Aura::should_deny_equip);

	ClassDB::bind_method(D_METHOD("son_equip_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::son_equip_success);
	ClassDB::bind_method(D_METHOD("son_equip_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::son_equip_fail);
	ClassDB::bind_method(D_METHOD("con_equip_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::con_equip_success);
	ClassDB::bind_method(D_METHOD("con_equip_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::con_equip_fail);

	//Calculations / Queries
	ClassDB::bind_method(D_METHOD("setup_aura_data", "data", "info"), &Aura::setup_aura_data);

	BIND_VMETHOD(MethodInfo("_setup_aura_data", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));

	ClassDB::bind_method(D_METHOD("_setup_aura_data", "data", "info"), &Aura::_setup_aura_data);

	//damage
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_receive", "data"), &Aura::sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_deal", "data"), &Aura::sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("calculate_initial_damage", "aura_data", "info"), &Aura::calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("handle_aura_damage", "aura_data", "data"), &Aura::handle_aura_damage);

	BIND_VMETHOD(MethodInfo("_sapply_passives_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_sapply_passives_damage_deal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_calculate_initial_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("_sapply_passives_damage_receive", "info"), &Aura::_sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("_sapply_passives_damage_deal", "info"), &Aura::_sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("_calculate_initial_damage", "aura_data", "info"), &Aura::_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("_handle_aura_damage", "aura_data", "info"), &Aura::_handle_aura_damage);

	//heal
	ClassDB::bind_method(D_METHOD("sapply_passives_heal_receive", "data"), &Aura::sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("sapply_passives_heal_deal", "data"), &Aura::sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("calculate_initial_heal", "aura_data", "info"), &Aura::calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("handle_aura_heal", "aura_data", "data"), &Aura::handle_aura_heal);

	BIND_VMETHOD(MethodInfo("_sapply_passives_heal_receive", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_sapply_passives_heal_deal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_calculate_initial_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "spell_heal_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ClassDB::bind_method(D_METHOD("_sapply_passives_heal_receive", "info"), &Aura::_sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("_sapply_passives_heal_deal", "info"), &Aura::_sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("_calculate_initial_heal", "aura_data", "info"), &Aura::_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("_handle_aura_heal", "aura_data", "info"), &Aura::_handle_aura_heal);

	//Properties
	ClassDB::bind_method(D_METHOD("get_id"), &Aura::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &Aura::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_icon"), &Aura::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &Aura::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_time"), &Aura::get_time);
	ClassDB::bind_method(D_METHOD("set_time", "value"), &Aura::set_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "time"), "set_time", "get_time");

	ClassDB::bind_method(D_METHOD("get_tick"), &Aura::get_tick);
	ClassDB::bind_method(D_METHOD("set_tick", "value"), &Aura::set_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "tick"), "set_tick", "get_tick");

	ClassDB::bind_method(D_METHOD("get_is_debuff"), &Aura::get_is_debuff);
	ClassDB::bind_method(D_METHOD("set_is_debuff", "value"), &Aura::set_is_debuff);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "debuff"), "set_is_debuff", "get_is_debuff");

	ClassDB::bind_method(D_METHOD("get_rank"), &Aura::get_rank);
	ClassDB::bind_method(D_METHOD("set_rank", "value"), &Aura::set_rank);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rank"), "set_rank", "get_rank");

	ClassDB::bind_method(D_METHOD("get_scale_with_level"), &Aura::get_scale_with_level);
	ClassDB::bind_method(D_METHOD("set_scale_with_level", "value"), &Aura::set_scale_with_level);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "scale_with_level"), "set_scale_with_level", "get_scale_with_level");

	ClassDB::bind_method(D_METHOD("get_aura_type"), &Aura::get_aura_type);
	ClassDB::bind_method(D_METHOD("set_aura_type", "value"), &Aura::set_aura_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_AURA_TYPES), "set_aura_type", "get_aura_type");

	ClassDB::bind_method(D_METHOD("get_aura_group"), &Aura::get_aura_group);
	ClassDB::bind_method(D_METHOD("set_aura_group", "value"), &Aura::set_aura_group);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_group", PROPERTY_HINT_RESOURCE_TYPE, "AuraGroup"), "set_aura_group", "get_aura_group");

	ClassDB::bind_method(D_METHOD("get_hide"), &Aura::get_hide);
	ClassDB::bind_method(D_METHOD("set_hide", "value"), &Aura::set_hide);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hide"), "set_hide", "get_hide");

	ClassDB::bind_method(D_METHOD("get_ability_scale_data_id"), &Aura::get_ability_scale_data_id);
	ClassDB::bind_method(D_METHOD("set_ability_scale_data_id", "value"), &Aura::set_ability_scale_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "ability_scale_data_id"), "set_ability_scale_data_id", "get_ability_scale_data_id");

	ADD_GROUP("Texts", "text");
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_get_description", PropertyInfo(Variant::INT, "class_level"), PropertyInfo(Variant::INT, "character_level")));

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_translation_key"), &Aura::get_text_translation_key);
	ClassDB::bind_method(D_METHOD("set_text_translation_key", "value"), &Aura::set_text_translation_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_translation_key"), "set_text_translation_key", "get_text_translation_key");

	ClassDB::bind_method(D_METHOD("get_text_description"), &Aura::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &Aura::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description", PROPERTY_HINT_MULTILINE_TEXT), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_name_translated"), &Aura::get_name_translated);
	ClassDB::bind_method(D_METHOD("get_description", "class_level", "character_level"), &Aura::get_description);
	ClassDB::bind_method(D_METHOD("_get_description", "class_level", "character_level"), &Aura::_get_description);

	ClassDB::bind_method(D_METHOD("get_visual_spell_effects"), &Aura::get_visual_spell_effects);
	ClassDB::bind_method(D_METHOD("set_visual_spell_effects", "value"), &Aura::set_visual_spell_effects);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "visual_spell_effects", PROPERTY_HINT_RESOURCE_TYPE, "SpellEffectVisual"), "set_visual_spell_effects", "get_visual_spell_effects");

	ClassDB::bind_method(D_METHOD("get_teaches_spell"), &Aura::get_teaches_spell);
	ClassDB::bind_method(D_METHOD("set_teaches_spell", "next_rank"), &Aura::set_teaches_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "teaches_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_teaches_spell", "get_teaches_spell");

	ADD_GROUP("Damage", "damage");
	//Damage
	ClassDB::bind_method(D_METHOD("get_damage_enabled"), &Aura::get_damage_enabled);
	ClassDB::bind_method(D_METHOD("set_damage_enabled", "value"), &Aura::set_damage_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_enabled"), "set_damage_enabled", "get_damage_enabled");

	ClassDB::bind_method(D_METHOD("get_damage_type"), &Aura::get_damage_type);
	ClassDB::bind_method(D_METHOD("set_damage_type", "value"), &Aura::set_damage_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "set_damage_type", "get_damage_type");

	ClassDB::bind_method(D_METHOD("get_damage_min"), &Aura::get_damage_min);
	ClassDB::bind_method(D_METHOD("set_damage_min", "value"), &Aura::set_damage_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_min"), "set_damage_min", "get_damage_min");

	ClassDB::bind_method(D_METHOD("get_damage_max"), &Aura::get_damage_max);
	ClassDB::bind_method(D_METHOD("set_damage_max", "value"), &Aura::set_damage_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_max"), "set_damage_max", "get_damage_max");

	ClassDB::bind_method(D_METHOD("get_damage_can_crit"), &Aura::get_damage_can_crit);
	ClassDB::bind_method(D_METHOD("set_damage_can_crit", "value"), &Aura::set_damage_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_can_crit"), "set_damage_can_crit", "get_damage_can_crit");

	ClassDB::bind_method(D_METHOD("set_damage", "min", "max", "can_crit"), &Aura::set_damage);

	ClassDB::bind_method(D_METHOD("get_damage_scaling_curve"), &Aura::get_damage_scaling_curve);
	ClassDB::bind_method(D_METHOD("set_damage_scaling_curve", "curve"), &Aura::set_damage_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damage_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_damage_scaling_curve", "get_damage_scaling_curve");

	ADD_GROUP("Absorb", "absorb");
	//Absorb
	ClassDB::bind_method(D_METHOD("get_absorb_enabled"), &Aura::get_absorb_enabled);
	ClassDB::bind_method(D_METHOD("set_absorb_enabled", "value"), &Aura::set_absorb_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "absorb_enabled"), "set_absorb_enabled", "get_absorb_enabled");

	ClassDB::bind_method(D_METHOD("get_absorb_damage_type"), &Aura::get_absorb_damage_type);
	ClassDB::bind_method(D_METHOD("set_absorb_damage_type", "value"), &Aura::set_absorb_damage_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "set_absorb_damage_type", "get_absorb_damage_type");

	ClassDB::bind_method(D_METHOD("get_absorb_min"), &Aura::get_absorb_min);
	ClassDB::bind_method(D_METHOD("set_absorb_min", "value"), &Aura::set_absorb_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_min"), "set_absorb_min", "get_absorb_min");

	ClassDB::bind_method(D_METHOD("get_absorb_max"), &Aura::get_absorb_max);
	ClassDB::bind_method(D_METHOD("set_absorb_max", "value"), &Aura::set_absorb_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_max"), "set_absorb_max", "get_absorb_max");

	ClassDB::bind_method(D_METHOD("get_absorb_scaling_curve"), &Aura::get_absorb_scaling_curve);
	ClassDB::bind_method(D_METHOD("set_absorb_scaling_curve", "curve"), &Aura::set_absorb_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "absorb_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_absorb_scaling_curve", "get_absorb_scaling_curve");

	ADD_GROUP("Heal", "heal");
	//Heal
	ClassDB::bind_method(D_METHOD("get_heal_enabled"), &Aura::get_heal_enabled);
	ClassDB::bind_method(D_METHOD("set_heal_enabled", "value"), &Aura::set_heal_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_enabled"), "set_heal_enabled", "get_heal_enabled");

	ClassDB::bind_method(D_METHOD("get_heal_min"), &Aura::get_heal_min);
	ClassDB::bind_method(D_METHOD("set_heal_min", "value"), &Aura::set_heal_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_min"), "set_heal_min", "get_heal_min");

	ClassDB::bind_method(D_METHOD("get_heal_max"), &Aura::get_heal_max);
	ClassDB::bind_method(D_METHOD("set_heal_max", "value"), &Aura::set_heal_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_max"), "set_heal_max", "get_heal_max");

	ClassDB::bind_method(D_METHOD("get_heal_can_crit"), &Aura::get_heal_can_crit);
	ClassDB::bind_method(D_METHOD("set_heal_can_crit", "value"), &Aura::set_heal_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_can_crit"), "set_heal_can_crit", "get_heal_can_crit");

	ClassDB::bind_method(D_METHOD("set_heal", "min", "max", "can_crit"), &Aura::set_heal);

	ClassDB::bind_method(D_METHOD("get_heal_scaling_curve"), &Aura::get_heal_scaling_curve);
	ClassDB::bind_method(D_METHOD("set_heal_scaling_curve", "curve"), &Aura::set_heal_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "heal_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_heal_scaling_curve", "get_heal_scaling_curve");

	ADD_GROUP("Dispell", "dispell");
	ClassDB::bind_method(D_METHOD("get_dispell_enabled"), &Aura::get_dispell_enabled);
	ClassDB::bind_method(D_METHOD("set_dispell_enabled", "value"), &Aura::set_dispell_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dispell_enabled"), "set_dispell_enabled", "get_dispell_enabled");

	ClassDB::bind_method(D_METHOD("get_dispell_count_min"), &Aura::get_dispell_count_min);
	ClassDB::bind_method(D_METHOD("set_dispell_count_min", "value"), &Aura::set_dispell_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_min"), "set_dispell_count_min", "get_dispell_count_min");

	ClassDB::bind_method(D_METHOD("get_dispell_count_max"), &Aura::get_dispell_count_max);
	ClassDB::bind_method(D_METHOD("set_dispell_count_max", "value"), &Aura::set_dispell_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_max"), "set_dispell_count_max", "get_dispell_count_max");

	ClassDB::bind_method(D_METHOD("get_dispell_aura_types"), &Aura::get_dispell_aura_types);
	ClassDB::bind_method(D_METHOD("set_dispell_aura_types", "value"), &Aura::set_dispell_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "set_dispell_aura_types", "get_dispell_aura_types");

	//Resources
	ADD_GROUP("Resources", "resource");
	ClassDB::bind_method(D_METHOD("get_resource_cost"), &Aura::get_resource_cost);
	ClassDB::bind_method(D_METHOD("set_resource_cost", "value"), &Aura::set_resource_cost);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_cost", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "set_resource_cost", "get_resource_cost");

	ClassDB::bind_method(D_METHOD("get_resource_give"), &Aura::get_resource_give);
	ClassDB::bind_method(D_METHOD("set_resource_give", "value"), &Aura::set_resource_give);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_give", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "set_resource_give", "get_resource_give");

	ADD_GROUP("States", "states");
	ClassDB::bind_method(D_METHOD("get_add_states"), &Aura::get_add_states);
	ClassDB::bind_method(D_METHOD("set_add_states", "value"), &Aura::set_add_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "states_add", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "set_add_states", "get_add_states");

	ClassDB::bind_method(D_METHOD("get_remove_effects_with_states"), &Aura::get_remove_effects_with_states);
	ClassDB::bind_method(D_METHOD("set_remove_effects_with_states", "value"), &Aura::set_remove_effects_with_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "states_remove_effects", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "set_remove_effects_with_states", "get_remove_effects_with_states");

	ClassDB::bind_method(D_METHOD("get_supress_states"), &Aura::get_supress_states);
	ClassDB::bind_method(D_METHOD("set_supress_states", "value"), &Aura::set_supress_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "states_supress", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "set_supress_states", "get_supress_states");

	////    Talents    ////
	ADD_GROUP("Talent", "talent");
	ClassDB::bind_method(D_METHOD("get_talent_required_talent"), &Aura::get_talent_required_talent);
	ClassDB::bind_method(D_METHOD("set_talent_required_talent", "next_rank"), &Aura::set_talent_required_talent);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "talent_required_talent", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_talent_required_talent", "get_talent_required_talent");

	ClassDB::bind_method(D_METHOD("get_talent_required_spell"), &Aura::get_talent_required_spell);
	ClassDB::bind_method(D_METHOD("set_talent_required_spell", "next_rank"), &Aura::set_talent_required_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "talent_required_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_talent_required_spell", "get_talent_required_spell");

	////    Triggers    ////
	ADD_GROUP("Triggers", "trigger");
	ClassDB::bind_method(D_METHOD("get_trigger_count"), &Aura::get_trigger_count);
	ClassDB::bind_method(D_METHOD("set_trigger_count", "count"), &Aura::set_trigger_count);

	ClassDB::bind_method(D_METHOD("get_trigger_event", "index"), &Aura::get_trigger_event);
	ClassDB::bind_method(D_METHOD("set_trigger_event", "index", "value"), &Aura::set_trigger_event);

	ClassDB::bind_method(D_METHOD("get_trigger_aura", "index"), &Aura::get_trigger_aura);
	ClassDB::bind_method(D_METHOD("set_trigger_aura", "index", "value"), &Aura::set_trigger_aura);

	ClassDB::bind_method(D_METHOD("get_trigger_spell", "index"), &Aura::get_trigger_spell);
	ClassDB::bind_method(D_METHOD("set_trigger_spell", "index", "value"), &Aura::set_trigger_spell);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "trigger_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_TRIGGER_DATA), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_trigger_count", "get_trigger_count");

	for (int i = 0; i < MAX_TRIGGER_DATA; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "Trigger_" + itos(i) + "/event", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_EVENTS, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_trigger_event", "get_trigger_event", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Trigger_" + itos(i) + "/aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_trigger_aura", "get_trigger_aura", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Trigger_" + itos(i) + "/spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_trigger_spell", "get_trigger_spell", i);
	}

	ADD_GROUP("Attributes", "attribute");
	//AuraStatAttributes
	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute_count"), &Aura::get_aura_stat_attribute_count);
	ClassDB::bind_method(D_METHOD("set_aura_stat_attribute_count", "count"), &Aura::set_aura_stat_attribute_count);

	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute_stat", "index"), &Aura::get_aura_stat_attribute_stat);
	ClassDB::bind_method(D_METHOD("set_aura_stat_attribute_stat", "index", "value"), &Aura::set_aura_stat_attribute_stat);

	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute_base_mod", "index"), &Aura::get_aura_stat_attribute_base_mod);
	ClassDB::bind_method(D_METHOD("set_aura_stat_attribute_base_mod", "index", "value"), &Aura::set_aura_stat_attribute_base_mod);

	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute_bonus_mod", "index"), &Aura::get_aura_stat_attribute_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_aura_stat_attribute_bonus_mod", "index", "value"), &Aura::set_aura_stat_attribute_bonus_mod);

	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute_percent_mod", "index"), &Aura::get_aura_stat_attribute_percent_mod);
	ClassDB::bind_method(D_METHOD("set_aura_stat_attribute_percent_mod", "index", "value"), &Aura::set_aura_stat_attribute_percent_mod);

	ClassDB::bind_method(D_METHOD("get_aura_stat_attribute", "index"), &Aura::get_aura_stat_attribute);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "attribute_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_AURA_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_aura_stat_attribute_count", "get_aura_stat_attribute_count");

	for (int i = 0; i < MAX_AURA_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "StatModAttribute_" + itos(i) + "/stat", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura_stat_attribute_stat", "get_aura_stat_attribute_stat", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "StatModAttribute_" + itos(i) + "/base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura_stat_attribute_base_mod", "get_aura_stat_attribute_base_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "StatModAttribute_" + itos(i) + "/bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura_stat_attribute_bonus_mod", "get_aura_stat_attribute_bonus_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "StatModAttribute_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura_stat_attribute_percent_mod", "get_aura_stat_attribute_percent_mod", i);
	}

	ClassDB::bind_method(D_METHOD("is_talent"), &Aura::is_talent);

	BIND_CONSTANT(MAX_AURA_STATS);
	BIND_CONSTANT(MAX_TRIGGER_DATA);
}
