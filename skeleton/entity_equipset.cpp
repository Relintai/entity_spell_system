#include "entity_equipset.h"

int EntityEquipSet::get_entry_count() const {
    return _entry_count;
}

void EntityEquipSet::set_entry_count(const int value) {
    if (value > MAX_ENTRIES) {
        _entry_count = MAX_ENTRIES;
        return;
    }
    
    if (value < 0) {
        _entry_count = 0;
        return;
    }
    
    _entry_count = value;
}
    

Ref<CharacterSkeletonVisualEntry> EntityEquipSet::get_entry(const int index) const {
    ERR_FAIL_INDEX_V(index, MAX_ENTRIES, Ref<CharacterSkeletonVisualEntry>());
    
    return _entries[index];
}

void EntityEquipSet::set_entry(const int index, const Ref<CharacterSkeletonVisualEntry> entry) {
    ERR_FAIL_INDEX(index, MAX_ENTRIES);
    
    _entries[index] = entry;
}

EntityEquipSet::EntityEquipSet() {
    _entry_count = 0;
}

void EntityEquipSet::_validate_property(PropertyInfo &property) const {

	String prop = property.name;
	if (prop.begins_with("Entry_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _entry_count) {
			property.usage = 0;
		}
	}
}

void EntityEquipSet::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_entry_count"), &EntityEquipSet::get_entry_count);
    ClassDB::bind_method(D_METHOD("set_entry_count", "value"), &EntityEquipSet::set_entry_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entry_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_ENTRIES), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_entry_count", "get_entry_count");

    ClassDB::bind_method(D_METHOD("get_entry", "index"), &EntityEquipSet::get_entry);
    ClassDB::bind_method(D_METHOD("set_entry", "index", "entry"), &EntityEquipSet::set_entry);

    ADD_GROUP("Entries", "Entry");
	for (int i = 0; i < MAX_ENTRIES; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Entry_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_entry", "get_entry", i);
	}
    
    BIND_CONSTANT(MAX_ENTRIES);
}



