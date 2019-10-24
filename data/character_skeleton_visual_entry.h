#ifndef VISUAL_BONE_ATTACHMENT_H
#define VISUAL_BONE_ATTACHMENT_H

#include "core/ustring.h"
#include "core/resource.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/mesh.h"

#include "../entity_enums.h"

#include "../meshes/mesh_data_resource.h"

class CharacterSkeletonVisualEntry : public Resource {
	GDCLASS(CharacterSkeletonVisualEntry, Resource);

public:
    int get_id();
	void set_id(int id);
    
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
	EntityEnums::CharacterSkeletonPoints _target_bone;
    Ref<PackedScene> _effect;
	Ref<MeshDataResource> _mesh;
};

#endif
