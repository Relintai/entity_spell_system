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

#include "entity_data.h"

#include "../../data/auras/aura.h"
#include "../../data/items/craft_recipe.h"
#include "../../data/spells/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../entity.h"
#include "character_spec.h"
#include "vendor_item_data.h"

#include "../../defines.h"

int EntityData::get_id() const {
	return _id;
}
void EntityData::set_id(int value) {
	_id = value;
}

String EntityData::get_text_description() const {
	return _text_description;
}
void EntityData::set_text_description(String value) {
	_text_description = value;
}

Ref<EntityData> EntityData::get_inherits() const {
	return _inherits;
}
void EntityData::set_inherits(const Ref<EntityData> &value) {
	_inherits = value;
}

int EntityData::get_entity_type() const {
	return _entity_type;
}
void EntityData::set_entity_type(const int value) {
	_entity_type = value;
}

EntityEnums::EntityInteractionType EntityData::get_entity_interaction_type() const {
	return _interaction_type;
}

void EntityData::set_entity_interaction_type(EntityEnums::EntityInteractionType value) {
	_interaction_type = value;
}

bool EntityData::get_is_playable() const {
	return _is_playable;
}
void EntityData::set_is_playable(const bool value) {
	_is_playable = value;
}

int EntityData::get_immunity_flags() const {
	return _immunity_flags;
}
void EntityData::set_immunity_flags(const int value) {
	_immunity_flags = value;
}

int EntityData::get_entity_flags() const {
	return _entity_flags;
}
void EntityData::set_entity_flags(const int value) {
	_entity_flags = value;
}

EntityEnums::EntityController EntityData::get_entity_controller() const {
	return _entity_controller;
}
void EntityData::set_entity_controller(EntityEnums::EntityController value) {
	_entity_controller = value;
}

int EntityData::get_money() const {
	return _money;
}
void EntityData::set_money(const int value) {
	_money = value;
}

int EntityData::get_bag_size() const {
	return _bag_size;
}
void EntityData::set_bag_size(const int value) {
	_bag_size = value;
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

Ref<EntitySpeciesData> EntityData::get_entity_species_data() const {
	return _entity_species_data;
}
void EntityData::set_entity_species_data(const Ref<EntitySpeciesData> &value) {
	_entity_species_data = value;
}

Ref<EntityClassData> EntityData::get_entity_class_data() const {
	return _entity_class_data;
}
void EntityData::set_entity_class_data(const Ref<EntityClassData> &data) {
	_entity_class_data = data;
}

Ref<EquipmentData> EntityData::get_equipment_data() const {
	return _equipment_data;
}
void EntityData::set_equipment_data(const Ref<EquipmentData> &data) {
	_equipment_data = data;
}

Ref<EntityAI> EntityData::get_ai() const {
	return _ai;
}
void EntityData::set_ai(const Ref<EntityAI> &ai) {
	_ai = ai;
}
Ref<EntityAI> EntityData::get_ai_instance() {
	return call("_get_ai_instance");
}
Ref<EntityAI> EntityData::_get_ai_instance() {
	if (_ai.is_valid()) {
		return _ai->duplicate();
	}

	Ref<EntityClassData> ecd = get_entity_class_data();

	if (ecd.is_valid()) {
		return ecd->get_ai_instance();
	}

	Ref<EntityAI> ai;
	ai.instance();
	return ai;
}

Ref<AIFormation> EntityData::get_formation() const {
	return _formation;
}
void EntityData::set_formation(const Ref<AIFormation> &data) {
	_formation = data;
}

Ref<LootDataBase> EntityData::get_loot_db() const {
	return _lootdb;
}
void EntityData::set_loot_db(const Ref<LootDataBase> &lootdb) {
	_lootdb = lootdb;
}

Ref<VendorItemData> EntityData::get_vendor_item_data() const {
	if (!_vendor_item_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_vendor_item_data();
	}

	return _vendor_item_data;
}
void EntityData::set_vendor_item_data(const Ref<VendorItemData> &data) {
	_vendor_item_data = data;
}

Ref<VendorItemData> EntityData::get_spell_train_data() const {
	if (!_spell_train_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_spell_train_data();
	}

	return _spell_train_data;
}
void EntityData::set_spell_train_data(const Ref<VendorItemData> &data) {
	_spell_train_data = data;
}

Ref<ItemContainerData> EntityData::get_item_container_data() const {
	if (!_vendor_item_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_item_container_data();
	}

	return _item_container_data;
}
void EntityData::set_item_container_data(const Ref<ItemContainerData> &data) {
	_item_container_data = data;
}

//Craft Recipes
int EntityData::get_num_craft_recipes() const {
	return _craft_recipes.size();
}

Ref<CraftRecipe> EntityData::get_craft_recipe(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes[index];
}
void EntityData::set_craft_recipe(int index, const Ref<CraftRecipe> &craft_data) {
	ERR_FAIL_INDEX(index, _craft_recipes.size());

	_craft_recipes.set(index, craft_data);
}

Vector<Variant> EntityData::get_craft_recipes() const {
	VARIANT_ARRAY_GET(_craft_recipes);
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

	return get_name();
}

////    SETUP    ////

void EntityData::setup_resources(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	if (_entity_class_data.is_valid())
		_entity_class_data->setup_resources(entity);

	if (has_method("_setup_resources"))
		call("_setup_resources", entity);
}

bool EntityData::cans_interact(Entity *entity) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(entity), false);

	if (has_method("_cans_interact"))
		return call("_cans_interact", entity);

	return false;
}

bool EntityData::cans_interact_bind(Node *entity) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return cans_interact(e);
}

void EntityData::sinteract(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	if (has_method("_sinteract"))
		call("_sinteract", entity);
}

void EntityData::sinteract_bind(Node *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	sinteract(e);
}

void EntityData::start_casting(int spell_id, Entity *caster, float spellScale) {
	if (_entity_class_data.is_valid())
		_entity_class_data->start_casting(spell_id, caster, spellScale);
}

void EntityData::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_saura(what, data);

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);
}
void EntityData::notification_sheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sheal(what, info);

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, info);
}
void EntityData::notification_scast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scast(what, info);

	if (has_method("_notification_scast"))
		call("_notification_scast", what, info);
}
void EntityData::notification_sdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sdamage(what, info);

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, info);
}

void EntityData::notification_sdeath(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sdeath(entity);

	if (has_method("_notification_sdeath"))
		call("_notification_sdeath", entity);
}

void EntityData::notification_sdeath_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sdeath(e);
}

void EntityData::notification_scooldown_added(Ref<Cooldown> cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scooldown_added(cooldown);

	if (has_method("_notification_scooldown_added"))
		call("_notification_scooldown_added", cooldown);
}
void EntityData::notification_scooldown_removed(Ref<Cooldown> cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scooldown_removed(cooldown);

	if (has_method("_notification_scooldown_removed"))
		call("_notification_scooldown_removed", cooldown);
}

void EntityData::notification_scategory_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scategory_cooldown_added(category_cooldown);

	if (has_method("_notification_scategory_cooldown_added"))
		call("_notification_scategory_cooldown_added", category_cooldown);
}
void EntityData::notification_scategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scategory_cooldown_removed(category_cooldown);

	if (has_method("_notification_scategory_cooldown_removed"))
		call("_notification_scategory_cooldown_removed", category_cooldown);
}

void EntityData::notification_sgcd_started(Entity *entity, float gcd) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sgcd_started(entity, gcd);

	if (has_method("_notification_sgcd_started"))
		call("_notification_sgcd_started", entity, gcd);
}
void EntityData::notification_sgcd_finished(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sgcd_finished(entity);

	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", entity);
}
void EntityData::notification_sgcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_started(e, gcd);
}
void EntityData::notification_sgcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_finished(e);
}

void EntityData::notification_sxp_gained(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sxp_gained(entity, value);

	if (has_method("_notification_sxp_gained"))
		call("_notification_sxp_gained", entity, value);
}
void EntityData::notification_sxp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sxp_gained(e, value);
}

void EntityData::notification_sclass_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sclass_level_up(entity, value);

	if (has_method("_notification_sclass_level_up"))
		call("_notification_sclass_level_up", entity);
}
void EntityData::notification_sclass_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sclass_level_up(e, value);
}

void EntityData::notification_scharacter_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_scharacter_level_up(entity, value);

	if (has_method("_notification_scharacter_level_up"))
		call("_notification_scharacter_level_up", entity);
}
void EntityData::notification_scharacter_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_scharacter_level_up(e, value);
}

void EntityData::notification_sentity_resource_added(Ref<EntityResource> resource) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_sentity_resource_added(resource);

	if (has_method("_notification_sentity_resource_added"))
		call("_notification_sentity_resource_added", resource);
}

void EntityData::notification_sentity_resource_removed(Ref<EntityResource> resource) {
	if (_entity_class_data.is_valid()) {
		_entity_class_data->notification_sentity_resource_removed(resource);
	}

	if (has_method("_notification_sentity_resource_removed"))
		call("_notification_sentity_resource_removed", resource);
}

//Clientside Event Handlers
void EntityData::notification_caura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_caura(what, data);

	if (has_method("_notification_caura"))
		call("_notification_caura", what, data);
}
void EntityData::notification_cheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cheal(what, info);

	if (has_method("_notification_cheal"))
		call("_notification_cheal", what, info);
}
void EntityData::notification_ccast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccast(what, info);

	if (has_method("_notification_ccast"))
		call("_notification_ccast", what, info);
}
void EntityData::notification_cdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cdamage(what, info);

	if (has_method("_notification_cdamage"))
		call("_notification_cdamage", what, info);
}

void EntityData::notification_cdeath(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cdeath(entity);

	if (has_method("_notification_cdeath"))
		call("_notification_cdeath", entity);
}

void EntityData::notification_cdeath_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cdeath(e);
}

void EntityData::notification_ccooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccooldown_added(cooldown);

	if (has_method("_notification_ccooldown_added"))
		call("_notification_ccooldown_added", cooldown);
}
void EntityData::notification_ccooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccooldown_removed(cooldown);

	if (has_method("_notification_ccooldown_removed"))
		call("_notification_ccooldown_removed", cooldown);
}
void EntityData::notification_ccategory_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccategory_cooldown_added(category_cooldown);

	if (has_method("_notification_ccategory_cooldown_added"))
		call("_notification_ccategory_cooldown_added", category_cooldown);
}
void EntityData::notification_ccategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccategory_cooldown_removed(category_cooldown);

	if (has_method("_notification_ccategory_cooldown_removed"))
		call("_notification_ccategory_cooldown_removed", category_cooldown);
}

void EntityData::notification_cgcd_started(Entity *entity, float gcd) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cgcd_started(entity, gcd);

	if (has_method("_notification_cgcd_started"))
		call("_notification_cgcd_started", entity, gcd);
}
void EntityData::notification_cgcd_finished(Entity *entity) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cgcd_finished(entity);

	if (has_method("_notification_cgcd_finished"))
		call("_notification_cgcd_finished", entity);
}
void EntityData::notification_cgcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cgcd_started(e, gcd);
}
void EntityData::notification_cgcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cgcd_finished(e);
}

void EntityData::notification_cxp_gained(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cxp_gained(entity, value);

	if (has_method("_notification_cxp_gained"))
		call("_notification_cxp_gained", entity, value);
}
void EntityData::notification_cxp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cxp_gained(e, value);
}

void EntityData::notification_cclass_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_cclass_level_up(entity, value);

	if (has_method("_notification_cclass_level_up"))
		call("_notification_cclass_level_up", entity);
}
void EntityData::notification_cclass_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cclass_level_up(e, value);
}

void EntityData::notification_ccharacter_level_up(Entity *entity, int value) {
	if (_entity_class_data.is_valid())
		_entity_class_data->notification_ccharacter_level_up(entity, value);

	if (has_method("_notification_ccharacter_level_up"))
		call("_notification_ccharacter_level_up", entity);
}
void EntityData::notification_ccharacter_level_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_ccharacter_level_up(e, value);
}

void EntityData::notification_centity_resource_added(Ref<EntityResource> resource) {
	if (_entity_class_data.is_valid()) {
		_entity_class_data->notification_centity_resource_added(resource);
	}

	if (has_method("_notification_centity_resource_added"))
		call("_notification_centity_resource_added", resource);
}

void EntityData::notification_centity_resource_removed(Ref<EntityResource> resource) {
	if (_entity_class_data.is_valid()) {
		_entity_class_data->notification_centity_resource_removed(resource);
	}

	if (has_method("_notification_centity_resource_removed"))
		call("_notification_centity_resource_removed", resource);
}

//Equipment

bool EntityData::equip_should_deny(Entity *entity, int equip_slot, Ref<ItemInstance> item) {
	if (_entity_class_data.is_valid())
		if (_entity_class_data->equip_should_deny(entity, equip_slot, item))
			return true;

	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", entity, equip_slot, item))
			return true;

	return false;
}
bool EntityData::equip_should_deny_bind(Node *entity, int equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return equip_should_deny(e, equip_slot, item);
}

void EntityData::equip_son_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->equip_son_success(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_equip_son_success"))
		call("_equip_son_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::equip_son_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::equip_son_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->equip_son_fail(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::equip_son_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_fail(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::equip_con_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->equip_con_success(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_equip_con_success"))
		call("_equip_con_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::equip_con_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityData::equip_con_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_entity_class_data.is_valid())
		_entity_class_data->equip_con_fail(entity, equip_slot, item, old_item, bag_slot);

	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityData::equip_con_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_fail(e, equip_slot, item, old_item, bag_slot);
}

EntityData::EntityData() {
	_id = 0;
	_money = 0;
	_bag_size = 0;
	_is_playable = false;

	_entity_type = 0;
	_interaction_type = EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL;
	_immunity_flags = 0;
	_entity_flags = 0;
	_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
}
EntityData::~EntityData() {
	_inherits.unref();

	_entity_class_data.unref();
	_entity_species_data.unref();
	_equipment_data.unref();

	_ai.unref();
	_formation.unref();

	_lootdb.unref();
	_vendor_item_data.unref();
	_spell_train_data.unref();
	_item_container_data.unref();

	_craft_recipes.clear();
}

void EntityData::_validate_property(PropertyInfo &property) const {
	if (property.name == "entity_type") {
		property.hint_string = ESS::get_instance()->entity_types_get();
	}
}

void EntityData::_bind_methods() {
	//Interactions
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_cans_interact", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sinteract", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("cans_interact", "entity"), &EntityData::cans_interact_bind);
	ClassDB::bind_method(D_METHOD("sinteract", "entity"), &EntityData::sinteract_bind);

	//EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &EntityData::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "info"), &EntityData::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "info"), &EntityData::notification_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "info"), &EntityData::notification_sdamage);

	BIND_VMETHOD(MethodInfo("_notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_caura", "what", "data"), &EntityData::notification_caura);
	ClassDB::bind_method(D_METHOD("notification_cheal", "what", "info"), &EntityData::notification_cheal);
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "info"), &EntityData::notification_ccast);
	ClassDB::bind_method(D_METHOD("notification_cdamage", "what", "info"), &EntityData::notification_cdamage);

	ClassDB::bind_method(D_METHOD("notification_sdeath", "data"), &EntityData::notification_sdeath_bind);

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "cooldown"), &EntityData::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "cooldown"), &EntityData::notification_scooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "category_cooldown"), &EntityData::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "category_cooldown"), &EntityData::notification_scategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started", "entity", "gcd"), &EntityData::notification_sgcd_started_bind);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished", "entity"), &EntityData::notification_sgcd_finished_bind);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "entity", "value"), &EntityData::notification_sxp_gained_bind);
	ClassDB::bind_method(D_METHOD("notification_sclass_level_up", "entity", "value"), &EntityData::notification_sclass_level_up_bind);
	ClassDB::bind_method(D_METHOD("notification_scharacter_level_up", "entity", "value"), &EntityData::notification_scharacter_level_up_bind);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "resource"), &EntityData::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "resource"), &EntityData::notification_sentity_resource_removed);

	BIND_VMETHOD(MethodInfo("_notification_sdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_sai_follow", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_rest", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_regenerate", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sai_attack", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_scooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_notification_scooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));

	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_notification_sgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_sgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_sclass_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scharacter_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	BIND_VMETHOD(MethodInfo("_setup_resources", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	//Clientside Event Handlers
	ClassDB::bind_method(D_METHOD("notification_cdeath", "data"), &EntityData::notification_cdeath_bind);

	ClassDB::bind_method(D_METHOD("notification_ccooldown_added", "cooldown"), &EntityData::notification_ccooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccooldown_removed", "cooldown"), &EntityData::notification_ccooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_added", "cooldown"), &EntityData::notification_ccategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_removed", "cooldown"), &EntityData::notification_ccategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_cgcd_started", "entity", "gcd"), &EntityData::notification_cgcd_started_bind);
	ClassDB::bind_method(D_METHOD("notification_cgcd_finished", "entity"), &EntityData::notification_cgcd_finished_bind);

	ClassDB::bind_method(D_METHOD("notification_cxp_gained", "entity", "value"), &EntityData::notification_cxp_gained_bind);
	ClassDB::bind_method(D_METHOD("notification_cclass_level_up", "entity", "value"), &EntityData::notification_cclass_level_up_bind);
	ClassDB::bind_method(D_METHOD("notification_ccharacter_level_up", "entity", "value"), &EntityData::notification_ccharacter_level_up_bind);

	ClassDB::bind_method(D_METHOD("notification_centity_resource_added", "resource"), &EntityData::notification_centity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_centity_resource_removed", "resource"), &EntityData::notification_centity_resource_removed);

	BIND_VMETHOD(MethodInfo("_notification_cdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_ccooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_notification_ccooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_notification_ccategory_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_notification_ccategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_notification_cgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_cgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_cxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_cclass_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_ccharacter_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_centity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_centity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	//Equipment

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_equip_should_deny", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_equip_son_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_son_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("equip_should_deny", "entity", "equip_slot", "item"), &EntityData::equip_should_deny_bind);

	ClassDB::bind_method(D_METHOD("equip_son_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::equip_son_success_bind);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::equip_son_fail_bind);
	ClassDB::bind_method(D_METHOD("equip_con_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::equip_con_success_bind);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityData::equip_con_fail_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &EntityData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_entity_type"), &EntityData::get_entity_type);
	ClassDB::bind_method(D_METHOD("set_entity_type", "value"), &EntityData::set_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_type", PROPERTY_HINT_ENUM, ""), "set_entity_type", "get_entity_type");

	ClassDB::bind_method(D_METHOD("get_entity_interaction_type"), &EntityData::get_entity_interaction_type);
	ClassDB::bind_method(D_METHOD("set_entity_interaction_type", "value"), &EntityData::set_entity_interaction_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_interaction_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE), "set_entity_interaction_type", "get_entity_interaction_type");

	ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityData::get_entity_controller);
	ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityData::set_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

	ClassDB::bind_method(D_METHOD("get_is_playable"), &EntityData::get_is_playable);
	ClassDB::bind_method(D_METHOD("set_is_playable", "value"), &EntityData::set_is_playable);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_playable"), "set_is_playable", "get_is_playable");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntityData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntityData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_money"), &EntityData::get_money);
	ClassDB::bind_method(D_METHOD("set_money", "value"), &EntityData::set_money);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "money"), "set_money", "get_money");

	ClassDB::bind_method(D_METHOD("get_bag_size"), &EntityData::get_bag_size);
	ClassDB::bind_method(D_METHOD("set_bag_size", "value"), &EntityData::set_bag_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bag_size"), "set_bag_size", "get_bag_size");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &EntityData::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &EntityData::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_entity_species_data"), &EntityData::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("set_entity_species_data", "value"), &EntityData::set_entity_species_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_species_data", PROPERTY_HINT_RESOURCE_TYPE, "EntitySpeciesData"), "set_entity_species_data", "get_entity_species_data");

	ClassDB::bind_method(D_METHOD("get_entity_class_data"), &EntityData::get_entity_class_data);
	ClassDB::bind_method(D_METHOD("set_entity_class_data", "value"), &EntityData::set_entity_class_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_class_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityClassData"), "set_entity_class_data", "get_entity_class_data");

	ClassDB::bind_method(D_METHOD("get_equipment_data"), &EntityData::get_equipment_data);
	ClassDB::bind_method(D_METHOD("set_equipment_data", "value"), &EntityData::set_equipment_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "equipment_data", PROPERTY_HINT_RESOURCE_TYPE, "EquipmentData"), "set_equipment_data", "get_equipment_data");

	//AI
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "ret", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "_get_ai_instance"));

	ClassDB::bind_method(D_METHOD("get_ai"), &EntityData::get_ai);
	ClassDB::bind_method(D_METHOD("set_ai", "value"), &EntityData::set_ai);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ai", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "set_ai", "get_ai");

	ClassDB::bind_method(D_METHOD("get_ai_instance"), &EntityData::get_ai_instance);
	ClassDB::bind_method(D_METHOD("_get_ai_instance"), &EntityData::_get_ai_instance);

	ClassDB::bind_method(D_METHOD("get_formation"), &EntityData::get_formation);
	ClassDB::bind_method(D_METHOD("set_formation", "value"), &EntityData::set_formation);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "formation", PROPERTY_HINT_RESOURCE_TYPE, "AIFormation"), "set_formation", "get_formation");

	// Loot DB
	ClassDB::bind_method(D_METHOD("get_loot_db"), &EntityData::get_loot_db);
	ClassDB::bind_method(D_METHOD("set_loot_db", "value"), &EntityData::set_loot_db);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "loot_db", PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase"), "set_loot_db", "get_loot_db");

	//Vendor
	ClassDB::bind_method(D_METHOD("get_vendor_item_data"), &EntityData::get_vendor_item_data);
	ClassDB::bind_method(D_METHOD("set_vendor_item_data", "value"), &EntityData::set_vendor_item_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "vendor_item_data", PROPERTY_HINT_RESOURCE_TYPE, "VendorItemData"), "set_vendor_item_data", "get_vendor_item_data");

	ClassDB::bind_method(D_METHOD("get_spell_train_data"), &EntityData::get_spell_train_data);
	ClassDB::bind_method(D_METHOD("set_spell_train_data", "value"), &EntityData::set_spell_train_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell_train_data", PROPERTY_HINT_RESOURCE_TYPE, "VendorItemData"), "set_spell_train_data", "get_spell_train_data");

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
