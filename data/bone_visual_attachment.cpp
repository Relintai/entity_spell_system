#include "bone_visual_attachment.h"

const String BoneVisualAttachment::BINDING_STRING_BONE_ATTACHMENT_TYPES = "None, Bodypart, Effect, Equipment, Override";

int BoneVisualAttachment::get_id() {
    return _id;
}

void BoneVisualAttachment::set_id(int id) {
    _id = id;
}
	
BoneVisualAttachment::BoneVisualAttachmentType BoneVisualAttachment::get_attachment_type() {
    return _attachment_type;
}

void BoneVisualAttachment::set_attachment_type(BoneVisualAttachment::BoneVisualAttachmentType attachment_type) {
    _attachment_type = attachment_type;
}
	
EntityEnums::CharacterSkeletonBoneId BoneVisualAttachment::get_target_bone() {
    return _target_bone;
}

void BoneVisualAttachment::set_target_bone(EntityEnums::CharacterSkeletonBoneId target_bone) {
    _target_bone = target_bone;
}
    
Ref<PackedScene> BoneVisualAttachment::get_effect() {
    return _effect;
}

void BoneVisualAttachment::set_effect(Ref<PackedScene> effect) {
    _effect = effect;
}

BoneVisualAttachment::BoneVisualAttachment() {
    _id = 0;
    _target_bone = EntityEnums::BONE_ID_HIP;
}

void BoneVisualAttachment::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &BoneVisualAttachment::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "path"), &BoneVisualAttachment::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_attachment_type"), &BoneVisualAttachment::get_attachment_type);
	ClassDB::bind_method(D_METHOD("set_attachment_type", "target_bone"), &BoneVisualAttachment::set_attachment_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "attachment_type", PROPERTY_HINT_ENUM, BoneVisualAttachment::BINDING_STRING_BONE_ATTACHMENT_TYPES), "set_attachment_type", "get_attachment_type");
    
    ClassDB::bind_method(D_METHOD("get_target_bone"), &BoneVisualAttachment::get_target_bone);
	ClassDB::bind_method(D_METHOD("set_target_bone", "target_bone"), &BoneVisualAttachment::set_target_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_BONE_ID), "set_target_bone", "get_target_bone");
    
    ClassDB::bind_method(D_METHOD("get_effect"), &BoneVisualAttachment::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "path"), &BoneVisualAttachment::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");
    
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_NONE);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_BODYPART);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EFFECT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EQUIPMENT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_OVERRIDE);
}

