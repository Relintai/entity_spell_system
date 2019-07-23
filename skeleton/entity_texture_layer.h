#ifndef ENTITY_TEXTURE_LAYER_H
#define ENTITY_TEXTURE_LAYER_H

#include "core/resource.h"
#include "core/ustring.h"

class EntityTextureLayer : public Resource {
	GDCLASS(EntityTextureLayer, Resource);

public:
	enum {
		MAX_COLORS = 6
	};

	enum EntityTextureLayerLayers {
		ENTITY_TEXTURE_LAYER_NONE = 0,
		ENTITY_TEXTURE_LAYER_SKIN = 1,
		ENTITY_TEXTURE_LAYER_UNDERWEAR = 2,
		ENTITY_TEXTURE_LAYER_SHIRT = 3,
		ENTITY_TEXTURE_LAYER_CLOTHES_BASE = 4,
		ENTITY_TEXTURE_LAYER_BELT = 5,
		ENTITY_TEXTURE_LAYER_TABARD = 6,
		ENTITY_TEXTURE_LAYER_OVERLAY = 7
	};

	enum EntityTextureLayerRectId {
		ENTITY_TEXTURE_LAYER_RECT_ID_FULL = 0,
		ENTITY_TEXTURE_LAYER_RECT_ID_HEAD = 1,
		ENTITY_TEXTURE_LAYER_RECT_ID_FOOT = 2,
		//etc
	};

	Ref<Texture> get_texture();
	void set_texture(Ref<Texture> texture);

protected:
	static void _bind_methods();

private:
	Ref<Texture> _texture;
	int _layer;
	Color _colors[MAX_COLORS];
};

#endif
