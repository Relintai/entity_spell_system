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

#ifndef ENTITY_CLASS_DATA_H
#define ENTITY_CLASS_DATA_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#include "core/ustring.h"
#endif

#include "core/math/math_funcs.h"
#include "scene/resources/texture.h"

#include "../../entities/stats/stat_data.h"
#include "../../entity_enums.h"

#include "../../entities/auras/aura_data.h"
#include "../../pipelines/spell_damage_info.h"
#include "../../pipelines/spell_heal_info.h"

#include "../../item_enums.h"

#include "../resources/entity_resource.h"

class Spell;
class Entity;
class ItemInstance;
class CharacterSpec;
class Entity;
class SpellCastInfo;
class EntityAI;
class VendorItemData;
class ItemContainerData;
class CraftRecipe;
class StatData;

class EntityClassData : public Resource {
	GDCLASS(EntityClassData, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_text_description();
	void set_text_description(String value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	int get_spell_points_per_level();
	void set_spell_points_per_level(int value);

	EntityEnums::EntityClassPlaystyleType get_playstyle_type();
	void set_playstyle_type(EntityEnums::EntityClassPlaystyleType playstyle_type);

	Ref<StatData> get_stat_data();
	void set_stat_data(Ref<StatData> value);

	//Entity Resources
	int get_num_entity_resources();
	void set_num_entity_resources(int value);

	Ref<EntityResource> get_entity_resource(int index) const;
	void set_entity_resource(int index, Ref<EntityResource> entity_resources);

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

	Ref<Spell> get_aura(int index);
	void set_aura(int index, Ref<Spell> aura);

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	//Data
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

	EntityClassData();
	~EntityClassData();

protected:
	static void _bind_methods();

private:
	int _id;

	String _text_description;

	Ref<Texture> _icon;

	int _spell_points_per_level;

	EntityEnums::EntityClassPlaystyleType _playstyle_type;

	Ref<StatData> _stat_data;

	Vector<Ref<EntityResource> > _entity_resources;
	Vector<Ref<CharacterSpec> > _specs;
	Vector<Ref<Spell> > _spells;
	Vector<Ref<Spell> > _start_spells;
	Vector<Ref<Spell> > _auras;

	Ref<VendorItemData> _vendor_item_data;
	Ref<VendorItemData> _spell_train_data;
	Ref<ItemContainerData> _item_container_data;
	Vector<Ref<CraftRecipe> > _craft_recipes;

	Vector<Ref<EntityAI> > _ais;
};

#endif
