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

#include "level_stat_data.h"

int LevelStatData::get_stat_diff(int main_stat, int old_level, int new_level) {
	if (has_method("_get_stat_diff"))
		return call("_get_stat_diff", main_stat, old_level, new_level);

	return 0;
}

void LevelStatData::_bind_methods() {

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "diff"), "_get_stat_diff", PropertyInfo(Variant::INT, "main_stat"), PropertyInfo(Variant::INT, "old_level"), PropertyInfo(Variant::INT, "new_level")));

	ClassDB::bind_method(D_METHOD("get_stat_diff", "stat", "old_level", "new_level"), &LevelStatData::get_stat_diff);
}
