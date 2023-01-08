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

#ifndef ENTITY_SKILL_H
#define ENTITY_SKILL_H

#include "core/version.h"

#include "core/io/resource.h"


#include "entity_skill_data.h"

class EntitySkill : public Resource {
	GDCLASS(EntitySkill, Resource);

public:
	Ref<EntitySkillData> get_skill();
	void set_skill(Ref<EntitySkillData> value);

	int get_skill_id();
	void set_skill_id(int value);

	int get_current();
	void set_current(int value);

	int get_max();
	void set_max(int value);

	bool get_disabled();
	void set_disabled(bool value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	EntitySkill();
	~EntitySkill();

protected:
	static void _bind_methods();

private:
	Ref<EntitySkillData> _skill;
	int _skill_id;
	StringName _skill_path;
	int _current;
	int _max;
	bool _disabled;
};

#endif
