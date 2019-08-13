#include "character_spec.h"

#include "talent.h"

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
	ERR_FAIL_INDEX_V(index, MAX_TALENT_ROWS, Ref<TalentRowData>(NULL));

	return _rows[index];
}

void CharacterSpec::set_talent_row(const int index, const Ref<TalentRowData> row) {
	ERR_FAIL_INDEX(index, MAX_TALENT_ROWS);

	_rows[index] = row;
}

Ref<Talent> CharacterSpec::get_talent(const int row_index, const int index) const {
	ERR_FAIL_INDEX_V(row_index, MAX_TALENT_ROWS, Ref<Talent>(NULL));

	if (_rows[row_index].is_valid()) {
		return _rows[row_index]->get_talent(index);
	}

	return Ref<Talent>(NULL);
}


CharacterSpec::CharacterSpec() {
	_spec_id = 0;
}

CharacterSpec::~CharacterSpec() {
	for (int i = 0; i < MAX_TALENT_ROWS; ++i) {
		_rows[i].unref();
	}
}

void CharacterSpec::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_spec_id"), &CharacterSpec::get_spec_id);
	ClassDB::bind_method(D_METHOD("set_spec_id", "value"), &CharacterSpec::set_spec_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spec_id"), "set_spec_id", "get_spec_id");

	ClassDB::bind_method(D_METHOD("get_spec_name"), &CharacterSpec::get_spec_name);
	ClassDB::bind_method(D_METHOD("set_spec_name", "value"), &CharacterSpec::set_spec_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "spec_name"), "set_spec_name", "get_spec_name");

	ClassDB::bind_method(D_METHOD("get_talent_row", "index"), &CharacterSpec::get_talent_row);
	ClassDB::bind_method(D_METHOD("set_talent_row", "index", "row"), &CharacterSpec::set_talent_row);

	for (int i = 0; i < MAX_TALENT_ROWS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "TalentRowData", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_row", "get_talent_row", i);
	}

	ClassDB::bind_method(D_METHOD("get_talent", "row_index", "index"), &CharacterSpec::get_talent);

	BIND_CONSTANT(MAX_TALENT_ROWS);
}
