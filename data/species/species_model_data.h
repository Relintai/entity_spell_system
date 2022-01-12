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

#ifndef SPECIES_MODEL_DATA_H
#define SPECIES_MODEL_DATA_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#include "core/math/color.h"
#else
#include "core/resource.h"
#include "core/vector.h"
#include "core/ustring.h"
#include "core/color.h"
#endif

#include "scene/resources/packed_scene.h"

#include "../items/model_visual_entry.h"

#include "../../entity_enums.h"

class ModelVisual;

class SpeciesModelData : public Resource {
	GDCLASS(SpeciesModelData, Resource);

public:
	int get_id();
	void set_id(int value);

	int get_bone_structure() const;
	void set_bone_structure(const int value);

	Ref<PackedScene> get_body();
	void set_body(Ref<PackedScene> value);

	//Entries
	Ref<ModelVisualEntry> get_visual(const int index) const;
	void set_visual(const int index, const Ref<ModelVisualEntry> visual);
	void add_visual(const Ref<ModelVisualEntry> &visual);
	void remove_visual(const int index);

	int get_visual_count() const;

	Vector<Variant> get_visuals();
	void set_visuals(const Vector<Variant> &visuals);

	//Customizable Slots
	String get_customizable_slots_string() const;
	void set_customizable_slots_string(const String &value);

	Ref<ModelVisualEntry> get_customizable_slot_entry(const int slot_index, const int index) const;
	void set_customizable_slot_entry(const int slot_index, const int index, const Ref<ModelVisualEntry> customizable_slot);
	void add_customizable_slot_entry(const int slot_index, const Ref<ModelVisualEntry> customizable_slot);
	void remove_customizable_slot_entry(const int slot_index, const int index);

	int get_customizable_slot_count() const;
	int get_customizable_slot_entry_count(const int slot_index) const;

	Vector<Variant> get_customizable_slot_entries(const int slot_index) const;
	void set_customizable_slot_entries(const int slot_index, const Vector<Variant> &customizable_slots);

	//Color Customizable Slots
	String get_customizable_color_slots_string() const;
	void set_customizable_color_slots_string(const String &value);

	Color get_color_customizable_slot_color(const int slot_index, const int index) const;
	void set_color_customizable_slot_color(const int slot_index, const int index, const Color color_customizable_slot);
	void add_color_customizable_slot_color(const int slot_index, const Color color_customizable_slot);
	void remove_color_customizable_slot_color(const int slot_index, const int index);

	Vector<Color> get_color_customizable_slot_colors(const int slot_index) const;
	void set_color_customizable_slot_colors(const int slot_index, const Vector<Color> &colors);

	uint64_t get_color_customizable_slot_bone_slot_mask(const int slot_index) const;
	void set_color_customizable_slot_bone_slot_mask(const int slot_index, const uint64_t value);

	int get_color_customizable_slot_texture_layer(const int slot_index) const;
	void set_color_customizable_slot_texture_layer(const int slot_index, const int value);

	int get_color_customizable_count() const;
	int get_color_customizable_slot_count(const int slot_index) const;

	SpeciesModelData();
	~SpeciesModelData();

protected:
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	void _validate_property(PropertyInfo &property) const;

	static void _bind_methods();

protected:
	struct ColorSlotData {
		int texture_layer;
		uint64_t bone_slot_mask;
		Vector<Color> colors;
	};

private:
	int _id;
	int _bone_structure;

	Ref<PackedScene> _body;

	String _customizable_slots_string;
	String _customizable_color_slots_string;

	Vector<Ref<ModelVisualEntry> > _visuals;

	Vector<Vector<Ref<ModelVisualEntry> > > _customizable_slots;
	Vector<ColorSlotData> _customizable_color_slots;
};

#endif
