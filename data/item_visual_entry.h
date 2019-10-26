#ifndef ITEM_VISUAL_ENTRY_H
#define ITEM_VISUAL_ENTRY_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/color.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../item_enums.h"

#include "scene/resources/packed_scene.h"
#include "scene/resources/mesh.h"
#include "../meshes/mesh_data_resource.h"

class ItemVisualEntry : public Resource {
	GDCLASS(ItemVisualEntry, Resource);

public:
	ItemEnums::EntityTextureLayers get_override_layer();
	void set_override_layer(ItemEnums::EntityTextureLayers layer);

	Ref<MeshDataResource> get_mesh();
	void set_mesh(Ref<MeshDataResource> mesh);

	Ref<Texture> get_texture();
	void set_texture(Ref<Texture> texture);

	Color get_color();
	void set_color(Color color);

	Ref<PackedScene> get_effect();
	void set_effect(Ref<PackedScene> effect);

	ItemVisualEntry();
	~ItemVisualEntry();

protected:
	static void _bind_methods();

private:
	ItemEnums::EntityTextureLayers _override_layer;
	Ref<MeshDataResource> _mesh;

	Ref<Texture> _texture;
	Color _color;

	Ref<PackedScene> _effect;
};

#endif
