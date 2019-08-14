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
	Ref<ItemInstance> get_item(const int index) const;
    Ref<ItemInstance> remove_item(const int index);
    
    bool can_add_item(Ref<ItemInstance> item);
	
	int get_item_count() const;

	int get_size() const;
    void set_size(const int size);
    
    bool is_full() const;
	
	//to_dict();
	//from_dict();
	
	Bag();
    ~Bag();

protected:
	static void _bind_methods();
    
private:
	int _allowed_item_types;
    int _item_count;
	Vector<Ref<ItemInstance> > _items;
};

#endif
