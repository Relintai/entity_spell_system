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

#ifndef ENTITY_SPECIES_DATA_H
#define ENTITY_SPECIES_DATA_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../../entity_enums.h"

#include "species_model_data.h"

class Spell;
class Aura;

class EntitySpeciesData : public Resource {
	GDCLASS(EntitySpeciesData, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	EntityEnums::EntityType get_type() const;
	void set_type(const EntityEnums::EntityType value);

	String get_text_description() const;
	void set_text_description(const String &value);

	Ref<SpeciesModelData> get_model_data();
	void set_model_data(const Ref<SpeciesModelData> &data);

	//Spells
	Ref<Spell> get_spell(const int index) const;
	void set_spell(const int index, const Ref<Spell> &spell);
	void add_spell(const Ref<Spell> &spell);
	void remove_spell(const int index);

	int get_spell_count() const;

	Vector<Variant> get_spells();
	void set_spells(const Vector<Variant> &spells);

	//Auras
	Ref<Aura> get_aura(const int index) const;
	void set_aura(const int index, const Ref<Aura> &aura);
	void add_aura(const Ref<Aura> &aura);
	void remove_aura(const int index);

	int get_aura_count() const;

	Vector<Variant> get_auras();
	void set_auras(const Vector<Variant> &auras);

	String generate_name(int seed);

	EntitySpeciesData();
	~EntitySpeciesData();

protected:
	static void _bind_methods();

private:
	int _id;
	EntityEnums::EntityType _type;
	String _text_description;

	Ref<SpeciesModelData> _model_data;

	Vector<Ref<Spell> > _spells;
	Vector<Ref<Aura> > _auras;
};

#endif
