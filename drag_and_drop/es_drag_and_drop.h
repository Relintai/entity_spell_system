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

#ifndef ES_DRAG_AND_DROP_H
#define ES_DRAG_AND_DROP_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#include "core/string/ustring.h"
#else
#include "core/reference.h"
#include "core/ustring.h"
#endif

#include "scene/main/node.h"

class ESDragAndDrop : public Reference {
	GDCLASS(ESDragAndDrop, Reference);

public:
	static const String BINDING_STRING_ES_DRAG_AND_DROP_TYPE;

	enum ESDragAndDropType {
		ES_DRAG_AND_DROP_TYPE_NONE = 0,
		ES_DRAG_AND_DROP_TYPE_SPELL = 1,
		ES_DRAG_AND_DROP_TYPE_ITEM = 2,
		ES_DRAG_AND_DROP_TYPE_INVENTORY_ITEM = 3,
		ES_DRAG_AND_DROP_TYPE_EQUIPPED_ITEM = 4,
	};

	Node *get_origin() const;
	void set_origin(Node *owner);

	ESDragAndDropType get_type() const;
	void set_type(const ESDragAndDropType type);

	StringName get_item_path() const;
	void set_item_path(const StringName &item_path);

	ESDragAndDrop();

protected:
	static void _bind_methods();

private:
	Node *_origin;
	ESDragAndDropType _type;
	StringName _item_path;
};

VARIANT_ENUM_CAST(ESDragAndDrop::ESDragAndDropType);

#endif
