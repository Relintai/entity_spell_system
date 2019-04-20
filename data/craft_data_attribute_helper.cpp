#include "craft_data_attribute_helper.h"

#if ENTITY_MEM_TOOLS
int CraftDataAttributeHelper::allocs = 0;
#endif

Ref<ItemTemplate> CraftDataAttributeHelper::get_item() {
	return _item;
}

void CraftDataAttributeHelper::set_item(Ref<ItemTemplate> value) {
	_item = value;
}

int CraftDataAttributeHelper::get_count() {
	return _count;
}

void CraftDataAttributeHelper::set_count(int value) {
	_count = value;
}

CraftDataAttributeHelper::CraftDataAttributeHelper(Ref<ItemTemplate> item, int count) {
	set_item(item);
	set_count(count);

#if ENTITY_MEM_TOOLS
	CraftDataAttributeHelper::allocs++;
	print_error("CraftDataAttributeHelper alloc " + String::num(CraftDataAttributeHelper::allocs));
#endif
}

CraftDataAttributeHelper::CraftDataAttributeHelper() {
	set_count(0);

#if ENTITY_MEM_TOOLS
	CraftDataAttributeHelper::allocs++;
	print_error("CraftDataAttributeHelper alloc " + String::num(CraftDataAttributeHelper::allocs));
#endif
}

CraftDataAttributeHelper::~CraftDataAttributeHelper() {
#if ENTITY_MEM_TOOLS
	CraftDataAttributeHelper::allocs--;
	print_error("CraftDataAttributeHelper dealloc " + String::num(CraftDataAttributeHelper::allocs));
#endif
}

void CraftDataAttributeHelper::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &CraftDataAttributeHelper::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &CraftDataAttributeHelper::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_count"), &CraftDataAttributeHelper::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &CraftDataAttributeHelper::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");
}
