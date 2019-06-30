#ifndef CHARACTER_SKELETON_H
#define CHARACTER_SKELETON_H

#ifdef ENTITIES_2D
#include "scene/2d/node_2d.h"
#else
#include "scene/3d/spatial.h"
#endif

#include "core/node_path.h"
#include "core/ustring.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"

#include "../data/character_skeleton_visual_entry.h"
#include "../entity_enums.h"

class CharacterSkeletonSlot : public Reference {
	GDCLASS(CharacterSkeletonSlot, Reference);

public:

	CharacterSkeleton();

protected:
	static void _bind_methods();

private:
	Ref<CharacterSkeletonVisualEntry> _attachments[EntityEnums::SKELETON_POINTS_MAX];
};


#endif
