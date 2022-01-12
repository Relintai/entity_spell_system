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

#include "character_spec.h"

#include "../../data/spells/spell.h"

#include "../../defines.h"

int CharacterSpec::get_id() const {
	return _id;
}
void CharacterSpec::set_id(const int value) {
	_id = value;
}

int CharacterSpec::get_num_rows() const {
	return _rows.size();
}
void CharacterSpec::set_num_rows(const int value) {
	_rows.resize(value);
}

int CharacterSpec::get_num_columns(const int row) const {
	ERR_FAIL_INDEX_V(row, _rows.size(), 0);

	return _rows[row].size();
}
void CharacterSpec::set_num_columns(const int row, const int value) {
	ERR_FAIL_INDEX(row, _rows.size());

	_rows.write[row].resize(value);
}

int CharacterSpec::get_num_ranks(const int row, const int column) const {
	ERR_FAIL_INDEX_V(row, _rows.size(), 0);
	ERR_FAIL_INDEX_V(column, _rows[row].size(), 0);

	return _rows[row][column].size();
}
void CharacterSpec::set_num_ranks(const int row, const int column, const int value) {
	ERR_FAIL_INDEX(row, _rows.size());

	_rows.write[row].write[column].resize(value);
}

Vector<Variant> CharacterSpec::get_talents() {
	Vector<Variant> r;
	for (int i = 0; i < _rows.size(); i++) {
		Vector<Variant> col;

		for (int j = 0; j < _rows[i].size(); j++) {
			Vector<Variant> entries;

			for (int k = 0; k < _rows[j].size(); k++) {
#if GODOT4
				entries.push_back(_rows[i][j][k]);
#else
				entries.push_back(_rows[i][j][k].get_ref_ptr());
#endif
			}

			col.push_back(entries);
		}

		r.push_back(col);
	}

	return r;
}

Ref<Spell> CharacterSpec::get_talent(const int row, const int column, const int rank) {
	ERR_FAIL_INDEX_V(row, _rows.size(), Ref<Spell>());
	ERR_FAIL_INDEX_V(column, _rows[row].size(), Ref<Spell>());
	ERR_FAIL_INDEX_V(rank, _rows[row][column].size(), Ref<Spell>());

	return _rows[row][column][rank];
}
void CharacterSpec::set_talent(const int row, const int column, const int rank, const Ref<Spell> &talent) {
	ERR_FAIL_INDEX(row, _rows.size());
	ERR_FAIL_INDEX(column, _rows[row].size());
	ERR_FAIL_INDEX(rank, _rows[row][column].size());

	_rows.write[row].write[column].write[rank] = talent;
}

bool CharacterSpec::has_talent_with_id(const int id) {
	for (int i = 0; i < _rows.size(); ++i) {
		for (int j = 0; j < _rows[i].size(); ++j) {
			for (int k = 0; k < _rows[i][j].size(); ++k) {
				const Ref<Spell> a = _rows[i][j][k];

				if (a.is_valid() && a->get_id() == id)
					return true;
			}
		}
	}

	return false;
}

Ref<Spell> CharacterSpec::get_talent_with_id(const int id) {
	for (int i = 0; i < _rows.size(); ++i) {
		for (int j = 0; j < _rows[i].size(); ++j) {
			for (int k = 0; k < _rows[i][j].size(); ++k) {
				const Ref<Spell> a = _rows[i][j][k];

				if (a.is_valid() && a->get_id() == id)
					return a;
			}
		}
	}

	return Ref<Spell>();
}

CharacterSpec::CharacterSpec() {
	_id = 0;
}

CharacterSpec::~CharacterSpec() {
	for (int i = 0; i < _rows.size(); ++i) {
		for (int j = 0; j < _rows[i].size(); ++j) {
			for (int k = 0; k < _rows[i][j].size(); ++k) {
				_rows.write[i].write[j].write[k].unref();
			}
		}
	}

	_rows.clear();
}

bool CharacterSpec::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.begins_with("row_")) {
		String nprop = name.get_slicec('/', 0); //row_[]
		int row_id = nprop.get_slicec('_', 1).to_int();

		if (row_id >= _rows.size()) {
			_rows.resize(row_id + 1);
		}

		String cprop = name.get_slicec('/', 1); //column_[] or size

		if (cprop == "size") {
			_rows.write[row_id].resize(p_value);

			return true;
		} else {
			int col_id = cprop.get_slicec('_', 1).to_int();

			if (col_id >= _rows[row_id].size()) {
				_rows.write[row_id].resize(col_id + 1);
			}

			String eprop = name.get_slicec('/', 2); //entry_[] or size

			if (eprop == "size") {
				_rows.write[row_id].write[col_id].resize(p_value);

				return true;
			} else {
				int entry_id = eprop.get_slicec('_', 1).to_int();

				if (entry_id >= _rows[row_id][col_id].size()) {
					_rows.write[row_id].write[col_id].resize(col_id + 1);
				}

				_rows.write[row_id].write[col_id].write[entry_id] = p_value;

				return true;
			}
		}
	}

	return false;
}

bool CharacterSpec::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.begins_with("row_")) {
		String nprop = name.get_slicec('/', 0); //row_[]
		int row_id = nprop.get_slicec('_', 1).to_int();

		if (row_id >= _rows.size()) {
			return false;
		}

		String cprop = name.get_slicec('/', 1); //column_[] or size

		if (cprop == "size") {
			r_ret = _rows[row_id].size();

			return true;
		} else {
			int col_id = cprop.get_slicec('_', 1).to_int();

			if (col_id >= _rows[row_id].size()) {
				return false;
			}

			String eprop = name.get_slicec('/', 2); //entry_[] or size

			if (eprop == "size") {
				r_ret = _rows[row_id][col_id].size();

				return true;
			} else {

				int entry_id = eprop.get_slicec('_', 1).to_int();

				if (entry_id >= _rows[row_id][col_id].size()) {
					return false;
				}

				r_ret = _rows[row_id][col_id][entry_id];

				return true;
			}
		}
	} else {
		return false;
	}

	return false;
}

void CharacterSpec::_get_property_list(List<PropertyInfo> *p_list) const {
	for (int i = 0; i < _rows.size(); ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, "row_" + itos(i) + "/size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED));

		for (int j = 0; j < _rows[i].size(); ++j) {
			p_list->push_back(PropertyInfo(Variant::INT, "row_" + itos(i) + "/column_" + itos(j) + "/size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED));

			for (int k = 0; k < _rows[i][j].size(); ++k) {
				p_list->push_back(PropertyInfo(Variant::OBJECT, "row_" + itos(i) + "/column_" + itos(j) + "/entry_" + itos(k), PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT));
			}
		}
	}
}

void CharacterSpec::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &CharacterSpec::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CharacterSpec::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_num_rows"), &CharacterSpec::get_num_rows);
	ClassDB::bind_method(D_METHOD("set_num_rows", "value"), &CharacterSpec::set_num_rows);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_rows", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_num_rows", "get_num_rows");

	ClassDB::bind_method(D_METHOD("get_num_columns", "row"), &CharacterSpec::get_num_columns);
	ClassDB::bind_method(D_METHOD("set_num_columns", "row", "value"), &CharacterSpec::set_num_columns);

	ClassDB::bind_method(D_METHOD("get_num_ranks", "row", "culomn"), &CharacterSpec::get_num_ranks);
	ClassDB::bind_method(D_METHOD("set_num_ranks", "row", "culomn", "value"), &CharacterSpec::set_num_ranks);

	ClassDB::bind_method(D_METHOD("get_talents"), &CharacterSpec::get_talents);

	ClassDB::bind_method(D_METHOD("get_talent", "row", "culomn", "rank"), &CharacterSpec::get_talent);
	ClassDB::bind_method(D_METHOD("set_talent", "row", "culomn", "rank"), &CharacterSpec::set_talent);

	ClassDB::bind_method(D_METHOD("has_talent_with_id", "id"), &CharacterSpec::has_talent_with_id);
	ClassDB::bind_method(D_METHOD("get_talent_with_id", "id"), &CharacterSpec::get_talent_with_id);
}
