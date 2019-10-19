#include "character_spec.h"

#include "../../data/aura.h"

int CharacterSpec::get_id() {
	return _id;
}
void CharacterSpec::set_id(int value) {
	_id = value;
}

String CharacterSpec::get_text_name() {
	return _text_name;
}
void CharacterSpec::set_text_name(String value) {
	_text_name = value;
}

int CharacterSpec::get_num_talent_rows() {
	return _rows.size();
}
void CharacterSpec::set_num_talent_rows(int value) {
	_rows.resize(value);
}

Ref<TalentRowData> CharacterSpec::get_talent_row(int index) const {
	ERR_FAIL_INDEX_V(index, _rows.size(), Ref<TalentRowData>(NULL));

	return _rows[index];
}
void CharacterSpec::set_talent_row(const int index, const Ref<TalentRowData> row) {
	ERR_FAIL_INDEX(index, _rows.size());

	_rows.set(index, row);
}

Vector<Variant> CharacterSpec::get_talent_rows() {
	Vector<Variant> r;
	for (int i = 0; i < _rows.size(); i++) {
		r.push_back(_rows[i].get_ref_ptr());
	}
	return r;
}
void CharacterSpec::set_talent_rows(const Vector<Variant> &talent_rows) {
	_rows.clear();
	for (int i = 0; i < talent_rows.size(); i++) {
		Ref<TalentRowData> talent_row = Ref<TalentRowData>(talent_rows[i]);

		_rows.push_back(talent_row);
	}
}

Ref<Aura> CharacterSpec::get_talent(const int row_index, const int culomn, const int rank) const {
	ERR_FAIL_INDEX_V(row_index, _rows.size(), Ref<Aura>(NULL));

	if (_rows[row_index].is_valid()) {
		return _rows[row_index]->get_talent(culomn, rank);
	}

	return Ref<Aura>(NULL);
}


CharacterSpec::CharacterSpec() {
	_id = 0;
}

CharacterSpec::~CharacterSpec() {
	_rows.clear();
}

void CharacterSpec::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &CharacterSpec::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CharacterSpec::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spec_id"), "set_id", "get_id");//REMOVE

	ClassDB::bind_method(D_METHOD("get_text_name"), &CharacterSpec::get_text_name);
	ClassDB::bind_method(D_METHOD("set_text_name", "value"), &CharacterSpec::set_text_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_text_name", "get_text_name");

	ClassDB::bind_method(D_METHOD("get_num_talent_rows"), &CharacterSpec::get_num_talent_rows);
	ClassDB::bind_method(D_METHOD("set_num_talent_rows", "value"), &CharacterSpec::set_num_talent_rows);

	ClassDB::bind_method(D_METHOD("get_talent_row", "index"), &CharacterSpec::get_talent_row);
	ClassDB::bind_method(D_METHOD("set_talent_row", "index", "row"), &CharacterSpec::set_talent_row);

	ClassDB::bind_method(D_METHOD("get_talent", "row_index", "culomn", "rank"), &CharacterSpec::get_talent);

	ClassDB::bind_method(D_METHOD("get_talent_rows"), &CharacterSpec::get_talent_rows);
	ClassDB::bind_method(D_METHOD("set_talent_rows", "auras"), &CharacterSpec::set_talent_rows);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "talent_rows", PROPERTY_HINT_NONE, "17/17:TalentRowData", PROPERTY_USAGE_DEFAULT, "TalentRowData"), "set_talent_rows", "get_talent_rows");
}
