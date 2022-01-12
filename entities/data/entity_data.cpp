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

#include "entity_data.h"

#include "../../data/spells/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../entity.h"
#include "character_spec.h"

#include "../../data/species/entity_species_data.h"
#include "../../data/species/species_instance.h"

#include "../../singletons/ess.h"

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

Ref<SpeciesInstance> EntityData::get_species_instance() const {
	return _species_instance;
}
void EntityData::set_species_instance(const Ref<SpeciesInstance> &value) {
	_species_instance = value;
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

Ref<LootDataBase> EntityData::get_loot_db() const {
	return _lootdb;
}
void EntityData::set_loot_db(const Ref<LootDataBase> &lootdb) {
	_lootdb = lootdb;
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

EntityData::EntityData() {
	_id = 0;
	_money = 0;
	_bag_size = 0;
	_is_playable = false;

	_interaction_type = EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL;
	_immunity_flags = 0;
	_entity_flags = 0;
}
EntityData::~EntityData() {
	_entity_class_data.unref();
	_entity_species_data.unref();
	_equipment_data.unref();
	_species_instance.unref();

	_ai.unref();

	_lootdb.unref();
}

void EntityData::_validate_property(PropertyInfo &property) const {
	if (property.name == "entity_type") {
		property.hint_string = ESS::get_singleton()->entity_types_get();
	}
}

void EntityData::_bind_methods() {
	//Interactions
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_cans_interact", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_sinteract", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("cans_interact", "entity"), &EntityData::cans_interact_bind);
	ClassDB::bind_method(D_METHOD("sinteract", "entity"), &EntityData::sinteract_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &EntityData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_entity_interaction_type"), &EntityData::get_entity_interaction_type);
	ClassDB::bind_method(D_METHOD("set_entity_interaction_type", "value"), &EntityData::set_entity_interaction_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_interaction_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE), "set_entity_interaction_type", "get_entity_interaction_type");

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

	ClassDB::bind_method(D_METHOD("get_entity_species_data"), &EntityData::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("set_entity_species_data", "value"), &EntityData::set_entity_species_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_species_data", PROPERTY_HINT_RESOURCE_TYPE, "EntitySpeciesData"), "set_entity_species_data", "get_entity_species_data");

	ClassDB::bind_method(D_METHOD("get_entity_class_data"), &EntityData::get_entity_class_data);
	ClassDB::bind_method(D_METHOD("set_entity_class_data", "value"), &EntityData::set_entity_class_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_class_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityClassData"), "set_entity_class_data", "get_entity_class_data");

	ClassDB::bind_method(D_METHOD("get_equipment_data"), &EntityData::get_equipment_data);
	ClassDB::bind_method(D_METHOD("set_equipment_data", "value"), &EntityData::set_equipment_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "equipment_data", PROPERTY_HINT_RESOURCE_TYPE, "EquipmentData"), "set_equipment_data", "get_equipment_data");

	ClassDB::bind_method(D_METHOD("get_species_instance"), &EntityData::get_species_instance);
	ClassDB::bind_method(D_METHOD("set_species_instance", "value"), &EntityData::set_species_instance);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_instance", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesInstance"), "set_species_instance", "get_species_instance");

	//AI
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "ret", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "_get_ai_instance"));

	ClassDB::bind_method(D_METHOD("get_ai"), &EntityData::get_ai);
	ClassDB::bind_method(D_METHOD("set_ai", "value"), &EntityData::set_ai);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ai", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "set_ai", "get_ai");

	ClassDB::bind_method(D_METHOD("get_ai_instance"), &EntityData::get_ai_instance);
	ClassDB::bind_method(D_METHOD("_get_ai_instance"), &EntityData::_get_ai_instance);

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
}
