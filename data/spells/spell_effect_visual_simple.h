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

#ifndef SPELL_EFFECT_VISUAL_SIMPLE_H
#define SPELL_EFFECT_VISUAL_SIMPLE_H

#include "spell_effect_visual.h"

#include "scene/resources/packed_scene.h"

#include "../../entity_enums.h"

class SpellEffectVisualSimple : public SpellEffectVisual {
	GDCLASS(SpellEffectVisualSimple, SpellEffectVisual);

public:
	bool has_spell_effect_visual();

	EntityEnums::CommonCharacterSkeletonPoints get_spell_effect_visual_point();
	void set_spell_effect_visual_point(EntityEnums::CommonCharacterSkeletonPoints point);

	Ref<PackedScene> get_spell_effect_visual();
	void set_spell_effect_visual(Ref<PackedScene> value);

	bool has_spell_cast_finish_effect();

	EntityEnums::CommonCharacterSkeletonPoints get_spell_cast_finish_effect_point();
	void set_spell_cast_finish_effect_point(EntityEnums::CommonCharacterSkeletonPoints point);

	Ref<PackedScene> get_spell_cast_finish_effect();
	void set_spell_cast_finish_effect(Ref<PackedScene> value);

	bool has_spell_cast_effect();
	Ref<PackedScene> get_spell_cast_effect();
	void set_spell_cast_effect(Ref<PackedScene> value);

	//VisualEffect
	bool has_aura_effect_visual();

	EntityEnums::CommonCharacterSkeletonPoints get_aura_effect_visual_point();
	void set_aura_effect_visual_point(EntityEnums::CommonCharacterSkeletonPoints point);

	Ref<PackedScene> get_aura_effect_visual();
	void set_aura_effect_visual(Ref<PackedScene> value);

	SpellEffectVisualSimple();
	~SpellEffectVisualSimple();

protected:
	static void _bind_methods();

private:
	EntityEnums::CommonCharacterSkeletonPoints _effect_visual_point;
	Ref<PackedScene> _effect_visual;

	EntityEnums::CommonCharacterSkeletonPoints _spell_cast_finish_effect_point;
	Ref<PackedScene> _spell_cast_finish_effect;

	Ref<PackedScene> _spell_cast_effect;

	EntityEnums::CommonCharacterSkeletonPoints _aura_effect_visual_point;
	Ref<PackedScene> _aura_effect_visual;
};

#endif
