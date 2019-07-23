#ifndef ENTITY_EQUIPSET_H
#define ENTITY_EQUIPSET_H

#include "core/resource.h"
#include "core/ustring.h"

#include "../data/character_skeleton_visual_entry.h"

class EntityEquipSet : public Resource {
	GDCLASS(EntityEquipSet, Resource);

public:
    int get_entry_count() const;
    void set_entry_count(const int value);
    
    Ref<CharacterSkeletonVisualEntry> get_entry(const int index) const;
    void set_entry(const int index, const Ref<CharacterSkeletonVisualEntry> entry);
    
    EntityEquipSet();
    
protected:
	static void _bind_methods();
    void _validate_property(PropertyInfo &property) const;

	enum {
		MAX_ENTRIES = 20
	};

private:
    int _entry_count;
	Ref<CharacterSkeletonVisualEntry> _entries[MAX_ENTRIES];
};

#endif
