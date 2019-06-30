#include "character_skeleton_visual_entry.h"

const String CharacterSkeletonVisualEntry::BINDING_STRING_BONE_ATTACHMENT_TYPES = "None, Mesh, Effect, Equipment, Override";

int CharacterSkeletonVisualEntry::get_id() {
    return _id;
}

void CharacterSkeletonVisualEntry::set_id(int id) {
    _id = id;
}
	
CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntryType CharacterSkeletonVisualEntry::get_attachment_type() {
    return _attachment_type;
}

void CharacterSkeletonVisualEntry::set_attachment_type(CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntryType attachment_type) {
    _attachment_type = attachment_type;
}
	
EntityEnums::CharacterSkeletonPoints CharacterSkeletonVisualEntry::get_target_bone() {
    return _target_bone;
}

void CharacterSkeletonVisualEntry::set_target_bone(EntityEnums::CharacterSkeletonPoints target_bone) {
    _target_bone = target_bone;
}
    
Ref<PackedScene> CharacterSkeletonVisualEntry::get_effect() {
    return _effect;
}
void CharacterSkeletonVisualEntry::set_effect(Ref<PackedScene> effect) {
    _effect = effect;
}

Ref<ArrayMesh> CharacterSkeletonVisualEntry::get_mesh() {
	return _mesh;
}
void CharacterSkeletonVisualEntry::set_mesh(Ref<ArrayMesh> mesh) {
	_mesh = mesh;
}

CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntry() {
    _id = 0;
    _target_bone = EntityEnums::SKELETON_POINT_ROOT;
	_attachment_type = BONE_ATTACHMENT_TYPE_NONE;
}

void CharacterSkeletonVisualEntry::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &CharacterSkeletonVisualEntry::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "path"), &CharacterSkeletonVisualEntry::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_attachment_type"), &CharacterSkeletonVisualEntry::get_attachment_type);
	ClassDB::bind_method(D_METHOD("set_attachment_type", "target_bone"), &CharacterSkeletonVisualEntry::set_attachment_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "attachment_type", PROPERTY_HINT_ENUM, CharacterSkeletonVisualEntry::BINDING_STRING_BONE_ATTACHMENT_TYPES), "set_attachment_type", "get_attachment_type");
    
    ClassDB::bind_method(D_METHOD("get_target_bone"), &CharacterSkeletonVisualEntry::get_target_bone);
	ClassDB::bind_method(D_METHOD("set_target_bone", "target_bone"), &CharacterSkeletonVisualEntry::set_target_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_target_bone", "get_target_bone");
    
    ClassDB::bind_method(D_METHOD("get_effect"), &CharacterSkeletonVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "path"), &CharacterSkeletonVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_mesh"), &CharacterSkeletonVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "mesh"), &CharacterSkeletonVisualEntry::set_mesh);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "ArrayMesh"), "set_mesh", "get_mesh");
    
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_NONE);
	BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_MESH);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EFFECT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EQUIPMENT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_OVERRIDE);
}

