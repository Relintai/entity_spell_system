#include "character_skeleton.h"

void CharacterSkeleton::add_item_visual(Ref<ItemVisual> vis) {
}
void CharacterSkeleton::remove_item_visual(Ref<ItemVisual> vis) {
}
void CharacterSkeleton::remove_item_visual_index(int index) {
}
Ref<ItemVisual> CharacterSkeleton::get_item_visual(int index) {
	return Ref<ItemVisual>();
}
int CharacterSkeleton::get_item_visual_count() {
	return 0;
}
void CharacterSkeleton::clear_item_visuals() {
}

CharacterSkeleton::CharacterSkeleton() {
}

CharacterSkeleton::~CharacterSkeleton() {
}

void CharacterSkeleton::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_item_visual", "vis"), &CharacterSkeleton::add_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual", "vis"), &CharacterSkeleton::remove_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual_index", "index"), &CharacterSkeleton::remove_item_visual_index);
	ClassDB::bind_method(D_METHOD("get_item_visual", "index"), &CharacterSkeleton::get_item_visual);
	ClassDB::bind_method(D_METHOD("get_item_visual_count"), &CharacterSkeleton::get_item_visual_count);
	ClassDB::bind_method(D_METHOD("clear_item_visuals"), &CharacterSkeleton::clear_item_visuals);
}
