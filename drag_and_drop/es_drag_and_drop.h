#ifndef ES_DRAG_AND_DROP_H
#define ES_DRAG_AND_DROP_H

#include "core/reference.h"
#include "core/ustring.h"

class ESDragAndDrop : public Reference {
	GDCLASS(ESDragAndDrop, Reference);

public:
	static const String BINDING_STRING_ES_DRAG_AND_DROP_TYPE;

	enum ESDragAndDropType {
		ES_DRAG_AND_DROP_TYPE_NONE = 0,
		ES_DRAG_AND_DROP_TYPE_SPELL = 1,
		ES_DRAG_AND_DROP_TYPE_ITEM = 2,
	};

	ESDragAndDropType get_type();
	void set_type(ESDragAndDropType type);
	int get_item_id();
	void set_item_id(int item_id);

	ESDragAndDrop();

protected:
	static void _bind_methods();

private:
	ESDragAndDropType _type;
	int _item_id;
};

VARIANT_ENUM_CAST(ESDragAndDrop::ESDragAndDropType);

#endif
