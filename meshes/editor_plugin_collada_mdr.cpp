#include "editor_plugin_collada_mdr.h"

void EditorPluginColladaMdr::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE:
			_importer.instance();

			add_import_plugin(_importer);

			break;
		case NOTIFICATION_EXIT_TREE:
			remove_import_plugin(_importer);

			_importer.unref();

			break;
	}
}

EditorPluginColladaMdr::EditorPluginColladaMdr(EditorNode *node) {
	_node = node;
}
