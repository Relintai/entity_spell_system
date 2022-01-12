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

#include "ess_resource_db_folders.h"

#include "../data/items/craft_recipe.h"
#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/data/entity_data.h"
#include "../entities/resources/entity_resource.h"
#include "../entities/skills/entity_skill_data.h"

bool ESSResourceDBFolders::get_automatic_load() const {
	return _automatic_load;
}
void ESSResourceDBFolders::set_automatic_load(const bool load) {
	_automatic_load = load;
}

bool ESSResourceDBFolders::get_load_folders() const {
	return _load_folders;
}
void ESSResourceDBFolders::set_load_folders(const bool load) {
	_load_folders = load;
}

PoolStringArray ESSResourceDBFolders::get_folders() const {
	return _folders;
}
void ESSResourceDBFolders::set_folders(const PoolStringArray &data) {
	_folders = data;
}

void ESSResourceDBFolders::_initialize() {
	load_all();
}

void ESSResourceDBFolders::load_all() {
	load_folders();
}

void ESSResourceDBFolders::load_folders() {
	for (int i = 0; i < _folders.size(); ++i) {
		load_folder(_folders[i]);
	}
}

void ESSResourceDBFolders::load_folder(const String &folder) {
	_Directory dir;

	bool ew = folder.ends_with("/");

	if (dir.open(folder) == OK) {

		dir.list_dir_begin();

		String filename;

		while (true) {
			filename = dir.get_next();

			if (filename == "")
				break;

			if (!dir.current_is_dir()) {
				String path;

				if (ew)
					path = folder + filename;
				else
					path = folder + "/" + filename;

				Ref<Resource> res = load_resource(path);

				ERR_CONTINUE(!res.is_valid());

				add_resource(res);
			}
		}
	} else {
		print_error("An error occurred when trying to access the path.");
	}
}

void ESSResourceDBFolders::add_resource(const Ref<Resource> &resource) {
	StringName cls = resource->get_class_name();

	if (cls == "EntityResource") {
		add_entity_resource(resource);
	} else if (cls == "EntitySkillData") {
		add_entity_skill(resource);
	} else if (cls == "EntityData") {
		add_entity_data(resource);
	} else if (cls == "Spell") {
		add_spell(resource);
	} else if (cls == "CraftRecipe") {
		add_craft_recipe(resource);
	} else if (cls == "ItemTemplate") {
		add_item_template(resource);
	} else if (cls == "EntitySpeciesData") {
		add_entity_species_data(resource);
	}
}

Ref<Resource> ESSResourceDBFolders::load_resource(const String &path, const String &type_hint) {
	_ResourceLoader *rl = _ResourceLoader::get_singleton();

#if VERSION_MAJOR < 4
	Ref<ResourceInteractiveLoader> resl = rl->load_interactive(path, type_hint);

	ERR_FAIL_COND_V(!resl.is_valid(), Ref<Resource>());

	resl->wait();

	return resl->get_resource();
#else
	return rl->load(path, type_hint);
#endif
}

ESSResourceDBFolders::ESSResourceDBFolders() {
	_automatic_load = false;

	_xp_data_path = "";

	if (_automatic_load) {
		call_deferred("load_all");
	}
}

ESSResourceDBFolders::~ESSResourceDBFolders() {
}

void ESSResourceDBFolders::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_automatic_load"), &ESSResourceDBFolders::get_automatic_load);
	ClassDB::bind_method(D_METHOD("set_automatic_load", "load"), &ESSResourceDBFolders::set_automatic_load);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "automatic_load"), "set_automatic_load", "get_automatic_load");

	ClassDB::bind_method(D_METHOD("get_folders"), &ESSResourceDBFolders::get_folders);
	ClassDB::bind_method(D_METHOD("set_folders", "recipe"), &ESSResourceDBFolders::set_folders);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_STRING_ARRAY, "folders"), "set_folders", "get_folders");

	//load
	ClassDB::bind_method(D_METHOD("_initialize"), &ESSResourceDBFolders::_initialize);
	ClassDB::bind_method(D_METHOD("load_all"), &ESSResourceDBFolders::load_all);
	ClassDB::bind_method(D_METHOD("load_folders"), &ESSResourceDBFolders::load_folders);
	ClassDB::bind_method(D_METHOD("load_folder", "folder"), &ESSResourceDBFolders::load_folder);
	ClassDB::bind_method(D_METHOD("add_resource", "resource"), &ESSResourceDBFolders::add_resource);

	ClassDB::bind_method(D_METHOD("load_resource", "path", "type_hint"), &ESSResourceDBFolders::load_resource, DEFVAL(""));
}
