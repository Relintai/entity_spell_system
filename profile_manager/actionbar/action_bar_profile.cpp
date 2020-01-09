#include "action_bar_profile.h"

String ActionBarProfile::get_action_bar_profile_name() {
	return _name;
}

void ActionBarProfile::set_action_bar_profile_name(String value) {
	_name = value;
}

Vector<Ref<ActionBarEntry> > &ActionBarProfile::get_action_bars() {
	return _action_bars;
}

void ActionBarProfile::load_defaults() {
	_action_bars.clear();

	Ref<ActionBarEntry> actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(1);
	actionBarEntry->set_slot_num(12);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(2);
	actionBarEntry->set_slot_num(12);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(3);
	actionBarEntry->set_slot_num(12);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));

	actionBarEntry = Ref<ActionBarEntry>(memnew(ActionBarEntry()));
	actionBarEntry->set_action_bar_id(4);
	actionBarEntry->set_slot_num(12);
	_action_bars.push_back(Ref<ActionBarEntry>(actionBarEntry));
}

int ActionBarProfile::get_action_bar_count() {
	return _action_bars.size();
}

void ActionBarProfile::add_action_bar(Ref<ActionBarEntry> actionbar) {
	_action_bars.push_back(Ref<ActionBarEntry>(actionbar));
}

Ref<ActionBarEntry> ActionBarProfile::get_action_bar(int index) {
	ERR_FAIL_INDEX_V(index, _action_bars.size(), Ref<ActionBarEntry>(NULL));

	return _action_bars.get(index);
}

void ActionBarProfile::remove_action_bar(int index) {
	_action_bars.remove(index);
}

void ActionBarProfile::clear_action_bars() {
	_action_bars.clear();
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
	if (dict.empty())
		return;

	_action_bars.clear();

	_name = dict.get("name", "");

	Array arr = dict.get("action_bars", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ActionBarEntry> e;
		e.instance();

		e->from_dict(arr.get(i));

		_action_bars.push_back(e);
	}
}

void ActionBarProfile::from_actionbar_profile(Ref<ActionBarProfile> other) {
	_action_bars.clear();

	_name = other->get_action_bar_profile_name();

	for (int i = 0; i < other->get_action_bar_count(); ++i) {
		_action_bars.push_back(other->get_action_bar(i));
	}
}

ActionBarProfile::ActionBarProfile() {
}

ActionBarProfile::~ActionBarProfile() {
	_action_bars.clear();
}

void ActionBarProfile::_bind_methods() {
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
}
