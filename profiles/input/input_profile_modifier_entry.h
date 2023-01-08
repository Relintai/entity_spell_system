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

#ifndef INPUT_PROFILE_MODIFIER_ENTRY_H
#define INPUT_PROFILE_MODIFIER_ENTRY_H

#include "core/version.h"

#include "core/object/ref_counted.h"
#include "core/string/ustring.h"


class InputProfileModifierEntry : public RefCounted {
	GDCLASS(InputProfileModifierEntry, RefCounted);

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
