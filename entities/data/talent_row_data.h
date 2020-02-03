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

#ifndef TALENT_ROW_DATA_H
#define TALENT_ROW_DATA_H

#include "core/reference.h"
#include "core/ustring.h"

#include "../../data/auras/aura.h"

class Aura;

class TalentRowData : public Resource {
	GDCLASS(TalentRowData, Resource);

public:
	Ref<Aura> get_talent_index(int index) const;
	void set_talent_index(int index, Ref<Aura> talent);

	Ref<Aura> get_talent(int culomn, int rank) const;
	void set_talent(int culomn, int rank, Ref<Aura> talent);

	bool has_talent_with_id(int id);
	Ref<Aura> get_talent_with_id(int id);

	TalentRowData();
	~TalentRowData();

public:
	enum {
		MAX_TALENTS_IN_ROW = 5,
		MAX_TALENTS_PER_ENTRY = 5,
		TOTAL_ENTRIES = MAX_TALENTS_IN_ROW * MAX_TALENTS_PER_ENTRY,
	};

protected:
	static void _bind_methods();

private:
	Ref<Aura> _talents[TOTAL_ENTRIES];
};

#endif
