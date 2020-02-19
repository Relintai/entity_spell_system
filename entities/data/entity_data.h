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

#include "../../utility/category_cooldown.h"
#include "../../utility/cooldown.h"

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

	Ref<EntityData> get_inherits() const;
	void set_inherits(const Ref<EntityData> &value);

	EntityEnums::EntityType get_entity_type() const;
	void set_entity_type(const EntityEnums::EntityType value);

	EntityEnums::EntityInteractionType get_entity_interaction_type() const;
	void set_entity_interaction_type(const EntityEnums::EntityInteractionType value);

	int get_immunity_flags() const;
	void set_immunity_flags(const int value);

	int get_entity_flags() const;
	void set_entity_flags(const int value);

	EntityEnums::EntityController get_entity_controller() const;
	void set_entity_controller(const EntityEnums::EntityController value);

	int get_money() const;
	void set_money(int value);

	int get_bag_size() const;
	void set_bag_size(int value);

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

	Ref<AIFormation> get_formation() const;
	void set_formation(const Ref<AIFormation> data);

	Ref<LootDataBase> get_loot_db() const;
	void set_loot_db(const Ref<LootDataBase> data);

	Ref<VendorItemData> get_vendor_item_data() const;
	void set_vendor_item_data(const Ref<VendorItemData> data);

	Ref<ItemContainerData> get_item_container_data() const;
	void set_item_container_data(const Ref<ItemContainerData> data);

	//Craft Recipes
	int get_num_craft_recipes() const;

	Ref<CraftRecipe> get_craft_recipe(int index);
	void set_craft_recipe(int index, Ref<CraftRecipe> recipe);

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

	////    Spell System    ////

	void start_casting(int spell_id, Entity *caster, float spellScale);

	void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<SpellCastInfo> info);
	void son_cast_started(Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<SpellCastInfo> info);
	void son_spell_cast_success(Ref<SpellCastInfo> info);

	void son_before_damage_hit(Ref<SpellDamageInfo> data);
	void son_hit(Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<SpellDamageInfo> data);

	void son_before_heal_hit(Ref<SpellHealInfo> data);
	void son_before_heal(Ref<SpellHealInfo> data);
	void son_heal_receive(Ref<SpellHealInfo> data);
	void son_dealt_heal(Ref<SpellHealInfo> data);
	void son_heal_dealt(Ref<SpellHealInfo> data);

	void son_before_aura_applied(Ref<AuraData> data);
	void son_after_aura_applied(Ref<AuraData> data);

	void son_death(Entity *entity);
	void son_death_bind(Node *entity);

	void son_cooldown_added(Ref<Cooldown> cooldown);
	void son_cooldown_removed(Ref<Cooldown> cooldown);

	void son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void son_gcd_started(Entity *entity, float gcd);
	void son_gcd_finished(Entity *entity);
	void son_gcd_started_bind(Node *entity, float gcd);
	void son_gcd_finished_bind(Node *entity);

	void son_xp_gained(Entity *entity, int value);
	void son_xp_gained_bind(Node *entity, int value);
	void son_class_level_up(Entity *entity, int value);
	void son_class_level_up_bind(Node *entity, int value);
	void son_character_level_up(Entity *entity, int value);
	void son_character_level_up_bind(Node *entity, int value);

	//Clientside Event Handlers
	void con_cast_failed(Ref<SpellCastInfo> info);
	void con_cast_started(Ref<SpellCastInfo> info);
	void con_cast_state_changed(Ref<SpellCastInfo> info);
	void con_cast_finished(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);

	void con_death(Entity *entity);
	void con_death_bind(Node *entity);

	void con_cooldown_added(Ref<Cooldown> cooldown);
	void con_cooldown_removed(Ref<Cooldown> cooldown);
	void con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void con_aura_added(Ref<AuraData> data);
	void con_aura_removed(Ref<AuraData> data);
	void con_aura_refresh(Ref<AuraData> data);

	void con_damage_dealt(Ref<SpellDamageInfo> info);
	void con_dealt_damage(Ref<SpellDamageInfo> info);
	void con_heal_dealt(Ref<SpellHealInfo> info);
	void con_dealt_heal(Ref<SpellHealInfo> info);

	void con_gcd_started(Entity *entity, float gcd);
	void con_gcd_finished(Entity *entity);
	void con_gcd_started_bind(Node *entity, float gcd);
	void con_gcd_finished_bind(Node *entity);

	void con_xp_gained(Entity *entity, int value);
	void con_xp_gained_bind(Node *entity, int value);
	void con_class_level_up(Entity *entity, int value);
	void con_class_level_up_bind(Node *entity, int value);
	void con_character_level_up(Entity *entity, int value);
	void con_character_level_up_bind(Node *entity, int value);

	//Equipment

	bool should_deny_equip(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);
	bool should_deny_equip_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);

	void son_equip_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void son_equip_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void son_equip_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void son_equip_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void con_equip_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void con_equip_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void con_equip_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void con_equip_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	EntityData();
	~EntityData();

protected:
	static void _bind_methods();

private:
	int _id;

	Ref<EntityData> _inherits;

	EntityEnums::EntityType _entity_type;

	EntityEnums::EntityInteractionType _interaction_type;

	int _immunity_flags;
	int _entity_flags;
	EntityEnums::EntityController _entity_controller;

	String _text_description;

	int _money;
	int _bag_size;

	Ref<EntityClassData> _entity_class_data;
	Ref<EntitySpeciesData> _entity_species_data;
	Ref<EquipmentData> _equipment_data;

	Ref<EntityAI> _ai;
	Ref<AIFormation> _formation;

	Ref<LootDataBase> _lootdb;
	Ref<VendorItemData> _vendor_item_data;
	Ref<ItemContainerData> _item_container_data;
	Vector<Ref<CraftRecipe> > _craft_recipes;
};

#endif
