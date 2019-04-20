#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/object.h"

class ItemInstance : public Object {
	GDCLASS(ItemInstance, Object);

private:
	int _item_id;
	int _count;
	int _slot_id;

protected:
	static void _bind_methods();

public:
	int get_item_id();
	void set_item_id(int value);
	int get_count();
	void set_count(int value);
	int get_slot_id();
	void set_slot_id(int value);

	ItemInstance();
	ItemInstance(int itemId);
	ItemInstance(int itemId, int count);
};

#endif
