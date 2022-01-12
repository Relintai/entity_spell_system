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

#include "spell_follow_projectile_3d.h"

#include "../../infos/spell_cast_info.h"

void SpellFollowProjectile3D::setup_projectile(Ref<SpellCastInfo> info) {
	_info = info;
}

SpellFollowProjectile3D::SpellFollowProjectile3D() {
}
SpellFollowProjectile3D::~SpellFollowProjectile3D() {
	_info.unref();
}

void SpellFollowProjectile3D::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("setup_projectile", "info"), &SpellFollowProjectile3D::setup_projectile);
}
