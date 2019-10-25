#ifndef SPECIES_MODEL_DATA_H
#define SPECIES_MODEL_DATA_H

#include "core/resource.h"

#include "core/vector.h"
#include "core/ustring.h"
#include "core/color.h"
#include "scene/resources/packed_scene.h"

#include "../data/item_visual_entry.h"

#include "../entity_enums.h"

class ItemVisual;

class SpeciesModelData : public Resource {
	GDCLASS(SpeciesModelData, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_name();
	void set_name(String value);

	SpeciesModelData();
	~SpeciesModelData();

protected:
	static void _bind_methods();

private:
	int _id;

	String _name;

	Vector<Ref<ItemVisualEntry> > _entries[EntityEnums::SKELETON_POINTS_MAX];
	Vector<Color> _skin_colors;
	Vector<Ref<ItemVisualEntry> > _hair_styles;
	Vector<Color> _hair_colors;
	Vector<Ref<ItemVisualEntry> > _heads;
	Ref<PackedScene> _skeleton;
};


#endif
