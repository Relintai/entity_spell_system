#ifndef ITEM_VISUAL_H
#define ITEM_VISUAL_H

#include "core/resource.h"

class ItemVisual : public Resource {
	GDCLASS(ItemVisual, Resource);

public:
	ItemVisual();
	~ItemVisual();

protected:
	static void _bind_methods();

//private:
};

#endif
