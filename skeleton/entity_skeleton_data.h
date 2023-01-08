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

#ifndef ENTITY_SKELETON_DATA_H
#define ENTITY_SKELETON_DATA_H

#include "core/version.h"

#include "core/io/resource.h"
#include "core/string/ustring.h"


class EntitySkeletonData : public Resource {
	GDCLASS(EntitySkeletonData, Resource);

public:
protected:
	static void _bind_methods();

	enum {
		MAX_ENTRIES = 20
	};

	struct ESDataEntry {
		Ref<CharacterSkeletonVisualEntry> entry;
		Vector3 offset;
		Vector3 rotation;
		Vector3 scale;
	};

private:
	ESDataEntry _entries[MAX_ENTRIES];
};

#endif
