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

#include "entity_class_data.h"

#include "../../data/auras/aura.h"
#include "../../data/items/item_instance.h"
#include "../../data/spells/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../ai/entity_ai.h"
#include "../entity.h"
#include "character_spec.h"

#include "../../defines.h"

int EntityClassData::get_id() {
	return _id;
}
void EntityClassData::set_id(int value) {
	_id = value;
}

String EntityClassData::get_text_description() {
	return _text_description;
}
void EntityClassData::set_text_description(String value) {
	_text_description = value;
}

Ref<Texture> EntityClassData::get_icon() {
	return _icon;
}
void EntityClassData::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

int EntityClassData::get_spell_points_per_level() {
	return _spell_points_per_level;
}
void EntityClassData::set_spell_points_per_level(int value) {
	_spell_points_per_level = value;
}

EntityEnums::EntityClassPlaystyleType EntityClassData::get_playstyle_type() {
	return _playstyle_type;
}
void EntityClassData::set_playstyle_type(EntityEnums::EntityClassPlaystyleType playstyle_type) {
	_playstyle_type = playstyle_type;
}

////    Entity Resources    ////

int EntityClassData::get_num_entity_resources() {
	return _entity_resources.size();
}
void EntityClassData::set_num_entity_resources(int value) {
	_entity_resources.resize(value);
}

Ref<EntityResourceData> EntityClassData::get_entity_resource(int index) const {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResourceData>());

	return _entity_resources[index];
}
void EntityClassData::set_entity_resource(int index, Ref<EntityResourceData> entity_resource) {
	ERR_FAIL_INDEX(index, _entity_resources.size());

	_entity_resources.set(index, Ref<EntityResourceData>(entity_resource));
}

Vector<Variant> EntityClassData::get_entity_resources() {
	VARIANT_ARRAY_GET(_entity_resources);
}
void EntityClassData::set_entity_resources(const Vector<Variant> &entity_resources) {
	_entity_resources.clear();
	for (int i = 0; i < entity_resources.size(); i++) {
		Ref<EntityResourceData> entity_resource = Ref<EntityResourceData>(entity_resources[i]);

		_entity_resources.push_back(entity_resource);
	}
}

////    SPECS    ////

int EntityClassData::get_num_specs() {
	return _specs.size();
}
void EntityClassData::set_num_specs(int value) {
	_specs.resize(value);
}

Ref<CharacterSpec> EntityClassData::get_spec(int index) const {
	ERR_FAIL_INDEX_V(index, _specs.size(), Ref<CharacterSpec>());

	return _specs[index];
}
void EntityClassData::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, _specs.size());

	_specs.set(index, Ref<CharacterSpec>(spec));
}

Vector<Variant> EntityClassData::get_specs() {
	VARIANT_ARRAY_GET(_specs);
}
void EntityClassData::set_specs(const Vector<Variant> &specs) {
	_specs.clear();
	for (int i = 0; i < specs.size(); i++) {
		Ref<CharacterSpec> spec = Ref<CharacterSpec>(specs[i]);

		_specs.push_back(spec);
	}
}

////    SPELLS    ////

int EntityClassData::get_num_spells() {
	return _spells.size();
}
void EntityClassData::set_num_spells(int value) {
	_spells.resize(value);
}

Ref<Spell> EntityClassData::get_spell(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells[index];
}
void EntityClassData::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> EntityClassData::get_spells() {
	VARIANT_ARRAY_GET(_spells);
}
void EntityClassData::set_spells(const Vector<Variant> &spells) {
	_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_spells.push_back(spell);
	}
}

////    Start Spells    ////

int EntityClassData::get_num_start_spells() {
	return _start_spells.size();
}
void EntityClassData::set_num_start_spells(int value) {
	_start_spells.resize(value);
}

Ref<Spell> EntityClassData::get_start_spell(int index) {
	ERR_FAIL_INDEX_V(index, _start_spells.size(), Ref<Spell>());

	return _start_spells[index];
}
void EntityClassData::set_start_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _start_spells.size());

	_start_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> EntityClassData::get_start_spells() {
	VARIANT_ARRAY_GET(_start_spells);
}
void EntityClassData::set_start_spells(const Vector<Variant> &spells) {
	_start_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_start_spells.push_back(spell);
	}
}

////    AURAS    ////

int EntityClassData::get_num_auras() {
	return _auras.size();
}
void EntityClassData::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> EntityClassData::get_aura(int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras[index];
}
void EntityClassData::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}

Vector<Variant> EntityClassData::get_auras() {
	VARIANT_ARRAY_GET(_auras);
}
void EntityClassData::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(auras[i]);

		_auras.push_back(aura);
	}
}

////    AI ACTIONS    ////

int EntityClassData::get_num_ais() {
	return _ais.size();
}
void EntityClassData::set_num_ais(int value) {
	_ais.resize(value);
}

Ref<EntityAI> EntityClassData::get_ai(int index) {
	ERR_FAIL_INDEX_V(index, _ais.size(), Ref<EntityAI>());

	return _ais[index];
}
void EntityClassData::set_ai(int index, Ref<EntityAI> ai) {
	ERR_FAIL_INDEX(index, _ais.size());

	_ais.set(index, ai);
}

Vector<Variant> EntityClassData::get_ais() {
	VARIANT_ARRAY_GET(_ais);
}
void EntityClassData::set_ais(const Vector<Variant> &ais) {
	_ais.clear();
	for (int i = 0; i < ais.size(); i++) {
		Ref<EntityAI> ai = Ref<EntityAI>(ais[i]);

		_ais.push_back(ai);
	}
}

Ref<EntityAI> EntityClassData::get_ai_instance() {
	return call("_get_ai_instance");
}
Ref<EntityAI> EntityClassData::_get_ai_instance() {
	if (_ais.size() > 0) {
		Ref<EntityAI> ai = _ais.get(Math::rand() % _ais.size());

		if (ai.is_valid()) {
			return ai->duplicate();
		}
	}

	Ref<EntityAI> ai;
	ai.instance();
	return ai;
}

////    SETUP    ////

void EntityClassData::setup_resources(Entity *entity) {
	call("_setup_resources", entity);
}

void EntityClassData::_setup_resources(Node *entity) {
	Entity *ent = Object::cast_to<Entity>(entity);

	for (int i = 0; i < _entity_resources.size(); ++i) {
		Ref<EntityResourceData> res = _entity_resources.get(i);

		if (res.is_valid()) {
			ent->resource_adds(res->get_entity_resource_instance());
		}
	}
}

EntityClassData::EntityClassData() {
	_id = 0;
	_spell_points_per_level = 1;
	_playstyle_type = EntityEnums::ENTITY_CLASS_PLAYSTYLE_TYPE_MELEE;
}

EntityClassData::~EntityClassData() {
	_spells.clear();
	_specs.clear();
	_auras.clear();
	_ais.clear();
}

void EntityClassData::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_setup_resources", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("get_id"), &EntityClassData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityClassData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntityClassData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntityClassData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_icon"), &EntityClassData::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &EntityClassData::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_spell_points_per_level"), &EntityClassData::get_spell_points_per_level);
	ClassDB::bind_method(D_METHOD("set_spell_points_per_level", "value"), &EntityClassData::set_spell_points_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_points_per_level"), "set_spell_points_per_level", "get_spell_points_per_level");

	ClassDB::bind_method(D_METHOD("get_playstyle_type"), &EntityClassData::get_playstyle_type);
	ClassDB::bind_method(D_METHOD("set_playstyle_type", "value"), &EntityClassData::set_playstyle_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "playstyle_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_PLAYSTYLE_TYPE), "set_playstyle_type", "get_playstyle_type");

	////    Entity Resources    ////
	ClassDB::bind_method(D_METHOD("get_num_entity_resources"), &EntityClassData::get_num_entity_resources);
	ClassDB::bind_method(D_METHOD("set_num_entity_resources", "value"), &EntityClassData::set_num_entity_resources);

	ClassDB::bind_method(D_METHOD("get_entity_resource", "index"), &EntityClassData::get_entity_resource);
	ClassDB::bind_method(D_METHOD("set_entity_resource", "index", "entity_resource"), &EntityClassData::set_entity_resource);

	ClassDB::bind_method(D_METHOD("get_entity_resources"), &EntityClassData::get_entity_resources);
	ClassDB::bind_method(D_METHOD("set_entity_resources", "entity_resources"), &EntityClassData::set_entity_resources);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_resources", PROPERTY_HINT_NONE, "17/17:EntityResourceData", PROPERTY_USAGE_DEFAULT, "EntityResourceData"), "set_entity_resources", "get_entity_resources");

	ClassDB::bind_method(D_METHOD("_setup_resources", "entity"), &EntityClassData::_setup_resources);

	////    Specs    ////
	ClassDB::bind_method(D_METHOD("get_num_specs"), &EntityClassData::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &EntityClassData::set_num_specs);

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &EntityClassData::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &EntityClassData::set_spec);

	ClassDB::bind_method(D_METHOD("get_specs"), &EntityClassData::get_specs);
	ClassDB::bind_method(D_METHOD("set_specs", "specs"), &EntityClassData::set_specs);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "specs", PROPERTY_HINT_NONE, "17/17:CharacterSpec", PROPERTY_USAGE_DEFAULT, "CharacterSpec"), "set_specs", "get_specs");

	////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &EntityClassData::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &EntityClassData::set_num_spells);

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &EntityClassData::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &EntityClassData::set_spell);

	ClassDB::bind_method(D_METHOD("get_spells"), &EntityClassData::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &EntityClassData::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	////    Start Spells    ////
	ClassDB::bind_method(D_METHOD("get_num_start_spells"), &EntityClassData::get_num_start_spells);
	ClassDB::bind_method(D_METHOD("set_num_start_spells", "value"), &EntityClassData::set_num_start_spells);

	ClassDB::bind_method(D_METHOD("get_start_spell", "index"), &EntityClassData::get_start_spell);
	ClassDB::bind_method(D_METHOD("set_start_spell", "index", "spell"), &EntityClassData::set_start_spell);

	ClassDB::bind_method(D_METHOD("get_start_spells"), &EntityClassData::get_start_spells);
	ClassDB::bind_method(D_METHOD("set_start_spells", "spells"), &EntityClassData::set_start_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "start_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_start_spells", "get_start_spells");

	////    AURAS    ////
	ClassDB::bind_method(D_METHOD("get_num_auras"), &EntityClassData::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &EntityClassData::set_num_auras);

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &EntityClassData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &EntityClassData::set_aura);

	ClassDB::bind_method(D_METHOD("get_auras"), &EntityClassData::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &EntityClassData::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	////    AI ACTIONS    ////
	ClassDB::bind_method(D_METHOD("get_num_ais"), &EntityClassData::get_num_ais);
	ClassDB::bind_method(D_METHOD("set_num_ais", "value"), &EntityClassData::set_num_ais);

	ClassDB::bind_method(D_METHOD("get_ai", "index"), &EntityClassData::get_ai);
	ClassDB::bind_method(D_METHOD("set_ai", "index", "action"), &EntityClassData::set_ai);

	ClassDB::bind_method(D_METHOD("get_ais"), &EntityClassData::get_ais);
	ClassDB::bind_method(D_METHOD("set_ais", "auras"), &EntityClassData::set_ais);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ais", PROPERTY_HINT_NONE, "17/17:EntityAI", PROPERTY_USAGE_DEFAULT, "EntityAI"), "set_ais", "get_ais");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "ret", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "_get_ai_instance"));

	ClassDB::bind_method(D_METHOD("get_ai_instance"), &EntityClassData::get_ai_instance);
	ClassDB::bind_method(D_METHOD("_get_ai_instance"), &EntityClassData::_get_ai_instance);
}
