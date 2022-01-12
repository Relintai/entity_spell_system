/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#include "core/string/node_path.h"
#else
#include "core/vector.h"
#include "core/ustring.h"
#include "core/node_path.h"
#endif

#include "scene/main/node.h"

#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"

#include "../entity_enums.h"
#include "skeleton_model_entry.h"

#include "../data/items/model_visual_entry.h"

#include "../defines.h"

#include spatial_h_path

#if GODOT4
#define Texture Texture2D
#endif

class ModelVisual;

//Rename to HumanoidCharSkeleton -> maybe make that a subclass?
class CharacterSkeleton3D : public Spatial {
	GDCLASS(CharacterSkeleton3D, Spatial);

public:
	int get_entity_type() const;
	void set_entity_type(const int value);

	int get_model_index();
	void set_model_index(int value);

	bool get_model_dirty() const;
	void set_model_dirty(bool value);

	NodePath attach_point_path_get(const int index) const;
	void attach_point_path_set(const int index, const NodePath &path);

	Node *attach_point_node_get(const int index);

	int attach_point_count() const;

	Node *common_attach_point_node_get(const EntityEnums::CommonCharacterSkeletonPoints point);
	void common_attach_point_add(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene);
	void common_attach_point_add_timed(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene, const float time);
	void common_attach_point_remove(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene);
	int common_attach_point_index_get(const EntityEnums::CommonCharacterSkeletonPoints point);
	virtual int _common_attach_point_index_get(const EntityEnums::CommonCharacterSkeletonPoints point);

	NodePath get_animation_player_path();
	void set_animation_player_path(NodePath path);

	AnimationPlayer *get_animation_player();

	NodePath get_animation_tree_path();
	void set_animation_tree_path(NodePath path);

	AnimationTree *get_animation_tree();

	void update_nodes();

	int bone_additional_mesh_transform_bone_index_get(const int index) const;
	void bone_additional_mesh_transform_bone_index_set(const int index, const int bone_index);

	Transform bone_additional_mesh_transform_transform_get(const int index) const;
	void bone_additional_mesh_transform_transform_set(const int index, const Transform &transform);

	Transform bone_additional_mesh_transform_user_transform_get(const int index) const;
	void bone_additional_mesh_transform_user_transform_set(const int index, const Transform &transform);

	void bone_additional_mesh_transform_set_count(const int size);
	int bone_additional_mesh_transform_get_count() const;

	void add_model_visual(Ref<ModelVisual> vis);
	void remove_model_visual(Ref<ModelVisual> vis);
	void remove_model_visual_index(int index);
	Ref<ModelVisual> get_model_visual(int index);
	int get_model_visual_count();
	void clear_model_visuals();

	void add_model_visual_entry(Ref<ModelVisual> vis, Ref<ModelVisualEntry> ive);
	void remove_model_visual_entry(Ref<ModelVisual> vis, Ref<ModelVisualEntry> ive);

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
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	void _validate_property(PropertyInfo &property) const;
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

	struct AttachPointNode {
		NodePath path;
		Node *node;

		AttachPointNode() {
			node = NULL;
		}
	};

	struct BoneModelAdditionalMeshTransforms {
		int bone_index;
		Transform transform;
		Transform user_transform;

		BoneModelAdditionalMeshTransforms() {
			bone_index = 0;
		}
	};

private:
	int _entity_type;
	int _model_index;
	NodePath _animation_player_path;
	NodePath _animation_tree_path;

	AnimationPlayer *_animation_player;
	AnimationTree *_animation_tree;

	Vector<AttachPointNode> _attach_point_nodes;

	Vector<BoneModelAdditionalMeshTransforms> _bone_model_additional_mesh_transforms;

	bool _model_dirty;
	Vector<Ref<ModelVisual> > _model_visuals;
	Vector<Vector<Ref<SkeletonModelEntry> > > _entries;
};

#endif
