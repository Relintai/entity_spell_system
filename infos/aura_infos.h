#ifndef AURA_INFOS_H
#define AURA_INFOS_H

#include "core/reference.h"
#include "../entities/entity.h"

class Entity;
class Aura;

class AuraApplyInfo : public Reference {
	GDCLASS(AuraApplyInfo, Reference);

public:
	Entity *get_caster() const;
	void set_caster(Node *caster);

	Entity *get_target() const;
	void set_target(Node *caster);


	float get_spell_scale() const;
	void set_spell_scale(float value);

	Ref<Aura> get_aura() const;
	void set_aura(Ref<Aura> aura);

	AuraApplyInfo();
	AuraApplyInfo(Entity *_caster, Entity *_target, float _spell_scale, Aura *_aura);
	AuraApplyInfo(Entity *_caster, Entity *_target, float _spell_scale);

protected:
	static void _bind_methods();

private:
	Entity *_caster;
	Entity *_target;
	float _spell_scale;
	Aura *_aura;
};


#endif
