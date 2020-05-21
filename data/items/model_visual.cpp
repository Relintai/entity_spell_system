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

#include "model_visual.h"

#include "../../singletons/ess.h"

int ModelVisual::get_layer() {
	return _layer;
}
void ModelVisual::set_layer(int layer) {
	_layer = layer;
}

//ModelVisualEntries

Ref<ModelVisualEntry> ModelVisual::get_visual_entry(const int index) const {
	ERR_FAIL_INDEX_V(index, _visual_entries.size(), Ref<ModelVisualEntry>());

	return _visual_entries.get(index);
}
void ModelVisual::set_visual_entry(const int index, const Ref<ModelVisualEntry> visual_entry) {
	ERR_FAIL_INDEX(index, _visual_entries.size());

	_visual_entries.set(index, visual_entry);
}
void ModelVisual::add_visual_entry(const Ref<ModelVisualEntry> visual_entry) {
	_visual_entries.push_back(visual_entry);
}
void ModelVisual::remove_visual_entry(const int index) {
	ERR_FAIL_INDEX(index, _visual_entries.size());

	_visual_entries.remove(index);
}

int ModelVisual::get_visual_entry_count() const {
	return _visual_entries.size();
}

Vector<Variant> ModelVisual::get_visual_entries() {
	Vector<Variant> r;
	for (int i = 0; i < _visual_entries.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_visual_entries[i].get_ref_ptr());
#else
		r.push_back(_visual_entries[i]);
#endif
	}
	return r;
}
void ModelVisual::set_visual_entries(const Vector<Variant> &visual_entries) {
	_visual_entries.clear();
	for (int i = 0; i < visual_entries.size(); i++) {
		Ref<ModelVisualEntry> visual_entry = Ref<ModelVisualEntry>(visual_entries[i]);

		_visual_entries.push_back(visual_entry);
	}
}

ModelVisual::ModelVisual() {
	_layer = 0;
}

ModelVisual::~ModelVisual() {
	_visual_entries.clear();
}

void ModelVisual::_validate_property(PropertyInfo &property) const {
	String name = property.name;

	if (name == "layer") {
		property.hint_string = ESS::get_instance()->texture_layers_get();
	}
}

void ModelVisual::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_layer"), &ModelVisual::get_layer);
	ClassDB::bind_method(D_METHOD("set_layer", "layer"), &ModelVisual::set_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "layer", PROPERTY_HINT_ENUM, ""), "set_layer", "get_layer");

	//ModelVisualEntry
	ClassDB::bind_method(D_METHOD("get_visual_entry", "index"), &ModelVisual::get_visual_entry);
	ClassDB::bind_method(D_METHOD("set_visual_entry", "index", "data"), &ModelVisual::set_visual_entry);
	ClassDB::bind_method(D_METHOD("add_visual_entry", "visual_entry"), &ModelVisual::add_visual_entry);
	ClassDB::bind_method(D_METHOD("remove_visual_entry", "index"), &ModelVisual::remove_visual_entry);

	ClassDB::bind_method(D_METHOD("get_visual_entry_count"), &ModelVisual::get_visual_entry_count);

	ClassDB::bind_method(D_METHOD("get_visual_entries"), &ModelVisual::get_visual_entries);
	ClassDB::bind_method(D_METHOD("set_visual_entries", "visual_entrys"), &ModelVisual::set_visual_entries);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "get_visual_entries", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visual_entries", "get_visual_entries");
}
