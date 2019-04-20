#ifndef CRAFT_DATA_ATTRIBUTE_HELPER_H
#define CRAFT_DATA_ATTRIBUTE_HELPER_H

#include "core/resource.h"
#include "item_template.h"

class CraftDataAttributeHelper : public Resource {
	GDCLASS(CraftDataAttributeHelper, Reference);

public:
	Ref<ItemTemplate> get_item();
	void set_item(Ref<ItemTemplate> value);
	int get_count();
	void set_count(int value);

	CraftDataAttributeHelper(Ref<ItemTemplate> item, int count);
	CraftDataAttributeHelper();
	~CraftDataAttributeHelper();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
	int _count;

#if ENTITY_MEM_TOOLS
	static int allocs;
#endif
};

#endif
