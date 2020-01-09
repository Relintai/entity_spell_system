#include "spell_effect_visual_simple.h"

bool SpellEffectVisualSimple::has_spell_effect_visual() {
	return _effect_visual.is_valid();
}

EntityEnums::CharacterSkeletonPoints SpellEffectVisualSimple::get_spell_effect_visual_point() {
	return _effect_visual_point;
}
void SpellEffectVisualSimple::set_spell_effect_visual_point(EntityEnums::CharacterSkeletonPoints point) {
	_effect_visual_point = point;
}

Ref<PackedScene> SpellEffectVisualSimple::get_spell_effect_visual() {
	return _effect_visual;
}
void SpellEffectVisualSimple::set_spell_effect_visual(Ref<PackedScene> value) {
	_effect_visual = value;
}

bool SpellEffectVisualSimple::has_spell_cast_finish_effect() {
	return _spell_cast_finish_effect.is_valid();
}

EntityEnums::CharacterSkeletonPoints SpellEffectVisualSimple::get_spell_cast_finish_effect_point() {
	return _spell_cast_finish_effect_point;
}
void SpellEffectVisualSimple::set_spell_cast_finish_effect_point(EntityEnums::CharacterSkeletonPoints point) {
	_spell_cast_finish_effect_point = point;
}

Ref<PackedScene> SpellEffectVisualSimple::get_spell_cast_finish_effect() {
	return _spell_cast_finish_effect;
}
void SpellEffectVisualSimple::set_spell_cast_finish_effect(Ref<PackedScene> value) {
	_spell_cast_finish_effect = value;
}

bool SpellEffectVisualSimple::has_spell_cast_effect() {
	return _spell_cast_effect.is_valid();
}
Ref<PackedScene> SpellEffectVisualSimple::get_spell_cast_effect() {
	return _spell_cast_effect;
}
void SpellEffectVisualSimple::set_spell_cast_effect(Ref<PackedScene> value) {
	_spell_cast_effect = value;
}

//Visual Effect

bool SpellEffectVisualSimple::has_aura_effect_visual() {
	return _effect_visual.is_valid();
}

EntityEnums::CharacterSkeletonPoints SpellEffectVisualSimple::get_aura_effect_visual_point() {
	return _aura_effect_visual_point;
}
void SpellEffectVisualSimple::set_aura_effect_visual_point(EntityEnums::CharacterSkeletonPoints point) {
	_aura_effect_visual_point = point;
}

Ref<PackedScene> SpellEffectVisualSimple::get_aura_effect_visual() {
	return _aura_effect_visual;
}
void SpellEffectVisualSimple::set_aura_effect_visual(Ref<PackedScene> value) {
	_aura_effect_visual = value;
}

SpellEffectVisualSimple::SpellEffectVisualSimple() {
}

SpellEffectVisualSimple::~SpellEffectVisualSimple() {
}

void SpellEffectVisualSimple::_bind_methods() {

	ADD_GROUP("Effect", "spell_effect");
	ClassDB::bind_method(D_METHOD("has_spell_effect_visual"), &SpellEffectVisualSimple::has_spell_effect_visual);

	ClassDB::bind_method(D_METHOD("get_spell_effect_visual_point"), &SpellEffectVisualSimple::get_spell_effect_visual_point);
	ClassDB::bind_method(D_METHOD("set_spell_effect_visual_point", "value"), &SpellEffectVisualSimple::set_spell_effect_visual_point);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_effect_visual_point", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_spell_effect_visual_point", "get_spell_effect_visual_point");

	ClassDB::bind_method(D_METHOD("get_spell_effect_visual"), &SpellEffectVisualSimple::get_spell_effect_visual);
	ClassDB::bind_method(D_METHOD("set_spell_effect_visual", "value"), &SpellEffectVisualSimple::set_spell_effect_visual);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell_effect_visual", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_spell_effect_visual", "get_spell_effect_visual");

	ClassDB::bind_method(D_METHOD("has_spell_spell_cast_finish_effect"), &SpellEffectVisualSimple::has_spell_cast_finish_effect);

	ClassDB::bind_method(D_METHOD("get_spell_cast_finish_effect_point"), &SpellEffectVisualSimple::get_spell_cast_finish_effect_point);
	ClassDB::bind_method(D_METHOD("set_spell_cast_finish_effect_point", "value"), &SpellEffectVisualSimple::set_spell_cast_finish_effect_point);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_cast_finish_effect_point", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_spell_cast_finish_effect_point", "get_spell_cast_finish_effect_point");

	ClassDB::bind_method(D_METHOD("get_spell_cast_finish_effect"), &SpellEffectVisualSimple::get_spell_cast_finish_effect);
	ClassDB::bind_method(D_METHOD("set_spell_cast_finish_effect", "value"), &SpellEffectVisualSimple::set_spell_cast_finish_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect_spell_cast_finish_effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_spell_cast_finish_effect", "get_spell_cast_finish_effect");

	ClassDB::bind_method(D_METHOD("has_spell_cast_effect"), &SpellEffectVisualSimple::has_spell_cast_effect);
	ClassDB::bind_method(D_METHOD("get_spell_cast_effect"), &SpellEffectVisualSimple::get_spell_cast_effect);
	ClassDB::bind_method(D_METHOD("set_spell_cast_effect", "value"), &SpellEffectVisualSimple::set_spell_cast_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect_spell_cast_effect_id", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_spell_cast_effect", "get_spell_cast_effect");

	//Visual Effect
	ADD_GROUP("Aura Effect", "aura_effect");
	ClassDB::bind_method(D_METHOD("has_aura_effect_visual"), &SpellEffectVisualSimple::has_aura_effect_visual);

	ClassDB::bind_method(D_METHOD("get_aura_effect_visual_point"), &SpellEffectVisualSimple::get_aura_effect_visual_point);
	ClassDB::bind_method(D_METHOD("set_aura_effect_visual_point", "value"), &SpellEffectVisualSimple::set_aura_effect_visual_point);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_effect_visual_point", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_aura_effect_visual_point", "get_aura_effect_visual_point");

	ClassDB::bind_method(D_METHOD("get_aura_effect_visual"), &SpellEffectVisualSimple::get_aura_effect_visual);
	ClassDB::bind_method(D_METHOD("set_aura_effect_visual", "value"), &SpellEffectVisualSimple::set_aura_effect_visual);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_effect_visual", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_aura_effect_visual", "get_aura_effect_visual");
}
