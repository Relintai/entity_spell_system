#ifndef ITEM_TEMPLATE_H
#define ITEM_TEMPLATE_H

#include "core/resource.h"
#include "scene/resources/texture.h"

#include "item_template_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class ItemInstance;
class Aura;
class Spell;
class Bag;

class ItemTemplate : public Resource {
	GDCLASS(ItemTemplate, Resource);

public:

	int get_id() const;
	void set_id(const int value);

	String get_name_key() const;
	void set_name_key(const String value);

	ItemEnums::ItemType get_item_type() const;
	void set_item_type(const ItemEnums::ItemType value);

	ItemEnums::ItemSubtype get_item_sub_type() const;
	void set_item_sub_type(const ItemEnums::ItemSubtype value);

	ItemEnums::ItemSubSubtype get_item_sub_sub_type() const;
	void set_item_sub_sub_type(const ItemEnums::ItemSubSubtype value);

	ItemEnums::ItemRarity get_rarity() const;
	void set_rarity(const ItemEnums::ItemRarity value);

	int get_inventory_size_x() const;
	void set_inventory_size_x(const int value);
	
	int get_inventory_size_y() const;
	void set_inventory_size_y(const int value);

	Ref<Texture> get_icon() const;
	void set_icon(const Ref<Texture> value);

	float get_scale_x() const;
	void set_scale_x(const float value);

	float get_scale_y() const;
	void set_scale_y(const float value);

	float get_scale_z() const;
	void set_scale_z(const float value);

	int get_bag_size() const;
	void set_bag_size(const int size);
	
	Ref<Spell> get_spell() const;
	void set_spell(const Ref<Spell> spell);

	Ref<Aura> get_aura(int index) const;
	void set_aura(const int index, const Ref<Aura> aura);


	int get_item_stat_modifier_count() const;
	void set_item_stat_modifier_count(const int value);

	Stat::StatId get_item_stat_id(int index);
	void set_item_stat_id(int index, Stat::StatId value);

	float get_item_min_base_mod(int index);
	void set_item_min_base_mod(int index, float value);
	float get_item_max_base_mod(int index);
	void set_item_max_base_mod(int index, float value);
	float get_item_min_bonus_mod(int index);
	void set_item_min_bonus_mod(int index, float value);
	float get_item_max_bonus_mod(int index);
	void set_item_max_bonus_mod(int index, float value);
	float get_item_min_percent_mod(int index);
	void set_item_min_percent_mod(int index, float value);
	float get_item_max_percent_mod(int index);
	void set_item_max_percent_mod(int index, float value);
	float get_item_scaling_factor(int index);
	void set_item_scaling_factor(int index, float value);

	Ref<ItemTemplateStatModifier> get_item_template_stat_modifier(int index);
	//void set_item_stat_modifier(int index, ItemStatModifier modifier);

	int get_animator_weapon_type();

	Ref<ItemInstance> create_item_instance();

	ItemTemplate();
	~ItemTemplate();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_ITEM_STAT_MOD = 6,
		MAX_AURAS = 5,
	};

	int _id;
	String _name_key;
	ItemEnums::ItemRarity _rarity;
	ItemEnums::ItemType _item_type;
	ItemEnums::ItemSubtype _item_sub_type;
	ItemEnums::ItemSubSubtype _item_sub_sub_type;

	int _inventory_size_x;
	int _inventory_size_y;
	
	Ref<Texture> _icon;

	float _scale_x;
	float _scale_y;
	float _scale_z;
	
	int _bag_size;

	Ref<Spell> *_spell;
	Ref<Aura> *_auras[MAX_AURAS];

	int _modifier_count;
	Ref<ItemTemplateStatModifier> _modifiers[MAX_ITEM_STAT_MOD];
};

#endif
