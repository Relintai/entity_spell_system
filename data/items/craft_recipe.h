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

#ifndef CRAFT_RECIPE_H
#define CRAFT_RECIPE_H

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

#include "item_template.h"

#include "craft_recipe_helper.h"

class CraftRecipe : public Resource {
	GDCLASS(CraftRecipe, Resource);

public:
	static const String BINDING_STRING_CRAFT_CATEGORIES;
	static const String BINDING_STRING_CRAFT_SUB_CATEGORIES;

	enum CraftCategories {
		CRAFT_CATEGORY_NONE,
		CRAFT_CATEGORY_ALCHEMY,
		CRAFT_CATEGORY_SMITHING,
		CRAFT_CATEGORY_TAILORING,
		CRAFT_CATEGORY_ENCHANTING,
		CRAFT_CATEGORY_ENGINEERING,
	};

	enum CraftSubCategories {
		CRAFT_SUB_CATEGORY_NONE,
		CRAFT_SUB_CATEGORY_POTIONS,
	};

public:
	int get_id() const;
	void set_id(const int value);

	CraftCategories get_category() const;
	void set_category(const CraftCategories value);

	CraftSubCategories get_sub_category() const;
	void set_sub_category(const CraftSubCategories value);

	//Tools
	Ref<CraftRecipeHelper> get_required_tool(int index);
	void set_required_tool(const int index, const Ref<CraftRecipeHelper> &value);

	int get_required_tools_count() const;
	void set_required_tools_count(const int value);

	//Materials
	Ref<CraftRecipeHelper> get_required_material(const int index);
	void set_required_material(const int index, const Ref<CraftRecipeHelper> &value);

	int get_required_materials_count() const;
	void set_required_materials_count(const int value);

	//Item
	Ref<CraftRecipeHelper> get_item();
	void set_item(const Ref<CraftRecipeHelper> &value);

	CraftRecipe();
	~CraftRecipe();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_REQUIRED_MATERIALS = 6, //Increase if necessary, should be enough for now
		MAX_REQUIRED_TOOLS = 6 //Increase if necessary, should be enough for now
	};

	int _id;
	String _text_name;

	CraftCategories _category;
	CraftSubCategories _sub_category;

	int _required_tools_count;
	Ref<CraftRecipeHelper> _required_tools[MAX_REQUIRED_TOOLS];

	int _required_materials_count;
	Ref<CraftRecipeHelper> _required_materials[MAX_REQUIRED_MATERIALS];

	Ref<CraftRecipeHelper> _item;
};

VARIANT_ENUM_CAST(CraftRecipe::CraftSubCategories);
VARIANT_ENUM_CAST(CraftRecipe::CraftCategories);

#endif
