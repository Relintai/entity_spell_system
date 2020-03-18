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

#ifndef ACTION_BAR_BUTTON_ENTRY_H
#define ACTION_BAR_BUTTON_ENTRY_H

#include "core/dictionary.h"
#include "core/reference.h"

class ActionBarEntry;

class ActionBarButtonEntry : public Reference {
	GDCLASS(ActionBarButtonEntry, Reference);

public:
	static const String BINDING_STRING_ACTIONBAR_BUTTON_ENTRY_TYPE;

	enum ActionBarButtonEntryType {
		ACTION_BAR_BUTTON_ENTRY_TYPE_NONE,
		ACTION_BAR_BUTTON_ENTRY_TYPE_SPELL,
		ACTION_BAR_BUTTON_ENTRY_TYPE_ITEM
	};

	Ref<ActionBarEntry> get_owner();
	void set_owner(ActionBarEntry *owner);

	int get_action_bar_id();
	void set_action_bar_id(int value);

	int get_slot_id();
	void set_slot_id(int value);

	ActionBarButtonEntryType get_type();
	void set_type(ActionBarButtonEntryType value);

	int get_item_id();
	void set_item_id(int value);

	void emit_change();

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ActionBarButtonEntry();
	ActionBarButtonEntry(int actionBarId, int slotId);
	ActionBarButtonEntry(int actionBarId, int slotId, ActionBarButtonEntryType type, int itemId);
	~ActionBarButtonEntry();

protected:
	static void _bind_methods();

private:
	int _action_bar_id;
	int _slot_id;
	ActionBarButtonEntryType _type;
	int _item_id;

	ActionBarEntry *_owner;
};

VARIANT_ENUM_CAST(ActionBarButtonEntry::ActionBarButtonEntryType);

#endif
