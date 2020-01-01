#ifndef SPELL_H
#define SPELL_H

#include "core/resource.h"
#include "scene/resources/texture.h"

#include "../entity_enums.h"
#include "../spell_enums.h"

#include "../infos/spell_cast_info.h"

#include "../entities/entity.h"
#include "../entities/stats/stat.h"

#include "../pipelines/spell_damage_info.h"
#include "../infos/aura_infos.h"

#include "spell_effect_visual.h"

#include "../world_spells/world_spell_data.h"

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
	int get_id();
	void set_id(int value);

	int get_spell_type();
	void set_spell_type(int value);

	SpellEnums::SpellCategory get_spell_category();
	void set_spell_category(SpellEnums::SpellCategory value);

	bool get_hide_from_actionbar();
	void set_hide_from_actionbar(bool value);

	float get_cooldown();
	void set_cooldown(float value);

	SpellTargetType get_target_type();
	void set_target_type(SpellTargetType value);

	TargetRelationType get_target_relation_type();
	void set_target_relation_type(TargetRelationType value);

	int get_level();
	void set_level(int value);

	int get_rank();
	void set_rank(int value);

	bool get_scale_with_level();
	void set_scale_with_level(bool value);

	int get_item_cost();
	void set_item_cost(int value);

	int get_craft_material_cost();
	void set_craft_material_cost(int value);

	int get_required_item();
	void set_required_item(int value);

	Ref<EntityResourceCostData> get_resource_cost();
	void set_resource_cost(Ref<EntityResourceCostData> value);

	Ref<EntityResourceCostData> get_resource_give();
	void set_resource_give(Ref<EntityResourceCostData> value);

	bool get_global_cooldown_enabled();
	void set_global_cooldown_enabled(bool value);

	bool get_is_local_spell();
	void set_is_local_spell(bool value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	String get_text_description();
	void set_text_description(String value);

	Ref<SpellEffectVisual> get_visual_spell_effects();
	void set_visual_spell_effects(Ref<SpellEffectVisual> value);

	Ref<WorldSpellData> get_projectile();
	void set_projectile(Ref<WorldSpellData> value);

	Ref<CraftRecipe> get_teaches_craft_recipe();
	void set_teaches_craft_recipe(Ref<CraftRecipe> value);

	//Caster Aura Apply
	int get_num_caster_aura_applys();
	void set_num_caster_aura_applys(int value);

	Ref<Aura> get_caster_aura_apply(int index) const;
	void set_caster_aura_apply(int index, Ref<Aura> caster_aura_apply);

	Vector<Variant> get_caster_aura_applys();
	void set_caster_aura_applys(const Vector<Variant> &caster_aura_applys);

	//Target Aura Apply
	int get_num_target_aura_applys();
	void set_num_target_aura_applys(int value);

	Ref<Aura> get_target_aura_apply(int index) const;
	void set_target_aura_apply(int index, Ref<Aura> target_aura_apply);

	Vector<Variant> get_target_aura_applys();
	void set_target_aura_applys(const Vector<Variant> &target_aura_applys);

	//Apply Auras On Learn
	int get_num_on_learn_auras();
	void set_num_on_learn_auras(int value);

	Ref<Aura> get_on_learn_aura(int index) const;
	void set_on_learn_aura(int index, Ref<Aura> on_learn_aura);

	Vector<Variant> get_on_learn_auras();
	void set_on_learn_auras(const Vector<Variant> &on_learn_auras);

	//Range
	bool get_range_enabled();
	void set_range_enabled(bool value);

	float get_range();
	void set_range(float value);

	bool get_cast_time_enabled();
	void set_cast_time_enabled(bool value);

	float get_cast_time();
	void set_cast_time(float value);

	bool get_damage_enabled();
	void set_damage_enabled(bool value);

	int get_damage_type();
	void set_damage_type(int value);

	int get_damage_min();
	void set_damage_min(int value);

	int get_damage_max();
	void set_damage_max(int value);

	Stat::StatId get_damage_scale_stat();
	void set_damage_scale_stat(Stat::StatId value);

	float get_damage_scale_coeff();
	void set_damage_scale_coeff(float value);

	bool get_heal_enabled();
	void set_heal_enabled(bool value);

	int get_heal_min();
	void set_heal_min(int value);

	int get_heal_max();
	void set_heal_max(int value);

	Stat::StatId get_heal_scale_stat();
	void set_heal_scale_stat(Stat::StatId value);

	float get_heal_scale_coeff();
	void set_heal_scale_coeff(float value);

	//Dispells
	bool get_dispell_enabled();
	void set_dispell_enabled(bool value);

	int get_dispell_count_min();
	void set_dispell_count_min(int value);

	int get_dispell_count_max();
	void set_dispell_count_max(int value);

	int get_dispell_aura_types();
	void set_dispell_aura_types(int value);

	//Target
	bool get_needs_target();
	void set_needs_target(bool value);

	bool get_can_move_while_casting();
	void set_can_move_while_casting(bool value);

	bool get_interrupt_enabled();
	void set_interrupt_enabled(bool value);

	float get_interrupt_time();
	void set_interrupt_time(float value);

	//AOE
	bool get_is_aoe();
	void set_is_aoe(bool value);

	SpellAOETargetType get_aoe_target_type();
	void set_aoe_target_type(SpellAOETargetType value);

	SpellEnums::ColliderType get_aoe_collider_type();
	void set_aoe_collider_type(SpellEnums::ColliderType value);

	float get_aoe_radius();
	void set_aoe_radius(float value);

	Vector3 get_aoe_box_extents();
	void set_aoe_box_extents(Vector3 value);

	int get_spell_cooldown_mainpulation_data_count();
	void set_spell_cooldown_mainpulation_data_count(int value);

	int get_training_cost();
	void set_training_cost(int value);

	Ref<Spell> get_training_required_spell();
	void set_training_required_spell(Ref<Spell> spell);

	Ref<EntitySkillData> get_training_required_skill();
	void set_training_required_skill(Ref<EntitySkillData> skill);

	int get_training_required_skill_level();
	void set_training_required_skill_level(int value);

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

	void fire_projectile(Ref<SpellCastInfo> info);
	void handle_effect(Ref<SpellCastInfo> info);

	virtual void _sstart_casting(Ref<SpellCastInfo> info);
	virtual void _sfinish_cast(Ref<SpellCastInfo> info);

	virtual void _son_cast_player_moved(Ref<SpellCastInfo> info);
	virtual void _son_spell_hit(Ref<SpellCastInfo> info);

	virtual void _calculate_initial_damage(Ref<SpellDamageInfo> data);
	virtual void _handle_spell_damage(Ref<SpellDamageInfo> data);

	virtual void _fire_projectile(Ref<SpellCastInfo> info);
	virtual void _handle_effect(Ref<SpellCastInfo> info);

	String get_description(int level);

	Spell();
	~Spell();

protected:
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
	int _item_cost;
	int _craft_material_cost;
	int _required_item;

	Ref<EntityResourceCostData> _resource_cost;
	Ref<EntityResourceCostData> _resource_give;

	bool _global_cooldown_enabled;
	bool _is_local_spell;
	Ref<Texture> _icon;

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
