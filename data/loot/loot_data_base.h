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

#ifndef LOOT_DATA_BASE_H
#define LOOT_DATA_BASE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/templates/vector.h"
#include "core/variant/array.h"
#else
#include "core/vector.h"
#include "core/array.h"
#endif

#include "../items/item_template.h"

class LootDataBase : public Resource {
	GDCLASS(LootDataBase, Resource);

public:
	int get_loot_db_size() const;
	void set_loot_db_size(const float value);

	int get_items_size() const;
	void set_items_size(const int value);

	float get_loot_db_chance(const int index) const;
	void set_loot_db_chance(const int index, const float value);

	Ref<LootDataBase> get_loot_db(const int index) const;
	void set_loot_db(const int index, const Ref<LootDataBase> &value);

	float get_item_chance(const int index) const;
	void set_item_chance(const int index, const float value);

	Ref<ItemTemplate> get_item(const int index) const;
	void set_item(const int index, const Ref<ItemTemplate> &value);

	Array get_loot();
	Array _get_loot();

	LootDataBase();
	~LootDataBase();

protected:
	struct LootDBLDF {
		float chance;
		Ref<LootDataBase> loot_db;

		LootDBLDF() {
			chance = 0;
		}
	};

	struct LootDBItem {
		float chance;
		Ref<ItemTemplate> item;

		LootDBItem() {
			chance = 0;
		}
	};

protected:
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	static void _bind_methods();

private:
	Vector<LootDBLDF> _loot_dbs;
	Vector<LootDBItem> _items;
};

#endif
