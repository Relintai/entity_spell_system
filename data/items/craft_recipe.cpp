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

#include "craft_recipe.h"

const String CraftRecipe::BINDING_STRING_CRAFT_CATEGORIES = "None,Alchemy,Smithing,Tailoring,Enchanting,Engineering";
const String CraftRecipe::BINDING_STRING_CRAFT_SUB_CATEGORIES = "None,Potions";

int CraftRecipe::get_id() const {
	return _id;
}
void CraftRecipe::set_id(const int value) {
	_id = value;
}

CraftRecipe::CraftCategories CraftRecipe::get_category() const {
	return _category;
}
void CraftRecipe::set_category(const CraftCategories value) {
	_category = value;
}

CraftRecipe::CraftSubCategories CraftRecipe::get_sub_category() const {
	return _sub_category;
}

void CraftRecipe::set_sub_category(const CraftSubCategories value) {
	_sub_category = value;
}

Ref<CraftRecipeHelper> CraftRecipe::get_required_tool(const int index) {
	return _required_tools[index];
}

void CraftRecipe::set_required_tool(const int index, const Ref<CraftRecipeHelper> &value) {
	_required_tools[index] = value;
}

int CraftRecipe::get_required_tools_count() const {
	return _required_tools_count;
}

void CraftRecipe::set_required_tools_count(const int value) {
	_required_tools_count = value;
}

void CraftRecipe::set_required_material(const int index, const Ref<CraftRecipeHelper> &value) {
	_required_materials[index] = value;
}

Ref<CraftRecipeHelper> CraftRecipe::get_required_material(int index) {
	return _required_materials[index];
}

int CraftRecipe::get_required_materials_count() const {
	return _required_materials_count;
}

void CraftRecipe::set_required_materials_count(const int value) {
	_required_materials_count = value;
}

Ref<CraftRecipeHelper> CraftRecipe::get_item() {
	return _item;
}

void CraftRecipe::set_item(const Ref<CraftRecipeHelper> &value) {
	_item = value;
}

CraftRecipe::CraftRecipe() {
	_id = 0;
	_category = CraftCategories::CRAFT_CATEGORY_NONE;
	_sub_category = CraftSubCategories::CRAFT_SUB_CATEGORY_NONE;
	//_item = Ref<CraftRecipeHelper>(memnew(CraftRecipeHelper()));
	_required_materials_count = 0;
	_required_tools_count = 0;

	//for (int i = 0; i < MAX_REQUIRED_TOOLS; ++i) {
	//	_required_tools[i] = Ref<CraftRecipeHelper>(memnew(CraftRecipeHelper()));
	//}

	//for (int i = 0; i < MAX_REQUIRED_MATERIALS; ++i) {
	//	_required_materials[i] = Ref<CraftRecipeHelper>(memnew(CraftRecipeHelper()));
	//}
}

CraftRecipe::~CraftRecipe() {
	//TODO check if the array destrutors actually unref the objects.

	//_item = Ref<CraftRecipeHelper>(NULL);
}

void CraftRecipe::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("RequiredMaterials_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _required_materials_count) {
			property.usage = 0;
		}
	} else if (prop.begins_with("RequiredTools_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _required_tools_count) {
			property.usage = 0;
		}
	}
}

void CraftRecipe::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &CraftRecipe::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CraftRecipe::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_category"), &CraftRecipe::get_category);
	ClassDB::bind_method(D_METHOD("set_category", "value"), &CraftRecipe::set_category);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "category", PROPERTY_HINT_ENUM, CraftRecipe::BINDING_STRING_CRAFT_CATEGORIES), "set_category", "get_category");

	ClassDB::bind_method(D_METHOD("get_sub_category"), &CraftRecipe::get_sub_category);
	ClassDB::bind_method(D_METHOD("set_sub_category", "value"), &CraftRecipe::set_sub_category);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sub_category", PROPERTY_HINT_ENUM, CraftRecipe::BINDING_STRING_CRAFT_SUB_CATEGORIES), "set_sub_category", "get_sub_category");

	ClassDB::bind_method(D_METHOD("get_required_material"), &CraftRecipe::get_required_material);
	ClassDB::bind_method(D_METHOD("set_required_material", "mat"), &CraftRecipe::set_required_material);

	ClassDB::bind_method(D_METHOD("get_required_materials_count"), &CraftRecipe::get_required_materials_count);
	ClassDB::bind_method(D_METHOD("set_required_materials_count", "count"), &CraftRecipe::set_required_materials_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "required_materials_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_REQUIRED_MATERIALS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_required_materials_count", "get_required_materials_count");

	for (int i = 0; i < MAX_REQUIRED_MATERIALS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "RequiredMaterials_" + itos(i) + "", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipeHelper", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_required_material", "get_required_material", i);
	}

	ClassDB::bind_method(D_METHOD("get_required_tool"), &CraftRecipe::get_required_tool);
	ClassDB::bind_method(D_METHOD("set_required_tool", "value"), &CraftRecipe::set_required_tool);

	ClassDB::bind_method(D_METHOD("get_required_tools_count"), &CraftRecipe::get_required_tools_count);
	ClassDB::bind_method(D_METHOD("set_required_tools_count", "value"), &CraftRecipe::set_required_tools_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "required_tools_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_REQUIRED_TOOLS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_required_tools_count", "get_required_tools_count");

	for (int i = 0; i < MAX_REQUIRED_TOOLS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "RequiredTools_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipeHelper", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_required_tool", "get_required_tool", i);
	}

	ClassDB::bind_method(D_METHOD("get_item"), &CraftRecipe::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &CraftRecipe::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipeHelper"), "set_item", "get_item");

	BIND_CONSTANT(MAX_REQUIRED_TOOLS);
	BIND_CONSTANT(MAX_REQUIRED_MATERIALS);

	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_NONE);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_ALCHEMY);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_SMITHING);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_TAILORING);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_ENCHANTING);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_ENGINEERING);

	BIND_ENUM_CONSTANT(CRAFT_SUB_CATEGORY_NONE);
	BIND_ENUM_CONSTANT(CRAFT_SUB_CATEGORY_POTIONS);
}
