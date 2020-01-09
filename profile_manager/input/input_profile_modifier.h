#ifndef INPUT_PROFILE_MODIFIER_H
#define INPUT_PROFILE_MODIFIER_H

#include "core/reference.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "input_profile_modifier_entry.h"

class InputProfileModifier : public Reference {
	GDCLASS(InputProfileModifier, Reference);

public:
	int get_modifier_count();
	void clear_modifiers();
	void add_modifier(String modifier);
	String get_modifier(int index);
	void set_modifier(int index, String value);
	void remove_modifier(int index);

	int get_entry_count();
	void clear_entries();
	void add_entry(Ref<InputProfileModifierEntry> modifier);
	Ref<InputProfileModifierEntry> get_entry(int index);
	void set_entry(int index, Ref<InputProfileModifierEntry> value);
	void remove_entry(int index);

	InputProfileModifier();
	~InputProfileModifier();

protected:
	static void _bind_methods();

private:
	Vector<String> *_modifier_actions;
	Vector<Ref<InputProfileModifierEntry> > *_entries;
};

#endif
