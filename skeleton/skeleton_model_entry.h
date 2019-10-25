#ifndef SKELETON_MODEL_ENTRY_H
#define SKELETON_MODEL_ENTRY_H

#include "core/reference.h"
#include "../data/item_visual_entry.h"

class SkeletonModelEntry : public Reference {
	GDCLASS(SkeletonModelEntry, Reference);

public:
    int get_priority();
	void set_priority(int value);

	Color get_color();
	void set_color(Color value);
    
	Ref<ItemVisualEntry> get_entry();
	void set_entry(Ref<ItemVisualEntry> entry);

    SkeletonModelEntry();
    ~SkeletonModelEntry();

protected:
	static void _bind_methods();

private:
	int _priority;
	Color _color;
	Ref<ItemVisualEntry> _entry;
};

#endif
