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

#ifndef CLASS_PROFILE_H
#define CLASS_PROFILE_H

#include "core/dictionary.h"
#include "core/reference.h"
#include "core/ustring.h"

#include "actionbar/action_bar_profile.h"
#include "input/input_profile.h"

class ClassProfile : public Reference {
	GDCLASS(ClassProfile, Reference);

public:
	int get_class_id();
	void set_class_id(int value);
	String get_character_class_name();
	void set_character_class_name(String value);
	int get_level();
	void set_level(int value);
	int get_xp();
	void set_xp(int value);
	bool get_actionbar_locked();
	void set_actionbar_locked(bool value);
	Ref<InputProfile> get_input_profile();
	Ref<ActionBarProfile> get_action_bar_profile();

	void emit_change();

	bool has_custom_data(const String &p_name) const;
	void set_custom_data(const String &p_name, const Variant &p_value);
	void remove_custom_data(const String &p_name);
	Variant get_custom_data(const String &p_name) const;

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ClassProfile();
	ClassProfile(int class_id);
	ClassProfile(String class_name, int class_id, int level, int xp, bool locked);
	~ClassProfile();

	void load_defaults();

protected:
	static void _bind_methods();

private:
	String _character_class_name;
	int _class_id;
	int _level;
	int _xp;
	bool _actionbar_locked;

	Ref<InputProfile> _input_profile;
	Ref<ActionBarProfile> _action_bar_profile;

	Dictionary _custom_data;
};

#endif
