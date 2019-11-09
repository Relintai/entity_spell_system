#include "entity_species_data.h"

#include "../data/spell.h"
#include "../data/aura.h"

int EntitySpeciesData::get_id() {
	return _id;
}
void EntitySpeciesData::set_id(int value) {
	_id = value;
}

EntityEnums::EntityType EntitySpeciesData::get_type() {
	return _type;
}
void EntitySpeciesData::set_type(EntityEnums::EntityType value) {
	_type = value;
}

String EntitySpeciesData::get_text_description() {
	return _text_description;
}
void EntitySpeciesData::set_text_description(String value) {
	_text_description = value;
}

Ref<SpeciesModelData> EntitySpeciesData::get_model_data() {
	return _model_data;
}
void EntitySpeciesData::set_model_data(Ref<SpeciesModelData> data) {
	_model_data = data;
}

//Spells

Ref<Spell> EntitySpeciesData::get_spell(const int index) const {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells.get(index);
}
void EntitySpeciesData::set_spell(const int index, const Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, spell);
}
void EntitySpeciesData::add_spell(const Ref<Spell> spell) {
	_spells.push_back(spell);
}
void EntitySpeciesData::remove_spell(const int index) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.remove(index);
}

int EntitySpeciesData::get_spell_count() const {
	return _spells.size();
}

Vector<Variant> EntitySpeciesData::get_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _spells.size(); i++) {
		r.push_back(_spells[i].get_ref_ptr());
	}
	return r;
}
void EntitySpeciesData::set_spells(const Vector<Variant> &spells) {
	_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_spells.push_back(spell);
	}
}

//Auras

Ref<Aura> EntitySpeciesData::get_aura(const int index) const {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras.get(index);
}
void EntitySpeciesData::set_aura(const int index, const Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}
void EntitySpeciesData::add_aura(const Ref<Aura> aura) {
	_auras.push_back(aura);
}
void EntitySpeciesData::remove_aura(const int index) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.remove(index);
}

int EntitySpeciesData::get_aura_count() const {
	return _auras.size();
}

Vector<Variant> EntitySpeciesData::get_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
		r.push_back(_auras[i].get_ref_ptr());
	}
	return r;
}
void EntitySpeciesData::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(auras[i]);

		_auras.push_back(aura);
	}
}

String EntitySpeciesData::generate_name(int seed) {
	if (has_method("_generate_name")) {
		return call("_generate_name", seed);
	}

	return "";
}

EntitySpeciesData::EntitySpeciesData() {
	_id = 0;
	_type = EntityEnums::ENITIY_TYPE_NONE;
}
EntitySpeciesData::~EntitySpeciesData() {
	_model_data.unref();

	_spells.clear();
	_auras.clear();
}

void EntitySpeciesData::_bind_methods() {
	BIND_VMETHOD(MethodInfo(Variant::STRING, "_generate_name", PropertyInfo(Variant::INT, "seed")));

	ClassDB::bind_method(D_METHOD("generate_name"), &EntitySpeciesData::generate_name);

	ClassDB::bind_method(D_METHOD("get_id"), &EntitySpeciesData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntitySpeciesData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_type"), &EntitySpeciesData::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &EntitySpeciesData::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_TYPES), "set_type", "get_type");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntitySpeciesData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntitySpeciesData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_model_data"), &EntitySpeciesData::get_model_data);
	ClassDB::bind_method(D_METHOD("set_model_data", "value"), &EntitySpeciesData::set_model_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "model_data", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesModelData"), "set_model_data", "get_model_data");

	//Spells
	ClassDB::bind_method(D_METHOD("get_spell", "index"), &EntitySpeciesData::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "data"), &EntitySpeciesData::set_spell);
	ClassDB::bind_method(D_METHOD("add_spell", "spell"), &EntitySpeciesData::add_spell);
	ClassDB::bind_method(D_METHOD("remove_spell", "index"), &EntitySpeciesData::remove_spell);

	ClassDB::bind_method(D_METHOD("get_spell_count"), &EntitySpeciesData::get_spell_count);

	ClassDB::bind_method(D_METHOD("get_spells"), &EntitySpeciesData::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &EntitySpeciesData::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	//Auras
	ClassDB::bind_method(D_METHOD("get_aura", "index"), &EntitySpeciesData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "data"), &EntitySpeciesData::set_aura);
	ClassDB::bind_method(D_METHOD("add_aura", "aura"), &EntitySpeciesData::add_aura);
	ClassDB::bind_method(D_METHOD("remove_aura", "index"), &EntitySpeciesData::remove_aura);

	ClassDB::bind_method(D_METHOD("get_aura_count"), &EntitySpeciesData::get_aura_count);

	ClassDB::bind_method(D_METHOD("get_auras"), &EntitySpeciesData::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &EntitySpeciesData::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");
 }
