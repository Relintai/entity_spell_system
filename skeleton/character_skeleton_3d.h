#ifndef CHARACTER_SKELETON_3D_H
#define CHARACTER_SKELETON_3D_H

#include "character_skeleton.h"

#include "core/vector.h"

#include "core/node_path.h"
#include "core/ustring.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"

#include "../data/character_skeleton_visual_entry.h"
#include "../entity_enums.h"
#include "skeleton_model_entry.h"

#include "../data/item_visual_entry.h"

class ItemVisual;

//Rename to HumanoidCharSkeleton
class CharacterSkeleton3D : public CharacterSkeleton {
	GDCLASS(CharacterSkeleton3D, CharacterSkeleton);

public:
	bool get_model_dirty() const;
	void set_model_dirty(bool value);

	NodePath get_bone_path(int index);
	void set_bone_path(int index, NodePath path);

	Ref<CharacterSkeletonVisualEntry> get_visual(int index);
	void set_visual(int index, Ref<CharacterSkeletonVisualEntry> entry);

	Node *get_bone_node(EntityEnums::CharacterSkeletonPoints node_id);

	NodePath get_animation_player_path();
	void set_animation_player_path(NodePath path);

	AnimationPlayer *get_animation_player();

	NodePath get_animation_tree_path();
	void set_animation_tree_path(NodePath path);

	AnimationTree *get_animation_tree();

	void update_nodes();

	void add_item_visual(Ref<ItemVisual> vis);
	void remove_item_visual(Ref<ItemVisual> vis);
	void remove_item_visual_index(int index);
	Ref<ItemVisual> get_item_visual(int index);
	int get_item_visual_count();
	void clear_item_visuals();

	void add_item_visual_entry(Ref<ItemVisual> vis, Ref<ItemVisualEntry> ive, int target_bone);
	void remove_item_visual_entry(Ref<ItemVisual> vis, Ref<ItemVisualEntry> ive, int target_bone);

	Ref<SkeletonModelEntry> get_model_entry(const int bone_index, const int index);
	int get_model_entry_count(const int bone_index);

	void sort_layers();

	void build_model();
	void _build_model();

	CharacterSkeleton3D();
	~CharacterSkeleton3D();

protected:
	static void _bind_methods();
	virtual void _notification(int p_notification);

protected:
	struct _ModelEntryComparator {
		_FORCE_INLINE_ bool operator()(const Ref<SkeletonModelEntry> &a, const Ref<SkeletonModelEntry> &b) const {
			if (!a.is_valid() || !b.is_valid()) {
				return false;
			}

			return (a->get_priority() < b->get_priority());
		}
	};

private:
	NodePath _animation_player_path;
	NodePath _animation_tree_path;

    NodePath _bone_paths[EntityEnums::SKELETON_POINTS_MAX];
    
	AnimationPlayer *_animation_player;
	AnimationTree *_animation_tree;

	Node *_bone_nodes[EntityEnums::SKELETON_POINTS_MAX];

	Ref<CharacterSkeletonVisualEntry> _visuals[EntityEnums::SKELETON_POINTS_MAX];

	bool _model_dirty;
	Vector<Ref<ItemVisual> > _item_visuals;
	Vector<Ref<SkeletonModelEntry> > _entries[EntityEnums::SKELETON_POINTS_MAX];
};


#endif
