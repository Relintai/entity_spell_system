
#ifndef EDITOR_IMPORT_COLLADA_MDR
#define EDITOR_IMPORT_COLLADA_MDR

#include "editor/import/editor_import_plugin.h"
#include "core/ustring.h"
#include "scene/main/node.h"
#include "scene/resources/mesh.h"
#include "scene/3d/mesh_instance.h"
#include "core/io/resource_saver.h"
#include "core/array.h"
#include "core/math/basis.h"
#include "core/math/transform.h"

#include "mesh_data_resource.h"
#include "editor/import/editor_import_collada.h"

class EditorImportColladaMdr : public EditorImportPlugin {

	GDCLASS(EditorImportColladaMdr, EditorImportPlugin);

public:
	virtual String get_importer_name() const;
	virtual String get_visible_name() const;
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual String get_save_extension() const;
	virtual String get_resource_type() const;
	virtual float get_priority() const;

	virtual int get_preset_count() const;
	virtual String get_preset_name(int p_idx) const;

	virtual void get_import_options(List<ImportOption> *r_options, int p_preset = 0) const;
	virtual bool get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const;

	virtual Error import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files = NULL, Variant *r_metadata = NULL);

	Array apply_transforms(Array &array, const Map<StringName, Variant> &p_options);

	EditorImportColladaMdr();
	~EditorImportColladaMdr();

private:
	Ref<EditorSceneImporterCollada> _importer;
};

#endif
