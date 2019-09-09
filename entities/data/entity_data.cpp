#include "entity_data.h"

#include "../../data/spell.h"
#include "../../data/aura.h"
#include "../entity.h"
#include "character_spec.h"
#include "../../infos/spell_cast_info.h"
#include "../../ai/ai_action.h"

int EntityData::get_id() {
	return _id;
}

void EntityData::set_id(int value) {
	_id = value;
}

String EntityData::get_entity_data_name() {
	return _entity_data_name;
}

void EntityData::set_entity_data_name(String value) {
	_entity_data_name = value;
}

Ref<Texture> EntityData::get_icon() {
	return _icon;
}

void EntityData::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

int EntityData::get_player_resource_type() {
	return _player_resource_type;
}

void EntityData::set_player_resource_type(int value) {
	_player_resource_type = value;
}

Ref<StatData> EntityData::get_stat_data() {
	return _stat_data;
}

void EntityData::set_stat_data(Ref<StatData> value) {
	_stat_data = value;
}

////    SPECS    ////

int EntityData::get_num_specs() {
	return _specs.size();
}
void EntityData::set_num_specs(int value) {
	_specs.resize(value);
}

Ref<CharacterSpec> EntityData::get_spec(int index) const {
	ERR_FAIL_INDEX_V(index, _specs.size(), Ref<CharacterSpec>());

	return _specs[index];
}
void EntityData::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, _specs.size());

	_specs.set(index, Ref<CharacterSpec>(spec));
}

Vector<Variant> EntityData::get_specs() {
	Vector<Variant> r;
	for (int i = 0; i < _specs.size(); i++) {
		r.push_back(_specs[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_specs(const Vector<Variant> &specs) {
	_specs.clear();
	for (int i = 0; i < specs.size(); i++) {
		Ref<CharacterSpec> spec = Ref<CharacterSpec>(specs[i]);

		_specs.push_back(spec);
	}
}

////    SPELLS    ////

int EntityData::get_num_spells() {
	return _spells.size();
}
void EntityData::set_num_spells(int value) {
	_spells.resize(value);
}

Ref<Spell> EntityData::get_spell(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells[index];
}
void EntityData::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> EntityData::get_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _spells.size(); i++) {
		r.push_back(_spells[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_spells(const Vector<Variant> &spells) {
	_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_spells.push_back(spell);
	}
}

////    AURAS    ////

int EntityData::get_num_auras() {
	return _auras.size();
}
void EntityData::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> EntityData::get_aura(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras[index];
}
void EntityData::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}

Vector<Variant> EntityData::get_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
		r.push_back(_auras[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(auras[i]);

		_auras.push_back(aura);
	}
}

////    AI ACTIONS    ////

int EntityData::get_num_ai_actions() {
	return _ai_actions.size();
}
void EntityData::set_num_ai_actions(int value) {
	_ai_actions.resize(value);
}

Ref<AIAction> EntityData::get_ai_action(int index) {
	ERR_FAIL_INDEX_V(index, _ai_actions.size(), Ref<AIAction>());

	return _ai_actions[index];
}
void EntityData::set_ai_action(int index, Ref<AIAction> ai_action) {
	ERR_FAIL_INDEX(index, _ai_actions.size());

	_ai_actions.set(index, ai_action);
}

Vector<Variant> EntityData::get_ai_actions() {
	Vector<Variant> r;
	for (int i = 0; i < _ai_actions.size(); i++) {
		r.push_back(_ai_actions[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_ai_actions(const Vector<Variant> &ai_actions) {
	_ai_actions.clear();
	for (int i = 0; i < ai_actions.size(); i++) {
		Ref<AIAction> ai_action = Ref<AIAction>(ai_actions[i]);

		_ai_actions.push_back(ai_action);
	}
}

////    SETUP    ////

void EntityData::setup_resources(Entity *entity) {
	if (has_method("_setup_resources"))
		call("_setup_resources", entity);
}
//void EntityData::_setup_resources(Entity *entity) {
//}

/*
Vector<int> EntityData::get_mob_party_ids() {
	return _mob_party_ids;
}

void EntityData::set_mob_party_ids(Vector<int> ids) {
	//specs;
}

Vector<int> EntityData::get_mob_dislike_ids() {
	return _mob_dislike_ids;
}

void EntityData::set_mob_dislike_ids(Vector<int> ids) {
	//specs;
}
*/
/*
int EntityData::get_inspector_max_spells() {
	return _inspector_max_spells;
}

void EntityData::set_inspector_max_spells(int value) {
	_inspector_max_spells = value;
}*/

void EntityData::start_casting(int spell_id, Entity *caster, float spellScale) {
	for (int i = 0; i < _spells.size(); i++) {
		Ref<Spell> s = _spells[i];

		if (s == NULL) {
			print_error("class doesn't have spell! spell_id: " + itos(spell_id));
			return;
		}

		if (s->get_spell_id() == spell_id) {
			s->sstart_casting_simple(caster, spellScale);
			return;
		}
	}
}


void EntityData::son_before_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast"))
		call("_son_before_cast", info);
}

void EntityData::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", info);
}

void EntityData::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", info);
}

void EntityData::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_started"))
		call("_son_cast_started", info);
}

void EntityData::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", info);
}

void EntityData::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", info);
}

void EntityData::son_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_hit"))
		call("_son_hit", data);
}

void EntityData::son_before_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage"))
		call("_son_before_damage", data);
}

void EntityData::son_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", data);
}

void EntityData::son_dealt_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", data);
}

void EntityData::son_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", data);
}

void EntityData::son_before_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal"))
		call("_son_before_heal", data);
}

void EntityData::son_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", data);
}

void EntityData::son_dealt_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", data);
}

void EntityData::son_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", data);
}

void EntityData::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);
}

void EntityData::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);
}

void EntityData::son_death(Entity *entity) {
    if (has_method("_son_death"))
		call("_son_death", entity);
}

void EntityData::son_death_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_death(e);
}

void EntityData::son_cooldown_added(Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_added"))
		call("_son_cooldown_added", cooldown);
}
void EntityData::son_cooldown_removed(Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", cooldown);
}
	
void EntityData::son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", category_cooldown);
}
void EntityData::son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", category_cooldown);
}

void EntityData::son_gcd_started(Entity *entity, float gcd) {
	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", entity, gcd);
}
void EntityData::son_gcd_finished(Entity *entity) {
	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished", entity);
}
void EntityData::son_gcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_gcd_started(e, gcd);
}
void EntityData::son_gcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_gcd_finished(e);
}

//Clientside Event Handlers
void EntityData::con_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_failed"))
		call("_con_cast_failed", info);
}
void EntityData::con_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_started"))
		call("_con_cast_started", info);
}
void EntityData::con_cast_state_changed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed", info);
}
void EntityData::con_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_finished"))
		call("_con_cast_finished", info);
}
void EntityData::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success", info);
}

void EntityData::con_death(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);
	
    if (has_method("_con_death"))
		call("_con_death", entity);
}

void EntityData::con_death_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_death(e);
}

void EntityData::con_cooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());
	
	if (has_method("_con_cooldown_added"))
		call("_con_cooldown_added", cooldown);
}
void EntityData::con_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());
	
	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed", cooldown);
}
void EntityData::con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());
	
	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added", category_cooldown);
}
void EntityData::con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());
	
	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed", category_cooldown);
}

void EntityData::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_added"))
		call("_con_aura_added", data);
}

void EntityData::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", data);
}

void EntityData::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh", data);
}

void EntityData::con_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", info);
}

void EntityData::con_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", info);
}

void EntityData::con_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", info);
}

void EntityData::con_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", info);
}

void EntityData::con_gcd_started(Entity *entity, float gcd) {
	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", entity, gcd);
}
void EntityData::con_gcd_finished(Entity *entity) {
	if (has_method("_con_gcd_finished"))
		call("_con_gcd_finished", entity);
}
void EntityData::con_gcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_gcd_started(e, gcd);
}
void EntityData::con_gcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_gcd_finished(e);
}


void EntityData::sai_follow(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_follow")) {
		call("_sai_follow", entity);
	}
}
void EntityData::sai_rest(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_rest")) {
		call("_sai_rest", entity);
	}
}
void EntityData::sai_regenerate(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_regenerate")) {
		call("_sai_regenerate", entity);
	}
}
void EntityData::sai_attack(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_attack")) {
		call("_sai_attack", entity);
	}
}

void EntityData::sai_follow_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_follow(e);
}
void EntityData::sai_rest_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_rest(e);
}
void EntityData::sai_regenerate_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_regenerate(e);
}
void EntityData::sai_attack_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_attack(e);
}

void EntityData::_bind_methods() {
    //EventHandlers
	ClassDB::bind_method(D_METHOD("son_before_cast", "info"), &EntityData::son_before_cast);
	ClassDB::bind_method(D_METHOD("son_before_cast_target", "info"), &EntityData::son_before_cast_target);
	ClassDB::bind_method(D_METHOD("son_cast_started", "info"), &EntityData::son_cast_started);
	ClassDB::bind_method(D_METHOD("son_cast_failed", "info"), &EntityData::son_cast_failed);
	ClassDB::bind_method(D_METHOD("son_cast_finished", "info"), &EntityData::son_cast_finished);
	ClassDB::bind_method(D_METHOD("son_cast_finished_target", "info"), &EntityData::son_cast_finished_target);

	ClassDB::bind_method(D_METHOD("son_hit", "data"), &EntityData::son_hit);

	ClassDB::bind_method(D_METHOD("son_before_damage", "data"), &EntityData::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_damage_receive", "data"), &EntityData::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_damage", "data"), &EntityData::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "data"), &EntityData::son_damage_dealt);

	ClassDB::bind_method(D_METHOD("son_before_heal", "data"), &EntityData::son_before_heal);
	ClassDB::bind_method(D_METHOD("son_heal_receive", "data"), &EntityData::son_heal_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_heal", "data"), &EntityData::son_dealt_heal);
	ClassDB::bind_method(D_METHOD("son_heal_dealt", "data"), &EntityData::son_heal_dealt);

	ClassDB::bind_method(D_METHOD("son_before_aura_applied", "data"), &EntityData::son_before_aura_applied);
	ClassDB::bind_method(D_METHOD("son_after_aura_applied", "data"), &EntityData::son_after_aura_applied);
    
    ClassDB::bind_method(D_METHOD("son_death", "data"), &EntityData::son_death_bind);
	
	ClassDB::bind_method(D_METHOD("son_cooldown_added", "cooldown"), &EntityData::son_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_cooldown_removed", "cooldown"), &EntityData::son_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("son_category_cooldown_added", "category_cooldown"), &EntityData::son_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_category_cooldown_removed", "category_cooldown"), &EntityData::son_category_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("son_gcd_started", "entity", "gcd"), &EntityData::son_gcd_started_bind);
	ClassDB::bind_method(D_METHOD("son_gcd_finished", "entity"), &EntityData::son_gcd_finished_bind);
	
	BIND_VMETHOD(MethodInfo("_son_before_cast", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_cast_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_son_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_heal", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_after_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
    
    BIND_VMETHOD(MethodInfo("_son_death", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
    
	BIND_VMETHOD(MethodInfo("_sai_follow", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_rest", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_regenerate", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_attack", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	
	BIND_VMETHOD(MethodInfo("_son_cooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_son_cooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	
	BIND_VMETHOD(MethodInfo("_son_category_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_son_category_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_son_gcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_son_gcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_setup_resources", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
    
    //Clientside Event Handlers
	ClassDB::bind_method(D_METHOD("con_cast_failed", "info"), &EntityData::con_cast_failed);
	ClassDB::bind_method(D_METHOD("con_cast_started", "info"), &EntityData::con_cast_started);
	ClassDB::bind_method(D_METHOD("con_cast_state_changed", "info"), &EntityData::con_cast_state_changed);
	ClassDB::bind_method(D_METHOD("con_cast_finished", "info"), &EntityData::con_cast_finished);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "info"), &EntityData::con_spell_cast_success);

	ClassDB::bind_method(D_METHOD("con_death", "data"), &EntityData::con_death_bind);
	
	ClassDB::bind_method(D_METHOD("con_cooldown_added", "cooldown"), &EntityData::con_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_cooldown_removed", "cooldown"), &EntityData::con_cooldown_removed);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_added", "cooldown"), &EntityData::con_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_removed", "cooldown"), &EntityData::con_category_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("con_aura_added", "data"), &EntityData::con_aura_added);
	ClassDB::bind_method(D_METHOD("con_aura_removed", "data"), &EntityData::con_aura_removed);
	ClassDB::bind_method(D_METHOD("con_aura_refresh", "data"), &EntityData::con_aura_refresh);
	
	ClassDB::bind_method(D_METHOD("con_gcd_started", "entity", "gcd"), &EntityData::con_gcd_started_bind);
	ClassDB::bind_method(D_METHOD("con_gcd_finished", "entity"), &EntityData::con_gcd_finished_bind);

	BIND_VMETHOD(MethodInfo("_con_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_state_changed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_finished", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_success", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	
	BIND_VMETHOD(MethodInfo("_con_death", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	
	BIND_VMETHOD(MethodInfo("_con_cooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_con_cooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_con_category_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_con_category_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_con_aura_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_refresh", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
    
	BIND_VMETHOD(MethodInfo("_con_gcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_con_gcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	
	ClassDB::bind_method(D_METHOD("sai_follow", "entity"), &EntityData::sai_follow_bind);
	ClassDB::bind_method(D_METHOD("sai_rest", "entity"), &EntityData::sai_rest_bind);
	ClassDB::bind_method(D_METHOD("sai_regenerate", "entity"), &EntityData::sai_regenerate_bind);
	ClassDB::bind_method(D_METHOD("sai_attack", "entity"), &EntityData::sai_attack_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &EntityData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_entity_data_name"), &EntityData::get_entity_data_name);
	ClassDB::bind_method(D_METHOD("set_entity_data_name", "value"), &EntityData::set_entity_data_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_data_name"), "set_entity_data_name", "get_entity_data_name");

	ClassDB::bind_method(D_METHOD("get_icon"), &EntityData::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &EntityData::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &EntityData::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &EntityData::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_player_resource_type"), &EntityData::get_player_resource_type);
	ClassDB::bind_method(D_METHOD("set_player_resource_type", "value"), &EntityData::set_player_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "player_resource_type", PROPERTY_HINT_ENUM, "None, Rage, Mana, Energy, Time Anomaly"), "set_player_resource_type", "get_player_resource_type");

	////    Specs    ////
	ClassDB::bind_method(D_METHOD("get_num_specs"), &EntityData::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &EntityData::set_num_specs);

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &EntityData::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &EntityData::set_spec);

    ClassDB::bind_method(D_METHOD("get_specs"), &EntityData::get_specs);
	ClassDB::bind_method(D_METHOD("set_specs", "specs"), &EntityData::set_specs);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "specs", PROPERTY_HINT_NONE, "17/17:CharacterSpec", PROPERTY_USAGE_DEFAULT, "CharacterSpec"), "set_specs", "get_specs");
    
    ////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &EntityData::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &EntityData::set_num_spells);

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &EntityData::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &EntityData::set_spell);

    ClassDB::bind_method(D_METHOD("get_spells"), &EntityData::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &EntityData::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	////    AURAS    ////
	ClassDB::bind_method(D_METHOD("get_num_auras"), &EntityData::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &EntityData::set_num_auras);
    
	ClassDB::bind_method(D_METHOD("get_aura", "index"), &EntityData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &EntityData::set_aura);

    ClassDB::bind_method(D_METHOD("get_auras"), &EntityData::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &EntityData::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	////    AI ACTIONS    ////
	ClassDB::bind_method(D_METHOD("get_num_ai_actions"), &EntityData::get_num_ai_actions);
	ClassDB::bind_method(D_METHOD("set_num_ai_actions", "value"), &EntityData::set_num_ai_actions);
    
	ClassDB::bind_method(D_METHOD("get_ai_action", "index"), &EntityData::get_ai_action);
	ClassDB::bind_method(D_METHOD("set_ai_action", "index", "action"), &EntityData::set_ai_action);

    ClassDB::bind_method(D_METHOD("get_ai_actions"), &EntityData::get_ai_actions);
	ClassDB::bind_method(D_METHOD("set_ai_actions", "auras"), &EntityData::set_ai_actions);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ai_actions", PROPERTY_HINT_NONE, "17/17:AIAction", PROPERTY_USAGE_DEFAULT, "AIAction"), "set_ai_actions", "get_ai_actions");
}

EntityData::EntityData() {
	//_spells = memnew(Vector<Ref<Spell> >());
	_id = 0;
	_player_resource_type = 0;
}

EntityData::~EntityData() {
	_spells.clear();
	_specs.clear();
	_auras.clear();
}
