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

#include "aura_infos.h"

#include "../data/spells/spell.h"

Entity *AuraApplyInfo::caster_get() const {
	return _caster;
}

void AuraApplyInfo::caster_set(Entity *value) {
	_caster = value;
}

void AuraApplyInfo::caster_set_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = Object::cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_caster = e;
}

Entity *AuraApplyInfo::target_get() const {
	return _target;
}

void AuraApplyInfo::target_set(Entity *value) {
	_target = value;
}

void AuraApplyInfo::target_set_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = Object::cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_target = e;
}

float AuraApplyInfo::spell_scale_get() const {
	return _spell_scale;
}

void AuraApplyInfo::spell_scale_set(float value) {
	_spell_scale = value;
}

Ref<Spell> AuraApplyInfo::get_aura() const {
	return Ref<Spell>(_aura);
}

void AuraApplyInfo::set_aura(Ref<Spell> aura) {
	_aura = (*aura);
}

AuraApplyInfo::AuraApplyInfo() {
	_caster = NULL;
	_target = NULL;
	_spell_scale = 0;
	_aura = NULL;
}

AuraApplyInfo::AuraApplyInfo(Entity *caster, Entity *target, float spell_scale, Spell *aura) {
	_caster = caster;
	_target = target;
	_spell_scale = spell_scale;
	_aura = aura;
}

AuraApplyInfo::AuraApplyInfo(Entity *caster, Entity *target, float spell_scale) {
	_caster = caster;
	_target = target;
	_spell_scale = spell_scale;
	_aura = NULL;
}

void AuraApplyInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("caster_get"), &AuraApplyInfo::caster_get);
	ClassDB::bind_method(D_METHOD("caster_set", "caster"), &AuraApplyInfo::caster_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "caster_set", "caster_get");

	ClassDB::bind_method(D_METHOD("target_get"), &AuraApplyInfo::target_get);
	ClassDB::bind_method(D_METHOD("target_set", "target"), &AuraApplyInfo::target_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "target_set", "target_get");

	ClassDB::bind_method(D_METHOD("spell_scale_get"), &AuraApplyInfo::spell_scale_get);
	ClassDB::bind_method(D_METHOD("spell_scale_set", "value"), &AuraApplyInfo::spell_scale_set);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "spell_scale"), "spell_scale_set", "spell_scale_get");

	ClassDB::bind_method(D_METHOD("get_aura"), &AuraApplyInfo::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "aura"), &AuraApplyInfo::set_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_aura", "get_aura");
}
