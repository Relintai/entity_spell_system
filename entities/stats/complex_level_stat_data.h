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

#ifndef COMPLEX_LEVEL_STAT_DATA_H
#define COMPLEX_LEVEL_STAT_DATA_H

#include "core/resource.h"

#include "../../entity_enums.h"
#include "level_stat_data.h"

class ComplexLevelStatData : public LevelStatData {
	GDCLASS(ComplexLevelStatData, LevelStatData);

public:
	int get_agility_for_level(int level);
	void set_agility_for_level(int level, int value);

	int get_strength_for_level(int level);
	void set_strength_for_level(int level, int value);

	int get_stamina_for_level(int level);
	void set_stamina_for_level(int level, int value);

	int get_intellect_for_level(int level);
	void set_intellect_for_level(int level, int value);

	int get_spirit_for_level(int level);
	void set_spirit_for_level(int level, int value);

	int _get_stat_diff(int stat, int old_level, int new_level);

public:
	struct ComplexLevelStatsEntry {
		int agility;
		int strength;
		int stamina;
		int intellect;
		int spirit;

		ComplexLevelStatsEntry() {
			agility = 0;
			strength = 0;
			stamina = 0;
			intellect = 0;
			spirit = 0;
		}
	};

protected:
	static void _bind_methods();

private:
	ComplexLevelStatsEntry _entries[EntityEnums::MAX_LEVEL];
};

#endif
