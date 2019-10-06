#ifndef ITEM_TEMPLATE_H
#define ITEM_TEMPLATE_H

#include "core/resource.h"
#include "scene/resources/texture.h"
#include "core/vector.h"

#include "item_visual.h"
#include "item_template_stat_modifier.h"
#include "../entities/stats/stat.h"
#include "../item_enums.h"

class ItemInstance;
class Aura;
class Spell;

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

	ItemEnums::EquipSlots get_equip_slot() const;
	void set_equip_slot(const ItemEnums::EquipSlots value);

	Ref<ItemVisual> get_item_visual() const;
	void set_item_visual(const Ref<ItemVisual> value);

	int get_price() const;
	void set_price(const int value);

	int get_stack_size() const;
	void set_stack_size(const int value);
	
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
	
	//Teaches
	int get_num_teaches_spells();
	void set_num_teaches_spells(int value);

	Ref<Spell> get_teaches_spell(int index) const;
	void set_teaches_spell(int index, Ref<Spell> teaches_spell);

	Vector<Variant> get_teaches_spells();
	void set_teaches_spells(const Vector<Variant> &teaches_spells);

	//Grants Spells
	int get_num_grants_spells();
	void set_num_grants_spells(int value);

	Ref<Spell> get_grants_spell(int index) const;
	void set_grants_spell(int index, Ref<Spell> grants_spell);

	Vector<Variant> get_grants_spells();
	void set_grants_spells(const Vector<Variant> &grants_spells);

	//Auras
	int get_num_auras();
	void set_num_auras(int value);

	Ref<Aura> get_aura(int index) const;
	void set_aura(int index, Ref<Aura> aura);

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	//use spell
	Ref<Spell> get_use_spell() const;
	void set_use_spell(Ref<Spell> use_spell);

	//Stat mods
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
	};

	int _id;
	String _name_key;
	ItemEnums::ItemRarity _rarity;
	ItemEnums::ItemType _item_type;
	ItemEnums::ItemSubtype _item_sub_type;
	ItemEnums::ItemSubSubtype _item_sub_sub_type;
	ItemEnums::EquipSlots _equip_slot;

	int _price;

	Ref<ItemVisual> _item_visual;

	int _stack_size;
	
	Ref<Texture> _icon;

	float _scale_x;
	float _scale_y;
	float _scale_z;
	
	int _bag_size;

	Vector<Ref<Spell> > _teaches_spells;
	Vector<Ref<Spell> > _grants_spells;
	Vector<Ref<Aura> > _auras;
	Ref<Spell> _use_spell;

	int _modifier_count;
	Ref<ItemTemplateStatModifier> _modifiers[MAX_ITEM_STAT_MOD];
};

#endif
