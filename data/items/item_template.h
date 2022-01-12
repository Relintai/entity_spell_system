/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ITEM_TEMPLATE_H
#define ITEM_TEMPLATE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#endif

#include "scene/resources/texture.h"

#include "../../item_enums.h"
#include "model_visual.h"

class ItemInstance;
class Spell;
class EntityClassData;

class ItemTemplate : public Resource {
	GDCLASS(ItemTemplate, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	ItemEnums::ItemType get_item_type() const;
	void set_item_type(const ItemEnums::ItemType value);

	ItemEnums::ItemSubtype get_item_sub_type() const;
	void set_item_sub_type(const ItemEnums::ItemSubtype value);

	ItemEnums::ItemSubSubtype get_item_sub_sub_type() const;
	void set_item_sub_sub_type(const ItemEnums::ItemSubSubtype value);

	ItemEnums::ItemRarity get_rarity() const;
	void set_rarity(const ItemEnums::ItemRarity value);

	ItemEnums::ArmorType get_armor_type() const;
	void set_armor_type(const ItemEnums::ArmorType value);

	int get_equip_slot() const;
	void set_equip_slot(const int value);

	Ref<ModelVisual> get_model_visual() const;
	void set_model_visual(const Ref<ModelVisual> &value);

	Ref<EntityClassData> get_required_character_class() const;
	void set_required_character_class(const Ref<EntityClassData> &value);

	int get_price() const;
	void set_price(const int value);

	int get_stack_size() const;
	void set_stack_size(const int value);

	Ref<Texture> get_icon() const;
	void set_icon(const Ref<Texture> &value);

	float get_scale_x() const;
	void set_scale_x(const float value);

	float get_scale_y() const;
	void set_scale_y(const float value);

	float get_scale_z() const;
	void set_scale_z(const float value);

	int get_bag_size() const;
	void set_bag_size(const int size);

	String get_text_translation_key() const;
	void set_text_translation_key(const String &value);

	//Teaches
	int get_num_teaches_spells() const;
	void set_num_teaches_spells(const int value);

	Ref<Spell> get_teaches_spell(const int index);
	void set_teaches_spell(const int index, const Ref<Spell> &teaches_spell);

	Vector<Variant> get_teaches_spells();
	void set_teaches_spells(const Vector<Variant> &teaches_spells);

	//Grants Spells
	int get_num_grants_spells() const;
	void set_num_grants_spells(const int value);

	Ref<Spell> get_grants_spell(const int index);
	void set_grants_spell(const int index, const Ref<Spell> &grants_spell);

	Vector<Variant> get_grants_spells();
	void set_grants_spells(const Vector<Variant> &grants_spells);

	//Auras
	int get_num_auras() const;
	void set_num_auras(const int value);

	Ref<Spell> get_aura(const int index);
	void set_aura(const int index, const Ref<Spell> &aura);

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	//Required Skills
	int get_num_required_skills() const;

	Ref<Spell> get_required_skill(const int index);
	void set_required_skill(const int index, const Ref<Spell> &skills);

	Vector<Variant> get_required_skills();
	void set_required_skills(const Vector<Variant> &grants_spells);

	//use spell
	Ref<Spell> get_use_spell();
	void set_use_spell(const Ref<Spell> &use_spell);

	int get_charges() const;
	void set_charges(const int value);

	bool get_consumed() const;
	void set_consumed(const bool value);

	//Stat mods
	int stat_modifier_get_count() const;
	void stat_modifier_set_count(const int value);

	int stat_modifier_get_stat_id(int index) const;
	void stat_modifier_set_stat_id(int index, int value);

	float stat_modifier_get_min_base_mod(const int index) const;
	void stat_modifier_set_min_base_mod(const int index, const float value);

	float stat_modifier_get_max_base_mod(const int index) const;
	void stat_modifier_set_max_base_mod(const int index, const float value);

	float stat_modifier_get_min_bonus_mod(const int index) const;
	void stat_modifier_set_min_bonus_mod(const int index, const float value);

	float stat_modifier_get_max_bonus_mod(const int index) const;
	void stat_modifier_set_max_bonus_mod(const int index, const float value);

	float stat_modifier_get_min_percent_mod(const int index) const;
	void stat_modifier_set_min_percent_mod(const int index, const float value);

	float stat_modifier_get_max_percent_mod(const int index) const;
	void stat_modifier_set_max_percent_mod(const int index, const float value);

	float stat_modifier_get_scaling_factor(const int index) const;
	void stat_modifier_set_scaling_factor(const int index, const float value);

	int get_animator_weapon_type();

	Ref<ItemInstance> create_item_instance();

	String get_description();

	ItemTemplate();
	~ItemTemplate();

public:
	struct SkillEntry {
		Ref<Spell> aura;
		int level;
	};

protected:
	void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

protected:
	struct ItemTemplateStatModifier {
		int stat_id;

		float min_base_mod;
		float max_base_mod;

		float min_bonus_mod;
		float max_bonus_mod;

		float min_percent_mod;
		float max_percent_mod;

		float scaling_factor;

		ItemTemplateStatModifier() {
			stat_id = 0;
			min_base_mod = 0;
			max_base_mod = 0;
			min_bonus_mod = 0;
			max_bonus_mod = 0;
			min_percent_mod = 0;
			max_percent_mod = 0;
			scaling_factor = 1;
		}
	};

private:
	enum {
		MAX_ITEM_STAT_MOD = 6,
	};

	int _id;
	ItemEnums::ItemRarity _rarity;
	ItemEnums::ItemType _item_type;
	ItemEnums::ItemSubtype _item_sub_type;
	ItemEnums::ItemSubSubtype _item_sub_sub_type;
	ItemEnums::ArmorType _armor_type;
	int _equip_slot;

	int _price;

	Ref<EntityClassData> _required_character_class;
	Ref<ModelVisual> _model_visual;

	int _stack_size;

	Ref<Texture> _icon;

	float _scale_x;
	float _scale_y;
	float _scale_z;

	int _bag_size;

	String _text_translation_key;

	Vector<Ref<Spell> > _teaches_spells;
	Vector<Ref<Spell> > _grants_spells;
	Vector<Ref<Spell> > _auras;
	Vector<Ref<Spell> > _required_skills;
	Ref<Spell> _use_spell;
	int _charges;
	bool _consumed;

	int _modifier_count;
	ItemTemplateStatModifier _modifiers[MAX_ITEM_STAT_MOD];
};

#endif
