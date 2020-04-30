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

#ifndef STAT_H
#define STAT_H

#include "core/reference.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "scene/resources/curve.h"

class StatDataEntry;
class Entity;

class Stat : public Reference {
	GDCLASS(Stat, Reference);

public:
	static String stat_id_name(int stat_id);

public:
	int get_id();
	void set_id(int id);

	Ref<StatDataEntry> get_stat_data_entry();
	void set_stat_data_entry(Ref<StatDataEntry> entry);

	Entity *get_owner();
	void set_owner(Entity *value);
	void set_owner_bind(Node *value);

	bool get_dirty();
	void set_dirty(bool value);

	float get_base();
	void set_base(float value);
	void mod_base(float value);

	float get_base_calculated();
	void set_base_calculated(float value);

	float get_bonus();
	void set_bonus(float value);
	void mod_bonus(float value);

	float get_percent();
	void set_percent(float value);
	void mod_percent(float value);

	float gets_current();
	void sets_current(float value);

	float getc_current();
	void setc_current(float value);

	void refresh();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	Stat();
	Stat(int id, Entity *owner);
	~Stat();

protected:
	virtual void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

private:
	int _id;

	bool _dirty;

	float _base;
	float _base_calculated;
	float _bonus;
	float _percent;

	float _s_current;

	float _c_current;

	Entity *_owner;
	Ref<StatDataEntry> _stat_data_entry;
};

#endif
