#include "item_instance.h"

#include "item_template.h"


Ref<ItemTemplate> ItemInstance::get_item_template() const {
	return _item_template;
}
void ItemInstance::set_item_template(const Ref<ItemTemplate> value) {
	_item_template = value;
}

Ref<ItemStatModifier> ItemInstance::get_item_stat_modifier(int index) {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), Ref<ItemStatModifier>());

	return _modifiers.get(index);
}
void ItemInstance::add_item_stat_modifier(Ref<ItemStatModifier> modifier) {
	_modifiers.push_back(modifier);
}
void ItemInstance::remove_item_stat_modifier(int index) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.remove(index);
}
void ItemInstance::clear_item_stat_modifiers() {
	_modifiers.clear();
}
int ItemInstance::get_item_stat_modifier_count() {
	return _modifiers.size();
}

int ItemInstance::get_stack_size() {
	return _stack_size;
}
void ItemInstance::set_stack_size(int value) {
	_stack_size = value;
}

ItemInstance::ItemInstance() {
	_stack_size = 1;
}
ItemInstance::~ItemInstance() {
	_modifiers.clear();
}


void ItemInstance::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_item_template"), &ItemInstance::get_item_template);
	ClassDB::bind_method(D_METHOD("set_item_template", "value"), &ItemInstance::set_item_template);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_template", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item_template", "get_item_template");

	ClassDB::bind_method(D_METHOD("get_stack_size"), &ItemInstance::get_stack_size);
	ClassDB::bind_method(D_METHOD("set_stack_size", "count"), &ItemInstance::set_stack_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stack_size"), "set_stack_size", "get_stack_size");

	ClassDB::bind_method(D_METHOD("get_item_stat_modifier", "index"), &ItemInstance::get_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("add_item_stat_modifier", "modifier"), &ItemInstance::add_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("remove_item_stat_modifier", "index"), &ItemInstance::remove_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("clear_item_stat_modifiers"), &ItemInstance::clear_item_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemInstance::get_item_stat_modifier_count);
}
