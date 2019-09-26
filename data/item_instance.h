#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/reference.h"
#include "core/vector.h"

#include "item_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class ItemTemplate;

class ItemInstance : public Reference {
	GDCLASS(ItemInstance, Reference);

public:
	Ref<ItemTemplate> get_item_template() const;
	void set_item_template(const Ref<ItemTemplate> value);

	Ref<ItemStatModifier> get_item_stat_modifier(int index);
	void add_item_stat_modifier(Ref<ItemStatModifier> modifier);
	void remove_item_stat_modifier(int index);
	void clear_item_stat_modifiers();

	int get_item_stat_modifier_count();
	
	int get_stack_size();
	void set_stack_size(int value);

	//to_dict();
	//from_dict();
	
	ItemInstance();
	~ItemInstance();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item_template;
	
	int _stack_size;

	Vector<Ref<ItemStatModifier> > _modifiers;
};

#endif
