#ifndef TALENT_H
#define TALENT_H

#include "core/resource.h"
#include "core/ustring.h"

#include "aura.h"

class Spell;

class Talent : public Aura {
	GDCLASS(Talent, Aura);

public:
	Ref<Talent> get_required_talent() const;
	void set_required_talent(const Ref<Talent> rank);

	Ref<Spell> get_required_spell() const;
	void set_required_spell(const Ref<Spell> spell);

	Ref<Spell> get_teaches_spell() const;
	void set_teaches_spell(const Ref<Spell> spell);

	Ref<Aura> get_apply_aura() const;
	void set_apply_aura(Ref<Aura> aura);

	Talent();
	~Talent();

protected:
	static void _bind_methods();

private:
	Ref<Talent> _required_talent;
	Ref<Spell> _required_spell;
	Ref<Spell> _teaches_spell;

	Ref<Aura> _aura;
};

#endif
