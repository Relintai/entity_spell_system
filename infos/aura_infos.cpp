#include "aura_infos.h"

#include "../data/aura.h"

Entity *AuraApplyInfo::get_caster() const {
	return _caster;
}

void AuraApplyInfo::set_caster(Entity *value) {
	_caster = value;
}

void AuraApplyInfo::set_caster_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = Object::cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_caster = e;
}

Entity *AuraApplyInfo::get_target() const {
	return _target;
}

void AuraApplyInfo::set_target(Entity *value) {
	_target = value;
}

void AuraApplyInfo::set_target_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = Object::cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_target = e;
}

float AuraApplyInfo::get_spell_scale() const {
	return _spell_scale;
}

void AuraApplyInfo::set_spell_scale(float value) {
	_spell_scale = value;
}

Ref<Aura> AuraApplyInfo::get_aura() const {
	return Ref<Aura>(_aura);
}

void AuraApplyInfo::set_aura(Ref<Aura> aura) {
	_aura = (*aura);
}

AuraApplyInfo::AuraApplyInfo() {
	_caster = NULL;
	_target = NULL;
	_spell_scale = 0;
	_aura = NULL;
}

AuraApplyInfo::AuraApplyInfo(Entity *caster, Entity *target, float spell_scale, Aura *aura) {
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
	ClassDB::bind_method(D_METHOD("get_caster"), &AuraApplyInfo::get_caster);
	ClassDB::bind_method(D_METHOD("set_caster", "caster"), &AuraApplyInfo::set_caster_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_caster", "get_caster");

	ClassDB::bind_method(D_METHOD("get_target"), &AuraApplyInfo::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "target"), &AuraApplyInfo::set_target_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_target", "get_target");

	ClassDB::bind_method(D_METHOD("get_spell_scale"), &AuraApplyInfo::get_spell_scale);
	ClassDB::bind_method(D_METHOD("set_spell_scale", "value"), &AuraApplyInfo::set_spell_scale);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "spell_scale"), "set_spell_scale", "get_spell_scale");

	ClassDB::bind_method(D_METHOD("get_aura"), &AuraApplyInfo::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "aura"), &AuraApplyInfo::set_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura");
}
