#ifndef CHARACTER_SKELETON_H
#define CHARACTER_SKELETON_H

#ifdef ENTITIES_2D
#include "scene/2d/node_2d.h"
#else
#include "scene/3d/spatial.h"
#endif

#include "core/node_path.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../entity_enums.h"

#include "../data/item_visual.h"

#ifdef ENTITIES_2D
class CharacterSkeleton : public Node2D {
	GDCLASS(CharacterSkeleton, Node2D);
#else
class CharacterSkeleton : public Spatial {
	GDCLASS(CharacterSkeleton, Spatial);
#endif

public:
	virtual void add_item_visual(Ref<ItemVisual> vis);
	virtual void remove_item_visual(Ref<ItemVisual> vis);
	virtual void remove_item_visual_index(int index);
	virtual Ref<ItemVisual> get_item_visual(int index);
	virtual int get_item_visual_count();
	virtual void clear_item_visuals();

	EntityEnums::EntityGender get_gender();
	void set_gender(EntityEnums::EntityGender value);

	CharacterSkeleton();
	~CharacterSkeleton();

protected:
	static void _bind_methods();

private:
	EntityEnums::EntityGender _gender;
};


#endif
