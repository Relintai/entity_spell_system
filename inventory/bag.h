#ifndef BAG_H
#define BAG_H

#include "core/reference.h"
#include "core/vector.h"

#include "../item_enums.h"

class ItemTemplate;
class ItemInstance;

class Bag : public Reference {
	GDCLASS(Bag, Reference);

public:
	int get_allowed_item_types() const;
	void set_allowed_item_types(const int value);

	bool add_item(Ref<ItemInstance> item);
	void add_item_at(int index, Ref<ItemInstance> item);
	Ref<ItemInstance> get_item(const int index);
    Ref<ItemInstance> remove_item(const int index);
    void swap_items(const int item1_index, const int item2_index);
	void change_item_equip(int slot_id, Ref<ItemInstance> item);
    
    bool can_add_item(Ref<ItemInstance> item);
	
	int get_item_count();
	int get_valid_item_count();

	int get_size();
    void set_size(const int size);
    
    bool is_full();
    bool is_overburdened();

    bool has_item(Ref<ItemTemplate> item, int count);
	bool _has_item(Ref<ItemTemplate> item, int count);

	void remove_items(Ref<ItemTemplate> item, int count);
	void _remove_items(Ref<ItemTemplate> item, int count);
	
	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);
	
	Bag();
    ~Bag();

protected:
	static void _bind_methods();
    
private:
	int _allowed_item_types;
	int _bag_size;
	Vector<Ref<ItemInstance> > _items;
};

#endif
