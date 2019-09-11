#include "vendor_item_data.h"

#include "../../data/item_template.h"

Ref<ItemTemplate> VendorItemData::get_item() {
    return _item;
}
void VendorItemData::set_item(Ref<ItemTemplate> item) {
    _item = item;
}
    
int VendorItemData::get_item_price() const {
    return _item_price;
}
void VendorItemData::set_item_price(int value) {
    _item_price = value;
}
    
int VendorItemData::get_item_count() const {
    return _item_count;
}
void VendorItemData::set_item_count(int value) {
    _item_count = value;
}
    
int VendorItemData::get_item_spawn_time() const {
    return _item_spawn_time;
}
void VendorItemData::set_item_spawn_time(int value) {
    _item_spawn_time = value;
}
    
VendorItemData::VendorItemData() {
    _item_price = 0;
    _item_count = 0;
    _item_spawn_time = 0;
}
VendorItemData::~VendorItemData() {
}

void VendorItemData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &VendorItemData::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &VendorItemData::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");
    
    ClassDB::bind_method(D_METHOD("get_item_price"), &VendorItemData::get_item_price);
	ClassDB::bind_method(D_METHOD("set_item_price", "value"), &VendorItemData::set_item_price);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_price"), "set_item_price", "get_item_price");
    
    ClassDB::bind_method(D_METHOD("get_item_count"), &VendorItemData::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "value"), &VendorItemData::set_item_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");
    
    ClassDB::bind_method(D_METHOD("get_item_spawn_time"), &VendorItemData::get_item_spawn_time);
	ClassDB::bind_method(D_METHOD("set_item_spawn_time", "value"), &VendorItemData::set_item_spawn_time);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_spawn_time"), "set_item_spawn_time", "get_item_spawn_time");
}
