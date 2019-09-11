#include "container_item_data.h"

#include "../../data/item_template.h"

Ref<ItemTemplate> ContainerItemData::get_item() {
    return _item;
}
void ContainerItemData::set_item(Ref<ItemTemplate> item) {
    _item = item;
}

int ContainerItemData::get_item_count() const {
    return _item_count;
}
void ContainerItemData::set_item_count(int value) {
    _item_count = value;
}

ContainerItemData::ContainerItemData() {
    _item_count = 0;
}
ContainerItemData::~ContainerItemData() {
}

void ContainerItemData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &ContainerItemData::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &ContainerItemData::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");
    
    ClassDB::bind_method(D_METHOD("get_item_count"), &ContainerItemData::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "value"), &ContainerItemData::set_item_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");
}
