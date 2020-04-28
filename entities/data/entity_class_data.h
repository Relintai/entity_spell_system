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

#ifndef ENTITY_CLASS_DATA_H
#define ENTITY_CLASS_DATA_H

#include "core/math/math_funcs.h"
#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "scene/resources/texture.h"

#include "../../entities/stats/stat_data.h"
#include "../../entity_enums.h"

#include "../../entities/auras/aura_data.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../item_enums.h"
#include "../../utility/category_cooldown.h"
#include "../../utility/cooldown.h"

#include "../resources/entity_resource_data.h"

class Aura;
class Spell;
class Entity;
class ItemInstance;
class CharacterSpec;
class Entity;
class SpellCastInfo;
class EntityAI;

class EntityClassData : public Resource {
	GDCLASS(EntityClassData, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_text_description();
	void set_text_description(String value);

	Ref<EntityClassData> get_inherits();
	void set_inherits(Ref<EntityClassData> value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	Ref<StatData> get_stat_data();
	void set_stat_data(Ref<StatData> value);

	int get_spell_points_per_level();
	void set_spell_points_per_level(int value);

	EntityEnums::EntityClassPlaystyleType get_playstyle_type();
	void set_playstyle_type(EntityEnums::EntityClassPlaystyleType playstyle_type);

	//Entity Resources
	int get_num_entity_resources();
	void set_num_entity_resources(int value);

	Ref<EntityResourceData> get_entity_resource(int index) const;
	void set_entity_resource(int index, Ref<EntityResourceData> entity_resources);

	Vector<Variant> get_entity_resources();
	void set_entity_resources(const Vector<Variant> &entity_resourcess);

	//Specs
	int get_num_specs();
	void set_num_specs(int value);

	Ref<CharacterSpec> get_spec(int index) const;
	void set_spec(int index, Ref<CharacterSpec> spec);

	Vector<Variant> get_specs();
	void set_specs(const Vector<Variant> &specs);

	//Spells
	int get_num_spells();
	void set_num_spells(int value);

	Ref<Spell> get_spell(int index);
	void set_spell(int index, Ref<Spell> spell);

	Vector<Variant> get_spells();
	void set_spells(const Vector<Variant> &spells);

	//Start Spells
	int get_num_start_spells();
	void set_num_start_spells(int value);

	Ref<Spell> get_start_spell(int index);
	void set_start_spell(int index, Ref<Spell> spell);

	Vector<Variant> get_start_spells();
	void set_start_spells(const Vector<Variant> &spells);

	//Auras
	int get_num_auras();
	void set_num_auras(int value);

	Ref<Aura> get_aura(int index);
	void set_aura(int index, Ref<Aura> aura);

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	//AI
	int get_num_ais();
	void set_num_ais(int value);

	Ref<EntityAI> get_ai(int index);
	void set_ai(int index, Ref<EntityAI> aura);

	Vector<Variant> get_ais();
	void set_ais(const Vector<Variant> &ais);

	Ref<EntityAI> get_ai_instance();
	Ref<EntityAI> _get_ai_instance();

	//Setup
	void setup_resources(Entity *entity);
	void _setup_resources(Node *entity);

	////    Spell System    ////

	void start_casting(int spell_id, Entity *caster, float spellScale);

	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<SpellHealInfo> info);
	void notification_scast(int what, Ref<SpellCastInfo> info);
	void notification_sdamage(int what, Ref<SpellDamageInfo> info);

	void notification_sdeath(Entity *entity);
	void notification_sdeath_bind(Node *entity);

	void notification_scooldown_added(Ref<Cooldown> cooldown);
	void notification_scooldown_removed(Ref<Cooldown> cooldown);

	void notification_scategory_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void notification_scategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void notification_sgcd_started(Entity *entity, float gcd);
	void notification_sgcd_finished(Entity *entity);
	void notification_sgcd_started_bind(Node *entity, float gcd);
	void notification_sgcd_finished_bind(Node *entity);

	void notification_sxp_gained(Entity *entity, int value);
	void notification_sxp_gained_bind(Node *entity, int value);
	void notification_sclass_level_up(Entity *entity, int value);
	void notification_sclass_level_up_bind(Node *entity, int value);
	void notification_scharacter_level_up(Entity *entity, int value);
	void notification_scharacter_level_up_bind(Node *entity, int value);

	void notification_sentity_resource_added(Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<EntityResource> resource);

	//Clientside Event Handlers
	void notification_caura(int what, Ref<AuraData> data);
	void notification_cheal(int what, Ref<SpellHealInfo> info);
	void notification_ccast(int what, Ref<SpellCastInfo> info);
	void notification_cdamage(int what, Ref<SpellDamageInfo> info);

	void notification_cdeath(Entity *entity);
	void notification_cdeath_bind(Node *entity);

	void notification_ccooldown_added(Ref<Cooldown> cooldown);
	void notification_ccooldown_removed(Ref<Cooldown> cooldown);
	void notification_ccategory_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void notification_ccategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void notification_cgcd_started(Entity *entity, float gcd);
	void notification_cgcd_finished(Entity *entity);
	void notification_cgcd_started_bind(Node *entity, float gcd);
	void notification_cgcd_finished_bind(Node *entity);

	void notification_cxp_gained(Entity *entity, int value);
	void notification_cxp_gained_bind(Node *entity, int value);
	void notification_cclass_level_up(Entity *entity, int value);
	void notification_cclass_level_up_bind(Node *entity, int value);
	void notification_ccharacter_level_up(Entity *entity, int value);
	void notification_ccharacter_level_up_bind(Node *entity, int value);

	void notification_centity_resource_added(Ref<EntityResource> resource);
	void notification_centity_resource_removed(Ref<EntityResource> resource);

	//Equipment

	bool equip_should_deny(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);
	bool equip_should_deny_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);

	void equip_son_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void equip_con_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	EntityClassData();
	~EntityClassData();

protected:
	static void _bind_methods();

private:
	int _id;

	String _text_description;

	Ref<EntityClassData> _inherits;

	Ref<Texture> _icon;

	int _spell_points_per_level;

	EntityEnums::EntityClassPlaystyleType _playstyle_type;

	Ref<StatData> _stat_data;

	Vector<Ref<EntityResourceData> > _entity_resources;
	Vector<Ref<CharacterSpec> > _specs;
	Vector<Ref<Spell> > _spells;
	Vector<Ref<Spell> > _start_spells;
	Vector<Ref<Aura> > _auras;
	Vector<Ref<EntityAI> > _ais;
};

#endif
