/*
Copyright (c) 2019-2020 Péter Magyar

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

#ifndef CHARACTER_SKELETON_3D_H
#define CHARACTER_SKELETON_3D_H

#include "scene/main/node.h"

#include "core/vector.h"

#include "core/node_path.h"
#include "core/ustring.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"

#include "../entity_enums.h"
#include "skeleton_model_entry.h"

#include "../data/items/item_visual_entry.h"

#include "core/version.h"

#if VERSION_MAJOR < 4
#include "scene/3d/spatial.h"
#else
#include "scene/3d/node_3d.h"
#define Spatial Node3D
#define Texture Texture2D
#endif

class ItemVisual;

//Rename to HumanoidCharSkeleton -> maybe make that a subclass?
class CharacterSkeleton3D : public Spatial {
	GDCLASS(CharacterSkeleton3D, Spatial);

public:
	EntityEnums::EntityGender get_gender();
	void set_gender(EntityEnums::EntityGender value);

	bool get_model_dirty() const;
	void set_model_dirty(bool value);

	NodePath get_bone_path(int index);
	void set_bone_path(int index, NodePath path);

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

	Array merge_mesh_array(Array arr) const;
	Array bake_mesh_array_uv(Array arr, Ref<Texture> tex, float mul_color = 0.7) const;

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

			return (a->get_priority() > b->get_priority());
		}
	};

private:
	EntityEnums::EntityGender _gender;
	NodePath _animation_player_path;
	NodePath _animation_tree_path;

	NodePath _bone_paths[EntityEnums::SKELETON_POINTS_MAX];

	AnimationPlayer *_animation_player;
	AnimationTree *_animation_tree;

	Node *_bone_nodes[EntityEnums::SKELETON_POINTS_MAX];

	bool _model_dirty;
	Vector<Ref<ItemVisual> > _item_visuals;
	Vector<Ref<SkeletonModelEntry> > _entries[EntityEnums::SKELETON_POINTS_MAX];
};

#endif
