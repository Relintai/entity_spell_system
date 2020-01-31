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

#ifndef CHARACTER_SPEC_H
#define CHARACTER_SPEC_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "talent_row_data.h"

class TalentRowData;
class Aura;

class CharacterSpec : public Resource {
	GDCLASS(CharacterSpec, Resource);

public:
	int get_id();
	void set_id(int value);

	int get_num_talent_rows();
	void set_num_talent_rows(int value);

	Ref<TalentRowData> get_talent_row(int index) const;
	void set_talent_row(const int index, const Ref<TalentRowData> row);

	Vector<Variant> get_talent_rows();
	void set_talent_rows(const Vector<Variant> &auras);

	Ref<Aura> get_talent(const int row_index, const int culomn, const int rank) const;

	CharacterSpec();
	~CharacterSpec();

protected:
	static void _bind_methods();

private:
	int _id;
	Vector<Ref<TalentRowData> > _rows;
};

#endif
