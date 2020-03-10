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

#include "spell.h"

#include "../../entities/resources/entity_resource_cost_data.h"
#include "../../entities/skills/entity_skill_data.h"
#include "../../world_spells/world_spell.h"
#include "../auras/aura.h"
#include "../items/craft_recipe.h"

#include "../../entities/auras/aura_data.h"

#include "../../singletons/entity_data_manager.h"

#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"


int Spell::get_id() const {
	return _id;
}
void Spell::set_id(const int value) {
	_id = value;
}

int Spell::get_spell_type() const {
	return _spell_type;
}
void Spell::set_spell_type(int value) {
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

Ref<WorldSpellData> Spell::get_projectile() {
	return _projectile;
}
void Spell::set_projectile(const Ref<WorldSpellData> &value) {
	_projectile = value;
}

Ref<CraftRecipe> Spell::get_teaches_craft_recipe() {
	return _teaches_craft_recipe;
}
void Spell::set_teaches_craft_recipe(const Ref<CraftRecipe> &value) {
	_teaches_craft_recipe = value;
}

////    Caster Aura Apply    ////

int Spell::get_num_caster_aura_applys() const {
	return _caster_aura_applys.size();
}
void Spell::set_num_caster_aura_applys(const int value) {
	_caster_aura_applys.resize(value);
}

Ref<Aura> Spell::get_caster_aura_apply(const int index) {
	ERR_FAIL_INDEX_V(index, _caster_aura_applys.size(), Ref<Aura>());

	return _caster_aura_applys[index];
}
void Spell::set_caster_aura_apply(const int index, const Ref<Aura> &caster_aura_apply) {
	ERR_FAIL_INDEX(index, _caster_aura_applys.size());

	_caster_aura_applys.set(index, Ref<Aura>(caster_aura_apply));
}

Vector<Variant> Spell::get_caster_aura_applys() {
	Vector<Variant> r;
	for (int i = 0; i < _caster_aura_applys.size(); i++) {
		r.push_back(_caster_aura_applys[i].get_ref_ptr());
	}
	return r;
}
void Spell::set_caster_aura_applys(const Vector<Variant> &caster_aura_applys) {
	_caster_aura_applys.clear();
	for (int i = 0; i < caster_aura_applys.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(caster_aura_applys[i]);

		_caster_aura_applys.push_back(aura);
	}
}

////    Target Aura Apply    ////

int Spell::get_num_target_aura_applys() const {
	return _target_aura_applys.size();
}
void Spell::set_num_target_aura_applys(const int value) {
	_target_aura_applys.resize(value);
}

Ref<Aura> Spell::get_target_aura_apply(const int index) {
	ERR_FAIL_INDEX_V(index, _target_aura_applys.size(), Ref<Aura>());

	return _target_aura_applys[index];
}
void Spell::set_target_aura_apply(const int index, const Ref<Aura> &target_aura_apply) {
	ERR_FAIL_INDEX(index, _target_aura_applys.size());

	_target_aura_applys.set(index, Ref<Aura>(target_aura_apply));
}

Vector<Variant> Spell::get_target_aura_applys() {
	Vector<Variant> r;
	for (int i = 0; i < _target_aura_applys.size(); i++) {
		r.push_back(_target_aura_applys[i].get_ref_ptr());
	}
	return r;
}
void Spell::set_target_aura_applys(const Vector<Variant> &target_aura_applys) {
	_target_aura_applys.clear();
	for (int i = 0; i < target_aura_applys.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(target_aura_applys[i]);

		_target_aura_applys.push_back(aura);
	}
}

////    Apply Auras On Learn    ////

int Spell::get_num_on_learn_auras() const {
	return _on_learn_auras.size();
}
void Spell::set_num_on_learn_auras(const int value) {
	_on_learn_auras.resize(value);
}

Ref<Aura> Spell::get_on_learn_aura(int index) {
	ERR_FAIL_INDEX_V(index, _on_learn_auras.size(), Ref<Aura>());

	return _on_learn_auras[index];
}
void Spell::set_on_learn_aura(const int index, const Ref<Aura> &on_learn_aura_apply) {
	ERR_FAIL_INDEX(index, _on_learn_auras.size());

	_on_learn_auras.set(index, Ref<Aura>(on_learn_aura_apply));
}

Vector<Variant> Spell::get_on_learn_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _on_learn_auras.size(); i++) {
		r.push_back(_on_learn_auras[i].get_ref_ptr());
	}
	return r;
}
void Spell::set_on_learn_auras(const Vector<Variant> &on_learn_aura_applys) {
	_on_learn_auras.clear();
	for (int i = 0; i < on_learn_aura_applys.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(on_learn_aura_applys[i]);

		_on_learn_auras.push_back(aura);
	}
}

////    Range    ////

bool Spell::get_range_enabled() const {
	return _range_enabled;
}
void Spell::set_range_enabled(const bool value) {
	_range_enabled = value;
}

float Spell::get_range() const {
	return _range;
}
void Spell::set_range(const float value) {
	_range = value;
}

bool Spell::get_cast_time_enabled() const {
	return _cast_time_enabled;
}
void Spell::set_cast_time_enabled(const bool value) {
	_cast_time_enabled = value;
}

float Spell::get_cast_time() const {
	return _cast_time;
}
void Spell::set_cast_time(const float value) {
	_cast_time = value;
}

bool Spell::get_damage_enabled() const {
	return _damage_enabled;
}
void Spell::set_damage_enabled(const bool value) {
	_damage_enabled = value;
}

int Spell::get_damage_type() const {
	return _damage_type;
}
void Spell::set_damage_type(const int value) {
	_damage_type = value;
}

int Spell::get_damage_min() const {
	return _damage_min;
}
void Spell::set_damage_min(const int value) {
	_damage_min = value;
}

int Spell::get_damage_max() const {
	return _damage_max;
}
void Spell::set_damage_max(const int value) {
	_damage_max = value;
}

Stat::StatId Spell::get_damage_scale_stat() const {
	return _damage_scale_stat;
}
void Spell::set_damage_scale_stat(const Stat::StatId value) {
	_damage_scale_stat = value;
}

float Spell::get_damage_scale_coeff() const {
	return _damage_scale_coeff;
}
void Spell::set_damage_scale_coeff(const float value) {
	_damage_scale_coeff = value;
}

bool Spell::get_heal_enabled() const {
	return _heal_enabled;
}
void Spell::set_heal_enabled(const bool value) {
	_heal_enabled = value;
}

int Spell::get_heal_min() const {
	return _heal_min;
}
void Spell::set_heal_min(const int value) {
	_heal_min = value;
}

int Spell::get_heal_max() const {
	return _heal_max;
}
void Spell::set_heal_max(const int value) {
	_heal_max = value;
}

Stat::StatId Spell::get_heal_scale_stat() const {
	return _heal_scale_stat;
}
void Spell::set_heal_scale_stat(const Stat::StatId value) {
	_heal_scale_stat = value;
}

float Spell::get_heal_scale_coeff() const {
	return _heal_scale_coeff;
}
void Spell::set_heal_scale_coeff(const float value) {
	_heal_scale_coeff = value;
}

bool Spell::get_dispell_enabled() const {
	return _dispell_enabled;
}
void Spell::set_dispell_enabled(const bool value) {
	_dispell_enabled = value;
}

int Spell::get_dispell_count_min() const {
	return _dispell_count_min;
}
void Spell::set_dispell_count_min(const int value) {
	_dispell_count_min = value;
}

int Spell::get_dispell_count_max() const {
	return _dispell_count_max;
}
void Spell::set_dispell_count_max(const int value) {
	_dispell_count_max = value;
}

int Spell::get_dispell_aura_types() const {
	return _dispell_aura_types;
}
void Spell::set_dispell_aura_types(const int value) {
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

void Spell::sstart_casting_simple(Entity *caster, float spell_scale) {
	ERR_FAIL_COND(!caster || !ObjectDB::instance_validate(caster));

	Ref<SpellCastInfo> info = Ref<SpellCastInfo>(memnew(SpellCastInfo()));

	info->set_caster(caster);
	info->set_target(caster->gets_target());
	info->set_has_cast_time(get_cast_time_enabled());
	info->set_cast_time(get_cast_time());
	info->set_spell_scale(spell_scale);
	info->set_spell(Ref<Spell>(this));

	sstart_casting(info);
}

void Spell::sinterrupt_cast_simple(Entity *caster) {
	ERR_FAIL_COND(!caster || !ObjectDB::instance_validate(caster));

	Ref<SpellCastInfo> info(memnew(SpellCastInfo()));

	info->set_caster(caster);
	info->set_spell(Ref<Spell>(this));

	sinterrupt_cast(info);
}

void Spell::sstart_casting_triggered_simple(Entity *caster) {
	ERR_FAIL_COND(!caster || !ObjectDB::instance_validate(caster));

	Ref<SpellCastInfo> info(memnew(SpellCastInfo()));

	info->set_caster(caster);
	info->set_spell(Ref<Spell>(this));

	sstart_casting_triggered(info);
}

//Script methods

void Spell::sstart_casting(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//Auto self cast. Note: Remove needs_target, and skip this if spell should only target enemies.
	if (info->get_target() == NULL) {
		info->set_target(info->get_caster());
	}

	if (has_method("_sstart_casting")) {
		call("_sstart_casting", info);
	}
}

void Spell::sstart_casting_triggered(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_sstart_casting_triggered")) {
		call("_sstart_casting_triggered", info);
	}
}

void Spell::sinterrupt_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_sinterrupt_cast")) {
		call("_sinterrupt_cast", info);
	}
}

void Spell::sfinish_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_sfinish_cast")) {
		call("_sfinish_cast", info);
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

void Spell::con_spell_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_started")) {
		call("_con_spell_cast_started", info);
	}
}

void Spell::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_success")) {
		call("_con_spell_cast_success", info);
	}
}

void Spell::con_spell_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_failed")) {
		call("_con_spell_cast_failed", info);
	}
}

void Spell::con_spell_cast_ended(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_ended")) {
		call("_con_spell_cast_ended", info);
	}
}

void Spell::con_spell_cast_interrupted(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_interrupted")) {
		call("_con_spell_cast_interrupted", info);
	}
}

void Spell::calculate_initial_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->get_receiver() == NULL);

	call("_calculate_initial_damage", data);
}

void Spell::handle_spell_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->get_receiver() == NULL);

	call("_handle_spell_damage", data);
}

void Spell::calculate_initial_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->get_receiver() == NULL);

	call("_calculate_initial_heal", data);
}

void Spell::handle_spell_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid() || data->get_receiver() == NULL);

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
		info->get_caster()->sstart_global_cooldown(info->get_caster()->get_gcd()->gets_current());
	}
}
void Spell::handle_cooldown(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_cooldown > 0.00001) {
		info->get_caster()->adds_cooldown(_id, _cooldown);
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
	_scale_with_level = EntityDataManager::get_instance()->get_scale_spells_by_default();

	_global_cooldown_enabled = true;
	_is_local_spell = false;

	_range_enabled = false;
	_range = 0;

	_damage_enabled = false;
	_damage_type = 0;
	_damage_min = 0;
	_damage_max = 0;
	_damage_scale_stat = Stat::STAT_ID_NONE;
	_damage_scale_coeff = 0;

	_heal_enabled = false;
	_heal_min = 0;
	_heal_max = 0;
	_heal_scale_stat = Stat::STAT_ID_NONE;
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
}

Spell::~Spell() {
	_caster_aura_applys.clear();
	_target_aura_applys.clear();
	_on_learn_auras.clear();

	_item_cost.unref();
	_required_item.unref();

	_resource_cost.unref();
	_resource_give.unref();

	_icon.unref();

	_visual_spell_effects.unref();

	_world_spell_data.unref();

	_teaches_craft_recipe.unref();
	_projectile.unref();
	_training_required_spell.unref();
	_training_required_skill.unref();
}

void Spell::_sstart_casting(Ref<SpellCastInfo> info) {
	if (info->get_caster()->sis_casting()) {
		return;
	}

	if ((get_global_cooldown_enabled() && info->get_caster()->gets_has_global_cooldown()) ||
			info->get_caster()->hass_category_cooldown(get_spell_type()) ||
			info->get_caster()->hass_cooldown(get_id())) {
		return;
	}

	if (!info->get_caster()->hass_spell_id(get_id())) {
		return;
	}

	if (get_cast_time_enabled()) {
		info->get_caster()->sstart_casting(info);
		return;
	}

	info->get_caster()->sspell_cast_success(info);

	info->get_target()->son_cast_finished_target(info);

	if (get_projectile().is_valid()) {
		handle_projectile(info);
	} else {
		handle_effect(info);
	}

	handle_cooldown(info);

	handle_gcd(info);
}

void Spell::_sfinish_cast(Ref<SpellCastInfo> info) {
	info->get_caster()->son_cast_finished(info);
	info->get_caster()->sspell_cast_success(info);

	if (ObjectDB::instance_validate(info->get_target())) {
		info->get_target()->son_cast_finished_target(info);
	}

	if (get_projectile().is_valid()) {
		handle_projectile(info);
	} else {
		handle_effect(info);
	}

	handle_cooldown(info);
}

void Spell::_son_cast_player_moved(Ref<SpellCastInfo> info) {
	if (get_can_move_while_casting()) {
		info->get_caster()->sfail_cast();
	}
}

void Spell::_son_spell_hit(Ref<SpellCastInfo> info) {
	handle_effect(info);
}

void Spell::_calculate_initial_damage(Ref<SpellDamageInfo> data) {
	Math::randomize();

	data->set_damage(get_damage_min() + (get_damage_max() - get_damage_min() * Math::randf()));
}

void Spell::_handle_spell_damage(Ref<SpellDamageInfo> data) {
	calculate_initial_damage(data);

	data->get_dealer()->sdeal_damage_to(data);
}

void Spell::_calculate_initial_heal(Ref<SpellHealInfo> data) {
	Math::randomize();

	data->set_heal(get_heal_min() + (get_heal_max() - get_heal_min() * Math::randf()));
}

void Spell::_handle_spell_heal(Ref<SpellHealInfo> data) {
	calculate_initial_heal(data);

	data->get_dealer()->sdeal_heal_to(data);
}

void Spell::_handle_projectile(Ref<SpellCastInfo> info) {
	if (_world_spell_data.is_valid()) {
		WorldSpell *ws = memnew(WorldSpell);

		Node *p = info->get_caster()->get_parent();

		ERR_FAIL_COND(!ObjectDB::instance_validate(p));

		p->add_child(ws);
		ws->send(_world_spell_data, info);
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

	bool has_target = ObjectDB::instance_validate(info->get_target());

	if (_target_type == SPELL_TARGET_TYPE_TARGET) {
		if (!has_target)
			return;
	} else if (_target_type == SPELL_TARGET_TYPE_SELF) {
		info->set_target(info->get_caster());
	}

	if (_damage_enabled && has_target) {
		Ref<SpellDamageInfo> sdi;
		sdi.instance();

		sdi->set_damage_source(Ref<Spell>(this));
		sdi->set_dealer(info->get_caster());
		sdi->set_receiver(info->get_target());

		handle_spell_damage(sdi);
	}

	for (int i = 0; i < _caster_aura_applys.size(); ++i) {
		Ref<AuraApplyInfo> aai;
		aai.instance();

		aai->set_caster(info->get_caster());
		aai->set_target(info->get_caster());
		aai->set_spell_scale(1);
		aai->set_aura(_caster_aura_applys[i]);

		_caster_aura_applys.get(i)->sapply(aai);
	}

	if (has_target) {
		for (int i = 0; i < _target_aura_applys.size(); ++i) {
			Ref<Aura> aura = _target_aura_applys.get(i);

			Ref<AuraData> ad;

			if (aura->get_aura_group().is_valid()) {
				ad = info->get_target()->gets_aura_with_group_by_bind(info->get_caster(), aura->get_aura_group());
			} else {
				ad = info->get_target()->gets_aura_by(info->get_caster(), aura->get_id());
			}

			if (ad.is_valid()) {
				info->get_target()->removes_aura_exact(ad);
			}

			Ref<AuraApplyInfo> aai;
			aai.instance();

			aai->set_caster(info->get_caster());
			aai->set_target(info->get_target());
			aai->set_spell_scale(1);
			aai->set_aura(aura);

			aura->sapply(aai);
		}
	}
}

void Spell::_bind_methods() {
	//Commands
	ClassDB::bind_method(D_METHOD("sstart_casting", "info"), &Spell::sstart_casting);
	ClassDB::bind_method(D_METHOD("sstart_casting_triggered", "info"), &Spell::sstart_casting_triggered);
	ClassDB::bind_method(D_METHOD("sinterrupt_cast", "info"), &Spell::sinterrupt_cast);
	ClassDB::bind_method(D_METHOD("sfinish_cast", "info"), &Spell::sfinish_cast);

	BIND_VMETHOD(MethodInfo("_sstart_casting", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_sstart_casting_triggered", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_sinterrupt_cast", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_sfinish_cast", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

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
	ClassDB::bind_method(D_METHOD("con_spell_cast_started", "info"), &Spell::con_spell_cast_started);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "info"), &Spell::con_spell_cast_success);
	ClassDB::bind_method(D_METHOD("con_spell_cast_failed", "info"), &Spell::con_spell_cast_failed);
	ClassDB::bind_method(D_METHOD("con_spell_cast_ended", "info"), &Spell::con_spell_cast_ended);
	ClassDB::bind_method(D_METHOD("con_spell_cast_interrupted", "info"), &Spell::con_spell_cast_interrupted);

	BIND_VMETHOD(MethodInfo("_con_spell_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_success", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_ended", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_interrupted", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

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
	ClassDB::bind_method(D_METHOD("_sstart_casting", "info"), &Spell::_sstart_casting);
	ClassDB::bind_method(D_METHOD("_sfinish_cast", "info"), &Spell::_sfinish_cast);

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

	ClassDB::bind_method(D_METHOD("get_spell_type"), &Spell::get_spell_type);
	ClassDB::bind_method(D_METHOD("set_spell_type", "value"), &Spell::set_spell_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_SPELL_TYPES), "set_spell_type", "get_spell_type");

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

	ClassDB::bind_method(D_METHOD("get_projectile"), &Spell::get_projectile);
	ClassDB::bind_method(D_METHOD("set_projectile", "value"), &Spell::set_projectile);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "projectile", PROPERTY_HINT_RESOURCE_TYPE, "WorldSpellData"), "set_projectile", "get_projectile");

	ClassDB::bind_method(D_METHOD("get_teaches_craft_recipe"), &Spell::get_teaches_craft_recipe);
	ClassDB::bind_method(D_METHOD("set_teaches_craft_recipe", "value"), &Spell::set_teaches_craft_recipe);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "teaches_craft_recipe", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipe"), "set_teaches_craft_recipe", "get_teaches_craft_recipe");

	//ADD_GROUP("Caster Aura Applys", "caster_aura_applys");
	ClassDB::bind_method(D_METHOD("get_num_caster_aura_applys"), &Spell::get_num_caster_aura_applys);
	ClassDB::bind_method(D_METHOD("set_num_caster_aura_applys", "value"), &Spell::set_num_caster_aura_applys);

	ClassDB::bind_method(D_METHOD("get_caster_aura_apply", "index"), &Spell::get_caster_aura_apply);
	ClassDB::bind_method(D_METHOD("set_caster_aura_apply", "index", "aura"), &Spell::set_caster_aura_apply);

	ClassDB::bind_method(D_METHOD("get_caster_aura_applys"), &Spell::get_caster_aura_applys);
	ClassDB::bind_method(D_METHOD("set_caster_aura_applys", "caster_aura_applys"), &Spell::set_caster_aura_applys);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "caster_aura_applys", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_caster_aura_applys", "get_caster_aura_applys");

	//ADD_GROUP("Target Aura Apply", "target_aura_applys");
	ClassDB::bind_method(D_METHOD("get_num_target_aura_applys"), &Spell::get_num_target_aura_applys);
	ClassDB::bind_method(D_METHOD("set_num_target_aura_applys", "value"), &Spell::set_num_target_aura_applys);

	ClassDB::bind_method(D_METHOD("get_target_aura_apply", "index"), &Spell::get_target_aura_apply);
	ClassDB::bind_method(D_METHOD("set_target_aura_apply", "index", "aura"), &Spell::set_target_aura_apply);

	ClassDB::bind_method(D_METHOD("get_target_aura_applys"), &Spell::get_target_aura_applys);
	ClassDB::bind_method(D_METHOD("set_target_aura_applys", "target_aura_applys"), &Spell::set_target_aura_applys);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "target_aura_applys", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_target_aura_applys", "get_target_aura_applys");

	//ADD_GROUP("Apply Auras On Learn", "on_learn_auras");
	ClassDB::bind_method(D_METHOD("get_num_on_learn_auras"), &Spell::get_num_on_learn_auras);
	ClassDB::bind_method(D_METHOD("set_num_on_learn_auras", "value"), &Spell::set_num_on_learn_auras);

	ClassDB::bind_method(D_METHOD("get_on_learn_aura", "index"), &Spell::get_on_learn_aura);
	ClassDB::bind_method(D_METHOD("set_on_learn_aura", "index", "aura"), &Spell::set_on_learn_aura);

	ClassDB::bind_method(D_METHOD("get_on_learn_auras"), &Spell::get_on_learn_auras);
	ClassDB::bind_method(D_METHOD("set_on_learn_auras", "spells"), &Spell::set_on_learn_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "on_learn_auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_on_learn_auras", "get_on_learn_auras");

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
	ClassDB::bind_method(D_METHOD("get_range_enabled"), &Spell::get_range_enabled);
	ClassDB::bind_method(D_METHOD("set_range_enabled", "value"), &Spell::set_range_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "range_enabled"), "set_range_enabled", "get_range_enabled");

	ClassDB::bind_method(D_METHOD("get_range"), &Spell::get_range);
	ClassDB::bind_method(D_METHOD("set_range", "value"), &Spell::set_range);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "range_range"), "set_range", "get_range");

	ADD_GROUP("Cast", "cast");
	ClassDB::bind_method(D_METHOD("get_cast_time_enabled"), &Spell::get_cast_time_enabled);
	ClassDB::bind_method(D_METHOD("set_cast_time_enabled", "value"), &Spell::set_cast_time_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast_enabled"), "set_cast_time_enabled", "get_cast_time_enabled");

	ClassDB::bind_method(D_METHOD("get_cast_time"), &Spell::get_cast_time);
	ClassDB::bind_method(D_METHOD("set_cast_time", "value"), &Spell::set_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cast_cast_time"), "set_cast_time", "get_cast_time");

	ClassDB::bind_method(D_METHOD("get_can_move_while_casting"), &Spell::get_can_move_while_casting);
	ClassDB::bind_method(D_METHOD("set_can_move_while_casting", "value"), &Spell::set_can_move_while_casting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast_can_move_while_casting"), "set_can_move_while_casting", "get_can_move_while_casting");

	ADD_GROUP("Damage", "damage");
	ClassDB::bind_method(D_METHOD("get_damage_enabled"), &Spell::get_damage_enabled);
	ClassDB::bind_method(D_METHOD("set_damage_enabled", "value"), &Spell::set_damage_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage_enabled"), "set_damage_enabled", "get_damage_enabled");

	ClassDB::bind_method(D_METHOD("get_damage_type"), &Spell::get_damage_type);
	ClassDB::bind_method(D_METHOD("set_damage_type", "value"), &Spell::set_damage_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "set_damage_type", "get_damage_type");

	ClassDB::bind_method(D_METHOD("get_damage_min"), &Spell::get_damage_min);
	ClassDB::bind_method(D_METHOD("set_damage_min", "value"), &Spell::set_damage_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_min"), "set_damage_min", "get_damage_min");

	ClassDB::bind_method(D_METHOD("get_damage_max"), &Spell::get_damage_max);
	ClassDB::bind_method(D_METHOD("set_damage_max", "value"), &Spell::set_damage_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_max"), "set_damage_max", "get_damage_max");

	ClassDB::bind_method(D_METHOD("get_damage_scale_stat"), &Spell::get_damage_scale_stat);
	ClassDB::bind_method(D_METHOD("set_damage_scale_stat", "value"), &Spell::set_damage_scale_stat);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_scale_stat", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_damage_scale_stat", "get_damage_scale_stat");

	ClassDB::bind_method(D_METHOD("get_damage_scale_coeff"), &Spell::get_damage_scale_coeff);
	ClassDB::bind_method(D_METHOD("set_damage_scale_coeff", "value"), &Spell::set_damage_scale_coeff);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "damage_scale_coeff"), "set_damage_scale_coeff", "get_damage_scale_coeff");

	ADD_GROUP("Heal", "heal");
	ClassDB::bind_method(D_METHOD("get_heal_enabled"), &Spell::get_heal_enabled);
	ClassDB::bind_method(D_METHOD("set_heal_enabled", "value"), &Spell::set_heal_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal_enabled"), "set_heal_enabled", "get_heal_enabled");

	ClassDB::bind_method(D_METHOD("get_heal_min"), &Spell::get_heal_min);
	ClassDB::bind_method(D_METHOD("set_heal_min", "value"), &Spell::set_heal_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_min"), "set_heal_min", "get_heal_min");

	ClassDB::bind_method(D_METHOD("get_heal_max"), &Spell::get_heal_max);
	ClassDB::bind_method(D_METHOD("set_heal_max", "value"), &Spell::set_heal_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_max"), "set_heal_max", "get_heal_max");

	ClassDB::bind_method(D_METHOD("get_heal_scale_stat"), &Spell::get_heal_scale_stat);
	ClassDB::bind_method(D_METHOD("set_heal_scale_stat", "value"), &Spell::set_heal_scale_stat);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_scale_stat", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_heal_scale_stat", "get_heal_scale_stat");

	ClassDB::bind_method(D_METHOD("get_heal_scale_coeff"), &Spell::get_heal_scale_coeff);
	ClassDB::bind_method(D_METHOD("set_heal_scale_coeff", "value"), &Spell::set_heal_scale_coeff);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "heal_scale_coeff"), "set_heal_scale_coeff", "get_heal_scale_coeff");

	ADD_GROUP("Dispell", "dispell");
	ClassDB::bind_method(D_METHOD("get_dispell_enabled"), &Spell::get_dispell_enabled);
	ClassDB::bind_method(D_METHOD("set_dispell_enabled", "value"), &Spell::set_dispell_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dispell_enabled"), "set_dispell_enabled", "get_dispell_enabled");

	ClassDB::bind_method(D_METHOD("get_dispell_count_min"), &Spell::get_dispell_count_min);
	ClassDB::bind_method(D_METHOD("set_dispell_count_min", "value"), &Spell::set_dispell_count_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_min"), "set_dispell_count_min", "get_dispell_count_min");

	ClassDB::bind_method(D_METHOD("get_dispell_count_max"), &Spell::get_dispell_count_max);
	ClassDB::bind_method(D_METHOD("set_dispell_count_max", "value"), &Spell::set_dispell_count_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_count_max"), "set_dispell_count_max", "get_dispell_count_max");

	ClassDB::bind_method(D_METHOD("get_dispell_aura_types"), &Spell::get_dispell_aura_types);
	ClassDB::bind_method(D_METHOD("set_dispell_aura_types", "value"), &Spell::set_dispell_aura_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dispell_aura_types", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_AURA_FLAG_TYPES), "set_dispell_aura_types", "get_dispell_aura_types");

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
