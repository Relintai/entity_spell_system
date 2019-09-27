#include "item_template.h"

#include "item_instance.h"
#include "aura.h"
#include "spell.h"

int ItemTemplate::get_id() const {
	return _id;
}
void ItemTemplate::set_id(const int value) {
	_id = value;
}

String ItemTemplate::get_name_key() const {
	return _name_key;
}
void ItemTemplate::set_name_key(const String value) {
	_name_key = value;
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

Ref<ItemVisual> ItemTemplate::get_item_visual() const {
	return _item_visual;
}
void ItemTemplate::set_item_visual(const Ref<ItemVisual> value) {
	_item_visual = value;
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

void ItemTemplate::set_icon(const Ref<Texture> value) {
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

////    TEACHES    ////

int ItemTemplate::get_num_teaches_spells() {
	return _teaches_spells.size();
}
void ItemTemplate::set_num_teaches_spells(int value) {
	_teaches_spells.resize(value);
}

Ref<Spell> ItemTemplate::get_teaches_spell(int index) const {
	ERR_FAIL_INDEX_V(index, _teaches_spells.size(), Ref<Spell>());

	return _teaches_spells[index];
}
void ItemTemplate::set_teaches_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _teaches_spells.size());

	_teaches_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> ItemTemplate::get_teaches_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _teaches_spells.size(); i++) {
		r.push_back(_teaches_spells[i].get_ref_ptr());
	}
	return r;
}
void ItemTemplate::set_teaches_spells(const Vector<Variant> &spells) {
	_teaches_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_teaches_spells.push_back(spell);
	}
}

////    GRANTS SPELLS    ////

int ItemTemplate::get_num_grants_spells() {
	return _grants_spells.size();
}
void ItemTemplate::set_num_grants_spells(int value) {
	_grants_spells.resize(value);
}

Ref<Spell> ItemTemplate::get_grants_spell(int index) const {
	ERR_FAIL_INDEX_V(index, _grants_spells.size(), Ref<Spell>());

	return _grants_spells[index];
}
void ItemTemplate::set_grants_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _grants_spells.size());

	_grants_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> ItemTemplate::get_grants_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _grants_spells.size(); i++) {
		r.push_back(_grants_spells[i].get_ref_ptr());
	}
	return r;
}
void ItemTemplate::set_grants_spells(const Vector<Variant> &spells) {
	_grants_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_grants_spells.push_back(spell);
	}
}

////    AURAS    ////

int ItemTemplate::get_num_auras() {
	return _auras.size();
}
void ItemTemplate::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> ItemTemplate::get_aura(int index) const {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras[index];
}
void ItemTemplate::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, Ref<Aura>(aura));
}

Vector<Variant> ItemTemplate::get_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
		r.push_back(_auras[i].get_ref_ptr());
	}
	return r;
}
void ItemTemplate::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> spell = Ref<Aura>(auras[i]);

		_auras.push_back(spell);
	}
}

Ref<Spell> ItemTemplate::get_use_spell() const {
	return _use_spell;
}
void ItemTemplate::set_use_spell(Ref<Spell> use_spell) {
	_use_spell = use_spell;
}

int ItemTemplate::get_item_stat_modifier_count() const {
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

Ref<ItemInstance> ItemTemplate::create_item_instance() {
	if (has_method("_create_item_instance")) {
		Ref<ItemInstance> ii = call("_create_item_instance");

		ERR_FAIL_COND_V(!ii.is_valid(), Ref<ItemInstance>());

		return ii;
	}

	Ref<ItemInstance> item;
	item.instance();

	//todo setup
	ERR_EXPLAIN("NOT YET IMPLEMENTED!");
	ERR_FAIL_V(item);

	return item;
}

ItemTemplate::ItemTemplate() {
	_id = 0;
	_name_key = "";
	_item_type = ItemEnums::ITEM_TYPE_NONE;
	_item_sub_type = ItemEnums::ITEM_SUB_TYPE_NONE;
	_item_sub_sub_type = ItemEnums::ITEM_SUB_SUB_TYPE_NONE;
	_rarity = ItemEnums::ITEM_RARITY_NONE;
	_price = 0;

	_scale_x = 0;
	_scale_y = 0;
	_scale_z = 0;
	_modifier_count = 0;
	
	_stack_size = 1;
	_bag_size = 0;

	for (int i = 0; i < MAX_ITEM_STAT_MOD; ++i) {
		_modifiers[i] = Ref<ItemTemplateStatModifier>(memnew(ItemTemplateStatModifier()));
	}
}

ItemTemplate::~ItemTemplate() {
	_teaches_spells.clear();
	_grants_spells.clear();
	_auras.clear();
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
	BIND_VMETHOD(MethodInfo("_create_item_instance"));
	
	ClassDB::bind_method(D_METHOD("create_item_instance"), &ItemTemplate::create_item_instance);

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
	ADD_PROPERTY(PropertyInfo(Variant::INT, "rarity", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_RARITY), "set_rarity", "get_rarity");

	ClassDB::bind_method(D_METHOD("get_price"), &ItemTemplate::get_price);
	ClassDB::bind_method(D_METHOD("set_price", "count"), &ItemTemplate::set_price);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "price"), "set_price", "get_price");

	ClassDB::bind_method(D_METHOD("get_item_visual"), &ItemTemplate::get_item_visual);
	ClassDB::bind_method(D_METHOD("set_item_visual", "value"), &ItemTemplate::set_item_visual);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_visual", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisual"), "set_item_visual", "get_item_visual");

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
	ADD_GROUP("Teaches Spells", "teaches_spells");
	ClassDB::bind_method(D_METHOD("get_num_teaches_spells"), &ItemTemplate::get_num_teaches_spells);
	ClassDB::bind_method(D_METHOD("set_num_teaches_spells", "value"), &ItemTemplate::set_num_teaches_spells);

	ClassDB::bind_method(D_METHOD("get_teaches_spell", "index"), &ItemTemplate::get_teaches_spell);
	ClassDB::bind_method(D_METHOD("set_teaches_spell", "index", "spell"), &ItemTemplate::set_teaches_spell);

	ClassDB::bind_method(D_METHOD("get_teaches_spells"), &ItemTemplate::get_teaches_spells);
	ClassDB::bind_method(D_METHOD("set_teaches_spells", "spells"), &ItemTemplate::set_teaches_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "teaches_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_teaches_spells", "get_teaches_spells");

	////    Grants Spells    ////
	ADD_GROUP("Grants Spells", "grants_spells");
	ClassDB::bind_method(D_METHOD("get_num_grants_spells"), &ItemTemplate::get_num_grants_spells);
	ClassDB::bind_method(D_METHOD("set_num_grants_spells", "value"), &ItemTemplate::set_num_grants_spells);

	ClassDB::bind_method(D_METHOD("get_grants_spell", "index"), &ItemTemplate::get_grants_spell);
	ClassDB::bind_method(D_METHOD("set_grants_spell", "index", "spell"), &ItemTemplate::set_grants_spell);

	ClassDB::bind_method(D_METHOD("get_grants_spells"), &ItemTemplate::get_grants_spells);
	ClassDB::bind_method(D_METHOD("set_grants_spells", "spells"), &ItemTemplate::set_grants_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "grants_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_grants_spells", "get_grants_spells");

	////    Auras    ////
	ADD_GROUP("Auras", "auras");
	ClassDB::bind_method(D_METHOD("get_num_auras"), &ItemTemplate::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &ItemTemplate::set_num_auras);

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &ItemTemplate::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &ItemTemplate::set_aura);

	ClassDB::bind_method(D_METHOD("get_auras"), &ItemTemplate::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &ItemTemplate::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	//Use spell
	ClassDB::bind_method(D_METHOD("get_use_spell"), &ItemTemplate::get_use_spell);
	ClassDB::bind_method(D_METHOD("set_use_spell", "size"), &ItemTemplate::set_use_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "use_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_use_spell", "get_use_spell");

	//StatMods Property binds
	ADD_GROUP("Item Stat Modifiers", "item_stat_modifier");
	ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemTemplate::get_item_stat_modifier_count);
	ClassDB::bind_method(D_METHOD("set_item_stat_modifier_count", "count"), &ItemTemplate::set_item_stat_modifier_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_stat_modifier_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ITEM_STAT_MOD), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_item_stat_modifier_count", "get_item_stat_modifier_count");

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
