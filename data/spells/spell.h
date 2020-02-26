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

#ifndef SPELL_H
#define SPELL_H

#include "core/resource.h"
#include "scene/resources/texture.h"

#include "../../entity_enums.h"
#include "../../spell_enums.h"

#include "../../infos/spell_cast_info.h"

#include "../../entities/entity.h"
#include "../../entities/stats/stat.h"

#include "../../infos/aura_infos.h"
#include "../../pipelines/spell_damage_info.h"

#include "spell_effect_visual.h"

#include "../../world_spells/world_spell_data.h"

class Entity;
class Aura;
class SpellCastInfo;
class Spell;
class CraftRecipe;
class EntityResourceCostData;
class EntitySkillData;

enum TargetRelationType {
	TARGET_SELF = 1 << 0,
	TARGET_ENEMY = 1 << 1,
	TARGET_FRIENDLY = 1 << 2
};

VARIANT_ENUM_CAST(TargetRelationType);

enum SpellTargetType {
	SPELL_TARGET_TYPE_SELF,
	SPELL_TARGET_TYPE_TARGET,
	SPELL_TARGET_TYPE_AROUND,
	SPELL_TARGET_TYPE_FRONT,
	SPELL_TARGET_TYPE_AROUND_TARGET
};

VARIANT_ENUM_CAST(SpellTargetType);

enum SpellAOETargetType {
	SPELL_AOE_TARGET_TYPE_CASTER,
	SPELL_AOE_TARGET_TYPE_TARGET,
	SPELL_AOE_TARGET_TYPE_GOUND_TARGET_SELECTION,
	SPELL_AOE_TARGET_TYPE_RANDOM
};

VARIANT_ENUM_CAST(SpellAOETargetType);

class Spell : public Resource {
	GDCLASS(Spell, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int get_spell_type() const;
	void set_spell_type(const int value);

	SpellEnums::SpellCategory get_spell_category() const;
	void set_spell_category(const SpellEnums::SpellCategory value);

	bool get_hide_from_actionbar() const;
	void set_hide_from_actionbar(const bool value);

	float get_cooldown() const;
	void set_cooldown(const float value);

	SpellTargetType get_target_type() const;
	void set_target_type(const SpellTargetType value);

	TargetRelationType get_target_relation_type() const;
	void set_target_relation_type(const TargetRelationType value);

	int get_level() const;
	void set_level(const int value);

	int get_rank() const;
	void set_rank(const int value);

	bool get_scale_with_level() const;
	void set_scale_with_level(const bool value);

	Ref<ItemTemplate> get_item_cost();
	void set_item_cost(const Ref<ItemTemplate> &value);

	Ref<ItemTemplate> get_required_item();
	void set_required_item(const Ref<ItemTemplate> &value);

	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(const Ref<EntityResourceCostData> &value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(const Ref<EntityResourceCostData> &value);

	bool get_global_cooldown_enabled() const;
	void set_global_cooldown_enabled(const bool value);

	bool get_is_local_spell() const;
	void set_is_local_spell(const bool value);

	Ref<Texture> get_icon();
	void set_icon(const Ref<Texture> &value);

	String get_text_translation_key() const;
	void set_text_translation_key(const String &value);

	String get_text_description() const;
	void set_text_description(const String &value);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(const Ref<SpellEffectVisual> &value);

	Ref<WorldSpellData> get_projectile();
	void set_projectile(const Ref<WorldSpellData> &value);

	Ref<CraftRecipe> get_teaches_craft_recipe();
	void set_teaches_craft_recipe(const Ref<CraftRecipe> &value);

	//Caster Aura Apply
	int get_num_caster_aura_applys() const;
	void set_num_caster_aura_applys(const int value);

	Ref<Aura> get_caster_aura_apply(const int index);
	void set_caster_aura_apply(const int index, const Ref<Aura> &caster_aura_apply);

	Vector<Variant> get_caster_aura_applys();
	void set_caster_aura_applys(const Vector<Variant> &caster_aura_applys);

	//Target Aura Apply
	int get_num_target_aura_applys() const;
	void set_num_target_aura_applys(const int value);

	Ref<Aura> get_target_aura_apply(const int index);
	void set_target_aura_apply(const int index, const Ref<Aura> &target_aura_apply);

	Vector<Variant> get_target_aura_applys();
	void set_target_aura_applys(const Vector<Variant> &target_aura_applys);

	//Apply Auras On Learn
	int get_num_on_learn_auras() const;
	void set_num_on_learn_auras(const int value);

	Ref<Aura> get_on_learn_aura(const int index);
	void set_on_learn_aura(const int index, const Ref<Aura> &on_learn_aura);

	Vector<Variant> get_on_learn_auras();
	void set_on_learn_auras(const Vector<Variant> &on_learn_auras);

	//Range
	bool get_range_enabled() const;
	void set_range_enabled(const bool value);

	float get_range() const;
	void set_range(const float value);

	bool get_cast_time_enabled() const;
	void set_cast_time_enabled(const bool value);

	float get_cast_time() const;
	void set_cast_time(const float value);

	bool get_damage_enabled() const;
	void set_damage_enabled(const bool value);

	int get_damage_type() const;
	void set_damage_type(const int value);

	int get_damage_min() const;
	void set_damage_min(const int value);

	int get_damage_max() const;
	void set_damage_max(const int value);

	Stat::StatId get_damage_scale_stat() const;
	void set_damage_scale_stat(const Stat::StatId value);

	float get_damage_scale_coeff() const;
	void set_damage_scale_coeff(const float value);

	bool get_heal_enabled() const;
	void set_heal_enabled(const bool value);

	int get_heal_min() const;
	void set_heal_min(const int value);

	int get_heal_max() const;
	void set_heal_max(const int value);

	Stat::StatId get_heal_scale_stat() const;
	void set_heal_scale_stat(const Stat::StatId value);

	float get_heal_scale_coeff() const;
	void set_heal_scale_coeff(const float value);

	//Dispells
	bool get_dispell_enabled() const;
	void set_dispell_enabled(const bool value);

	int get_dispell_count_min() const;
	void set_dispell_count_min(const int value);

	int get_dispell_count_max() const;
	void set_dispell_count_max(const int value);

	int get_dispell_aura_types() const;
	void set_dispell_aura_types(const int value);

	//Target
	bool get_needs_target() const;
	void set_needs_target(const bool value);

	bool get_can_move_while_casting() const;
	void set_can_move_while_casting(const bool value);

	bool get_interrupt_enabled() const;
	void set_interrupt_enabled(const bool value);

	float get_interrupt_time() const;
	void set_interrupt_time(const float value);

	//AOE
	bool get_is_aoe() const;
	void set_is_aoe(const bool value);

	SpellAOETargetType get_aoe_target_type() const;
	void set_aoe_target_type(const SpellAOETargetType value);

	SpellEnums::ColliderType get_aoe_collider_type() const;
	void set_aoe_collider_type(const SpellEnums::ColliderType value);

	float get_aoe_radius() const;
	void set_aoe_radius(const float value);

	Vector3 get_aoe_box_extents() const;
	void set_aoe_box_extents(const Vector3 value);

	int get_spell_cooldown_mainpulation_data_count() const;
	void set_spell_cooldown_mainpulation_data_count(const int value);

	int get_training_cost() const;
	void set_training_cost(int value);

	Ref<Spell> get_training_required_spell();
	void set_training_required_spell(const Ref<Spell> &spell);

	Ref<EntitySkillData> get_training_required_skill();
	void set_training_required_skill(const Ref<EntitySkillData> &skill);

	int get_training_required_skill_level() const;
	void set_training_required_skill_level(const int value);

	////    Spell Script    ////

	float PLAYER_HIT_RADIUS;

	//Commands, c++ only
	void sstart_casting_simple(Entity *caster, float spell_scale);
	void sinterrupt_cast_simple(Entity *caster);
	void sstart_casting_triggered_simple(Entity *caster);

	//Commands
	void sstart_casting(Ref<SpellCastInfo> info);
	void sstart_casting_triggered(Ref<SpellCastInfo> info);
	void sinterrupt_cast(Ref<SpellCastInfo> info);
	void sfinish_cast(Ref<SpellCastInfo> info);

	//eventhandlers
	void son_cast_player_moved(Ref<SpellCastInfo> info);
	void son_cast_damage_received(Ref<SpellCastInfo> info);
	void son_spell_hit(Ref<SpellCastInfo> info);
	void son_physics_process(Ref<SpellCastInfo> info, float delta);

	//Clientside Event Handlers
	void con_spell_cast_started(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);
	void con_spell_cast_failed(Ref<SpellCastInfo> info);
	void con_spell_cast_ended(Ref<SpellCastInfo> info);
	void con_spell_cast_interrupted(Ref<SpellCastInfo> info);

	//Calculations / Queries
	void calculate_initial_damage(Ref<SpellDamageInfo> data);
	void handle_spell_damage(Ref<SpellDamageInfo> data);

	void handle_projectile(Ref<SpellCastInfo> info);
	void handle_effect(Ref<SpellCastInfo> info);

	void handle_gcd(Ref<SpellCastInfo> info);
	void handle_cooldown(Ref<SpellCastInfo> info);

	String get_name_translated() const;
	String get_description(const int class_level, const int character_level);
	String _get_description(const int class_level, const int character_level);

	Spell();
	~Spell();

protected:
	virtual void _sstart_casting(Ref<SpellCastInfo> info);
	virtual void _sfinish_cast(Ref<SpellCastInfo> info);

	virtual void _son_cast_player_moved(Ref<SpellCastInfo> info);
	virtual void _son_spell_hit(Ref<SpellCastInfo> info);

	virtual void _calculate_initial_damage(Ref<SpellDamageInfo> data);
	virtual void _handle_spell_damage(Ref<SpellDamageInfo> data);

	virtual void _handle_projectile(Ref<SpellCastInfo> info);
	virtual void _handle_effect(Ref<SpellCastInfo> info);

	static void _bind_methods();

private:
	int _id;
	int _spell_type;
	SpellEnums::SpellCategory _spell_category;

	bool _hide_from_actionbar;
	float _cooldown;
	SpellTargetType _target_type;
	TargetRelationType _target_relation_type;

	Vector<Ref<Aura> > _caster_aura_applys;
	Vector<Ref<Aura> > _target_aura_applys;
	Vector<Ref<Aura> > _on_learn_auras;

	int _level;
	int _rank;

	bool _scale_with_level;

	Ref<ItemTemplate> _item_cost;
	Ref<ItemTemplate> _required_item;

	Ref<EntityResourceCostData> _resource_cost;
	Ref<EntityResourceCostData> _resource_give;

	bool _global_cooldown_enabled;
	bool _is_local_spell;
	Ref<Texture> _icon;

	String _text_translation_key;
	String _text_description;

	Ref<SpellEffectVisual> _visual_spell_effects;

	Ref<WorldSpellData> _world_spell_data;
	Ref<CraftRecipe> _teaches_craft_recipe;

	bool _range_enabled;
	float _range;

	bool _damage_enabled;
	int _damage_type;
	int _damage_min;
	int _damage_max;
	Stat::StatId _damage_scale_stat;
	float _damage_scale_coeff;

	bool _heal_enabled;
	int _heal_min;
	int _heal_max;
	Stat::StatId _heal_scale_stat;
	float _heal_scale_coeff;

	bool _dispell_enabled;
	int _dispell_count_min;
	int _dispell_count_max;
	int _dispell_aura_types;

	bool _cast_time_enabled;
	float _cast_time;

	bool _needs_target;
	bool _can_move_while_casting;

	bool _interrupt_enabled;
	float _interrupt_time;

	bool _is_aoe;
	SpellAOETargetType _aoe_targetType;
	SpellEnums::ColliderType _aoe_colliderType;
	float _aoe_radius;
	Vector3 _aoe_box_extents;

	Ref<WorldSpellData> _projectile;

	int _spell_cooldown_mainpulation_data_count;

	int _training_cost;
	Ref<Spell> _training_required_spell;
	Ref<EntitySkillData> _training_required_skill;
	int _training_required_skill_level;
};

#endif
