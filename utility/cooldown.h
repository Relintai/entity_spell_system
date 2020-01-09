#ifndef COOLDOWN_H
#define COOLDOWN_H

#include "core/reference.h"

class Cooldown : public Reference {
	GDCLASS(Cooldown, Reference);

public:
	int get_spell_id() const;
	void set_spell_id(const int value);

	float get_remaining() const;
	void set_remaining(const float value);

	bool update(const float delta);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

protected:
	static void _bind_methods();

private:
	int _spell_id;
	float _remaining;
};

#endif
