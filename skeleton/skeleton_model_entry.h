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

#ifndef SKELETON_MODEL_ENTRY_H
#define SKELETON_MODEL_ENTRY_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#else
#include "core/reference.h"
#endif

#include "../data/items/model_visual_entry.h"

class SkeletonModelEntry : public Reference {
	GDCLASS(SkeletonModelEntry, Reference);

public:
	int get_count() const;
	void set_count(const int value);

	int get_priority() const;
	void set_priority(const int value);

	Color get_color() const;
	void set_color(const Color value);

	Ref<ModelVisualEntry> get_entry();
	void set_entry(Ref<ModelVisualEntry> entry);

	SkeletonModelEntry();
	~SkeletonModelEntry();

protected:
	static void _bind_methods();

private:
	int _count;
	int _priority;
	Color _color;
	Ref<ModelVisualEntry> _entry;
};

#endif
