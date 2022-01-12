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

#include "ess_resource_db_static.h"

#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource.h"
#include "../entities/skills/entity_skill_data.h"

bool ESSResourceDBStatic::get_remap_ids() const {
	return _remap_ids;
}
void ESSResourceDBStatic::set_remap_ids(const bool value) {
	_remap_ids = value;
}

Ref<EntityResource> ESSResourceDBStatic::get_entity_resource(int id) {
	if (id < 0 || id >= _entity_resources.size())
		return Ref<EntityResource>();

	return _entity_resources.get(id);
}
Ref<EntityResource> ESSResourceDBStatic::get_entity_resource_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResource>(NULL));

	return _entity_resources.get(index);
}
int ESSResourceDBStatic::get_entity_resource_count() {
	return _entity_resources.size();
}
void ESSResourceDBStatic::add_entity_resource(Ref<EntityResource> cls) {
	if (_remap_ids && cls.is_valid())
		cls->set_id(_entity_resources.size());

	_entity_resources.push_back(cls);

	ESSResourceDB::add_entity_resource(cls);
}
Vector<Variant> ESSResourceDBStatic::get_entity_resources() const {
	VARIANT_ARRAY_GET(_entity_resources);
}
void ESSResourceDBStatic::set_entity_resources(const Vector<Variant> &data) {
	_entity_resources.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		add_entity_resource(d);
	}
}

Ref<EntitySkillData> ESSResourceDBStatic::get_entity_skill(int id) {
	if (id < 0 || id >= _entity_skills.size())
		return Ref<EntitySkillData>();

	return _entity_skills.get(id);
}
Ref<EntitySkillData> ESSResourceDBStatic::get_entity_skill_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_skills.size(), Ref<EntitySkillData>(NULL));

	return _entity_skills.get(index);
}
int ESSResourceDBStatic::get_entity_skill_count() {
	return _entity_skills.size();
}
void ESSResourceDBStatic::add_entity_skill(Ref<EntitySkillData> cls) {
	if (_remap_ids && cls.is_valid())
		cls->set_id(_entity_skills.size());

	_entity_skills.push_back(cls);

	ESSResourceDB::add_entity_skill(cls);
}
Vector<Variant> ESSResourceDBStatic::get_entity_skills() const {
	VARIANT_ARRAY_GET(_entity_skills);
}
void ESSResourceDBStatic::set_entity_skills(const Vector<Variant> &data) {
	_entity_skills.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySkillData> d = Ref<EntitySkillData>(data[i]);

		add_entity_skill(d);
	}
}

Ref<EntityData> ESSResourceDBStatic::get_entity_data(int id) {
	if (id < 0 || id >= _entity_datas.size())
		return Ref<EntityData>();

	return _entity_datas.get(id);
}
Ref<EntityData> ESSResourceDBStatic::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}
int ESSResourceDBStatic::get_entity_data_count() {
	return _entity_datas.size();
}
void ESSResourceDBStatic::add_entity_data(Ref<EntityData> cls) {
	if (_remap_ids && cls.is_valid())
		cls->set_id(_entity_datas.size());

	_entity_datas.push_back(cls);

	ESSResourceDB::add_entity_data(cls);
}
Vector<Variant> ESSResourceDBStatic::get_entity_datas() const {
	VARIANT_ARRAY_GET(_entity_datas);
}
void ESSResourceDBStatic::set_entity_datas(const Vector<Variant> &data) {
	_entity_datas.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityData> d = Ref<EntityData>(data[i]);

		add_entity_data(d);
	}
}

Ref<Spell> ESSResourceDBStatic::get_spell(int id) {
	if (id < 0 || id >= _spells.size())
		return Ref<Spell>();

	return _spells.get(id);
}

Ref<Spell> ESSResourceDBStatic::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}
int ESSResourceDBStatic::get_spell_count() {
	return _spells.size();
}
void ESSResourceDBStatic::add_spell(Ref<Spell> spell) {
	if (_remap_ids && spell.is_valid())
		spell->set_id(_spells.size());

	_spells.push_back(spell);

	ESSResourceDB::add_spell(spell);
}
Vector<Variant> ESSResourceDBStatic::get_spells() const {
	VARIANT_ARRAY_GET(_spells);
}
void ESSResourceDBStatic::set_spells(const Vector<Variant> &data) {
	_spells.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Spell> d = Ref<Spell>(data[i]);

		add_spell(d);
	}
}

//Craft Data
void ESSResourceDBStatic::add_craft_recipe(Ref<CraftRecipe> cda) {
	if (_remap_ids && cda.is_valid())
		cda->set_id(_craft_recipes.size());

	_craft_recipes.push_back(cda);

	ESSResourceDB::add_craft_recipe(cda);
}

Ref<CraftRecipe> ESSResourceDBStatic::get_craft_recipe(int id) {
	if (id < 0 || id >= _craft_recipes.size())
		return Ref<CraftRecipe>();

	return _craft_recipes.get(id);
}

Ref<CraftRecipe> ESSResourceDBStatic::get_craft_recipe_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes.get(index);
}

int ESSResourceDBStatic::get_craft_recipe_count() {
	return _craft_recipes.size();
}

Vector<Variant> ESSResourceDBStatic::get_craft_recipes() const {
	VARIANT_ARRAY_GET(_craft_recipes);
}
void ESSResourceDBStatic::set_craft_recipes(const Vector<Variant> &data) {
	_craft_recipes.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<CraftRecipe> d = Ref<CraftRecipe>(data[i]);

		add_craft_recipe(d);
	}
}

void ESSResourceDBStatic::add_item_template(Ref<ItemTemplate> cda) {
	if (_remap_ids && cda.is_valid())
		cda->set_id(_item_templates.size());

	_item_templates.push_back(cda);

	ESSResourceDB::add_item_template(cda);
}

Ref<ItemTemplate> ESSResourceDBStatic::get_item_template(int item_id) {
	if (item_id < 0 || item_id >= _item_templates.size())
		return Ref<ItemTemplate>();

	return _item_templates.get(item_id);
}

Ref<ItemTemplate> ESSResourceDBStatic::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>());

	return _item_templates.get(index);
}

int ESSResourceDBStatic::get_item_template_count() {
	return _item_templates.size();
}
Vector<Variant> ESSResourceDBStatic::get_item_templates() const {
	VARIANT_ARRAY_GET(_item_templates);
}
void ESSResourceDBStatic::set_item_templates(const Vector<Variant> &data) {
	_item_templates.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<ItemTemplate> d = Ref<ItemTemplate>(data[i]);

		add_item_template(d);
	}
}

void ESSResourceDBStatic::add_entity_species_data(Ref<EntitySpeciesData> cda) {
	if (_remap_ids && cda.is_valid())
		cda->set_id(_entity_species_datas.size());

	_entity_species_datas.push_back(cda);

	ESSResourceDB::add_entity_species_data(cda);
}
Ref<EntitySpeciesData> ESSResourceDBStatic::get_entity_species_data(int id) {
	if (id < 0 || id > _entity_species_datas.size())
		return Ref<EntitySpeciesData>();

	return _entity_species_datas.get(id);
}
Ref<EntitySpeciesData> ESSResourceDBStatic::get_entity_species_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_species_datas.size(), Ref<EntitySpeciesData>());

	return _entity_species_datas.get(index);
}
int ESSResourceDBStatic::get_entity_species_data_count() {
	return _entity_species_datas.size();
}
Vector<Variant> ESSResourceDBStatic::get_entity_species_datas() const {
	VARIANT_ARRAY_GET(_entity_species_datas);
}
void ESSResourceDBStatic::set_entity_species_datas(const Vector<Variant> &data) {
	_entity_species_datas.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySpeciesData> d = Ref<EntitySpeciesData>(data[i]);

		add_entity_species_data(d);
	}
}

void ESSResourceDBStatic::clear() {
	_entity_resources.clear();
	_entity_skills.clear();
	_entity_datas.clear();
	_spells.clear();
	_craft_recipes.clear();
	_item_templates.clear();
	_entity_species_datas.clear();
}

ESSResourceDBStatic::ESSResourceDBStatic() {
	_remap_ids = false;
}

ESSResourceDBStatic::~ESSResourceDBStatic() {
	_entity_resources.clear();
	_entity_skills.clear();
	_entity_datas.clear();
	_spells.clear();
	_craft_recipes.clear();
	_item_templates.clear();
	_entity_species_datas.clear();
}

void ESSResourceDBStatic::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_remap_ids"), &ESSResourceDBStatic::get_remap_ids);
	ClassDB::bind_method(D_METHOD("set_remap_ids", "value"), &ESSResourceDBStatic::set_remap_ids);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "remap_ids"), "set_remap_ids", "get_remap_ids");

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_resources", PROPERTY_HINT_NONE, "17/17:EntityResource", PROPERTY_USAGE_DEFAULT, "EntityResource"), "set_entity_resources", "get_entity_resources");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_skills", PROPERTY_HINT_NONE, "17/17:EntitySkillData", PROPERTY_USAGE_DEFAULT, "EntitySkillData"), "set_entity_skills", "get_entity_skills");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_datas", PROPERTY_HINT_NONE, "17/17:EntityData", PROPERTY_USAGE_DEFAULT, "EntityData"), "set_entity_datas", "get_entity_datas");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "craft_recipes", PROPERTY_HINT_NONE, "17/17:CraftRecipe", PROPERTY_USAGE_DEFAULT, "CraftRecipe"), "set_craft_recipes", "get_craft_recipes");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "item_templates", PROPERTY_HINT_NONE, "17/17:ItemTemplate", PROPERTY_USAGE_DEFAULT, "ItemTemplate"), "set_item_templates", "get_item_templates");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_species_datas", PROPERTY_HINT_NONE, "17/17:EntitySpeciesData", PROPERTY_USAGE_DEFAULT, "EntitySpeciesData"), "set_entity_species_datas", "get_entity_species_datas");
}
