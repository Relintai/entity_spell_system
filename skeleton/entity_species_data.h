#ifndef ENTITY_SPECIES_DATA_H
#define ENTITY_SPECIES_DATA_H

#include "core/resource.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../entity_enums.h"

#include "species_model_data.h"

class Spell;
class Aura;

class EntitySpeciesData : public Resource {
	GDCLASS(EntitySpeciesData, Resource);

public:
	int get_id();
	void set_id(int value);

	EntityEnums::EntityType get_type();
	void set_type(EntityEnums::EntityType value);

	String get_text_description();
	void set_text_description(String value);

	Ref<SpeciesModelData> get_model_data();
	void set_model_data(Ref<SpeciesModelData> data);

	//Spells
	Ref<Spell> get_spell(const int index) const;
	void set_spell(const int index, const Ref<Spell> spell);
	void add_spell(const Ref<Spell> spell);
	void remove_spell(const int index);

	int get_spell_count() const;

	Vector<Variant> get_spells();
	void set_spells(const Vector<Variant> &spells);

	//Auras
	Ref<Aura> get_aura(const int index) const;
	void set_aura(const int index, const Ref<Aura> aura);
	void add_aura(const Ref<Aura> aura);
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
