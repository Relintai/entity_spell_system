#ifndef CHARACTER_SKELETON_2D_H
#define CHARACTER_SKELETON_2D_H

#include "scene/2d/node_2d.h"

#include "core/node_path.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../entity_enums.h"

#include "../data/item_visual.h"

class CharacterSkeleton2D : public Node2D {
	GDCLASS(CharacterSkeleton2D, Node2D);

public:
	virtual void add_item_visual(Ref<ItemVisual> vis);
	virtual void remove_item_visual(Ref<ItemVisual> vis);
	virtual void remove_item_visual_index(int index);
	virtual Ref<ItemVisual> get_item_visual(int index);
	virtual int get_item_visual_count();
	virtual void clear_item_visuals();

	EntityEnums::EntityGender get_gender();
	void set_gender(EntityEnums::EntityGender value);

	CharacterSkeleton2D();
	~CharacterSkeleton2D();

protected:
	static void _bind_methods();

private:
	EntityEnums::EntityGender _gender;
};

#endif
