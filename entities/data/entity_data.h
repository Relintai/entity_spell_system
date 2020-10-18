/*
Copyright (c) 2019-2020 Péter Magyar

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

#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "scene/resources/texture.h"

#include "../../entities/stats/stat_data.h"
#include "../../entity_enums.h"

#include "../../entities/auras/aura_data.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../data/loot/loot_data_base.h"

#include "entity_class_data.h"
#include "item_container_data.h"

#include "../../data/items/equipment_data.h"

#include "../../data/species/entity_species_data.h"

#include "../../formations/ai_formation.h"
#include "../ai/entity_ai.h"

class Aura;
class Spell;
class Entity;
class CharacterSpec;
class Entity;
class SpellCastInfo;
class AIAction;
class VendorItemData;
class CraftRecipe;

class EntityData : public Resource {
	GDCLASS(EntityData, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	String get_text_description() const;
	void set_text_description(const String value);

	int get_entity_type() const;
	void set_entity_type(const int value);

	EntityEnums::EntityInteractionType get_entity_interaction_type() const;
	void set_entity_interaction_type(const EntityEnums::EntityInteractionType value);

	bool get_is_playable() const;
	void set_is_playable(const bool value);

	int get_immunity_flags() const;
	void set_immunity_flags(const int value);

	int get_entity_flags() const;
	void set_entity_flags(const int value);

	EntityEnums::EntityController get_entity_controller() const;
	void set_entity_controller(const EntityEnums::EntityController value);

	int get_money() const;
	void set_money(const int value);

	int get_bag_size() const;
	void set_bag_size(const int value);

	Ref<StatData> get_stat_data();
	void set_stat_data(Ref<StatData> value);

	Ref<EntitySpeciesData> get_entity_species_data() const;
	void set_entity_species_data(const Ref<EntitySpeciesData> &value);

	Ref<EntityClassData> get_entity_class_data() const;
	void set_entity_class_data(const Ref<EntityClassData> &data);

	Ref<EquipmentData> get_equipment_data() const;
	void set_equipment_data(const Ref<EquipmentData> &data);

	Ref<EntityAI> get_ai() const;
	void set_ai(const Ref<EntityAI> &ai);
	Ref<EntityAI> get_ai_instance();
	Ref<EntityAI> _get_ai_instance();

	Ref<LootDataBase> get_loot_db() const;
	void set_loot_db(const Ref<LootDataBase> &data);

	Ref<VendorItemData> get_vendor_item_data() const;
	void set_vendor_item_data(const Ref<VendorItemData> &data);

	Ref<VendorItemData> get_spell_train_data() const;
	void set_spell_train_data(const Ref<VendorItemData> &data);

	Ref<ItemContainerData> get_item_container_data() const;
	void set_item_container_data(const Ref<ItemContainerData> &data);

	//Craft Recipes
	int get_num_craft_recipes() const;

	Ref<CraftRecipe> get_craft_recipe(int index);
	void set_craft_recipe(int index, const Ref<CraftRecipe> &recipe);

	Vector<Variant> get_craft_recipes() const;
	void set_craft_recipes(const Vector<Variant> &recipe);

	String generate_name();

	//Setup
	void setup_resources(Entity *entity);

	////    Interactions    ////
	bool cans_interact(Entity *entity);
	bool cans_interact_bind(Node *entity);

	void sinteract(Entity *entity);
	void sinteract_bind(Node *entity);

	EntityData();
	~EntityData();

protected:
	void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

private:
	int _id;

	int _entity_type;

	EntityEnums::EntityInteractionType _interaction_type;

	bool _is_playable;

	int _immunity_flags;
	int _entity_flags;
	EntityEnums::EntityController _entity_controller;

	String _text_description;

	int _money;
	int _bag_size;

	Ref<StatData> _stat_data;
	Ref<EntityClassData> _entity_class_data;
	Ref<EntitySpeciesData> _entity_species_data;
	Ref<EquipmentData> _equipment_data;

	Ref<EntityAI> _ai;

	Ref<LootDataBase> _lootdb;
	Ref<VendorItemData> _vendor_item_data;
	Ref<VendorItemData> _spell_train_data;
	Ref<ItemContainerData> _item_container_data;
	Vector<Ref<CraftRecipe> > _craft_recipes;
};

#endif
