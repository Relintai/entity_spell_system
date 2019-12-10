#include "world_spell_data.h"

int WorldSpellData::get_id() {
	return _id;
}
void WorldSpellData::set_id(int value) {
	_id = value;
}

SpellEnums::ColliderType WorldSpellData::get_collider_type() {
	return _collider_type;
}
void WorldSpellData::set_collider_type(SpellEnums::ColliderType value) {
	_collider_type = value;
}

Vector3 WorldSpellData::get_collider_box_extents() {
	return _collider_box_extents;
}
void WorldSpellData::set_collider_box_extents(Vector3 value) {
	_collider_box_extents = value;
}

float WorldSpellData::get_collider_sphere_radius() {
	return _collider_sphere_radius;
}
void WorldSpellData::set_collider_sphere_radius(float value) {
	_collider_sphere_radius = value;
}

SpellEnums::TargetType WorldSpellData::get_target_type() {
	return _target_type;
}
void WorldSpellData::set_target_type(SpellEnums::TargetType value) {
	_target_type = value;
}

int WorldSpellData::get_target_bone_id() {
	return _target_bone_id;
}
void WorldSpellData::set_target_bone_id(int value) {
	_target_bone_id = value;
}

bool WorldSpellData::get_move() {
	return _move;
}
void WorldSpellData::set_move(bool value) {
	_move = value;
}

float WorldSpellData::get_movement_speed() {
	return _movement_speed;
}
void WorldSpellData::set_movement_speed(float value) {
	_movement_speed = value;
}

Vector3 WorldSpellData::get_movement_dir() {
	return _movement_dir;
}
void WorldSpellData::set_movement_dir(Vector3 value) {
	_movement_dir = value;
}

float WorldSpellData::get_max_dist() {
	return _max_dist;
}
void WorldSpellData::set_max_dist(float value) {
	_max_dist = value;
}

Ref<PackedScene> WorldSpellData::get_effect() {
	return _effect;
}
void WorldSpellData::set_effect(Ref<PackedScene> value) {
	_effect = value;
}

Vector3 WorldSpellData::get_effect_offset() {
	return _effect_offset;
}
void WorldSpellData::set_effect_offset(Vector3 value) {
	_effect_offset = value;
}

WorldSpellData::WorldSpellData() {
	_id = 0;

	_collider_type = SpellEnums::COLLIDER_TYPE_NONE;

	_collider_sphere_radius = 1;

	_target_type = SpellEnums::TARGET_TYPE_NONE;
	_target_bone_id = 0;

	_move = true;
	_movement_speed = 10;

	_max_dist = 400;
}

WorldSpellData::~WorldSpellData() {
	_effect.unref();
}

void WorldSpellData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &WorldSpellData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &WorldSpellData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_collider_type"), &WorldSpellData::get_collider_type);
	ClassDB::bind_method(D_METHOD("set_collider_type", "value"), &WorldSpellData::set_collider_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "collider_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_COLLIDER_TYPE), "set_collider_type", "get_collider_type");

	ClassDB::bind_method(D_METHOD("get_collider_box_extents"), &WorldSpellData::get_collider_box_extents);
	ClassDB::bind_method(D_METHOD("set_collider_box_extents", "value"), &WorldSpellData::set_collider_box_extents);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "collider_box_extents"), "set_collider_box_extents", "get_collider_box_extents");

	ClassDB::bind_method(D_METHOD("get_collider_sphere_radius"), &WorldSpellData::get_collider_sphere_radius);
	ClassDB::bind_method(D_METHOD("set_collider_sphere_radius", "value"), &WorldSpellData::set_collider_sphere_radius);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "collider_sphere_radius"), "set_collider_sphere_radius", "get_collider_sphere_radius");

	ClassDB::bind_method(D_METHOD("get_target_type"), &WorldSpellData::get_target_type);
	ClassDB::bind_method(D_METHOD("set_target_type", "value"), &WorldSpellData::set_target_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TARGET_TYPE), "set_target_type", "get_target_type");

	ClassDB::bind_method(D_METHOD("get_target_bone_id"), &WorldSpellData::get_target_bone_id);
	ClassDB::bind_method(D_METHOD("set_target_bone_id", "value"), &WorldSpellData::set_target_bone_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone_id"), "set_target_bone_id", "get_target_bone_id");

	ClassDB::bind_method(D_METHOD("get_move"), &WorldSpellData::get_move);
	ClassDB::bind_method(D_METHOD("set_move", "value"), &WorldSpellData::set_move);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "move"), "set_move", "get_move");

	ClassDB::bind_method(D_METHOD("get_movement_speed"), &WorldSpellData::get_movement_speed);
	ClassDB::bind_method(D_METHOD("set_movement_speed", "value"), &WorldSpellData::set_movement_speed);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "movement_speed"), "set_movement_speed", "get_movement_speed");

	ClassDB::bind_method(D_METHOD("get_movement_dir"), &WorldSpellData::get_movement_dir);
	ClassDB::bind_method(D_METHOD("set_movement_dir", "value"), &WorldSpellData::set_movement_dir);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "movement_dir"), "set_movement_dir", "get_movement_dir");

	ClassDB::bind_method(D_METHOD("get_max_dist"), &WorldSpellData::get_max_dist);
	ClassDB::bind_method(D_METHOD("set_max_dist", "value"), &WorldSpellData::set_max_dist);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_dist"), "set_max_dist", "get_max_dist");

	ClassDB::bind_method(D_METHOD("get_effect"), &WorldSpellData::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &WorldSpellData::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_effect_offset"), &WorldSpellData::get_effect_offset);
	ClassDB::bind_method(D_METHOD("set_effect_offset", "value"), &WorldSpellData::set_effect_offset);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "effect_offset"), "set_effect_offset", "get_effect_offset");
}
