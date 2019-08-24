#ifndef ITEM_VISUAL_ENTRY_H
#define ITEM_VISUAL_ENTRY_H

#include "core/resource.h"

class ItemVisualEntry : public Resource {
	GDCLASS(ItemVisualEntry, Resource);

public:
	ItemVisualEntry();
	~ItemVisualEntry();

protected:
	static void _bind_methods();

//private:
};

#endif
