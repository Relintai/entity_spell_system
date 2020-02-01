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

#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include "core/object.h"

#include "core/vector.h"

#include "class_profile.h"

class ProfileManager : public Object {
	GDCLASS(ProfileManager, Object);

public:
	static const String DEFAULT_PROFILE_FILE_NAME;

	static ProfileManager *get_instance();

	bool get_automatic_load() { return _automatic_load; }
	void set_automatic_load(bool load) { _automatic_load = load; }

	String get_save_file() const;
	void set_save_file(const String &file);

	int get_last_used_class();
	void set_last_used_class(int value);

	int get_class_profile_count();
	Ref<ClassProfile> get_class_profile_index(int index);
	void add_class_profile(Ref<ClassProfile> profile);
	void clear_class_profiles();
	void remove_class_profile(int index);

	Vector<Ref<ClassProfile> > &get_class_profiles();
	Ref<ClassProfile> get_class_profile(int class_id);

	void save();
	void load();

	void _save();
	void _load();

	void save_profile(String name);
	void load_profile(String name);

	void load_defaults();

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ProfileManager();
	~ProfileManager();

protected:
	static void _bind_methods();

private:
	static ProfileManager *_instance;

	bool _automatic_load;

	int _last_used_class;

	String _profile_name;
	String _save_file;

	Vector<Ref<ClassProfile> > _class_profiles;
};

#endif
