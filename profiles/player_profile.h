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

#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

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

#include "class_profile.h"

class PlayerProfile : public Reference {
	GDCLASS(PlayerProfile, Reference);

public:
	static const String DEFAULT_PROFILE_FILE_NAME;

	int get_id();
	void set_id(int value);

	String get_profile_name();
	void set_profile_name(String value);

	int get_last_used_character() const;
	void set_last_used_character(const int value);

	int get_class_profile_count() const;
	Ref<ClassProfile> get_class_profile_index(const int index);
	void add_class_profile(Ref<ClassProfile> profile);
	void clear_class_profiles();
	void remove_class_profile(const int index);

	Vector<Ref<ClassProfile> > &get_class_profiles();
	Ref<ClassProfile> get_class_profile(const StringName &class_path);

	Dictionary get_custom_data();
	void set_custom_data(const Dictionary &dict);

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	void emit_change();

	PlayerProfile();
	~PlayerProfile();

	void load_defaults();

protected:
	void _on_class_profile_changed();

	static void _bind_methods();

private:
	int _id;
	int _last_used_character;
	String _profile_name;

	Dictionary _custom_data;

	Vector<Ref<ClassProfile> > _class_profiles;
};

#endif
