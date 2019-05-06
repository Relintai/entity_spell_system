#include "bag.h"

Ref<BagSlot> Bag::get_slot(int index) {
    ERR_FAIL_INDEX_V(index, _slots->size(), Ref<BagSlot>(NULL));
    
    return(_slots->get(index));
}

Ref<BagSlot> Bag::get_and_remove_slot(int index) {
    ERR_FAIL_INDEX_V(index, _slots->size(), Ref<BagSlot>(NULL));
    
    Ref<BagSlot> slot = _slots->get(index);
    
    _slots->set(index, Ref<BagSlot>(memnew(BagSlot()));
    
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

bool Bag::try_to_add_item(Ref<ItemInstance> item, int count = 1) {
    ERR_FAIL_COND_V(!item.is_valid(), false);
    
    for (int i = 0; i < _slots->size(); ++i) {
        Ref<BagSlot> slot = _slots->get(i); 
        //cont
    }
}

bool Bag::add_item_to_slot(Ref<ItemInstance> item, int slot_index) {
}


Bag::Bag() {
     _slots = memnew(Vector<Ref<BagSlot> >());
}

Bag::~Bag() {
    _slots->clear();
    
     memdelete(_slots);
}

void Bag::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_item"), &Bag::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &Bag::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "set_item", "get_item");
    
    ClassDB::bind_method(D_METHOD("get_count"), &Bag::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &Bag::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");
    
    ClassDB::bind_method(D_METHOD("get_slot_id"), &Bag::get_slot_id);
	ClassDB::bind_method(D_METHOD("set_slot_id", "value"), &Bag::set_slot_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_id"), "set_slot_id", "get_slot_id");
}

