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

int CharacterClass::get_num_spells() {
	return _num_spells;
}

void CharacterClass::set_num_spells(int value) {
	_num_spells = value;
}

int CharacterClass::get_current_spell_page() {
	return _current_spell_page;
}

void CharacterClass::set_current_spell_page(int value) {
	if (value < 0 || value > (int)(_num_spells / ITEMS_PER_PAGE)) {
		return;
	}

	_current_spell_page = value;
}

Ref<Spell> CharacterClass::get_spell(int id) {
	ERR_FAIL_INDEX_V(id, MAX_SPELLS, Ref<Spell>());

	return _spells[id];
}

void CharacterClass::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, MAX_SPELLS);

	_spells[index] = Ref<Spell>(spell);
}

int CharacterClass::get_num_specs() {
	return _num_specs;
}

void CharacterClass::set_num_specs(int value) {
	_num_specs = value;
}

Ref<CharacterSpec> CharacterClass::get_spec(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_SPECS, Ref<CharacterSpec>());

	return _specs[index];
}

void CharacterClass::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, MAX_SPECS);

	_specs[index] = Ref<CharacterSpec>(spec);
}

Ref<Aura> CharacterClass::get_aura(int index) {
	ERR_FAIL_INDEX_V(index, MAX_AURAS, Ref<Aura>());

	return _auras[index];
}
void CharacterClass::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, MAX_AURAS);

	_auras[index] = aura;
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
	for (int i = 0; i < MAX_SPELLS; i++) {
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

void CharacterClass::_validate_property(PropertyInfo &property) const {

	String prop = property.name;
	if (prop.begins_with("Spell_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _num_spells || frame < ITEMS_PER_PAGE * _current_spell_page || frame > ITEMS_PER_PAGE * (_current_spell_page + 1)) {
			property.usage = 0;
		}
	} else if (prop.begins_with("Spec_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _num_specs) {
			property.usage = 0;
		}
	} else if (prop.begins_with("current_spell_page")) {
		if (_num_spells <= ITEMS_PER_PAGE) {
			property.usage = 0;
		}
	}
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
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_specs", PROPERTY_HINT_RANGE, "0," + itos(MAX_SPECS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_num_specs", "get_num_specs");

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &CharacterClass::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &CharacterClass::set_spec);

	for (int i = 0; i < MAX_SPECS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Spec_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "CharacterSpec", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_spec", "get_spec", i);
	}

	////    AURAS    ////
	
	ClassDB::bind_method(D_METHOD("get_aura", "index"), &CharacterClass::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &CharacterClass::set_aura);

	ADD_GROUP("Auras", "Aura");
	for (int i = 0; i < MAX_AURAS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Aura_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Aura", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura", "get_aura", i);
	}

	////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &CharacterClass::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &CharacterClass::set_num_spells);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_spells", PROPERTY_HINT_RANGE, "0," + itos(MAX_SPELLS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_num_spells", "get_num_spells");

	ClassDB::bind_method(D_METHOD("get_current_spell_page"), &CharacterClass::get_current_spell_page);
	ClassDB::bind_method(D_METHOD("set_current_spell_page", "value"), &CharacterClass::set_current_spell_page);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_spell_page", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_current_spell_page", "get_current_spell_page");

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &CharacterClass::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &CharacterClass::set_spell);

	for (int i = 0; i < MAX_SPELLS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Spell_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_spell", "get_spell", i);
	}

	BIND_CONSTANT(MAX_SPELLS);
	BIND_CONSTANT(MAX_SPECS);
	BIND_CONSTANT(MAX_AURAS);
}

CharacterClass::CharacterClass() {
	//_spells = memnew(Vector<Ref<Spell> >());
	_id = 0;

	_num_specs = 0;
	_num_spells = 0;
	_current_spell_page = 0;
}

CharacterClass::~CharacterClass() {
	//memdelete(_spells);

	//for (int i = 0; i < MAX_SPELLS; ++i) {
		//_spells[i] = Ref<Spell>(NULL);
	//}
}
