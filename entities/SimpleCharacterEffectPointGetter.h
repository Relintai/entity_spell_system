#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "IEffectPointGetter.h"
#include "EffectPoints.h"
#include "Transform.h"

using namespace UnityEngine;
using namespace System;
namespace BS {
	namespace Player {
		class SimpleCharacterEffectPointGetter : public virtual MonoBehaviour, public virtual IEffectPointGetter, public virtual Object
		{
			public:
				Transform* GetEffectPoint(EffectPoints bodyPartEffectPoint);
		};
	}
}
