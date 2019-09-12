#include "entity_data.h"

#include "../../ai/ai_action.h"
#include "../../data/aura.h"
#include "../../data/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../entity.h"
#include "character_spec.h"
#include "vendor_item_data.h"
#include "container_item_data.h"

int EntityData::get_id() {
	return _id;
}
void EntityData::set_id(int value) {
	_id = value;
}

Ref<EntityData> EntityData::get_inherits() {
	return _inherits;
}
void EntityData::set_inherits(Ref<EntityData> value) {
	_inherits = value;
}

EntityEnums::EntityType EntityData::get_entity_type() {
	return _entity_type;
}
void EntityData::set_entity_type(EntityEnums::EntityType value) {
	_entity_type = value;
}

int EntityData::get_immunity_flags() {
	return _immunity_flags;
}
void EntityData::set_immunity_flags(int value) {
	_immunity_flags = value;
}

int EntityData::get_entity_flags() {
	return _entity_flags;
}
void EntityData::set_entity_flags(int value) {
	_entity_flags = value;
}

EntityEnums::EntityController EntityData::get_entity_controller() {
	return _entity_controller;
}
void EntityData::set_entity_controller(EntityEnums::EntityController value) {
	_entity_controller = value;
}

String EntityData::get_entity_name() {
	return _entity_name;
}
void EntityData::set_entity_name(String value) {
	_entity_name = value;
}

int EntityData::get_money() {
	return _money;
}
void EntityData::set_money(int value) {
	_money = value;
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

int EntityData::get_stat_points_per_level() {
	return _stat_points_per_level;
}
void EntityData::set_stat_points_per_level(int value) {
	_stat_points_per_level = value;
}

Ref<LootDataBase> EntityData::get_loot_db() const {
	return _lootdb;
}
void EntityData::set_loot_db(const Ref<LootDataBase> lootdb) {
	_lootdb = lootdb;
}

Ref<StatData> EntityData::get_stat_data() {
	if (!_stat_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_stat_data();
	}

	return _stat_data;
}

void EntityData::set_stat_data(Ref<StatData> value) {
	_stat_data = value;
}

////    SPECS    ////

int EntityData::get_num_specs() {
	if (_specs.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_specs();
	}

	return _specs.size();
}
void EntityData::set_num_specs(int value) {
	_specs.resize(value);
}

Ref<CharacterSpec> EntityData::get_spec(int index) const {
	if (_specs.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_spec(index);
	}

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
	if (_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_spells();
	}

	return _spells.size();
}
void EntityData::set_num_spells(int value) {
	_spells.resize(value);
}

Ref<Spell> EntityData::get_spell(int index) {
	if (_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_spell(index);
	}

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
	if (_auras.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_auras();
	}

	return _auras.size();
}
void EntityData::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> EntityData::get_aura(int index) {
	if (_auras.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_aura(index);
	}

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
	if (_ai_actions.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_ai_actions();
	}

	return _ai_actions.size();
}
void EntityData::set_num_ai_actions(int value) {
	_ai_actions.resize(value);
}

Ref<AIAction> EntityData::get_ai_action(int index) {
	if (_ai_actions.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_ai_action(index);
	}

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

////    VENDOR DATA    ////

int EntityData::get_num_vendor_datas() {
	if (_vendor_datas.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_vendor_datas();
	}

	return _vendor_datas.size();
}
void EntityData::set_num_vendor_datas(int value) {
	_vendor_datas.resize(value);
}

Ref<VendorItemData> EntityData::get_vendor_data(int index) {
	if (_vendor_datas.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_vendor_data(index);
	}

	ERR_FAIL_INDEX_V(index, _vendor_datas.size(), Ref<VendorItemData>());

	return _vendor_datas[index];
}
void EntityData::set_vendor_data(int index, Ref<VendorItemData> vendor_data) {
	ERR_FAIL_INDEX(index, _vendor_datas.size());

	_vendor_datas.set(index, vendor_data);
}

Vector<Variant> EntityData::get_vendor_datas() {
	Vector<Variant> r;
	for (int i = 0; i < _vendor_datas.size(); i++) {
		r.push_back(_vendor_datas[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_vendor_datas(const Vector<Variant> &vendor_datas) {
	_vendor_datas.clear();
	for (int i = 0; i < vendor_datas.size(); i++) {
		Ref<VendorItemData> vendor_data = Ref<VendorItemData>(vendor_datas[i]);

		_vendor_datas.push_back(vendor_data);
	}
}

////    Container Data    ////

int EntityData::get_num_container_datas() {
	if (_container_datas.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_container_datas();
	}

	return _container_datas.size();
}
void EntityData::set_num_container_datas(int value) {
	_container_datas.resize(value);
}

Ref<ContainerItemData> EntityData::get_container_data(int index) {
	if (_container_datas.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_container_data(index);
	}

	ERR_FAIL_INDEX_V(index, _container_datas.size(), Ref<ContainerItemData>());

	return _container_datas[index];
}
void EntityData::set_container_data(int index, Ref<ContainerItemData> container_data) {
	ERR_FAIL_INDEX(index, _container_datas.size());

	_container_datas.set(index, container_data);
}

Vector<Variant> EntityData::get_container_datas() {
	Vector<Variant> r;
	for (int i = 0; i < _container_datas.size(); i++) {
		r.push_back(_container_datas[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_container_datas(const Vector<Variant> &container_datas) {
	_container_datas.clear();
	for (int i = 0; i < container_datas.size(); i++) {
		Ref<ContainerItemData> container_data = Ref<ContainerItemData>(container_datas[i]);

		_container_datas.push_back(container_data);
	}
}

////    SETUP    ////

void EntityData::setup_resources(Entity *entity) {
	if (has_method("_setup_resources"))
		call("_setup_resources", entity);
	else if (_inherits.is_valid())
		_inherits->setup_resources(entity);
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

bool EntityData::cans_interact(Entity* entity) {
    ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);
    
    if (has_method("_cans_interact"))
        return call("_cans_interact");

    return false;
}

bool EntityData::cans_interact_bind(Node* entity) {
    ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return cans_interact(e);
}

void EntityData::sinteract(Entity* entity) {
    ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
    
    if (has_method("_sinteract"))
        call("_sinteract");
}

void EntityData::sinteract_bind(Node* entity) {
    ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sinteract(e);
}

void EntityData::start_casting(int spell_id, Entity *caster, float spellScale) {
	if (_spells.size() == 0 && _inherits.is_valid()) {
		_inherits->start_casting(spell_id, caster, spellScale);
		return;
	}

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
	else if (_inherits.is_valid())
		_inherits->son_before_cast(info);
}

void EntityData::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", info);
	else if (_inherits.is_valid())
		_inherits->son_before_cast_target(info);
}

void EntityData::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", info);
	else if (_inherits.is_valid())
		_inherits->son_cast_finished(info);
}

void EntityData::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_started"))
		call("_son_cast_started", info);
	else if (_inherits.is_valid())
		_inherits->son_cast_started(info);
}

void EntityData::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", info);
	else if (_inherits.is_valid())
		_inherits->son_cast_failed(info);
}

void EntityData::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", info);
	else if (_inherits.is_valid())
		_inherits->son_cast_finished_target(info);
}

void EntityData::son_before_damage_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage_hit"))
		call("_son_before_damage_hit", data);
	else if (_inherits.is_valid())
		_inherits->son_before_damage_hit(data);
}

void EntityData::son_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_hit"))
		call("_son_hit", data);
	else if (_inherits.is_valid())
		_inherits->son_hit(data);
}

void EntityData::son_before_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_damage"))
		call("_son_before_damage", data);
	else if (_inherits.is_valid())
		_inherits->son_before_damage(data);
}

void EntityData::son_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", data);
	else if (_inherits.is_valid())
		_inherits->son_damage_receive(data);
}

void EntityData::son_dealt_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", data);
	else if (_inherits.is_valid())
		_inherits->son_dealt_damage(data);
}

void EntityData::son_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", data);
	else if (_inherits.is_valid())
		_inherits->son_damage_dealt(data);
}

void EntityData::son_before_heal_hit(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal_hit"))
		call("_son_before_heal_hit", data);
	else if (_inherits.is_valid())
		_inherits->son_before_heal_hit(data);
}

void EntityData::son_before_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_heal"))
		call("_son_before_heal", data);
	else if (_inherits.is_valid())
		_inherits->son_before_heal(data);
}

void EntityData::son_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", data);
	else if (_inherits.is_valid())
		_inherits->son_heal_receive(data);
}

void EntityData::son_dealt_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", data);
	else if (_inherits.is_valid())
		_inherits->son_dealt_heal(data);
}

void EntityData::son_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", data);
	else if (_inherits.is_valid())
		_inherits->son_heal_dealt(data);
}

void EntityData::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);
	else if (_inherits.is_valid())
		_inherits->son_before_aura_applied(data);
}

void EntityData::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);
	else if (_inherits.is_valid())
		_inherits->son_after_aura_applied(data);
}

void EntityData::son_death(Entity *entity) {
	if (has_method("_son_death"))
		call("_son_death", entity);
	else if (_inherits.is_valid())
		_inherits->son_death(entity);
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
	else if (_inherits.is_valid())
		_inherits->son_cooldown_added(cooldown);
}
void EntityData::son_cooldown_removed(Ref<Cooldown> cooldown) {
	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", cooldown);
	else if (_inherits.is_valid())
		_inherits->son_cooldown_removed(cooldown);
}

void EntityData::son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", category_cooldown);
	else if (_inherits.is_valid())
		_inherits->son_category_cooldown_added(category_cooldown);
}
void EntityData::son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", category_cooldown);
	else if (_inherits.is_valid())
		_inherits->son_category_cooldown_removed(category_cooldown);
}

void EntityData::son_gcd_started(Entity *entity, float gcd) {
	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", entity, gcd);
	else if (_inherits.is_valid())
		_inherits->son_gcd_started(entity, gcd);
}
void EntityData::son_gcd_finished(Entity *entity) {
	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished", entity);
	else if (_inherits.is_valid())
		_inherits->son_gcd_finished(entity);
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


void EntityData::son_xp_gained(Entity *entity, int value) {
	if (has_method("_son_xp_gained"))
		call("_son_xp_gained", entity, value);
	else if (_inherits.is_valid())
		_inherits->son_xp_gained(entity, value);
}
void EntityData::son_xp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_xp_gained(e, value);
}

void EntityData::son_level_up(Entity *entity, int value) {
	if (has_method("_son_level_up"))
		call("_son_level_up", entity);
	else if (_inherits.is_valid())
		_inherits->son_level_up(entity, value);
}
void EntityData::son_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_level_up(e, value);
}


//Clientside Event Handlers
void EntityData::con_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_cast_failed"))
		call("_con_cast_failed", info);
	else if (_inherits.is_valid())
		_inherits->con_cast_failed(info);
}
void EntityData::con_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_cast_started"))
		call("_con_cast_started", info);
	else if (_inherits.is_valid())
		_inherits->con_cast_started(info);
}
void EntityData::con_cast_state_changed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed", info);
	else if (_inherits.is_valid())
		_inherits->con_cast_state_changed(info);
}
void EntityData::con_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_cast_finished"))
		call("_con_cast_finished", info);
	else if (_inherits.is_valid())
		_inherits->con_cast_finished(info);
}
void EntityData::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success", info);
	else if (_inherits.is_valid())
		_inherits->con_spell_cast_success(info);
}

void EntityData::con_death(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_con_death"))
		call("_con_death", entity);
	else if (_inherits.is_valid())
		_inherits->con_death(entity);
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
	else if (_inherits.is_valid())
		_inherits->con_cooldown_added(cooldown);
}
void EntityData::con_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed", cooldown);
	else if (_inherits.is_valid())
		_inherits->con_cooldown_removed(cooldown);
}
void EntityData::con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added", category_cooldown);
	else if (_inherits.is_valid())
		_inherits->con_category_cooldown_added(category_cooldown);
}
void EntityData::con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed", category_cooldown);
	else if (_inherits.is_valid())
		_inherits->con_category_cooldown_removed(category_cooldown);
}

void EntityData::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_added"))
		call("_con_aura_added", data);
	else if (_inherits.is_valid())
		_inherits->con_aura_added(data);
}

void EntityData::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", data);
	else if (_inherits.is_valid())
		_inherits->con_aura_removed(data);
}

void EntityData::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh", data);
	else if (_inherits.is_valid())
		_inherits->con_aura_refresh(data);
}

void EntityData::con_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", info);
	else if (_inherits.is_valid())
		_inherits->con_damage_dealt(info);
}

void EntityData::con_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", info);
	else if (_inherits.is_valid())
		_inherits->con_dealt_damage(info);
}

void EntityData::con_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", info);
	else if (_inherits.is_valid())
		_inherits->con_heal_dealt(info);
}

void EntityData::con_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", info);
	else if (_inherits.is_valid())
		_inherits->con_dealt_heal(info);
}

void EntityData::con_gcd_started(Entity *entity, float gcd) {
	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", entity, gcd);
	else if (_inherits.is_valid())
		_inherits->con_gcd_started(entity, gcd);
}
void EntityData::con_gcd_finished(Entity *entity) {
	if (has_method("_con_gcd_finished"))
		call("_con_gcd_finished", entity);
	else if (_inherits.is_valid())
		_inherits->con_gcd_finished(entity);
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

void EntityData::con_xp_gained(Entity *entity, int value) {
	if (has_method("_con_xp_gained"))
		call("_con_xp_gained", entity, value);
	else if (_inherits.is_valid())
		_inherits->con_xp_gained(entity, value);
}
void EntityData::con_xp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_xp_gained(e, value);
}

void EntityData::con_level_up(Entity *entity, int value) {
	if (has_method("_con_level_up"))
		call("_con_level_up", entity);
	else if (_inherits.is_valid())
		_inherits->con_level_up(entity, value);
}
void EntityData::con_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_level_up(e, value);
}

void EntityData::sai_follow(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_follow"))
		call("_sai_follow", entity);
	else if (_inherits.is_valid())
		_inherits->sai_follow(entity);
}
void EntityData::sai_rest(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_rest"))
		call("_sai_rest", entity);
	else if (_inherits.is_valid())
		_inherits->sai_rest(entity);
}
void EntityData::sai_regenerate(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_regenerate"))
		call("_sai_regenerate", entity);
	else if (_inherits.is_valid())
		_inherits->sai_regenerate(entity);
}
void EntityData::sai_attack(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_attack"))
		call("_sai_attack", entity);
	else if (_inherits.is_valid())
		_inherits->sai_attack(entity);
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

String EntityData::generate_name() {
	if (has_method("_generate_name")) {
		return call("_generate_name");
	}

	return _entity_name;
}

void EntityData::_bind_methods() {
    //Interactions
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_cans_interact", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
    BIND_VMETHOD(MethodInfo("_sinteract", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
    
    ClassDB::bind_method(D_METHOD("cans_interact", "entity"), &EntityData::cans_interact_bind);
    ClassDB::bind_method(D_METHOD("sinteract", "entity"), &EntityData::sinteract_bind);
    
	//EventHandlers
	ClassDB::bind_method(D_METHOD("son_before_cast", "info"), &EntityData::son_before_cast);
	ClassDB::bind_method(D_METHOD("son_before_cast_target", "info"), &EntityData::son_before_cast_target);
	ClassDB::bind_method(D_METHOD("son_cast_started", "info"), &EntityData::son_cast_started);
	ClassDB::bind_method(D_METHOD("son_cast_failed", "info"), &EntityData::son_cast_failed);
	ClassDB::bind_method(D_METHOD("son_cast_finished", "info"), &EntityData::son_cast_finished);
	ClassDB::bind_method(D_METHOD("son_cast_finished_target", "info"), &EntityData::son_cast_finished_target);

    ClassDB::bind_method(D_METHOD("son_before_damage_hit", "data"), &EntityData::son_before_damage_hit);
	ClassDB::bind_method(D_METHOD("son_hit", "data"), &EntityData::son_hit);
	ClassDB::bind_method(D_METHOD("son_before_damage", "data"), &EntityData::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_damage_receive", "data"), &EntityData::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_damage", "data"), &EntityData::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "data"), &EntityData::son_damage_dealt);

    ClassDB::bind_method(D_METHOD("son_before_heal_hit", "data"), &EntityData::son_before_heal_hit);
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

	ClassDB::bind_method(D_METHOD("son_xp_gained", "entity", "value"), &EntityData::son_xp_gained_bind);
	ClassDB::bind_method(D_METHOD("son_level_up", "entity", "value"), &EntityData::son_level_up_bind);

	BIND_VMETHOD(MethodInfo("_son_before_cast", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_cast_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

    BIND_VMETHOD(MethodInfo("_son_before_damage_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_receive", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_damage", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_dealt", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

    BIND_VMETHOD(MethodInfo("_son_before_heal_hit", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
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

	BIND_VMETHOD(MethodInfo("_son_xp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_son_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

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

	ClassDB::bind_method(D_METHOD("con_xp_gained", "entity", "value"), &EntityData::con_xp_gained_bind);
	ClassDB::bind_method(D_METHOD("con_level_up", "entity", "value"), &EntityData::con_level_up_bind);

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

	BIND_VMETHOD(MethodInfo("_con_xp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_con_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	ClassDB::bind_method(D_METHOD("sai_follow", "entity"), &EntityData::sai_follow_bind);
	ClassDB::bind_method(D_METHOD("sai_rest", "entity"), &EntityData::sai_rest_bind);
	ClassDB::bind_method(D_METHOD("sai_regenerate", "entity"), &EntityData::sai_regenerate_bind);
	ClassDB::bind_method(D_METHOD("sai_attack", "entity"), &EntityData::sai_attack_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &EntityData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_entity_type"), &EntityData::get_entity_type);
	ClassDB::bind_method(D_METHOD("set_entity_type", "value"), &EntityData::set_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_TYPES), "set_entity_type", "get_entity_type");

    ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityData::get_entity_controller);
	ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityData::set_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

	ClassDB::bind_method(D_METHOD("get_entity_name"), &EntityData::get_entity_name);
	ClassDB::bind_method(D_METHOD("set_entity_name", "value"), &EntityData::set_entity_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_name"), "set_entity_name", "get_entity_name");
    
    ClassDB::bind_method(D_METHOD("get_money"), &EntityData::get_money);
	ClassDB::bind_method(D_METHOD("set_money", "value"), &EntityData::set_money);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "money"), "set_money", "get_money");

	ClassDB::bind_method(D_METHOD("get_inherits"), &EntityData::get_inherits);
	ClassDB::bind_method(D_METHOD("set_inherits", "value"), &EntityData::set_inherits);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "inherits", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_inherits", "get_inherits");

	ClassDB::bind_method(D_METHOD("get_icon"), &EntityData::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &EntityData::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &EntityData::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &EntityData::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_player_resource_type"), &EntityData::get_player_resource_type);
	ClassDB::bind_method(D_METHOD("set_player_resource_type", "value"), &EntityData::set_player_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "player_resource_type", PROPERTY_HINT_ENUM, "None, Rage, Mana, Energy, Time Anomaly"), "set_player_resource_type", "get_player_resource_type");

	ClassDB::bind_method(D_METHOD("get_stat_points_per_level"), &EntityData::get_stat_points_per_level);
	ClassDB::bind_method(D_METHOD("set_stat_points_per_level", "value"), &EntityData::set_stat_points_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_points_per_level"), "set_stat_points_per_level", "get_stat_points_per_level");

	// Loot DB
	ClassDB::bind_method(D_METHOD("get_loot_db"), &EntityData::get_loot_db);
	ClassDB::bind_method(D_METHOD("set_loot_db", "value"), &EntityData::set_loot_db);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "loot_db", PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase"), "set_loot_db", "get_loot_db");

	ClassDB::bind_method(D_METHOD("generate_name"), &EntityData::generate_name);
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "name"), "_generate_name"));

    ADD_GROUP("Immunities", "immunity");
    ClassDB::bind_method(D_METHOD("get_immunity_flags"), &EntityData::get_immunity_flags);
	ClassDB::bind_method(D_METHOD("set_immunity_flags", "value"), &EntityData::set_immunity_flags);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "immunity_flags", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_IMMUNITY_FLAGS), "set_immunity_flags", "get_immunity_flags");
    
    ADD_GROUP("Entity Flags", "entity_flags");
    ClassDB::bind_method(D_METHOD("get_entity_flags"), &EntityData::get_entity_flags);
	ClassDB::bind_method(D_METHOD("set_entity_flags", "value"), &EntityData::set_entity_flags);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_flags", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_FLAGS), "set_entity_flags", "get_entity_flags");
    
	////    Specs    ////
    ADD_GROUP("Specs", "specs");
	ClassDB::bind_method(D_METHOD("get_num_specs"), &EntityData::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &EntityData::set_num_specs);

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &EntityData::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &EntityData::set_spec);

	ClassDB::bind_method(D_METHOD("get_specs"), &EntityData::get_specs);
	ClassDB::bind_method(D_METHOD("set_specs", "specs"), &EntityData::set_specs);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "specs", PROPERTY_HINT_NONE, "17/17:CharacterSpec", PROPERTY_USAGE_DEFAULT, "CharacterSpec"), "set_specs", "get_specs");

	////    Spell    ////
    ADD_GROUP("Spells", "spells");
	ClassDB::bind_method(D_METHOD("get_num_spells"), &EntityData::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &EntityData::set_num_spells);

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &EntityData::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &EntityData::set_spell);

	ClassDB::bind_method(D_METHOD("get_spells"), &EntityData::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &EntityData::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	////    AURAS    ////
    ADD_GROUP("Auras", "auras");
	ClassDB::bind_method(D_METHOD("get_num_auras"), &EntityData::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &EntityData::set_num_auras);

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &EntityData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &EntityData::set_aura);

	ClassDB::bind_method(D_METHOD("get_auras"), &EntityData::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &EntityData::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	////    AI ACTIONS    ////
    ADD_GROUP("Ai_actions", "ai_actions");
	ClassDB::bind_method(D_METHOD("get_num_ai_actions"), &EntityData::get_num_ai_actions);
	ClassDB::bind_method(D_METHOD("set_num_ai_actions", "value"), &EntityData::set_num_ai_actions);

	ClassDB::bind_method(D_METHOD("get_ai_action", "index"), &EntityData::get_ai_action);
	ClassDB::bind_method(D_METHOD("set_ai_action", "index", "action"), &EntityData::set_ai_action);

	ClassDB::bind_method(D_METHOD("get_ai_actions"), &EntityData::get_ai_actions);
	ClassDB::bind_method(D_METHOD("set_ai_actions", "auras"), &EntityData::set_ai_actions);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ai_actions", PROPERTY_HINT_NONE, "17/17:AIAction", PROPERTY_USAGE_DEFAULT, "AIAction"), "set_ai_actions", "get_ai_actions");
    
    ////    Vendor data    ////
    ADD_GROUP("Vendor Data", "vendor_datas");
	ClassDB::bind_method(D_METHOD("get_num_vendor_datas"), &EntityData::get_num_vendor_datas);
	ClassDB::bind_method(D_METHOD("set_num_vendor_datas", "value"), &EntityData::set_num_vendor_datas);

	ClassDB::bind_method(D_METHOD("get_vendor_data", "index"), &EntityData::get_vendor_data);
	ClassDB::bind_method(D_METHOD("set_vendor_data", "index", "vendor_data"), &EntityData::set_vendor_data);

	ClassDB::bind_method(D_METHOD("get_vendor_datas"), &EntityData::get_vendor_datas);
	ClassDB::bind_method(D_METHOD("set_vendor_datas", "vendor_datas"), &EntityData::set_vendor_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "vendor_datas", PROPERTY_HINT_NONE, "17/17:VendorItemData", PROPERTY_USAGE_DEFAULT, "VendorItemData"), "set_vendor_datas", "get_vendor_datas");
    
    ////    Container data    ////
    ADD_GROUP("Container Data", "container_datas");
	ClassDB::bind_method(D_METHOD("get_num_container_datas"), &EntityData::get_num_container_datas);
	ClassDB::bind_method(D_METHOD("set_num_container_datas", "value"), &EntityData::set_num_container_datas);

	ClassDB::bind_method(D_METHOD("get_container_data", "index"), &EntityData::get_container_data);
	ClassDB::bind_method(D_METHOD("set_container_data", "index", "container_data"), &EntityData::set_container_data);

	ClassDB::bind_method(D_METHOD("get_container_datas"), &EntityData::get_container_datas);
	ClassDB::bind_method(D_METHOD("set_container_datas", "container_datas"), &EntityData::set_container_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "container_datas", PROPERTY_HINT_NONE, "17/17:ContainerItemData", PROPERTY_USAGE_DEFAULT, "ContainerItemData"), "set_container_datas", "get_container_datas");
}

EntityData::EntityData() {
	_id = 0;
	_player_resource_type = 0;
    _money = 0;
    
    _entity_type = EntityEnums::ENITIY_TYPE_NONE;
    _immunity_flags = 0;
    _entity_flags = 0;
    _entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;

	_player_resource_type  = 0;
	_stat_points_per_level = 5;
}

EntityData::~EntityData() {
	_spells.clear();
	_specs.clear();
	_auras.clear();
	_ai_actions.clear();
    _vendor_datas.clear();
	_container_datas.clear();
}
