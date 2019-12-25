
#ifndef EDITOR_PLUGIN_COLLADA_MDR
#define EDITOR_PLUGIN_COLLADA_MDR

#include "editor/editor_plugin.h"
#include "core/ustring.h"

#include "editor_import_collada_mdr.h"

class EditorPluginColladaMdr : public EditorPlugin {

	GDCLASS(EditorPluginColladaMdr, EditorPlugin);

public:
	EditorPluginColladaMdr(EditorNode *node);

protected:
	void _notification(int p_what);

private:
	EditorNode *_node;
	Ref<EditorImportColladaMdr> _importer;
};

#endif
