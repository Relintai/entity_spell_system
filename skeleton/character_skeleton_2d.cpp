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

#include "character_skeleton_2d.h"

void CharacterSkeleton2D::add_model_visual(Ref<ModelVisual> vis) {
}
void CharacterSkeleton2D::remove_model_visual(Ref<ModelVisual> vis) {
}
void CharacterSkeleton2D::remove_model_visual_index(int index) {
}
Ref<ModelVisual> CharacterSkeleton2D::get_model_visual(int index) {
	return Ref<ModelVisual>();
}
int CharacterSkeleton2D::get_model_visual_count() {
	return 0;
}
void CharacterSkeleton2D::clear_model_visuals() {
}

int CharacterSkeleton2D::get_model_index() {
	return _model_index;
}
void CharacterSkeleton2D::set_model_index(int value) {
	_model_index = value;
}

CharacterSkeleton2D::CharacterSkeleton2D() {
	_model_index = 0;
}

CharacterSkeleton2D::~CharacterSkeleton2D() {
}

void CharacterSkeleton2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_model_index"), &CharacterSkeleton2D::get_model_index);
	ClassDB::bind_method(D_METHOD("set_model_index", "value"), &CharacterSkeleton2D::set_model_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "model_index"), "set_model_index", "get_model_index");

	ClassDB::bind_method(D_METHOD("add_model_visual", "vis"), &CharacterSkeleton2D::add_model_visual);
	ClassDB::bind_method(D_METHOD("remove_model_visual", "vis"), &CharacterSkeleton2D::remove_model_visual);
	ClassDB::bind_method(D_METHOD("remove_model_visual_index", "index"), &CharacterSkeleton2D::remove_model_visual_index);
	ClassDB::bind_method(D_METHOD("get_model_visual", "index"), &CharacterSkeleton2D::get_model_visual);
	ClassDB::bind_method(D_METHOD("get_model_visual_count"), &CharacterSkeleton2D::get_model_visual_count);
	ClassDB::bind_method(D_METHOD("clear_model_visuals"), &CharacterSkeleton2D::clear_model_visuals);
}
