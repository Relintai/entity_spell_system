#include "craft_data_attribute.h"

#if ENTITY_MEM_TOOLS
int CraftDataAttribute::allocs = 0;
#endif

const String CraftDataAttribute::BINDING_STRING_CRAFT_CATEGORIES = "None, Alchemy";
const String CraftDataAttribute::BINDING_STRING_CRAFT_SUB_CATEGORIES = "None, Potions";

int CraftDataAttribute::get_id() {
	return _id;
}

void CraftDataAttribute::set_id(int value) {
	_id = value;
}

CraftDataAttribute::CraftCategories CraftDataAttribute::get_category() {
	return _category;
}

void CraftDataAttribute::set_category(CraftCategories value) {
	_category = value;
}

CraftDataAttribute::CraftSubCategories CraftDataAttribute::get_sub_category() {
	return _sub_category;
}

void CraftDataAttribute::set_sub_category(CraftSubCategories value) {
	_sub_category = value;
}

Ref<CraftDataAttributeHelper> CraftDataAttribute::get_required_tool(int index) {
	return _required_tools[index];
}

void CraftDataAttribute::set_required_tool(int index, const Ref<CraftDataAttributeHelper> value) {
	_required_tools[index] = value;
}

int CraftDataAttribute::get_required_tools_count() {
	return _required_tools_count;
}

void CraftDataAttribute::set_required_tools_count(int value) {
	_required_tools_count = value;
}


void CraftDataAttribute::set_required_material(int index, const Ref<CraftDataAttributeHelper> value) {
	_required_materials[index] = value;
}

Ref<CraftDataAttributeHelper> CraftDataAttribute::get_required_material(int index) {
	return _required_materials[index];
}


int CraftDataAttribute::get_required_materials_count() {
	return _required_materials_count;
}

void CraftDataAttribute::set_required_materials_count(int value) {
	_required_materials_count = value;
}

Ref<CraftDataAttributeHelper> CraftDataAttribute::get_item() {
	return _item;
}

void CraftDataAttribute::set_item(Ref<CraftDataAttributeHelper> value) {
	_item = value;
}

CraftDataAttribute::CraftDataAttribute() {
	_id = 0;
	_category = CraftCategories::CRAFT_CATEGORY_NONE;
	_sub_category = CraftSubCategories::CRAFT_SUB_CATEGORY_NONE;
	//_item = Ref<CraftDataAttributeHelper>(memnew(CraftDataAttributeHelper()));
	_required_materials_count = 0;
	_required_tools_count = 0;

	//for (int i = 0; i < MAX_REQUIRED_TOOLS; ++i) {
	//	_required_tools[i] = Ref<CraftDataAttributeHelper>(memnew(CraftDataAttributeHelper()));
	//}

	//for (int i = 0; i < MAX_REQUIRED_MATERIALS; ++i) {
	//	_required_materials[i] = Ref<CraftDataAttributeHelper>(memnew(CraftDataAttributeHelper()));
	//}

#if ENTITY_MEM_TOOLS
	CraftDataAttribute::allocs++;
	print_error("CraftDataAttribute alloc " + String::num(CraftDataAttribute::allocs));
#endif
}

CraftDataAttribute::~CraftDataAttribute() {
	//TODO check if the array destrutors actually unref the objects.

	//_item = Ref<CraftDataAttributeHelper>(NULL);

#if ENTITY_MEM_TOOLS
	CraftDataAttribute::allocs--;
	print_error("CraftDataAttributede alloc " + String::num(CraftDataAttribute::allocs));
#endif
}

void CraftDataAttribute::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("RequiredMaterials_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _required_materials_count) {
			property.usage = 0;
		}
	} else if (prop.begins_with("RequiredTools_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _required_tools_count) {
			property.usage = 0;
		}
	}
}

void CraftDataAttribute::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &CraftDataAttribute::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &CraftDataAttribute::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_category"), &CraftDataAttribute::get_category);
	ClassDB::bind_method(D_METHOD("set_category", "value"), &CraftDataAttribute::set_category);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "category", PROPERTY_HINT_ENUM, CraftDataAttribute::BINDING_STRING_CRAFT_CATEGORIES), "set_category", "get_category");

	ClassDB::bind_method(D_METHOD("get_sub_category"), &CraftDataAttribute::get_sub_category);
	ClassDB::bind_method(D_METHOD("set_sub_category", "value"), &CraftDataAttribute::set_sub_category);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sub_category", PROPERTY_HINT_ENUM, CraftDataAttribute::BINDING_STRING_CRAFT_SUB_CATEGORIES), "set_sub_category", "get_sub_category");

	ClassDB::bind_method(D_METHOD("get_required_material"), &CraftDataAttribute::get_required_material);
	ClassDB::bind_method(D_METHOD("set_required_material", "mat"), &CraftDataAttribute::set_required_material);

	ClassDB::bind_method(D_METHOD("get_required_materials_count"), &CraftDataAttribute::get_required_materials_count);
	ClassDB::bind_method(D_METHOD("set_required_materials_count", "count"), &CraftDataAttribute::set_required_materials_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "required_materials_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_REQUIRED_MATERIALS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_required_materials_count", "get_required_materials_count");

	for (int i = 0; i < MAX_REQUIRED_MATERIALS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "RequiredMaterials_" + itos(i) + "", PROPERTY_HINT_RESOURCE_TYPE, "CraftDataAttributeHelper", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_required_material", "get_required_material", i);
	}

	ClassDB::bind_method(D_METHOD("get_required_tool"), &CraftDataAttribute::get_required_tool);
	ClassDB::bind_method(D_METHOD("set_required_tool", "value"), &CraftDataAttribute::set_required_tool);

	ClassDB::bind_method(D_METHOD("get_required_tools_count"), &CraftDataAttribute::get_required_tools_count);
	ClassDB::bind_method(D_METHOD("set_required_tools_count", "value"), &CraftDataAttribute::set_required_tools_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "required_tools_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_REQUIRED_TOOLS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_required_tools_count", "get_required_tools_count");

	for (int i = 0; i < MAX_REQUIRED_TOOLS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "RequiredTools_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "CraftDataAttributeHelper", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_required_tool", "get_required_tool", i);
	}

	ClassDB::bind_method(D_METHOD("get_item"), &CraftDataAttribute::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &CraftDataAttribute::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "CraftDataAttributeHelper"), "set_item", "get_item");

	BIND_CONSTANT(MAX_REQUIRED_TOOLS);
	BIND_CONSTANT(MAX_REQUIRED_MATERIALS);

	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_NONE);
	BIND_ENUM_CONSTANT(CRAFT_CATEGORY_ALCHEMY);

	BIND_ENUM_CONSTANT(CRAFT_SUB_CATEGORY_NONE);
	BIND_ENUM_CONSTANT(CRAFT_SUB_CATEGORY_POTIONS);
}
