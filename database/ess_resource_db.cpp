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

#include "ess_resource_db.h"

#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource.h"
#include "../entities/skills/entity_skill_data.h"

Ref<Spell> ESSResourceDB::get_skill_for_armor_type(const int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::ARMOR_TYPE_MAX, Ref<Spell>());

	return _armor_type_skills[index];
}
void ESSResourceDB::set_skill_for_armor_type(const int index, const Ref<Spell> &aura) {
	ERR_FAIL_INDEX(index, ItemEnums::ARMOR_TYPE_MAX);

	_armor_type_skills[index] = aura;
}

void ESSResourceDB::add_entity_resource(Ref<EntityResource> cls) {
	if (!cls.is_valid())
		return;

	_entity_resources_id_to_path.set(cls->get_id(), cls->get_path());
	_entity_resources_path_to_id.set(cls->get_path(), cls->get_id());
}

Ref<EntityResource> ESSResourceDB::get_entity_resource_path(const StringName &path) {
	return get_entity_resource(entity_resource_path_to_id(path));
}

void ESSResourceDB::add_entity_skill(Ref<EntitySkillData> cls) {
	if (!cls.is_valid())
		return;

	_entity_skill_id_to_path.set(cls->get_id(), cls->get_path());
	_entity_skill_path_to_id.set(cls->get_path(), cls->get_id());
}

Ref<EntitySkillData> ESSResourceDB::get_entity_skill_path(const StringName &path) {
	return get_entity_skill(entity_skill_path_to_id(path));
}

void ESSResourceDB::add_entity_data(Ref<EntityData> cls) {
	if (!cls.is_valid())
		return;

	_entity_data_id_to_path.set(cls->get_id(), cls->get_path());
	_entity_data_path_to_id.set(cls->get_path(), cls->get_id());
}

Ref<EntityData> ESSResourceDB::get_entity_data_path(const StringName &path) {
	return get_entity_data(entity_data_path_to_id(path));
}

void ESSResourceDB::add_spell(Ref<Spell> spell) {
	if (!spell.is_valid())
		return;

	_spell_id_to_path.set(spell->get_id(), spell->get_path());
	_spell_path_to_id.set(spell->get_path(), spell->get_id());
}

Ref<Spell> ESSResourceDB::get_spell_path(const StringName &path) {
	return get_spell(spell_path_to_id(path));
}

void ESSResourceDB::add_craft_recipe(Ref<CraftRecipe> cda) {
	if (!cda.is_valid())
		return;

	_craft_recipe_id_to_path.set(cda->get_id(), cda->get_path());
	_craft_recipe_path_to_id.set(cda->get_path(), cda->get_id());
}

Ref<CraftRecipe> ESSResourceDB::get_craft_recipe_path(const StringName &path) {
	return get_craft_recipe(craft_recipe_path_to_id(path));
}

void ESSResourceDB::add_item_template(Ref<ItemTemplate> cda) {
	if (!cda.is_valid())
		return;

	_item_template_id_to_path.set(cda->get_id(), cda->get_path());
	_item_template_path_to_id.set(cda->get_path(), cda->get_id());
}

Ref<ItemTemplate> ESSResourceDB::get_item_template_path(const StringName &path) {
	return get_item_template(item_template_path_to_id(path));
}

void ESSResourceDB::add_entity_species_data(Ref<EntitySpeciesData> cda) {
	if (!cda.is_valid())
		return;

	_entity_species_id_to_path.set(cda->get_id(), cda->get_path());
	_entity_species_path_to_id.set(cda->get_path(), cda->get_id());
}

Ref<EntitySpeciesData> ESSResourceDB::get_entity_species_data_path(const StringName &path) {
	return get_entity_species_data(entity_species_path_to_id(path));
}

StringName ESSResourceDB::entity_resource_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_entity_resources_id_to_path.has(id), StringName());

	return _entity_resources_id_to_path[id];
}
int ESSResourceDB::entity_resource_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_entity_resources_path_to_id.has(path), 0);

	return _entity_resources_path_to_id[path];
}

StringName ESSResourceDB::entity_skill_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_entity_skill_id_to_path.has(id), StringName());

	return _entity_skill_id_to_path[id];
}
int ESSResourceDB::entity_skill_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_entity_skill_path_to_id.has(path), 0);

	return _entity_skill_path_to_id[path];
}

StringName ESSResourceDB::entity_data_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_entity_data_id_to_path.has(id), StringName());

	return _entity_data_id_to_path[id];
}
int ESSResourceDB::entity_data_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_entity_data_path_to_id.has(path), 0);

	return _entity_data_path_to_id[path];
}

StringName ESSResourceDB::spell_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_spell_id_to_path.has(id), StringName());

	return _spell_id_to_path[id];
}
int ESSResourceDB::spell_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_spell_path_to_id.has(path), 0);

	return _spell_path_to_id[path];
}

StringName ESSResourceDB::craft_recipe_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_craft_recipe_id_to_path.has(id), StringName());

	return _craft_recipe_id_to_path[id];
}
int ESSResourceDB::craft_recipe_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_craft_recipe_path_to_id.has(path), 0);

	return _craft_recipe_path_to_id[path];
}

StringName ESSResourceDB::item_template_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_item_template_id_to_path.has(id), StringName());

	return _item_template_id_to_path[id];
}
int ESSResourceDB::item_template_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_item_template_path_to_id.has(path), 0);

	return _item_template_path_to_id[path];
}

StringName ESSResourceDB::entity_species_id_to_path(const int id) const {
	ERR_FAIL_COND_V(!_entity_species_id_to_path.has(id), StringName());

	return _entity_species_id_to_path[id];
}
int ESSResourceDB::entity_species_path_to_id(const StringName &path) const {
	ERR_FAIL_COND_V(!_entity_species_path_to_id.has(path), 0);

	return _entity_species_path_to_id[path];
}

void ESSResourceDB::clear() {
}

void ESSResourceDB::add_entity_resource_db(Ref<ESSResourceDB> other) {
	if (!other.is_valid())
		return;

	for (int i = 0; i < other->get_entity_resource_count(); ++i) {
		add_entity_resource(other->get_entity_resource_index(i));
	}

	for (int i = 0; i < other->get_entity_skill_count(); ++i) {
		add_entity_skill(other->get_entity_skill_index(i));
	}

	for (int i = 0; i < other->get_entity_data_count(); ++i) {
		add_entity_data(other->get_entity_data_index(i));
	}

	for (int i = 0; i < other->get_spell_count(); ++i) {
		add_spell(other->get_spell_index(i));
	}

	for (int i = 0; i < other->get_craft_recipe_count(); ++i) {
		add_craft_recipe(other->get_craft_recipe_index(i));
	}

	for (int i = 0; i < other->get_item_template_count(); ++i) {
		add_item_template(other->get_item_template_index(i));
	}

	for (int i = 0; i < other->get_entity_species_data_count(); ++i) {
		add_entity_species_data(other->get_entity_species_data_index(i));
	}
}

void ESSResourceDB::initialize() {
	if (has_method("_initialize"))
		call("_initialize");
}

ESSResourceDB::ESSResourceDB() {
}

ESSResourceDB::~ESSResourceDB() {
	_entity_resources_path_to_id.clear();
	_entity_resources_id_to_path.clear();

	_entity_skill_path_to_id.clear();
	_entity_skill_id_to_path.clear();

	_entity_data_path_to_id.clear();
	_entity_data_id_to_path.clear();

	_spell_path_to_id.clear();
	_spell_id_to_path.clear();

	_craft_recipe_path_to_id.clear();
	_craft_recipe_id_to_path.clear();

	_item_template_path_to_id.clear();
	_item_template_id_to_path.clear();

	_entity_species_path_to_id.clear();
	_entity_species_id_to_path.clear();
}

void ESSResourceDB::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_skill_for_armor_type", "index"), &ESSResourceDB::get_skill_for_armor_type);
	ClassDB::bind_method(D_METHOD("set_skill_for_armor_type", "index", "aura"), &ESSResourceDB::set_skill_for_armor_type);

	for (int i = 0; i < ItemEnums::ARMOR_TYPE_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "skill_for_armor_type_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_skill_for_armor_type", "get_skill_for_armor_type", i);
	}

	//EntityResource
	ClassDB::bind_method(D_METHOD("add_entity_resource", "cls"), &ESSResourceDB::add_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource", "class_id"), &ESSResourceDB::get_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource_index", "index"), &ESSResourceDB::get_entity_resource_index);
	ClassDB::bind_method(D_METHOD("get_entity_resource_count"), &ESSResourceDB::get_entity_resource_count);
	ClassDB::bind_method(D_METHOD("get_entity_resources"), &ESSResourceDB::get_entity_resources);
	ClassDB::bind_method(D_METHOD("set_entity_resources", "recipe"), &ESSResourceDB::set_entity_resources);

	ClassDB::bind_method(D_METHOD("get_entity_resource_path", "path"), &ESSResourceDB::get_entity_resource_path);
	ClassDB::bind_method(D_METHOD("entity_resource_id_to_path", "id"), &ESSResourceDB::entity_resource_id_to_path);
	ClassDB::bind_method(D_METHOD("entity_resource_path_to_id", "path"), &ESSResourceDB::entity_resource_path_to_id);

	//EntitySkills
	ClassDB::bind_method(D_METHOD("add_entity_skill", "cls"), &ESSResourceDB::add_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill", "class_id"), &ESSResourceDB::get_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill_index", "index"), &ESSResourceDB::get_entity_skill_index);
	ClassDB::bind_method(D_METHOD("get_entity_skill_count"), &ESSResourceDB::get_entity_skill_count);
	ClassDB::bind_method(D_METHOD("get_entity_skills"), &ESSResourceDB::get_entity_skills);
	ClassDB::bind_method(D_METHOD("set_entity_skills", "recipe"), &ESSResourceDB::set_entity_skills);

	ClassDB::bind_method(D_METHOD("get_entity_skill_path", "path"), &ESSResourceDB::get_entity_skill_path);
	ClassDB::bind_method(D_METHOD("entity_skill_id_to_path", "id"), &ESSResourceDB::entity_skill_id_to_path);
	ClassDB::bind_method(D_METHOD("entity_skill_path_to_id", "path"), &ESSResourceDB::entity_skill_path_to_id);

	//EntityData
	ClassDB::bind_method(D_METHOD("add_entity_data", "cls"), &ESSResourceDB::add_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data", "class_id"), &ESSResourceDB::get_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data_index", "index"), &ESSResourceDB::get_entity_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_data_count"), &ESSResourceDB::get_entity_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_datas"), &ESSResourceDB::get_entity_datas);
	ClassDB::bind_method(D_METHOD("set_entity_datas", "recipe"), &ESSResourceDB::set_entity_datas);

	ClassDB::bind_method(D_METHOD("get_entity_data_path", "path"), &ESSResourceDB::get_entity_data_path);
	ClassDB::bind_method(D_METHOD("entity_data_id_to_path", "id"), &ESSResourceDB::entity_data_id_to_path);
	ClassDB::bind_method(D_METHOD("entity_data_path_to_id", "path"), &ESSResourceDB::entity_data_path_to_id);

	//Spell
	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &ESSResourceDB::add_spell);
	ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &ESSResourceDB::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &ESSResourceDB::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &ESSResourceDB::get_spell_count);
	ClassDB::bind_method(D_METHOD("get_spells"), &ESSResourceDB::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "recipe"), &ESSResourceDB::set_spells);

	ClassDB::bind_method(D_METHOD("get_spell_path", "path"), &ESSResourceDB::get_spell_path);
	ClassDB::bind_method(D_METHOD("spell_id_to_path", "id"), &ESSResourceDB::spell_id_to_path);
	ClassDB::bind_method(D_METHOD("spell_path_to_id", "path"), &ESSResourceDB::spell_path_to_id);

	//Craft Data
	ClassDB::bind_method(D_METHOD("add_craft_recipe", "craft_recipe"), &ESSResourceDB::add_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe", "craft_recipe_id"), &ESSResourceDB::get_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_index", "index"), &ESSResourceDB::get_craft_recipe_index);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_count"), &ESSResourceDB::get_craft_recipe_count);
	ClassDB::bind_method(D_METHOD("get_craft_recipes"), &ESSResourceDB::get_craft_recipes);
	ClassDB::bind_method(D_METHOD("set_craft_recipes", "recipe"), &ESSResourceDB::set_craft_recipes);

	ClassDB::bind_method(D_METHOD("get_craft_recipe_path", "path"), &ESSResourceDB::get_craft_recipe_path);
	ClassDB::bind_method(D_METHOD("craft_recipe_id_to_path", "id"), &ESSResourceDB::craft_recipe_id_to_path);
	ClassDB::bind_method(D_METHOD("craft_recipe_path_to_id", "path"), &ESSResourceDB::craft_recipe_path_to_id);

	//Item Templates
	ClassDB::bind_method(D_METHOD("add_item_template", "item_template"), &ESSResourceDB::add_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template", "item_template_id"), &ESSResourceDB::get_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template_index", "index"), &ESSResourceDB::get_item_template_index);
	ClassDB::bind_method(D_METHOD("get_item_template_count"), &ESSResourceDB::get_item_template_count);
	ClassDB::bind_method(D_METHOD("get_item_templates"), &ESSResourceDB::get_item_templates);
	ClassDB::bind_method(D_METHOD("set_item_templates", "recipe"), &ESSResourceDB::set_item_templates);

	ClassDB::bind_method(D_METHOD("get_item_template_path", "path"), &ESSResourceDB::get_item_template_path);
	ClassDB::bind_method(D_METHOD("item_template_id_to_path", "id"), &ESSResourceDB::item_template_id_to_path);
	ClassDB::bind_method(D_METHOD("item_template_path_to_id", "path"), &ESSResourceDB::item_template_path_to_id);

	//Entity Species
	ClassDB::bind_method(D_METHOD("add_entity_species_data", "pcd"), &ESSResourceDB::add_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data", "pcd_id"), &ESSResourceDB::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_index", "index"), &ESSResourceDB::get_entity_species_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_count"), &ESSResourceDB::get_entity_species_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_species_datas"), &ESSResourceDB::get_entity_species_datas);
	ClassDB::bind_method(D_METHOD("set_entity_species_datas", "recipe"), &ESSResourceDB::set_entity_species_datas);

	ClassDB::bind_method(D_METHOD("get_entity_species_data_path", "path"), &ESSResourceDB::get_entity_species_data_path);
	ClassDB::bind_method(D_METHOD("entity_species_id_to_path", "id"), &ESSResourceDB::entity_species_id_to_path);
	ClassDB::bind_method(D_METHOD("entity_species_path_to_id", "path"), &ESSResourceDB::entity_species_path_to_id);

	ClassDB::bind_method(D_METHOD("clear"), &ESSResourceDB::clear);
	ClassDB::bind_method(D_METHOD("add_entity_resource_db", "other"), &ESSResourceDB::add_entity_resource_db);

	BIND_VMETHOD(MethodInfo("_initialize"));
	ClassDB::bind_method(D_METHOD("initialize"), &ESSResourceDB::initialize);
}
