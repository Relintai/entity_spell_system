#include "item_instance.h"

#include "item_template.h"
#include "../inventory/bag.h"

int ItemInstance::get_id() {
	return _id;
}

void ItemInstance::set_id(int value) {
	_id = value;
}

int ItemInstance::get_inventory_position_x() const {
	return _inventory_position_x;
}
void ItemInstance::set_inventory_position_x(const int value) {
	_inventory_position_x = value;
}
	
int ItemInstance::get_inventory_position_y() const {
	return _inventory_position_y;
}
void ItemInstance::set_inventory_position_y(const int value) {
	_inventory_position_y = value;
}

Ref<Bag> ItemInstance::get_bag() const {
	if (_bag == NULL) {
		return Ref<Bag>(NULL);
	}
	
	return *_bag;
}

void ItemInstance::set_bag(const Ref<Bag> bag) {
	if (_bag == NULL) {
		_bag = memnew(Ref<Bag>(NULL));
	} else {
		_bag->unref();
		(*_bag) = bag;
	}
}

Ref<ItemTemplate> ItemInstance::get_item_template() const {
	return _item_template;
}
void ItemInstance::set_item_template(const Ref<ItemTemplate> value) {
	_item_template = value;
}

Ref<ItemStatModifier> ItemInstance::get_item_stat_modifier(int index) {
	return _modifiers[index];
}
/*
void ItemInstance::set_item_stat_modifier(int index, ItemStatModifier modifier) {
	_modifiers[index] = modifier;
}*/

int ItemInstance::get_item_stat_modifier_count() {
	return _modifier_count;
}

void ItemInstance::set_item_stat_modifier_count(int value) {
	_modifier_count = value;
}

Stat::StatId ItemInstance::get_item_stat_id(int index) {
	return _modifiers[index]->get_stat_id();
}

void ItemInstance::set_item_stat_id(int index, Stat::StatId value) {
	_modifiers[index]->set_stat_id(value);
}

float ItemInstance::get_item_base_mod(int index) {
	return _modifiers[index]->get_base_mod();
}

void ItemInstance::set_item_base_mod(int index, float value) {
	_modifiers[index]->set_base_mod(value);
}

float ItemInstance::get_item_bonus_mod(int index) {
	return _modifiers[index]->get_bonus_mod();
}

void ItemInstance::set_item_bonus_mod(int index, float value) {
	_modifiers[index]->set_bonus_mod(value);
}

float ItemInstance::get_percent_mod(int index) {
	return _modifiers[index]->get_percent_mod();
}

void ItemInstance::set_percent_mod(int index, float value) {
	_modifiers[index]->set_percent_mod(value);
}

int ItemInstance::get_count() {
	return _count;
}

void ItemInstance::set_count(int value) {
	_count = value;
}

ItemInstance::ItemInstance() {
	_id = 0;
	
	_bag = NULL;
	
	_count = 0;
	
	_modifier_count = 0;

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		_modifiers[i] = Ref<ItemStatModifier>(memnew(ItemStatModifier()));
	}
}

ItemInstance::~ItemInstance() {
	if (_bag != NULL) {
		_bag->unref();

		memdelete(_bag);
	}
}

void ItemInstance::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("Modifiers_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _modifier_count) {
			property.usage = 0;
		}
	}
}


void ItemInstance::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_id"), &ItemInstance::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "count"), &ItemInstance::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
	
	ClassDB::bind_method(D_METHOD("get_inventory_position_x"), &ItemInstance::get_inventory_position_x);
	ClassDB::bind_method(D_METHOD("set_inventory_position_x", "value"), &ItemInstance::set_inventory_position_x);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "inventory_position_x"), "set_inventory_position_x", "get_inventory_position_x");
	
	ClassDB::bind_method(D_METHOD("get_inventory_position_y"), &ItemInstance::get_inventory_position_y);
	ClassDB::bind_method(D_METHOD("set_inventory_position_y", "value"), &ItemInstance::set_inventory_position_y);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "inventory_position_y"), "set_inventory_position_y", "get_inventory_position_y");
	
	ClassDB::bind_method(D_METHOD("get_bag"), &ItemInstance::get_bag);
	ClassDB::bind_method(D_METHOD("set_bag", "bag"), &ItemInstance::set_bag);
	
	ClassDB::bind_method(D_METHOD("get_item_template"), &ItemInstance::get_item_template);
	ClassDB::bind_method(D_METHOD("set_item_template", "value"), &ItemInstance::set_item_template);

	ClassDB::bind_method(D_METHOD("get_count"), &ItemInstance::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "count"), &ItemInstance::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "ount"), "set_count", "get_count");

	ClassDB::bind_method(D_METHOD("get_item_stat_modifier", "index"), &ItemInstance::get_item_stat_modifier);
	//ClassDB::bind_method(D_METHOD("set_item_stat_modifier", "index", "value"), &ItemInstance::set_item_stat_modifier);

	//StatMods Property binds
	ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemInstance::get_item_stat_modifier_count);
	ClassDB::bind_method(D_METHOD("set_item_stat_modifier_count", "count"), &ItemInstance::set_item_stat_modifier_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "set_item_stat_modifier_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ITEM_STAT_MOD), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_item_stat_modifier_count", "get_item_stat_modifier_count");

	ClassDB::bind_method(D_METHOD("get_item_stat_id", "index"), &ItemInstance::get_item_stat_id);
	ClassDB::bind_method(D_METHOD("set_item_stat_id", "index", "value"), &ItemInstance::set_item_stat_id);

	ClassDB::bind_method(D_METHOD("get_item_base_mod", "index"), &ItemInstance::get_item_base_mod);
	ClassDB::bind_method(D_METHOD("set_item_base_mod", "index", "value"), &ItemInstance::set_item_base_mod);

	ClassDB::bind_method(D_METHOD("get_item_bonus_mod", "index"), &ItemInstance::get_item_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_item_bonus_mod", "index", "value"), &ItemInstance::set_item_bonus_mod);

	ClassDB::bind_method(D_METHOD("get_percent_mod", "index"), &ItemInstance::get_percent_mod);
	ClassDB::bind_method(D_METHOD("set_percent_mod", "index", "value"), &ItemInstance::set_percent_mod);

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "Modifiers_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_stat_id", "get_item_stat_id", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/item_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_base_mod", "get_item_base_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/item_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_bonus_mod", "get_item_bonus_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_percent_mod", "get_percent_mod", i);
	}
}
