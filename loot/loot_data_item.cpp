#include "loot_data_item.h"

Ref<ItemTemplate> LootDataItem::get_item() const {
	return _item;
}
void LootDataItem::set_item(const Ref<ItemTemplate> item) {
	_item = item;
}

void LootDataItem::_get_loot(Array into) {
	if (_item.is_valid()) {
		Math::randomize();

		float val = Math::randf() * 100.0;

		if (val < get_chance()) {
			into.append(_item);
		}
	}
}

LootDataItem::LootDataItem() {
}

void LootDataItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_loot", "into"), &LootDataItem::_get_loot);

	ClassDB::bind_method(D_METHOD("get_item"), &LootDataItem::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &LootDataItem::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");
}
