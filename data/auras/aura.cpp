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

float Aura::damage_get_scale_for_level(const int level) const {
	//return this->getDamageLevelScaling()->Evaluate((float)(level));
	return 1;
}
float Aura::heal_get_scale_for_level(const int level) const {
	//return this->getHealLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Aura::absorb_get_scale_for_level(const int level) const {
	//return this->getAbsorbLevelScaling()->Evaluate((float)(level));
	return 1;
}

bool Aura::diminishing_return_enabled_get() const {
	return _diminishing_return_enabled;
}
void Aura::diminishing_return_enabled_set(const bool value) {
	_diminishing_return_enabled = value;
}

int Aura::diminishing_return_category_get() const {
	return _diminishing_return_category;
}
void Aura::diminishing_return_category_set(const int value) {
	_diminishing_return_category = value;
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
bool Aura::damage_get_enabled() const {
	return _damage_enabled;
}
void Aura::damage_set_enabled(const bool value) {
	_damage_enabled = value;
}

int Aura::damage_get_type() const {
	return _damage_type;
}

void Aura::damage_set_type(const int value) {
	_damage_type = value;
}

int Aura::damage_get_min() const {
	return _damage_min;
}
void Aura::damage_set_min(const int value) {
	_damage_min = value;
}

int Aura::damage_get_max() const {
	return _damage_max;
}
void Aura::damage_set_max(const int value) {
	_damage_max = value;
}

bool Aura::damage_get_can_crit() const {
	return _damage_can_crit;
}
void Aura::damage_set_can_crit(const bool value) {
	_damage_can_crit = value;
}

void Aura::damage_set(const int min, const int max, const bool can_crit) {
	damage_set_enabled(true);
	damage_set_min(min);
	damage_set_max(max);
	damage_set_can_crit(can_crit);
}

//Absorb
bool Aura::absorb_get_enabled() const {
	return _absorb_enabled;
}
void Aura::absorb_set_enabled(const bool value) {
	_absorb_enabled = value;
}

int Aura::absorb_damage_get_type() const {
	return _absorb_damage_type;
}

void Aura::absorb_damage_set_type(const int value) {
	_absorb_damage_type = value;
}

int Aura::absorb_get_min() const {
	return _absorb_min;
}
void Aura::absorb_set_min(const int value) {
	_absorb_min = value;
}

int Aura::absorb_get_max() const {
	return _absorb_max;
}
void Aura::absorb_set_max(const int value) {
	_absorb_max = value;
}

//Heal
bool Aura::heal_get_enabled() const {
	return _heal_enabled;
}
void Aura::heal_set_enabled(const bool value) {
	_heal_enabled = value;
}

int Aura::heal_get_min() const {
	return _heal_min;
}
void Aura::heal_set_min(const int value) {
	_heal_min = value;
}

int Aura::heal_get_max() const {
	return _heal_max;
}
void Aura::heal_set_max(const int value) {
	_heal_max = value;
}

bool Aura::heal_get_can_crit() const {
	return _heal_can_crit;
}
void Aura::heal_set_can_crit(const bool value) {
	_heal_can_crit = value;
}

void Aura::heal_set(const int min, const int max, const bool can_crit) {
	heal_set_enabled(true);
	heal_set_min(min);
	heal_set_max(max);
	heal_set_can_crit(can_crit);
}

//Dispell
bool Aura::dispell_get_enabled() const {
	return _dispell_enabled;
}
void Aura::dispell_set_enabled(const bool value) {
	_dispell_enabled = value;
}

int Aura::dispell_get_count_min() const {
	return _dispell_count_min;
}
void Aura::dispell_set_count_min(const int value) {
	_dispell_count_min = value;
}

int Aura::dispell_get_count_max() const {
	return _dispell_count_max;
}
void Aura::dispell_set_count_max(const int value) {
	_dispell_count_max = value;
}

int Aura::dispell_get_aura_types() const {
	return _dispell_aura_types;
}
void Aura::dispell_set_aura_types(const int value) {
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
	_scale_with_level = ESS::get_singleton()->get_scale_spells_by_default();

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
	_trigger_count = 0;

	_diminishing_return_enabled = false;
	_diminishing_return_category = 0;
}

Aura::~Aura() {
	_icon.unref();

	_teaches_spell.unref();

	_visual_spell_effects.unref();

	_damage_scaling_curve.unref();
	_absorb_scaling_curve.unref();
	_heal_scaling_curve.unref();

	for (int i = 0; i < MAX_TRIGGER_DATA; ++i) {
		_trigger_datas[i].spell.unref();
	}

	_talent_required_talent.unref();
	_talent_required_spell.unref();
}

//////     Triggers      ///////

int Aura::trigger_get_count() const {
	return _trigger_count;
}

void Aura::trigger_set_count(const int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_TRIGGER_DATA);

	_trigger_count = count;
}

SpellEnums::TriggerNotificationType Aura::trigger_get_notification_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, SpellEnums::TRIGGER_NOTIFICATION_TYPE_AURA);

	return _trigger_datas[index].notification_type;
}

void Aura::trigger_set_notification_type(const int index, const SpellEnums::TriggerNotificationType value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index].notification_type = value;
}

int Aura::trigger_get_notification_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, 0);

	return _trigger_datas[index].notification_data;
}

void Aura::trigger_set_notification_data(const int index, const int value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index].notification_data = value;
}

SpellEnums::TriggerType Aura::trigger_get_trigger_type(const int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, SpellEnums::TRIGGER_TYPE_NONE);

	return _trigger_datas[index].trigger_type;
}

void Aura::trigger_set_trigger_type(const int index, const SpellEnums::TriggerType value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index].trigger_type = value;
}

float Aura::trigger_get_trigger_type_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, 0);

	return _trigger_datas[index].trigger_type_data;
}

void Aura::trigger_set_trigger_type_data(const int index, const float value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index].trigger_type_data = value;
}

Ref<Spell> Aura::trigger_get_spell(const int index) const {
	ERR_FAIL_INDEX_V(index, _trigger_count, Ref<Spell>());

	return _trigger_datas[index].spell;
}

void Aura::trigger_set_spell(const int index, const Ref<Spell> &value) {
	ERR_FAIL_COND(index < 0 || index > _trigger_count);

	_trigger_datas[index].spell = value;
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

int Aura::stat_attribute_get_count() const {
	return _aura_stat_attribute_count;
}
void Aura::stat_attribute_set_count(int count) {
	ERR_FAIL_COND(count < 0 || count > MAX_AURA_STATS);

	_aura_stat_attribute_count = count;
}

int Aura::stat_attribute_get_stat(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].stat;
}
void Aura::stat_attribute_set_stat(int index, const int value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].stat = value;
}

float Aura::stat_attribute_get_base_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].base_mod;
}
void Aura::stat_attribute_set_base_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].base_mod = value;
}

float Aura::stat_attribute_get_bonus_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].bonus_mod;
}
void Aura::stat_attribute_set_bonus_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].bonus_mod = value;
}

float Aura::stat_attribute_get_percent_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_AURA_STATS, 0);

	return _aura_stat_attributes[index].percent_mod;
}
void Aura::stat_attribute_set_percent_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_AURA_STATS);

	_aura_stat_attributes[index].percent_mod = value;
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

void Aura::_sapply(Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(info->target_get() == NULL || info->caster_get() == NULL || !info->get_aura().is_valid());

	Ref<AuraData> ad = info->target_get()->aura_gets_by(info->caster_get(), _id);

	if (!ad.is_valid()) {
		ad.instance();

		setup_aura_data(ad, info);

		Entity *owner = ad->get_owner();

		for (int i = 0; i < _aura_stat_attribute_count; ++i) {
			owner->stat_mod(_aura_stat_attributes[i].stat, _aura_stat_attributes[i].base_mod, _aura_stat_attributes[i].bonus_mod, _aura_stat_attributes[i].percent_mod);
		}

		if (_add_states != 0) {
			for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
				int t = 1 << i;

				if ((_add_states & t) != 0) {
					info->target_get()->adds_state_ref(i);
				}
			}
		}

		info->target_get()->aura_adds(ad);
	} else {
		ad->set_remaining_time(_time);
	}
}

void Aura::_sdeapply(Ref<AuraData> data) {
	ERR_FAIL_COND(data->get_owner() == NULL || data->caster_get() == NULL || !data->get_aura().is_valid());

	Entity *owner = data->get_owner();

	for (int i = 0; i < _aura_stat_attribute_count; ++i) {
		owner->stat_mod(_aura_stat_attributes[i].stat, -_aura_stat_attributes[i].base_mod, -_aura_stat_attributes[i].bonus_mod, -_aura_stat_attributes[i].percent_mod);
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

	aura->get_owner()->aura_removes(aura);
	aura->get_owner()->aura_adds(aura);
}

void Aura::_sremove(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->aura_removes(aura);
}

void Aura::_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->aura_removes_expired(aura);
}

void Aura::_removes_dispell(Ref<AuraData> aura) {
	ERR_FAIL_COND(aura->get_owner() == NULL);

	sdeapply(aura);

	aura->get_owner()->aura_removes_dispelled(aura);
}

void Aura::_supdate(Ref<AuraData> aura, float delta) {
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
		removes_expired(aura);
	}
}

void Aura::_setup_aura_data(Ref<AuraData> data, Ref<AuraApplyInfo> info) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(info->caster_get()));

	data->set_aura(Ref<Aura>(this));
	data->set_aura_id(get_id());
	data->set_owner(info->target_get());
	data->caster_set(info->caster_get());
	data->set_tick(info->get_aura()->get_tick());

	if (get_time() > 0.2) {
		data->set_is_timed(true);
		data->set_remaining_time(get_time());

	} else {
		data->set_is_timed(false);
	}

	if (damage_get_enabled()) {
		calculate_initial_damage(data, info);
	}

	if (heal_get_enabled()) {
		calculate_initial_heal(data, info);
	}
}

void Aura::_sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
}

void Aura::_sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
}

void Aura::_calculate_initial_damage(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_damage = damage_get_min();
	int max_damage = damage_get_max();

	Math::randomize();
	int damage = min_damage + Math::rand() % (max_damage - min_damage);

	if (get_scale_with_level()) {
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

void Aura::_sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());
}

void Aura::_calculate_initial_heal(Ref<AuraData> aura_data, Ref<AuraApplyInfo> info) {
	int min_heal = heal_get_min();
	int max_heal = heal_get_max();

	Math::randomize();
	int heal = min_heal + Math::rand() % (max_heal - min_heal);

	if (get_scale_with_level()) {
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
		if (frame >= _trigger_count) {
			property.usage = 0;
		} else {
			if (prop.ends_with("notification_data")) {
				switch (_trigger_datas[frame].notification_type) {
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
	ClassDB::bind_method(D_METHOD("damage_get_enabled"), &Aura::damage_get_enabled);
	ClassDB::bind_method(D_METHOD("damage_set_enabled", "value"), &Aura::damage_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_enabled"), "damage_set_enabled", "damage_get_enabled");

	ClassDB::bind_method(D_METHOD("damage_get_type"), &Aura::damage_get_type);
	ClassDB::bind_method(D_METHOD("damage_set_type", "value"), &Aura::damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "damage_set_type", "damage_get_type");

	ClassDB::bind_method(D_METHOD("damage_get_min"), &Aura::damage_get_min);
	ClassDB::bind_method(D_METHOD("damage_set_min", "value"), &Aura::damage_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_min"), "damage_set_min", "damage_get_min");

	ClassDB::bind_method(D_METHOD("damage_get_max"), &Aura::damage_get_max);
	ClassDB::bind_method(D_METHOD("damage_set_max", "value"), &Aura::damage_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_max"), "damage_set_max", "damage_get_max");

	ClassDB::bind_method(D_METHOD("damage_get_can_crit"), &Aura::damage_get_can_crit);
	ClassDB::bind_method(D_METHOD("damage_set_can_crit", "value"), &Aura::damage_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_can_crit"), "damage_set_can_crit", "damage_get_can_crit");

	ClassDB::bind_method(D_METHOD("damage_set", "min", "max", "can_crit"), &Aura::damage_set);

	ClassDB::bind_method(D_METHOD("damage_get_scaling_curve"), &Aura::damage_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("damage_set_scaling_curve", "curve"), &Aura::damage_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damage_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "damage_set_scaling_curve", "damage_get_scaling_curve");

	ADD_GROUP("Absorb", "absorb");
	//Absorb
	ClassDB::bind_method(D_METHOD("absorb_get_enabled"), &Aura::absorb_get_enabled);
	ClassDB::bind_method(D_METHOD("absorb_set_enabled", "value"), &Aura::absorb_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "absorb_enabled"), "absorb_set_enabled", "absorb_get_enabled");

	ClassDB::bind_method(D_METHOD("absorb_damage_get_type"), &Aura::absorb_damage_get_type);
	ClassDB::bind_method(D_METHOD("absorb_damage_set_type", "value"), &Aura::absorb_damage_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "absorb_damage_set_type", "absorb_damage_get_type");

	ClassDB::bind_method(D_METHOD("absorb_get_min"), &Aura::absorb_get_min);
	ClassDB::bind_method(D_METHOD("absorb_set_min", "value"), &Aura::absorb_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_min"), "absorb_set_min", "absorb_get_min");

	ClassDB::bind_method(D_METHOD("absorb_get_max"), &Aura::absorb_get_max);
	ClassDB::bind_method(D_METHOD("absorb_set_max", "value"), &Aura::absorb_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absorb_max"), "absorb_set_max", "absorb_get_max");

	ClassDB::bind_method(D_METHOD("absorb_get_scaling_curve"), &Aura::absorb_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("absorb_set_scaling_curve", "curve"), &Aura::absorb_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "absorb_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "absorb_set_scaling_curve", "absorb_get_scaling_curve");

	ADD_GROUP("Heal", "heal");
	//Heal
	ClassDB::bind_method(D_METHOD("heal_get_enabled"), &Aura::heal_get_enabled);
	ClassDB::bind_method(D_METHOD("heal_set_enabled", "value"), &Aura::heal_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_enabled"), "heal_set_enabled", "heal_get_enabled");

	ClassDB::bind_method(D_METHOD("heal_get_min"), &Aura::heal_get_min);
	ClassDB::bind_method(D_METHOD("heal_set_min", "value"), &Aura::heal_set_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_min"), "heal_set_min", "heal_get_min");

	ClassDB::bind_method(D_METHOD("heal_get_max"), &Aura::heal_get_max);
	ClassDB::bind_method(D_METHOD("heal_set_max", "value"), &Aura::heal_set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_max"), "heal_set_max", "heal_get_max");

	ClassDB::bind_method(D_METHOD("heal_get_can_crit"), &Aura::heal_get_can_crit);
	ClassDB::bind_method(D_METHOD("heal_set_can_crit", "value"), &Aura::heal_set_can_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_can_crit"), "heal_set_can_crit", "heal_get_can_crit");

	ClassDB::bind_method(D_METHOD("heal_set", "min", "max", "can_crit"), &Aura::heal_set);

	ClassDB::bind_method(D_METHOD("heal_get_scaling_curve"), &Aura::heal_get_scaling_curve);
	ClassDB::bind_method(D_METHOD("heal_set_scaling_curve", "curve"), &Aura::heal_set_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "heal_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "heal_set_scaling_curve", "heal_get_scaling_curve");

	ADD_GROUP("Dispell", "dispell");
	ClassDB::bind_method(D_METHOD("dispell_get_enabled"), &Aura::dispell_get_enabled);
	ClassDB::bind_method(D_METHOD("dispell_set_enabled", "value"), &Aura::dispell_set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dispell_enabled"), "dispell_set_enabled", "dispell_get_enabled");

	ClassDB::bind_method(D_METHOD("dispell_get_count_min"), &Aura::dispell_get_count_min);
	ClassDB::bind_method(D_METHOD("dispell_set_count_min", "value"), &Aura::dispell_set_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_min"), "dispell_set_count_min", "dispell_get_count_min");

	ClassDB::bind_method(D_METHOD("dispell_get_count_max"), &Aura::dispell_get_count_max);
	ClassDB::bind_method(D_METHOD("dispell_set_count_max", "value"), &Aura::dispell_set_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_max"), "dispell_set_count_max", "dispell_get_count_max");

	ClassDB::bind_method(D_METHOD("dispell_get_aura_types"), &Aura::dispell_get_aura_types);
	ClassDB::bind_method(D_METHOD("dispell_set_aura_types", "value"), &Aura::dispell_set_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "dispell_set_aura_types", "dispell_get_aura_types");

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

	//Diminishing Returns
	ADD_GROUP("Diminishing Returns", "diminishing_return");
	ClassDB::bind_method(D_METHOD("diminishing_return_enabled_get"), &Aura::diminishing_return_enabled_get);
	ClassDB::bind_method(D_METHOD("diminishing_return_enabled_set", "value"), &Aura::diminishing_return_enabled_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "diminishing_return_enabled"), "diminishing_return_enabled_set", "diminishing_return_enabled_get");

	ClassDB::bind_method(D_METHOD("diminishing_return_category_get"), &Aura::diminishing_return_category_get);
	ClassDB::bind_method(D_METHOD("diminishing_return_category_set", "value"), &Aura::diminishing_return_category_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "diminishing_return_category", PROPERTY_HINT_ENUM, ""), "diminishing_return_category_set", "diminishing_return_category_get");

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
	ClassDB::bind_method(D_METHOD("trigger_get_count"), &Aura::trigger_get_count);
	ClassDB::bind_method(D_METHOD("trigger_set_count", "count"), &Aura::trigger_set_count);

	ClassDB::bind_method(D_METHOD("trigger_get_notification_type", "index"), &Aura::trigger_get_notification_type);
	ClassDB::bind_method(D_METHOD("trigger_set_notification_type", "index", "value"), &Aura::trigger_set_notification_type);

	ClassDB::bind_method(D_METHOD("trigger_get_notification_data", "index"), &Aura::trigger_get_notification_data);
	ClassDB::bind_method(D_METHOD("trigger_set_notification_data", "index", "value"), &Aura::trigger_set_notification_data);

	ClassDB::bind_method(D_METHOD("trigger_get_trigger_type", "index"), &Aura::trigger_get_trigger_type);
	ClassDB::bind_method(D_METHOD("trigger_set_trigger_type", "index", "value"), &Aura::trigger_set_trigger_type);

	ClassDB::bind_method(D_METHOD("trigger_get_trigger_type_data", "index"), &Aura::trigger_get_trigger_type_data);
	ClassDB::bind_method(D_METHOD("trigger_set_trigger_type_data", "index", "value"), &Aura::trigger_set_trigger_type_data);

	ClassDB::bind_method(D_METHOD("trigger_get_spell", "index"), &Aura::trigger_get_spell);
	ClassDB::bind_method(D_METHOD("trigger_set_spell", "index", "value"), &Aura::trigger_set_spell);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "trigger_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_TRIGGER_DATA), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "trigger_set_count", "trigger_get_count");

	for (int i = 0; i < MAX_TRIGGER_DATA; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "trigger_" + itos(i) + "/notification_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_NOTIFICATION_TYPE, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "trigger_set_notification_type", "trigger_get_notification_type", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "trigger_" + itos(i) + "/notification_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "trigger_set_notification_data", "trigger_get_notification_data", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "trigger_" + itos(i) + "/trigger_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_TYPE, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "trigger_set_trigger_type", "trigger_get_trigger_type", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "trigger_" + itos(i) + "/trigger_type_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "trigger_set_trigger_type_data", "trigger_get_trigger_type_data", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "trigger_" + itos(i) + "/spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "trigger_set_spell", "trigger_get_spell", i);
	}

	ADD_GROUP("Stat Attributes", "stat_attribute");
	//AuraStatAttributes
	ClassDB::bind_method(D_METHOD("stat_attribute_get_count"), &Aura::stat_attribute_get_count);
	ClassDB::bind_method(D_METHOD("stat_attribute_set_count", "count"), &Aura::stat_attribute_set_count);

	ClassDB::bind_method(D_METHOD("stat_attribute_get_stat", "index"), &Aura::stat_attribute_get_stat);
	ClassDB::bind_method(D_METHOD("stat_attribute_set_stat", "index", "value"), &Aura::stat_attribute_set_stat);

	ClassDB::bind_method(D_METHOD("stat_attribute_get_base_mod", "index"), &Aura::stat_attribute_get_base_mod);
	ClassDB::bind_method(D_METHOD("stat_attribute_set_base_mod", "index", "value"), &Aura::stat_attribute_set_base_mod);

	ClassDB::bind_method(D_METHOD("stat_attribute_get_bonus_mod", "index"), &Aura::stat_attribute_get_bonus_mod);
	ClassDB::bind_method(D_METHOD("stat_attribute_set_bonus_mod", "index", "value"), &Aura::stat_attribute_set_bonus_mod);

	ClassDB::bind_method(D_METHOD("stat_attribute_get_percent_mod", "index"), &Aura::stat_attribute_get_percent_mod);
	ClassDB::bind_method(D_METHOD("stat_attribute_set_percent_mod", "index", "value"), &Aura::stat_attribute_set_percent_mod);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_attribute_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_AURA_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "stat_attribute_set_count", "stat_attribute_get_count");

	for (int i = 0; i < MAX_AURA_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "stat_attribute_" + itos(i) + "/stat", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_attribute_set_stat", "stat_attribute_get_stat", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_attribute_" + itos(i) + "/base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_attribute_set_base_mod", "stat_attribute_get_base_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_attribute_" + itos(i) + "/bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_attribute_set_bonus_mod", "stat_attribute_get_bonus_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_attribute_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_attribute_set_percent_mod", "stat_attribute_get_percent_mod", i);
	}

	ClassDB::bind_method(D_METHOD("is_talent"), &Aura::is_talent);

	BIND_CONSTANT(MAX_AURA_STATS);
	BIND_CONSTANT(MAX_TRIGGER_DATA);
}
