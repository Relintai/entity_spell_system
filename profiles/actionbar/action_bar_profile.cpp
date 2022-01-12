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

#include "action_bar_profile.h"

#include "core/version.h"

#include "../class_profile.h"

Ref<ClassProfile> ActionBarProfile::get_owner() {
	return Ref<ClassProfile>(_owner);
}
void ActionBarProfile::set_owner(ClassProfile *owner) {
	_owner = owner;
}

String ActionBarProfile::get_action_bar_profile_name() {
	return _name;
}

void ActionBarProfile::set_action_bar_profile_name(const String &value) {
	_name = value;

	emit_change();
}

Vector<Ref<ActionBarEntry>> &ActionBarProfile::get_action_bars() {
	return _action_bars;
}

void ActionBarProfile::load_defaults() {
	_action_bars.clear();

	Ref<ActionBarEntry> actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(1);
	actionBarEntry->set_slot_num(12);
	actionBarEntry->set_owner(this);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(2);
	actionBarEntry->set_slot_num(12);
	actionBarEntry->set_owner(this);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(3);
	actionBarEntry->set_slot_num(12);
	actionBarEntry->set_owner(this);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(4);
	actionBarEntry->set_slot_num(12);
	actionBarEntry->set_owner(this);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	emit_change();
}

int ActionBarProfile::get_action_bar_count() const {
	return _action_bars.size();
}

void ActionBarProfile::add_action_bar(Ref<ActionBarEntry> actionbar) {
	ERR_FAIL_COND(!actionbar.is_valid());

	actionbar->set_owner(this);
	_action_bars.push_back(Ref<ActionBarEntry>(actionbar));

	emit_change();
}

Ref<ActionBarEntry> ActionBarProfile::get_action_bar(int index) {
	ERR_FAIL_INDEX_V(index, _action_bars.size(), Ref<ActionBarEntry>(NULL));

	return _action_bars.get(index);
}

void ActionBarProfile::remove_action_bar(const int index) {
	_action_bars.get(index)->set_owner(NULL);

	_action_bars.remove(index);

	emit_change();
}

void ActionBarProfile::clear_action_bars() {
	for (int i = 0; i < _action_bars.size(); ++i) {
		_action_bars.get(i)->set_owner(NULL);
	}

	_action_bars.clear();

	emit_change();
}

Dictionary ActionBarProfile::to_dict() const {
	Dictionary dict;

	dict["name"] = _name;

	Array arr;

	for (int i = 0; i < _action_bars.size(); ++i) {
		Dictionary d = _action_bars[i]->to_dict();

		arr.append(d);
	}

	dict["action_bars"] = arr;

	return dict;
}
void ActionBarProfile::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	if (dict.is_empty())
		return;
#else
	if (dict.empty())
		return;
#endif

	for (int i = 0; i < _action_bars.size(); ++i) {
		_action_bars.get(i)->set_owner(NULL);
	}

	_action_bars.clear();

	_name = dict.get("name", "");

	Array arr = dict.get("action_bars", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ActionBarEntry> e;
		e.instance();

		e->from_dict(arr.get(i));
		e->set_owner(this);

		_action_bars.push_back(e);
	}

	emit_change();
}

void ActionBarProfile::from_actionbar_profile(Ref<ActionBarProfile> other) {
	for (int i = 0; i < _action_bars.size(); ++i) {
		_action_bars.get(i)->set_owner(NULL);
	}

	_action_bars.clear();

	_name = other->get_action_bar_profile_name();

	for (int i = 0; i < other->get_action_bar_count(); ++i) {
		Ref<ActionBarEntry> e = other->get_action_bar(i);

		e->set_owner(this);
		_action_bars.push_back(e);
	}

	emit_change();
}

ActionBarProfile::ActionBarProfile() {
	_owner = NULL;
}

ActionBarProfile::~ActionBarProfile() {
	_action_bars.clear();
}

void ActionBarProfile::emit_change() {
	emit_signal("changed");

	if (_owner != NULL)
		_owner->emit_change();
}

void ActionBarProfile::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	ClassDB::bind_method(D_METHOD("get_owner"), &ActionBarProfile::get_owner);

	ClassDB::bind_method(D_METHOD("get_action_bar_profile_name"), &ActionBarProfile::get_action_bar_profile_name);
	ClassDB::bind_method(D_METHOD("set_action_bar_profile_name", "value"), &ActionBarProfile::set_action_bar_profile_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "action_bar_profile_name"), "set_action_bar_profile_name", "get_action_bar_profile_name");

	ClassDB::bind_method(D_METHOD("load_defaults"), &ActionBarProfile::load_defaults);

	ClassDB::bind_method(D_METHOD("get_action_bar_count"), &ActionBarProfile::get_action_bar_count);
	ClassDB::bind_method(D_METHOD("add_action_bar", "actionbar"), &ActionBarProfile::add_action_bar);
	ClassDB::bind_method(D_METHOD("get_action_bar", "index"), &ActionBarProfile::get_action_bar);
	ClassDB::bind_method(D_METHOD("remove_action_bar", "index"), &ActionBarProfile::remove_action_bar);
	ClassDB::bind_method(D_METHOD("clear_action_bars"), &ActionBarProfile::clear_action_bars);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ActionBarProfile::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ActionBarProfile::to_dict);

	ClassDB::bind_method(D_METHOD("from_actionbar_profile", "other"), &ActionBarProfile::from_actionbar_profile);

	ClassDB::bind_method(D_METHOD("emit_change"), &ActionBarProfile::emit_change);
}
