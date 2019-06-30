#ifndef VISUAL_BONE_ATTACHMENT_H
#define VISUAL_BONE_ATTACHMENT_H

#include "core/ustring.h"
#include "core/resource.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/mesh.h"

#include "../entity_enums.h"

class CharacterSkeletonVisualEntry : public Resource {
	GDCLASS(CharacterSkeletonVisualEntry, Resource);

public:
    static const String BINDING_STRING_BONE_ATTACHMENT_TYPES;
    
    enum CharacterSkeletonVisualEntryType {
        BONE_ATTACHMENT_TYPE_NONE = 0,
        BONE_ATTACHMENT_TYPE_MESH = 1,
        BONE_ATTACHMENT_TYPE_EFFECT = 2,
        BONE_ATTACHMENT_TYPE_EQUIPMENT = 3,
        BONE_ATTACHMENT_TYPE_OVERRIDE = 4
    };
    
    int get_id();
	void set_id(int id);
    
    CharacterSkeletonVisualEntryType get_attachment_type();
    void set_attachment_type(CharacterSkeletonVisualEntryType attachment_type);
	
    EntityEnums::CharacterSkeletonPoints get_target_bone();
	void set_target_bone(EntityEnums::CharacterSkeletonPoints bone);
    
    Ref<PackedScene> get_effect();
    void set_effect(Ref<PackedScene> effect);

	Ref<ArrayMesh> get_mesh();
	void set_mesh(Ref<ArrayMesh> effect);

    CharacterSkeletonVisualEntry();

protected:
	static void _bind_methods();

private:
	int _id;
    CharacterSkeletonVisualEntryType _attachment_type;
	EntityEnums::CharacterSkeletonPoints _target_bone;
    Ref<PackedScene> _effect;
    Ref<ArrayMesh> _mesh;
};

VARIANT_ENUM_CAST(CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntryType);

#endif
