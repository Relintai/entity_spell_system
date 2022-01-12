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

#ifndef VENDOR_ITEM_DATA_ENTRY_H
#define VENDOR_ITEM_DATA_ENTRY_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

class ItemTemplate;
class Spell;

class VendorItemDataEntry : public Resource {
	GDCLASS(VendorItemDataEntry, Resource);

public:
	Ref<ItemTemplate> get_item();
	void set_item(const Ref<ItemTemplate> &item);

	Ref<Spell> get_spell();
	void set_spell(const Ref<Spell> &spell);

	Ref<ItemTemplate> get_cost_item();
	void set_cost_item(const Ref<ItemTemplate> &item);

	int get_price() const;
	void set_price(const int value);

	int get_count() const;
	void set_count(const int value);

	int get_spawn_time() const;
	void set_spawn_time(const int time);

	VendorItemDataEntry();
	~VendorItemDataEntry();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item;
	Ref<Spell> _spell;
	Ref<ItemTemplate> _cost_item;

	int _price;
	int _count;
	int _spawn_time;
};

#endif
