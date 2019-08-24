#ifndef ITEM_VISUAL_ENTRY_H
#define ITEM_VISUAL_ENTRY_H

#include "core/reference.h"

class ItemVisualEntry : public Reference {
	GDCLASS(ItemVisualEntry, Reference);

public:
	ItemVisualEntry();
	~ItemVisualEntry();

protected:
	static void _bind_methods();

//private:
};

#endif
