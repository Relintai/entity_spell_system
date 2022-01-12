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

#include "input_profile.h"

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/string/ustring.h"
#include "core/config/project_settings.h"
#else
#include "core/ustring.h"
#include "core/project_settings.h"
#endif

#include "../class_profile.h"

Ref<ClassProfile> InputProfile::get_owner() {
	return Ref<ClassProfile>(_owner);
}
void InputProfile::set_owner(ClassProfile *owner) {
	_owner = owner;
}

Array InputProfile::get_data() {
	return _data;
}
void InputProfile::set_data(const Array &data) {
	_data = data;
}

void InputProfile::load_to_projectsettings() {
	for (int i = 0; i < _data.size(); ++i) {
		Array arr = _data[i];

		ProjectSettings::get_singleton()->set(arr[0], arr[1]);
	}
}

void InputProfile::save_from_projectsettings() {
	_data.clear();

	List<PropertyInfo> pinfo;
	ProjectSettings::get_singleton()->get_property_list(&pinfo);

	for (List<PropertyInfo>::Element *E = pinfo.front(); E; E = E->next()) {
		const PropertyInfo &pi = E->get();

		if (!pi.name.begins_with("input/"))
			continue;

		String name = pi.name.substr(pi.name.find("/") + 1, pi.name.length());

		Dictionary action = ProjectSettings::get_singleton()->get(pi.name);

		Array arr;
		arr.push_back(name);
		arr.push_back(action);

		_data.push_back(arr);
	}
}

void InputProfile::load_defaults() {
	_data.clear();
}

void InputProfile::emit_change() {
	emit_signal("changed");

	if (_owner != NULL)
		_owner->emit_change();
}

Dictionary InputProfile::to_dict() const {
	Dictionary dict;

	dict["data"] = _data;

	return dict;
}
void InputProfile::from_dict(const Dictionary &dict) {
	_data = dict.get("data", Array());

	emit_change();
}

InputProfile::InputProfile() {
}

void InputProfile::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	ClassDB::bind_method(D_METHOD("get_owner"), &InputProfile::get_owner);

	ClassDB::bind_method(D_METHOD("load_defaults"), &InputProfile::load_defaults);

	ClassDB::bind_method(D_METHOD("get_data"), &InputProfile::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "data"), &InputProfile::set_data);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data"), "set_data", "get_data");

	ClassDB::bind_method(D_METHOD("load_to_projectsettings"), &InputProfile::load_to_projectsettings);
	ClassDB::bind_method(D_METHOD("save_from_projectsettings"), &InputProfile::save_from_projectsettings);
}