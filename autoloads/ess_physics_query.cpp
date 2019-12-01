#include "ess_physics_query.h"

ESSPhysicsQuery *ESSPhysicsQuery::instance;

ESSPhysicsQuery *ESSPhysicsQuery::get_instance() {
	return instance;
}

void ESSPhysicsQuery::_notification(int p_what) {

	switch (p_what) {

		case NOTIFICATION_ENTER_TREE: {
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}
}

void ESSPhysicsQuery::_bind_methods() {
}

ESSPhysicsQuery::ESSPhysicsQuery() {
	instance = this;
}

ESSPhysicsQuery::~ESSPhysicsQuery() {
	instance = NULL;
}
