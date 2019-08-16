#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Inventory;

class Player : public Entity {
    GDCLASS(Player, Entity);

public:
	enum InventorySizes {
        BACKPACK_SIZE = 20,
        MAX_BAG_SLOTS = 5,
    };
	
	////    Inventory    ////

	Ref<Inventory> gets_inventory() const;
	Ref<Inventory> getc_inventory() const;
	
	void sets_inventory(const Ref<Inventory> inventory);
	void setc_inventory(const Ref<Inventory> inventory);
    
	Ref<Inventory> gets_target_inventory() const;
	void sets_target_inventory(const Ref<Inventory> inventory);
	
	Ref<Inventory> getc_target_inventory() const;
	void setc_target_inventory(const Ref<Inventory> inventory);
	
	bool add_item_to_inventory(Ref<ItemInstance> item);
	
	bool stry_to_add_item(int itemId, int count);
	bool stry_to_remove_item(int itemId, int count);
	void ssend_add_item(int slotId, int itemId, int count);
	void ssend_change_item_count(int slotId, int count);
	void ssend_remove_item(int slotId);
	void ssend_move_item(int slot1, int slot2);
	void ssend_sent_items(String items);
	void csend_swap_items(int slot1, int slot2);
	void csend_craft_item_request(int craftId);
	void creceive_add_item(int slotId, int itemId, int count);
	void creceive_change_item_count(int slotId, int count);
	void creceive_remove_item(int slotId);
	void creceive_move_item(int slot1, int slot2);
	void creceive_sent_items(String items);
	void sreceive_swap_items(int slot1, int slot2);
	bool shas_item(int itemId, int count);
	bool chas_item(int itemId, int count);
	int cget_item_count(int itemId);
	int sget_item_count(int itemId);
	bool ccan_craft(CraftDataAttribute *cda);
	bool ctry_to_craft(CraftDataAttribute *cda);
	bool scan_craft(CraftDataAttribute *cda);
	void scraft(CraftDataAttribute *cda);
	void sreceive_craft_item_msg(int craftId);
	void cswap_items_in_slots(int slot1, int slot2);
	
	void send_all_items();
	
	Player();

protected:
	static void _bind_methods();
	
private:
	////    Inventory    ////

	Ref<Inventory> _s_inventory;
	Ref<Inventory> _c_inventory;
	
	Ref<Inventory> _s_target_inventory;
	Ref<Inventory> _c_target_inventory;

};

VARIANT_ENUM_CAST(Player::InventorySizes);

#endif
