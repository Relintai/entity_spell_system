#include "world_spell.h"

NodePath WorldSpell::get_body_path() {
	return _body_path;
}
void WorldSpell::set_body_path(NodePath value) {
	_body_path = value;

	_body = get_node_or_null(_body_path);

	if (ObjectDB::instance_validate(_body))
		_body->set_owner(this);
}
Node *WorldSpell::get_body() {
	return _body;
}

int WorldSpell::get_data_id() {
	return _data_id;
}
void WorldSpell::set_data_id(int value) {
	_data_id = value;
}

Ref<WorldSpellData> WorldSpell::get_data() {
	return _data;
}
void WorldSpell::set_data(Ref<WorldSpellData> value) {
	_data = value;
}

SpellEnums::ColliderType WorldSpell::get_collider_type() {
	return _collider_type;
}
void WorldSpell::set_collider_type(SpellEnums::ColliderType value) {
	_collider_type = value;
}

Vector3 WorldSpell::get_collider_box_extents() {
	return _collider_box_extents;
}
void WorldSpell::set_collider_box_extents(Vector3 value) {
	_collider_box_extents = value;
}

float WorldSpell::get_collider_sphere_radius() {
	return _collider_sphere_radius;
}
void WorldSpell::set_collider_sphere_radius(float value) {
	_collider_sphere_radius = value;
}

SpellEnums::TargetType WorldSpell::get_target_type() {
	return _target_type;
}
void WorldSpell::set_target_type(SpellEnums::TargetType value) {
	_target_type = value;
}

int WorldSpell::get_target_bone_id() {
	return _target_bone_id;
}
void WorldSpell::set_target_bone_id(int value) {
	_target_bone_id = value;
}

bool WorldSpell::get_move() {
	return _move;
}
void WorldSpell::set_move(bool value) {
	_move = value;
}

float WorldSpell::get_movement_speed() {
	return _movement_speed;
}
void WorldSpell::set_movement_speed(float value) {
	_movement_speed = value;
}

Vector3 WorldSpell::get_movement_dir() {
	return _movement_dir;
}
void WorldSpell::set_movement_dir(Vector3 value) {
	_movement_dir = value;
}

float WorldSpell::get_max_dist() {
	return _max_dist;
}
void WorldSpell::set_max_dist(float value) {
	_max_dist = value;
}

Ref<PackedScene> WorldSpell::get_effect() {
	return _effect;
}
void WorldSpell::set_effect(Ref<PackedScene> value) {
	_effect = value;
}

Vector3 WorldSpell::get_effect_offset() {
	return _effect_offset;
}
void WorldSpell::set_effect_offset(Vector3 value) {
	_effect_offset = value;
}

WorldSpell::WorldSpell() {
	_data_id = 0;

	_collider_type = SpellEnums::COLLIDER_TYPE_NONE;

	_collider_sphere_radius = 1;

	_target_type = SpellEnums::TARGET_TYPE_NONE;
	_target_bone_id = 0;

	_move = true;
	_movement_speed = 10;

	_max_dist = 400;
}

WorldSpell::~WorldSpell() {
	_data.unref();
	_effect.unref();
}

void WorldSpell::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_body_path"), &WorldSpell::get_body_path);
	ClassDB::bind_method(D_METHOD("set_body_path", "value"), &WorldSpell::set_body_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "body_path"), "set_body_path", "get_body_path");

	ClassDB::bind_method(D_METHOD("get_body"), &WorldSpell::get_body);

	ClassDB::bind_method(D_METHOD("get_data_id"), &WorldSpell::get_data_id);
	ClassDB::bind_method(D_METHOD("set_data_id", "value"), &WorldSpell::set_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "data_id"), "set_data_id", "get_data_id");

	ClassDB::bind_method(D_METHOD("get_data"), &WorldSpell::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "value"), &WorldSpell::set_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "WorldSpellData"), "set_data", "get_data");

	ClassDB::bind_method(D_METHOD("get_collider_type"), &WorldSpell::get_collider_type);
	ClassDB::bind_method(D_METHOD("set_collider_type", "value"), &WorldSpell::set_collider_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "collider_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_COLLIDER_TYPE), "set_collider_type", "get_collider_type");

	ClassDB::bind_method(D_METHOD("get_collider_box_extents"), &WorldSpell::get_collider_box_extents);
	ClassDB::bind_method(D_METHOD("set_collider_box_extents", "value"), &WorldSpell::set_collider_box_extents);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "collider_box_extents"), "set_collider_box_extents", "get_collider_box_extents");

	ClassDB::bind_method(D_METHOD("get_collider_sphere_radius"), &WorldSpell::get_collider_sphere_radius);
	ClassDB::bind_method(D_METHOD("set_collider_sphere_radius", "value"), &WorldSpell::set_collider_sphere_radius);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "collider_sphere_radius"), "set_collider_sphere_radius", "get_collider_sphere_radius");

	ClassDB::bind_method(D_METHOD("get_target_type"), &WorldSpell::get_target_type);
	ClassDB::bind_method(D_METHOD("set_target_type", "value"), &WorldSpell::set_target_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_type", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TARGET_TYPE), "set_target_type", "get_target_type");

	ClassDB::bind_method(D_METHOD("get_target_bone_id"), &WorldSpell::get_target_bone_id);
	ClassDB::bind_method(D_METHOD("set_target_bone_id", "value"), &WorldSpell::set_target_bone_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone_id"), "set_target_bone_id", "get_target_bone_id");

	ClassDB::bind_method(D_METHOD("get_move"), &WorldSpell::get_move);
	ClassDB::bind_method(D_METHOD("set_move", "value"), &WorldSpell::set_move);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "move"), "set_move", "get_move");

	ClassDB::bind_method(D_METHOD("get_movement_speed"), &WorldSpell::get_movement_speed);
	ClassDB::bind_method(D_METHOD("set_movement_speed", "value"), &WorldSpell::set_movement_speed);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "movement_speed"), "set_movement_speed", "get_movement_speed");

	ClassDB::bind_method(D_METHOD("get_movement_dir"), &WorldSpell::get_movement_dir);
	ClassDB::bind_method(D_METHOD("set_movement_dir", "value"), &WorldSpell::set_movement_dir);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "movement_dir"), "set_movement_dir", "get_movement_dir");

	ClassDB::bind_method(D_METHOD("get_max_dist"), &WorldSpell::get_max_dist);
	ClassDB::bind_method(D_METHOD("set_max_dist", "value"), &WorldSpell::set_max_dist);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_dist"), "set_max_dist", "get_max_dist");

	ClassDB::bind_method(D_METHOD("get_effect"), &WorldSpell::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &WorldSpell::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_effect_offset"), &WorldSpell::get_effect_offset);
	ClassDB::bind_method(D_METHOD("set_effect_offset", "value"), &WorldSpell::set_effect_offset);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "effect_offset"), "set_effect_offset", "get_effect_offset");
}
