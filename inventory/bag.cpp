#include "bag.h"

Ref<BagSlot> Bag::get_slot(int index) {
	ERR_FAIL_INDEX_V(index, _slots->size(), Ref<BagSlot>(NULL));

	return (_slots->get(index));
}

Ref<BagSlot> Bag::get_and_remove_slot(int index) {
	ERR_FAIL_INDEX_V(index, _slots->size(), Ref<BagSlot>(NULL));

	Ref<BagSlot> slot = _slots->get(index);

	_slots->set(index, Ref<BagSlot>(memnew(BagSlot())));
    
    return slot;
}

int Bag::get_slot_count() {
	return _slots->size();
}

void Bag::set_slot_count(int count) {
	ERR_FAIL_COND(_slots->size() != 0);

	for (int i = 0; i < count; ++i) {
		_slots->push_back(memnew(BagSlot()));
	}
}

bool Bag::try_to_add_item(Ref<ItemInstance> item, int count) {
	ERR_FAIL_COND_V(!item.is_valid(), false);

	for (int i = 0; i < _slots->size(); ++i) {
		Ref<BagSlot> slot = _slots->get(i);

		if (!slot->has_item()) {
			slot->set_item(item);
			slot->set_count(count);

			return true;
		}
	}

	return false;
}

bool Bag::add_item_to_slot(Ref<ItemInstance> item, int slot_index, int count) {
	ERR_FAIL_COND_V(!item.is_valid(), false);

	ERR_FAIL_INDEX_V(slot_index, _slots->size(), false);

	Ref<BagSlot> slot = _slots->get(slot_index);

	ERR_FAIL_COND_V(!slot.is_valid(), false);

	if (slot->has_item()) {
		return false;
	}

	slot->set_item_count(item, count);

	return true;
}

Bag::Bag() {
	_slots = memnew(Vector<Ref<BagSlot> >());
}

Bag::~Bag() {
	_slots->clear();

	memdelete(_slots);
}

void Bag::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_slot", "index"), &Bag::get_slot);
	ClassDB::bind_method(D_METHOD("get_and_remove_slot", "index"), &Bag::get_and_remove_slot);
	ClassDB::bind_method(D_METHOD("get_slot_count"), &Bag::get_slot_count);
	ClassDB::bind_method(D_METHOD("set_slot_count", "count"), &Bag::set_slot_count);
	ClassDB::bind_method(D_METHOD("try_to_add_item", "item", "count"), &Bag::try_to_add_item, DEFVAL(1));
	ClassDB::bind_method(D_METHOD("add_item_to_slot", "item", "slot_index", "count"), &Bag::add_item_to_slot, DEFVAL(1));
}
