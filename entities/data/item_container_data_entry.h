#ifndef CONTAINER_ITEM_DATA_H
#define CONTAINER_ITEM_DATA_H

#include "core/resource.h"

class ItemTemplate;

class ItemContainerDataEntry : public Resource {
	GDCLASS(ItemContainerDataEntry, Resource);

public:
    Ref<ItemTemplate> get_item();
	void set_item(Ref<ItemTemplate> item);
    
    int get_item_count() const;
	void set_item_count(int value);

	ItemContainerDataEntry();
	~ItemContainerDataEntry();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
    int _item_count;
};

#endif
