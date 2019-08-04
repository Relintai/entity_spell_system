#ifndef CATEGORY_COOLDOWN_H
#define CATEGORY_COOLDOWN_H

#include "core/reference.h"

class CategoryCooldown : public Reference {
	GDCLASS(CategoryCooldown, Reference);

public:
	int get_category_id() const;
	void set_category_id(const int value);

	float get_remaining() const;
	void set_remaining(const float value);
    
    bool update(const float delta);

protected:
	static void _bind_methods();

private:
	int _category_id;
	float _remaining;
};

#endif
