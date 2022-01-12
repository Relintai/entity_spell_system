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

#ifndef CLASS_PROFILE_H
#define CLASS_PROFILE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#include "core/string/ustring.h"
#include "core/variant/dictionary.h"
#else
#include "core/reference.h"
#include "core/ustring.h"
#include "core/dictionary.h"
#endif

#include "actionbar/action_bar_profile.h"
#include "input/input_profile.h"

class ClassProfile : public Reference {
	GDCLASS(ClassProfile, Reference);

public:
	StringName get_class_path() const;
	void set_class_path(const StringName &value);

	String get_character_class_name() const;
	void set_character_class_name(const String &value);

	int get_level() const;
	void set_level(const int value);

	int get_xp() const;
	void set_xp(const int value);

	bool get_actionbar_locked() const;
	void set_actionbar_locked(const bool value);

	Ref<InputProfile> get_input_profile();
	Ref<ActionBarProfile> get_default_action_bar_profile();

	void emit_change();

	bool has_custom_data(const String &p_name) const;
	void set_custom_data(const String &p_name, const Variant &p_value);
	void remove_custom_data(const String &p_name);
	Variant get_custom_data(const String &p_name) const;

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ClassProfile();
	ClassProfile(const StringName &class_path);
	ClassProfile(const String &class_name, const StringName &class_path, const int level, const int xp, const bool locked);
	~ClassProfile();

	void load_defaults();

protected:
	static void _bind_methods();

private:
	String _character_class_name;
	StringName _class_path;
	int _level;
	int _xp;
	bool _actionbar_locked;

	Ref<InputProfile> _input_profile;
	Ref<ActionBarProfile> _action_bar_profile;

	Dictionary _custom_data;
};

#endif
