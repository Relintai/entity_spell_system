#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/reference.h"
#include "core/vector.h"

#include "item_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

#include "../entity_data_manager.h"

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

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);
	
	ItemInstance();
	~ItemInstance();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item_template;
	int _item_template_id;
	
	int _stack_size;

	Vector<Ref<ItemStatModifier> > _modifiers;
};

#endif
