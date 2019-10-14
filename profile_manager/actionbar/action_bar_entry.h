#ifndef ACTION_BAR_ENTRY_H
#define ACTION_BAR_ENTRY_H

#include "core/reference.h"
#include "core/vector.h"
#include "core/dictionary.h"
#include "core/array.h"

#include "action_bar_button_entry.h"

class ActionBarEntry : public Reference {
	GDCLASS(ActionBarEntry, Reference);

public:
	float get_size();
	void set_size(float value);

	int get_action_bar_id();
	void set_action_bar_id(int value);

	int get_slot_num();
	void set_slot_num(int value);

	int get_action_bar_entry_count();

	Ref<ActionBarButtonEntry> get_button_for_slotid(int slotId);
	Ref<ActionBarButtonEntry> get_button(int index);

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
};

#endif
