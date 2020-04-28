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

#include "entity_class_data.h"

#include "../../data/auras/aura.h"
#include "../../data/items/item_instance.h"
#include "../../data/spells/spell.h"
#include "../../infos/spell_cast_info.h"
#include "../ai/entity_ai.h"
#include "../entity.h"
#include "character_spec.h"

#include "core/version.h"

int EntityClassData::get_id() {
	return _id;
}
void EntityClassData::set_id(int value) {
	_id = value;
}

String EntityClassData::get_text_description() {
	return _text_description;
}
void EntityClassData::set_text_description(String value) {
	_text_description = value;
}

Ref<EntityClassData> EntityClassData::get_inherits() {
	return _inherits;
}
void EntityClassData::set_inherits(Ref<EntityClassData> value) {
	_inherits = value;
}

Ref<Texture> EntityClassData::get_icon() {
	return _icon;
}
void EntityClassData::set_icon(Ref<Texture> value) {
	_icon = Ref<Texture>(value);
}

int EntityClassData::get_spell_points_per_level() {
	return _spell_points_per_level;
}
void EntityClassData::set_spell_points_per_level(int value) {
	_spell_points_per_level = value;
}

EntityEnums::EntityClassPlaystyleType EntityClassData::get_playstyle_type() {
	return _playstyle_type;
}
void EntityClassData::set_playstyle_type(EntityEnums::EntityClassPlaystyleType playstyle_type) {
	_playstyle_type = playstyle_type;
}

Ref<StatData> EntityClassData::get_stat_data() {
	if (!_stat_data.is_valid() && _inherits.is_valid()) {
		return _inherits->get_stat_data();
	}

	if (!_stat_data.is_valid())
		return Ref<StatData>();

	return _stat_data;
}

void EntityClassData::set_stat_data(Ref<StatData> value) {
	_stat_data = value;
}

////    Entity Resources    ////

int EntityClassData::get_num_entity_resources() {
	if (_entity_resources.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_entity_resources();
	}

	return _entity_resources.size();
}
void EntityClassData::set_num_entity_resources(int value) {
	_entity_resources.resize(value);
}

Ref<EntityResourceData> EntityClassData::get_entity_resource(int index) const {
	if (_entity_resources.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_entity_resource(index);
	}

	ERR_FAIL_INDEX_V(index, _entity_resources.size(), Ref<EntityResourceData>());

	return _entity_resources[index];
}
void EntityClassData::set_entity_resource(int index, Ref<EntityResourceData> entity_resource) {
	ERR_FAIL_INDEX(index, _entity_resources.size());

	_entity_resources.set(index, Ref<EntityResourceData>(entity_resource));
}

Vector<Variant> EntityClassData::get_entity_resources() {
	Vector<Variant> r;
	for (int i = 0; i < _entity_resources.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_entity_resources[i].get_ref_ptr());
#else
		r.push_back(_entity_resources[i]);
#endif
	}
	return r;
}
void EntityClassData::set_entity_resources(const Vector<Variant> &entity_resources) {
	_entity_resources.clear();
	for (int i = 0; i < entity_resources.size(); i++) {
		Ref<EntityResourceData> entity_resource = Ref<EntityResourceData>(entity_resources[i]);

		_entity_resources.push_back(entity_resource);
	}
}

////    SPECS    ////

int EntityClassData::get_num_specs() {
	if (_specs.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_specs();
	}

	return _specs.size();
}
void EntityClassData::set_num_specs(int value) {
	_specs.resize(value);
}

Ref<CharacterSpec> EntityClassData::get_spec(int index) const {
	if (_specs.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_spec(index);
	}

	ERR_FAIL_INDEX_V(index, _specs.size(), Ref<CharacterSpec>());

	return _specs[index];
}
void EntityClassData::set_spec(int index, Ref<CharacterSpec> spec) {
	ERR_FAIL_INDEX(index, _specs.size());

	_specs.set(index, Ref<CharacterSpec>(spec));
}

Vector<Variant> EntityClassData::get_specs() {
	Vector<Variant> r;
	for (int i = 0; i < _specs.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_specs[i].get_ref_ptr());
#else
		r.push_back(_specs[i]);
#endif
	}
	return r;
}
void EntityClassData::set_specs(const Vector<Variant> &specs) {
	_specs.clear();
	for (int i = 0; i < specs.size(); i++) {
		Ref<CharacterSpec> spec = Ref<CharacterSpec>(specs[i]);

		_specs.push_back(spec);
	}
}

////    SPELLS    ////

int EntityClassData::get_num_spells() {
	if (_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_spells();
	}

	return _spells.size();
}
void EntityClassData::set_num_spells(int value) {
	_spells.resize(value);
}

Ref<Spell> EntityClassData::get_spell(int index) {
	if (_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_spell(index);
	}

	ERR_FAIL_INDEX_V(index, _spells.size(), Ref<Spell>());

	return _spells[index];
}
void EntityClassData::set_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _spells.size());

	_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> EntityClassData::get_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _spells.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_spells[i].get_ref_ptr());
#else
		r.push_back(_spells[i]);
#endif
	}
	return r;
}
void EntityClassData::set_spells(const Vector<Variant> &spells) {
	_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_spells.push_back(spell);
	}
}

////    Start Spells    ////

int EntityClassData::get_num_start_spells() {
	if (_start_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_start_spells();
	}

	return _start_spells.size();
}
void EntityClassData::set_num_start_spells(int value) {
	_start_spells.resize(value);
}

Ref<Spell> EntityClassData::get_start_spell(int index) {
	if (_start_spells.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_start_spell(index);
	}

	ERR_FAIL_INDEX_V(index, _start_spells.size(), Ref<Spell>());

	return _start_spells[index];
}
void EntityClassData::set_start_spell(int index, Ref<Spell> spell) {
	ERR_FAIL_INDEX(index, _start_spells.size());

	_start_spells.set(index, Ref<Spell>(spell));
}

Vector<Variant> EntityClassData::get_start_spells() {
	Vector<Variant> r;
	for (int i = 0; i < _start_spells.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_start_spells[i].get_ref_ptr());
#else
		r.push_back(_start_spells[i]);
#endif
	}
	return r;
}
void EntityClassData::set_start_spells(const Vector<Variant> &spells) {
	_start_spells.clear();
	for (int i = 0; i < spells.size(); i++) {
		Ref<Spell> spell = Ref<Spell>(spells[i]);

		_start_spells.push_back(spell);
	}
}

////    AURAS    ////

int EntityClassData::get_num_auras() {
	if (_auras.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_auras();
	}

	return _auras.size();
}
void EntityClassData::set_num_auras(int value) {
	_auras.resize(value);
}

Ref<Aura> EntityClassData::get_aura(int index) {
	if (_auras.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_aura(index);
	}

	ERR_FAIL_INDEX_V(index, _auras.size(), Ref<Aura>());

	return _auras[index];
}
void EntityClassData::set_aura(int index, Ref<Aura> aura) {
	ERR_FAIL_INDEX(index, _auras.size());

	_auras.set(index, aura);
}

Vector<Variant> EntityClassData::get_auras() {
	Vector<Variant> r;
	for (int i = 0; i < _auras.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_auras[i].get_ref_ptr());
#else
		r.push_back(_auras[i]);
#endif
	}
	return r;
}
void EntityClassData::set_auras(const Vector<Variant> &auras) {
	_auras.clear();
	for (int i = 0; i < auras.size(); i++) {
		Ref<Aura> aura = Ref<Aura>(auras[i]);

		_auras.push_back(aura);
	}
}

////    AI ACTIONS    ////

int EntityClassData::get_num_ais() {
	if (_ais.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_num_ais();
	}

	return _ais.size();
}
void EntityClassData::set_num_ais(int value) {
	_ais.resize(value);
}

Ref<EntityAI> EntityClassData::get_ai(int index) {
	if (_ais.size() == 0 && _inherits.is_valid()) {
		return _inherits->get_ai(index);
	}

	ERR_FAIL_INDEX_V(index, _ais.size(), Ref<EntityAI>());

	return _ais[index];
}
void EntityClassData::set_ai(int index, Ref<EntityAI> ai) {
	ERR_FAIL_INDEX(index, _ais.size());

	_ais.set(index, ai);
}

Vector<Variant> EntityClassData::get_ais() {
	Vector<Variant> r;
	for (int i = 0; i < _ais.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_ais[i].get_ref_ptr());
#else
		r.push_back(_ais[i]);
#endif
	}
	return r;
}
void EntityClassData::set_ais(const Vector<Variant> &ais) {
	_ais.clear();
	for (int i = 0; i < ais.size(); i++) {
		Ref<EntityAI> ai = Ref<EntityAI>(ais[i]);

		_ais.push_back(ai);
	}
}

Ref<EntityAI> EntityClassData::get_ai_instance() {
	return call("_get_ai_instance");
}
Ref<EntityAI> EntityClassData::_get_ai_instance() {
	if (_ais.size() > 0) {
		Ref<EntityAI> ai = _ais.get(Math::rand() % _ais.size());

		if (ai.is_valid()) {
			return ai->duplicate();
		}
	}

	Ref<EntityAI> ai;
	ai.instance();
	return ai;
}

////    SETUP    ////

void EntityClassData::setup_resources(Entity *entity) {
	if (_inherits.is_valid())
		_inherits->setup_resources(entity);

	call("_setup_resources", entity);
}

void EntityClassData::_setup_resources(Node *entity) {
	Entity *ent = Object::cast_to<Entity>(entity);

	for (int i = 0; i < _entity_resources.size(); ++i) {
		Ref<EntityResourceData> res = _entity_resources.get(i);

		if (res.is_valid()) {
			ent->resource_adds(res->get_entity_resource_instance());
		}
	}
}

void EntityClassData::start_casting(int spell_id, Entity *caster, float spellScale) {
	if (_spells.size() == 0 && _inherits.is_valid()) {
		_inherits->start_casting(spell_id, caster, spellScale);
		return;
	}

	for (int i = 0; i < _spells.size(); i++) {
		Ref<Spell> s = _spells[i];

		if (s == NULL) {
			print_error("class doesn't have spell! spell_id: " + itos(spell_id));
			return;
		}

		if (s->get_id() == spell_id) {
			s->cast_starts_simple(caster, spellScale);
			return;
		}
	}
}

void EntityClassData::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);
}
void EntityClassData::notification_sheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, info);
}
void EntityClassData::notification_scast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_scast"))
		call("_notification_scast", what, info);
}
void EntityClassData::notification_sdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, info);
}

void EntityClassData::notification_sdeath(Entity *entity) {
	if (has_method("_notification_sdeath"))
		call("_notification_sdeath", entity);
}

void EntityClassData::notification_sdeath_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sdeath(e);
}

void EntityClassData::notification_scooldown_added(Ref<Cooldown> cooldown) {
	if (has_method("_notification_scooldown_added"))
		call("_notification_scooldown_added", cooldown);
}
void EntityClassData::notification_scooldown_removed(Ref<Cooldown> cooldown) {
	if (has_method("_notification_scooldown_removed"))
		call("_notification_scooldown_removed", cooldown);
}

void EntityClassData::notification_scategory_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_notification_scategory_cooldown_added"))
		call("_notification_scategory_cooldown_added", category_cooldown);
}
void EntityClassData::notification_scategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	if (has_method("_notification_scategory_cooldown_removed"))
		call("_notification_scategory_cooldown_removed", category_cooldown);
}

void EntityClassData::notification_sgcd_started(Entity *entity, float gcd) {
	if (has_method("_notification_sgcd_started"))
		call("_notification_sgcd_started", entity, gcd);
}
void EntityClassData::notification_sgcd_finished(Entity *entity) {
	if (has_method("_notification_sgcd_finished"))
		call("_notification_sgcd_finished", entity);
}
void EntityClassData::notification_sgcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_started(e, gcd);
}
void EntityClassData::notification_sgcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sgcd_finished(e);
}

void EntityClassData::notification_sxp_gained(Entity *entity, int value) {
	if (has_method("_notification_sxp_gained"))
		call("_notification_sxp_gained", entity, value);
}
void EntityClassData::notification_sxp_gained_bind(Node *entity, int value) {

#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sxp_gained(e, value);
}

void EntityClassData::notification_sclass_level_up(Entity *entity, int value) {
	if (has_method("_notification_sclass_level_up"))
		call("_notification_sclass_level_up", entity);
}
void EntityClassData::notification_sclass_level_up_bind(Node *entity, int value) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_sclass_level_up(e, value);
}

void EntityClassData::notification_scharacter_level_up(Entity *entity, int value) {
	if (has_method("_notification_scharacter_level_up"))
		call("_notification_scharacter_level_up", entity);
}
void EntityClassData::notification_scharacter_level_up_bind(Node *entity, int value) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_scharacter_level_up(e, value);
}

void EntityClassData::notification_sentity_resource_added(Ref<EntityResource> resource) {
	if (has_method("_notification_sentity_resource_added"))
		call("_notification_sentity_resource_added", resource);
}

void EntityClassData::notification_sentity_resource_removed(Ref<EntityResource> resource) {
	if (has_method("_notification_sentity_resource_removed"))
		call("_notification_sentity_resource_removed", resource);
}

//Clientside Event Handlers
void EntityClassData::notification_caura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (has_method("_notification_caura"))
		call("_notification_caura", what, data);
}
void EntityClassData::notification_cheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_cheal"))
		call("_notification_cheal", what, info);
}
void EntityClassData::notification_ccast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_ccast"))
		call("_notification_ccast", what, info);
}
void EntityClassData::notification_cdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (has_method("_notification_cdamage"))
		call("_notification_cdamage", what, info);
}

void EntityClassData::notification_cdeath(Entity *entity) {
	ERR_FAIL_COND(entity == NULL);

	if (has_method("_notification_cdeath"))
		call("_notification_cdeath", entity);
}

void EntityClassData::notification_cdeath_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cdeath(e);
}

void EntityClassData::notification_ccooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (has_method("_notification_ccooldown_added"))
		call("_notification_ccooldown_added", cooldown);
}
void EntityClassData::notification_ccooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (has_method("_notification_ccooldown_removed"))
		call("_notification_ccooldown_removed", cooldown);
}
void EntityClassData::notification_ccategory_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (has_method("_notification_ccategory_cooldown_added"))
		call("_notification_ccategory_cooldown_added", category_cooldown);
}
void EntityClassData::notification_ccategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (has_method("_notification_ccategory_cooldown_removed"))
		call("_notification_ccategory_cooldown_removed", category_cooldown);
}

void EntityClassData::notification_cgcd_started(Entity *entity, float gcd) {
	if (has_method("_notification_cgcd_started"))
		call("_notification_cgcd_started", entity, gcd);
}
void EntityClassData::notification_cgcd_finished(Entity *entity) {
	if (has_method("_notification_cgcd_finished"))
		call("_notification_cgcd_finished", entity);
}
void EntityClassData::notification_cgcd_started_bind(Node *entity, float gcd) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cgcd_started(e, gcd);
}
void EntityClassData::notification_cgcd_finished_bind(Node *entity) {
	ERR_FAIL_COND(entity == NULL);

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cgcd_finished(e);
}

void EntityClassData::notification_cxp_gained(Entity *entity, int value) {
	if (has_method("_notification_cxp_gained"))
		call("_notification_cxp_gained", entity, value);
}
void EntityClassData::notification_cxp_gained_bind(Node *entity, int value) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cxp_gained(e, value);
}

void EntityClassData::notification_cclass_level_up(Entity *entity, int value) {
	if (has_method("_notification_cclass_level_up"))
		call("_notification_cclass_level_up", entity);
}
void EntityClassData::notification_cclass_level_up_bind(Node *entity, int value) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_cclass_level_up(e, value);
}

void EntityClassData::notification_ccharacter_level_up(Entity *entity, int value) {
	if (has_method("_notification_ccharacter_level_up"))
		call("_notification_ccharacter_level_up", entity);
}
void EntityClassData::notification_ccharacter_level_up_bind(Node *entity, int value) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	notification_ccharacter_level_up(e, value);
}

void EntityClassData::notification_centity_resource_added(Ref<EntityResource> resource) {
	if (has_method("_notification_centity_resource_added"))
		call("_notification_centity_resource_added", resource);
}

void EntityClassData::notification_centity_resource_removed(Ref<EntityResource> resource) {
	if (has_method("_notification_centity_resource_removed"))
		call("_notification_centity_resource_removed", resource);
}

//Equipment

bool EntityClassData::equip_should_deny(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item) {
	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", entity, equip_slot, item))
			return true;

	return false;
}
bool EntityClassData::equip_should_deny_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND_V(!ObjectDB::instance_validate(entity), false);
#else
	ERR_FAIL_COND_V(entity == NULL, false);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND_V(e == NULL, false);

	return equip_should_deny(e, equip_slot, item);
}

void EntityClassData::equip_son_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_son_success"))
		call("_equip_son_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityClassData::equip_son_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityClassData::equip_son_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityClassData::equip_son_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_son_fail(e, equip_slot, item, old_item, bag_slot);
}

void EntityClassData::equip_con_success(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_con_success"))
		call("_equip_con_success", entity, equip_slot, item, old_item, bag_slot);
}
void EntityClassData::equip_con_success_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_success(e, equip_slot, item, old_item, bag_slot);
}

void EntityClassData::equip_con_fail(Entity *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", entity, equip_slot, item, old_item, bag_slot);
}
void EntityClassData::equip_con_fail_bind(Node *entity, ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
#else
	ERR_FAIL_COND(entity == NULL);
#endif

	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(e == NULL);

	equip_con_fail(e, equip_slot, item, old_item, bag_slot);
}

EntityClassData::EntityClassData() {
	_id = 0;
	_spell_points_per_level = 1;
	_playstyle_type = EntityEnums::ENTITY_CLASS_PLAYSTYLE_TYPE_MELEE;
}

EntityClassData::~EntityClassData() {
	_spells.clear();
	_specs.clear();
	_auras.clear();
	_ais.clear();
}

void EntityClassData::_bind_methods() {
	//EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &EntityClassData::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "info"), &EntityClassData::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "info"), &EntityClassData::notification_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "info"), &EntityClassData::notification_sdamage);

	BIND_VMETHOD(MethodInfo("_notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_caura", "what", "data"), &EntityClassData::notification_caura);
	ClassDB::bind_method(D_METHOD("notification_cheal", "what", "info"), &EntityClassData::notification_cheal);
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "info"), &EntityClassData::notification_ccast);
	ClassDB::bind_method(D_METHOD("notification_cdamage", "what", "info"), &EntityClassData::notification_cdamage);

	ClassDB::bind_method(D_METHOD("notification_sdeath", "data"), &EntityClassData::notification_sdeath_bind);

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "cooldown"), &EntityClassData::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "cooldown"), &EntityClassData::notification_scooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "category_cooldown"), &EntityClassData::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "category_cooldown"), &EntityClassData::notification_scategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started", "entity", "gcd"), &EntityClassData::notification_sgcd_started_bind);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished", "entity"), &EntityClassData::notification_sgcd_finished_bind);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "entity", "value"), &EntityClassData::notification_sxp_gained_bind);
	ClassDB::bind_method(D_METHOD("notification_sclass_level_up", "entity", "value"), &EntityClassData::notification_sclass_level_up_bind);
	ClassDB::bind_method(D_METHOD("notification_scharacter_level_up", "entity", "value"), &EntityClassData::notification_scharacter_level_up_bind);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "resource"), &EntityClassData::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "resource"), &EntityClassData::notification_sentity_resource_removed);

	BIND_VMETHOD(MethodInfo("_notification_sdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_scooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("_notification_scooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));

	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("_notification_scategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_notification_sgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_sgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_sclass_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_scharacter_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	BIND_VMETHOD(MethodInfo("_notification_centity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_centity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	BIND_VMETHOD(MethodInfo("_setup_resources", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	//Clientside Event Handlers
	ClassDB::bind_method(D_METHOD("notification_cdeath", "data"), &EntityClassData::notification_cdeath_bind);

	ClassDB::bind_method(D_METHOD("notification_ccooldown_added", "cooldown"), &EntityClassData::notification_ccooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccooldown_removed", "cooldown"), &EntityClassData::notification_ccooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_added", "cooldown"), &EntityClassData::notification_ccategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_removed", "cooldown"), &EntityClassData::notification_ccategory_cooldown_removed);

	ClassDB::bind_method(D_METHOD("notification_cgcd_started", "entity", "gcd"), &EntityClassData::notification_cgcd_started_bind);
	ClassDB::bind_method(D_METHOD("notification_cgcd_finished", "entity"), &EntityClassData::notification_cgcd_finished_bind);

	ClassDB::bind_method(D_METHOD("notification_cxp_gained", "entity", "value"), &EntityClassData::notification_cxp_gained_bind);
	ClassDB::bind_method(D_METHOD("notification_cclass_level_up", "entity", "value"), &EntityClassData::notification_cclass_level_up_bind);
	ClassDB::bind_method(D_METHOD("notification_ccharacter_level_up", "entity", "value"), &EntityClassData::notification_ccharacter_level_up_bind);

	ClassDB::bind_method(D_METHOD("notification_centity_resource_added", "resource"), &EntityClassData::notification_centity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_centity_resource_removed", "resource"), &EntityClassData::notification_centity_resource_removed);

	BIND_VMETHOD(MethodInfo("_notification_cdeath", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_cgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_cgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_notification_cxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_cclass_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_ccharacter_level_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	//Equipment
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_equip_should_deny", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_equip_son_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_son_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("equip_should_deny", "entity", "equip_slot", "item"), &EntityClassData::equip_should_deny_bind);

	ClassDB::bind_method(D_METHOD("equip_son_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityClassData::equip_son_success_bind);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityClassData::equip_son_fail_bind);
	ClassDB::bind_method(D_METHOD("equip_con_success", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityClassData::equip_con_success_bind);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "entity", "equip_slot", "item", "old_item", "bag_slot"), &EntityClassData::equip_con_fail_bind);

	ClassDB::bind_method(D_METHOD("get_id"), &EntityClassData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityClassData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntityClassData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntityClassData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_text_description", "get_text_description");

	ClassDB::bind_method(D_METHOD("get_inherits"), &EntityClassData::get_inherits);
	ClassDB::bind_method(D_METHOD("set_inherits", "value"), &EntityClassData::set_inherits);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "inherits", PROPERTY_HINT_RESOURCE_TYPE, "EntityClassData"), "set_inherits", "get_inherits");

	ClassDB::bind_method(D_METHOD("get_icon"), &EntityClassData::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &EntityClassData::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("get_stat_data"), &EntityClassData::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "value"), &EntityClassData::set_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data", PROPERTY_HINT_RESOURCE_TYPE, "StatData"), "set_stat_data", "get_stat_data");

	ClassDB::bind_method(D_METHOD("get_spell_points_per_level"), &EntityClassData::get_spell_points_per_level);
	ClassDB::bind_method(D_METHOD("set_spell_points_per_level", "value"), &EntityClassData::set_spell_points_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_points_per_level"), "set_spell_points_per_level", "get_spell_points_per_level");

	ClassDB::bind_method(D_METHOD("get_playstyle_type"), &EntityClassData::get_playstyle_type);
	ClassDB::bind_method(D_METHOD("set_playstyle_type", "value"), &EntityClassData::set_playstyle_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "playstyle_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_PLAYSTYLE_TYPE), "set_playstyle_type", "get_playstyle_type");

	////    Entity Resources    ////
	ClassDB::bind_method(D_METHOD("get_num_entity_resources"), &EntityClassData::get_num_entity_resources);
	ClassDB::bind_method(D_METHOD("set_num_entity_resources", "value"), &EntityClassData::set_num_entity_resources);

	ClassDB::bind_method(D_METHOD("get_entity_resource", "index"), &EntityClassData::get_entity_resource);
	ClassDB::bind_method(D_METHOD("set_entity_resource", "index", "entity_resource"), &EntityClassData::set_entity_resource);

	ClassDB::bind_method(D_METHOD("get_entity_resources"), &EntityClassData::get_entity_resources);
	ClassDB::bind_method(D_METHOD("set_entity_resources", "entity_resources"), &EntityClassData::set_entity_resources);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entity_resources", PROPERTY_HINT_NONE, "17/17:EntityResourceData", PROPERTY_USAGE_DEFAULT, "EntityResourceData"), "set_entity_resources", "get_entity_resources");

	ClassDB::bind_method(D_METHOD("_setup_resources", "entity"), &EntityClassData::_setup_resources);

	////    Specs    ////
	ClassDB::bind_method(D_METHOD("get_num_specs"), &EntityClassData::get_num_specs);
	ClassDB::bind_method(D_METHOD("set_num_specs", "value"), &EntityClassData::set_num_specs);

	ClassDB::bind_method(D_METHOD("get_spec", "index"), &EntityClassData::get_spec);
	ClassDB::bind_method(D_METHOD("set_spec", "index", "spec"), &EntityClassData::set_spec);

	ClassDB::bind_method(D_METHOD("get_specs"), &EntityClassData::get_specs);
	ClassDB::bind_method(D_METHOD("set_specs", "specs"), &EntityClassData::set_specs);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "specs", PROPERTY_HINT_NONE, "17/17:CharacterSpec", PROPERTY_USAGE_DEFAULT, "CharacterSpec"), "set_specs", "get_specs");

	////    Spell    ////
	ClassDB::bind_method(D_METHOD("get_num_spells"), &EntityClassData::get_num_spells);
	ClassDB::bind_method(D_METHOD("set_num_spells", "value"), &EntityClassData::set_num_spells);

	ClassDB::bind_method(D_METHOD("get_spell", "index"), &EntityClassData::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "index", "spell"), &EntityClassData::set_spell);

	ClassDB::bind_method(D_METHOD("get_spells"), &EntityClassData::get_spells);
	ClassDB::bind_method(D_METHOD("set_spells", "spells"), &EntityClassData::set_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_spells", "get_spells");

	////    Start Spells    ////
	ClassDB::bind_method(D_METHOD("get_num_start_spells"), &EntityClassData::get_num_start_spells);
	ClassDB::bind_method(D_METHOD("set_num_start_spells", "value"), &EntityClassData::set_num_start_spells);

	ClassDB::bind_method(D_METHOD("get_start_spell", "index"), &EntityClassData::get_start_spell);
	ClassDB::bind_method(D_METHOD("set_start_spell", "index", "spell"), &EntityClassData::set_start_spell);

	ClassDB::bind_method(D_METHOD("get_start_spells"), &EntityClassData::get_start_spells);
	ClassDB::bind_method(D_METHOD("set_start_spells", "spells"), &EntityClassData::set_start_spells);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "start_spells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_DEFAULT, "Spell"), "set_start_spells", "get_start_spells");

	////    AURAS    ////
	ClassDB::bind_method(D_METHOD("get_num_auras"), &EntityClassData::get_num_auras);
	ClassDB::bind_method(D_METHOD("set_num_auras", "value"), &EntityClassData::set_num_auras);

	ClassDB::bind_method(D_METHOD("get_aura", "index"), &EntityClassData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "index", "aura"), &EntityClassData::set_aura);

	ClassDB::bind_method(D_METHOD("get_auras"), &EntityClassData::get_auras);
	ClassDB::bind_method(D_METHOD("set_auras", "auras"), &EntityClassData::set_auras);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "auras", PROPERTY_HINT_NONE, "17/17:Aura", PROPERTY_USAGE_DEFAULT, "Aura"), "set_auras", "get_auras");

	////    AI ACTIONS    ////
	ClassDB::bind_method(D_METHOD("get_num_ais"), &EntityClassData::get_num_ais);
	ClassDB::bind_method(D_METHOD("set_num_ais", "value"), &EntityClassData::set_num_ais);

	ClassDB::bind_method(D_METHOD("get_ai", "index"), &EntityClassData::get_ai);
	ClassDB::bind_method(D_METHOD("set_ai", "index", "action"), &EntityClassData::set_ai);

	ClassDB::bind_method(D_METHOD("get_ais"), &EntityClassData::get_ais);
	ClassDB::bind_method(D_METHOD("set_ais", "auras"), &EntityClassData::set_ais);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ais", PROPERTY_HINT_NONE, "17/17:EntityAI", PROPERTY_USAGE_DEFAULT, "EntityAI"), "set_ais", "get_ais");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "ret", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI"), "_get_ai_instance"));

	ClassDB::bind_method(D_METHOD("get_ai_instance"), &EntityClassData::get_ai_instance);
	ClassDB::bind_method(D_METHOD("_get_ai_instance"), &EntityClassData::_get_ai_instance);
}
