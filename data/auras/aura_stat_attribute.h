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

#ifndef AURA_STAT_ATTRIBUTE_H
#define AURA_STAT_ATTRIBUTE_H

#include "../../entities/stats/stat.h"
#include "core/reference.h"

#include "../../singletons/ess.h"

class AuraStatAttribute : public Reference {
	GDCLASS(AuraStatAttribute, Reference);

public:
	int get_stat() const { return _stat; }
	void set_stat(int value) { _stat = value; }

	float get_base_mod() const { return _base_mod; }
	void set_base_mod(float value) { _base_mod = value; }

	float get_bonus_mod() const { return _bonus_mod; }
	void set_bonus_mod(float value) { _bonus_mod = value; }

	float get_percent_mod() const { return _percent_mod; }
	void set_percent_mod(float value) { _percent_mod = value; }

	AuraStatAttribute() {
		_stat = 0;
		_base_mod = 0;
		_bonus_mod = 0;
		_percent_mod = 0;
	}

protected:
	void validate_property(PropertyInfo &property) const {
		if (property.name == "stat") {
			property.hint_string = ESS::get_instance()->stat_get_string();
		}
	}

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_stat"), &AuraStatAttribute::get_stat);
		ClassDB::bind_method(D_METHOD("set_stat", "value"), &AuraStatAttribute::set_stat);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "stat", PROPERTY_HINT_ENUM, ""), "set_stat", "get_stat");

		ClassDB::bind_method(D_METHOD("get_base_mod"), &AuraStatAttribute::get_base_mod);
		ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &AuraStatAttribute::set_base_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");

		ClassDB::bind_method(D_METHOD("get_bonus_mod"), &AuraStatAttribute::get_bonus_mod);
		ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &AuraStatAttribute::set_bonus_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

		ClassDB::bind_method(D_METHOD("get_percent_mod"), &AuraStatAttribute::get_percent_mod);
		ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &AuraStatAttribute::set_percent_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");
	}

private:
	int _stat;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
};

#endif
