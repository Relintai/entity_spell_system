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

#ifndef ESS_RESOURCE_DB_H
#define ESS_RESOURCE_DB_H

#include "core/resource.h"

#include "core/variant.h"
#include "core/vector.h"

#include "core/ustring.h"

#include "core/bind/core_bind.h"

#include "../item_enums.h"

#include "../data/entities/xp_data.h"

#include "core/hash_map.h"

class Aura;
class Spell;
class EntityData;
class CraftRecipe;
class ItemTemplate;
class EntityResourceData;
class EntitySkillData;
class EntityCreateInfo;
class SpellCastInfo;
class EntitySpeciesData;

class ESSResourceDB : public Resource {
	GDCLASS(ESSResourceDB, Resource);

public:
	Ref<Aura> get_skill_for_armor_type(const int index);
	void set_skill_for_armor_type(const int index, const Ref<Aura> &aura);

	Ref<XPData> get_xp_data();
	void set_xp_data(const Ref<XPData> &data);

	virtual Ref<EntityResourceData> get_entity_resource(int class_id) = 0;
	virtual Ref<EntityResourceData> get_entity_resource_index(int index) = 0;
	virtual int get_entity_resource_count() = 0;
	virtual void add_entity_resource(Ref<EntityResourceData> cls);
	virtual Vector<Variant> get_entity_resources() const = 0;
	virtual void set_entity_resources(const Vector<Variant> &data) = 0;
	StringName entity_resource_id_to_path(const int id) const;
	int entity_resource_path_to_id(const StringName &path) const;

	virtual Ref<EntitySkillData> get_entity_skill(int class_id) = 0;
	virtual Ref<EntitySkillData> get_entity_skill_index(int index) = 0;
	virtual int get_entity_skill_count() = 0;
	virtual void add_entity_skill(Ref<EntitySkillData> cls);
	virtual Vector<Variant> get_entity_skills() const = 0;
	virtual void set_entity_skills(const Vector<Variant> &data) = 0;
	StringName entity_skill_id_to_path(const int id) const;
	int entity_skill_path_to_id(const StringName &path) const;

	virtual Ref<EntityData> get_entity_data(int class_id) = 0;
	virtual Ref<EntityData> get_entity_data_index(int index) = 0;
	virtual int get_entity_data_count() = 0;
	virtual void add_entity_data(Ref<EntityData> cls);
	virtual Vector<Variant> get_entity_datas() const = 0;
	virtual void set_entity_datas(const Vector<Variant> &data) = 0;
	StringName entity_data_id_to_path(const int id) const;
	int entity_data_path_to_id(const StringName &path) const;

	virtual Ref<Spell> get_spell(int spell_id) = 0;
	virtual Ref<Spell> get_spell_index(int index) = 0;
	virtual int get_spell_count() = 0;
	virtual void add_spell(Ref<Spell> spell);
	virtual Vector<Variant> get_spells() const = 0;
	virtual void set_spells(const Vector<Variant> &data) = 0;
	StringName spell_id_to_path(const int id) const;
	int spell_path_to_id(const StringName &path) const;

	virtual Ref<Aura> get_aura(int aura_id) = 0;
	virtual Ref<Aura> get_aura_index(int index) = 0;
	virtual int get_aura_count() = 0;
	virtual void add_aura(Ref<Aura> aura);
	virtual Vector<Variant> get_auras() const = 0;
	virtual void set_auras(const Vector<Variant> &data) = 0;
	StringName aura_id_to_path(const int id) const;
	int aura_path_to_id(const StringName &path) const;

	virtual Ref<CraftRecipe> get_craft_recipe(int craft_id) = 0;
	virtual Ref<CraftRecipe> get_craft_recipe_index(int index) = 0;
	virtual int get_craft_recipe_count() = 0;
	virtual void add_craft_recipe(Ref<CraftRecipe> aura);
	virtual Vector<Variant> get_craft_recipes() const = 0;
	virtual void set_craft_recipes(const Vector<Variant> &data) = 0;
	StringName craft_recipe_id_to_path(const int id) const;
	int craft_recipe_path_to_id(const StringName &path) const;

	virtual void add_item_template(Ref<ItemTemplate> aura);
	virtual Ref<ItemTemplate> get_item_template(int item_id) = 0;
	virtual Ref<ItemTemplate> get_item_template_index(int index) = 0;
	virtual int get_item_template_count() = 0;
	virtual Vector<Variant> get_item_templates() const = 0;
	virtual void set_item_templates(const Vector<Variant> &data) = 0;
	StringName item_template_id_to_path(const int id) const;
	int item_template_path_to_id(const StringName &path) const;

	virtual void add_entity_species_data(Ref<EntitySpeciesData> aura);
	virtual Ref<EntitySpeciesData> get_entity_species_data(int item_id) = 0;
	virtual Ref<EntitySpeciesData> get_entity_species_data_index(int index) = 0;
	virtual int get_entity_species_data_count() = 0;
	virtual Vector<Variant> get_entity_species_datas() const = 0;
	virtual void set_entity_species_datas(const Vector<Variant> &data) = 0;
	StringName entity_species_id_to_path(const int id) const;
	int entity_species_path_to_id(const StringName &path) const;

	virtual void clear();

	void add_entity_resource_db(Ref<ESSResourceDB> other);

	void initialize();

	ESSResourceDB();
	~ESSResourceDB();

protected:
	static void _bind_methods();

	Ref<XPData> _xp_data;

	Ref<Aura> _armor_type_skills[ItemEnums::ARMOR_TYPE_MAX];

	HashMap<int, StringName> _entity_resources_id_to_path;
	HashMap<StringName, int> _entity_resources_path_to_id;

	HashMap<int, StringName> _entity_skill_id_to_path;
	HashMap<StringName, int> _entity_skill_path_to_id;

	HashMap<int, StringName> _entity_data_id_to_path;
	HashMap<StringName, int> _entity_data_path_to_id;

	HashMap<int, StringName> _spell_id_to_path;
	HashMap<StringName, int> _spell_path_to_id;

	HashMap<int, StringName> _aura_id_to_path;
	HashMap<StringName, int> _aura_path_to_id;

	HashMap<int, StringName> _craft_recipe_id_to_path;
	HashMap<StringName, int> _craft_recipe_path_to_id;

	HashMap<int, StringName> _item_template_id_to_path;
	HashMap<StringName, int> _item_template_path_to_id;

	HashMap<int, StringName> _entity_species_id_to_path;
	HashMap<StringName, int> _entity_species_path_to_id;
};

#endif
