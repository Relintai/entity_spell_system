#include "character_class.h"

#include "../data/spell.h"
#include "../data/aura.h"
#include "../entities/entity.h"
#include "character_spec.h"
#include "../infos/spell_cast_info.h"

int CharacterClass::get_id() {
	return _id;
}

void CharacterClass::set_id(int value) {
	_id = value;
}

String CharacterClass::get_character_class_name() {
	return _character_class_name;
}

void CharacterClass::set_character_class_name(String value) {
	_character_class_name = value;
}

Ref<Texture> CharacterClass::get_icon() {
	return _icon;
}

void CharacterClass::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

int CharacterClass::get_player_resource_type() {
	return _player_resource_type;
}

void CharacterClass::set_player_resource_type(int value) {
	_player_resource_type = value;
}

Ref<StatData> CharacterClass::get_stat_data() {
	return _stat_data;
}

void CharacterClass::set_stat_data(Ref<StatData> value) {
	_stat_data = value;
}

////    SPECS    ////

int CharacterClass::get_num_specs() {
	return _specs.size();
}
void CharacterClass::set_num_specs(int value) {
	_specs.resize(value);
}

Ref<CharacterSpec> CharacterClass::get_spec(int index) const {
	ERR_FAIL_INDEX_V(index, _specs.size(), Ref<CharacterSpec>());

	return _specs[index];
}
void CharacterClass::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, _specs.size());

	_specs.set(index, Ref<CharacterSpec>(spec));
}

Vector<Variant> CharacterClass::get_specs() {
	Vector<Variant> r;
	for (int i = 0; i < _specs.size(); i++) {
		r.push_back(_specs[i].get_ref_ptr());
	}
	return r;
}
void CharacterClass::set_specs(const Vector<Variant> &specs) {
	_specs.clear();
	for (int i = 0; i < specs.size(); i++) {
		Ref<CharacterSpec> spec = Ref<CharacterSpec>(specs[i]);

		_specs.push_back(spec);
	}
}

////    SPELLS    ////

int CharacterClass::get_num_spells() {
	return _spells.size();
}
void CharacterClass::set_num_spells(int value) {
	_spells.resize(value);
}

Ref<Spell> CharacterClass::get_spell(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells[index];
}
void CharacterClass::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> CharacterClass::get_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _spells.size(); i++) {
		r.push_back(_spells[i].get_ref_ptr());
	}
	return r;
}
void CharacterClass::set_spells(const Vector<Variant> &spells) {
	_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_spells.push_back(spell);
	}
}

////    AURAS    ////

int CharacterClass::get_num_auras() {
	return _auras.size();
}
void CharacterClass::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> CharacterClass::get_aura(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras[index];
}
void CharacterClass::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}

Vector<Variant> CharacterClass::get_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
		r.push_back(_auras[i].get_ref_ptr());
	}
	return r;
}
void CharacterClass::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(auras[i]);

		_auras.push_back(aura);
	}
}


void CharacterClass::setup_resources(Entity *entity) {
	if (has_method("_setup_resources"))
		call("_setup_resources", entity);
}
//void CharacterClass::_setup_resources(Entity *entity) {
//}

/*
Vector<int> CharacterClass::get_mob_party_ids() {
	return _mob_party_ids;
}

void CharacterClass::set_mob_party_ids(Vector<int> ids) {
	//specs;
}

Vector<int> CharacterClass::get_mob_dislike_ids() {
	return _mob_dislike_ids;
}

void CharacterClass::set_mob_dislike_ids(Vector<int> ids) {
	//specs;
}
*/
/*
int CharacterClass::get_inspector_max_spells() {
	return _inspector_max_spells;
}

void CharacterClass::set_inspector_max_spells(int value) {
	_inspector_max_spells = value;
}*/

void CharacterClass::start_casting(int spell_id, Entity *caster, float spellScale) {
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


void CharacterClass::son_before_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast"))
		call("_son_before_cast", info);
}

void CharacterClass::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", info);
}

void CharacterClass::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", info);
}

void CharacterClass::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_started"))
		call("_son_cast_started", info);
}

void CharacterClass::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", info);
}

void CharacterClass::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", info);
}

void CharacterClass::son_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_hit"))
		call("_son_hit", data);
}

void CharacterClass::son_before_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage"))
		call("_son_before_damage", data);
}

void CharacterClass::son_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", data);
}

void CharacterClass::son_dealt_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", data);
}

void CharacterClass::son_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", data);
}

void CharacterClass::son_before_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal"))
		call("_son_before_heal", data);
}

void CharacterClass::son_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", data);
}

void CharacterClass::son_dealt_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", data);
}

void CharacterClass::son_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", data);
}

void CharacterClass::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);
}

void CharacterClass::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);
}

void CharacterClass::son_death(Entity *entity) {
    if (has_method("_son_death"))
		call("_son_death", entity);
}

void CharacterClass::son_death_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_death(e);
}

void CharacterClass::son_cooldown_added(Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_added"))
		call("_son_cooldown_added", cooldown);
}
void CharacterClass::son_cooldown_removed(Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", cooldown);
}
	
void CharacterClass::son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", category_cooldown);
}
void CharacterClass::son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", category_cooldown);
}

void CharacterClass::son_gcd_started(Entity *entity, float gcd) {
	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", entity, gcd);
}
void CharacterClass::son_gcd_finished(Entity *entity) {
	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished", entity);
}
void CharacterClass::son_gcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_gcd_started(e, gcd);
}
void CharacterClass::son_gcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_gcd_finished(e);
}

//Clientside Event Handlers
void CharacterClass::con_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_failed"))
		call("_con_cast_failed", info);
}
void CharacterClass::con_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_started"))
		call("_con_cast_started", info);
}
void CharacterClass::con_cast_state_changed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed", info);
}
void CharacterClass::con_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_cast_finished"))
		call("_con_cast_finished", info);
}
void CharacterClass::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	
	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success", info);
}

void CharacterClass::con_death(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);
	
    if (has_method("_con_death"))
		call("_con_death", entity);
}

void CharacterClass::con_death_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_death(e);
}

void CharacterClass::con_cooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());
	
	if (has_method("_con_cooldown_added"))
		call("_con_cooldown_added", cooldown);
}
void CharacterClass::con_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());
	
	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed", cooldown);
}
void CharacterClass::con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());
	
	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added", category_cooldown);
}
void CharacterClass::con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());
	
	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed", category_cooldown);
}

void CharacterClass::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_added"))
		call("_con_aura_added", data);
}

void CharacterClass::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", data);
}

void CharacterClass::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh", data);
}

void CharacterClass::con_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", info);
}

void CharacterClass::con_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", info);
}

void CharacterClass::con_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", info);
}

void CharacterClass::con_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", info);
}

void CharacterClass::con_gcd_started(Entity *entity, float gcd) {
	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", entity, gcd);
}
void CharacterClass::con_gcd_finished(Entity *entity) {
	if (has_method("_con_gcd_finished"))
		call("_con_gcd_finished", entity);
}
void CharacterClass::con_gcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_gcd_started(e, gcd);
}
void CharacterClass::con_gcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_gcd_finished(e);
}


void CharacterClass::sai_follow(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_follow")) {
		call("_sai_follow", entity);
	}
}
void CharacterClass::sai_rest(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_rest")) {
		call("_sai_rest", entity);
	}
}
void CharacterClass::sai_regenerate(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_regenerate")) {
		call("_sai_regenerate", entity);
	}
}
void CharacterClass::sai_attack(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_attack")) {
		call("_sai_attack", entity);
	}
}

void CharacterClass::sai_follow_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_follow(e);
}
void CharacterClass::sai_rest_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_rest(e);
}
void CharacterClass::sai_regenerate_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_regenerate(e);
}
void CharacterClass::sai_attack_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sai_attack(e);
}

void CharacterClass::_bind_methods() {
    //EventHandlers
	ClassDB::bind_method(D_METHOD("son_before_cast", "info"), &CharacterClass::son_before_cast);
	ClassDB::bind_method(D_METHOD("son_before_cast_target", "info"), &CharacterClass::son_before_cast_target);
	ClassDB::bind_method(D_METHOD("son_cast_started", "info"), &CharacterClass::son_cast_started);
	ClassDB::bind_method(D_METHOD("son_cast_failed", "info"), &CharacterClass::son_cast_failed);
	ClassDB::bind_method(D_METHOD("son_cast_finished", "info"), &CharacterClass::son_cast_finished);
	ClassDB::bind_method(D_METHOD("son_cast_finished_target", "info"), &CharacterClass::son_cast_finished_target);

	ClassDB::bind_method(D_METHOD("son_hit", "data"), &CharacterClass::son_hit);

	ClassDB::bind_method(D_METHOD("son_before_damage", "data"), &CharacterClass::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_damage_receive", "data"), &CharacterClass::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_damage", "data"), &CharacterClass::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "data"), &CharacterClass::son_damage_dealt);

	ClassDB::bind_method(D_METHOD("son_before_heal", "data"), &CharacterClass::son_before_heal);
	ClassDB::bind_method(D_METHOD("son_heal_receive", "data"), &CharacterClass::son_heal_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_heal", "data"), &CharacterClass::son_dealt_heal);
	ClassDB::bind_method(D_METHOD("son_heal_dealt", "data"), &CharacterClass::son_heal_dealt);

	ClassDB::bind_method(D_METHOD("son_before_aura_applied", "data"), &CharacterClass::son_before_aura_applied);
	ClassDB::bind_method(D_METHOD("son_after_aura_applied", "data"), &CharacterClass::son_after_aura_applied);
    
    ClassDB::bind_method(D_METHOD("son_death", "data"), &CharacterClass::son_death_bind);
	
	ClassDB::bind_method(D_METHOD("son_cooldown_added", "cooldown"), &CharacterClass::son_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_cooldown_removed", "cooldown"), &CharacterClass::son_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("son_category_cooldown_added", "category_cooldown"), &CharacterClass::son_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("son_category_cooldown_removed", "category_cooldown"), &CharacterClass::son_category_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("son_gcd_started", "entity", "gcd"), &CharacterClass::son_gcd_started_bind);
	ClassDB::bind_method(D_METHOD("son_gcd_finished", "entity"), &CharacterClass::son_gcd_finished_bind);
	
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
	ClassDB::bind_method(D_METHOD("con_cast_failed", "info"), &CharacterClass::con_cast_failed);
	ClassDB::bind_method(D_METHOD("con_cast_started", "info"), &CharacterClass::con_cast_started);
	ClassDB::bind_method(D_METHOD("con_cast_state_changed", "info"), &CharacterClass::con_cast_state_changed);
	ClassDB::bind_method(D_METHOD("con_cast_finished", "info"), &CharacterClass::con_cast_finished);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "info"), &CharacterClass::con_spell_cast_success);

	ClassDB::bind_method(D_METHOD("con_death", "data"), &CharacterClass::con_death_bind);
	
	ClassDB::bind_method(D_METHOD("con_cooldown_added", "cooldown"), &CharacterClass::con_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_cooldown_removed", "cooldown"), &CharacterClass::con_cooldown_removed);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_added", "cooldown"), &CharacterClass::con_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_removed", "cooldown"), &CharacterClass::con_category_cooldown_removed);
	
	ClassDB::bind_method(D_METHOD("con_aura_added", "data"), &CharacterClass::con_aura_added);
	ClassDB::bind_method(D_METHOD("con_aura_removed", "data"), &CharacterClass::con_aura_removed);
	ClassDB::bind_method(D_METHOD("con_aura_refresh", "data"), &CharacterClass::con_aura_refresh);
	
	ClassDB::bind_method(D_METHOD("con_gcd_started", "entity", "gcd"), &CharacterClass::con_gcd_started_bind);
	ClassDB::bind_method(D_METHOD("con_gcd_finished", "entity"), &CharacterClass::con_gcd_finished_bind);

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
	
	ClassDB::bind_method(D_METHOD("sai_follow", "entity"), &CharacterClass::sai_follow_bind);
	ClassDB::bind_method(D_METHOD("sai_rest", "entity"), &CharacterClass::sai_rest_bind);
	ClassDB::bind_method(D_METHOD("sai_regenerate", "entity"), &CharacterClass::sai_regenerate_bind);
	ClassDB::bind_method(D_METHOD("sai_attack", "entity"), &CharacterClass::sai_attack_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &CharacterClass::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CharacterClass::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_character_class_name"), &CharacterClass::get_character_class_name);
	ClassDB::bind_method(D_METHOD("set_character_class_name", "value"), &CharacterClass::set_character_class_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "character_class_name"), "set_character_class_name", "get_character_class_name");

	ClassDB::bind_method(D_METHOD("get_icon"), &CharacterClass::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &CharacterClass::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &CharacterClass::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &CharacterClass::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_player_resource_type"), &CharacterClass::get_player_resource_type);
	ClassDB::bind_method(D_METHOD("set_player_resource_type", "value"), &CharacterClass::set_player_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "player_resource_type", PROPERTY_HINT_ENUM, "None, Rage, Mana, Energy, Time Anomaly"), "set_player_resource_type", "get_player_resource_type");

	////    Specs    ////
	ClassDB::bind_method(D_METHOD("get_num_specs"), &CharacterClass::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &CharacterClass::set_num_specs);

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &CharacterClass::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &CharacterClass::set_spec);

    ClassDB::bind_method(D_METHOD("get_specs"), &CharacterClass::get_specs);
	ClassDB::bind_method(D_METHOD("set_specs", "specs"), &CharacterClass::set_specs);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "specs", PROPERTY_HINT_NONE, "17/17:CharacterSpec", PROPERTY_USAGE_DEFAULT, "CharacterSpec"), "set_specs", "get_specs");
    
    ////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &CharacterClass::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &CharacterClass::set_num_spells);

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &CharacterClass::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &CharacterClass::set_spell);

    ClassDB::bind_method(D_METHOD("get_spells"), &CharacterClass::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &CharacterClass::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	////    AURAS    ////
	ClassDB::bind_method(D_METHOD("get_num_auras"), &CharacterClass::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &CharacterClass::set_num_auras);
    
	ClassDB::bind_method(D_METHOD("get_aura", "index"), &CharacterClass::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &CharacterClass::set_aura);

    ClassDB::bind_method(D_METHOD("get_auras"), &CharacterClass::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &CharacterClass::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");
    

}

CharacterClass::CharacterClass() {
	//_spells = memnew(Vector<Ref<Spell> >());
	_id = 0;
}

CharacterClass::~CharacterClass() {
	_spells.clear();
	_specs.clear();
	_auras.clear();
}
