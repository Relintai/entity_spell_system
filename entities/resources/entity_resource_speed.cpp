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

#include "entity_resource_speed.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"
#include "../entity.h"
#include "entity_resource.h"

void EntityResourceSpeed::_init() {
	set_current_value(base_value);

	speed_stat_id = 0;

	if (ESS::get_singleton()->stat_is_property("Speed"))
		speed_stat_id = ESS::get_singleton()->stat_get_id("Speed");
}
void EntityResourceSpeed::_ons_added(Node *entity) {
	refresh();
}
void EntityResourceSpeed::_notification_sstat_changed(int statid, float current) {
	if (statid == speed_stat_id)
		refresh();
}
void EntityResourceSpeed::refresh() {
	ERR_FAIL_COND(get_owner() == NULL);

	float speed_stat = get_owner()->stat_gets_current(speed_stat_id);

	set_max_value(base_value + speed_stat * 0.01);
	set_current_value(base_value + speed_stat * 0.01);
}

void EntityResourceSpeed::resolve_references() {
}

EntityResourceSpeed::EntityResourceSpeed() {
	speed_stat_id = 0;
	base_value = 100;
}

EntityResourceSpeed::~EntityResourceSpeed() {
}

void EntityResourceSpeed::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_init"), &EntityResourceSpeed::_init);
	ClassDB::bind_method(D_METHOD("_ons_added", "entity"), &EntityResourceSpeed::_ons_added);
	ClassDB::bind_method(D_METHOD("_notification_sstat_changed", "statid", "current"), &EntityResourceSpeed::_notification_sstat_changed);
	ClassDB::bind_method(D_METHOD("refresh"), &EntityResourceSpeed::refresh);
}
