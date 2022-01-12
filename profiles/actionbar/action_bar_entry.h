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

#ifndef ACTION_BAR_ENTRY_H
#define ACTION_BAR_ENTRY_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#include "core/templates/vector.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"
#else
#include "core/reference.h"
#include "core/vector.h"
#include "core/array.h"
#include "core/dictionary.h"
#endif

#include "action_bar_button_entry.h"

class ActionBarProfile;

class ActionBarEntry : public Reference {
	GDCLASS(ActionBarEntry, Reference);

public:
	Ref<ActionBarProfile> get_owner();
	void set_owner(ActionBarProfile *owner);

	float get_size() const;
	void set_size(const float value);

	int get_action_bar_id() const;
	void set_action_bar_id(const int value);

	int get_slot_num() const;
	void set_slot_num(const int value);

	int get_action_bar_entry_count() const;

	void emit_change();

	Ref<ActionBarButtonEntry> get_button_for_slotid(const int slotId);
	Ref<ActionBarButtonEntry> get_button(const int index);

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ActionBarEntry();
	~ActionBarEntry();

protected:
	static void _bind_methods();

private:
	int _action_bar_id;
	int _slot_num;
	Vector<Ref<ActionBarButtonEntry> > _button_entries;

	float _size;

	ActionBarProfile *_owner;
};

#endif
