#ifndef ITEM_VISUAL_ENTRY_H
#define ITEM_VISUAL_ENTRY_H

#include "core/color.h"
#include "core/resource.h"
#include "core/ustring.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../item_enums.h"

#include "scene/resources/mesh.h"
#include "scene/resources/packed_scene.h"

#ifdef MESH_DATA_RESOURCE_PRESENT
#include "../../mesh_data_resource/mesh_data_resource.h"
#endif

class ItemVisualEntry : public Resource {
	GDCLASS(ItemVisualEntry, Resource);

public:
	ItemEnums::EntityTextureLayers get_override_layer();
	void set_override_layer(ItemEnums::EntityTextureLayers layer);

#ifdef MESH_DATA_RESOURCE_PRESENT
	Ref<MeshDataResource> get_mesh(int index);
	void set_mesh(int index, Ref<MeshDataResource> mesh);
#endif

	Ref<Texture> get_texture(int index);
	void set_texture(int index, Ref<Texture> texture);

	Color get_color();
	void set_color(Color color);

	Ref<PackedScene> get_effect();
	void set_effect(Ref<PackedScene> effect);

	Vector3 get_effect_offset(int index);
	void set_effect_offset(int index, Vector3 offset);

	ItemVisualEntry();
	~ItemVisualEntry();

protected:
	static void _bind_methods();

private:
	ItemEnums::EntityTextureLayers _override_layer;

#ifdef MESH_DATA_RESOURCE_PRESENT
	Ref<MeshDataResource> _mesh[EntityEnums::GENDER_COUNT];
#endif

	Ref<Texture> _texture[EntityEnums::GENDER_COUNT];
	Color _color;

	Ref<PackedScene> _effect;
	Vector3 _effect_offset[EntityEnums::GENDER_COUNT];
};

#endif
