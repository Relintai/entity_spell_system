#include "input_profile_modifier.h"

int InputProfileModifier::get_modifier_count() {
	return _modifier_actions->size();
}

void InputProfileModifier::clear_modifiers() {
	_modifier_actions->clear();
}

void InputProfileModifier::add_modifier(String modifier) {
	_modifier_actions->push_back(modifier);
}

String InputProfileModifier::get_modifier(int index) {
	return _modifier_actions->get(index);
}

void InputProfileModifier::set_modifier(int index, String value) {
	_modifier_actions->set(index, value);
}

void InputProfileModifier::remove_modifier(int index) {
	_modifier_actions->remove(index);
}

int InputProfileModifier::get_entry_count() {
	return _entries->size();
}

void InputProfileModifier::clear_entries() {
	_entries->clear();
}

void InputProfileModifier::add_entry(Ref<InputProfileModifierEntry> modifier) {
	_entries->push_back(Ref<InputProfileModifierEntry>(modifier));
}

Ref<InputProfileModifierEntry> InputProfileModifier::get_entry(int index) {
	return _entries->get(index);
}

void InputProfileModifier::set_entry(int index, Ref<InputProfileModifierEntry> value) {
	_entries->set(index, Ref<InputProfileModifierEntry>(value));
}

void InputProfileModifier::remove_entry(int index) {
	_entries->remove(index);
}

InputProfileModifier::InputProfileModifier() {
	_modifier_actions = memnew(Vector<String>());
	_entries = memnew(Vector<Ref<InputProfileModifierEntry> >());
}

InputProfileModifier::~InputProfileModifier() {
	_modifier_actions->clear();
	_entries->clear();

	memdelete(_modifier_actions);
	memdelete(_entries);
}

void InputProfileModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_modifier_count"), &InputProfileModifier::get_modifier_count);
	ClassDB::bind_method(D_METHOD("clear_modifiers"), &InputProfileModifier::clear_modifiers);
	ClassDB::bind_method(D_METHOD("add_modifier", "modifier"), &InputProfileModifier::add_modifier);
	ClassDB::bind_method(D_METHOD("get_modifier", "index"), &InputProfileModifier::get_modifier);
	ClassDB::bind_method(D_METHOD("set_modifier", "index", "value"), &InputProfileModifier::set_modifier);
	ClassDB::bind_method(D_METHOD("remove_modifier", "index"), &InputProfileModifier::remove_modifier);

	ClassDB::bind_method(D_METHOD("get_entry_count"), &InputProfileModifier::get_entry_count);
	ClassDB::bind_method(D_METHOD("clear_entries"), &InputProfileModifier::clear_entries);
	ClassDB::bind_method(D_METHOD("add_entry", "entry"), &InputProfileModifier::add_entry);
	ClassDB::bind_method(D_METHOD("get_entry", "index"), &InputProfileModifier::get_entry);
	ClassDB::bind_method(D_METHOD("set_entry", "index", "value"), &InputProfileModifier::set_entry);
	ClassDB::bind_method(D_METHOD("remove_entry", "index"), &InputProfileModifier::remove_entry);

}
