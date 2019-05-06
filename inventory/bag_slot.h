#ifndef BAG_SLOT_H
#define BAG_SLOT_H

#include "core/reference.h"
#include "../data/item_instance.h"

class BagSlot : public Reference {
	GDCLASS(BagSlot, Reference);

public:
	Ref<ItemInstance> get_item();
	void set_item(Ref<ItemInstance> item);
	void set_item_count(Ref<ItemInstance> item, int count = 1);
	int get_count();
	void set_count(int value);
	int get_slot_index();
	void set_slot_index(int value);
	bool has_item();
	void clear();

	BagSlot();
	BagSlot(Ref<ItemInstance> item);
	BagSlot(Ref<ItemInstance> item, int count);

protected:
	static void _bind_methods();
    
private:
	Ref<ItemInstance> _item;
	int _count;
	int _slot_index;
};

#endif
