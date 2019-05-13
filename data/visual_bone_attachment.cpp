#include "visual_bone_attachment.h"

const String VisualBoneAttachment::BINDING_STRING_BONE_ATTACHMENT_TYPES = "None, Bodypart, Effect, Equipment, Override";

int VisualBoneAttachment::get_id() {
    return _id;
}

void VisualBoneAttachment::set_id(int id) {
    _id = id;
}
	
VisualBoneAttachment::VisualBoneAttachmentType VisualBoneAttachment::get_attachment_type() {
    return _attachment_type;
}

void VisualBoneAttachment::set_attachment_type(VisualBoneAttachment::VisualBoneAttachmentType attachment_type) {
    _attachment_type = attachment_type;
}
	
EntityEnums::CharacterSkeletonBoneId VisualBoneAttachment::get_target_bone() {
    return _target_bone;
}

void VisualBoneAttachment::set_target_bone(EntityEnums::CharacterSkeletonBoneId target_bone) {
    _target_bone = target_bone;
}
    
Ref<PackedScene> VisualBoneAttachment::get_effect() {
    return _effect;
}

void VisualBoneAttachment::set_effect(Ref<PackedScene> effect) {
    _effect = effect;
}

VisualBoneAttachment::VisualBoneAttachment() {
    _id = 0;
    _target_bone = EntityEnums::BONE_ID_HIP;
}

void VisualBoneAttachment::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &VisualBoneAttachment::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "path"), &VisualBoneAttachment::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_attachment_type"), &VisualBoneAttachment::get_attachment_type);
	ClassDB::bind_method(D_METHOD("set_attachment_type", "target_bone"), &VisualBoneAttachment::set_attachment_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "attachment_type", PROPERTY_HINT_ENUM, VisualBoneAttachment::BINDING_STRING_BONE_ATTACHMENT_TYPES), "set_attachment_type", "get_attachment_type");
    
    ClassDB::bind_method(D_METHOD("get_target_bone"), &VisualBoneAttachment::get_target_bone);
	ClassDB::bind_method(D_METHOD("set_target_bone", "target_bone"), &VisualBoneAttachment::set_target_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_BONE_ID), "set_target_bone", "get_target_bone");
    
    ClassDB::bind_method(D_METHOD("get_effect"), &VisualBoneAttachment::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "path"), &VisualBoneAttachment::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");
    
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_NONE);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_BODYPART);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EFFECT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_EQUIPMENT);
    BIND_ENUM_CONSTANT(BONE_ATTACHMENT_TYPE_OVERRIDE);
}

