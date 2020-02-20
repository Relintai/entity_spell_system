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

#ifndef LEVEL_XP_H
#define LEVEL_XP_H

#include "core/resource.h"
#include "core/variant.h"
#include "core/vector.h"

class XPData : public Resource {
	GDCLASS(XPData, Resource);

public:
	int get_character_max_level();
	int get_character_xp(int level);
	void set_character_xp(int level, int value);
	bool can_character_level_up(int level);

	int get_class_max_level();
	int get_class_xp(int level);
	void set_class_xp(int level, int value);
	bool can_class_level_up(int level);

	XPData();
	~XPData();

protected:
	static void _bind_methods();

private:
	Vector<int> _character_xps;
	Vector<int> _class_xps;
};

#endif
