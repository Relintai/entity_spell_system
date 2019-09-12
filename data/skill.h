#ifndef TALENT_H
#define TALENT_H

#include "core/resource.h"
#include "core/ustring.h"

#include "aura.h"

class Skill : public Aura {
	GDCLASS(Skill, Aura);

public:

	Skill();
	~Skill();

protected:
	static void _bind_methods();

private:

};

#endif
