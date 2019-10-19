#include "entity_data.h"

#include "../../ai/ai_action.h"
#include "../../data/aura.h"
#include "../../data/craft_recipe.h"
#include "../../data/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../entity.h"
#include "character_spec.h"
#include "vendor_item_data.h"

int EntityData::get_id() {
	return _id;
}
void EntityData::set_id(int value) {
	_id = value;
}

String EntityData::get_text_name() {
	return _text_name;
}
void EntityData::set_text_name(String value) {
	_text_name = value;
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

EntityEnums::EntityInteractionType EntityData::get_entity_interaction_type() {
	return _interaction_type;
}

void EntityData::set_entity_interaction_type(EntityEnums::EntityInteractionType value) {
	_interaction_type = value;
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

int EntityData::get_money() {
	return _money;
}
void EntityData::set_money(int value) {
	_money = value;
}

int EntityData::get_bag_size() {
	return _bag_size;
}
void EntityData::set_bag_size(int value) {
	_bag_size = value;
}

Ref<EntityClassData> EntityData::get_entity_class_data() {
	return _entity_class_data;
}
void EntityData::set_entity_class_data(Ref<EntityClassData> data) {
	_entity_class_data = data;
}

Ref<EquipmentData> EntityData::get_equipment_data() {
	return _equipment_data;
}
void EntityData::set_equipment_data(Ref<EquipmentData> data) {
	_equipment_data = data;
}

Ref<LootDataBase> EntityData::get_loot_db() const {
	return _lootdb;
}
void EntityData::set_loot_db(const Ref<LootDataBase> lootdb) {
	_lootdb = lootdb;
}

Ref<VendorItemData> EntityData::get_vendor_item_data() const {
	if (!_vendor_item_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_vendor_item_data();
	}

	return _vendor_item_data;
}
void EntityData::set_vendor_item_data(const Ref<VendorItemData> data) {
	_vendor_item_data = data;
}

Ref<ItemContainerData> EntityData::get_item_container_data() const {
	if (!_vendor_item_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_item_container_data();
	}

	return _item_container_data;
}
void EntityData::set_item_container_data(const Ref<ItemContainerData> data) {
	_item_container_data = data;
}

//Craft Recipes
int EntityData::get_num_craft_recipes() {
	return _craft_recipes.size();
}

Ref<CraftRecipe> EntityData::get_craft_recipe(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes[index];
}
void EntityData::set_craft_recipe(int index, Ref<CraftRecipe> craft_data) {
	ERR_FAIL_INDEX(index, _craft_recipes.size());

	_craft_recipes.set(index, craft_data);
}

Vector<Variant> EntityData::get_craft_recipes() {
	Vector<Variant> r;
	for (int i = 0; i < _craft_recipes.size(); i++) {
		r.push_back(_craft_recipes[i].get_ref_ptr());
	}
	return r;
}
void EntityData::set_craft_recipes(const Vector<Variant> &craft_datas) {
	_craft_recipes.clear();
	for (int i = 0; i < craft_datas.size(); i++) {
		Ref<CraftRecipe> craft_data = Ref<CraftRecipe>(craft_datas[i]);

		_craft_recipes.push_back(craft_data);
	}
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

String EntityData::generate_name() {
	if (has_method("_generate_name")) {
		return call("_generate_name");
	}

	return _text_name;
}

////    SETUP    ////

void EntityData::setup_resources(Entity *entity) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	if (_entity_class_data.is_valid())
		_entity_class_data->setup_resources(entity);

	if (has_method("_setup_resources"))
		call("_setup_resources", entity);
}

bool EntityData::cans_interact(Entity *entity) {
	ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);

	if (has_method("_cans_interact"))
		return call("_cans_interact", entity);

	return false;
}

bool EntityData::cans_interact_bind(Node *entity) {
	ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return cans_interact(e);
}

void EntityData::sinteract(Entity *entity) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	if (has_method("_sinteract"))
		call("_sinteract", entity);
}

void EntityData::sinteract_bind(Node *entity) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sinteract(e);
}

void EntityData::start_casting(int spell_id, Entity *caster, float spellScale) {
	if (_entity_class_data.is_valid())
		_entity_class_data->start_casting(spell_id, caster, spellScale);
}

void EntityData::son_before_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_cast(info);

	if (has_method("_son_before_cast"))
		call("_son_before_cast", info);
}

void EntityData::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_cast_target(info);

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", info);
}

void EntityData::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_cast_finished(info);

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", info);
}

void EntityData::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_cast_started(info);

	if (has_method("_son_cast_started"))
		call("_son_cast_started", info);
}

void EntityData::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_cast_failed(info);

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", info);
}

void EntityData::son_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_spell_cast_success(info);

	if (has_method("_son_spell_cast_success"))
		call("_son_spell_cast_success", info);
}

void EntityData::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_cast_finished_target(info);

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", info);
}

void EntityData::son_before_damage_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_damage_hit(data);

	if (has_method("_son_before_damage_hit"))
		call("_son_before_damage_hit", data);
}

void EntityData::son_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_hit(data);

	if (has_method("_son_hit"))
		call("_son_hit", data);
}

void EntityData::son_before_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_damage(data);

	if (has_method("_son_before_damage"))
		call("_son_before_damage", data);
}

void EntityData::son_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_damage_receive(data);

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", data);
}

void EntityData::son_dealt_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_dealt_damage(data);

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", data);
}

void EntityData::son_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_damage_dealt(data);

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", data);
}

void EntityData::son_before_heal_hit(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_heal_hit(data);

	if (has_method("_son_before_heal_hit"))
		call("_son_before_heal_hit", data);
}

void EntityData::son_before_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_heal(data);

	if (has_method("_son_before_heal"))
		call("_son_before_heal", data);
}

void EntityData::son_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_heal_receive(data);

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", data);
}

void EntityData::son_dealt_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_dealt_heal(data);

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", data);
}

void EntityData::son_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_heal_dealt(data);

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", data);
}

void EntityData::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_before_aura_applied(data);

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);
}

void EntityData::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->son_after_aura_applied(data);

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);
}

void EntityData::son_death(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_death(entity);

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
	if (_entity_class_data.is_valid())
		_entity_class_data->son_cooldown_added(cooldown);

	if (has_method("_son_cooldown_added"))
		call("_son_cooldown_added", cooldown);
}
void EntityData::son_cooldown_removed(Ref<Cooldown> cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_cooldown_removed(cooldown);

	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", cooldown);
}

void EntityData::son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_category_cooldown_added(category_cooldown);

	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", category_cooldown);
}
void EntityData::son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_category_cooldown_removed(category_cooldown);

	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", category_cooldown);
}

void EntityData::son_gcd_started(Entity *entity, float gcd) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_gcd_started(entity, gcd);

	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", entity, gcd);
}
void EntityData::son_gcd_finished(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_gcd_finished(entity);

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

void EntityData::son_xp_gained(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_xp_gained(entity, value);

	if (has_method("_son_xp_gained"))
		call("_son_xp_gained", entity, value);
}
void EntityData::son_xp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_xp_gained(e, value);
}

void EntityData::son_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_level_up(entity, value);

	if (has_method("_son_level_up"))
		call("_son_level_up", entity);
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

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cast_failed(info);

	if (has_method("_con_cast_failed"))
		call("_con_cast_failed", info);
}
void EntityData::con_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cast_started(info);

	if (has_method("_con_cast_started"))
		call("_con_cast_started", info);
}
void EntityData::con_cast_state_changed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cast_state_changed(info);

	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed", info);
}
void EntityData::con_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cast_finished(info);

	if (has_method("_con_cast_finished"))
		call("_con_cast_finished", info);
}
void EntityData::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_spell_cast_success(info);

	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success", info);
}

void EntityData::con_death(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (_entity_class_data.is_valid())
		_entity_class_data->con_death(entity);

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

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cooldown_added(cooldown);

	if (has_method("_con_cooldown_added"))
		call("_con_cooldown_added", cooldown);
}
void EntityData::con_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_cooldown_removed(cooldown);

	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed", cooldown);
}
void EntityData::con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_category_cooldown_added(category_cooldown);

	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added", category_cooldown);
}
void EntityData::con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_category_cooldown_removed(category_cooldown);

	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed", category_cooldown);
}

void EntityData::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_aura_added(data);

	if (has_method("_con_aura_added"))
		call("_con_aura_added", data);
}

void EntityData::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_aura_removed(data);

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", data);
}

void EntityData::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_aura_refresh(data);

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh", data);
}

void EntityData::con_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_damage_dealt(info);

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", info);
}

void EntityData::con_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_dealt_damage(info);

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", info);
}

void EntityData::con_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_heal_dealt(info);

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", info);
}

void EntityData::con_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->con_dealt_heal(info);

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", info);
}

void EntityData::con_gcd_started(Entity *entity, float gcd) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_gcd_started(entity, gcd);

	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", entity, gcd);
}
void EntityData::con_gcd_finished(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_gcd_finished(entity);

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

void EntityData::con_xp_gained(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_xp_gained(entity, value);

	if (has_method("_con_xp_gained"))
		call("_con_xp_gained", entity, value);
}
void EntityData::con_xp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_xp_gained(e, value);
}

void EntityData::con_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_level_up(entity, value);

	if (has_method("_con_level_up"))
		call("_con_level_up", entity);
}
void EntityData::con_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_level_up(e, value);
}

//Equipment

bool EntityData::should_deny_equip(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item) {
	if (_entity_class_data.is_valid())
		if (_entity_class_data->should_deny_equip(entity, equip_slot, item))
			return true;

	if (has_method("_should_deny_equip"))
		if (call("_should_deny_equip", entity, equip_slot, item))
			return true;

	return false;
}
bool EntityData::should_deny_equip_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return should_deny_equip(e, equip_slot, item);
}

void EntityData::son_equip_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_equip_success(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_son_equip_success"))
		call("_son_equip_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::son_equip_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_equip_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::son_equip_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->son_equip_fail(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_son_equip_fail"))
		call("_son_equip_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::son_equip_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	son_equip_fail(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::con_equip_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_equip_success(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_con_equip_success"))
		call("_con_equip_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::con_equip_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_equip_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::con_equip_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->con_equip_fail(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_con_equip_fail"))
		call("_con_equip_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::con_equip_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	con_equip_fail(e, equip_slot, item, old_item, bag_slot);
}

//AI

void EntityData::sai_follow(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_follow"))
		call("_sai_follow", entity);
	else if (_entity_class_data.is_valid())
		_entity_class_data->sai_follow(entity);
}
void EntityData::sai_rest(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_rest"))
		call("_sai_rest", entity);
	else if (_entity_class_data.is_valid())
		_entity_class_data->sai_rest(entity);
}
void EntityData::sai_regenerate(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_regenerate"))
		call("_sai_regenerate", entity);
	else if (_entity_class_data.is_valid())
		_entity_class_data->sai_regenerate(entity);
}
void EntityData::sai_attack(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_sai_attack"))
		call("_sai_attack", entity);
	else if (_entity_class_data.is_valid())
		_entity_class_data->sai_attack(entity);
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

EntityData::EntityData() {
	_id = 0;
	_money = 0;
	_bag_size = 0;

	_entity_type = EntityEnums::ENITIY_TYPE_NONE;
	_interaction_type = EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL;
	_immunity_flags = 0;
	_entity_flags = 0;
	_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
}
EntityData::~EntityData() {
	_craft_recipes.clear();
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
	ClassDB::bind_method(D_METHOD("son_spell_cast_success", "info"), &EntityData::son_spell_cast_success);

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
	BIND_VMETHOD(MethodInfo("_son_spell_cast_success", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

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

	//Equipment

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_should_deny_equip", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_son_equip_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_son_equip_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_con_equip_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_con_equip_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("should_deny_equip", "entity", "equip_slot", "item"), &EntityData::should_deny_equip_bind);

	ClassDB::bind_method(D_METHOD("son_equip_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::son_equip_success_bind);
	ClassDB::bind_method(D_METHOD("son_equip_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::son_equip_fail_bind);
	ClassDB::bind_method(D_METHOD("con_equip_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::con_equip_success_bind);
	ClassDB::bind_method(D_METHOD("con_equip_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::con_equip_fail_bind);

	//AI
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

	ClassDB::bind_method(D_METHOD("get_entity_interaction_type"), &EntityData::get_entity_interaction_type);
	ClassDB::bind_method(D_METHOD("set_entity_interaction_type", "value"), &EntityData::set_entity_interaction_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_interaction_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE), "set_entity_interaction_type", "get_entity_interaction_type");

	ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityData::get_entity_controller);
	ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityData::set_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

	ClassDB::bind_method(D_METHOD("get_text_name"), &EntityData::get_text_name);
	ClassDB::bind_method(D_METHOD("set_text_name", "value"), &EntityData::set_text_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_text_name", "get_text_name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "entity_name"), "set_text_name", "get_text_name"); //REMOVE

	ClassDB::bind_method(D_METHOD("get_money"), &EntityData::get_money);
	ClassDB::bind_method(D_METHOD("set_money", "value"), &EntityData::set_money);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "money"), "set_money", "get_money");

	ClassDB::bind_method(D_METHOD("get_bag_size"), &EntityData::get_bag_size);
	ClassDB::bind_method(D_METHOD("set_bag_size", "value"), &EntityData::set_bag_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bag_size"), "set_bag_size", "get_bag_size");

	ClassDB::bind_method(D_METHOD("get_entity_class_data"), &EntityData::get_entity_class_data);
	ClassDB::bind_method(D_METHOD("set_entity_class_data", "value"), &EntityData::set_entity_class_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_class_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityClassData"), "set_entity_class_data", "get_entity_class_data");

	// Loot DB
	ClassDB::bind_method(D_METHOD("get_loot_db"), &EntityData::get_loot_db);
	ClassDB::bind_method(D_METHOD("set_loot_db", "value"), &EntityData::set_loot_db);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "loot_db", PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase"), "set_loot_db", "get_loot_db");

	//EntityData
	ClassDB::bind_method(D_METHOD("get_vendor_item_data"), &EntityData::get_vendor_item_data);
	ClassDB::bind_method(D_METHOD("set_vendor_item_data", "value"), &EntityData::set_vendor_item_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "vendor_item_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_vendor_item_data", "get_vendor_item_data");

	//ItemContainerData
	ClassDB::bind_method(D_METHOD("get_item_container_data"), &EntityData::get_item_container_data);
	ClassDB::bind_method(D_METHOD("set_item_container_data", "value"), &EntityData::set_item_container_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_container_data", PROPERTY_HINT_RESOURCE_TYPE, "ItemContainerData"), "set_item_container_data", "get_item_container_data");

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

	//Crafting
	ClassDB::bind_method(D_METHOD("get_num_craft_recipes"), &EntityData::get_num_craft_recipes);

	ClassDB::bind_method(D_METHOD("get_craft_recipe", "index"), &EntityData::get_craft_recipe);
	ClassDB::bind_method(D_METHOD("set_craft_recipe", "index", "recipe"), &EntityData::set_craft_recipe);

	ClassDB::bind_method(D_METHOD("get_craft_recipes"), &EntityData::get_craft_recipes);
	ClassDB::bind_method(D_METHOD("set_craft_recipes", "recipe"), &EntityData::set_craft_recipes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "craft_recipes", PROPERTY_HINT_NONE, "17/17:CraftRecipe", PROPERTY_USAGE_DEFAULT, "CraftRecipe"), "set_craft_recipes", "get_craft_recipes");
}
