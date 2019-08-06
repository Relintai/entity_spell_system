#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/reference.h"
#include "scene/resources/texture.h"

#include "item_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class Bag;
class ItemTemplate;

class ItemInstance : public Reference {
	GDCLASS(ItemInstance, Reference);

public:
	int get_id();
	void set_id(int value);
	
	int get_inventory_position_x() const;
	void set_inventory_position_x(const int value);
	
	int get_inventory_position_y() const;
	void set_inventory_position_y(const int value);
	
	Ref<ItemTemplate> get_item_template() const;
	void set_item_template(const Ref<ItemTemplate> value);

	Ref<ItemStatModifier> get_item_stat_modifier(int index);
	//void set_item_stat_modifier(int index, ItemStatModifier modifier);

	int get_item_stat_modifier_count();
	void set_item_stat_modifier_count(int value);

	Stat::StatId get_item_stat_id(int index);
	void set_item_stat_id(int index, Stat::StatId value);

	float get_item_base_mod(int index);
	void set_item_base_mod(int index, float value);

	float get_item_bonus_mod(int index);
	void set_item_bonus_mod(int index, float value);

	float get_percent_mod(int index);
	void set_percent_mod(int index, float value);
	
	int get_count();
	void set_count(int value);

	//to_dict();
	//from_dict();
	
	ItemInstance();
	~ItemInstance();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_ITEM_STAT_MOD = 6,
	};

	int _id;
	
	int _inventory_position_x;
	int _inventory_position_y;

	int _item_tamplate_id;
	Ref<ItemTemplate> _item_template;
	
	int _count;
	
	Ref<Bag> *_s_bag;
	Ref<Bag> *_c_bag;

	int _modifier_count;
	Ref<ItemStatModifier> _modifiers[MAX_ITEM_STAT_MOD];
};

#endif
