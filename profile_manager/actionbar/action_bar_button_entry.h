#ifndef ACTION_BAR_BUTTON_ENTRY_H
#define ACTION_BAR_BUTTON_ENTRY_H

#include "core/dictionary.h"
#include "core/reference.h"

class ActionBarButtonEntry : public Reference {
	GDCLASS(ActionBarButtonEntry, Reference);

public:
	static const String BINDING_STRING_ACTIONBAR_BUTTON_ENTRY_TYPE;

	enum ActionBarButtonEntryType {
		ACTION_BAR_BUTTON_ENTRY_TYPE_NONE,
		ACTION_BAR_BUTTON_ENTRY_TYPE_SPELL,
		ACTION_BAR_BUTTON_ENTRY_TYPE_ITEM
	};

	int get_action_bar_id();
	void set_action_bar_id(int value);

	int get_slot_id();
	void set_slot_id(int value);

	ActionBarButtonEntryType get_type();
	void set_type(ActionBarButtonEntryType value);

	int get_item_id();
	void set_item_id(int value);

	void changed();

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ActionBarButtonEntry();
	ActionBarButtonEntry(int actionBarId, int slotId);
	ActionBarButtonEntry(int actionBarId, int slotId, ActionBarButtonEntryType type, int itemId);

protected:
	static void _bind_methods();

private:
	int _action_bar_id;
	int _slot_id;
	ActionBarButtonEntryType _type;
	int _item_id;
};

VARIANT_ENUM_CAST(ActionBarButtonEntry::ActionBarButtonEntryType);

#endif
