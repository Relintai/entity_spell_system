#ifndef CRAFT_RECIPE_HELPER_H
#define CRAFT_RECIPE_HELPER_H

#include "core/resource.h"
#include "item_template.h"

class CraftRecipeHelper : public Resource {
	GDCLASS(CraftRecipeHelper, Resource);

public:
	Ref<ItemTemplate> get_item();
	void set_item(Ref<ItemTemplate> value);
	int get_count();
	void set_count(int value);

	CraftRecipeHelper(Ref<ItemTemplate> item, int count);
	CraftRecipeHelper();
	~CraftRecipeHelper();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
	int _count;
};

#endif
