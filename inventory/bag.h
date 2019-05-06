#ifndef BAG_H
#define BAG_H

#include "core/reference.h"

#include "core/vector.h"

#include "../data/item_instance.h"
#include "bag_slot.h"

class Bag : public Reference {
	GDCLASS(Bag, Reference);

public:
	Ref<BagSlot> get_slot(int index);
    Ref<BagSlot> get_and_remove_slot(int index);
    int get_slot_count();
    void set_slot_count(int count);
    bool try_to_add_item(Ref<ItemInstance> item, int count = 1);
	bool add_item_to_slot(Ref<ItemInstance> item, int slot_index, int count = 1);

	Bag();
    ~Bag();

protected:
	static void _bind_methods();
    
private:
	Vector<Ref<BagSlot> > *_slots;
};

#endif
