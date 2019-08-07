#ifndef BAG_H
#define BAG_H

#include "core/reference.h"
#include "core/vector.h"

#include "../item_enums.h"

class itemTemplate;
class ItemInstance;

class Bag : public Reference {
	GDCLASS(Bag, Reference);

public:
	int get_allowed_item_types() const;
	void set_allowed_item_types(const int value);
	
	bool add_item(Ref<ItemInstance> item);
	bool add_item_to_position(const int x, const int y, Ref<ItemInstance> item);
	
	bool can_add_item_at(const int x, const int y, const Ref<ItemInstance> item) const;
	int item_count_under_area(const int x, const int y, const int size_x, const int size_y) const;
	
	Ref<ItemInstance> get_item(const int index) const;
    Ref<ItemInstance> get_and_remove_item(const int index);
	void remove_item(const int index);
	
	void basic_add_item(const Ref<ItemInstance> item);
	void basic_remove_item(const int index);
	
	int get_item_count() const;

	int get_space_map_entry(const int index) const;
	void set_space_map_entry(const int index, const int value);
	
	int get_size_x() const;
	int get_size_y() const;
	
    void set_size(const int x, const int y);
	
	//to_dict();
	//from_dict();
	
	Bag();
    ~Bag();

protected:
	static void _bind_methods();
    
private:
	int _allowed_item_types;
	
	int _size_x;
	int _size_y;
	
	Vector<Ref<ItemInstance> > _items;
	Vector<int> _space_map;
};

#endif
