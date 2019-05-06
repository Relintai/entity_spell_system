#include "bag_slot.h"

Ref<ItemInstance> BagSlot::get_item() {
	return _item;
}

void BagSlot::set_item(Ref<ItemInstance> item) {
	_item = Ref<ItemInstance>(item);
}

int BagSlot::get_count() {
	return _count;
}

void BagSlot::set_count(int value) {
	_count = value;
}

int BagSlot::get_slot_id() {
	return _slot_index;
}

void BagSlot::set_slot_id(int index) {
	_slot_index = index;
}

BagSlot::BagSlot() {
    _count = 0;
}

BagSlot::BagSlot(Ref<ItemInstance> item) {
	_item = item;
	_count = 1;
}

BagSlot::BagSlot(Ref<ItemInstance> item, int count) {
	_item = item;
	_count = count;
}

void BagSlot::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_item"), &BagSlot::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &BagSlot::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "set_item", "get_item");
    
    ClassDB::bind_method(D_METHOD("get_count"), &BagSlot::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &BagSlot::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");
    
    ClassDB::bind_method(D_METHOD("get_slot_id"), &BagSlot::get_slot_id);
	ClassDB::bind_method(D_METHOD("set_slot_id", "value"), &BagSlot::set_slot_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_id"), "set_slot_id", "get_slot_id");
}

