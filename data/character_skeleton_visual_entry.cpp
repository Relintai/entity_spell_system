#include "character_skeleton_visual_entry.h"

int CharacterSkeletonVisualEntry::get_id() {
    return _id;
}

void CharacterSkeletonVisualEntry::set_id(int id) {
    _id = id;
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

Ref<MeshDataResource> CharacterSkeletonVisualEntry::get_mesh() {
	return _mesh;
}
void CharacterSkeletonVisualEntry::set_mesh(Ref<MeshDataResource> mesh) {
	_mesh = mesh;
}

CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntry() {
    _id = 0;
    _target_bone = EntityEnums::SKELETON_POINT_ROOT;
}

void CharacterSkeletonVisualEntry::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &CharacterSkeletonVisualEntry::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "path"), &CharacterSkeletonVisualEntry::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ClassDB::bind_method(D_METHOD("get_target_bone"), &CharacterSkeletonVisualEntry::get_target_bone);
	ClassDB::bind_method(D_METHOD("set_target_bone", "target_bone"), &CharacterSkeletonVisualEntry::set_target_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_target_bone", "get_target_bone");
    
    ClassDB::bind_method(D_METHOD("get_effect"), &CharacterSkeletonVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "path"), &CharacterSkeletonVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_mesh"), &CharacterSkeletonVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "mesh"), &CharacterSkeletonVisualEntry::set_mesh);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh");
}

