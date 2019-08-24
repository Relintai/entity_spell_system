#ifndef ITEM_VISUAL_H
#define ITEM_VISUAL_H

#include "core/reference.h"

class ItemVisual : public Reference {
	GDCLASS(ItemVisual, Reference);

public:
	ItemVisual();
	~ItemVisual();

protected:
	static void _bind_methods();

//private:
};

#endif
