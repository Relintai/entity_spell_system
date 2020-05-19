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

#ifndef CHARACTER_SKELETON_2D_H
#define CHARACTER_SKELETON_2D_H

#include "scene/2d/node_2d.h"

#include "core/node_path.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../entity_enums.h"

#include "../data/items/model_visual.h"

class CharacterSkeleton2D : public Node2D {
	GDCLASS(CharacterSkeleton2D, Node2D);

public:
	virtual void add_model_visual(Ref<ModelVisual> vis);
	virtual void remove_model_visual(Ref<ModelVisual> vis);
	virtual void remove_model_visual_index(int index);
	virtual Ref<ModelVisual> get_model_visual(int index);
	virtual int get_model_visual_count();
	virtual void clear_model_visuals();

	EntityEnums::EntityGender get_gender();
	void set_gender(EntityEnums::EntityGender value);

	CharacterSkeleton2D();
	~CharacterSkeleton2D();

protected:
	static void _bind_methods();

private:
	EntityEnums::EntityGender _gender;
};

#endif
