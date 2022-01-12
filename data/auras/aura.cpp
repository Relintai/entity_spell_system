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

#include "aura.h"

#include "../../entities/resources/entity_resource_cost_data.h"
#include "../../singletons/ess.h"

#include "../../defines.h"

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

int Aura::get_rank() const {
	return _rank;
}
void Aura::set_rank(const int value) {
	_rank = value;
}

float Aura::aura_get_time() const {
	return _aura_time;
}
void Aura::aura_set_time(const float value) {
	_aura_time = value;
}

float Aura::aura_get_tick() const {
	return _aura_tick;
}
void Aura::aura_set_tick(const float value) {
	_aura_tick = value;
}

Ref<AuraGroup> Aura::aura_get_aura_group() {
	return _aura_group;
}
void Aura::aura_set_aura_group(const Ref<AuraGroup> &value) {
	_aura_group = value;
}

bool Aura::aura_get_is_debuff() const {
	return _aura_is_debuff;
}
void Aura::aura_set_is_debuff(const bool value) {
	_aura_is_debuff = value;
}

SpellEnums::AuraType Aura::aura_get_aura_type() const {
	return _aura_type;
}
void Aura::aura_set_aura_type(SpellEnums::AuraType value) {
	_aura_type = value;
}

bool Aura::aura_get_scale_with_level() const {
	return _aura_scale_with_level;
}
void Aura::aura_set_scale_with_level(const bool value) {
	_aura_scale_with_level = value;
}

String Aura::aura_get_text_translation_key() const {
	return _aura_text_translation_key;
}
void Aura::aura_set_text_translation_key(const String &value) {
	_aura_text_translation_key = value;
}

String Aura::aura_get_text_description() const {
	return _aura_text_description;
}
void Aura::aura_set_text_description(const String description) {
	_aura_text_description = description;
}

bool Aura::aura_get_hide() const {
	return _aura_hide;
}
void Aura::aura_set_hide(const bool value) {
	_aura_hide = value;
}

Ref<SpellEffectVisual> Aura::aura_get_visual_spell_effects() {
	return _aura_visual_spell_effects;
}
void Aura::aura_set_visual_spell_effects(const Ref<SpellEffectVisual> &value) {
	_aura_visual_spell_effects = value;
}

int Aura::aura_get_ability_scale_data_id() const {
	return _aura_ability_scale_data_id;
}
void Aura::aura_set_ability_scale_data_id(const int value) {
	_aura_ability_scale_data_id = value;
}

float Aura::aura_damage_get_scale_for_level(const int level) const {
	//return this->getDamageLevelScaling()->Evaluate((float)(level));
	return 1;
}
float Aura::aura_heal_get_scale_for_level(const int level) const {
	//return this->getHealLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Aura::aura_absorb_get_scale_for_level(const int level) const {
	//return this->getAbsorbLevelScaling()->Evaluate((float)(level));
	return 1;
}

bool Aura::aura_diminishing_return_enabled_get() const {
	return _aura_diminishing_return_enabled;
}
void Aura::aura_diminishing_return_enabled_set(const bool value) {
	_aura_diminishing_return_enabled = value;
}

int Aura::aura_diminishing_return_category_get() const {
	return _aura_diminishing_return_category;
}
void Aura::aura_diminishing_return_category_set(const int value) {
	_aura_diminishing_return_category = value;
}

Ref<Spell> Aura::aura_get_teaches_spell() {
	return _aura_teaches_spell;
}
void Aura::aura_set_teaches_spell(const Ref<Spell> &spell) {
	_aura_teaches_spell = spell;
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
bool Aura::aura_damage_get_enabled() const {
	return _aura_damage_enabled;
}
void Aura::aura_damage_set_enabled(const bool value) {
	_aura_damage_enabled = value;
}

int Aura::aura_damage_get_type() const {
	return _aura_damage_type;
}

void Aura::aura_damage_set_type(const int value) {
	_aura_damage_type = value;
}

int Aura::aura_damage_get_min() const {
	return _aura_damage_min;
}
void Aura::aura_damage_set_min(const int value) {
	_aura_damage_min = value;
}

int Aura::aura_damage_get_max() const {
	return _aura_damage_max;
}
void Aura::aura_damage_set_max(const int value) {
	_aura_damage_max = value;
}

bool Aura::aura_damage_get_can_crit() const {
	return _aura_damage_can_crit;
}
void Aura::aura_damage_set_can_crit(const bool value) {
	_aura_damage_can_crit = value;
}

void Aura::aura_damage_set(const int min, const int max, const bool can_crit) {
	aura_damage_set_enabled(true);
	aura_damage_set_min(min);
	aura_damage_set_max(max);
	aura_damage_set_can_crit(can_crit);
}

//Absorb
bool Aura::aura_absorb_get_enabled() const {
	return _aura_absorb_enabled;
}
void Aura::aura_absorb_set_enabled(const bool value) {
	_aura_absorb_enabled = value;
}

int Aura::aura_absorb_damage_get_type() const {
	return _aura_absorb_damage_type;
}

void Aura::aura_absorb_damage_set_type(const int value) {
	_aura_absorb_damage_type = value;
}

int Aura::aura_absorb_get_min() const {
	return _aura_absorb_min;
}
void Aura::aura_absorb_set_min(const int value) {
	_aura_absorb_min = value;
}

int Aura::aura_absorb_get_max() const {
	return _aura_absorb_max;
}
void Aura::aura_absorb_set_max(const int value) {
	_aura_absorb_max = value;
}

//Heal
bool Aura::aura_heal_get_enabled() const {
	return _aura_heal_enabled;
}
void Aura::aura_heal_set_enabled(const bool value) {
	_aura_heal_enabled = value;
}

int Aura::aura_heal_get_min() const {
	return _aura_heal_min;
}
void Aura::aura_heal_set_min(const int value) {
	_aura_heal_min = value;
}

int Aura::aura_heal_get_max() const {
	return _aura_heal_max;
}
void Aura::aura_heal_set_max(const int value) {
	_aura_heal_max = value;
}

bool Aura::aura_heal_get_can_crit() const {
	return _aura_heal_can_crit;
}
void Aura::aura_heal_set_can_crit(const bool value) {
	_aura_heal_can_crit = value;
}

void Aura::aura_heal_set(const int min, const int max, const bool can_crit) {
	aura_heal_set_enabled(true);
	aura_heal_set_min(min);
	aura_heal_set_max(max);
	aura_heal_set_can_crit(can_crit);
}

//Dispell
bool Aura::aura_dispell_get_enabled() const {
	return _aura_dispell_enabled;
}
void Aura::aura_dispell_set_enabled(const bool value) {
	_aura_dispell_enabled = value;
}

int Aura::aura_dispell_get_count_min() const {
	return _aura_dispell_count_min;
}
void Aura::aura_dispell_set_count_min(const int value) {
	_aura_dispell_count_min = value;
}

int Aura::aura_dispell_get_count_max() const {
	return _aura_dispell_count_max;
}
void Aura::aura_dispell_set_count_max(const int value) {
	_aura_dispell_count_max = value;
}

int Aura::aura_dispell_get_aura_types() const {
	return _aura_dispell_aura_types;
}
void Aura::aura_dispell_set_aura_types(const int value) {
	_aura_dispell_aura_types = value;
}

Ref<EntityResourceCostData> Aura::aura_get_resource_cost() {
	return _aura_resource_cost;
}
void Aura::aura_set_resource_cost(const Ref<EntityResourceCostData> &value) {
	_aura_resource_cost = value;
}

Ref<EntityResourceCostData> Aura::aura_get_resource_give() {
	return _aura_resource_give;
}
void Aura::aura_set_resource_give(const Ref<EntityResourceCostData> &value) {
	_aura_resource_give = value;
}

Aura::Aura() {
	_id = 0;
	_rank = 0;

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

Aura::~Aura() {
	_icon.unref();

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

//////     Triggers      ///////

int Aura::aura_trigger_get_count() const {
	return _aura_trigger_count;
}

void Aura::aura_trigger_set_count(const int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_TRIGGER_DATA);

	_aura_trigger_count = count;
}

SpellEnums::TriggerNotificationType Aura::aura_trigger_get_notification_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA);

	return _aura_trigger_datas[index].notification_type;
}

void Aura::aura_trigger_set_notification_type(const int index, const SpellEnums::TriggerNotificationType value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].notification_type = value;
}

int Aura::aura_trigger_get_notification_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, 0);

	return _aura_trigger_datas[index].notification_data;
}

void Aura::aura_trigger_set_notification_data(const int index, const int value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].notification_data = value;
}

SpellEnums::TriggerType Aura::aura_trigger_get_trigger_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, SpellEnums::TRIGGER_TYPE_NONE);

	return _aura_trigger_datas[index].trigger_type;
}

void Aura::aura_trigger_set_trigger_type(const int index, const SpellEnums::TriggerType value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].trigger_type = value;
}

float Aura::aura_trigger_get_trigger_type_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, 0);

	return _aura_trigger_datas[index].trigger_type_data;
}

void Aura::aura_trigger_set_trigger_type_data(const int index, const float value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].trigger_type_data = value;
}

Ref<Spell> Aura::aura_trigger_get_spell(const int index) const {
	ERR_FAIL_INDEX_V(index, _aura_trigger_count, Ref<Spell>());

	return _aura_trigger_datas[index].spell;
}

void Aura::aura_trigger_set_spell(const int index, const Ref<Spell> &value) {
	ERR_FAIL_COND(index < 0 || index > _aura_trigger_count);

	_aura_trigger_datas[index].spell = value;
}

////    Talent    ////
Ref<Aura> Aura::aura_get_talent_required_talent() const {
	return _aura_talent_required_talent;
}
void Aura::aura_set_talent_required_talent(const Ref<Aura> rank) {
	_aura_talent_required_talent = rank;
}

Ref<Spell> Aura::aura_get_talent_required_spell() const {
	return _aura_talent_required_talent;
}
void Aura::aura_set_talent_required_spell(const Ref<Spell> spell) {
	_aura_talent_required_spell = spell;
}

////// Aura Stat Attributes //////

int Aura::aura_stat_attribute_get_count() const {
	return _aura_stat_attribute_count;
}
void Aura::aura_stat_attribute_set_count(int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_AURA_STATS);

	_aura_stat_attribute_count = count;
}

int Aura::aura_stat_attribute_get_stat(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].stat;
}
void Aura::aura_stat_attribute_set_stat(int index, const int value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].stat = value;
}

float Aura::aura_stat_attribute_get_base_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].base_mod;
}
void Aura::aura_stat_attribute_set_base_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].base_mod = value;
}

float Aura::aura_stat_attribute_get_bonus_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].bonus_mod;
}
void Aura::aura_stat_attribute_set_bonus_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].bonus_mod = value;
}

float Aura::aura_stat_attribute_get_percent_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].percent_mod;
}
void Aura::aura_stat_attribute_set_percent_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].percent_mod = value;
}

void Aura::aura_sapply_simple(Entity *caster, Entity *target, float spell_scale) {
	ERR_FAIL_COND(caster == NULL || target == NULL);

	Ref<AuraApplyInfo> info(memnew(AuraApplyInfo(caster, target, spell_scale, this)));

	aura_sapply(info);
}

void Aura::aura_sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply", info);
}

void Aura::aura_sdeapply(Ref<AuraData> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sdeapply", info);
}

void Aura::aura_sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_sadd", aura);
}

void Aura::aura_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_sremove", aura);
}

void Aura::aura_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_removes_expired", aura);
}

void Aura::aura_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_removes_dispell", aura);
}

void Aura::aura_supdate(Ref<AuraData> aura, float delta) {
	ERR_FAIL_COND(!aura.is_valid());

	//always exists
	call("_aura_supdate", aura, delta);
}

void Aura::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);
}
void Aura::notification_sheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, aura, data);
}
void Aura::notification_scast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_scast"))
		call("_notification_scast", what, aura, info);
}
void Aura::notification_sdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, aura, data);
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

void Aura::notification_sdeath(Ref<AuraData> data) {
	if (has_method("_notification_sdeath"))
		call("_notification_sdeath", data);
}

void Aura::notification_scooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scooldown_added"))
		call("_notification_scooldown_added", data, id, value);
}
void Aura::notification_scooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scooldown_removed"))
		call("_notification_scooldown_removed", data, id, value);
}

void Aura::notification_scategory_cooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scategory_cooldown_added"))
		call("_notification_scategory_cooldown_added", data, id, value);
}
void Aura::notification_scategory_cooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_scategory_cooldown_removed"))
		call("_notification_scategory_cooldown_removed", data, id, value);
}

void Aura::notification_sgcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sgcd_started"))
		call("_notification_sgcd_started", data, gcd);
}
void Aura::notification_sgcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", data);
}

void Aura::son_physics_process(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", data);
}

void Aura::notification_sxp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_sxp_gained"))
		call("_notification_sxp_gained", data, value);
}

void Aura::notification_slevel_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_slevel_up"))
		call("_notification_slevel_up", data, value);
}

void Aura::notification_sentity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_sentity_resource_added"))
		call("_notification_sentity_resource_added", data, resource);
}
void Aura::notification_sentity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_sentity_resource_removed"))
		call("_notification_sentity_resource_removed", data, resource);
}

void Aura::notification_caura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_caura"))
		call("_notification_caura", what, data);
}
void Aura::notification_cheal(int what, Ref<AuraData> aura, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cheal"))
		call("_notification_cheal", what, aura, data);
}
void Aura::notification_ccast(int what, Ref<AuraData> aura, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_ccast"))
		call("_notification_ccast", what, aura, info);
}
void Aura::notification_cdamage(int what, Ref<AuraData> aura, Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!aura.is_valid());
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cdamage"))
		call("_notification_cdamage", what, aura, data);
}

void Aura::notification_cdeath(Ref<AuraData> data) {
	if (has_method("_notification_cdeath"))
		call("_notification_cdeath", data);
}

void Aura::notification_ccooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccooldown_added"))
		call("_notification_ccooldown_added", data, id, value);
}
void Aura::notification_ccooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccooldown_removed"))
		call("_notification_ccooldown_removed", data, id, value);
}
void Aura::notification_ccategory_cooldown_added(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccategory_cooldown_added"))
		call("_notification_ccategory_cooldown_added", data, id, value);
}
void Aura::notification_ccategory_cooldown_removed(Ref<AuraData> data, int id, float value) {
	if (has_method("_notification_ccategory_cooldown_removed"))
		call("_notification_ccategory_cooldown_removed", data, id, value);
}

void Aura::notification_cgcd_started(Ref<AuraData> data, float gcd) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cgcd_started"))
		call("_notification_cgcd_started", data, gcd);
}
void Aura::notification_cgcd_finished(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cgcd_finished"))
		call("_notification_cgcd_finished", data);
}

void Aura::notification_cxp_gained(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_cxp_gained"))
		call("_notification_cxp_gained", data, value);
}

void Aura::notification_clevel_up(Ref<AuraData> data, int value) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_clevel_up"))
		call("_notification_clevel_up", data, value);
}

void Aura::notification_centity_resource_added(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_centity_resource_added"))
		call("_notification_centity_resource_added", data, resource);
}
void Aura::notification_centity_resource_removed(Ref<AuraData> data, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!data.is_valid());
	ERR_FAIL_COND(!resource.is_valid());

	if (has_method("_notification_centity_resource_removed"))
		call("_notification_centity_resource_removed", data, resource);
}

//Equipment

bool Aura::equip_should_deny(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!data.is_valid(), false);

	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", data, equip_slot, item))
			return true;

	return false;
}

void Aura::equip_son_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_son_success"))
		call("_equip_son_success", data, equip_slot, item, old_item, bag_slot);
}
void Aura::equip_son_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", data, equip_slot, item, old_item, bag_slot);
}

void Aura::equip_con_success(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_con_success"))
		call("_equip_con_success", data, equip_slot, item, old_item, bag_slot);
}
void Aura::equip_con_fail(Ref<AuraData> data, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", data, equip_slot, item, old_item, bag_slot);
}

void Aura::setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!data.is_valid() || !info.is_valid());

	//always exists
	call("_setup_aura_data", data, info);
}

void Aura::aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply_passives_damage_receive", info);
}

void Aura::aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//always exists
	call("_aura_sapply_passives_damage_deal", info);
}

void Aura::aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_aura_calculate_initial_damage", aura_data, info);
}

void Aura::handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_handle_aura_damage", aura_data, info);
}

void Aura::aura_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_aura_sapply_passives_heal_receive", data);
}

void Aura::aura_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//always exists
	call("_aura_sapply_passives_heal_deal", data);
}

void Aura::aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!aura_data.is_valid() || !info.is_valid());

	//always exists
	call("_aura_calculate_initial_heal", aura_data, info);
}

void Aura::handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!aura_data.is_valid() || !data.is_valid());

	//always exists
	call("_handle_aura_heal", aura_data, data);
}

String Aura::aura_get_name_translated() const {
	if (_aura_text_translation_key != "") {
		return tr(_aura_text_translation_key);
	}

	return get_name();
}

String Aura::aura_get_description(const int class_level, const int character_level) {
	return call("_aura_get_description", class_level, character_level);
}

String Aura::_aura_get_description(const int class_level, const int character_level) {
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

void Aura::_aura_sapply(Ref<AuraApplyInfo> info) {
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

void Aura::_aura_sdeapply(Ref<AuraData> data) {
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

void Aura::_aura_sadd(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	//sapply(aura);

	aura->get_owner()->aura_removes(aura);
	aura->get_owner()->aura_adds(aura);
}

void Aura::_aura_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes(aura);
}

void Aura::_aura_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes_expired(aura);
}

void Aura::_aura_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	aura_sdeapply(aura);

	aura->get_owner()->aura_removes_dispelled(aura);
}

void Aura::_aura_supdate(Ref<AuraData> aura, float delta) {
	bool remove = false;

	remove = aura->update(delta);

	//ontick
	while (aura->get_unhandled_ticks() > 0) {
		if (aura->damage_get() != 0) {
			Ref<SpellDamageInfo> dpd = Ref<SpellDamageInfo>(memnew(SpellDamageInfo()));

			dpd->aura_source_set(Ref<Aura>(this));
			dpd->dealer_set(aura->caster_get());
			dpd->receiver_set(aura->get_owner());

			handle_aura_damage(aura, dpd);
		}

		if (aura->heal_get() != 0) {
			Ref<SpellHealInfo> shi = Ref<SpellHealInfo>(memnew(SpellHealInfo()));

			shi->aura_source_set(Ref<Aura>(this));
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

void Aura::_setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(info->caster_get()));

	data->set_aura(Ref<Aura>(this));
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

void Aura::_aura_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
}

void Aura::_aura_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
}

void Aura::_aura_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_damage = aura_damage_get_min();
	int max_damage = aura_damage_get_max();

	Math::randomize();
	int damage = min_damage + Math::rand() % (max_damage - min_damage);

	if (aura_get_scale_with_level()) {
		damage = static_cast<int>(damage * static_cast<float>(info->caster_get()->gets_level()) / static_cast<float>(ESS::get_singleton()->get_max_character_level()));
	}

	aura_data->damage_set(damage);
}

void Aura::_handle_aura_damage(Ref<AuraData> aura_data, Ref<SpellDamageInfo> info) {
	if (info->dealer_get() && !INSTANCE_VALIDATE(info->dealer_get())) {
		info->dealer_set(NULL);
	}

	info->damage_set(aura_data->damage_get());
	info->aura_source_set(Ref<Aura>(this));

	if (info->dealer_get()) {
		info->dealer_get()->sdeal_damage_to(info);
	} else {
		info->receiver_get()->stake_damage(info);
	}
}

void Aura::_aura_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_aura_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_aura_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_heal = aura_heal_get_min();
	int max_heal = aura_heal_get_max();

	Math::randomize();
	int heal = min_heal + Math::rand() % (max_heal - min_heal);

	if (aura_get_scale_with_level()) {
		heal = static_cast<int>(heal * static_cast<float>(info->caster_get()->gets_level()) / static_cast<float>(ESS::get_singleton()->get_max_character_level()));
	}

	aura_data->heal_set(heal);
}

void Aura::_handle_aura_heal(Ref<AuraData> aura_data, Ref<SpellHealInfo> info) {
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

void Aura::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("stat_attribute_")) {
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
	} else if (prop.begins_with("trigger_")) {
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
	}
}

void Aura::_bind_methods() {
	//Commands
	ClassDB::bind_method(D_METHOD("aura_sapply", "info"), &Aura::aura_sapply);
	ClassDB::bind_method(D_METHOD("aura_sdeapply", "aura"), &Aura::aura_sdeapply);
	ClassDB::bind_method(D_METHOD("aura_sadd", "aura"), &Aura::aura_sadd);
	ClassDB::bind_method(D_METHOD("aura_sremove", "aura"), &Aura::aura_sremove);
	ClassDB::bind_method(D_METHOD("aura_removes_expired", "aura"), &Aura::aura_removes_expired);
	ClassDB::bind_method(D_METHOD("aura_removes_dispell", "aura"), &Aura::aura_removes_dispell);
	ClassDB::bind_method(D_METHOD("aura_supdate", "aura", "delta"), &Aura::aura_supdate);

	BIND_VMETHOD(MethodInfo("_aura_sapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sdeapply", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_sadd", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_sremove", PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_removes_expired", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_removes_dispell", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_aura_supdate", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("_aura_sapply", "info"), &Aura::_aura_sapply);
	ClassDB::bind_method(D_METHOD("_aura_sdeapply", "aura"), &Aura::_aura_sdeapply);
	ClassDB::bind_method(D_METHOD("_aura_sadd", "aura"), &Aura::_aura_sadd);
	ClassDB::bind_method(D_METHOD("_aura_sremove", "aura"), &Aura::_aura_sremove);
	ClassDB::bind_method(D_METHOD("_aura_removes_expired", "aura"), &Aura::_aura_removes_expired);
	ClassDB::bind_method(D_METHOD("_aura_removes_dispell", "aura"), &Aura::_aura_removes_dispell);
	ClassDB::bind_method(D_METHOD("_aura_supdate", "aura", "delta"), &Aura::_aura_supdate);

	//EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &Aura::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "aura", "info"), &Aura::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "aura", "info"), &Aura::notification_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "aura", "info"), &Aura::notification_sdamage);

	ClassDB::bind_method(D_METHOD("son_remove", "aura"), &Aura::son_remove);
	ClassDB::bind_method(D_METHOD("son_remove_expired", "aura"), &Aura::son_remove_expired);
	ClassDB::bind_method(D_METHOD("son_remove_dispell", "aura"), &Aura::son_remove_dispell);

	ClassDB::bind_method(D_METHOD("notification_sdeath", "data"), &Aura::notification_sdeath);

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "data", "cooldown"), &Aura::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "data", "cooldown"), &Aura::notification_scooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "data", "category_cooldown"), &Aura::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "data", "category_cooldown"), &Aura::notification_scategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started", "data", "gcd"), &Aura::notification_sgcd_started);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished", "data"), &Aura::notification_sgcd_finished);

	ClassDB::bind_method(D_METHOD("son_physics_process", "data"), &Aura::son_physics_process);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "data", "value"), &Aura::notification_sxp_gained);
	ClassDB::bind_method(D_METHOD("notification_slevel_up", "data", "value"), &Aura::notification_slevel_up);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "data", "value"), &Aura::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "data", "value"), &Aura::notification_sentity_resource_removed);

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

	BIND_VMETHOD(MethodInfo("_son_physics_process", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_slevel_up", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::INT, "value")));

	//Clientside Event Handlers
	BIND_VMETHOD(MethodInfo("_notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_caura", "what", "data"), &Aura::notification_caura);
	ClassDB::bind_method(D_METHOD("notification_cheal", "what", "aura", "info"), &Aura::notification_cheal);
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "aura", "info"), &Aura::notification_ccast);
	ClassDB::bind_method(D_METHOD("notification_cdamage", "what", "aura", "info"), &Aura::notification_cdamage);

	ClassDB::bind_method(D_METHOD("notification_cdeath", "data"), &Aura::notification_cdeath);

	ClassDB::bind_method(D_METHOD("notification_ccooldown_added", "data", "info"), &Aura::notification_ccooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccooldown_removed", "data", "info"), &Aura::notification_ccooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_added", "data", "info"), &Aura::notification_ccategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_removed", "data", "info"), &Aura::notification_ccategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_cgcd_started", "data", "info"), &Aura::notification_cgcd_started);
	ClassDB::bind_method(D_METHOD("notification_cgcd_finished", "data"), &Aura::notification_cgcd_finished);

	ClassDB::bind_method(D_METHOD("notification_cxp_gained", "data", "value"), &Aura::notification_cxp_gained);
	ClassDB::bind_method(D_METHOD("notification_clevel_up", "data", "value"), &Aura::notification_clevel_up);

	ClassDB::bind_method(D_METHOD("notification_centity_resource_added", "data", "value"), &Aura::notification_centity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_centity_resource_removed", "data", "value"), &Aura::notification_centity_resource_removed);

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

	ClassDB::bind_method(D_METHOD("equip_should_deny", "data", "equip_slot", "item"), &Aura::equip_should_deny);

	ClassDB::bind_method(D_METHOD("equip_son_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::equip_son_success);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::equip_son_fail);
	ClassDB::bind_method(D_METHOD("equip_con_success", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::equip_con_success);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "data", "equip_slot", "item", "old_item", "bag_slot"), &Aura::equip_con_fail);

	//Calculations / Queries
	ClassDB::bind_method(D_METHOD("setup_aura_data", "data", "info"), &Aura::setup_aura_data);

	BIND_VMETHOD(MethodInfo("_setup_aura_data", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));

	ClassDB::bind_method(D_METHOD("_setup_aura_data", "data", "info"), &Aura::_setup_aura_data);

	//damage
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_damage_receive", "data"), &Aura::aura_sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_damage_deal", "data"), &Aura::aura_sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("aura_calculate_initial_damage", "aura_data", "info"), &Aura::aura_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("handle_aura_damage", "aura_data", "data"), &Aura::handle_aura_damage);

	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_damage_deal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_calculate_initial_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_damage_receive", "info"), &Aura::_aura_sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_damage_deal", "info"), &Aura::_aura_sapply_passives_damage_deal);
	ClassDB::bind_method(D_METHOD("_aura_calculate_initial_damage", "aura_data", "info"), &Aura::_aura_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("_handle_aura_damage", "aura_data", "info"), &Aura::_handle_aura_damage);

	//heal
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_heal_receive", "data"), &Aura::aura_sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("aura_sapply_passives_heal_deal", "data"), &Aura::aura_sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("aura_calculate_initial_heal", "aura_data", "info"), &Aura::aura_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("handle_aura_heal", "aura_data", "data"), &Aura::handle_aura_heal);

	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_heal_receive", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_sapply_passives_heal_deal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_aura_calculate_initial_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "AuraApplyInfo")));
	BIND_VMETHOD(MethodInfo("_handle_aura_heal", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData"), PropertyInfo(Variant::OBJECT, "spell_heal_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_heal_receive", "info"), &Aura::_aura_sapply_passives_heal_receive);
	ClassDB::bind_method(D_METHOD("_aura_sapply_passives_heal_deal", "info"), &Aura::_aura_sapply_passives_heal_deal);
	ClassDB::bind_method(D_METHOD("_aura_calculate_initial_heal", "aura_data", "info"), &Aura::_aura_calculate_initial_heal);
	ClassDB::bind_method(D_METHOD("_handle_aura_heal", "aura_data", "info"), &Aura::_handle_aura_heal);

	//Properties
	ClassDB::bind_method(D_METHOD("get_id"), &Aura::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &Aura::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_icon"), &Aura::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &Aura::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_rank"), &Aura::get_rank);
	ClassDB::bind_method(D_METHOD("set_rank", "value"), &Aura::set_rank);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rank"), "set_rank", "get_rank");

	ADD_GROUP("Aura", "aura");
	ClassDB::bind_method(D_METHOD("aura_get_time"), &Aura::aura_get_time);
	ClassDB::bind_method(D_METHOD("aura_set_time", "value"), &Aura::aura_set_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "aura_time"), "aura_set_time", "aura_get_time");

	ClassDB::bind_method(D_METHOD("aura_get_tick"), &Aura::aura_get_tick);
	ClassDB::bind_method(D_METHOD("aura_set_tick", "value"), &Aura::aura_set_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "aura_tick"), "aura_set_tick", "aura_get_tick");

	ClassDB::bind_method(D_METHOD("aura_get_is_debuff"), &Aura::aura_get_is_debuff);
	ClassDB::bind_method(D_METHOD("aura_set_is_debuff", "value"), &Aura::aura_set_is_debuff);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_debuff"), "aura_set_is_debuff", "aura_get_is_debuff");

	ClassDB::bind_method(D_METHOD("aura_get_scale_with_level"), &Aura::aura_get_scale_with_level);
	ClassDB::bind_method(D_METHOD("aura_set_scale_with_level", "value"), &Aura::aura_set_scale_with_level);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_scale_with_level"), "aura_set_scale_with_level", "aura_get_scale_with_level");

	ClassDB::bind_method(D_METHOD("aura_get_aura_type"), &Aura::aura_get_aura_type);
	ClassDB::bind_method(D_METHOD("aura_set_aura_type", "value"), &Aura::aura_set_aura_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_AURA_TYPES), "aura_set_aura_type", "aura_get_aura_type");

	ClassDB::bind_method(D_METHOD("aura_get_aura_group"), &Aura::aura_get_aura_group);
	ClassDB::bind_method(D_METHOD("aura_set_aura_group", "value"), &Aura::aura_set_aura_group);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_group", PROPERTY_HINT_RESOURCE_TYPE, "AuraGroup"), "aura_set_aura_group", "aura_get_aura_group");

	ClassDB::bind_method(D_METHOD("aura_get_hide"), &Aura::aura_get_hide);
	ClassDB::bind_method(D_METHOD("aura_set_hide", "value"), &Aura::aura_set_hide);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_hide"), "aura_set_hide", "aura_get_hide");

	ClassDB::bind_method(D_METHOD("aura_get_ability_scale_data_id"), &Aura::aura_get_ability_scale_data_id);
	ClassDB::bind_method(D_METHOD("aura_set_ability_scale_data_id", "value"), &Aura::aura_set_ability_scale_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_ability_scale_data_id"), "aura_set_ability_scale_data_id", "aura_get_ability_scale_data_id");

	ClassDB::bind_method(D_METHOD("aura_get_visual_spell_effects"), &Aura::aura_get_visual_spell_effects);
	ClassDB::bind_method(D_METHOD("aura_set_visual_spell_effects", "value"), &Aura::aura_set_visual_spell_effects);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_visual_spell_effects", PROPERTY_HINT_RESOURCE_TYPE, "SpellEffectVisual"), "aura_set_visual_spell_effects", "aura_get_visual_spell_effects");

	ADD_GROUP("Aura Texts", "aura_text");
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_aura_get_description", PropertyInfo(Variant::INT, "class_level"), PropertyInfo(Variant::INT, "character_level")));

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("aura_get_text_translation_key"), &Aura::aura_get_text_translation_key);
	ClassDB::bind_method(D_METHOD("aura_set_text_translation_key", "value"), &Aura::aura_set_text_translation_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "aura_text_translation_key"), "aura_set_text_translation_key", "aura_get_text_translation_key");

	ClassDB::bind_method(D_METHOD("aura_get_text_description"), &Aura::aura_get_text_description);
	ClassDB::bind_method(D_METHOD("aura_set_text_description", "value"), &Aura::aura_set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "aura_text_description", PROPERTY_HINT_MULTILINE_TEXT), "aura_set_text_description", "aura_get_text_description");

	ClassDB::bind_method(D_METHOD("aura_get_name_translated"), &Aura::aura_get_name_translated);
	ClassDB::bind_method(D_METHOD("aura_get_description", "class_level", "character_level"), &Aura::aura_get_description);
	ClassDB::bind_method(D_METHOD("_aura_get_description", "class_level", "character_level"), &Aura::_aura_get_description);

	ClassDB::bind_method(D_METHOD("aura_get_teaches_spell"), &Aura::aura_get_teaches_spell);
	ClassDB::bind_method(D_METHOD("aura_set_teaches_spell", "next_rank"), &Aura::aura_set_teaches_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_teaches_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "aura_set_teaches_spell", "aura_get_teaches_spell");

	ADD_GROUP("Aura Damage", "aura_damage");
	//Damage
	ClassDB::bind_method(D_METHOD("aura_damage_get_enabled"), &Aura::aura_damage_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_damage_set_enabled", "value"), &Aura::aura_damage_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_damage_enabled"), "aura_damage_set_enabled", "aura_damage_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_damage_get_type"), &Aura::aura_damage_get_type);
	ClassDB::bind_method(D_METHOD("aura_damage_set_type", "value"), &Aura::aura_damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "aura_damage_set_type", "aura_damage_get_type");

	ClassDB::bind_method(D_METHOD("aura_damage_get_min"), &Aura::aura_damage_get_min);
	ClassDB::bind_method(D_METHOD("aura_damage_set_min", "value"), &Aura::aura_damage_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_min"), "damage_set_min", "damage_get_min");

	ClassDB::bind_method(D_METHOD("aura_damage_get_max"), &Aura::aura_damage_get_max);
	ClassDB::bind_method(D_METHOD("aura_damage_set_max", "value"), &Aura::aura_damage_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_damage_max"), "aura_damage_set_max", "aura_damage_get_max");

	ClassDB::bind_method(D_METHOD("aura_damage_get_can_crit"), &Aura::aura_damage_get_can_crit);
	ClassDB::bind_method(D_METHOD("aura_damage_set_can_crit", "value"), &Aura::aura_damage_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_damage_can_crit"), "aura_damage_set_can_crit", "aura_damage_get_can_crit");

	ClassDB::bind_method(D_METHOD("aura_damage_set", "min", "max", "can_crit"), &Aura::aura_damage_set);

	ClassDB::bind_method(D_METHOD("aura_damage_get_scaling_curve"), &Aura::aura_damage_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_damage_set_scaling_curve", "curve"), &Aura::aura_damage_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_damage_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_damage_set_scaling_curve", "aura_damage_get_scaling_curve");

	ADD_GROUP("Aura Absorb", "aura_absorb");
	//Absorb
	ClassDB::bind_method(D_METHOD("aura_absorb_get_enabled"), &Aura::aura_absorb_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_enabled", "value"), &Aura::aura_absorb_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_absorb_enabled"), "aura_absorb_set_enabled", "aura_absorb_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_absorb_damage_get_type"), &Aura::aura_absorb_damage_get_type);
	ClassDB::bind_method(D_METHOD("aura_absorb_damage_set_type", "value"), &Aura::aura_absorb_damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "aura_absorb_damage_set_type", "aura_absorb_damage_get_type");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_min"), &Aura::aura_absorb_get_min);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_min", "value"), &Aura::aura_absorb_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_min"), "aura_absorb_set_min", "aura_absorb_get_min");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_max"), &Aura::aura_absorb_get_max);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_max", "value"), &Aura::aura_absorb_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_absorb_max"), "aura_absorb_set_max", "aura_absorb_get_max");

	ClassDB::bind_method(D_METHOD("aura_absorb_get_scaling_curve"), &Aura::aura_absorb_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_absorb_set_scaling_curve", "curve"), &Aura::aura_absorb_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_absorb_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_absorb_set_scaling_curve", "aura_absorb_get_scaling_curve");

	ADD_GROUP("Aura Heal", "aura_heal");
	//Heal
	ClassDB::bind_method(D_METHOD("aura_heal_get_enabled"), &Aura::aura_heal_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_heal_set_enabled", "value"), &Aura::aura_heal_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_heal_enabled"), "aura_heal_set_enabled", "aura_heal_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_heal_get_min"), &Aura::aura_heal_get_min);
	ClassDB::bind_method(D_METHOD("aura_heal_set_min", "value"), &Aura::aura_heal_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_heal_min"), "aura_heal_set_min", "aura_heal_get_min");

	ClassDB::bind_method(D_METHOD("aura_heal_get_max"), &Aura::aura_heal_get_max);
	ClassDB::bind_method(D_METHOD("aura_heal_set_max", "value"), &Aura::aura_heal_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_heal_max"), "aura_heal_set_max", "aura_heal_get_max");

	ClassDB::bind_method(D_METHOD("aura_heal_get_can_crit"), &Aura::aura_heal_get_can_crit);
	ClassDB::bind_method(D_METHOD("aura_heal_set_can_crit", "value"), &Aura::aura_heal_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_heal_can_crit"), "aura_heal_set_can_crit", "aura_heal_get_can_crit");

	ClassDB::bind_method(D_METHOD("aura_heal_set", "min", "max", "can_crit"), &Aura::aura_heal_set);

	ClassDB::bind_method(D_METHOD("aura_heal_get_scaling_curve"), &Aura::aura_heal_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("aura_heal_set_scaling_curve", "curve"), &Aura::aura_heal_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_heal_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "aura_heal_set_scaling_curve", "aura_heal_get_scaling_curve");

	ADD_GROUP("Aura Dispell", "aura_dispell");
	ClassDB::bind_method(D_METHOD("aura_dispell_get_enabled"), &Aura::aura_dispell_get_enabled);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_enabled", "value"), &Aura::aura_dispell_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_dispell_enabled"), "aura_dispell_set_enabled", "aura_dispell_get_enabled");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_count_min"), &Aura::aura_dispell_get_count_min);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_count_min", "value"), &Aura::aura_dispell_set_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_count_min"), "aura_dispell_set_count_min", "aura_dispell_get_count_min");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_count_max"), &Aura::aura_dispell_get_count_max);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_count_max", "value"), &Aura::aura_dispell_set_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_count_max"), "aura_dispell_set_count_max", "aura_dispell_get_count_max");

	ClassDB::bind_method(D_METHOD("aura_dispell_get_aura_types"), &Aura::aura_dispell_get_aura_types);
	ClassDB::bind_method(D_METHOD("aura_dispell_set_aura_types", "value"), &Aura::aura_dispell_set_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "aura_dispell_set_aura_types", "aura_dispell_get_aura_types");

	//Resources
	ADD_GROUP("Aura Resources", "aura_resource");
	ClassDB::bind_method(D_METHOD("aura_get_resource_cost"), &Aura::aura_get_resource_cost);
	ClassDB::bind_method(D_METHOD("aura_set_resource_cost", "value"), &Aura::aura_set_resource_cost);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_resource_cost", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "aura_set_resource_cost", "aura_get_resource_cost");

	ClassDB::bind_method(D_METHOD("aura_get_resource_give"), &Aura::aura_get_resource_give);
	ClassDB::bind_method(D_METHOD("aura_set_resource_give", "value"), &Aura::aura_set_resource_give);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_resource_give", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceCostData"), "aura_set_resource_give", "aura_get_resource_give");

	ADD_GROUP("Aura States", "aura_states");
	ClassDB::bind_method(D_METHOD("aura_get_add_states"), &Aura::aura_get_add_states);
	ClassDB::bind_method(D_METHOD("aura_set_add_states", "value"), &Aura::aura_set_add_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_add", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_add_states", "aura_get_add_states");

	ClassDB::bind_method(D_METHOD("aura_get_remove_effects_with_states"), &Aura::aura_get_remove_effects_with_states);
	ClassDB::bind_method(D_METHOD("aura_set_remove_effects_with_states", "value"), &Aura::aura_set_remove_effects_with_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_remove_effects", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_remove_effects_with_states", "aura_get_remove_effects_with_states");

	ClassDB::bind_method(D_METHOD("aura_get_supress_states"), &Aura::aura_get_supress_states);
	ClassDB::bind_method(D_METHOD("aura_set_supress_states", "value"), &Aura::aura_set_supress_states);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_states_supress", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES), "aura_set_supress_states", "aura_get_supress_states");

	//Diminishing Returns
	ADD_GROUP("Aura Diminishing Returns", "aura_diminishing_return");
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_enabled_get"), &Aura::aura_diminishing_return_enabled_get);
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_enabled_set", "value"), &Aura::aura_diminishing_return_enabled_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "aura_diminishing_return_enabled"), "aura_diminishing_return_enabled_set", "aura_diminishing_return_enabled_get");

	ClassDB::bind_method(D_METHOD("aura_diminishing_return_category_get"), &Aura::aura_diminishing_return_category_get);
	ClassDB::bind_method(D_METHOD("aura_diminishing_return_category_set", "value"), &Aura::aura_diminishing_return_category_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_diminishing_return_category", PROPERTY_HINT_ENUM, ""), "aura_diminishing_return_category_set", "aura_diminishing_return_category_get");

	////    Talents    ////
	ADD_GROUP("Aura Talent", "aura_talent");
	ClassDB::bind_method(D_METHOD("aura_get_talent_required_talent"), &Aura::aura_get_talent_required_talent);
	ClassDB::bind_method(D_METHOD("aura_set_talent_required_talent", "next_rank"), &Aura::aura_set_talent_required_talent);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_talent_required_talent", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "aura_set_talent_required_talent", "aura_get_talent_required_talent");

	ClassDB::bind_method(D_METHOD("aura_get_talent_required_spell"), &Aura::aura_get_talent_required_spell);
	ClassDB::bind_method(D_METHOD("aura_set_talent_required_spell", "next_rank"), &Aura::aura_set_talent_required_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_talent_required_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "aura_set_talent_required_spell", "aura_get_talent_required_spell");

	////    Triggers    ////
	ADD_GROUP("Aura Triggers", "aura_trigger");
	ClassDB::bind_method(D_METHOD("aura_trigger_get_count"), &Aura::aura_trigger_get_count);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_count", "count"), &Aura::aura_trigger_set_count);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_notification_type", "index"), &Aura::aura_trigger_get_notification_type);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_notification_type", "index", "value"), &Aura::aura_trigger_set_notification_type);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_notification_data", "index"), &Aura::aura_trigger_get_notification_data);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_notification_data", "index", "value"), &Aura::aura_trigger_set_notification_data);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_trigger_type", "index"), &Aura::aura_trigger_get_trigger_type);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_trigger_type", "index", "value"), &Aura::aura_trigger_set_trigger_type);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_trigger_type_data", "index"), &Aura::aura_trigger_get_trigger_type_data);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_trigger_type_data", "index", "value"), &Aura::aura_trigger_set_trigger_type_data);

	ClassDB::bind_method(D_METHOD("aura_trigger_get_spell", "index"), &Aura::aura_trigger_get_spell);
	ClassDB::bind_method(D_METHOD("aura_trigger_set_spell", "index", "value"), &Aura::aura_trigger_set_spell);

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
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_count"), &Aura::aura_stat_attribute_get_count);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_count", "count"), &Aura::aura_stat_attribute_set_count);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_stat", "index"), &Aura::aura_stat_attribute_get_stat);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_stat", "index", "value"), &Aura::aura_stat_attribute_set_stat);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_base_mod", "index"), &Aura::aura_stat_attribute_get_base_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_base_mod", "index", "value"), &Aura::aura_stat_attribute_set_base_mod);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_bonus_mod", "index"), &Aura::aura_stat_attribute_get_bonus_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_bonus_mod", "index", "value"), &Aura::aura_stat_attribute_set_bonus_mod);

	ClassDB::bind_method(D_METHOD("aura_stat_attribute_get_percent_mod", "index"), &Aura::aura_stat_attribute_get_percent_mod);
	ClassDB::bind_method(D_METHOD("aura_stat_attribute_set_percent_mod", "index", "value"), &Aura::aura_stat_attribute_set_percent_mod);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_stat_attribute_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_AURA_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "aura_stat_attribute_set_count", "aura_stat_attribute_get_count");

	for (int i = 0; i < MAX_AURA_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "aura_stat_attribute_" + itos(i) + "/stat", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_stat", "aura_stat_attribute_get_stat", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_base_mod", "aura_stat_attribute_get_base_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_bonus_mod", "aura_stat_attribute_get_bonus_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "aura_stat_attribute_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "aura_stat_attribute_set_percent_mod", "aura_stat_attribute_get_percent_mod", i);
	}

	ClassDB::bind_method(D_METHOD("aura_is_talent"), &Aura::aura_is_talent);

	BIND_CONSTANT(MAX_AURA_STATS);
	BIND_CONSTANT(MAX_TRIGGER_DATA);
}
