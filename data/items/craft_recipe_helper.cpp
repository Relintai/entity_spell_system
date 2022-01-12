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

#include "craft_recipe_helper.h"

Ref<ItemTemplate> CraftRecipeHelper::get_item() {
	return _item;
}

void CraftRecipeHelper::set_item(Ref<ItemTemplate> value) {
	_item = value;
}

int CraftRecipeHelper::get_count() {
	return _count;
}

void CraftRecipeHelper::set_count(int value) {
	_count = value;
}

CraftRecipeHelper::CraftRecipeHelper(Ref<ItemTemplate> item, int count) {
	set_item(item);
	set_count(count);
}

CraftRecipeHelper::CraftRecipeHelper() {
	set_count(0);
}

CraftRecipeHelper::~CraftRecipeHelper() {
}

void CraftRecipeHelper::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &CraftRecipeHelper::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &CraftRecipeHelper::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_count"), &CraftRecipeHelper::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &CraftRecipeHelper::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");
}
