#include "aura_group.h"

AuraGroup::AuraGroup() {
}

void AuraGroup::_bind_methods() {
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description"), "set_name", "get_name");
}
