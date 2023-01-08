/*
Copyright (c) 2020-2022 Péter Magyar

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

#include "ess_editor_plugin.h"

#include "core/version.h"

void ESSEditorPlugin::fix_ids(Variant param) {
}

ESSEditorPlugin::ESSEditorPlugin(EditorNode *p_node) {
	editor = p_node;

	//editor->add_tool_menu_item("ESS: make ids unique", this, "fix_ids");

}

ESSEditorPlugin::~ESSEditorPlugin() {
}

void ESSEditorPlugin::_bind_methods() {
	ClassDB::bind_method(D_METHOD("fix_ids"), &ESSEditorPlugin::fix_ids);
}
