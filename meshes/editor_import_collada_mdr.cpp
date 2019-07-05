#include "editor_import_collada_mdr.h"

String EditorImportColladaMdr::get_importer_name() const {
	return "collada_mdr";
}

String EditorImportColladaMdr::get_visible_name() const {
	return "Collada MDR";
}

void EditorImportColladaMdr::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("dae");
}

String EditorImportColladaMdr::get_save_extension() const {
	return "res";
}

String EditorImportColladaMdr::get_resource_type() const {
	return "MeshDataResource";
}

float EditorImportColladaMdr::get_priority() const {
	return 1.0;
}

int EditorImportColladaMdr::get_preset_count() const {
	return 0;
}

String EditorImportColladaMdr::get_preset_name(int p_idx) const {
	return "";
}

void EditorImportColladaMdr::get_import_options(List<ImportOption> *r_options, int p_preset) const {

}

bool EditorImportColladaMdr::get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const {
	return true;
}

Error EditorImportColladaMdr::import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files, Variant *r_metadata) {
	Node *n = _importer->import_scene(p_source_file, 0, 15);

	if (n == NULL) {
		n->queue_delete();
		return Error::ERR_PARSE_ERROR;
	}

	for (int i = 0; i < n->get_child_count(); ++i) {
		Node *c = n->get_child(i);
		print_error(String::num(i));

		if (c == NULL) {
			continue;
		}

		if (Object::cast_to<MeshInstance>(c)) {
			MeshInstance *mi = Object::cast_to<MeshInstance>(c);

			Ref<ArrayMesh> mesh = mi->get_mesh();

			if (mesh.is_valid()) {
				Ref<MeshDataResource> mdr;
				mdr.instance();

				mdr->set_array(mesh->surface_get_arrays(0));

				n->queue_delete();

				return ResourceSaver::save(p_save_path + "." + get_save_extension(), mdr);
			}
		}
	}

	n->queue_delete();
	return Error::ERR_PARSE_ERROR;
}


EditorImportColladaMdr::EditorImportColladaMdr() {
	_importer.instance();
}

EditorImportColladaMdr::~EditorImportColladaMdr() {
	_importer.unref();
}
