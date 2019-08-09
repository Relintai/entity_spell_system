#ifndef LOOT_DATA_ITEM_H
#define LOOT_DATA_ITEM_H

#include "core/math/math_funcs.h"

#include "loot_data_base.h"


class LootDataItem : public LootDataBase {
	GDCLASS(LootDataItem, LootDataBase);

public:
	Ref<ItemTemplate> get_item() const;
	void set_item(const Ref<ItemTemplate> item);

	void _get_loot(Array into);

	LootDataItem();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
};

#endif
