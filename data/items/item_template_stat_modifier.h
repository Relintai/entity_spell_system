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

#ifndef ITEM_TEMPLATE_STAT_MODIFIER_H
#define ITEM_TEMPLATE_STAT_MODIFIER_H

#include "../../entities/stats/stat.h"
#include "core/reference.h"

class ItemTemplateStatModifier : public Reference {
	GDCLASS(ItemTemplateStatModifier, Reference);

public:
	Stat::StatId get_stat_id();
	void set_stat_id(Stat::StatId value);

	float get_min_base_mod();
	void set_min_base_mod(float value);

	float get_max_base_mod();
	void set_max_base_mod(float value);

	float get_min_bonus_mod();
	void set_min_bonus_mod(float value);

	float get_max_bonus_mod();
	void set_max_bonus_mod(float value);

	float get_min_percent_mod();
	void set_min_percent_mod(float value);

	float get_max_percent_mod();
	void set_max_percent_mod(float value);

	float get_scaling_factor();
	void set_scaling_factor(float value);

	ItemTemplateStatModifier();

protected:
	static void _bind_methods();

private:
	Stat::StatId _stat_id;

	float _min_mod_max;
	float _max_mod_max;

	float _min_mod_precent;
	float _max_mod_precent;

	float _scaling_factor;
};

#endif
