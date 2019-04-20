#include "item_instance.h"

int ItemInstance::get_item_id() {
	return _item_id;
}

void ItemInstance::set_item_id(int value) {
	_item_id = value;
}

int ItemInstance::get_count() {
	return _count;
}

void ItemInstance::set_count(int value) {
	_count = value;
}

int ItemInstance::get_slot_id() {
	return _slot_id;
}

void ItemInstance::set_slot_id(int value) {
	_slot_id = value;
}

ItemInstance::ItemInstance() {
}

ItemInstance::ItemInstance(int _item_id) {
	set_item_id(_item_id);
	_count = 1;
}

ItemInstance::ItemInstance(int _item_id, int count) {
	set_item_id(_item_id);
	set_count(count);
}

void ItemInstance::_bind_methods() {
}

