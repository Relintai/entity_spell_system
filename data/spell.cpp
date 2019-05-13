#include "spell.h"

#include "aura.h"

Ref<Aura> Spell::get_caster_aura_apply() {
	return Ref<Aura>(_caster_aura_apply);
}

void Spell::set_caster_aura_apply(Ref<Aura> value) {
	_caster_aura_apply = (*value);

	if (_caster_aura_apply_ref)
		memdelete(_caster_aura_apply_ref);

	_caster_aura_apply_ref = memnew(Ref<Aura>(value));
}

Ref<Aura> Spell::get_caster_aura_apply2() {
	return Ref<Aura>(_caster_aura_apply2);
}

void Spell::set_caster_aura_apply2(Ref<Aura> value) {
	_caster_aura_apply2 = (*value);

	if (_caster_aura_apply2_ref)
		memdelete(_caster_aura_apply2_ref);

	_caster_aura_apply2_ref = memnew(Ref<Aura>(value));
}

Ref<Aura> Spell::get_target_aura_apply() {
	return Ref<Aura>(_target_aura_apply);
}

void Spell::set_target_aura_apply(Ref<Aura> value) {
	_target_aura_apply = (*value);

	if (_target_aura_apply_ref)
		memdelete(_target_aura_apply_ref);

	_target_aura_apply_ref = memnew(Ref<Aura>(value));
}

Ref<Aura> Spell::get_target_aura_apply2() {
	return Ref<Aura>(_target_aura_apply2);
}

void Spell::set_target_aura_apply2(Ref<Aura> value) {
	_target_aura_apply2 = (*value);

	if (_target_aura_apply2_ref)
		memdelete(_target_aura_apply2_ref);

	_target_aura_apply2_ref = memnew(Ref<Aura>(value));
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

////    Spell System    ////

void Spell::sstart_casting_simple(Entity *caster, float spell_scale) {
	ERR_FAIL_COND(caster == NULL);

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
	ERR_FAIL_COND(caster == NULL);

	Ref<SpellCastInfo> info(memnew(SpellCastInfo()));

	info->set_caster(caster);
	info->set_spell(Ref<Spell>(this));

	sinterrupt_cast(info);
}

void Spell::sstart_casting_triggered_simple(Entity *caster) {
	ERR_FAIL_COND(caster == NULL);

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

	Ref<Spell> spell = info->get_spell();

	if (spell->get_needs_target() || spell->get_has_damage()) {
		if (!info->get_target()) {
			//print_error("no target, return");

			return;
		}
	}

	if (spell->get_has_cast_time()) {
		//can cast
		info->get_caster()->son_before_cast(info);

		if (info->get_target()) {
			info->get_target()->son_before_cast_target(info);
		}

		info->get_caster()->sstart_casting(info);
	} else {
		if (spell->get_has_damage()) {
			Ref<SpellDamageInfo> dpd = Ref<SpellDamageInfo>(memnew(SpellDamageInfo()));

			dpd->set_spell_damage_source(spell);
			dpd->set_dealer(info->get_caster());
			dpd->set_receiver(info->get_target());

			handle_spell_damage(dpd);
		}

		if (spell->get_caster_aura_apply() != NULL) {
			Ref<AuraApplyInfo> aainfo(memnew(AuraApplyInfo(info->get_caster(), info->get_caster(), info->get_spell_scale())));

			spell->get_caster_aura_apply()->sapply(aainfo);
		}

		if (spell->get_caster_aura_apply2() != NULL) {
			Ref<AuraApplyInfo> aainfo(memnew(AuraApplyInfo(info->get_caster(), info->get_caster(), info->get_spell_scale())));

			spell->get_caster_aura_apply2()->sapply(aainfo);
		}

		if (spell->get_target_aura_apply() != NULL) {
			Ref<AuraApplyInfo> aainfo(memnew(AuraApplyInfo(info->get_caster(), info->get_caster()->getc_target(), info->get_spell_scale())));

			spell->get_target_aura_apply()->sapply(aainfo);
		}

		if (spell->get_target_aura_apply2() != NULL) {
			Ref<AuraApplyInfo> aainfo(memnew(AuraApplyInfo(info->get_caster(), info->get_caster()->getc_target(), info->get_spell_scale())));

			spell->get_target_aura_apply2()->sapply(aainfo);
		}
	}
	/*
	WorldEntity *worldEntity = null;
	if (spell->GenericSpellData->NeedsTarget || damage) {
		worldEntity = Spell::GetTarget(caster);
	}

	if (!hasCastTime) {
		if (spell->SpellRangeData->Enabled && !Spell::isInRange(caster, worldEntity)) {
			return;
		}
		HandleSpellEffect(caster, worldEntity, spellScale);
		return;
	} else {
		if (!Spell::SpellCostCheck(caster)) {
			return;
		}
		Spell::DoStartCasting(caster, spellId, spell->SpellName, spell->CastTime, !spell->GenericSpellData->CanMoveWhileCasting, spellScale);
		return;
	}*/
}

void Spell::_calculate_initial_damage(Ref<SpellDamageInfo> data) {
	data->set_damage(get_damage_min());
}

void Spell::_handle_spell_damage(Ref<SpellDamageInfo> data) {
	calculate_initial_damage(data);

	data->get_dealer()->sdeal_damage_to(data);
}

String Spell::get_name() {
	return _spell_name;
}

String Spell::get_description(int level) {
	return _spell_description;
}

Spell::Spell() {
	PLAYER_HIT_RADIUS = (float)0.5;

	_level = 1;

	_spell_id = 1;
	_spell_type = SpellEnums::SPELL_TYPE_NONE;

	_hide_from_actionbar = false;
	_cast_time = 0;
	_cooldown = 0;
	//SpellTargetType _target_type;

	_level = 0;
	_item_cost = 0;
	_craft_material_cost = 0;
	_required_item = 0;
	//PlayerResourceTypes _cost_type;
	_cost_resource = 0;
	//PlayerResourceTypes _give_resource_type;
	_give_resource = 0;
	_has_global_cooldown = false;
	_is_local_spell = false;

	//String _name_key;

	//String _spell_name;
	//String _spell_description;

	_has_range = false;
	_range = 0;

	_has_damage = false;
	_damage_type = 0;
	_damage_min = 0;
	_damage_max = 0;

	_has_heal = false;
	_heal_min = 0;
	_heal_max = 0;

	_needs_target = false;
	_can_move_while_casting = false;

	_is_interrupt = false;
	_interrupt_time = 0;

	_is_aoe = false;
	//SpellAOETargetType _aoe_targetType;
	//SpellAOEMovementType _aoe_movementType;
	//SpellAOEColliderType _aoe_colliderType;
	//Vector3 _aoe_half_extents;

	_has_cast_time = false;
	_cast_time = 0;

	_has_effect = false;
	_effect_id = 0;

	_has_spell_cast_finish_effect = false;
	_spell_cast_finish_effect_id = 0;

	_has_spell_cast_effect = false;
	_spell_cast_effect_id = 0;

	_has_projectile = false;
	_projectile_id = 0;
	_projectile_speed = 0;
	_projectile_time = 0;
	_projectile_range = 0;
	//SpellProjectileType _projectile_type;
	_projectile_destroy_on_impact = false;
	_projectile_collision = false;

	_caster_aura_apply = NULL;
	_caster_aura_apply2 = NULL;
	_target_aura_apply = NULL;
	_target_aura_apply2 = NULL;

	_caster_aura_apply_ref = NULL;
	_caster_aura_apply2_ref = NULL;
	_target_aura_apply_ref = NULL;
	_target_aura_apply2_ref = NULL;

	_spell_cooldown_mainpulation_data_count = 0;
}

Spell::~Spell() {
	if (_caster_aura_apply_ref != NULL)
		memdelete(_caster_aura_apply_ref);

	if (_caster_aura_apply2_ref != NULL)
		memdelete(_caster_aura_apply2_ref);

	if (_target_aura_apply_ref != NULL)
		memdelete(_target_aura_apply_ref);

	if (_target_aura_apply2_ref != NULL)
		memdelete(_target_aura_apply2_ref);

	_caster_aura_apply = NULL;
	_caster_aura_apply2 = NULL;
	_target_aura_apply = NULL;
	_target_aura_apply2 = NULL;
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
	ClassDB::bind_method(D_METHOD("get_spell_id"), &Spell::get_spell_id);
	ClassDB::bind_method(D_METHOD("set_spell_id", "value"), &Spell::set_spell_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_id"), "set_spell_id", "get_spell_id");

	ClassDB::bind_method(D_METHOD("get_spell_type"), &Spell::get_spell_type);
	ClassDB::bind_method(D_METHOD("set_spell_type", "value"), &Spell::set_spell_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_FLAGS, SpellEnums::BINDING_STRING_SPELL_TYPES), "set_spell_type", "get_spell_type");

	ClassDB::bind_method(D_METHOD("get_hide_from_actionbar"), &Spell::get_hide_from_actionbar);
	ClassDB::bind_method(D_METHOD("set_hide_from_actionbar", "value"), &Spell::set_hide_from_actionbar);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hide_from_actionbar"), "set_hide_from_actionbar", "get_hide_from_actionbar");

	ClassDB::bind_method(D_METHOD("get_target_type"), &Spell::get_target_type);
	ClassDB::bind_method(D_METHOD("set_target_type", "value"), &Spell::set_target_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_type", PROPERTY_HINT_ENUM, "Self, Target, Around, Front, Around Target"), "set_target_type", "get_target_type");

	ClassDB::bind_method(D_METHOD("get_level"), &Spell::get_level);
	ClassDB::bind_method(D_METHOD("set_level", "value"), &Spell::set_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "level"), "set_level", "get_level");

	ClassDB::bind_method(D_METHOD("get_is_local_spell"), &Spell::get_is_local_spell);
	ClassDB::bind_method(D_METHOD("set_is_local_spell", "value"), &Spell::set_is_local_spell);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_local_spell"), "set_is_local_spell", "get_is_local_spell");

	ClassDB::bind_method(D_METHOD("get_icon"), &Spell::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &Spell::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_needs_target"), &Spell::get_needs_target);
	ClassDB::bind_method(D_METHOD("set_needs_target", "value"), &Spell::set_needs_target);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "needs_target"), "set_needs_target", "get_needs_target");

	ClassDB::bind_method(D_METHOD("get_damage_scale_for_level"), &Spell::get_damage_scale_for_level);
	ClassDB::bind_method(D_METHOD("get_heal_scale_for_level"), &Spell::get_heal_scale_for_level);
	ClassDB::bind_method(D_METHOD("get_absorb_scale_for_level"), &Spell::get_absorb_scale_for_level);

	ADD_GROUP("Texts", "text");
	ClassDB::bind_method(D_METHOD("get_name_key"), &Spell::get_name_key);
	ClassDB::bind_method(D_METHOD("set_name_key", "value"), &Spell::set_name_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name_key"), "set_name_key", "get_name_key");

	ClassDB::bind_method(D_METHOD("get_spell_name"), &Spell::get_spell_name);
	ClassDB::bind_method(D_METHOD("set_spell_name", "value"), &Spell::set_spell_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_spell_name"), "set_spell_name", "get_spell_name");

	ClassDB::bind_method(D_METHOD("get_spell_description"), &Spell::get_spell_description);
	ClassDB::bind_method(D_METHOD("set_spell_description", "value"), &Spell::set_spell_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_spell_description", PROPERTY_HINT_MULTILINE_TEXT), "set_spell_description", "get_spell_description");

	ADD_GROUP("Cooldown", "cooldown");
	ClassDB::bind_method(D_METHOD("get_cooldown"), &Spell::get_cooldown);
	ClassDB::bind_method(D_METHOD("set_cooldown", "value"), &Spell::set_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cooldown_cooldown"), "set_cooldown", "get_cooldown");

	ClassDB::bind_method(D_METHOD("has_global_cooldown"), &Spell::has_global_cooldown);
	ClassDB::bind_method(D_METHOD("set_has_global_cooldown", "value"), &Spell::set_has_global_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cooldown_global_cooldown"), "set_has_global_cooldown", "has_global_cooldown");

	ADD_GROUP("Auras", "aura");
	ClassDB::bind_method(D_METHOD("get_caster_aura_apply"), &Spell::get_caster_aura_apply);
	ClassDB::bind_method(D_METHOD("set_caster_aura_apply", "value"), &Spell::set_caster_aura_apply);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_caster_apply", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_caster_aura_apply", "get_caster_aura_apply");

	ClassDB::bind_method(D_METHOD("get_caster_aura_apply2"), &Spell::get_caster_aura_apply2);
	ClassDB::bind_method(D_METHOD("set_caster_aura_apply2", "value"), &Spell::set_caster_aura_apply2);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_caster_aura_apply2", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_caster_aura_apply2", "get_caster_aura_apply2");

	ClassDB::bind_method(D_METHOD("get_target_aura_apply"), &Spell::get_target_aura_apply);
	ClassDB::bind_method(D_METHOD("set_target_aura_apply", "value"), &Spell::set_target_aura_apply);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_target_apply", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_target_aura_apply", "get_target_aura_apply");

	ClassDB::bind_method(D_METHOD("get_target_aura_apply2"), &Spell::get_target_aura_apply2);
	ClassDB::bind_method(D_METHOD("set_target_aura_apply2", "value"), &Spell::set_target_aura_apply2);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_target_apply2", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_target_aura_apply2", "get_target_aura_apply2");

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

	ClassDB::bind_method(D_METHOD("get_cost_type"), &Spell::get_cost_type);
	ClassDB::bind_method(D_METHOD("set_cost_type", "value"), &Spell::set_cost_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_type", PROPERTY_HINT_ENUM, "None, Rage"), "set_cost_type", "get_cost_type");

	ClassDB::bind_method(D_METHOD("get_cost_resource"), &Spell::get_cost_resource);
	ClassDB::bind_method(D_METHOD("set_cost_resource", "value"), &Spell::set_cost_resource);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_resource"), "set_cost_resource", "get_cost_resource");

	ADD_GROUP("Gives", "give");
	ClassDB::bind_method(D_METHOD("get_give_resource_type"), &Spell::get_give_resource_type);
	ClassDB::bind_method(D_METHOD("set_give_resource_type", "value"), &Spell::set_give_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "give_resource_type", PROPERTY_HINT_ENUM, "None, Rage"), "set_give_resource_type", "get_give_resource_type");

	ClassDB::bind_method(D_METHOD("get_give_resource"), &Spell::get_give_resource);
	ClassDB::bind_method(D_METHOD("set_give_resource", "value"), &Spell::set_give_resource);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "give_resource"), "set_give_resource", "get_give_resource");

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

	ADD_GROUP("Effect", "effect");
	ClassDB::bind_method(D_METHOD("get_has_effect"), &Spell::get_has_effect);
	ClassDB::bind_method(D_METHOD("set_has_effect", "value"), &Spell::set_has_effect);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "effect"), "set_has_effect", "get_has_effect");

	ClassDB::bind_method(D_METHOD("get_effect_id"), &Spell::get_effect_id);
	ClassDB::bind_method(D_METHOD("set_effect_id", "value"), &Spell::set_effect_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "effect_id"), "set_effect_id", "get_effect_id");

	ClassDB::bind_method(D_METHOD("get_has_spell_cast_finish_effect"), &Spell::get_has_spell_cast_finish_effect);
	ClassDB::bind_method(D_METHOD("set_has_spell_cast_finish_effect", "value"), &Spell::set_has_spell_cast_finish_effect);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "effect_spell_cast_finish_effect"), "set_has_spell_cast_finish_effect", "get_has_spell_cast_finish_effect");

	ClassDB::bind_method(D_METHOD("get_spell_cast_finish_effect_id"), &Spell::get_spell_cast_finish_effect_id);
	ClassDB::bind_method(D_METHOD("set_spell_cast_finish_effect_id", "value"), &Spell::set_spell_cast_finish_effect_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "effect_spell_cast_finish_effect_id"), "set_spell_cast_finish_effect_id", "get_spell_cast_finish_effect_id");

	ClassDB::bind_method(D_METHOD("get_has_spell_cast_effect"), &Spell::get_has_spell_cast_effect);
	ClassDB::bind_method(D_METHOD("set_has_spell_cast_effect", "value"), &Spell::set_has_spell_cast_effect);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "effect_m_spell_cast_effect"), "set_has_spell_cast_effect", "get_has_spell_cast_effect");

	ClassDB::bind_method(D_METHOD("get_spell_cast_effect_id"), &Spell::get_spell_cast_effect_id);
	ClassDB::bind_method(D_METHOD("set_spell_cast_effect_id", "value"), &Spell::set_spell_cast_effect_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "effect_spell_cast_effect_id"), "set_spell_cast_effect_id", "get_spell_cast_effect_id");

	ADD_GROUP("Projectile", "projectile");
	ClassDB::bind_method(D_METHOD("get_has_projectile"), &Spell::get_has_projectile);
	ClassDB::bind_method(D_METHOD("set_has_projectile", "value"), &Spell::set_has_projectile);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "projectile"), "set_has_projectile", "get_has_projectile");

	ClassDB::bind_method(D_METHOD("get_projectile_id"), &Spell::get_projectile_id);
	ClassDB::bind_method(D_METHOD("set_projectile_id", "value"), &Spell::set_projectile_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "projectile_id"), "set_projectile_id", "get_projectile_id");

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

	BIND_ENUM_CONSTANT(TARGET_SELF);
	BIND_ENUM_CONSTANT(TARGET_ENEMY);
	BIND_ENUM_CONSTANT(TARGET_TARGET);

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

//// SpellScript Old

/*
void Spell::TriggerGlobalCooldown(Entity* player)
{
	player->Stats->TriggerGlobalCooldown();
}

bool Spell::IsCasting(Entity* player)
{
	return player->SpellCastData->SCasting;
}

bool Spell::HasClobalCooldown(Entity* player)
{
	return player->Stats->SHasGlobalCooldown;
}

bool Spell::IsStunned(Entity* player)
{
	return player->StateComponent->SHasState(StateData::StateType::TYPE_STUN);
}

bool Spell::HasState(StateData::StateType state, Entity* player)
{
	return player->StateComponent->SHasState(state);
}

int Spell::GetId(Entity* spell)
{
	return spell->GetComponent<Spell>()->SpellID;
}

bool Spell::IsSpellOnCooldown(int spellId, Entity* player)
{
	PlayerSpellDataComponent* playerSpellDataComponent = player->PlayerSpellDataComponent;
	for (int i = 0; i < playerSpellDataComponent->SSpellData->Count; i += 1) {
		if (playerSpellDataComponent->SSpellData->GetData(i)->SpellId == spellId) {
			return true;
		}
	}
	return false;
}

void Spell::ApplyAura(int auraId, Entity* caster, float spellScale)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->Apply(caster, caster, spellScale);
}

void Spell::ApplyAura(int auraId, Entity* caster, Entity* target, float spellScale)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->Apply(caster, target, spellScale);
}

void Spell::RemoveAura(int auraId, Entity* caster)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->RemoveAura(caster);
}

void Spell::AddCooldown(Entity* player, int spellId, float cooldown)
{
	PlayerSpellDataComponent* arg_10_0 = player->PlayerSpellDataComponent;
	PlayerSpellCooldownData* psd = new PlayerSpellCooldownData(spellId, cooldown, cooldown);
	arg_10_0->AddSSpellData(psd);
}

void Spell::DoStartCasting(Entity* player, int spellId, String* spellName, float castTime, bool addMoveHook, float spellScale)
{
	player->SpellCastData->StartCasting(spellId, spellName, castTime, spellScale);
	if (addMoveHook) {
		OnPlayerMoveCallbackComponent* expr_1B = player->Opmcc;
		expr_1B->RegisterSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
		expr_1B->ServerCallbackAdded();
	}
}

void Spell::DoCastFail(Entity* player, bool removeHook)
{
	player->SpellCastData->SCastFailed();
	if (removeHook) {
		player->Opmcc->RemoveSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
	}
	CastingFailed(player);
}

void Spell::AddOnMoveHook(Entity* player)
{
	OnPlayerMoveCallbackComponent* expr_06 = player->Opmcc;
	expr_06->RegisterSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
	expr_06->ServerCallbackAdded();
}

void Spell::RemoveOnMoveHook(Entity* player)
{
	player->Opmcc->RemoveSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
}
Entity* Spell::GetTarget(Entity* player)
{
	return player->TargetComponent->STarget;
}

void Spell::DealDamage(Entity* caster, Entity* target, int damage)
{
	if (target != null) {
		damagePipelineData->Set(damage, false, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		target->Stats->TakeDamage(damagePipelineData->Damage, false, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}

void Spell::DealDamage(Entity* caster, Entity* target, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->DamageMin, spell->DamageMax);
	if (checkParry(caster, target)) {
		return;
	}
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetDamageScaleForLevel(playerData->Level)) * spellScale);
	Stats* stats = caster->Stats;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		PercentStat* sMeleeDamage = stats->SMeleeDamage;
		num = (int)((float)(num) * (sMeleeDamage->ModPercent / (float)100));
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			PercentStat* sSpellDamage = stats->SSpellDamage;
			num = (int)((float)(num) * (sSpellDamage->ModPercent / (float)100));
		}
	}
	float num2 = (float)0;
	float num3 = (float)0;
	bool flag = false;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		num2 = stats->SMeleeCrit->ModPercent;
		num3 = stats->SMeleeCritBonus->ModPercent;
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			num2 = stats->SSpellCrit->ModPercent;
			num3 = stats->SSpellCritBonus->ModPercent;
		}
	}
	num2 /= (float)100;
	if (UnityEngine::Random::value <= num2) {
		flag = true;
	}
	if (flag) {
		num += (int)((float)(num) * (num3 / (float)100));
	}
	if (target != null) {
		Stats* stats2 = target->Stats;
		num = (int)((float)(num) * (((float)100 - stats2->SDamageReduction->ModPercent) / (float)100));
		if (spell->GetSpellType == SpellType::TYPE_MELEE) {
			num = (int)((float)(num) * (((float)100 - stats2->SMeleeDamageReduction->ModPercent) / (float)100));
		}
		else {
			if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
				num = (int)((float)(num) * (((float)100 - stats2->SSpellDamageReduction->ModPercent) / (float)100));
			}
		}
		num = (int)((float)(num) * (stats2->SDamageTaken->ModPercent / (float)100));
		damagePipelineData->Set(num, flag, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		stats2->TakeDamage(damagePipelineData->Damage, flag, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}

void Spell::VashDealDamage(Entity* caster, Entity* target, bool increased, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->DamageMin, spell->DamageMax);
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetDamageScaleForLevel(playerData->Level)) * spellScale);
	Stats* stats = caster->Stats;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		PercentStat* sMeleeDamage = stats->SMeleeDamage;
		num = (int)((float)(num) * (sMeleeDamage->ModPercent / (float)100));
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			PercentStat* sSpellDamage = stats->SSpellDamage;
			num = (int)((float)(num) * (sSpellDamage->ModPercent / (float)100));
		}
	}
	float num2 = (float)0;
	float num3 = (float)0;
	bool flag = false;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		num2 = stats->SMeleeCrit->ModPercent;
		num3 = stats->SMeleeCritBonus->ModPercent;
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			num2 = stats->SSpellCrit->ModPercent;
			num3 = stats->SSpellCritBonus->ModPercent;
		}
	}
	num2 /= (float)100;
	if (UnityEngine::Random::value <= num2) {
		flag = true;
	}
	if (flag) {
		num += (int)((float)(num) * (num3 / (float)100));
	}
	if (increased) {
		num = (int)((float)(num) * (float)1.4);
	}
	if (target != null) {
		Stats* stats2 = target->Stats;
		num = (int)((float)(num) * (((float)100 - stats2->SDamageReduction->ModPercent) / (float)100));
		if (spell->GetSpellType == SpellType::TYPE_MELEE) {
			num = (int)((float)(num) * (((float)100 - stats2->SMeleeDamageReduction->ModPercent) / (float)100));
		}
		else {
			if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
				num = (int)((float)(num) * (((float)100 - stats2->SSpellDamageReduction->ModPercent) / (float)100));
			}
		}
		num = (int)((float)(num) * (stats2->SDamageTaken->ModPercent / (float)100));
		damagePipelineData->Set(num, flag, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		stats2->TakeDamage(damagePipelineData->Damage, flag, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}

void Spell::Heal(Entity* caster, Entity* target, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->SpellHealData->HealMin, spell->SpellHealData->HealMax);
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetHealScaleForLevel(playerData->Level)) * spellScale);
	caster->Stats->TakeHeal(num, false, caster);
}

void Spell::Heal(Entity* caster, Entity* target, int heal)
{
	caster->Stats->TakeHeal(heal, false, caster);
}

bool Spell::checkParry(Entity* caster, Entity* target)
{
	if (spell->GetSpellType != SpellType::TYPE_MELEE) {
		return false;
	}
	Stat* sParry = target->Stats->SParry;
	return (!sParry->Disabled && ((UnityEngine::Random::value * (float)100) <= sParry->ModPercent)) && (Vector3::Angle(caster->transform->forward, target->transform->forward) > (float)90);
}

WorldSpell* Spell::SpawnProjectile(Entity* caster, Entity* target, float spellScale)
{
	SpellProjectileData* spellProjectileData = spell->SpellProjectileData;
	GameObject* arg_B7_0 = UnityEngine::Object::Instantiate<GameObject>(spellProjectileData->Projectile);
	PlayerFacingComponent* playerFacingComponent = caster->PlayerFacingComponent;
	tmp3->Set(playerFacingComponent->SFacing->x, playerFacingComponent->SFacing->y, playerFacingComponent->SFacing->z);
	tmp3->Normalize();
	tmp2->Set(caster->transform->position->x, caster->transform->position->y + (float)1.2, caster->transform->position->z);
	tmp2 += tmp3 * (float)0.4;
	arg_B7_0->transform->position = tmp2;
	arg_B7_0->transform->rotation = caster->transform->rotation;
	WorldSpell* expr_E3 = arg_B7_0->GetComponent<WorldSpell>();
	expr_E3->SetData(spellProjectileData, caster, spell, spellScale, tmp3, null);
	return expr_E3;
}

bool Spell::isInRange(Entity* target, Entity* player)
{
	SpellRangeData* spellRangeData = spell->SpellRangeData;
	tmp2->Set(target->transform->position->x, target->transform->position->y, target->transform->position->z);
	tmp2 -= player->transform->position;
	return tmp2->magnitude < (spellRangeData->Range + ((float)2 * PLAYER_HIT_RADIUS));
}

bool Spell::CanCast(Entity* caster, int skipCheck)
{
	return ((((!IsCasting(caster) && (!spell->HasGlobalCooldown || !HasClobalCooldown(caster))) && !IsSpellOnCooldown(spellId, caster)) && (((skipCheck & 1) == 1) || !IsStunned(caster))) && (((skipCheck & 2) == 2) || !HasState(StateData::StateType::TYPE_ROOT, caster))) && (((skipCheck & 4) == 4) || !HasState(StateData::StateType::TYPE_FROZEN, caster));
}

bool Spell::CanCastTarget(Entity* caster, int skipCheck)
{
	return (((!IsCasting(caster) && (!spell->HasGlobalCooldown || !HasClobalCooldown(caster))) && !IsSpellOnCooldown(spellId, caster)) && (((skipCheck & 1) == 1) || !IsStunned(caster))) && !GetTarget(caster) == null;
}

bool Spell::CanCastTargetRange(Entity* caster, int skipCheck)
{
	if (IsCasting(caster)) {
		return false;
	}
	if (spell->HasGlobalCooldown && HasClobalCooldown(caster)) {
		return false;
	}
	if (IsSpellOnCooldown(spellId, caster)) {
		return false;
	}
	if (((skipCheck & 1) != 1) && IsStunned(caster)) {
		return false;
	}
	Entity* target = GetTarget(caster);
	return !target == null && isInRange(target, caster);
}

bool Spell::SpellCostCheckAndRemove(Entity* caster)
{
	if ((spell->CostType == PlayerResourceTypes::None) && (spell->ItemCost == 0)) {
		return true;
	}
	Inventory* inventory = null;
	if (spell->ItemCost != 0) {
		inventory = caster->Inventory;
		if (!inventory->SHasItem(spell->ItemCost, 1)) {
			return false;
		}
	}
	if (spell->CostType != PlayerResourceTypes::None) {
		PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->CostType);
		if (playerResource == null) {
			return false;
		}
		if (playerResource->Current < spell->CostResource) {
			return false;
		}
		PlayerResource* expr_87 = playerResource;
		expr_87->Current -= spell->CostResource;
	}
	if (spell->ItemCost != 0) {
		inventory->STryToRemoveItem(spell->ItemCost, 1);
	}
	return true;
}

bool Spell::SpellCostCheck(Entity* caster)
{
	if ((spell->CostType == PlayerResourceTypes::None) && (spell->ItemCost == 0)) {
		return true;
	}
	if ((spell->ItemCost != 0) && !caster->Inventory->SHasItem(spell->ItemCost, 1)) {
		return false;
	}
	if (spell->CostType != PlayerResourceTypes::None) {
		PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->CostType);
		if (playerResource == null) {
			return false;
		}
		if (playerResource->Current < spell->CostResource) {
			return false;
		}
	}
	return true;
}

void Spell::SpellResourceGive(Entity* caster)
{
	if (spell->GiveResourceType == PlayerResourceTypes::None) {
		return;
	}
	PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->GiveResourceType);
	if (playerResource == null) {
		return;
	}
	if (playerResource->Current == playerResource->Max) {
		return;
	}
	PlayerResource* expr_39 = playerResource;
	expr_39->Current += spell->GiveResource;
}

void Spell::AddSpellCastEffect(Entity* caster)
{
	SpellCastEffectData* spellCastEffectData = spell->SpellCastEffectData;
	if (spellCastEffectData->Effect == null) {
		return;
	}
	CharacterEffectPointGetter* component = caster->GetComponent<CharacterEffectPointGetter>();
	if (component != null) {
		component->AddSpellCastEffect(spellCastEffectData->Effect);
	}
}

void Spell::RemoveSpellCastEffects(Entity* caster)
{
	CharacterEffectPointGetter* component = caster->GetComponent<CharacterEffectPointGetter>();
	if (component != null) {
		component->RemoveSpellCastEffects();
	}
}

void Spell::AddEffect(Entity* player, GameObject* effectPrefab, EffectPoints bodyPart, Quaternion* rotation)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	GameObject* expr_28 = UnityEngine::Object::Instantiate<GameObject>(effectPrefab, Vector3::zero, Quaternion::identity, effectPoint);
	expr_28->AddComponent<EffectIdAttribute>()->Id = spellId;
	expr_28->transform->localRotation = rotation;
	expr_28->transform->localPosition = Vector3::zero;
}

void Spell::AddWorldEffect(Entity* location, GameObject* effectPrefab, Vector3* offset, Quaternion* rotation)
{
	UnityEngine::Object::Instantiate<GameObject>(effectPrefab, *(location->transform->position) + *offset, location->transform->rotation)->AddComponent<EffectIdAttribute>()->Id = spellId;
}

void Spell::RemoveEffect(Entity* player, EffectPoints bodyPart)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	for (int i = 0; i < effectPoint->childCount; i += 1) {
		Transform* child = effectPoint->GetChild(i);
		EffectIdAttribute* component = child->GetComponent<EffectIdAttribute>();
		if (!component == null && (component->Id == spellId)) {
			child->SetParent(null);
			UnityEngine::Object::Destroy(child->gameObject);
			return;
		}
	}
}

String* Spell::StringifyCooldown(float cooldown)
{
	if (cooldown < (float)60) {
		return BOX<int>((int)(cooldown)) + *(new String(" sec"));
	}
	cooldown /= (float)60;
	int num = (int)(cooldown);
	float num2 = (float)(num);
	if (((double)(cooldown) > ((double)(num2) - 0.05)) && ((double)(cooldown) < ((double)(num2) + 0.05))) {
		return BOX<int>(num) + *(new String(" min"));
	}
	return String::Format(new String("{0:0.0} min"), BOX<float>(cooldown));
}

String* Spell::GetName()
{
	return spell->SpellName;
}

String* Spell::GetDescription(int level)
{
	if (spell->SpellDescription == *(new String(""))) {
		return new String("");
	}
	String* arg_A6_0 = spell->SpellDescription;
	Array<Object>* expr_2E = new Array<Object>(4);
	expr_2E->SetData(0, BOX<int>((int)((float)(spell->DamageMin) * spell->GetDamageScaleForLevel(level))));
	expr_2E->SetData(1, BOX<int>((int)((float)(spell->DamageMax) * spell->GetDamageScaleForLevel(level))));
	expr_2E->SetData(2, StringifyCooldown(spell->Cooldown));
	expr_2E->SetData(3, new String(spell->CastTime) + *(new String(" sec")));
	return String::Format(arg_A6_0, expr_2E);
}

void Spell::SpellCastSuccess(Entity* caster)
{
	caster->SpellMgrComponent->SSendSpellCastSuccess(spellId);
}

void Spell::PlaySound(String* sound)
{
	SoundMgr::PlaySoundAndForget(sound);
}

void Spell::PlayStandardSpellCastFinish()
{
	PlaySound(new String("SpellEnd"));
}

void Spell::PlayStandardSpellCastFinish(Entity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("SpellEnd"));
}

void Spell::PlayStandardIceArcherAttackSpellCastFinish(Entity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("SpellEnd"));
}

void Spell::PlayStandardBerserkerAttackSpellCastFinish(Entity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("MHit"));
}

void Spell::AnimStop(Entity* player)
{
	bool arg_0A_0 = BSSettings::Getinstance()->AnimStopEnabled;
}*/

//Generic

/*

GenericSpell::GenericSpell(Spell* spell) : Spell(spell){
	if (!Mathf::Approximately(spell->CastTime, (float)0)){
		hasCastTime = true;
	}
	if (!Mathf::Approximately(spell->Cooldown, (float)0)) {
		hasCooldown = true;
	}
	if ((spell->DamageMin > 0) && (spell->DamageMax > 0)) {
		damage = true;
	}
}
void GenericSpell::StartCasting(WorldEntity* caster, float spellScale)
{
	if ((spell->GenericSpellData->NeedsTarget || damage) && !hasCastTime) {
		if (!Spell::CanCastTarget(caster, 0)) {
			return;
		}
	}
	else {
		if (!Spell::CanCast(caster, 0)) {
			return;
		}
	}
	WorldEntity* worldEntity = null;
	if (spell->GenericSpellData->NeedsTarget || damage) {
		worldEntity = Spell::GetTarget(caster);
	}
	if (!hasCastTime) {
		if (spell->SpellRangeData->Enabled && !Spell::isInRange(caster, worldEntity)) {
			return;
		}
		HandleSpellEffect(caster, worldEntity, spellScale);
		return;
	}
	else {
		if (!Spell::SpellCostCheck(caster)) {
			return;
		}
		Spell::DoStartCasting(caster, spellId, spell->SpellName, spell->CastTime, !spell->GenericSpellData->CanMoveWhileCasting, spellScale);
		return;
	}
}
void GenericSpell::CastingFinished(WorldEntity* caster, float spellScale)
{
	WorldEntity* worldEntity = null;
	if (spell->GenericSpellData->NeedsTarget || damage) {
		worldEntity = Spell::GetTarget(caster);
	}
	if (spell->GenericSpellData->NeedsTarget && (worldEntity == null)) {
		return;
	}
	if (spell->SpellRangeData->Enabled && !Spell::isInRange(caster, worldEntity)) {
		return;
	}
	HandleSpellEffect(caster, worldEntity, spellScale);
	if (hasCastTime && !spell->GenericSpellData->CanMoveWhileCasting) {
		Spell::RemoveOnMoveHook(caster);
	}
}
void GenericSpell::SpellHit(WorldEntity* caster, WorldEntity* target, WorldSpell* worldSpell, Spell* spellGO, float spellScale)
{
	if (target->CompareTag(new String("Player"))) {
		if (damage) {
			Spell::DealDamage(caster, target, spellScale);
		}
		if (spell->SpellHealData->Enabled) {
			Spell::Heal(caster, caster, spellScale);
		}
		if (spell->CasterAuraApply != 0) {
			Spell::ApplyAura(spell->CasterAuraApply, caster, spellScale);
		}
		if (spell->CasterAuraApply2 != 0) {
			Spell::ApplyAura(spell->CasterAuraApply2, caster, spellScale);
		}
		if (spell->TargetAuraApply != 0) {
			Spell::ApplyAura(spell->TargetAuraApply, target, spellScale);
		}
		if (spell->TargetAuraApply2 != 0) {
			Spell::ApplyAura(spell->TargetAuraApply2, target, spellScale);
		}
		HandleSpellStatValueMod(caster);
	}
	if (spell->SpellProjectileData->DestroyOnImpact) {
		worldSpell->Destroy();
	}
}
void GenericSpell::OnPlayerMove(Entity* caster)
{
	Spell::DoCastFail((WorldEntity*)(caster), true);
}
void GenericSpell::HandleSpellEffect(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	if (!Spell::SpellCostCheckAndRemove(caster)) {
		return;
	}
	if (!spell->SpellProjectileData->Enabled) {
		if (damage) {
			Spell::DealDamage(caster, target, spellScale);
		}
		if (spell->SpellHealData->Enabled) {
			Spell::Heal(caster, caster, spellScale);
		}
		if (spell->CasterAuraApply != 0) {
			Spell::ApplyAura(spell->CasterAuraApply, caster, spellScale);
		}
		if (spell->CasterAuraApply2 != 0) {
			Spell::ApplyAura(spell->CasterAuraApply2, caster, spellScale);
		}
		if (spell->TargetAuraApply != 0) {
			Spell::ApplyAura(spell->TargetAuraApply, caster, target, spellScale);
		}
		if (spell->TargetAuraApply2 != 0) {
			Spell::ApplyAura(spell->TargetAuraApply2, caster, target, spellScale);
		}
		HandleSpellStatValueMod(caster);
	}
	else {
		Spell::SpawnProjectile(caster, target, spellScale);
	}
	if (spell->HasGlobalCooldown && !hasCastTime) {
		Spell::TriggerGlobalCooldown(caster);
	}
	Spell::SpellResourceGive(caster);
	if (hasCooldown) {
		Spell::AddCooldown(caster, spellId, spell->Cooldown);
	}
	Spell::SpellCastSuccess(caster);
}
void GenericSpell::HandleSpellStatValueMod(WorldEntity* caster)
{
	if (!spell->SpellStatValueModData->Enabled) {
		return;
	}
	Stats* stats = caster->Stats;
	for (int i = 0; i < spell->SpellStatValueModData->StatValueMods->Count; i += 1) {
		SpellStatValueModAttributeHelper* spellStatValueModAttributeHelper = spell->SpellStatValueModData->StatValueMods->GetData(i);
		ValueStat* valueStat = (ValueStat*)(stats->GetSStatFromId(spellStatValueModAttributeHelper->Stat));
		if (spellStatValueModAttributeHelper->Stat != 0) {
			if (spellStatValueModAttributeHelper->HasValueMod) {
				ValueStat* expr_5B = valueStat;
				expr_5B->Current += spellStatValueModAttributeHelper->GiveValue;
			}
			if (spellStatValueModAttributeHelper->HasPercentMod) {
				ValueStat* expr_79 = valueStat;
				expr_79->Current += valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100);
			}
		}
		else {
			if (spellStatValueModAttributeHelper->HasValueMod) {
				if (spellStatValueModAttributeHelper->GiveValue > (float)0) {
					stats->TakeHeal((int)(spellStatValueModAttributeHelper->GiveValue), false, caster);
				}
				else {
					stats->TakeDamage((int)(spellStatValueModAttributeHelper->GiveValue), false, caster);
				}
			}
			if (spellStatValueModAttributeHelper->HasPercentMod) {
				if (spellStatValueModAttributeHelper->GivePercentValue > (float)0) {
					stats->TakeHeal((int)(valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100)), false, caster);
				}
				else {
					stats->TakeDamage((int)(valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100)), false, caster);
				}
			}
		}
	}
}
void GenericSpell::COnSpellCastSuccess(WorldEntity* player)
{
	if (!hasCastTime && damage) {
		Spell::PlayStandardSpellCastFinish(player);
		return;
	}
	Spell::PlayStandardSpellCastFinish();
}
void GenericSpell::COnSpellCastStarted(WorldEntity* player)
{
	if (spell->SpellCastEffectData->Enabled) {
		Spell::AddSpellCastEffect(player);
	}
}
void GenericSpell::COnSpellCastEnded(WorldEntity* player)
{
	if (spell->SpellCastEffectData->Enabled) {
		Spell::RemoveSpellCastEffects(player);
	}
}

*/
