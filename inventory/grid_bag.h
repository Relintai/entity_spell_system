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

#ifndef GRID_BAG_H
#define GRID_BAG_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#endif

#include "../item_enums.h"

class itemTemplate;
class ItemInstance;

class GridBag : public Reference {
	GDCLASS(GridBag, Reference);

public:
	int get_allowed_item_types() const;
	void set_allowed_item_types(const int value);

	bool add_item(Ref<ItemInstance> item);
	bool add_item_to_position(const int x, const int y, Ref<ItemInstance> item);

	bool can_add_item_at(const int x, const int y, const Ref<ItemInstance> item) const;
	int item_count_under_area(const int x, const int y, const int size_x, const int size_y) const;

	Ref<ItemInstance> get_item(const int index) const;
	Ref<ItemInstance> get_and_remove_item(const int index);
	void remove_item(const int index);

	void basic_add_item(const Ref<ItemInstance> item);
	void basic_remove_item(const int index);

	int get_item_count() const;

	int get_space_map_entry(const int index) const;
	void set_space_map_entry(const int index, const int value);

	int get_size_x() const;
	int get_size_y() const;

	void set_size(const int x, const int y);

	//to_dict();
	//from_dict();

	GridBag();
	~GridBag();

protected:
	static void _bind_methods();

private:
	int _allowed_item_types;

	int _size_x;
	int _size_y;

	Vector<Ref<ItemInstance> > _items;
	Vector<int> _space_map;
};

#endif
