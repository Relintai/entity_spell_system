#ifndef CATEGORY_COOLDOWN_H
#define CATEGORY_COOLDOWN_H

#include "core/reference.h"

class CategoryCooldown : public Reference {
	GDCLASS(CategoryCooldown, Reference);

public:
	int get_category_id();
	void set_category_id(int value);

	int get_remaining();
	void set_remaining(int value);

protected:
	static void _bind_methods();

private:
	int _category_id;
	int _remaining;
};

#endif
