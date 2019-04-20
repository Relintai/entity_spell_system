#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"

using namespace UnityEngine;
using namespace System;
class EffectAuraIdAttribute : public virtual MonoBehaviour, public virtual Object
{
	private:
		int auraid;
	public:
		int getAuraId();
	public:
		void setAuraId(int value);
};
