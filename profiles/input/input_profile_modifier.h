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

#ifndef INPUT_PROFILE_MODIFIER_H
#define INPUT_PROFILE_MODIFIER_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#else
#include "core/reference.h"
#include "core/vector.h"
#include "core/ustring.h"
#endif

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
