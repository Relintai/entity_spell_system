#ifndef ITEM_TEMPLATE_H
#define ITEM_TEMPLATE_H

#include "core/resource.h"
#include "scene/resources/texture.h"

#include "item_template_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class Aura;
class Spell;

class ItemTemplate : public Resource {
	GDCLASS(ItemTemplate, Resource);

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

	int get_rarity();
	void set_rarity(int value);


	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);


	float get_scale_x();
	void set_scale_x(float value);

	float get_scale_y();
	void set_scale_y(float value);

	float get_scale_z();
	void set_scale_z(float value);


	Ref<Spell> get_spell();
	void set_spell(Ref<Spell> spell);

	Ref<Aura> get_aura(int index);
	void set_aura(int index, Ref<Aura> aura);


	int get_item_stat_modifier_count();
	void set_item_stat_modifier_count(int value);

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
	int _rarity;
	ItemEnums::ItemType _item_type;
	ItemEnums::ItemSubtype _item_sub_type;
	ItemEnums::ItemSubSubtype _item_sub_sub_type;

	Ref<Texture> _icon;

	float _scale_x;
	float _scale_y;
	float _scale_z;

	Ref<Spell> *_spell;
	Ref<Aura> *_auras[MAX_AURAS];

	int _modifier_count;
	Ref<ItemTemplateStatModifier> _modifiers[MAX_ITEM_STAT_MOD];
};

#endif
