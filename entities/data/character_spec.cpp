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

#include "character_spec.h"

#include "../../data/auras/aura.h"

#include "core/version.h"

int CharacterSpec::get_id() {
	return _id;
}
void CharacterSpec::set_id(int value) {
	_id = value;
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
		#if VERSION_MAJOR < 4
		r.push_back(_rows[i].get_ref_ptr());
		#else
		r.push_back(_rows[i]);
		#endif
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

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_num_talent_rows"), &CharacterSpec::get_num_talent_rows);
	ClassDB::bind_method(D_METHOD("set_num_talent_rows", "value"), &CharacterSpec::set_num_talent_rows);

	ClassDB::bind_method(D_METHOD("get_talent_row", "index"), &CharacterSpec::get_talent_row);
	ClassDB::bind_method(D_METHOD("set_talent_row", "index", "row"), &CharacterSpec::set_talent_row);

	ClassDB::bind_method(D_METHOD("get_talent", "row_index", "culomn", "rank"), &CharacterSpec::get_talent);

	ClassDB::bind_method(D_METHOD("get_talent_rows"), &CharacterSpec::get_talent_rows);
	ClassDB::bind_method(D_METHOD("set_talent_rows", "auras"), &CharacterSpec::set_talent_rows);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "talent_rows", PROPERTY_HINT_NONE, "17/17:TalentRowData", PROPERTY_USAGE_DEFAULT, "TalentRowData"), "set_talent_rows", "get_talent_rows");
}
