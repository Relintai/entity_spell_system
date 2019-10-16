#ifndef LEVEL_XP_H
#define LEVEL_XP_H

#include "core/resource.h"
#include "core/variant.h"
#include "core/vector.h"

class XPData : public Resource {
	GDCLASS(XPData, Resource);

public:
	int get_max_level();
	int get_xp(int level);
	void set_xp(int level, int value);
	bool can_level_up(int level);

	XPData();
	~XPData();

protected:
	static void _bind_methods();

private:
	Vector<int> _xps;
};

#endif
