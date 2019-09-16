#include "item_container_data_entry.h"

#include "../../data/item_template.h"

Ref<ItemTemplate> ItemContainerDataEntry::get_item() {
    return _item;
}
void ItemContainerDataEntry::set_item(Ref<ItemTemplate> item) {
    _item = item;
}

int ItemContainerDataEntry::get_item_count() const {
    return _item_count;
}
void ItemContainerDataEntry::set_item_count(int value) {
    _item_count = value;
}

ItemContainerDataEntry::ItemContainerDataEntry() {
    _item_count = 0;
}
ItemContainerDataEntry::~ItemContainerDataEntry() {

}

void ItemContainerDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &ItemContainerDataEntry::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &ItemContainerDataEntry::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");
    
    ClassDB::bind_method(D_METHOD("get_item_count"), &ItemContainerDataEntry::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "value"), &ItemContainerDataEntry::set_item_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");
}
