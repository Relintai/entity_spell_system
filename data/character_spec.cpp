#include "character_spec.h"

int CharacterSpec::get_spec_id() {
	return _spec_id;
}

void CharacterSpec::set_spec_id(int value) {
	_spec_id = value;
}

String CharacterSpec::get_spec_name() {
	return _spec_name;
}

void CharacterSpec::set_spec_name(String value) {
	_spec_name = value;
}

Ref<TalentRowData> CharacterSpec::get_talent_row(int index) const {
	return _rows[index];
}

Ref<Talent> CharacterSpec::get_talent0_in_row(int index) const {
	return _rows[index]->get_talent0();
}

void CharacterSpec::set_talent0_in_row(int index, Ref<Talent> talent) {
	_rows[index]->set_talent0(talent);
}

Ref<Talent> CharacterSpec::get_talent1_in_row(int index) const {
	return _rows[index]->get_talent1();
}
void CharacterSpec::set_talent1_in_row(int index, Ref<Talent> talent) {
	_rows[index]->set_talent1(talent);
}

Ref<Talent> CharacterSpec::get_talent2_in_row(int index) const {
	return _rows[index]->get_talent2();
}

void CharacterSpec::set_talent2_in_row(int index, Ref<Talent> talent) {
	_rows[index]->set_talent2(talent);
}

Ref<Talent> CharacterSpec::get_talent3_in_row(int index) const {
	return _rows[index]->get_talent3();
}

void CharacterSpec::set_talent3_in_row(int index, Ref<Talent> talent) {
	_rows[index]->set_talent3(talent);
}

Ref<Talent> CharacterSpec::get_talent4_in_row(int index) const {
	return _rows[index]->get_talent4();
}

void CharacterSpec::set_talent4_in_row(int index, Ref<Talent> talent) {
	_rows[index]->set_talent4(talent);
}

CharacterSpec::CharacterSpec() {
	for (int i = 0; i < MAX_TALENT_ROWS; ++i) {
		_rows[i] = Ref<TalentRowData>(memnew(TalentRowData()));
	}

	_spec_id = 0;
}

CharacterSpec::~CharacterSpec() {
}

void CharacterSpec::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_spec_id"), &CharacterSpec::get_spec_id);
	ClassDB::bind_method(D_METHOD("set_spec_id", "value"), &CharacterSpec::set_spec_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spec_id"), "set_spec_id", "get_spec_id");

	ClassDB::bind_method(D_METHOD("get_spec_name"), &CharacterSpec::get_spec_name);
	ClassDB::bind_method(D_METHOD("set_spec_name", "value"), &CharacterSpec::set_spec_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "spec_name"), "set_spec_name", "get_spec_name");

	ClassDB::bind_method(D_METHOD("get_talent0_in_row", "index"), &CharacterSpec::get_talent0_in_row);
	ClassDB::bind_method(D_METHOD("set_talent0_in_row", "index", "value"), &CharacterSpec::set_talent0_in_row);
	ClassDB::bind_method(D_METHOD("get_talent1_in_row", "index"), &CharacterSpec::get_talent0_in_row);
	ClassDB::bind_method(D_METHOD("set_talent1_in_row", "index", "value"), &CharacterSpec::set_talent0_in_row);
	ClassDB::bind_method(D_METHOD("get_talent2_in_row", "index"), &CharacterSpec::get_talent0_in_row);
	ClassDB::bind_method(D_METHOD("set_talent2_in_row", "index", "value"), &CharacterSpec::set_talent0_in_row);
	ClassDB::bind_method(D_METHOD("get_talent3_in_row", "index"), &CharacterSpec::get_talent0_in_row);
	ClassDB::bind_method(D_METHOD("set_talent3_in_row", "index", "value"), &CharacterSpec::set_talent0_in_row);
	ClassDB::bind_method(D_METHOD("get_talent4_in_row", "index"), &CharacterSpec::get_talent0_in_row);
	ClassDB::bind_method(D_METHOD("set_talent4_in_row", "index", "value"), &CharacterSpec::set_talent0_in_row);

	for (int i = 0; i < MAX_TALENT_ROWS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent0", PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent0_in_row", "get_talent0_in_row", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent1", PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent1_in_row", "get_talent1_in_row", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent2", PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent2_in_row", "get_talent2_in_row", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent3", PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent3_in_row", "get_talent3_in_row", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent4", PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent4_in_row", "get_talent4_in_row", i);
	}

	ClassDB::bind_method(D_METHOD("get_talent_row"), &CharacterSpec::get_talent_row);
}
