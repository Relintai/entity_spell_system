#include "item_template.h"

#include "aura.h"
#include "spell.h"

int ItemTemplate::get_id() {
    return _id;
}

void ItemTemplate::set_id(int value) {
    _id = value;
}

String ItemTemplate::get_name_key() {
    return _name_key;
}

void ItemTemplate::set_name_key(String value) {
    _name_key = value;
}


ItemEnums::ItemType ItemTemplate::get_item_type() {
    return _item_type;
}

void ItemTemplate::set_item_type(ItemEnums::ItemType value) {
    _item_type = value;
}

ItemEnums::ItemSubtype ItemTemplate::get_item_sub_type() {
    return _item_sub_type;
}

void ItemTemplate::set_item_sub_type(ItemEnums::ItemSubtype value) {
    _item_sub_type = value;
}

ItemEnums::ItemSubSubtype ItemTemplate::get_item_sub_sub_type() {
    return _item_sub_sub_type;
}

void ItemTemplate::set_item_sub_sub_type(ItemEnums::ItemSubSubtype value) {
    _item_sub_sub_type = value;
}

int ItemTemplate::get_rarity() {
    return _rarity;
}

void ItemTemplate::set_rarity(int value) {
    _rarity = value;
}


Ref<Texture> ItemTemplate::get_icon() {
    return _icon;
}

void ItemTemplate::set_icon(Ref<Texture> value) {
    _icon = value;
}


float ItemTemplate::get_scale_x() {
    return _scale_x;
}

void ItemTemplate::set_scale_x(float value) {
    _scale_x = value;
}

float ItemTemplate::get_scale_y() {
    return _scale_y;
}

void ItemTemplate::set_scale_y(float value) {
    _scale_y = value;
}

float ItemTemplate::get_scale_z() {
    return _scale_z;
}

void ItemTemplate::set_scale_z(float value) {
    _scale_z = value;
}


Ref<Spell> ItemTemplate::get_spell() {
	if (_spell)
		return (*_spell);

	return Ref<Spell>(NULL);
}

void ItemTemplate::set_spell(Ref<Spell> spell) {
	if (_spell)
		memdelete(_spell);

	_spell = memnew(Ref<Spell>(spell));
}


Ref<Aura> ItemTemplate::get_aura(int index) {
	if (_auras[index])
		return (*_auras[index]);

	return Ref<Aura>(NULL);
}

void ItemTemplate::set_aura(int index, Ref<Aura> aura) {
	if (_auras[index])
		memdelete(_auras[index]);

	_auras[index] = memnew(Ref<Aura>(aura));
}


int ItemTemplate::get_item_stat_modifier_count() {
    return _modifier_count;
}

void ItemTemplate::set_item_stat_modifier_count(int value) {
    _modifier_count = value;
}

Stat::StatId ItemTemplate::get_item_stat_id(int index) {
    return _modifiers[index]->get_stat_id();
}

void ItemTemplate::set_item_stat_id(int index, Stat::StatId value) {
    _modifiers[index]->set_stat_id(value);
}

float ItemTemplate::get_item_min_base_mod(int index) {
    return _modifiers[index]->get_min_base_mod();
}

void ItemTemplate::set_item_min_base_mod(int index, float value) {
    _modifiers[index]->set_min_base_mod(value);
}

float ItemTemplate::get_item_max_base_mod(int index) {
    return _modifiers[index]->get_max_base_mod();
}

void ItemTemplate::set_item_max_base_mod(int index, float value) {
    _modifiers[index]->set_max_base_mod(value);
}


float ItemTemplate::get_item_min_bonus_mod(int index) {
    return _modifiers[index]->get_min_bonus_mod();
}

void ItemTemplate::set_item_min_bonus_mod(int index, float value) {
    _modifiers[index]->set_min_bonus_mod(value);
}

float ItemTemplate::get_item_max_bonus_mod(int index) {
    return _modifiers[index]->get_max_bonus_mod();
}

void ItemTemplate::set_item_max_bonus_mod(int index, float value) {
    _modifiers[index]->set_max_bonus_mod(value);
}


float ItemTemplate::get_item_min_percent_mod(int index) {
    return _modifiers[index]->get_min_percent_mod();
}

void ItemTemplate::set_item_min_percent_mod(int index, float value) {
    _modifiers[index]->set_min_percent_mod(value);
}

float ItemTemplate::get_item_max_percent_mod(int index) {
    return _modifiers[index]->get_max_percent_mod();
}

void ItemTemplate::set_item_max_percent_mod(int index, float value) {
    _modifiers[index]->set_max_percent_mod(value);
}


float ItemTemplate::get_item_scaling_factor(int index) {
    return _modifiers[index]->get_scaling_factor();
}

void ItemTemplate::set_item_scaling_factor(int index, float value) {
    _modifiers[index]->set_scaling_factor(value);
}

Ref<ItemTemplateStatModifier> ItemTemplate::get_item_template_stat_modifier(int index) {
    return Ref<ItemTemplateStatModifier>(_modifiers[index]);
}
/*
void ItemTemplate::set_item_stat_modifier(int index, ItemStatModifier modifier) {
	_modifiers[index] = modifier;
}*/


int ItemTemplate::get_animator_weapon_type() {
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


ItemTemplate::ItemTemplate() {
    _id = 0;
    _name_key = "";
    _item_type = ItemEnums::ITEM_TYPE_NONE;
    _item_sub_type = ItemEnums::ITEM_SUB_TYPE_NONE;
    _item_sub_sub_type = ItemEnums::ITEM_SUB_SUB_TYPE_NONE;
    _rarity = ItemEnums::ITEM_RARITY_NONE;

    _scale_x = 0;
    _scale_y = 0;
    _scale_z = 0;
    _modifier_count = 0;

	_spell = NULL;

	for (int i = 0; i < MAX_AURAS; ++i) {
		_auras[i] = NULL;
	}

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		_modifiers[i] = Ref<ItemTemplateStatModifier>(memnew(ItemTemplateStatModifier()));
	}
}

ItemTemplate::~ItemTemplate() {

	if (_spell)
		memdelete(_spell);

	for (int i = 0; i < MAX_AURAS; ++i) {
		if (_auras[i])
			memdelete(_auras[i]);
	}
}

void ItemTemplate::_validate_property(PropertyInfo &property) const {
    String prop = property.name;
    if (prop.begins_with("Modifiers_")) {
        int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
        if (frame >= _modifier_count) {
            property.usage = 0;
        }
    }
}


void ItemTemplate::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_id"), &ItemTemplate::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "count"), &ItemTemplate::set_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ClassDB::bind_method(D_METHOD("get_name_key"), &ItemTemplate::get_name_key);
    ClassDB::bind_method(D_METHOD("set_name_key", "count"), &ItemTemplate::set_name_key);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "name_key"), "set_name_key", "get_name_key");

    ClassDB::bind_method(D_METHOD("get_item_type"), &ItemTemplate::get_item_type);
	ClassDB::bind_method(D_METHOD("set_item_type", "count"), &ItemTemplate::set_item_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_TYPE), "set_item_type", "get_item_type");

	ClassDB::bind_method(D_METHOD("get_item_sub_type"), &ItemTemplate::get_item_sub_type);
	ClassDB::bind_method(D_METHOD("set_item_sub_type", "count"), &ItemTemplate::set_item_sub_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_sub_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_SUB_TYPE), "set_item_sub_type", "get_item_sub_type");

	ClassDB::bind_method(D_METHOD("get_item_sub_sub_type"), &ItemTemplate::get_item_sub_sub_type);
	ClassDB::bind_method(D_METHOD("set_item_sub_sub_type", "count"), &ItemTemplate::set_item_sub_sub_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_sub_sub_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ITEM_SUB_SUB_TYPE), "set_item_sub_sub_type", "get_item_sub_sub_type");

	ClassDB::bind_method(D_METHOD("get_rarity"), &ItemTemplate::get_rarity);
	ClassDB::bind_method(D_METHOD("set_rarity", "count"), &ItemTemplate::set_rarity);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rarity", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_RARITY), "set_rarity", "get_rarity");


	ClassDB::bind_method(D_METHOD("get_icon"), &ItemTemplate::get_icon);
    ClassDB::bind_method(D_METHOD("set_icon", "value"), &ItemTemplate::set_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");



    ClassDB::bind_method(D_METHOD("get_scale_x"), &ItemTemplate::get_scale_x);
    ClassDB::bind_method(D_METHOD("set_scale_x", "count"), &ItemTemplate::set_scale_x);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_x"), "set_scale_x", "get_scale_x");

    ClassDB::bind_method(D_METHOD("get_scale_y"), &ItemTemplate::get_scale_y);
    ClassDB::bind_method(D_METHOD("set_scale_y", "count"), &ItemTemplate::set_scale_y);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_y"), "set_scale_y", "get_scale_y");

    ClassDB::bind_method(D_METHOD("get_scale_z"), &ItemTemplate::get_scale_z);
    ClassDB::bind_method(D_METHOD("set_scale_z", "count"), &ItemTemplate::set_scale_z);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale_z"), "set_scale_z", "get_scale_z");


	ClassDB::bind_method(D_METHOD("get_spell"), &ItemTemplate::get_spell);
    ClassDB::bind_method(D_METHOD("set_spell", "spell"), &ItemTemplate::set_spell);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &ItemTemplate::get_aura);
    ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &ItemTemplate::set_aura);

	for (int i = 0; i < MAX_AURAS; ++i) {
        ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "aura_" + itos(i + 1), PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura", i);
    }

    //StatMods Property binds
    ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemTemplate::get_item_stat_modifier_count);
    ClassDB::bind_method(D_METHOD("set_item_stat_modifier_count", "count"), &ItemTemplate::set_item_stat_modifier_count);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "set_item_stat_modifier_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ITEM_STAT_MOD), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_item_stat_modifier_count", "get_item_stat_modifier_count");

    ClassDB::bind_method(D_METHOD("get_item_stat_id", "index"), &ItemTemplate::get_item_stat_id);
    ClassDB::bind_method(D_METHOD("set_item_stat_id", "index", "value"), &ItemTemplate::set_item_stat_id);

    ClassDB::bind_method(D_METHOD("get_item_min_base_mod", "index"), &ItemTemplate::get_item_min_base_mod);
    ClassDB::bind_method(D_METHOD("set_item_min_base_mod", "index", "value"), &ItemTemplate::set_item_min_base_mod);

	ClassDB::bind_method(D_METHOD("get_item_max_base_mod", "index"), &ItemTemplate::get_item_max_base_mod);
    ClassDB::bind_method(D_METHOD("set_item_max_base_mod", "index", "value"), &ItemTemplate::set_item_max_base_mod);


    ClassDB::bind_method(D_METHOD("get_item_min_bonus_mod", "index"), &ItemTemplate::get_item_min_bonus_mod);
    ClassDB::bind_method(D_METHOD("set_item_min_bonus_mod", "index", "value"), &ItemTemplate::set_item_min_bonus_mod);

	ClassDB::bind_method(D_METHOD("get_item_max_bonus_mod", "index"), &ItemTemplate::get_item_max_bonus_mod);
    ClassDB::bind_method(D_METHOD("set_item_max_bonus_mod", "index", "value"), &ItemTemplate::set_item_max_bonus_mod);


	ClassDB::bind_method(D_METHOD("get_item_min_percent_mod", "index"), &ItemTemplate::get_item_min_percent_mod);
    ClassDB::bind_method(D_METHOD("set_item_min_percent_mod", "index", "value"), &ItemTemplate::set_item_min_percent_mod);

	ClassDB::bind_method(D_METHOD("get_item_max_percent_mod", "index"), &ItemTemplate::get_item_max_percent_mod);
    ClassDB::bind_method(D_METHOD("set_item_max_percent_mod", "index", "value"), &ItemTemplate::set_item_max_percent_mod);


	ClassDB::bind_method(D_METHOD("get_item_scaling_factor", "index"), &ItemTemplate::get_item_scaling_factor);
    ClassDB::bind_method(D_METHOD("set_item_scaling_factor", "index", "value"), &ItemTemplate::set_item_scaling_factor);


    for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
        ADD_PROPERTYI(PropertyInfo(Variant::INT, "Modifiers_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_stat_id", "get_item_stat_id", i);


        ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/min_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_min_base_mod", "get_item_min_base_mod", i);

		 ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/max_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_max_base_mod", "get_item_max_base_mod", i);


        ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/min_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_min_bonus_mod", "get_item_min_bonus_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/max_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_max_bonus_mod", "get_item_max_bonus_mod", i);


		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/min_percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_min_percent_mod", "get_item_min_percent_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/max_percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_max_percent_mod", "get_item_max_percent_mod", i);


		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "Modifiers_" + itos(i) + "/scaling_factor", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_item_scaling_factor", "get_item_scaling_factor", i);
    }

    //ClassDB::bind_method(D_METHOD("get_item_stat_modifier", "index"), &ItemTemplate::get_item_stat_modifier);
    //ClassDB::bind_method(D_METHOD("set_item_stat_modifier", "index", "value"), &ItemTemplate::set_item_stat_modifier);

	ClassDB::bind_method(D_METHOD("get_animator_weapon_type"), &ItemTemplate::get_animator_weapon_type);

}
