#ifndef VISUAL_BONE_ATTACHMENT_H
#define VISUAL_BONE_ATTACHMENT_H

#include "core/ustring.h"
#include "core/resource.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/mesh.h"

#include "../entity_enums.h"

#include "../meshes/mesh_data_resource.h"
#include "../skeleton/entity_texture_layer.h"

class CharacterSkeletonVisualEntry : public Resource {
	GDCLASS(CharacterSkeletonVisualEntry, Resource);

public:
    static const String BINDING_STRING_BONE_ATTACHMENT_TYPES;

	enum {
		MAX_TEXTURE_LAYERS = 5
	};

	//not needed, delete
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

	Ref<MeshDataResource> get_mesh();
	void set_mesh(Ref<MeshDataResource> effect);

    CharacterSkeletonVisualEntry();

protected:
	static void _bind_methods();

private:
	int _id;
    CharacterSkeletonVisualEntryType _attachment_type;
	EntityEnums::CharacterSkeletonPoints _target_bone;
    Ref<PackedScene> _effect;
	Ref<MeshDataResource> _mesh;
	//apply these from to to bottom, with color index 0, if index not present. store color index in item instance. Use the same index for all of them at once.
	Ref<EntityTextureLayer> _texture_layers[MAX_TEXTURE_LAYERS];
};

VARIANT_ENUM_CAST(CharacterSkeletonVisualEntry::CharacterSkeletonVisualEntryType);

#endif
