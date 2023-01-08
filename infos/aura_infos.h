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

#ifndef AURA_INFOS_H
#define AURA_INFOS_H

#include "core/version.h"

#include "core/object/ref_counted.h"


#include "../entities/entity.h"

class Entity;
class Spell;

class AuraApplyInfo : public RefCounted {
	GDCLASS(AuraApplyInfo, RefCounted);

public:
	Entity *caster_get() const;
	void caster_set(Entity *caster);
	void caster_set_bind(Node *caster);

	Entity *target_get() const;
	void target_set(Entity *caster);
	void target_set_bind(Node *caster);

	float spell_scale_get() const;
	void spell_scale_set(float value);

	Ref<Spell> get_aura() const;
	void set_aura(Ref<Spell> aura);

	AuraApplyInfo();
	AuraApplyInfo(Entity *_caster, Entity *_target, float _spell_scale, Spell *_aura);
	AuraApplyInfo(Entity *_caster, Entity *_target, float _spell_scale);

protected:
	static void _bind_methods();

private:
	Entity *_caster;
	Entity *_target;
	float _spell_scale;
	Spell *_aura;
};

#endif
