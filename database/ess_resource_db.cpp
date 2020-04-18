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

#include "ess_resource_db.h"

#include "../data/auras/aura.h"
#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource_data.h"
#include "../entities/skills/entity_skill_data.h"

Ref<Aura> ESSResourceDB::get_skill_for_armor_type(const int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::ARMOR_TYPE_MAX, Ref<Aura>());

	return _armor_type_skills[index];
}
void ESSResourceDB::set_skill_for_armor_type(const int index, const Ref<Aura> &aura) {
	ERR_FAIL_INDEX(index, ItemEnums::ARMOR_TYPE_MAX);

	_armor_type_skills[index] = aura;
}

Ref<XPData> ESSResourceDB::get_xp_data() {
	return _xp_data;
}
void ESSResourceDB::set_xp_data(const Ref<XPData> &data) {
	_xp_data = data;
}

void ESSResourceDB::initialize() {
	if (has_method("_initialize"))
		call("_initialize");
}

ESSResourceDB::ESSResourceDB() {
}

ESSResourceDB::~ESSResourceDB() {
	_xp_data.unref();
}

void ESSResourceDB::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_skill_for_armor_type", "index"), &ESSResourceDB::get_skill_for_armor_type);
	ClassDB::bind_method(D_METHOD("set_skill_for_armor_type", "index", "aura"), &ESSResourceDB::set_skill_for_armor_type);

	for (int i = 0; i < ItemEnums::ARMOR_TYPE_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "skill_for_armor_type_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_skill_for_armor_type", "get_skill_for_armor_type", i);
	}

	//XPData
	ClassDB::bind_method(D_METHOD("get_xp_data"), &ESSResourceDB::get_xp_data);
	ClassDB::bind_method(D_METHOD("set_xp_data", "data"), &ESSResourceDB::set_xp_data);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp_data"), "set_xp_data", "get_xp_data");

	//EntityResourceData
	ClassDB::bind_method(D_METHOD("add_entity_resource", "cls"), &ESSResourceDB::add_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource", "class_id"), &ESSResourceDB::get_entity_resource);
	ClassDB::bind_method(D_METHOD("get_entity_resource_index", "index"), &ESSResourceDB::get_entity_resource_index);
	ClassDB::bind_method(D_METHOD("get_entity_resource_count"), &ESSResourceDB::get_entity_resource_count);
	ClassDB::bind_method(D_METHOD("get_entity_resources"), &ESSResourceDB::get_entity_resources);
	ClassDB::bind_method(D_METHOD("set_entity_resources", "recipe"), &ESSResourceDB::set_entity_resources);

	//EntitySkills
	ClassDB::bind_method(D_METHOD("add_entity_skill", "cls"), &ESSResourceDB::add_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill", "class_id"), &ESSResourceDB::get_entity_skill);
	ClassDB::bind_method(D_METHOD("get_entity_skill_index", "index"), &ESSResourceDB::get_entity_skill_index);
	ClassDB::bind_method(D_METHOD("get_entity_skill_count"), &ESSResourceDB::get_entity_skill_count);
	ClassDB::bind_method(D_METHOD("get_entity_skills"), &ESSResourceDB::get_entity_skills);
	ClassDB::bind_method(D_METHOD("set_entity_skills", "recipe"), &ESSResourceDB::set_entity_skills);

	//EntityData
	ClassDB::bind_method(D_METHOD("add_entity_data", "cls"), &ESSResourceDB::add_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data", "class_id"), &ESSResourceDB::get_entity_data);
	ClassDB::bind_method(D_METHOD("get_entity_data_index", "index"), &ESSResourceDB::get_entity_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_data_count"), &ESSResourceDB::get_entity_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_datas"), &ESSResourceDB::get_entity_datas);
	ClassDB::bind_method(D_METHOD("set_entity_datas", "recipe"), &ESSResourceDB::set_entity_skills);

	//Spell
	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &ESSResourceDB::add_spell);
	ClassDB::bind_method(D_METHOD("get_spell", "spell_id"), &ESSResourceDB::get_spell);
	ClassDB::bind_method(D_METHOD("get_spell_index", "index"), &ESSResourceDB::get_spell_index);
	ClassDB::bind_method(D_METHOD("get_spell_count"), &ESSResourceDB::get_spell_count);
	ClassDB::bind_method(D_METHOD("get_spells"), &ESSResourceDB::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "recipe"), &ESSResourceDB::set_spells);

	//Aura
	ClassDB::bind_method(D_METHOD("add_aura", "spell"), &ESSResourceDB::add_aura);
	ClassDB::bind_method(D_METHOD("get_aura", "id"), &ESSResourceDB::get_aura);
	ClassDB::bind_method(D_METHOD("get_aura_index", "index"), &ESSResourceDB::get_aura_index);
	ClassDB::bind_method(D_METHOD("get_aura_count"), &ESSResourceDB::get_aura_count);
	ClassDB::bind_method(D_METHOD("get_auras"), &ESSResourceDB::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "recipe"), &ESSResourceDB::set_auras);

	//Craft Data
	ClassDB::bind_method(D_METHOD("add_craft_recipe", "craft_recipe"), &ESSResourceDB::add_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe", "craft_recipe_id"), &ESSResourceDB::get_craft_recipe);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_index", "index"), &ESSResourceDB::get_craft_recipe_index);
	ClassDB::bind_method(D_METHOD("get_craft_recipe_count"), &ESSResourceDB::get_craft_recipe_count);
	ClassDB::bind_method(D_METHOD("get_craft_recipes"), &ESSResourceDB::get_craft_recipes);
	ClassDB::bind_method(D_METHOD("set_craft_recipes", "recipe"), &ESSResourceDB::set_craft_recipes);

	//Item Templates
	ClassDB::bind_method(D_METHOD("add_item_template", "item_template"), &ESSResourceDB::add_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template", "item_template_id"), &ESSResourceDB::get_item_template);
	ClassDB::bind_method(D_METHOD("get_item_template_index", "index"), &ESSResourceDB::get_item_template_index);
	ClassDB::bind_method(D_METHOD("get_item_template_count"), &ESSResourceDB::get_item_template_count);
	ClassDB::bind_method(D_METHOD("get_item_templates"), &ESSResourceDB::get_item_templates);
	ClassDB::bind_method(D_METHOD("set_item_templates", "recipe"), &ESSResourceDB::set_item_templates);

	//Player Character Data
	ClassDB::bind_method(D_METHOD("add_entity_species_data", "pcd"), &ESSResourceDB::add_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data", "pcd_id"), &ESSResourceDB::get_entity_species_data);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_index", "index"), &ESSResourceDB::get_entity_species_data_index);
	ClassDB::bind_method(D_METHOD("get_entity_species_data_count"), &ESSResourceDB::get_entity_species_data_count);
	ClassDB::bind_method(D_METHOD("get_entity_species_datas"), &ESSResourceDB::get_entity_species_datas);
	ClassDB::bind_method(D_METHOD("set_entity_species_datas", "recipe"), &ESSResourceDB::set_entity_species_datas);

	BIND_VMETHOD(MethodInfo("_initialize"));
	ClassDB::bind_method(D_METHOD("initialize"), &ESSResourceDB::initialize);
}
