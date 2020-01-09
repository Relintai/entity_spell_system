#ifndef VENDOR_ITEM_DATA_ENTRY_H
#define VENDOR_ITEM_DATA_ENTRY_H

#include "core/resource.h"

class ItemTemplate;

class VendorItemDataEntry : public Resource {
	GDCLASS(VendorItemDataEntry, Resource);

public:
	Ref<ItemTemplate> get_item();
	void set_item(Ref<ItemTemplate> item);

	int get_item_price() const;
	void set_item_price(int value);

	int get_item_count() const;
	void set_item_count(int value);

	int get_item_spawn_time() const;
	void set_item_spawn_time(int time);

	VendorItemDataEntry();
	~VendorItemDataEntry();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
	int _item_price;
	int _item_count;
	int _item_spawn_time;
};

#endif
