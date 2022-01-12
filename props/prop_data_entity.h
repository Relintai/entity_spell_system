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

#ifndef PROP_DATA_ENTITY_H
#define PROP_DATA_ENTITY_H

#if PROPS_PRESENT

#include "../../props/props/prop_data_entry.h"

#include "../entities/data/entity_data.h"

class PropDataEntity : public PropDataEntry {
	GDCLASS(PropDataEntity, PropDataEntry);

public:
	Ref<EntityData> get_entity_data() const;
	void set_entity_data(const Ref<EntityData> &value);

	int get_level() const;
	void set_level(const int value);

	PropDataEntity();
	~PropDataEntity();

protected:
	static void _bind_methods();

private:
	int _level;
	Ref<EntityData> _entity_data;
};

#endif

#endif
