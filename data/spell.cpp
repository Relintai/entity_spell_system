#include "spell.h"

#include "aura.h"
#include "craft_recipe.h"
#include "../entities/resources/entity_resource_cost_data.h"

int Spell::get_id() {
	return _id;
}
void Spell::set_id(int value) {
	_id = value;
}

int Spell::get_spell_type() {
	return _spell_type;
}
void Spell::set_spell_type(int value) {
	_spell_type = value;
}

SpellEnums::SpellCategory Spell::get_spell_category() {
	return _spell_category;
}
void Spell::set_spell_category(SpellEnums::SpellCategory value) {
	_spell_category = value;
}

bool Spell::get_hide_from_actionbar() {
	return _hide_from_actionbar;
}
void Spell::set_hide_from_actionbar(bool value) {
	_hide_from_actionbar = value;
}

float Spell::get_cooldown() {
	return _cooldown;
}
void Spell::set_cooldown(float value) {
	_cooldown = value;
}

SpellTargetType Spell::get_target_type() {
	return _target_type;
}
void Spell::set_target_type(SpellTargetType value) {
	_target_type = value;
}

TargetRelationType Spell::get_target_relation_type() {
	return _target_relation_type;
}
void Spell::set_target_relation_type(TargetRelationType value) {
	_target_relation_type = value;
}

int Spell::get_level() {
	return _level;
}
void Spell::set_level(int value) {
	_level = value;
}

int Spell::get_rank() {
	return _rank;
}
void Spell::set_rank(int value) {
	_rank = value;
}

int Spell::get_item_cost() {
	return _item_cost;
}
void Spell::set_item_cost(int value) {
	_item_cost = value;
}

int Spell::get_craft_material_cost() {
	return _craft_material_cost;
}
void Spell::set_craft_material_cost(int value) {
	_craft_material_cost = value;
}

int Spell::get_required_item() {
	return _required_item;
}
void Spell::set_required_item(int value) {
	_required_item = value;
}

Ref<EntityResourceCostData> Spell::get_resource_cost() {
	return _resource_cost;
}
void Spell::set_resource_cost(Ref<EntityResourceCostData> value) {
	_resource_cost = value;
}

Ref<EntityResourceCostData> Spell::get_resource_give() {
	return _resource_give;
}
void Spell::set_resource_give(Ref<EntityResourceCostData> value) {
	_resource_give = value;
}

bool Spell::has_global_cooldown() {
	return _has_global_cooldown;
}
void Spell::set_has_global_cooldown(bool value) {
	_has_global_cooldown = value;
}

bool Spell::get_is_local_spell() {
	return _is_local_spell;
}
void Spell::set_is_local_spell(bool value) {
	_is_local_spell = value;
}

Ref<Texture> Spell::get_icon() {
	return _icon;
}
void Spell::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

String Spell::get_text_description() {
	return _text_description;
}
void Spell::set_text_description(String value) {
	_text_description = value;
}

Ref<SpellEffectVisual> Spell::get_visual_spell_effects() {
	return _visual_spell_effects;
}
void Spell::set_visual_spell_effects(Ref<SpellEffectVisual> value) {
	_visual_spell_effects = value;
}

Ref<SpellProjectileData> Spell::get_spell_projectile_data() {
	return _spell_projectile_data;
}
void Spell::set_spell_projectile_data(Ref<SpellProjectileData> value) {
	_spell_projectile_data = value;
}

Ref<WorldEffectData> Spell::get_world_effect_data() {
	return _world_effect_data;
}
void Spell::set_world_effect_data(Ref<WorldEffectData> value) {
	_world_effect_data = value;
}

Ref<CraftRecipe> Spell::get_teaches_craft_recipe() {
	return _teaches_craft_recipe;
}
void Spell::set_teaches_craft_recipe(Ref<CraftRecipe> value) {
	_teaches_craft_recipe = value;
}

float Spell::get_damage_scale_for_level(int level) {
	//return getDamageLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Spell::get_heal_scale_for_level(int level) {
	//return getHealLevelScaling()->Evaluate((float)(level));
	return 1;
}

float Spell::get_absorb_scale_for_level(int level) {
	//return getAbsorbLevelScaling()->Evaluate((float)(level));
	return 1;
}

////    Caster Aura Apply    ////

int Spell::get_num_caster_aura_applys() {
	return _caster_aura_applys.size();
}
void Spell::set_num_caster_aura_applys(int value) {
	_caster_aura_applys.resize(value);
}

Ref<Aura> Spell::get_caster_aura_apply(int index) const {
	ERR_FAIL_INDEX_V(index, _caster_aura_applys.size(), Ref<Aura>());

	return _caster_aura_applys[index];
}
void Spell::set_caster_aura_apply(int index, Ref<Aura> caster_aura_apply) {
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

int Spell::get_num_target_aura_applys() {
	return _target_aura_applys.size();
}
void Spell::set_num_target_aura_applys(int value) {
	_target_aura_applys.resize(value);
}

Ref<Aura> Spell::get_target_aura_apply(int index) const {
	ERR_FAIL_INDEX_V(index, _target_aura_applys.size(), Ref<Aura>());

	return _target_aura_applys[index];
}
void Spell::set_target_aura_apply(int index, Ref<Aura> target_aura_apply) {
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

int Spell::get_num_on_learn_auras() {
	return _on_learn_auras.size();
}
void Spell::set_num_on_learn_auras(int value) {
	_on_learn_auras.resize(value);
}

Ref<Aura> Spell::get_on_learn_aura(int index) const {
	ERR_FAIL_INDEX_V(index, _on_learn_auras.size(), Ref<Aura>());

	return _on_learn_auras[index];
}
void Spell::set_on_learn_aura(int index, Ref<Aura> on_learn_aura_apply) {
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

bool Spell::get_has_range() {
	return _has_range;
}
void Spell::set_has_range(bool value) {
	_has_range = value;
}

float Spell::get_range() {
	return _range;
}
void Spell::set_range(float value) {
	_range = value;
}

bool Spell::get_has_cast_time() {
	return _has_cast_time;
}
void Spell::set_has_cast_time(bool value) {
	_has_cast_time = value;
}

float Spell::get_cast_time() {
	return _cast_time;
}
void Spell::set_cast_time(float value) {
	_cast_time = value;
}

bool Spell::get_has_damage() {
	return _has_damage;
}
void Spell::set_has_damage(bool value) {
	_has_damage = value;
}

int Spell::get_damage_type() {
	return _damage_type;
}
void Spell::set_damage_type(int value) {
	_damage_type = value;
}

int Spell::get_damage_min() {
	return _damage_min;
}
void Spell::set_damage_min(int value) {
	_damage_min = value;
}

int Spell::get_damage_max() {
	return _damage_max;
}
void Spell::set_damage_max(int value) {
	_damage_max = value;
}

Ref<Curve> Spell::get_damage_scaling_curve() {
	return _damage_scaling_curve;
}
void Spell::set_damage_scaling_curve(Ref<Curve> curve) {
	_damage_scaling_curve = curve;
}

bool Spell::get_has_heal() {
	return _has_heal;
}
void Spell::set_has_heal(bool value) {
	_has_heal = value;
}

int Spell::get_heal_min() {
	return _heal_min;
}
void Spell::set_heal_min(int value) {
	_heal_min = value;
}

int Spell::get_heal_max() {
	return _heal_max;
}
void Spell::set_heal_max(int value) {
	_heal_max = value;
}

Ref<Curve> Spell::get_heal_scaling_curve() {
	return _heal_scaling_curve;
}
void Spell::set_heal_scaling_curve(Ref<Curve> curve) {
	_heal_scaling_curve = curve;
}

bool Spell::get_needs_target() {
	return _needs_target;
}
void Spell::set_needs_target(bool value) {
	_needs_target = value;
}

bool Spell::get_can_move_while_casting() {
	return _can_move_while_casting;
}
void Spell::set_can_move_while_casting(bool value) {
	_can_move_while_casting = value;
}

bool Spell::get_is_interrupt() {
	return _is_interrupt;
}
void Spell::set_is_interrupt(bool value) {
	_is_interrupt = value;
}

float Spell::get_interrupt_time() {
	return _interrupt_time;
}
void Spell::set_interrupt_time(float value) {
	_interrupt_time = value;
}

bool Spell::get_is_aoe() {
	return _is_aoe;
}
void Spell::set_is_aoe(bool value) {
	_is_aoe = value;
}

SpellAOETargetType Spell::get_aoe_target_type() {
	return _aoe_targetType;
}
void Spell::set_aoe_target_type(SpellAOETargetType value) {
	_aoe_targetType = value;
}

SpellAOEMovementType Spell::get_aoe_movement_type() {
	return _aoe_movementType;
}
void Spell::set_aoe_movement_type(SpellAOEMovementType value) {
	_aoe_movementType = value;
}

SpellAOEColliderType Spell::get_aoe_collider_type() {
	return _aoe_colliderType;
}
void Spell::set_aoe_collider_type(SpellAOEColliderType value) {
	_aoe_colliderType = value;
}

Vector3 Spell::get_aoe_half_extents() {
	return _aoe_half_extents;
}
void Spell::set_aoe_half_extents(Vector3 value) {
	_aoe_half_extents = value;
}

Ref<PackedScene> Spell::get_projectile() {
	return _projectile;
}
void Spell::set_projectile(Ref<PackedScene> value) {
	_projectile = value;
}

bool Spell::has_projectile() {
	return _projectile.is_valid();
}
float Spell::get_projectile_speed() {
	return _projectile_speed;
}
void Spell::set_projectile_speed(float value) {
	_projectile_speed = value;
}

float Spell::get_projectile_time() {
	return _projectile_time;
}
void Spell::set_projectile_time(float value) {
	_projectile_time = value;
}

float Spell::get_projectile_range() {
	return _projectile_range;
}
void Spell::set_projectile_range(float value) {
	_projectile_range = value;
}

bool Spell::get_has_projectile_collision() {
	return _projectile_collision;
}
void Spell::set_has_projectile_collision(bool value) {
	_projectile_collision = value;
}

SpellProjectileType Spell::get_projectile_type() {
	return _projectile_type;
}
void Spell::set_projectile_type(SpellProjectileType value) {
	_projectile_type = value;
}

bool Spell::get_has_projectile_destroy_on_impact() {
	return _projectile_destroy_on_impact;
}
void Spell::set_has_projectile_destroy_on_impact(bool value) {
	_projectile_destroy_on_impact = value;
}

int Spell::get_spell_cooldown_mainpulation_data_count() {
	return _spell_cooldown_mainpulation_data_count;
}
void Spell::set_spell_cooldown_mainpulation_data_count(int value) {
	_spell_cooldown_mainpulation_data_count = value;
}

int Spell::get_training_cost() {
	return _training_cost;
}
void Spell::set_training_cost(int value) {
	_training_cost = value;
}

Ref<Spell> Spell::get_training_required_spell() {
	return _training_required_spell;
}
void Spell::set_training_required_spell(Ref<Spell> spell) {
	_training_required_spell = spell;
}

Ref<Aura> Spell::get_training_required_skill() {
	return _training_required_skill;
}
void Spell::set_training_required_skill(Ref<Aura> skill) {
	_training_required_skill = skill;
}

int Spell::get_training_required_skill_level() {
	return _training_required_skill_level;
}
void Spell::set_training_required_skill_level(int value) {
	_training_required_skill_level = value;

}

////    Spell System    ////

void Spell::sstart_casting_simple(Entity *caster, float spell_scale) {
	ERR_FAIL_COND(!caster || !ObjectDB::instance_validate(caster));

	Ref<SpellCastInfo> info = Ref<SpellCastInfo>(memnew(SpellCastInfo()));

	info->set_caster(caster);
	info->set_target(caster->gets_target());
	info->set_has_cast_time(get_has_cast_time());
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

void Spell::_sstart_casting(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid() || info->get_spell() == NULL);

	//Ref<Spell> spell = info->get_spell();

	if (get_needs_target() || get_has_damage()) {
		if (!info->get_target()) {
			//print_error("no target, return");

			return;
		}
	}

	if (get_has_cast_time()) {
		//can cast
		info->get_caster()->son_before_cast(info);

		if (info->get_target()) {
			info->get_target()->son_before_cast_target(info);
		}

		info->get_caster()->sstart_casting(info);
	} else {
		if (get_has_damage()) {
			Ref<SpellDamageInfo> dpd = Ref<SpellDamageInfo>(memnew(SpellDamageInfo()));

			dpd->set_spell_damage_source(Ref<Spell>(this));
			dpd->set_dealer(info->get_caster());
			dpd->set_receiver(info->get_target());

			handle_spell_damage(dpd);
		}
	}
}

void Spell::_calculate_initial_damage(Ref<SpellDamageInfo> data) {
	data->set_damage(get_damage_min());
}

void Spell::_handle_spell_damage(Ref<SpellDamageInfo> data) {
	calculate_initial_damage(data);

	data->get_dealer()->sdeal_damage_to(data);
}

String Spell::get_description(int level) {
	return _text_description;
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

	_item_cost = 0;
	_craft_material_cost = 0;
	_required_item = 0;

	_has_global_cooldown = true;
	_is_local_spell = false;

	_has_range = false;
	_range = 0;

	_has_damage = false;
	_damage_type = 0;
	_damage_min = 0;
	_damage_max = 0;

	_has_heal = false;
	_heal_min = 0;
	_heal_max = 0;

	_has_cast_time = false;
	_cast_time = 0;

	_needs_target = false;
	_can_move_while_casting = false;

	_is_interrupt = false;
	_interrupt_time = 0;

	_is_aoe = false;
	_aoe_targetType = SpellAOETargetType::SPELL_AOE_TARGET_TYPE_CASTER;
	_aoe_movementType = SpellAOEMovementType::SPELL_AOE_MOVEMENT_TYPE_STATIC;
	_aoe_colliderType = SpellAOEColliderType::SPELL_AOE_COLLIDER_TYPE_BOX;
	//Vector3 _aoe_half_extents;

	_projectile_speed = 0;
	_projectile_time = 0;
	_projectile_range = 0;
	_projectile_type = SpellProjectileType::SPELL_PROJECTILE_TYPE_FOLLOW;
	_projectile_destroy_on_impact = false;
	_projectile_collision = false;

	_spell_cooldown_mainpulation_data_count = 0;

	_training_cost = 0;
	_training_required_skill_level = 0;
}

Spell::~Spell() {
	_caster_aura_applys.clear();
	_target_aura_applys.clear();
	_on_learn_auras.clear();

	_resource_cost.unref();
	_resource_give.unref();

	_icon.unref();

	_visual_spell_effects.unref();
	_spell_projectile_data.unref();
	_world_effect_data.unref();
	_teaches_craft_recipe.unref();
	_damage_scaling_curve.unref();
	_heal_scaling_curve.unref();
	_projectile.unref();
	_training_required_spell.unref();
	_training_required_skill.unref();
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

	ClassDB::bind_method(D_METHOD("_sstart_casting", "info"), &Spell::_sstart_casting);

	//Eventhandlers
	ClassDB::bind_method(D_METHOD("son_cast_player_moved", "info"), &Spell::son_cast_player_moved);
	ClassDB::bind_method(D_METHOD("son_cast_damage_received", "info"), &Spell::son_cast_damage_received);
	ClassDB::bind_method(D_METHOD("son_spell_hit", "info"), &Spell::son_spell_hit);

	BIND_VMETHOD(MethodInfo("_son_cast_player_moved", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_damage_received", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_spell_hit", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

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

	ClassDB::bind_method(D_METHOD("_calculate_initial_damage", "info"), &Spell::_calculate_initial_damage);
	ClassDB::bind_method(D_METHOD("_handle_spell_damage", "info"), &Spell::_handle_spell_damage);

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

	ClassDB::bind_method(D_METHOD("get_visual_spell_effects"), &Spell::get_visual_spell_effects);
	ClassDB::bind_method(D_METHOD("set_visual_spell_effects", "value"), &Spell::set_visual_spell_effects);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "visual_spell_effects", PROPERTY_HINT_RESOURCE_TYPE, "SpellEffectVisual"), "set_visual_spell_effects", "get_visual_spell_effects");

	ClassDB::bind_method(D_METHOD("get_spell_projectile_data"), &Spell::get_spell_projectile_data);
	ClassDB::bind_method(D_METHOD("set_spell_projectile_data", "value"), &Spell::set_spell_projectile_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell_projectile_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellProjectileData"), "set_spell_projectile_data", "get_spell_projectile_data");

	ClassDB::bind_method(D_METHOD("get_world_effect_data"), &Spell::get_world_effect_data);
	ClassDB::bind_method(D_METHOD("set_world_effect_data", "value"), &Spell::set_world_effect_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world_effect_data", PROPERTY_HINT_RESOURCE_TYPE, "WorldEffectData"), "set_world_effect_data", "get_world_effect_data");

	ClassDB::bind_method(D_METHOD("get_teaches_craft_recipe"), &Spell::get_teaches_craft_recipe);
	ClassDB::bind_method(D_METHOD("set_teaches_craft_recipe", "value"), &Spell::set_teaches_craft_recipe);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "teaches_craft_recipe", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipe"), "set_teaches_craft_recipe", "get_teaches_craft_recipe");

	ClassDB::bind_method(D_METHOD("get_damage_scale_for_level"), &Spell::get_damage_scale_for_level);
	ClassDB::bind_method(D_METHOD("get_heal_scale_for_level"), &Spell::get_heal_scale_for_level);
	ClassDB::bind_method(D_METHOD("get_absorb_scale_for_level"), &Spell::get_absorb_scale_for_level);

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
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &Spell::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &Spell::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description", PROPERTY_HINT_MULTILINE_TEXT), "set_text_description", "get_text_description");

	ADD_GROUP("Cooldown", "cooldown");
	ClassDB::bind_method(D_METHOD("get_cooldown"), &Spell::get_cooldown);
	ClassDB::bind_method(D_METHOD("set_cooldown", "value"), &Spell::set_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cooldown_cooldown"), "set_cooldown", "get_cooldown");

	ClassDB::bind_method(D_METHOD("has_global_cooldown"), &Spell::has_global_cooldown);
	ClassDB::bind_method(D_METHOD("set_has_global_cooldown", "value"), &Spell::set_has_global_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cooldown_global_cooldown"), "set_has_global_cooldown", "has_global_cooldown");

	ADD_GROUP("Range", "range");
	ClassDB::bind_method(D_METHOD("get_has_range"), &Spell::get_has_range);
	ClassDB::bind_method(D_METHOD("set_has_range", "value"), &Spell::set_has_range);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "range"), "set_has_range", "get_has_range");

	ClassDB::bind_method(D_METHOD("get_range"), &Spell::get_range);
	ClassDB::bind_method(D_METHOD("set_range", "value"), &Spell::set_range);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "range_range"), "set_range", "get_range");

	ADD_GROUP("Cast", "cast");
	ClassDB::bind_method(D_METHOD("get_has_cast_time"), &Spell::get_has_cast_time);
	ClassDB::bind_method(D_METHOD("set_has_cast_time", "value"), &Spell::set_has_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast"), "set_has_cast_time", "get_has_cast_time");

	ClassDB::bind_method(D_METHOD("get_cast_time"), &Spell::get_cast_time);
	ClassDB::bind_method(D_METHOD("set_cast_time", "value"), &Spell::set_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cast_cast_time"), "set_cast_time", "get_cast_time");

	ClassDB::bind_method(D_METHOD("get_can_move_while_casting"), &Spell::get_can_move_while_casting);
	ClassDB::bind_method(D_METHOD("set_can_move_while_casting", "value"), &Spell::set_can_move_while_casting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cast_can_move_while_casting"), "set_can_move_while_casting", "get_can_move_while_casting");

	ADD_GROUP("Damage", "damage");
	ClassDB::bind_method(D_METHOD("get_has_damage"), &Spell::get_has_damage);
	ClassDB::bind_method(D_METHOD("set_has_damage", "value"), &Spell::set_has_damage);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damage"), "set_has_damage", "get_has_damage");

	ClassDB::bind_method(D_METHOD("get_damage_type"), &Spell::get_damage_type);
	ClassDB::bind_method(D_METHOD("set_damage_type", "value"), &Spell::set_damage_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_DAMAGE_TYPES), "set_damage_type", "get_damage_type");

	ClassDB::bind_method(D_METHOD("get_damage_min"), &Spell::get_damage_min);
	ClassDB::bind_method(D_METHOD("set_damage_min", "value"), &Spell::set_damage_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_min"), "set_damage_min", "get_damage_min");

	ClassDB::bind_method(D_METHOD("get_damage_max"), &Spell::get_damage_max);
	ClassDB::bind_method(D_METHOD("set_damage_max", "value"), &Spell::set_damage_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_max"), "set_damage_max", "get_damage_max");

	ClassDB::bind_method(D_METHOD("get_damage_scaling_curve"), &Spell::get_damage_scaling_curve);
	ClassDB::bind_method(D_METHOD("set_damage_scaling_curve", "curve"), &Spell::set_damage_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damage_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_damage_scaling_curve", "get_damage_scaling_curve");

	ADD_GROUP("Heal", "heal");
	ClassDB::bind_method(D_METHOD("get_has_heal"), &Spell::get_has_heal);
	ClassDB::bind_method(D_METHOD("set_has_heal", "value"), &Spell::set_has_heal);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "heal"), "set_has_heal", "get_has_heal");

	ClassDB::bind_method(D_METHOD("get_heal_min"), &Spell::get_heal_min);
	ClassDB::bind_method(D_METHOD("set_heal_min", "value"), &Spell::set_heal_min);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_min"), "set_heal_min", "get_heal_min");

	ClassDB::bind_method(D_METHOD("get_heal_max"), &Spell::get_heal_max);
	ClassDB::bind_method(D_METHOD("set_heal_max", "value"), &Spell::set_heal_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_max"), "set_heal_max", "get_heal_max");

	ClassDB::bind_method(D_METHOD("get_heal_scaling_curve"), &Spell::get_heal_scaling_curve);
	ClassDB::bind_method(D_METHOD("set_heal_scaling_curve", "curve"), &Spell::set_heal_scaling_curve);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "heal_scaling_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_heal_scaling_curve", "get_heal_scaling_curve");

	ADD_GROUP("Interrupt", "interrupt");
	ClassDB::bind_method(D_METHOD("get_is_interrupt"), &Spell::get_is_interrupt);
	ClassDB::bind_method(D_METHOD("set_is_interrupt", "value"), &Spell::set_is_interrupt);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "interrupt"), "set_is_interrupt", "get_is_interrupt");

	ClassDB::bind_method(D_METHOD("get_interrupt_time"), &Spell::get_interrupt_time);
	ClassDB::bind_method(D_METHOD("set_interrupt_time", "value"), &Spell::set_interrupt_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "interrupt_time"), "set_interrupt_time", "get_interrupt_time");

	ADD_GROUP("Cost", "cost");
	ClassDB::bind_method(D_METHOD("get_item_cost"), &Spell::get_item_cost);
	ClassDB::bind_method(D_METHOD("set_item_cost", "value"), &Spell::set_item_cost);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_item"), "set_item_cost", "get_item_cost");

	ClassDB::bind_method(D_METHOD("get_craft_material_cost"), &Spell::get_craft_material_cost);
	ClassDB::bind_method(D_METHOD("set_craft_material_cost", "value"), &Spell::set_craft_material_cost);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_craft_material"), "set_craft_material_cost", "get_craft_material_cost");

	ClassDB::bind_method(D_METHOD("get_required_item"), &Spell::get_required_item);
	ClassDB::bind_method(D_METHOD("set_required_item", "value"), &Spell::set_required_item);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_required_item"), "set_required_item", "get_required_item");

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

	ClassDB::bind_method(D_METHOD("get_aoe_movement_type"), &Spell::get_aoe_movement_type);
	ClassDB::bind_method(D_METHOD("set_aoe_movement_type", "value"), &Spell::set_aoe_movement_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aoe_movement_type", PROPERTY_HINT_ENUM, "Static, Moving To Target, Random Direction, Randomly, Caster Facing, Moving"), "set_aoe_movement_type", "get_aoe_movement_type");

	ClassDB::bind_method(D_METHOD("get_aoe_collider_type"), &Spell::get_aoe_collider_type);
	ClassDB::bind_method(D_METHOD("set_aoe_collider_type", "value"), &Spell::set_aoe_collider_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aoe_colliderType", PROPERTY_HINT_ENUM, "Sphere, Box, Box Non Uniform"), "set_aoe_collider_type", "get_aoe_collider_type");

	ClassDB::bind_method(D_METHOD("get_aoe_half_extents"), &Spell::get_aoe_half_extents);
	ClassDB::bind_method(D_METHOD("set_aoe_half_extents", "value"), &Spell::set_aoe_half_extents);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "aoe_half_extents"), "set_aoe_half_extents", "get_aoe_half_extents");

	ADD_GROUP("Projectile", "projectile");
	ClassDB::bind_method(D_METHOD("has_projectile"), &Spell::has_projectile);
	ClassDB::bind_method(D_METHOD("get_projectile"), &Spell::get_projectile);
	ClassDB::bind_method(D_METHOD("set_projectile", "value"), &Spell::set_projectile);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "projectile", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_projectile", "get_projectile");

	ClassDB::bind_method(D_METHOD("get_projectile_speed"), &Spell::get_projectile_speed);
	ClassDB::bind_method(D_METHOD("set_projectile_speed", "value"), &Spell::set_projectile_speed);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "projectile_speed"), "set_projectile_speed", "get_projectile_speed");

	ClassDB::bind_method(D_METHOD("get_projectile_time"), &Spell::get_projectile_time);
	ClassDB::bind_method(D_METHOD("set_projectile_time", "value"), &Spell::set_projectile_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "projectile_time"), "set_projectile_time", "get_projectile_time");

	ClassDB::bind_method(D_METHOD("get_projectile_range"), &Spell::get_projectile_range);
	ClassDB::bind_method(D_METHOD("set_projectile_range", "value"), &Spell::set_projectile_range);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "projectile_range"), "set_projectile_range", "get_projectile_range");

	ClassDB::bind_method(D_METHOD("get_has_projectile_collision"), &Spell::get_has_projectile_collision);
	ClassDB::bind_method(D_METHOD("set_has_projectile_collision", "value"), &Spell::set_has_projectile_collision);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "projectile_has_projectile_collision"), "set_has_projectile_collision", "get_has_projectile_collision");

	ClassDB::bind_method(D_METHOD("get_projectile_type"), &Spell::get_projectile_type);
	ClassDB::bind_method(D_METHOD("set_projectile_type", "value"), &Spell::set_projectile_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "projectile_type", PROPERTY_HINT_ENUM, "Follow, Straight, Stationary"), "set_projectile_type", "get_projectile_type");

	ClassDB::bind_method(D_METHOD("get_has_projectile_destroy_on_impact"), &Spell::get_has_projectile_destroy_on_impact);
	ClassDB::bind_method(D_METHOD("set_has_projectile_destroy_on_impact", "value"), &Spell::set_has_projectile_destroy_on_impact);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "projectile_has_projectile_destroy_on_impact"), "set_has_projectile_destroy_on_impact", "get_has_projectile_destroy_on_impact");

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
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "training_required_skill", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_training_required_skill", "get_training_required_skill");

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

	BIND_ENUM_CONSTANT(SPELL_AOE_COLLIDER_TYPE_SPHERE);
	BIND_ENUM_CONSTANT(SPELL_AOE_COLLIDER_TYPE_BOX);
	BIND_ENUM_CONSTANT(SPELL_AOE_COLLIDER_TYPE_BOX_NON_UNIFORM);

	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_STATIC);
	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_MOVING_TO_TARGET);
	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_MOVING_RANDOM_DIRECTION);
	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_MOVING_RANDOMLY);
	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_MOVING_CASTER_FACING);
	BIND_ENUM_CONSTANT(SPELL_AOE_MOVEMENT_TYPE_MOVING);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_CASTER);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_TARGET);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_GOUND_TARGET_SELECTION);
	BIND_ENUM_CONSTANT(SPELL_AOE_TARGET_TYPE_RANDOM);

	BIND_ENUM_CONSTANT(SPELL_PROJECTILE_TYPE_FOLLOW);
	BIND_ENUM_CONSTANT(SPELL_PROJECTILE_TYPE_STRAIGHT);
	BIND_ENUM_CONSTANT(SPELL_PROJECTILE_TYPE_STATIONARY);
}
