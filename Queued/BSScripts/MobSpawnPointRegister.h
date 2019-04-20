#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "MobSpawner.h"

using namespace UnityEngine;
using namespace System;
class MobSpawnPointRegister : public virtual MonoBehaviour, public virtual Object
{
	private:
		void Start();
};
