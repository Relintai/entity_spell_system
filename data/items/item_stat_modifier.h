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

#ifndef ITEM_STAT_MODIFIER_H
#define ITEM_STAT_MODIFIER_H

#include "../../entities/stats/stat.h"
#include "core/reference.h"

#include "core/version.h"

#if VERSION_MAJOR >= 4
#define REAL FLOAT
#endif

class ItemStatModifier : public Reference {
	GDCLASS(ItemStatModifier, Reference);

public:
	int get_stat_id();
	void set_stat_id(int value);

	float get_base_mod();
	void set_base_mod(float value);

	float get_bonus_mod();
	void set_bonus_mod(float value);

	float get_percent_mod();
	void set_percent_mod(float value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);

	ItemStatModifier();

protected:
	void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

private:
	int _stat_id;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
};

#endif
