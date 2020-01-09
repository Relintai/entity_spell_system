#ifndef CRAFT_RECIPE_H
#define CRAFT_RECIPE_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"

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
	int get_id();
	void set_id(int value);

	CraftCategories get_category();
	void set_category(CraftCategories value);

	CraftSubCategories get_sub_category();
	void set_sub_category(CraftSubCategories value);

	//Tools
	Ref<CraftRecipeHelper> get_required_tool(int index);
	void set_required_tool(int index, const Ref<CraftRecipeHelper> value);

	int get_required_tools_count();
	void set_required_tools_count(int value);

	//Materials
	Ref<CraftRecipeHelper> get_required_material(int index);
	void set_required_material(int index, const Ref<CraftRecipeHelper> value);

	int get_required_materials_count();
	void set_required_materials_count(int value);

	//Item
	Ref<CraftRecipeHelper> get_item();
	void set_item(Ref<CraftRecipeHelper> value);

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
