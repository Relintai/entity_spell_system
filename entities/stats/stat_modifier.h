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

#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include "core/reference.h"

class Stat;

class StatModifier : public Reference {
	GDCLASS(StatModifier, Reference);

public:
	StatModifier();

	StatModifier(int i, float base_mod, float bonus_mod, float percent_mod, Stat *owner);

	Ref<Stat> get_owner();
	void set_owner(Ref<Stat> stat);

	int get_id();
	void set_id(int value);

	float get_base_mod();
	void set_base_mod(float value);

	float get_bonus_mod();
	void set_bonus_mod(float value);

	float get_percent_mod();
	void set_percent_mod(float value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

protected:
	static void _bind_methods();

private:
	int _id;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;

	Stat *_owner;
};

#endif
