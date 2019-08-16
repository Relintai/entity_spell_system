#include "inventory.h"

#include "../data/item_template.h"
#include "../data/item_instance.h"

#include "../entities/player.h"

int Inventory::get_allowed_item_types() const {
	return _allowed_item_types;
}

void Inventory::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

Player *Inventory::get_target() const {
    return _target;
}

void Inventory::set_target(Player *value) {
	_target = value;
}

void Inventory::set_target_bind(Node *caster) {
    if (!caster) {
        return;
    }

    Player *e = Object::cast_to<Player>(caster);

    if (!e) {
        return;
    }

    _target = e;
}

Inventory::Inventory() {
	_allowed_item_types = 0xFFFFFF;
}

Inventory::~Inventory() {
}

void Inventory::_bind_methods() {
    ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "inventory", PROPERTY_HINT_RESOURCE_TYPE, "Inventory")));
    
	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Inventory::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Inventory::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");
	
	ClassDB::bind_method(D_METHOD("get_target"), &Inventory::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "target"), &Inventory::set_target_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Player"), "set_target", "get_target");
}

