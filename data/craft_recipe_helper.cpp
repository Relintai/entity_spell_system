#include "craft_recipe_helper.h"

Ref<ItemTemplate> CraftRecipeHelper::get_item() {
	return _item;
}

void CraftRecipeHelper::set_item(Ref<ItemTemplate> value) {
	_item = value;
}

int CraftRecipeHelper::get_count() {
	return _count;
}

void CraftRecipeHelper::set_count(int value) {
	_count = value;
}

CraftRecipeHelper::CraftRecipeHelper(Ref<ItemTemplate> item, int count) {
	set_item(item);
	set_count(count);
}

CraftRecipeHelper::CraftRecipeHelper() {
	set_count(0);
}

CraftRecipeHelper::~CraftRecipeHelper() {
}

void CraftRecipeHelper::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &CraftRecipeHelper::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &CraftRecipeHelper::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_count"), &CraftRecipeHelper::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &CraftRecipeHelper::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");
}
