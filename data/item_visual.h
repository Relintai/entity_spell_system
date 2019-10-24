#ifndef ITEM_VISUAL_H
#define ITEM_VISUAL_H

#include "core/resource.h"

#include "../item_enums.h"
#include "item_visual_entry.h"

class ItemVisual : public Resource {
	GDCLASS(ItemVisual, Resource);

public:
	ItemEnums::EntityTextureLayers get_layer();
	void set_layer(ItemEnums::EntityTextureLayers layer);

	Ref<ItemVisualEntry> get_visual(int index);
	void set_visual(int index, Ref<ItemVisualEntry> entry);

	ItemVisual();
	~ItemVisual();

protected:
	static void _bind_methods();

private:
	ItemEnums::EntityTextureLayers _layer;
	Ref<ItemVisualEntry> _entries[EntityEnums::SKELETON_POINTS_MAX];
};

#endif
