#include "item_data_instance.h"

#if ENTITY_MEM_TOOLS
int ItemDataInstance::allocs = 0;
#endif

int ItemDataInstance::get_id() {
	return _id;
}

void ItemDataInstance::set_id(int value) {
	_id = value;
}

String ItemDataInstance::get_name_key() {
	return _name_key;
}

void ItemDataInstance::set_name_key(String value) {
	_name_key = value;
}

ItemEnums::ItemType ItemDataInstance::get_item_type() {
	return _item_type;
}

void ItemDataInstance::set_item_type(ItemEnums::ItemType value) {
	_item_type = value;
}

ItemEnums::ItemSubtype ItemDataInstance::get_item_sub_type() {
	return _item_sub_type;
}

void ItemDataInstance::set_item_sub_type(ItemEnums::ItemSubtype value) {
	_item_sub_type = value;
}

ItemEnums::ItemSubSubtype ItemDataInstance::get_item_sub_sub_type() {
	return _item_sub_sub_type;
}

void ItemDataInstance::set_item_sub_sub_type(ItemEnums::ItemSubSubtype value) {
	_item_sub_sub_type = value;
}

ItemEnums::ItemRarity ItemDataInstance::get_rarity() {
	return _rarity;
}

void ItemDataInstance::set_rarity(ItemEnums::ItemRarity value) {
	_rarity = value;
}

int ItemDataInstance::get_spell_id() {
	return _spell_id;
}

void ItemDataInstance::set_spell_id(int value) {
	_spell_id = value;
}

float ItemDataInstance::get_scale_x() {
	return _scale_x;
}

void ItemDataInstance::set_scale_x(float value) {
	_scale_x = value;
}

float ItemDataInstance::get_scale_y() {
	return _scale_y;
}

void ItemDataInstance::set_scale_y(float value) {
	_scale_y = value;
}

float ItemDataInstance::get_scale_z() {
	return _scale_z;
}

void ItemDataInstance::set_scale_z(float value) {
	_scale_z = value;
}

Ref<Texture> ItemDataInstance::get_icon() {
	return _icon;
}

void ItemDataInstance::set_icon(Ref<Texture> value) {
	_icon = value;
}

int ItemDataInstance::get_animator_weapon_type() {
	if (_item_sub_type == ItemEnums::ITEM_SUB_TYPE_SWORD) {
		return 1;
	}
	if (_item_sub_type == ItemEnums::ITEM_SUB_TYPE_BOW) {
		return 2;
	}
	if (_item_sub_type == ItemEnums::ITEM_SUB_TYPE_AXE) {
		return 3;
	}
	return 0;
}

Ref<ItemStatModifier> ItemDataInstance::get_item_stat_modifier(int index) {
	return _modifiers[index];
}
/*
void ItemDataInstance::set_item_stat_modifier(int index, ItemStatModifier modifier) {
	_modifiers[index] = modifier;
}*/

int ItemDataInstance::get_item_stat_modifier_count() {
	return _modifier_count;
}

void ItemDataInstance::set_item_stat_modifier_count(int value) {
	_modifier_count = value;
}

Stat::StatId ItemDataInstance::get_item_stat_id(int index) {
	return _modifiers[index]->get_stat_id();
}

void ItemDataInstance::set_item_stat_id(int index, Stat::StatId value) {
	_modifiers[index]->set_stat_id(value);
}

float ItemDataInstance::get_item_base_mod(int index) {
	return _modifiers[index]->get_base_mod();
}

void ItemDataInstance::set_item_base_mod(int index, float value) {
	_modifiers[index]->set_base_mod(value);
}

float ItemDataInstance::get_item_bonus_mod(int index) {
	return _modifiers[index]->get_bonus_mod();
}

void ItemDataInstance::set_item_bonus_mod(int index, float value) {
	_modifiers[index]->set_bonus_mod(value);
}

float ItemDataInstance::get_percent_mod(int index) {
	return _modifiers[index]->get_percent_mod();
}

void ItemDataInstance::set_percent_mod(int index, float value) {
	_modifiers[index]->set_percent_mod(value);
}

ItemDataInstance::ItemDataInstance() {
	_id = 0;
	_name_key = "";
	_item_type = ItemEnums::ITEM_TYPE_NONE;
	_item_sub_type = ItemEnums::ITEM_SUB_TYPE_NONE;
	_item_sub_sub_type = ItemEnums::ITEM_SUB_SUB_TYPE_NONE;
	_rarity = ItemEnums::ITEM_RARITY_UNCOMMON;
	_spell_id = 0;
	_scale_x = 0;
	_scale_y = 0;
	_scale_z = 0;
	_modifier_count = 0;

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		_modifiers[i] = Ref<ItemStatModifier>(memnew(ItemStatModifier()));
	}

#if ENTITY_MEM_TOOLS
	ItemDataInstance::allocs++;
	print_error("ItemDataInstance alloc " + String::num(ItemDataInstance::allocs));
#endif
}

ItemDataInstance::~ItemDataInstance() {
#if ENTITY_MEM_TOOLS
	ItemDataInstance::allocs--;
	print_error("ItemDataInstance dealloc " + String::num(ItemDataInstance::allocs));
#endif
}

void ItemDataInstance::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("Modifiers_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _modifier_count) {
			property.usage = 0;
		}
	}
}


void ItemDataInstance::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_id"), &ItemDataInstance::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "count"), &ItemDataInstance::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_name_key"), &ItemDataInstance::get_name_key);
	ClassDB::bind_method(D_METHOD("set_name_key", "count"), &ItemDataInstance::set_name_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name_key"), "set_name_key", "get_name_key");

	ClassDB::bind_method(D_METHOD("get_item_type"), &ItemDataInstance::get_item_type);
	ClassDB::bind_method(D_METHOD("set_item_type", "count"), &ItemDataInstance::set_item_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_TYPE), "set_item_type", "get_item_type");

	ClassDB::bind_method(D_METHOD("get_item_sub_type"), &ItemDataInstance::get_item_sub_type);
	ClassDB::bind_method(D_METHOD("set_item_sub_type", "count"), &ItemDataInstance::set_item_sub_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_sub_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_SUB_TYPE), "set_item_sub_type", "get_item_sub_type");

	ClassDB::bind_method(D_METHOD("get_item_sub_sub_type"), &ItemDataInstance::get_item_sub_sub_type);
	ClassDB::bind_method(D_METHOD("set_item_sub_sub_type", "count"), &ItemDataInstance::set_item_sub_sub_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_sub_sub_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_SUB_SUB_TYPE), "set_item_sub_sub_type", "get_item_sub_sub_type");

	ClassDB::bind_method(D_METHOD("get_rarity"), &ItemDataInstance::get_rarity);
	ClassDB::bind_method(D_METHOD("set_rarity", "count"), &ItemDataInstance::set_rarity);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rarity", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_RARITY), "set_rarity", "get_rarity");

	ClassDB::bind_method(D_METHOD("get_spell_id"), &ItemDataInstance::get_spell_id);
	ClassDB::bind_method(D_METHOD("set_spell_id", "count"), &ItemDataInstance::set_spell_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_id"), "set_spell_id", "get_spell_id");

	ClassDB::bind_method(D_METHOD("get_scale_x"), &ItemDataInstance::get_scale_x);
	ClassDB::bind_method(D_METHOD("set_scale_x", "count"), &ItemDataInstance::set_scale_x);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_x"), "set_scale_x", "get_scale_x");

	ClassDB::bind_method(D_METHOD("get_scale_y"), &ItemDataInstance::get_scale_y);
	ClassDB::bind_method(D_METHOD("set_scale_y", "count"), &ItemDataInstance::set_scale_y);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_y"), "set_scale_y", "get_scale_y");

	ClassDB::bind_method(D_METHOD("get_scale_z"), &ItemDataInstance::get_scale_z);
	ClassDB::bind_method(D_METHOD("set_scale_z", "count"), &ItemDataInstance::set_scale_z);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_z"), "set_scale_z", "get_scale_z");

	ClassDB::bind_method(D_METHOD("get_icon"), &ItemDataInstance::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "count"), &ItemDataInstance::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_animator_weapon_type"), &ItemDataInstance::get_animator_weapon_type);

	//ClassDB::bind_method(D_METHOD("get_item_stat_modifier", "index"), &ItemDataInstance::get_item_stat_modifier);
	//ClassDB::bind_method(D_METHOD("set_item_stat_modifier", "index", "value"), &ItemDataInstance::set_item_stat_modifier);

	//StatMods Property binds
	ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemDataInstance::get_item_stat_modifier_count);
	ClassDB::bind_method(D_METHOD("set_item_stat_modifier_count", "count"), &ItemDataInstance::set_item_stat_modifier_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "set_item_stat_modifier_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ITEM_STAT_MOD), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_item_stat_modifier_count", "get_item_stat_modifier_count");

	ClassDB::bind_method(D_METHOD("get_item_stat_id", "index"), &ItemDataInstance::get_item_stat_id);
	ClassDB::bind_method(D_METHOD("set_item_stat_id", "index", "value"), &ItemDataInstance::set_item_stat_id);

	ClassDB::bind_method(D_METHOD("get_item_base_mod", "index"), &ItemDataInstance::get_item_base_mod);
	ClassDB::bind_method(D_METHOD("set_item_base_mod", "index", "value"), &ItemDataInstance::set_item_base_mod);

	ClassDB::bind_method(D_METHOD("get_item_bonus_mod", "index"), &ItemDataInstance::get_item_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_item_bonus_mod", "index", "value"), &ItemDataInstance::set_item_bonus_mod);

	ClassDB::bind_method(D_METHOD("get_percent_mod", "index"), &ItemDataInstance::get_percent_mod);
	ClassDB::bind_method(D_METHOD("set_percent_mod", "index", "value"), &ItemDataInstance::set_percent_mod);

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "Modifiers_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_stat_id", "get_item_stat_id", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/item_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_base_mod", "get_item_base_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/item_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_bonus_mod", "get_item_bonus_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_percent_mod", "get_percent_mod", i);
	}
}
