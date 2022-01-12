/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "entity_resource_health.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"
#include "../entity.h"
#include "entity_resource.h"

void EntityResourceHealth::_init() {
	set_current_value(100);
	stamina_stat_id = 0;
	health_stat_id = 0;

	if (ESS::get_singleton()->stat_is_property("Stamina")) {
		stamina_stat_id = ESS::get_singleton()->stat_get_id("Stamina");
	}

	if (ESS::get_singleton()->stat_is_property("Health")) {
		health_stat_id = ESS::get_singleton()->stat_get_id("Health");
	}
}
void EntityResourceHealth::_ons_added(Node *entity) {
	refresh();
}
void EntityResourceHealth::_notification_sstat_changed(int statid, float current) {
	if (statid == stamina_stat_id || statid == health_stat_id)
		refresh();
}
void EntityResourceHealth::refresh() {
	ERR_FAIL_COND(get_owner() == NULL);

	float stamina = get_owner()->stat_gets_current(stamina_stat_id);
	float health = get_owner()->stat_gets_current(health_stat_id);

	int val = int(stamina) * 10 + int(health);

	set_max_value(val);
	set_current_value(val);
}

void EntityResourceHealth::resolve_references() {
}

EntityResourceHealth::EntityResourceHealth() {
	stamina_stat_id = 0;
	health_stat_id = 0;
}

EntityResourceHealth::~EntityResourceHealth() {
}

void EntityResourceHealth::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_init"), &EntityResourceHealth::_init);
	ClassDB::bind_method(D_METHOD("_ons_added", "entity"), &EntityResourceHealth::_ons_added);
	ClassDB::bind_method(D_METHOD("_notification_sstat_changed", "statid", "current"), &EntityResourceHealth::_notification_sstat_changed);
	ClassDB::bind_method(D_METHOD("refresh"), &EntityResourceHealth::refresh);
}
