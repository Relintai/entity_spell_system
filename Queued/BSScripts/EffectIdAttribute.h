#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"

using namespace UnityEngine;
using namespace System;
class EffectIdAttribute : public virtual MonoBehaviour, public virtual Object
{
	private:
		int id;
	public:
		int getId();
	public:
		void setId(int value);
};
