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

#ifndef ENTITY_DATA_MANAGER_H
#define ENTITY_DATA_MANAGER_H

#include "core/object.h"

#include "core/engine.h"

#include "core/resource.h"
#include "core/ustring.h"
#include "scene/main/node.h"

#include "core/bind/core_bind.h"

class ESSResourceDB;
class EntityCreateInfo;

class EntityDataManager : public Object {
	GDCLASS(EntityDataManager, Object);

public:
	static EntityDataManager *get_instance();

	bool get_use_spell_points() const;
	void set_use_spell_points(const bool value);

	bool get_scale_spells_by_default() const;
	void set_scale_spells_by_default(const bool value);

	bool get_automatic_load() const;
	void set_automatic_load(const bool load);

	bool get_load_folders() const;
	void set_load_folders(const bool load);

	bool get_use_class_xp() const;
	void set_use_class_xp(const bool value);

	bool get_automatic_class_levelups() const;
	void set_automatic_class_levelups(const bool value);

	bool get_use_global_class_level() const;
	void set_use_global_class_level(const bool value);

	bool get_allow_class_spell_learning() const;
	void set_allow_class_spell_learning(const bool value);

	bool get_allow_class_recipe_learning() const;
	void set_allow_class_recipe_learning(const bool value);

	String get_resource_db_path();
	void set_resource_db_path(String path);
	Ref<ESSResourceDB> get_resource_db();
	void load_resource_db();
	Ref<Resource> load_resource(const String &path, const String &type_hint = "");

	void request_entity_spawn(const Ref<EntityCreateInfo> &info);
	void request_entity_spawn_deferred(const Ref<EntityCreateInfo> &info);

	EntityDataManager();
	~EntityDataManager();

protected:
	static void _bind_methods();

private:
	bool _automatic_load;
	String _ess_resource_db_path;
	Ref<ESSResourceDB> _ess_resource_db;

	static EntityDataManager *instance;

	bool _use_spell_points;
	bool _scale_spells_by_default;
	bool _automatic_class_levelups;
	bool _use_global_class_level;
	bool _use_class_xp;
	bool _allow_class_spell_learning;
	bool _allow_class_recipe_learning;
};

#endif
