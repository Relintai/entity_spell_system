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

#ifdef ENTITIES_2D

class CharacterSkeleton : public Node2D {
	GDCLASS(CharacterSkeleton, Node2D);

#else

class CharacterSkeleton : public Spatial {
	GDCLASS(CharacterSkeleton, Spatial);

#endif

public:
	static const String BINDING_STRING_CHARCATER_SKELETON_BONE_ID;

	enum CharacterSkeletonBoneId {
		BONE_ID_HIP = 0,
		BONE_ID_LEFT_HAND = 1,
		BONE_ID_RIGHT_HAND = 2,
		MAX_BONE_ID = 3,
	};

	NodePath get_hip_path();
	void set_hip_path(NodePath path);

	NodePath get_left_hand_path();
	void set_left_hand_path(NodePath path);

	NodePath get_right_hand_path();
	void set_right_hand_path(NodePath path);

	Node *get_bone_node(CharacterSkeletonBoneId node_id);

	NodePath get_animation_player_path();
	void set_animation_player_path(NodePath path);

	AnimationPlayer *get_animation_player();

	NodePath get_animation_tree_path();
	void set_animation_tree_path(NodePath path);

	AnimationTree *get_animation_tree();

	void update_nodes();

	CharacterSkeleton();

protected:
	static void _bind_methods();
	virtual void _notification(int p_notification);

private:
	NodePath _hip_path;
	NodePath _left_hand_path;
	NodePath _right_hand_path;

	NodePath _animation_player_path;
	NodePath _animation_tree_path;

	AnimationPlayer *_animation_player;
	AnimationTree *_animation_tree;

	Node *_nodes[MAX_BONE_ID];
};

VARIANT_ENUM_CAST(CharacterSkeleton::CharacterSkeletonBoneId);

#endif
