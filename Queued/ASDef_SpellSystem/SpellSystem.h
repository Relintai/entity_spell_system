#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "SpellScript.h"
#include "AuraScript.h"

using namespace UnityEngine;
using namespace System;
//Attribute: DefaultExecutionOrder*(-1000)
class SpellSystem : public virtual MonoBehaviour, public virtual Object{
	private:
		void Awake();
};
