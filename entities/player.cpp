#include "player.h"

#include "../inventory/inventory.h"

////    Inventory    ////

Ref<Inventory> Player::gets_inventory() const {
	return _s_inventory;
}

Ref<Inventory> Player::getc_inventory() const {
	return _c_inventory;
}

void Player::sets_inventory(const Ref<Inventory> inventory) {
	_s_inventory = inventory;
}
void Player::setc_inventory(const Ref<Inventory> inventory) {
	_c_inventory = inventory;
}

Ref<Inventory> Player::gets_target_inventory() const {
	return _s_target_inventory;
}

void Player::sets_target_inventory(const Ref<Inventory> inventory) {
	_s_target_inventory = inventory;
}

Ref<Inventory> Player::getc_target_inventory() const {
	return _c_target_inventory;
}

void Player::setc_target_inventory(const Ref<Inventory> inventory) {
	_c_target_inventory = inventory;
}

bool Player::stry_to_add_item(int itemId, int count) {
	return false;
}

bool Player::stry_to_remove_item(int itemId, int count) {
	return false;
}

void Player::ssend_add_item(int slotId, int itemId, int count) {
}

void Player::ssend_change_item_count(int slotId, int count) {
}

void Player::ssend_remove_item(int slotId) {
}

void Player::ssend_move_item(int slot1, int slot2) {
}

void Player::ssend_sent_items(String items) {
}

void Player::csend_swap_items(int slot1, int slot2) {
}

void Player::csend_craft_item_request(int craftId) {
}

void Player::creceive_add_item(int slotId, int itemId, int count) {
}

void Player::creceive_change_item_count(int slotId, int count) {
}

void Player::creceive_remove_item(int slotId) {
}

void Player::creceive_move_item(int slot1, int slot2) {
}

void Player::creceive_sent_items(String items) {
}

void Player::sreceive_swap_items(int slot1, int slot2) {
}

void Player::send_all_items() {
}

bool Player::shas_item(int itemId, int count) {
	/*
       for (int i = 0; i < getSInventory()->Count; i += 1) {
       if (((getSInventory()->GetData(i) != null) && (getSInventory()->GetData(i)->ItemID == itemId)) && (getSInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

bool Player::chas_item(int itemId, int count) {
	/*
       for (int i = 0; i < getCInventory()->Count; i += 1) {
       if (((getCInventory()->GetData(i) != null) && (getCInventory()->GetData(i)->ItemID == itemId)) && (getCInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

int Player::cget_item_count(int itemId) {
	return 0;
}

int Player::sget_item_count(int itemId) {
	return 0;
}

bool Player::ccan_craft(CraftDataAttribute *cda) {
	return false;
}

bool Player::ctry_to_craft(CraftDataAttribute *cda) {
	return false;
}

bool Player::scan_craft(CraftDataAttribute *cda) {
	return false;
}

void Player::scraft(CraftDataAttribute *cda) {
}

void Player::sreceive_craft_item_msg(int craftId) {
}

void Player::cswap_items_in_slots(int slot1, int slot2) {
}

Player::Player() {
}

void Player::_bind_methods() {
	////    Inventory System    ////

	ADD_SIGNAL(MethodInfo("sitem_added", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	ADD_SIGNAL(MethodInfo("citem_added", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("gets_inventory"), &Player::gets_inventory);
	ClassDB::bind_method(D_METHOD("getc_inventory"), &Player::getc_inventory);

	ClassDB::bind_method(D_METHOD("sets_inventory", "inventory"), &Player::sets_inventory);
	ClassDB::bind_method(D_METHOD("setc_inventory", "inventory"), &Player::setc_inventory);

	ClassDB::bind_method(D_METHOD("gets_target_inventory"), &Player::gets_target_inventory);
	ClassDB::bind_method(D_METHOD("sets_target_inventory", "inventory"), &Player::sets_target_inventory);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "starget_inventory", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), "sets_target_inventory", "gets_target_inventory");

	ClassDB::bind_method(D_METHOD("getc_target_inventory"), &Player::getc_target_inventory);
	ClassDB::bind_method(D_METHOD("setc_target_inventory", "inventory"), &Player::setc_target_inventory);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ctarget_inventory", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), "setc_target_inventory", "getc_target_inventory");

	BIND_ENUM_CONSTANT(BACKPACK_SIZE);
	BIND_ENUM_CONSTANT(MAX_BAG_SLOTS);
}
