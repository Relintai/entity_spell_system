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

#include "ess_resource_db_map.h"

#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource.h"
#include "../entities/skills/entity_skill_data.h"

Ref<EntityResource> ESSResourceDBMap::get_entity_resource(int class_id) {
	//ERR_FAIL_COND_V_MSG(!_entity_resource_map.has(class_id), Ref<EntityResource>(), "Could not find EntityResource! Id:" + String::num(class_id));

	if (!_entity_resource_map.has(class_id)) {
		return Ref<EntityResource>();
	}

	return _entity_resource_map.get(class_id);
}
Ref<EntityResource> ESSResourceDBMap::get_entity_resource_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResource>(NULL));

	return _entity_resources.get(index);
}
int ESSResourceDBMap::get_entity_resource_count() {
	return _entity_resources.size();
}
void ESSResourceDBMap::add_entity_resource(Ref<EntityResource> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_resources.push_back(cls);
	_entity_resource_map.set(cls->get_id(), cls);

	ESSResourceDB::add_entity_resource(cls);
}
Vector<Variant> ESSResourceDBMap::get_entity_resources() const {
	VARIANT_ARRAY_GET(_entity_resources);
}
void ESSResourceDBMap::set_entity_resources(const Vector<Variant> &data) {
	_entity_resources.clear();
	_entity_resource_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_resource(d);
	}
}

Ref<EntitySkillData> ESSResourceDBMap::get_entity_skill(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_skill_map.has(class_id), Ref<EntitySkillData>(), "Could not find EntitySkillData! Id:" + String::num(class_id));

	return _entity_skill_map.get(class_id);
}
Ref<EntitySkillData> ESSResourceDBMap::get_entity_skill_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_skills.size(), Ref<EntitySkillData>(NULL));

	return _entity_skills.get(index);
}
int ESSResourceDBMap::get_entity_skill_count() {
	return _entity_skills.size();
}
void ESSResourceDBMap::add_entity_skill(Ref<EntitySkillData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_skills.push_back(cls);
	_entity_skill_map.set(cls->get_id(), cls);

	ESSResourceDB::add_entity_skill(cls);
}
Vector<Variant> ESSResourceDBMap::get_entity_skills() const {
	VARIANT_ARRAY_GET(_entity_skills);
}
void ESSResourceDBMap::set_entity_skills(const Vector<Variant> &data) {
	_entity_skills.clear();
	_entity_skill_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySkillData> d = Ref<EntitySkillData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_skill(d);
	}
}

Ref<EntityData> ESSResourceDBMap::get_entity_data(int class_id) {
	ERR_FAIL_COND_V_MSG(!_entity_data_map.has(class_id), Ref<EntityData>(), "Could not find EntityData! Id:" + String::num(class_id));

	return _entity_data_map.get(class_id);
}
Ref<EntityData> ESSResourceDBMap::get_entity_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_datas.size(), Ref<EntityData>(NULL));

	return _entity_datas.get(index);
}
int ESSResourceDBMap::get_entity_data_count() {
	return _entity_datas.size();
}
void ESSResourceDBMap::add_entity_data(Ref<EntityData> cls) {
	ERR_FAIL_COND(!cls.is_valid());

	_entity_datas.push_back(cls);
	_entity_data_map.set(cls->get_id(), cls);

	ESSResourceDB::add_entity_data(cls);
}
Vector<Variant> ESSResourceDBMap::get_entity_datas() const {
	VARIANT_ARRAY_GET(_entity_datas);
}
void ESSResourceDBMap::set_entity_datas(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntityResource> d = Ref<EntityResource>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_entity_data(d);
	}
}

Ref<Spell> ESSResourceDBMap::get_spell(int spell_id) {
	ERR_FAIL_COND_V_MSG(!_spell_map.has(spell_id), Ref<Spell>(), "Could not find Spell! Id:" + String::num(spell_id));

	return _spell_map.get(spell_id);
}

Ref<Spell> ESSResourceDBMap::get_spell_index(int index) {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>(NULL));

	return _spells.get(index);
}
int ESSResourceDBMap::get_spell_count() {
	return _spells.size();
}
void ESSResourceDBMap::add_spell(Ref<Spell> spell) {
	ERR_FAIL_COND(!spell.is_valid());

	_spells.push_back(spell);
	_spell_map.set(spell->get_id(), spell);

	ESSResourceDB::add_spell(spell);
}
Vector<Variant> ESSResourceDBMap::get_spells() const {
	VARIANT_ARRAY_GET(_spells);
}
void ESSResourceDBMap::set_spells(const Vector<Variant> &data) {
	_spells.clear();
	_spell_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<Spell> d = Ref<Spell>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_spell(d);
	}
}

//Craft Data
void ESSResourceDBMap::add_craft_recipe(Ref<CraftRecipe> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_craft_recipes.push_back(cda);
	_craft_recipe_map.set(cda->get_id(), cda);

	ESSResourceDB::add_craft_recipe(cda);
}

Ref<CraftRecipe> ESSResourceDBMap::get_craft_recipe(int craft_id) {
	ERR_FAIL_COND_V_MSG(!_craft_recipe_map.has(craft_id), Ref<CraftRecipe>(), "Could not find CraftRecipe! Id:" + String::num(craft_id));

	return _craft_recipe_map.get(craft_id);
}

Ref<CraftRecipe> ESSResourceDBMap::get_craft_recipe_index(int index) {
	ERR_FAIL_INDEX_V(index, _craft_recipes.size(), Ref<CraftRecipe>());

	return _craft_recipes.get(index);
}

int ESSResourceDBMap::get_craft_recipe_count() {
	return _craft_recipes.size();
}

Vector<Variant> ESSResourceDBMap::get_craft_recipes() const {
	VARIANT_ARRAY_GET(_craft_recipes);
}
void ESSResourceDBMap::set_craft_recipes(const Vector<Variant> &data) {
	_craft_recipes.clear();
	_craft_recipe_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<CraftRecipe> d = Ref<CraftRecipe>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_craft_recipe(d);
	}
}

void ESSResourceDBMap::add_item_template(Ref<ItemTemplate> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_item_templates.push_back(cda);
	_item_template_map.set(cda->get_id(), cda);

	ESSResourceDB::add_item_template(cda);
}

Ref<ItemTemplate> ESSResourceDBMap::get_item_template(int item_id) {
	ERR_FAIL_COND_V_MSG(!_item_template_map.has(item_id), Ref<ItemTemplate>(), "Could not find ItemTemplate! Id:" + String::num(item_id));

	return _item_template_map.get(item_id);
}

Ref<ItemTemplate> ESSResourceDBMap::get_item_template_index(int index) {
	ERR_FAIL_INDEX_V(index, _item_templates.size(), Ref<ItemTemplate>());

	return _item_templates.get(index);
}

int ESSResourceDBMap::get_item_template_count() {
	return _item_templates.size();
}
Vector<Variant> ESSResourceDBMap::get_item_templates() const {
	VARIANT_ARRAY_GET(_item_templates);
}
void ESSResourceDBMap::set_item_templates(const Vector<Variant> &data) {
	_item_templates.clear();
	_item_template_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<ItemTemplate> d = Ref<ItemTemplate>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

void ESSResourceDBMap::add_entity_species_data(Ref<EntitySpeciesData> cda) {
	ERR_FAIL_COND(!cda.is_valid());

	_entity_species_datas.push_back(cda);
	_entity_species_data_map.set(cda->get_id(), cda);

	ESSResourceDB::add_entity_species_data(cda);
}
Ref<EntitySpeciesData> ESSResourceDBMap::get_entity_species_data(int item_id) {
	if (!_entity_species_data_map.has(item_id))
		return Ref<EntitySpeciesData>();

	return _entity_species_data_map.get(item_id);
}
Ref<EntitySpeciesData> ESSResourceDBMap::get_entity_species_data_index(int index) {
	ERR_FAIL_INDEX_V(index, _entity_species_datas.size(), Ref<EntitySpeciesData>());

	return _entity_species_datas.get(index);
}
int ESSResourceDBMap::get_entity_species_data_count() {
	return _entity_species_datas.size();
}
Vector<Variant> ESSResourceDBMap::get_entity_species_datas() const {
	VARIANT_ARRAY_GET(_entity_species_datas);
}
void ESSResourceDBMap::set_entity_species_datas(const Vector<Variant> &data) {
	_entity_species_datas.clear();
	_entity_species_data_map.clear();
	for (int i = 0; i < data.size(); i++) {
		Ref<EntitySpeciesData> d = Ref<EntitySpeciesData>(data[i]);

		ERR_CONTINUE(!d.is_valid());

		add_item_template(d);
	}
}

ESSResourceDBMap::ESSResourceDBMap() {
}

ESSResourceDBMap::~ESSResourceDBMap() {
	_entity_resources.clear();
	_entity_resource_map.clear();

	_entity_skills.clear();
	_entity_skill_map.clear();

	_entity_datas.clear();
	_entity_data_map.clear();

	_spells.clear();
	_spell_map.clear();

	_craft_recipes.clear();
	_craft_recipe_map.clear();

	_item_templates.clear();
	_item_template_map.clear();

	_entity_species_datas.clear();
	_entity_species_data_map.clear();
}

void ESSResourceDBMap::_bind_methods() {
}
