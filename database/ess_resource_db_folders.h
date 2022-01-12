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

#ifndef ESS_RESOURCE_DB_FOLDERS_H
#define ESS_RESOURCE_DB_FOLDERS_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/variant/variant.h"
#include "core/templates/vector.h"
#include "core/templates/hash_map.h"
#include "core/string/ustring.h"
#include "core/config/engine.h"
#include "core/variant/array.h"
#include "core/core_bind.h"
#else
#include "core/variant.h"
#include "core/vector.h"
#include "core/hash_map.h"
#include "core/ustring.h"
#include "core/engine.h"
#include "core/array.h"
#include "core/bind/core_bind.h"
#endif

#include "ess_resource_db_map.h"

#include "scene/main/node.h"

#include "../item_enums.h"

#include "../defines.h"

class Spell;
class EntityData;
class CraftRecipe;
class ItemTemplate;
class EntityResource;
class EntitySkillData;
class EntityCreateInfo;
class SpellCastInfo;
class EntitySpeciesData;

class ESSResourceDBFolders : public ESSResourceDBMap {
	GDCLASS(ESSResourceDBFolders, ESSResourceDBMap);

public:
	bool get_automatic_load() const;
	void set_automatic_load(const bool load);

	bool get_load_folders() const;
	void set_load_folders(const bool load);

	PoolStringArray get_folders() const;
	void set_folders(const PoolStringArray &folders);

	virtual void _initialize();
	void load_all();
	void load_folders();
	void load_folder(const String &folder);
	void add_resource(const Ref<Resource> &resource);

	Ref<Resource> load_resource(const String &path, const String &type_hint = "");

	ESSResourceDBFolders();
	~ESSResourceDBFolders();

protected:
	static void _bind_methods();

private:
	String _xp_data_path;

	PoolStringArray _folders;

	bool _automatic_load;
	bool _load_folders;
};

#endif
