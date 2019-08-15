#include "bag.h"

#include "../data/item_template.h"
#include "../data/item_instance.h"

int Bag::get_allowed_item_types() const {
	return _allowed_item_types;
}

void Bag::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

/*
bool Bag::add_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!has_method("_add_item"), false);
    
    return call("_add_item", item);
}


Ref<ItemInstance> Bag::get_item(const int index) {
	ERR_FAIL_COND_V(!has_method("_get_item"), Ref<ItemInstance>(NULL));
    
    return call("_get_item", index);
}

Ref<ItemInstance> Bag::remove_item(const int index) {
	ERR_FAIL_COND_V(!has_method("_remove_item"), Ref<ItemInstance>(NULL));
    
    return call("_remove_item", index);
}

void Bag::swap_items(const int item1_index, const int item2_index) {
    ERR_FAIL_COND(!has_method("_swap_items"));
    
    call("_swap_items", item1_index, item2_index);
}

bool Bag::can_add_item(const Ref<ItemInstance> item) {
    ERR_FAIL_COND_V(!has_method("_can_add_item"), false);
    
    return call("_can_add_item", item);
}

int Bag::get_item_count() {
	ERR_FAIL_COND_V(!has_method("_get_item_count"), 0);
    
    return call("_get_item_count");
}


int Bag::get_size() {
	ERR_FAIL_COND_V(!has_method("_get_size"), 0);
    
    return call("_get_size");
}

void Bag::set_size(const int size) {
	ERR_FAIL_COND(!has_method("_set_size"));
    
    call("_set_size");
}


bool Bag::is_full() {
    ERR_FAIL_COND_V(!has_method("_is_full"), true);
    
    return call("_is_full");
}
*/
Bag::Bag() {
	_allowed_item_types = 0xFFFFFF;
}

Bag::~Bag() {
}

void Bag::_bind_methods() {
    ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
    
	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Bag::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Bag::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");
	/*
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "could_add"), "_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_get_item", PropertyInfo(Variant::INT, "index")));
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_remove_item", PropertyInfo(Variant::INT, "index")));
    BIND_VMETHOD(MethodInfo("_swap_items", PropertyInfo(Variant::INT, "item1_index"), PropertyInfo(Variant::INT, "item2_index")));
    
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_can_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
    
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "count"), "_get_item_count"));
    
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "size"), "_get_size"));
    BIND_VMETHOD(MethodInfo("_set_size", PropertyInfo(Variant::INT, "size")));
    
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "full"), "_is_full"));
    
	ClassDB::bind_method(D_METHOD("add_item", "item"), &Bag::add_item);
	ClassDB::bind_method(D_METHOD("get_item", "index"), &Bag::get_item);
	ClassDB::bind_method(D_METHOD("remove_item", "index"), &Bag::remove_item);
    ClassDB::bind_method(D_METHOD("swap_items", "item1_index", "item2_index"), &Bag::swap_items);

    ClassDB::bind_method(D_METHOD("can_add_item", "item"), &Bag::can_add_item);
    
	ClassDB::bind_method(D_METHOD("get_item_count"), &Bag::get_item_count);
	
	ClassDB::bind_method(D_METHOD("get_size"), &Bag::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Bag::set_size);
    
    ClassDB::bind_method(D_METHOD("is_full"), &Bag::is_full);*/
}
