/*
Copyright (c) 2019-2020 Péter Magyar

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

#include "item_template_stat_modifier.h"

Stat::StatId ItemTemplateStatModifier::get_stat_id() const {
	return _stat_id;
}

void ItemTemplateStatModifier::set_stat_id(const Stat::StatId value) {
	_stat_id = value;
}

float ItemTemplateStatModifier::get_min_base_mod() const {
	return _min_mod_max;
}

void ItemTemplateStatModifier::set_min_base_mod(const float value) {
	_min_mod_max = value;
}

float ItemTemplateStatModifier::get_max_base_mod() const {
	return _max_mod_max;
}

void ItemTemplateStatModifier::set_max_base_mod(const float value) {
	_max_mod_max = value;
}

float ItemTemplateStatModifier::get_min_bonus_mod() const {
	return _min_mod_max;
}

void ItemTemplateStatModifier::set_min_bonus_mod(const float value) {
	_min_mod_max = value;
}

float ItemTemplateStatModifier::get_max_bonus_mod() const {
	return _max_mod_max;
}

void ItemTemplateStatModifier::set_max_bonus_mod(const float value) {
	_max_mod_max = value;
}

float ItemTemplateStatModifier::get_min_percent_mod() const {
	return _min_mod_precent;
}

void ItemTemplateStatModifier::set_min_percent_mod(const float value) {
	_min_mod_precent = value;
}

float ItemTemplateStatModifier::get_max_percent_mod() const {
	return _max_mod_precent;
}

void ItemTemplateStatModifier::set_max_percent_mod(const float value) {
	_max_mod_precent = value;
}

float ItemTemplateStatModifier::get_scaling_factor() const {
	return _scaling_factor;
}

void ItemTemplateStatModifier::set_scaling_factor(const float value) {
	_scaling_factor = value;
}

ItemTemplateStatModifier::ItemTemplateStatModifier() {
	_stat_id = Stat::STAT_ID_HEALTH;
	_min_mod_max = 0;
	_max_mod_max = 0;
	_min_mod_precent = 0;
	_max_mod_precent = 0;
	_scaling_factor = 1;
}

void ItemTemplateStatModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_stat_id"), &ItemTemplateStatModifier::get_stat_id);
	ClassDB::bind_method(D_METHOD("set_stat_id", "value"), &ItemTemplateStatModifier::set_stat_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_stat_id", "get_stat_id");

	ClassDB::bind_method(D_METHOD("get_min_base_mod"), &ItemTemplateStatModifier::get_min_base_mod);
	ClassDB::bind_method(D_METHOD("set_min_base_mod", "value"), &ItemTemplateStatModifier::set_min_base_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "min_base_mod"), "set_min_base_mod", "get_min_base_mod");

	ClassDB::bind_method(D_METHOD("get_max_base_mod"), &ItemTemplateStatModifier::get_max_base_mod);
	ClassDB::bind_method(D_METHOD("set_max_base_mod", "value"), &ItemTemplateStatModifier::set_max_base_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_base_mod"), "set_max_base_mod", "get_max_base_mod");

	ClassDB::bind_method(D_METHOD("get_min_bonus_mod"), &ItemTemplateStatModifier::get_min_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_min_bonus_mod", "value"), &ItemTemplateStatModifier::set_min_bonus_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "min_bonus_mod"), "set_min_bonus_mod", "get_min_bonus_mod");

	ClassDB::bind_method(D_METHOD("get_max_bonus_mod"), &ItemTemplateStatModifier::get_max_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_max_bonus_mod", "value"), &ItemTemplateStatModifier::set_max_bonus_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_bonus_mod"), "set_max_bonus_mod", "get_max_bonus_mod");

	ClassDB::bind_method(D_METHOD("get_min_percent_mod"), &ItemTemplateStatModifier::get_min_percent_mod);
	ClassDB::bind_method(D_METHOD("set_min_percent_mod", "value"), &ItemTemplateStatModifier::set_min_percent_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "min_percent_mod"), "set_min_percent_mod", "get_min_percent_mod");

	ClassDB::bind_method(D_METHOD("get_max_percent_mod"), &ItemTemplateStatModifier::get_max_percent_mod);
	ClassDB::bind_method(D_METHOD("set_max_percent_mod", "value"), &ItemTemplateStatModifier::set_max_percent_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_percent_mod"), "set_max_percent_mod", "get_max_percent_mod");

	ClassDB::bind_method(D_METHOD("get_scaling_factor"), &ItemTemplateStatModifier::get_scaling_factor);
	ClassDB::bind_method(D_METHOD("set_scaling_factor", "value"), &ItemTemplateStatModifier::set_scaling_factor);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scaling_factor"), "set_scaling_factor", "get_scaling_factor");
}
