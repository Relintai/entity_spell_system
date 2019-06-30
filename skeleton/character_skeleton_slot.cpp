#include "character_skeleton_slot.h"


void CharacterSkeletonSlot::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_bone_path", "index"), &CharacterSkeleton::get_bone_path);
	ClassDB::bind_method(D_METHOD("set_bone_path", "index", "path"), &CharacterSkeleton::set_bone_path);

    ADD_GROUP("Bone Paths", "bone_path_");
	ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_hip"), "set_bone_path", "get_bone_path", EntityEnums::SKELETON_POINT_HIP);


	ClassDB::bind_method(D_METHOD("get_bone_node", "bone_idx"), &CharacterSkeleton::get_bone_node);

	ClassDB::bind_method(D_METHOD("get_animation_player_path"), &CharacterSkeleton::get_animation_player_path);
	ClassDB::bind_method(D_METHOD("set_animation_player_path", "path"), &CharacterSkeleton::set_animation_player_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_player_path"), "set_animation_player_path", "get_animation_player_path");

	ClassDB::bind_method(D_METHOD("get_animation_tree_path"), &CharacterSkeleton::get_animation_tree_path);
	ClassDB::bind_method(D_METHOD("set_animation_tree_path", "path"), &CharacterSkeleton::set_animation_tree_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_tree_path"), "set_animation_tree_path", "get_animation_tree_path");

	ClassDB::bind_method(D_METHOD("get_animation_player"), &CharacterSkeleton::get_animation_player);
	ClassDB::bind_method(D_METHOD("get_animation_tree"), &CharacterSkeleton::get_animation_tree);

	ClassDB::bind_method(D_METHOD("update_nodes"), &CharacterSkeleton::update_nodes);
}
