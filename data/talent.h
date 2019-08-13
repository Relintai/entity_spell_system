#ifndef TALENT_H
#define TALENT_H

#include "core/resource.h"
#include "core/ustring.h"

#include "aura.h"

class Talent : public Aura {
	GDCLASS(Talent, Aura);

public:
	Ref<Talent> get_next_rank() const;
	void set_next_rank(const Ref<Talent> rank);

	Ref<Aura> get_apply_aura() const { return _aura; }
	void set_apply_aura(Ref<Aura> aura) { _aura = Ref<Aura>(aura); }

	Talent();
	~Talent();

protected:
	static void _bind_methods();

private:
	Ref<Talent> _next_rank;

	Ref<Aura> _aura;
};

#endif
