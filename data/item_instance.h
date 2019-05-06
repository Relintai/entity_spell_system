#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/reference.h"
#include "scene/resources/texture.h"

#include "item_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class ItemInstance : public Reference {
	GDCLASS(ItemInstance, Reference);

public:
	int get_id();
	void set_id(int value);

	String get_name_key();
	void set_name_key(String value);

	ItemEnums::ItemType get_item_type();
	void set_item_type(ItemEnums::ItemType value);

	ItemEnums::ItemSubtype get_item_sub_type();
	void set_item_sub_type(ItemEnums::ItemSubtype value);

	ItemEnums::ItemSubSubtype get_item_sub_sub_type();
	void set_item_sub_sub_type(ItemEnums::ItemSubSubtype value);

	ItemEnums::ItemRarity get_rarity();
	void set_rarity(ItemEnums::ItemRarity value);

	int get_spell_id();
	void set_spell_id(int value);

	float get_scale_x();
	void set_scale_x(float value);

	float get_scale_y();
	void set_scale_y(float value);

	float get_scale_z();
	void set_scale_z(float value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	int get_animator_weapon_type();

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
	String _name_key;
	ItemEnums::ItemType _item_type;
	ItemEnums::ItemSubtype _item_sub_type;
	ItemEnums::ItemSubSubtype _item_sub_sub_type;
	ItemEnums::ItemRarity _rarity;
	int _spell_id;
	float _scale_x;
	float _scale_y;
	float _scale_z;
	Ref<Texture> _icon;

	int _modifier_count;
	Ref<ItemStatModifier> _modifiers[MAX_ITEM_STAT_MOD];

#if ENTITY_MEM_TOOLS
	static int allocs;
#endif
};

#endif
