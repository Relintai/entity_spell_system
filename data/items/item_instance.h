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

#ifndef ITEM_INSTANCE_H
#define ITEM_INSTANCE_H

#include "core/reference.h"
#include "core/vector.h"

#include "../../entities/stats/stat.h"
#include "../../item_enums.h"
#include "item_stat_modifier.h"

class ItemTemplate;

class ItemInstance : public Reference {
	GDCLASS(ItemInstance, Reference);

public:
	Ref<ItemTemplate> get_item_template();
	void set_item_template(const Ref<ItemTemplate> &value);

	Ref<ItemStatModifier> get_item_stat_modifier(const int index);
	void add_item_stat_modifier(const Ref<ItemStatModifier> &modifier);
	void remove_item_stat_modifier(const int index);
	void clear_item_stat_modifiers();

	int get_item_stat_modifier_count() const;

	int get_stack_size() const;
	void set_stack_size(const int value);

	int get_charges() const;
	void set_charges(const int value);

	String get_description();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);

	ItemInstance();
	~ItemInstance();

protected:
	static void _bind_methods();

private:
	Ref<ItemTemplate> _item_template;
	StringName _item_template_path;

	int _stack_size;
	int _charges;

	Vector<Ref<ItemStatModifier> > _modifiers;
};

#endif
