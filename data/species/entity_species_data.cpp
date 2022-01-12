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

#include "entity_species_data.h"

#include "../spells/spell.h"

#include "../../singletons/ess.h"

#include "core/version.h"

int EntitySpeciesData::get_id() const {
	return _id;
}
void EntitySpeciesData::set_id(const int value) {
	_id = value;
}

int EntitySpeciesData::get_type() const {
	return _type;
}
void EntitySpeciesData::set_type(const int value) {
	_type = value;
}

String EntitySpeciesData::get_text_description() const {
	return _text_description;
}
void EntitySpeciesData::set_text_description(const String &value) {
	_text_description = value;
}

//ModelData

Ref<SpeciesModelData> EntitySpeciesData::get_model_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _model_datas.size(), Ref<SpeciesModelData>());

	return _model_datas.get(index);
}
void EntitySpeciesData::set_model_data(const int index, const Ref<SpeciesModelData> &model_data) {
	ERR_FAIL_INDEX(index, _model_datas.size());

	_model_datas.set(index, model_data);
}
void EntitySpeciesData::add_model_data(const Ref<SpeciesModelData> &model_data) {
	_model_datas.push_back(model_data);
}
void EntitySpeciesData::remove_model_data(const int index) {
	ERR_FAIL_INDEX(index, _model_datas.size());

	_model_datas.remove(index);
}

int EntitySpeciesData::get_model_data_count() const {
	return _model_datas.size();
}

Vector<Variant> EntitySpeciesData::get_model_datas() {
	VARIANT_ARRAY_GET(_model_datas);
}
void EntitySpeciesData::set_model_datas(const Vector<Variant> &model_datas) {
	VARIANT_ARRAY_SET(model_datas, _model_datas, SpeciesModelData);
}

//Spells

Ref<Spell> EntitySpeciesData::get_spell(const int index) const {
	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells.get(index);
}
void EntitySpeciesData::set_spell(const int index, const Ref<Spell> &spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, spell);
}
void EntitySpeciesData::add_spell(const Ref<Spell> &spell) {
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
	VARIANT_ARRAY_GET(_spells);
}
void EntitySpeciesData::set_spells(const Vector<Variant> &spells) {
	VARIANT_ARRAY_SET(spells, _spells, Spell);
}

//Auras

Ref<Spell> EntitySpeciesData::get_aura(const int index) const {
	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Spell>());

	return _auras.get(index);
}
void EntitySpeciesData::set_aura(const int index, const Ref<Spell> &aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}
void EntitySpeciesData::add_aura(const Ref<Spell> &aura) {
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
	VARIANT_ARRAY_GET(_auras);
}
void EntitySpeciesData::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Spell> aura = Ref<Spell>(auras[i]);

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
	_type = 0;
}
EntitySpeciesData::~EntitySpeciesData() {
	_model_datas.clear();

	_spells.clear();
	_auras.clear();
}

void EntitySpeciesData::_validate_property(PropertyInfo &property) const {
	if (property.name == "type") {
		property.hint_string = ESS::get_singleton()->entity_types_get();
	}
}

void EntitySpeciesData::_bind_methods() {
	BIND_VMETHOD(MethodInfo(Variant::STRING, "_generate_name", PropertyInfo(Variant::INT, "seed")));

	ClassDB::bind_method(D_METHOD("generate_name"), &EntitySpeciesData::generate_name);

	ClassDB::bind_method(D_METHOD("get_id"), &EntitySpeciesData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntitySpeciesData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_type"), &EntitySpeciesData::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &EntitySpeciesData::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, ""), "set_type", "get_type");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntitySpeciesData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntitySpeciesData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_text_description", "get_text_description");

	//ModelData
	ClassDB::bind_method(D_METHOD("get_model_data", "index"), &EntitySpeciesData::get_model_data);
	ClassDB::bind_method(D_METHOD("set_model_data", "index", "data"), &EntitySpeciesData::set_model_data);
	ClassDB::bind_method(D_METHOD("add_model_data", "model_data"), &EntitySpeciesData::add_model_data);
	ClassDB::bind_method(D_METHOD("remove_model_data", "index"), &EntitySpeciesData::remove_model_data);

	ClassDB::bind_method(D_METHOD("get_model_data_count"), &EntitySpeciesData::get_model_data_count);

	ClassDB::bind_method(D_METHOD("get_model_datas"), &EntitySpeciesData::get_model_datas);
	ClassDB::bind_method(D_METHOD("set_model_datas", "model_datas"), &EntitySpeciesData::set_model_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "model_datas", PROPERTY_HINT_NONE, "17/17:SpeciesModelData", PROPERTY_USAGE_DEFAULT, "SpeciesModelData"), "set_model_datas", "get_model_datas");

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
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_auras", "get_auras");
}
