#include "character.h"

#include "../data/spell.h"
#include "../data/aura.h"
#include "../entities/entity.h"

int CharacterClass::get_id() {
	return _id;
}

void CharacterClass::set_id(int value) {
	_id = value;
}

String CharacterClass::get_character_class_name() {
	return _character_class_name;
}

void CharacterClass::set_character_class_name(String value) {
	_character_class_name = value;
}

Ref<Texture> CharacterClass::get_icon() {
	return _icon;
}

void CharacterClass::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

EntityEnums::PlayerResourceTypes CharacterClass::get_player_resource_type() {
	return _player_resource_type;
}

void CharacterClass::set_player_resource_type(EntityEnums::PlayerResourceTypes value) {
	_player_resource_type = value;
}

Ref<StatData> CharacterClass::get_stat_data() {
	return _stat_data;
}

void CharacterClass::set_stat_data(Ref<StatData> value) {
	_stat_data = value;
}

int CharacterClass::get_num_spells() {
	return _num_spells;
}

void CharacterClass::set_num_spells(int value) {
	_num_spells = value;
}

int CharacterClass::get_current_spell_page() {
	return _current_spell_page;
}

void CharacterClass::set_current_spell_page(int value) {
	if (value < 0 || value > (int)(_num_spells / ITEMS_PER_PAGE)) {
		return;
	}

	_current_spell_page = value;
}

Ref<Spell> CharacterClass::get_spell(int id) {
	ERR_FAIL_INDEX_V(id, MAX_SPELLS, Ref<Spell>());

	return _spells[id];
}

void CharacterClass::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, MAX_SPELLS);

	_spells[index] = Ref<Spell>(spell);
}

int CharacterClass::get_num_specs() {
	return _num_specs;
}

void CharacterClass::set_num_specs(int value) {
	_num_specs = value;
}

Ref<CharacterSpec> CharacterClass::get_spec(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_SPECS, Ref<CharacterSpec>());

	return _specs[index];
}

void CharacterClass::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, MAX_SPECS);

	_specs[index] = Ref<CharacterSpec>(spec);
}

Ref<Aura> CharacterClass::get_aura(int index) {
	ERR_FAIL_INDEX_V(index, MAX_AURAS, Ref<Aura>());

	return _auras[index];
}
void CharacterClass::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, MAX_AURAS);

	_auras[index] = aura;
}

/*
Vector<int> CharacterClass::get_mob_party_ids() {
	return _mob_party_ids;
}

void CharacterClass::set_mob_party_ids(Vector<int> ids) {
	//specs;
}

Vector<int> CharacterClass::get_mob_dislike_ids() {
	return _mob_dislike_ids;
}

void CharacterClass::set_mob_dislike_ids(Vector<int> ids) {
	//specs;
}
*/
/*
int CharacterClass::get_inspector_max_spells() {
	return _inspector_max_spells;
}

void CharacterClass::set_inspector_max_spells(int value) {
	_inspector_max_spells = value;
}*/

void CharacterClass::start_casting(int spell_id, Entity *caster, float spellScale) {
	for (int i = 0; i < MAX_SPELLS; i++) {
		Ref<Spell> s = _spells[i];

		if (s == NULL) {
			print_error("class doesn't have spell! spell_id: " + itos(spell_id));
			return;
		}

		if (s->get_spell_id() == spell_id) {
			s->sstart_casting_simple(caster, spellScale);
			return;
		}
	}
}

void CharacterClass::casting_finished(Entity *caster, float spellScale) {
}

void CharacterClass::casting_failed(Entity *caster) {
}

void CharacterClass::spell_hit(Entity *caster, Entity *target, Node *worldSpell, Spell *spell, float spellScale) {
}

void CharacterClass::on_player_move(Entity *caster) {
}

void CharacterClass::c_on_spell_cast_started(Entity *caster) {
}

void CharacterClass::c_on_spell_cast_success(Entity *caster) {
}

void CharacterClass::c_on_spell_cast_failed(Entity *caster) {
}

void CharacterClass::c_on_spell_cast_ended(Entity *caster) {
}

void CharacterClass::on_cast_state_changed(Entity *caster) {
}

String CharacterClass::get_name() {

	return "stubname";
}

String CharacterClass::get_description(int level) {

	return "stubdesc";
}

void CharacterClass::_validate_property(PropertyInfo &property) const {

	String prop = property.name;
	if (prop.begins_with("Spell_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _num_spells || frame < ITEMS_PER_PAGE * _current_spell_page || frame > ITEMS_PER_PAGE * (_current_spell_page + 1)) {
			property.usage = 0;
		}
	} else if (prop.begins_with("Spec_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _num_specs) {
			property.usage = 0;
		}
	} else if (prop.begins_with("current_spell_page")) {
		if (_num_spells <= ITEMS_PER_PAGE) {
			property.usage = 0;
		}
	}
}

void CharacterClass::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &CharacterClass::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CharacterClass::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_character_class_name"), &CharacterClass::get_character_class_name);
	ClassDB::bind_method(D_METHOD("set_character_class_name", "value"), &CharacterClass::set_character_class_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "character_class_name"), "set_character_class_name", "get_character_class_name");

	ClassDB::bind_method(D_METHOD("get_icon"), &CharacterClass::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &CharacterClass::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &CharacterClass::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &CharacterClass::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_player_resource_type"), &CharacterClass::get_player_resource_type);
	ClassDB::bind_method(D_METHOD("set_player_resource_type", "value"), &CharacterClass::set_player_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "player_resource_type", PROPERTY_HINT_ENUM, "None, Rage, Mana, Energy, Time Anomaly"), "set_player_resource_type", "get_player_resource_type");

	////    Specs    ////
	ClassDB::bind_method(D_METHOD("get_num_specs"), &CharacterClass::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &CharacterClass::set_num_specs);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_specs", PROPERTY_HINT_RANGE, "0," + itos(MAX_SPECS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_num_specs", "get_num_specs");

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &CharacterClass::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &CharacterClass::set_spec);

	for (int i = 0; i < MAX_SPECS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Spec_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "CharacterSpec", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_spec", "get_spec", i);
	}

	////    AURAS    ////
	
	ClassDB::bind_method(D_METHOD("get_aura", "index"), &CharacterClass::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &CharacterClass::set_aura);

	ADD_GROUP("Auras", "Aura");
	for (int i = 0; i < MAX_AURAS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Aura_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Aura", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_aura", "get_aura", i);
	}

	////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &CharacterClass::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &CharacterClass::set_num_spells);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_spells", PROPERTY_HINT_RANGE, "0," + itos(MAX_SPELLS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_num_spells", "get_num_spells");

	ClassDB::bind_method(D_METHOD("get_current_spell_page"), &CharacterClass::get_current_spell_page);
	ClassDB::bind_method(D_METHOD("set_current_spell_page", "value"), &CharacterClass::set_current_spell_page);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_spell_page", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_current_spell_page", "get_current_spell_page");

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &CharacterClass::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &CharacterClass::set_spell);

	for (int i = 0; i < MAX_SPELLS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Spell_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Spell", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_spell", "get_spell", i);
	}

	BIND_CONSTANT(MAX_SPELLS);
	BIND_CONSTANT(MAX_SPECS);
	BIND_CONSTANT(MAX_AURAS);
}

CharacterClass::CharacterClass() {
	//_spells = memnew(Vector<Ref<Spell> >());
	_id = 0;

	_num_specs = 0;
	_num_spells = 0;
	_current_spell_page = 0;
}

CharacterClass::~CharacterClass() {
	//memdelete(_spells);

	//for (int i = 0; i < MAX_SPELLS; ++i) {
		//_spells[i] = Ref<Spell>(NULL);
	//}
}
