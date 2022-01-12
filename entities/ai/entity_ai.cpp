/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "entity_ai.h"

#include "../entity.h"

#include "../../infos/spell_cast_info.h"

#include "../../data/items/item_instance.h"
#include "../../entities/auras/aura_data.h"
#include "../../entities/resources/entity_resource.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../defines.h"

bool EntityAI::get_enabled() {
	return _enabled;
}
void EntityAI::set_enabled(bool value) {
	_enabled = value;
}

void EntityAI::set_owner(Entity *entity) {
	if (entity == _owner)
		return;

	_owner = entity;

	call("_on_set_owner");
}

void EntityAI::set_owner_bind(Node *entity) {
	if (!entity) {
		return;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return;
	}

	return set_owner(e);
}

Entity *EntityAI::get_owner() {
	return _owner;
}

Vector<int> EntityAI::get_spec_distribution() {
	return _spec_distribution;
}
void EntityAI::set_spec_distribution(Vector<int> data) {
	_spec_distribution = data;
}

int EntityAI::get_spec_variance() {
	return _spec_variance;
}
void EntityAI::set_spec_variance(int value) {
	_spec_variance = value;
}

EntityEnums::AIStates EntityAI::get_state() {
	return _state;
}
void EntityAI::set_state(EntityEnums::AIStates state) {
	_state = state;
}

EntityEnums::AIStates EntityAI::get_force_state() {
	return _force_state;
}
void EntityAI::set_force_state(EntityEnums::AIStates state) {
	_force_state = state;
}

void EntityAI::set_editor_description(const String &p_editor_description) {
	set_meta("_editor_description_", p_editor_description);
}
String EntityAI::get_editor_description() const {
	if (has_meta("_editor_description_")) {
		return get_meta("_editor_description_");
	} else {
		return "";
	}
}

void EntityAI::update(float delta) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(_owner));

	if (has_method("_update"))
		call("_update", delta);
}
void EntityAI::pet_update(float delta) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(_owner));

	if (has_method("_pet_update"))
		call("_pet_update", delta);
}

void EntityAI::move(float delta) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(_owner));

	if (has_method("_move"))
		call("_move", delta);
}
void EntityAI::pet_move(float delta) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(_owner));

	if (has_method("_pet_move"))
		call("_pet_move", delta);
}

void EntityAI::_on_set_owner() {
}

void EntityAI::start_casting(int spell_id, Entity *caster, float spellScale) {
	//if (_entity_class_data.is_valid())
	//	_entity_class_data->start_casting(spell_id, caster, spellScale);
}

void EntityAI::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);
}
void EntityAI::notification_sheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, info);
}
void EntityAI::notification_scast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_scast"))
		call("_notification_scast", what, info);
}
void EntityAI::notification_sdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, info);
}

void EntityAI::notification_sdeath(Entity *entity) {
	if (has_method("_notification_sdeath"))
		call("_notification_sdeath", entity);
}

void EntityAI::notification_sdeath_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sdeath(e);
}

void EntityAI::notification_scooldown_added(int id, float value) {
	if (has_method("_notification_scooldown_added"))
		call("_notification_scooldown_added", id, value);
}
void EntityAI::notification_scooldown_removed(int id, float value) {
	if (has_method("_notification_scooldown_removed"))
		call("_notification_scooldown_removed", id, value);
}

void EntityAI::notification_scategory_cooldown_added(int id, float value) {
	if (has_method("_notification_scategory_cooldown_added"))
		call("_notification_scategory_cooldown_added", id, value);
}
void EntityAI::notification_scategory_cooldown_removed(int id, float value) {
	if (has_method("_notification_scategory_cooldown_removed"))
		call("_notification_scategory_cooldown_removed", id, value);
}

void EntityAI::notification_sgcd_started(Entity *entity, float gcd) {
	if (has_method("_notification_sgcd_started"))
		call("_notification_sgcd_started", entity, gcd);
}
void EntityAI::notification_sgcd_finished(Entity *entity) {
	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", entity);
}
void EntityAI::notification_sgcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_started(e, gcd);
}
void EntityAI::notification_sgcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_finished(e);
}

void EntityAI::notification_sxp_gained(Entity *entity, int value) {
	if (has_method("_notification_sxp_gained"))
		call("_notification_sxp_gained", entity, value);
}
void EntityAI::notification_sxp_gained_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sxp_gained(e, value);
}

void EntityAI::notification_slevel_up(Entity *entity, int value) {
	if (has_method("_notification_slevel_up"))
		call("_notification_slevel_up", entity);
}
void EntityAI::notification_slevel_up_bind(Node *entity, int value) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_slevel_up(e, value);
}

void EntityAI::notification_sentity_resource_added(Ref<EntityResource> resource) {
	if (has_method("_notification_sentity_resource_added"))
		call("_notification_sentity_resource_added", resource);
}

void EntityAI::notification_sentity_resource_removed(Ref<EntityResource> resource) {
	if (has_method("_notification_sentity_resource_removed"))
		call("_notification_sentity_resource_removed", resource);
}

//Equipment

bool EntityAI::equip_should_deny(Entity *entity, int equip_slot, Ref<ItemInstance> item) {
	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", entity, equip_slot, item))
			return true;

	return false;
}
bool EntityAI::equip_should_deny_bind(Node *entity, int equip_slot, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(entity), false);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return equip_should_deny(e, equip_slot, item);
}

void EntityAI::equip_son_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_son_success"))
		call("_equip_son_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityAI::equip_son_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityAI::equip_son_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityAI::equip_son_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_fail(e, equip_slot, item, old_item, bag_slot);
}

void EntityAI::equip_con_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_con_success"))
		call("_equip_con_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityAI::equip_con_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityAI::equip_con_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityAI::equip_con_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_fail(e, equip_slot, item, old_item, bag_slot);
}

EntityAI::EntityAI() {
	_enabled = true;
	_owner = NULL;

	_spec_variance = 0;

	_state = EntityEnums::AI_STATE_OFF;
	_force_state = EntityEnums::AI_STATE_OFF;
}

EntityAI::~EntityAI() {
	_spec_distribution.clear();
}

void EntityAI::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_on_set_owner"));

	BIND_VMETHOD(MethodInfo("_update", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_pet_update", PropertyInfo(Variant::REAL, "delta")));

	BIND_VMETHOD(MethodInfo("_move", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_pet_move", PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("get_enabled"), &EntityAI::get_enabled);
	ClassDB::bind_method(D_METHOD("set_enabled", "value"), &EntityAI::set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "get_enabled"), "set_enabled", "get_enabled");

	ClassDB::bind_method(D_METHOD("get_owner"), &EntityAI::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "entity"), &EntityAI::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_spec_distribution"), &EntityAI::get_spec_distribution);
	ClassDB::bind_method(D_METHOD("set_spec_distribution", "value"), &EntityAI::set_spec_distribution);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spec_distribution"), "set_spec_distribution", "get_spec_distribution");

	ClassDB::bind_method(D_METHOD("get_spec_variance"), &EntityAI::get_spec_variance);
	ClassDB::bind_method(D_METHOD("set_spec_variance", "value"), &EntityAI::set_spec_variance);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spec_variance"), "set_spec_variance", "get_spec_variance");

	ClassDB::bind_method(D_METHOD("get_state"), &EntityAI::get_state);
	ClassDB::bind_method(D_METHOD("set_state", "state"), &EntityAI::set_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES), "set_state", "get_state");

	ClassDB::bind_method(D_METHOD("get_force_state"), &EntityAI::get_force_state);
	ClassDB::bind_method(D_METHOD("set_force_state", "state"), &EntityAI::set_force_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "force_state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES), "set_force_state", "get_force_state");

	ClassDB::bind_method(D_METHOD("set_editor_description", "editor_description"), &EntityAI::set_editor_description);
	ClassDB::bind_method(D_METHOD("get_editor_description"), &EntityAI::get_editor_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "editor_description", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_INTERNAL), "set_editor_description", "get_editor_description");

	ClassDB::bind_method(D_METHOD("update", "delta"), &EntityAI::update);
	ClassDB::bind_method(D_METHOD("pet_update", "delta"), &EntityAI::pet_update);

	ClassDB::bind_method(D_METHOD("move", "delta"), &EntityAI::move);
	ClassDB::bind_method(D_METHOD("pet_move", "delta"), &EntityAI::pet_move);

	ClassDB::bind_method(D_METHOD("_on_set_owner"), &EntityAI::_on_set_owner);

	//EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &EntityAI::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "info"), &EntityAI::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "info"), &EntityAI::notification_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "info"), &EntityAI::notification_sdamage);

	ClassDB::bind_method(D_METHOD("notification_sdeath", "data"), &EntityAI::notification_sdeath_bind);

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "cooldown"), &EntityAI::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "cooldown"), &EntityAI::notification_scooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "category_cooldown"), &EntityAI::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "category_cooldown"), &EntityAI::notification_scategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started", "entity", "gcd"), &EntityAI::notification_sgcd_started_bind);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished", "entity"), &EntityAI::notification_sgcd_finished_bind);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "entity", "value"), &EntityAI::notification_sxp_gained_bind);
	ClassDB::bind_method(D_METHOD("notification_slevel_up", "entity", "value"), &EntityAI::notification_slevel_up_bind);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "resource"), &EntityAI::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "resource"), &EntityAI::notification_sentity_resource_removed);

	BIND_VMETHOD(MethodInfo("_notification_sdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_scooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_sgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_slevel_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	//Equipment

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_equip_should_deny", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_equip_son_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_son_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("equip_should_deny", "entity", "equip_slot", "item"), &EntityAI::equip_should_deny_bind);

	ClassDB::bind_method(D_METHOD("equip_son_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityAI::equip_son_success_bind);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityAI::equip_son_fail_bind);
	ClassDB::bind_method(D_METHOD("equip_con_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityAI::equip_con_success_bind);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityAI::equip_con_fail_bind);
}
