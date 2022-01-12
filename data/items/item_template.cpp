/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "item_template.h"

#include "../../entities/data/entity_class_data.h"
#include "../spells/spell.h"
#include "item_instance.h"

#include "../../singletons/ess.h"

#include "../../defines.h"

int ItemTemplate::get_id() const {
	return _id;
}
void ItemTemplate::set_id(const int value) {
	_id = value;
}

ItemEnums::ItemType ItemTemplate::get_item_type() const {
	return _item_type;
}
void ItemTemplate::set_item_type(const ItemEnums::ItemType value) {
	_item_type = value;
}

ItemEnums::ItemSubtype ItemTemplate::get_item_sub_type() const {
	return _item_sub_type;
}
void ItemTemplate::set_item_sub_type(const ItemEnums::ItemSubtype value) {
	_item_sub_type = value;
}

ItemEnums::ItemSubSubtype ItemTemplate::get_item_sub_sub_type() const {
	return _item_sub_sub_type;
}
void ItemTemplate::set_item_sub_sub_type(const ItemEnums::ItemSubSubtype value) {
	_item_sub_sub_type = value;
}

ItemEnums::ItemRarity ItemTemplate::get_rarity() const {
	return _rarity;
}
void ItemTemplate::set_rarity(const ItemEnums::ItemRarity value) {
	_rarity = value;
}

ItemEnums::ArmorType ItemTemplate::get_armor_type() const {
	return _armor_type;
}
void ItemTemplate::set_armor_type(const ItemEnums::ArmorType value) {
	_armor_type = value;
}

int ItemTemplate::get_equip_slot() const {
	return _equip_slot;
}
void ItemTemplate::set_equip_slot(const int value) {
	_equip_slot = value;
}

Ref<ModelVisual> ItemTemplate::get_model_visual() const {
	return _model_visual;
}
void ItemTemplate::set_model_visual(const Ref<ModelVisual> &value) {
	_model_visual = value;
}

Ref<EntityClassData> ItemTemplate::get_required_character_class() const {
	return _required_character_class;
}
void ItemTemplate::set_required_character_class(const Ref<EntityClassData> &value) {
	_required_character_class = value;
}

int ItemTemplate::get_price() const {
	return _price;
}

void ItemTemplate::set_price(const int value) {
	_price = value;
}

int ItemTemplate::get_stack_size() const {
	return _stack_size;
}
void ItemTemplate::set_stack_size(const int value) {
	_stack_size = value;
}

Ref<Texture> ItemTemplate::get_icon() const {
	return _icon;
}

void ItemTemplate::set_icon(const Ref<Texture> &value) {
	_icon = value;
}

float ItemTemplate::get_scale_x() const {
	return _scale_x;
}

void ItemTemplate::set_scale_x(const float value) {
	_scale_x = value;
}

float ItemTemplate::get_scale_y() const {
	return _scale_y;
}

void ItemTemplate::set_scale_y(const float value) {
	_scale_y = value;
}

float ItemTemplate::get_scale_z() const {
	return _scale_z;
}

void ItemTemplate::set_scale_z(const float value) {
	_scale_z = value;
}

int ItemTemplate::get_bag_size() const {
	return _bag_size;
}
void ItemTemplate::set_bag_size(const int size) {
	_bag_size = size;
}

///     TEXTS    ////

String ItemTemplate::get_text_translation_key() const {
	return _text_translation_key;
}
void ItemTemplate::set_text_translation_key(const String &value) {
	_text_translation_key = value;
}

////    TEACHES    ////

int ItemTemplate::get_num_teaches_spells() const {
	return _teaches_spells.size();
}
void ItemTemplate::set_num_teaches_spells(int value) {
	_teaches_spells.resize(value);
}

Ref<Spell> ItemTemplate::get_teaches_spell(const int index) {
	ERR_FAIL_INDEX_V(index, _teaches_spells.size(), Ref<Spell>());

	return _teaches_spells[index];
}
void ItemTemplate::set_teaches_spell(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _teaches_spells.size());

	_teaches_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> ItemTemplate::get_teaches_spells() {
	VARIANT_ARRAY_GET(_teaches_spells);
}
void ItemTemplate::set_teaches_spells(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _teaches_spells, Spell);
}

////    GRANTS SPELLS    ////

int ItemTemplate::get_num_grants_spells() const {
	return _grants_spells.size();
}
void ItemTemplate::set_num_grants_spells(const int value) {
	_grants_spells.resize(value);
}

Ref<Spell> ItemTemplate::get_grants_spell(const int index) {
	ERR_FAIL_INDEX_V(index, _grants_spells.size(), Ref<Spell>());

	return _grants_spells[index];
}
void ItemTemplate::set_grants_spell(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _grants_spells.size());

	_grants_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> ItemTemplate::get_grants_spells() {
	VARIANT_ARRAY_GET(_grants_spells);
}
void ItemTemplate::set_grants_spells(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _grants_spells, Spell);
}

////    AURAS    ////

int ItemTemplate::get_num_auras() const {
	return _auras.size();
}
void ItemTemplate::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Spell> ItemTemplate::get_aura(const int index) {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Spell>());

	return _auras[index];
}
void ItemTemplate::set_aura(const int index, const Ref<Spell> &aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, Ref<Spell>(aura));
}

Vector<Variant> ItemTemplate::get_auras() {
	VARIANT_ARRAY_GET(_auras);
}
void ItemTemplate::set_auras(const Vector<Variant> &auras) {
	VARIANT_ARRAY_SET(auras, _auras, Spell);
}

//Required Skills
int ItemTemplate::get_num_required_skills() const {
	return _required_skills.size();
}

Ref<Spell> ItemTemplate::get_required_skill(const int index) {
	ERR_FAIL_INDEX_V(index, _required_skills.size(), Ref<Spell>());

	return _required_skills.get(index);
}
void ItemTemplate::set_required_skill(const int index, const Ref<Spell> &aura) {
	ERR_FAIL_INDEX(index, _required_skills.size());

	_required_skills.set(index, aura);
}

Vector<Variant> ItemTemplate::get_required_skills() {
	VARIANT_ARRAY_GET(_required_skills);
}
void ItemTemplate::set_required_skills(const Vector<Variant> &skills) {
	VARIANT_ARRAY_SET(skills, _required_skills, Spell);
}

//use spell
Ref<Spell> ItemTemplate::get_use_spell() {
	return _use_spell;
}
void ItemTemplate::set_use_spell(const Ref<Spell> &use_spell) {
	_use_spell = use_spell;
}

int ItemTemplate::get_charges() const {
	return _charges;
}
void ItemTemplate::set_charges(const int value) {
	_charges = value;
}

bool ItemTemplate::get_consumed() const {
	return _consumed;
}
void ItemTemplate::set_consumed(const bool value) {
	_consumed = false;
}

int ItemTemplate::stat_modifier_get_count() const {
	return _modifier_count;
}

void ItemTemplate::stat_modifier_set_count(int value) {
	_modifier_count = value;
}

int ItemTemplate::stat_modifier_get_stat_id(const int index) const {
	return _modifiers[index].stat_id;
}

void ItemTemplate::stat_modifier_set_stat_id(const int index, const int value) {
	_modifiers[index].stat_id = value;
}

float ItemTemplate::stat_modifier_get_min_base_mod(const int index) const {
	return _modifiers[index].min_base_mod;
}

void ItemTemplate::stat_modifier_set_min_base_mod(const int index, const float value) {
	_modifiers[index].min_base_mod = value;
}

float ItemTemplate::stat_modifier_get_max_base_mod(const int index) const {
	return _modifiers[index].max_base_mod;
}

void ItemTemplate::stat_modifier_set_max_base_mod(const int index, const float value) {
	_modifiers[index].max_base_mod = value;
}

float ItemTemplate::stat_modifier_get_min_bonus_mod(const int index) const {
	return _modifiers[index].min_bonus_mod;
}

void ItemTemplate::stat_modifier_set_min_bonus_mod(const int index, const float value) {
	_modifiers[index].min_bonus_mod = value;
}

float ItemTemplate::stat_modifier_get_max_bonus_mod(const int index) const {
	return _modifiers[index].max_bonus_mod;
}

void ItemTemplate::stat_modifier_set_max_bonus_mod(const int index, const float value) {
	_modifiers[index].max_bonus_mod = value;
}

float ItemTemplate::stat_modifier_get_min_percent_mod(const int index) const {
	return _modifiers[index].min_percent_mod;
}

void ItemTemplate::stat_modifier_set_min_percent_mod(const int index, const float value) {
	_modifiers[index].min_percent_mod = value;
}

float ItemTemplate::stat_modifier_get_max_percent_mod(const int index) const {
	return _modifiers[index].max_percent_mod;
}

void ItemTemplate::stat_modifier_set_max_percent_mod(const int index, const float value) {
	_modifiers[index].max_percent_mod = value;
}

float ItemTemplate::stat_modifier_get_scaling_factor(const int index) const {
	return _modifiers[index].scaling_factor;
}

void ItemTemplate::stat_modifier_set_scaling_factor(const int index, const float value) {
	_modifiers[index].scaling_factor = value;
}

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

Ref<ItemInstance> ItemTemplate::create_item_instance() {
	if (has_method("_create_item_instance")) {
		Ref<ItemInstance> ii = call("_create_item_instance");

		ERR_FAIL_COND_V(!ii.is_valid(), Ref<ItemInstance>());

		return ii;
	}

	Ref<ItemInstance> item;
	item.instance();

	//todo setup
	//ERR_EXPLAIN("NOT YET IMPLEMENTED!");
	ERR_FAIL_V(item);

	return item;
}

String ItemTemplate::get_description() {
	if (!has_method("_get_description"))
		return "";

	return call("_get_description");
}

ItemTemplate::ItemTemplate() {
	_id = 0;
	_item_type = ItemEnums::ITEM_TYPE_NONE;
	_item_sub_type = ItemEnums::ITEM_SUB_TYPE_NONE;
	_item_sub_sub_type = ItemEnums::ITEM_SUB_SUB_TYPE_NONE;
	_rarity = ItemEnums::ITEM_RARITY_NONE;
	_armor_type = ItemEnums::ARMOR_TYPE_NONE;
	_equip_slot = ESS::get_singleton()->equip_slot_get_count();
	_price = 0;

	_scale_x = 0;
	_scale_y = 0;
	_scale_z = 0;
	_modifier_count = 0;

	_stack_size = 1;
	_bag_size = 0;

	_charges = -1;
	_consumed = false;
}

ItemTemplate::~ItemTemplate() {
	_teaches_spells.clear();
	_grants_spells.clear();
	_auras.clear();
	_required_character_class.unref();
}

void ItemTemplate::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("stat_modifier_")) {
		if (prop.ends_with("count"))
			return;

		int frame = prop.get_slicec('/', 0).get_slicec('_', 2).to_int();
		if (frame >= _modifier_count) {
			property.usage = 0;
		}

		if (property.name.ends_with("stat_id"))
			property.hint_string = ESS::get_singleton()->stat_get_string();
	} else if (prop == "equip_slot") {
		property.hint_string = ESS::get_singleton()->equip_slot_get_string();
	}
}

void ItemTemplate::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_create_item_instance"));

	ClassDB::bind_method(D_METHOD("create_item_instance"), &ItemTemplate::create_item_instance);

	ClassDB::bind_method(D_METHOD("get_id"), &ItemTemplate::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "count"), &ItemTemplate::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

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
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rarity", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_RARITY), "set_rarity", "get_rarity");

	ClassDB::bind_method(D_METHOD("get_armor_type"), &ItemTemplate::get_armor_type);
	ClassDB::bind_method(D_METHOD("set_armor_type", "value"), &ItemTemplate::set_armor_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "armor_type", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ARMOR_TYPE), "set_armor_type", "get_armor_type");

	ClassDB::bind_method(D_METHOD("get_equip_slot"), &ItemTemplate::get_equip_slot);
	ClassDB::bind_method(D_METHOD("set_equip_slot", "count"), &ItemTemplate::set_equip_slot);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "equip_slot", PROPERTY_HINT_ENUM, ""), "set_equip_slot", "get_equip_slot");

	ClassDB::bind_method(D_METHOD("get_price"), &ItemTemplate::get_price);
	ClassDB::bind_method(D_METHOD("set_price", "count"), &ItemTemplate::set_price);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "price"), "set_price", "get_price");

	ClassDB::bind_method(D_METHOD("get_model_visual"), &ItemTemplate::get_model_visual);
	ClassDB::bind_method(D_METHOD("set_model_visual", "value"), &ItemTemplate::set_model_visual);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "model_visual", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisual"), "set_model_visual", "get_model_visual");

	ClassDB::bind_method(D_METHOD("get_stack_size"), &ItemTemplate::get_stack_size);
	ClassDB::bind_method(D_METHOD("set_stack_size", "value"), &ItemTemplate::set_stack_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stack_size"), "set_stack_size", "get_stack_size");

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

	ClassDB::bind_method(D_METHOD("get_bag_size"), &ItemTemplate::get_bag_size);
	ClassDB::bind_method(D_METHOD("set_bag_size", "size"), &ItemTemplate::set_bag_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bag_size"), "set_bag_size", "get_bag_size");

	////    Teaches    ////
	ClassDB::bind_method(D_METHOD("get_num_teaches_spells"), &ItemTemplate::get_num_teaches_spells);
	ClassDB::bind_method(D_METHOD("set_num_teaches_spells", "value"), &ItemTemplate::set_num_teaches_spells);

	ClassDB::bind_method(D_METHOD("get_teaches_spell", "index"), &ItemTemplate::get_teaches_spell);
	ClassDB::bind_method(D_METHOD("set_teaches_spell", "index", "spell"), &ItemTemplate::set_teaches_spell);

	ClassDB::bind_method(D_METHOD("get_teaches_spells"), &ItemTemplate::get_teaches_spells);
	ClassDB::bind_method(D_METHOD("set_teaches_spells", "spells"), &ItemTemplate::set_teaches_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "teaches_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_teaches_spells", "get_teaches_spells");

	////    Grants Spells    ////
	ClassDB::bind_method(D_METHOD("get_num_grants_spells"), &ItemTemplate::get_num_grants_spells);
	ClassDB::bind_method(D_METHOD("set_num_grants_spells", "value"), &ItemTemplate::set_num_grants_spells);

	ClassDB::bind_method(D_METHOD("get_grants_spell", "index"), &ItemTemplate::get_grants_spell);
	ClassDB::bind_method(D_METHOD("set_grants_spell", "index", "spell"), &ItemTemplate::set_grants_spell);

	ClassDB::bind_method(D_METHOD("get_grants_spells"), &ItemTemplate::get_grants_spells);
	ClassDB::bind_method(D_METHOD("set_grants_spells", "spells"), &ItemTemplate::set_grants_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "grants_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_grants_spells", "get_grants_spells");

	////    Auras    ////
	ClassDB::bind_method(D_METHOD("get_num_auras"), &ItemTemplate::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &ItemTemplate::set_num_auras);

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &ItemTemplate::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &ItemTemplate::set_aura);

	ClassDB::bind_method(D_METHOD("get_auras"), &ItemTemplate::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &ItemTemplate::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_auras", "get_auras");

	////    Required Skills    ////
	ClassDB::bind_method(D_METHOD("get_num_required_skills"), &ItemTemplate::get_num_required_skills);

	ClassDB::bind_method(D_METHOD("get_required_skill", "index"), &ItemTemplate::get_required_skill);
	ClassDB::bind_method(D_METHOD("set_required_skill", "index", "aura"), &ItemTemplate::set_required_skill);

	ClassDB::bind_method(D_METHOD("get_required_skills"), &ItemTemplate::get_required_skills);
	ClassDB::bind_method(D_METHOD("set_required_skills", "auras"), &ItemTemplate::set_required_skills);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "required_skills", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_required_skills", "get_required_skills");

	//Use spell
	ClassDB::bind_method(D_METHOD("get_use_spell"), &ItemTemplate::get_use_spell);
	ClassDB::bind_method(D_METHOD("set_use_spell", "size"), &ItemTemplate::set_use_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "use_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_use_spell", "get_use_spell");

	ClassDB::bind_method(D_METHOD("get_charges"), &ItemTemplate::get_charges);
	ClassDB::bind_method(D_METHOD("set_charges", "size"), &ItemTemplate::set_charges);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "charges"), "set_charges", "get_charges");

	ClassDB::bind_method(D_METHOD("get_consumed"), &ItemTemplate::get_consumed);
	ClassDB::bind_method(D_METHOD("set_consumed", "size"), &ItemTemplate::set_consumed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "consumed"), "set_consumed", "get_consumed");

	ADD_GROUP("Texts", "text");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_translation_key"), &ItemTemplate::get_text_translation_key);
	ClassDB::bind_method(D_METHOD("set_text_translation_key", "value"), &ItemTemplate::set_text_translation_key);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_translation_key"), "set_text_translation_key", "get_text_translation_key");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_get_description"));
	ClassDB::bind_method(D_METHOD("get_description"), &ItemTemplate::get_description);

	//StatMods Property binds
	ADD_GROUP("Stat Modifiers", "stat_modifier");
	ClassDB::bind_method(D_METHOD("stat_modifier_get_count"), &ItemTemplate::stat_modifier_get_count);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_count", "count"), &ItemTemplate::stat_modifier_set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_modifier_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ITEM_STAT_MOD), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "stat_modifier_set_count", "stat_modifier_get_count");

	ClassDB::bind_method(D_METHOD("stat_modifier_get_stat_id", "index"), &ItemTemplate::stat_modifier_get_stat_id);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_stat_id", "index", "value"), &ItemTemplate::stat_modifier_set_stat_id);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_min_base_mod", "index"), &ItemTemplate::stat_modifier_get_min_base_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_min_base_mod", "index", "value"), &ItemTemplate::stat_modifier_set_min_base_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_max_base_mod", "index"), &ItemTemplate::stat_modifier_get_max_base_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_max_base_mod", "index", "value"), &ItemTemplate::stat_modifier_set_max_base_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_min_bonus_mod", "index"), &ItemTemplate::stat_modifier_get_min_bonus_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_min_bonus_mod", "index", "value"), &ItemTemplate::stat_modifier_set_min_bonus_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_max_bonus_mod", "index"), &ItemTemplate::stat_modifier_get_max_bonus_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_max_bonus_mod", "index", "value"), &ItemTemplate::stat_modifier_set_max_bonus_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_min_percent_mod", "index"), &ItemTemplate::stat_modifier_get_min_percent_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_min_percent_mod", "index", "value"), &ItemTemplate::stat_modifier_set_min_percent_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_max_percent_mod", "index"), &ItemTemplate::stat_modifier_get_max_percent_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_max_percent_mod", "index", "value"), &ItemTemplate::stat_modifier_set_max_percent_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_scaling_factor", "index"), &ItemTemplate::stat_modifier_get_scaling_factor);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_scaling_factor", "index", "value"), &ItemTemplate::stat_modifier_set_scaling_factor);

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "stat_modifier_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_stat_id", "stat_modifier_get_stat_id", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/min_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_min_base_mod", "stat_modifier_get_min_base_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/max_base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_max_base_mod", "stat_modifier_get_max_base_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/min_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_min_bonus_mod", "stat_modifier_get_min_bonus_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/max_bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_max_bonus_mod", "stat_modifier_get_max_bonus_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/min_percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_min_percent_mod", "stat_modifier_get_min_percent_mod", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/max_percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_max_percent_mod", "stat_modifier_get_max_percent_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "stat_modifier_" + itos(i) + "/scaling_factor", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "stat_modifier_set_scaling_factor", "stat_modifier_get_scaling_factor", i);
	}

	ClassDB::bind_method(D_METHOD("get_animator_weapon_type"), &ItemTemplate::get_animator_weapon_type);

	BIND_CONSTANT(MAX_ITEM_STAT_MOD);
}
