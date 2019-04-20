#ifndef CRAFT_DATA_ATTRIBUTE_H
#define CRAFT_DATA_ATTRIBUTE_H

#include "core/vector.h"
#include "core/resource.h"
#include "core/ustring.h"

#include "item_template.h"

#include "craft_data_attribute_helper.h"

class CraftDataAttribute : public Resource {
	GDCLASS(CraftDataAttribute, Resource);

public:
	static const String BINDING_STRING_CRAFT_CATEGORIES;
	static const String BINDING_STRING_CRAFT_SUB_CATEGORIES;

	enum CraftCategories {
		CRAFT_CATEGORY_NONE,
		CRAFT_CATEGORY_ALCHEMY,
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
	Ref<CraftDataAttributeHelper> get_required_tool(int index);
	void set_required_tool(int index, const Ref<CraftDataAttributeHelper> value);

	int get_required_tools_count();
	void set_required_tools_count(int value);

	//Materials
	Ref<CraftDataAttributeHelper> get_required_material(int index);
	void set_required_material(int index, const Ref<CraftDataAttributeHelper> value);

	int get_required_materials_count();
	void set_required_materials_count(int value);

	//Item
	Ref<CraftDataAttributeHelper> get_item();
	void set_item(Ref<CraftDataAttributeHelper> value);

	CraftDataAttribute();
	~CraftDataAttribute();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_REQUIRED_MATERIALS = 6, //Increase if necessary, should be enough for now
		MAX_REQUIRED_TOOLS = 6 //Increase if necessary, should be enough for now
	};

	int _id;

	CraftCategories _category;
	CraftSubCategories _sub_category;

	int _required_tools_count;
	Ref<CraftDataAttributeHelper> _required_tools[MAX_REQUIRED_TOOLS];

	int _required_materials_count;
	Ref<CraftDataAttributeHelper> _required_materials[MAX_REQUIRED_MATERIALS];

	Ref<CraftDataAttributeHelper> _item;

#if ENTITY_MEM_TOOLS
	static int allocs;
#endif
};

VARIANT_ENUM_CAST(CraftDataAttribute::CraftSubCategories);
VARIANT_ENUM_CAST(CraftDataAttribute::CraftCategories);

#endif
