#ifndef INPUT_PROFILE_MODIFIER_ENTRY_H
#define INPUT_PROFILE_MODIFIER_ENTRY_H

#include "core/reference.h"
#include "core/ustring.h"

class InputProfileModifierEntry : public Reference {
	GDCLASS(InputProfileModifierEntry, Reference);

public:
	String get_action();
	void set_action(String value);

	String get_translate_to();
	void set_translate_to(String value);

	InputProfileModifierEntry();

protected:
	static void _bind_methods();

private:
    String _action;
    String _translate_to;
};


#endif
