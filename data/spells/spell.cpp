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

#include "spell.h"

#include "../../entities/resources/entity_resource_cost_data.h"
#include "../../entities/skills/entity_skill_data.h"
#include "../auras/aura.h"
#include "../items/craft_recipe.h"

#include "../../entities/auras/aura_data.h"

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

Ref<Aura> Spell::spell_cast_on_caster_get(const int index) {
	ERR_FAIL_INDEX_V(index, _spells_cast_on_caster.size(), Ref<Aura>());

	return _spells_cast_on_caster[index];
}
void Spell::spell_cast_on_caster_set(const int index, const Ref<Aura> &spell) {
	ERR_FAIL_INDEX(index, _spells_cast_on_caster.size());

	_spells_cast_on_caster.set(index, Ref<Aura>(spell));
}

Vector<Variant> Spell::spells_cast_on_caster_get() {
	VARIANT_ARRAY_GET(_spells_cast_on_caster);
}
void Spell::spells_cast_on_caster_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _spells_cast_on_caster, Aura);
}

////    Target Aura Apply    ////

int Spell::spells_cast_on_target_num_get() const {
	return _spells_cast_on_target.size();
}
void Spell::spells_cast_on_target_num_set(const int value) {
	_spells_cast_on_target.resize(value);
}

Ref<Aura> Spell::spell_cast_on_target_get(const int index) {
	ERR_FAIL_INDEX_V(index, _spells_cast_on_target.size(), Ref<Aura>());

	return _spells_cast_on_target[index];
}
void Spell::spell_cast_on_target_set(const int index, const Ref<Aura> &spell) {
	ERR_FAIL_INDEX(index, _spells_cast_on_target.size());

	_spells_cast_on_target.set(index, Ref<Aura>(spell));
}

Vector<Variant> Spell::spells_cast_on_target_get() {
	VARIANT_ARRAY_GET(_spells_cast_on_target);
}
void Spell::spells_cast_on_target_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _spells_cast_on_target, Aura);
}

////    Apply Auras On Learn    ////

int Spell::on_learn_cast_spells_num_get() const {
	return _on_learn_cast_spells.size();
}
void Spell::on_learn_cast_spells_num_set(const int value) {
	_on_learn_cast_spells.resize(value);
}

Ref<Aura> Spell::spell_cast_on_learn_get(int index) {
	ERR_FAIL_INDEX_V(index, _on_learn_cast_spells.size(), Ref<Aura>());

	return _on_learn_cast_spells[index];
}
void Spell::spell_cast_on_learn_set(const int index, const Ref<Aura> &spell) {
	ERR_FAIL_INDEX(index, _on_learn_cast_spells.size());

	_on_learn_cast_spells.set(index, Ref<Aura>(spell));
}

Vector<Variant> Spell::spells_cast_on_learn_get() {
	VARIANT_ARRAY_GET(_on_learn_cast_spells);
}
void Spell::spells_cast_on_learn_set(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _on_learn_cast_spells, Aura);
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

	for (int i = 0; i < _spells_cast_on_caster.size(); ++i) {
		Ref<AuraApplyInfo> aai;
		aai.instance();

		aai->caster_set(info->caster_get());
		aai->target_set(info->caster_get());
		aai->spell_scale_set(1);
		aai->set_aura(_spells_cast_on_caster[i]);

		_spells_cast_on_caster.get(i)->aura_sapply(aai);
	}

	if (has_target) {
		for (int i = 0; i < _spells_cast_on_target.size(); ++i) {
			Ref<Aura> aura = _spells_cast_on_target.get(i);

			Ref<AuraData> ad;

			if (aura->aura_get_aura_group().is_valid()) {
				ad = info->target_get()->aura_gets_with_group_by_bind(info->caster_get(), aura->aura_get_aura_group());
			} else {
				ad = info->target_get()->aura_gets_by(info->caster_get(), aura->get_id());
			}

			if (ad.is_valid()) {
				info->target_get()->aura_removes_exact(ad);
			}

			Ref<AuraApplyInfo> aai;
			aai.instance();

			aai->caster_set(info->caster_get());
			aai->target_set(info->target_get());
			aai->spell_scale_set(1);
			aai->set_aura(aura);

			aura->aura_sapply(aai);
		}
	}
}

void Spell::_validate_property(PropertyInfo &property) const {
	if (property.name.ends_with("_stat")) {
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
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "info"), &Spell::notification_scast);

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
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_caster", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "spells_cast_on_caster_set", "spells_cast_on_caster_get");

	//ADD_GROUP("Target Aura Apply", "target_aura_applys");
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_num_get"), &Spell::spells_cast_on_target_num_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_num_set", "value"), &Spell::spells_cast_on_target_num_set);

	ClassDB::bind_method(D_METHOD("spell_cast_on_target_get", "index"), &Spell::spell_cast_on_target_get);
	ClassDB::bind_method(D_METHOD("spell_cast_on_target_set", "index", "spell"), &Spell::spell_cast_on_target_set);

	ClassDB::bind_method(D_METHOD("spells_cast_on_target_get"), &Spell::spells_cast_on_target_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_target_set", "target_aura_applys"), &Spell::spells_cast_on_target_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_target", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "spells_cast_on_target_set", "spells_cast_on_target_get");

	//ADD_GROUP("Apply Auras On Learn", "on_learn_auras");
	ClassDB::bind_method(D_METHOD("on_learn_cast_spells_num_get"), &Spell::on_learn_cast_spells_num_get);
	ClassDB::bind_method(D_METHOD("on_learn_cast_spells_num_set", "value"), &Spell::on_learn_cast_spells_num_set);

	ClassDB::bind_method(D_METHOD("spell_cast_on_learn_get", "index"), &Spell::spell_cast_on_learn_get);
	ClassDB::bind_method(D_METHOD("spell_cast_on_learn_set", "index", "spell"), &Spell::spell_cast_on_learn_set);

	ClassDB::bind_method(D_METHOD("spells_cast_on_learn_get"), &Spell::spells_cast_on_learn_get);
	ClassDB::bind_method(D_METHOD("spells_cast_on_learn_set", "spells"), &Spell::spells_cast_on_learn_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells_cast_on_learn", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "spells_cast_on_learn_set", "spells_cast_on_learn_get");
	
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
}
