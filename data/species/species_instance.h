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

#ifndef SPECIES_INSTANCE_H
#define SPECIES_INSTANCE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

#include "../items/model_visual_entry.h"

class EntitySpeciesData;

class SpeciesInstance : public Resource {
	GDCLASS(SpeciesInstance, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int get_species_id() const;
	void set_species_id(const int value);

	StringName get_species_path() const;
	void set_species_path(const StringName &value);

	Ref<EntitySpeciesData> get_species();
	void set_species(const Ref<EntitySpeciesData> &value);

	int get_skin_color_index() const;
	void set_skin_color_index(const int value);

	int get_hair_style_index() const;
	void set_hair_style_index(const int value);

	int get_hair_color_index() const;
	void set_hair_color_index(const int value);

	int get_head_index() const;
	void set_head_index(const int value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	SpeciesInstance();
	~SpeciesInstance();

protected:
	static void _bind_methods();

private:
	int _id;
	StringName _path;
	int _species_id;
	Ref<EntitySpeciesData> _species;
	int _skin_color_index;
	int _hair_style_index;
	int _hair_color_index;
	int _head_index;
};

#endif
