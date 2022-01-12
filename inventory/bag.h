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

#ifndef BAG_H
#define BAG_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#endif

#include "../item_enums.h"

class ItemTemplate;
class ItemInstance;

class Bag : public Resource {
	GDCLASS(Bag, Resource);

public:
	int get_allowed_item_types() const;
	void set_allowed_item_types(const int value);

	bool add_item(Ref<ItemInstance> item);
	void add_item_at(int index, Ref<ItemInstance> item, bool signal = true);
	Ref<ItemInstance> get_item(const int index);
	Ref<ItemInstance> remove_item(const int index);
	void swap_items(const int item1_index, const int item2_index);
	void change_item_equip(int slot_id, Ref<ItemInstance> item);
	void set_item_count(int slot_id, int new_count);

	bool can_add_item(Ref<ItemInstance> item);

	int get_item_count();
	int get_valid_item_count();

	int get_size();
	void set_size(const int size);

	bool is_full();
	bool is_overburdened();

	bool has_item(Ref<ItemTemplate> item, int count);
	bool _has_item(Ref<ItemTemplate> item, int count);

	void remove_items(Ref<ItemTemplate> item, int count);
	void _remove_items(Ref<ItemTemplate> item, int count);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	Bag();
	~Bag();

protected:
	static void _bind_methods();

private:
	int _allowed_item_types;
	int _bag_size;
	Vector<Ref<ItemInstance> > _items;
};

#endif
