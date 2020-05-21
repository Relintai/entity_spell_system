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

#ifndef SPECIES_MODEL_DATA_H
#define SPECIES_MODEL_DATA_H

#include "core/resource.h"

#include "core/color.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "scene/resources/packed_scene.h"

#include "../items/model_visual_entry.h"

#include "../../entity_enums.h"

class ModelVisual;

class SpeciesModelData : public Resource {
	GDCLASS(SpeciesModelData, Resource);

public:
	int get_id();
	void set_id(int value);

	Ref<PackedScene> get_body();
	void set_body(Ref<PackedScene> value);

	//Entries
	Ref<ModelVisualEntry> get_visual(const int bone_index, const int index) const;
	void set_visual(const int bone_index, const int index, const Ref<ModelVisualEntry> visual);
	void add_visual(const int bone_index, const Ref<ModelVisualEntry> visual);
	void remove_visual(const int bone_index, const int index);

	int get_visual_count(const int bone_index) const;

	Vector<Variant> get_visuals(const int bone_index);
	void set_visuals(const int bone_index, const Vector<Variant> &visuals);

	//Layer Colors
	Color get_layer_color(const int index) const;
	void set_layer_color(const int index, const Color &layer_color);
	void add_layer_color(const Color &layer_color);
	void remove_layer_color(const int index);

	int get_layer_color_count() const;

	Vector<Variant> get_layer_colors();
	void set_layer_colors(const Vector<Variant> &layer_colors);

	//SkinColors
	Color get_skin_color(const int index) const;
	void set_skin_color(const int index, const Color skin_color);
	void add_skin_color(const Color skin_color);
	void remove_skin_color(const int index);

	int get_skin_color_count() const;

	Vector<Variant> get_skin_colors();
	void set_skin_colors(const Vector<Variant> &skin_colors);

	//HairStyles
	Ref<ModelVisualEntry> get_hair_style(const int index) const;
	void set_hair_style(const int index, const Ref<ModelVisualEntry> hair_style);
	void add_hair_style(const Ref<ModelVisualEntry> hair_style);
	void remove_hair_style(const int index);

	int get_hair_style_count() const;

	Vector<Variant> get_hair_styles();
	void set_hair_styles(const Vector<Variant> &hair_styles);

	//HairColors
	Color get_hair_color(const int index) const;
	void set_hair_color(const int index, const Color hair_color);
	void add_hair_color(const Color hair_color);
	void remove_hair_color(const int index);

	int get_hair_color_count() const;

	Vector<Variant> get_hair_colors();
	void set_hair_colors(const Vector<Variant> &hair_colors);

	//Heads
	Ref<ModelVisualEntry> get_head(const int index) const;
	void set_head(const int index, const Ref<ModelVisualEntry> head);
	void add_head(const Ref<ModelVisualEntry> head);
	void remove_head(const int index);

	int get_head_count() const;

	Vector<Variant> get_heads();
	void set_heads(const Vector<Variant> &heads);

	SpeciesModelData();
	~SpeciesModelData();

protected:
	static void _bind_methods();

private:
	int _id;

	Ref<PackedScene> _body;

	Vector<Ref<ModelVisualEntry> > _visuals[EntityEnums::SKELETON_POINTS_MAX];
	Vector<Color> _layer_colors;

	Vector<Color> _skin_colors;
	Vector<Ref<ModelVisualEntry> > _hair_styles;
	Vector<Color> _hair_colors;
	Vector<Ref<ModelVisualEntry> > _heads;
};

#endif
