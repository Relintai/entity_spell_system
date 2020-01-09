#ifndef INPUT_PROFILE_H
#define INPUT_PROFILE_H

#include "core/reference.h"
#include "core/ustring.h"

class InputProfile : public Reference {
	GDCLASS(InputProfile, Reference);

public:
	InputProfile() {}

protected:
	static void _bind_methods() {}

private:
	int placeholder;
};

#endif
