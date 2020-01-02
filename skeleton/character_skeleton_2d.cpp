#include "character_skeleton_2d.h"

void CharacterSkeleton2D::add_item_visual(Ref<ItemVisual> vis) {
}
void CharacterSkeleton2D::remove_item_visual(Ref<ItemVisual> vis) {
}
void CharacterSkeleton2D::remove_item_visual_index(int index) {
}
Ref<ItemVisual> CharacterSkeleton2D::get_item_visual(int index) {
	return Ref<ItemVisual>();
}
int CharacterSkeleton2D::get_item_visual_count() {
	return 0;
}
void CharacterSkeleton2D::clear_item_visuals() {
}

EntityEnums::EntityGender CharacterSkeleton2D::get_gender() {
	return _gender;
}
void CharacterSkeleton2D::set_gender(EntityEnums::EntityGender value) {
	_gender = value;
}

CharacterSkeleton2D::CharacterSkeleton2D() {
	_gender = EntityEnums::GENDER_MALE;
}

CharacterSkeleton2D::~CharacterSkeleton2D() {
}

void CharacterSkeleton2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_gender"), &CharacterSkeleton2D::get_gender);
	ClassDB::bind_method(D_METHOD("set_gender", "value"), &CharacterSkeleton2D::set_gender);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "gender", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_GENDER), "set_gender", "get_gender");

	ClassDB::bind_method(D_METHOD("add_item_visual", "vis"), &CharacterSkeleton2D::add_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual", "vis"), &CharacterSkeleton2D::remove_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual_index", "index"), &CharacterSkeleton2D::remove_item_visual_index);
	ClassDB::bind_method(D_METHOD("get_item_visual", "index"), &CharacterSkeleton2D::get_item_visual);
	ClassDB::bind_method(D_METHOD("get_item_visual_count"), &CharacterSkeleton2D::get_item_visual_count);
	ClassDB::bind_method(D_METHOD("clear_item_visuals"), &CharacterSkeleton2D::clear_item_visuals);
}
