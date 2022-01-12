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

#include "spell_cast_info.h"

#include "core/version.h"

#include "../data/items/item_instance.h"
#include "../data/items/item_template.h"
#include "../data/spells/spell.h"
#include "../database/ess_resource_db.h"
#include "../entities/entity.h"
#include "../singletons/ess.h"

#include "../defines.h"

////    SpellCastInfo    ////

Entity *SpellCastInfo::caster_get() {
	if (_caster && !INSTANCE_VALIDATE(_caster)) {
		_caster = NULL;
	}

	return _caster;
}
void SpellCastInfo::caster_set(Entity *value) {
	_caster = value;
}
void SpellCastInfo::caster_set_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_caster = e;
}

Entity *SpellCastInfo::target_get() {
	if (_target && !INSTANCE_VALIDATE(_target)) {
		_target = NULL;
	}

	return _target;
}
void SpellCastInfo::target_set(Entity *value) {
	_target = value;
}
void SpellCastInfo::target_set_bind(Node *target) {
	if (!target) {
		return;
	}

	Entity *e = cast_to<Entity>(target);

	if (!e) {
		return;
	}

	_target = e;
}

bool SpellCastInfo::has_cast_time_get() const {
	return _has_cast_time;
}
void SpellCastInfo::has_cast_time_set(bool value) {
	_has_cast_time = value;
}

float SpellCastInfo::cast_time_get() const {
	return _cast_time;
}
void SpellCastInfo::cast_time_set(float value) {
	_cast_time = value;
}

float SpellCastInfo::current_cast_time_get() const {
	return _current_cast_time;
}
void SpellCastInfo::current_cast_time_set(float value) {
	_current_cast_time = value;
}

bool SpellCastInfo::is_casting_get() const {
	return _is_casting;
}
void SpellCastInfo::is_casting_set(bool value) {
	_is_casting = value;
}

int SpellCastInfo::num_pushbacks_get() const {
	return _num_pushbacks;
}
void SpellCastInfo::num_pushbacks_set(int value) {
	_num_pushbacks = value;
}

float SpellCastInfo::spell_scale_get() const {
	return _spell_scale;
}
void SpellCastInfo::spell_scale_set(float value) {
	_spell_scale = value;
}

Ref<Spell> SpellCastInfo::get_spell() const {
	return _spell;
}
void SpellCastInfo::set_spell(const Ref<Spell> &spell) {
	_spell = spell;
}

Ref<ItemInstance> SpellCastInfo::get_source_item() const {
	return _source_item;
}
void SpellCastInfo::set_source_item(const Ref<ItemInstance> &item) {
	_source_item = item;
}

Ref<ItemTemplate> SpellCastInfo::get_source_template() const {
	return _source_template;
}
void SpellCastInfo::set_source_template(const Ref<ItemTemplate> &source_template) {
	_source_template = source_template;
}

bool SpellCastInfo::update_cast_time(float delta) {
	_current_cast_time += delta;

	if (_current_cast_time >= _cast_time) {
		_current_cast_time = _cast_time;

		return true;
	}

	return false;
}

void SpellCastInfo::physics_process(float delta) {
	ERR_FAIL_COND(!_spell.is_valid());

	_spell->son_physics_process(Ref<SpellCastInfo>(this), delta);
}

void SpellCastInfo::resolve_references(Node *owner) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(owner));

	ERR_FAIL_COND(!owner->is_inside_tree());

	_caster = Object::cast_to<Entity>(owner);

	if (owner->is_inside_tree()) {
		_target = Object::cast_to<Entity>(owner->get_node_or_null(_target_path));
	}

	Ref<Spell> spell = ESS::get_singleton()->get_resource_db()->get_spell(_spell_id);

	if (spell.is_valid()) {
		_spell = spell;
	}
}

Dictionary SpellCastInfo::to_dict() {
	Dictionary dict;

	if (INSTANCE_VALIDATE(_caster))
		dict["caster"] = _caster->get_path();

	if (INSTANCE_VALIDATE(_target))
		dict["target"] = _target->get_path();

	dict["has_cast_time"] = _has_cast_time;
	dict["cast_time"] = _cast_time;

	dict["current_cast_time"] = _current_cast_time;
	dict["num_pushbacks"] = _num_pushbacks;
	dict["is_casting"] = _is_casting;

	dict["spell_id"] = _spell->get_id();

	//item serialization not needed

	return dict;
}
void SpellCastInfo::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_has_cast_time = dict.get("has_cast_time", true);
	_cast_time = dict.get("cast_time", 0);

	_current_cast_time = dict.get("current_cast_time", 0);
	_num_pushbacks = dict.get("num_pushbacks", 0);
	_is_casting = dict.get("is_casting", true);

	_spell_id = dict.get("spell_id", 0);

	//item serialization not needed
}

SpellCastInfo::SpellCastInfo() {
	_caster = NULL;
	_target = NULL;

	_has_cast_time = false;
	_cast_time = 0;
	_spell_scale = 0;

	_current_cast_time = 0;
	_num_pushbacks = 0;

	_is_casting = false;

	_spell_id = 0;
}

SpellCastInfo::~SpellCastInfo() {
	_caster = NULL;
	_target = NULL;

	_spell.unref();
	_source_item.unref();
	_source_template.unref();
}

void SpellCastInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("caster_get"), &SpellCastInfo::caster_get);
	ClassDB::bind_method(D_METHOD("caster_set", "caster"), &SpellCastInfo::caster_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "caster_set", "caster_get");

	ClassDB::bind_method(D_METHOD("target_get"), &SpellCastInfo::target_get);
	ClassDB::bind_method(D_METHOD("set_target", "caster"), &SpellCastInfo::target_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_target", "target_get");

	ClassDB::bind_method(D_METHOD("has_cast_time_get"), &SpellCastInfo::has_cast_time_get);
	ClassDB::bind_method(D_METHOD("has_cast_time_set", "value"), &SpellCastInfo::has_cast_time_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_cast_time"), "has_cast_time_set", "has_cast_time_get");

	ClassDB::bind_method(D_METHOD("cast_time_get"), &SpellCastInfo::cast_time_get);
	ClassDB::bind_method(D_METHOD("cast_time_set", "value"), &SpellCastInfo::cast_time_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cast_time"), "cast_time_set", "cast_time_get");

	ClassDB::bind_method(D_METHOD("current_cast_time_get"), &SpellCastInfo::current_cast_time_get);
	ClassDB::bind_method(D_METHOD("current_cast_time_set", "value"), &SpellCastInfo::current_cast_time_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "current_cast_time"), "current_cast_time_set", "current_cast_time_get");

	ClassDB::bind_method(D_METHOD("is_casting_get"), &SpellCastInfo::is_casting_get);
	ClassDB::bind_method(D_METHOD("is_casting_set", "value"), &SpellCastInfo::is_casting_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_casting"), "is_casting_set", "is_casting_get");

	ClassDB::bind_method(D_METHOD("num_pushbacks_get"), &SpellCastInfo::num_pushbacks_get);
	ClassDB::bind_method(D_METHOD("num_pushbacks_set", "value"), &SpellCastInfo::num_pushbacks_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_pushbacks"), "num_pushbacks_set", "num_pushbacks_get");

	ClassDB::bind_method(D_METHOD("spell_scale_get"), &SpellCastInfo::spell_scale_get);
	ClassDB::bind_method(D_METHOD("spell_scale_set", "value"), &SpellCastInfo::spell_scale_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "spell_scale"), "spell_scale_set", "spell_scale_get");

	ClassDB::bind_method(D_METHOD("get_spell"), &SpellCastInfo::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "spell"), &SpellCastInfo::set_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	ClassDB::bind_method(D_METHOD("get_source_item"), &SpellCastInfo::get_source_item);
	ClassDB::bind_method(D_METHOD("set_source_item", "spell"), &SpellCastInfo::set_source_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "source_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "set_source_item", "get_source_item");

	ClassDB::bind_method(D_METHOD("get_source_template"), &SpellCastInfo::get_source_template);
	ClassDB::bind_method(D_METHOD("set_source_template", "spell"), &SpellCastInfo::set_source_template);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "source_template", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_source_template", "get_source_template");

	ClassDB::bind_method(D_METHOD("update_cast_time", "delta"), &SpellCastInfo::update_cast_time);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &SpellCastInfo::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &SpellCastInfo::to_dict);
}
