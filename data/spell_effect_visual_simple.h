#ifndef SPELL_EFFECT_VISUAL_SIMPLE_H
#define SPELL_EFFECT_VISUAL_SIMPLE_H

#include "spell_effect_visual.h"

#include "scene/resources/packed_scene.h"

#include "../entity_enums.h"

class SpellEffectVisualSimple : public SpellEffectVisual {
	GDCLASS(SpellEffectVisualSimple, SpellEffectVisual);

public:
	bool has_spell_effect_visual();

	EntityEnums::CharacterSkeletonPoints get_spell_effect_visual_point();
	void set_spell_effect_visual_point(EntityEnums::CharacterSkeletonPoints point);

	Ref<PackedScene> get_spell_effect_visual();
	void set_spell_effect_visual(Ref<PackedScene> value);

	bool has_spell_cast_finish_effect();

	EntityEnums::CharacterSkeletonPoints get_spell_cast_finish_effect_point();
	void set_spell_cast_finish_effect_point(EntityEnums::CharacterSkeletonPoints point);

	Ref<PackedScene> get_spell_cast_finish_effect();
	void set_spell_cast_finish_effect(Ref<PackedScene> value);

	bool has_spell_cast_effect();
	Ref<PackedScene> get_spell_cast_effect();
	void set_spell_cast_effect(Ref<PackedScene> value);

	//VisualEffect
	bool has_aura_effect_visual();

	EntityEnums::CharacterSkeletonPoints get_aura_effect_visual_point();
	void set_aura_effect_visual_point(EntityEnums::CharacterSkeletonPoints point);

	Ref<PackedScene> get_aura_effect_visual();
	void set_aura_effect_visual(Ref<PackedScene> value);

	SpellEffectVisualSimple();
	~SpellEffectVisualSimple();

protected:
	static void _bind_methods();

private:
	EntityEnums::CharacterSkeletonPoints _effect_visual_point;
	Ref<PackedScene> _effect_visual;

	EntityEnums::CharacterSkeletonPoints _spell_cast_finish_effect_point;
	Ref<PackedScene> _spell_cast_finish_effect;

	Ref<PackedScene> _spell_cast_effect;

	EntityEnums::CharacterSkeletonPoints _aura_effect_visual_point;
	Ref<PackedScene> _aura_effect_visual;
};

#endif
