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

#ifndef STAT_DATA_ENTRY_H
#define STAT_DATA_ENTRY_H

#include "core/resource.h"
#include "scene/resources/curve.h"

#include "level_stat_data.h"

class StatDataEntry : public Resource {
	GDCLASS(StatDataEntry, Resource);

public:
	float get_base();
	void set_base(float value);

	bool has_mod_stats();

	int get_mod_stat_count();
	void set_mod_stat_count(int value);

	int get_mod_stat_id(int index);
	void set_mod_stat_id(int index, int value);

	float get_mod_stat_multiplier(int index);
	void set_mod_stat_multiplier(int index, float value);

	StatDataEntry();
	~StatDataEntry();

protected:
	void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

public:
	struct ModStat {
		int stat_id;
		float multiplier;
	};

	enum {
		MAX_MOD_STATS = 3,
	};

private:
	float _base;

	int _mod_stat_count;
	ModStat _mod_stats[MAX_MOD_STATS];
};

#endif
