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

#ifndef CHARACTER_SPEC_H
#define CHARACTER_SPEC_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#include "core/ustring.h"
#endif

class Spell;

class CharacterSpec : public Resource {
	GDCLASS(CharacterSpec, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int get_num_rows() const;
	void set_num_rows(const int value);

	int get_num_columns(const int row) const;
	void set_num_columns(const int row, const int value);

	int get_num_ranks(const int row, const int column) const;
	void set_num_ranks(const int row, const int column, const int value);

	Vector<Variant> get_talents();

	Ref<Spell> get_talent(const int row, const int column, const int rank);
	void set_talent(const int row, const int column, const int rank, const Ref<Spell> &talent);

	bool has_talent_with_id(const int id);
	Ref<Spell> get_talent_with_id(const int id);

	CharacterSpec();
	~CharacterSpec();

protected:
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	static void _bind_methods();

private:
	int _id;
	Vector<Vector<Vector<Ref<Spell> > > > _rows;
};

#endif
