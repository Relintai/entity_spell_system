#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Vector3.h"
#include "Transform.h"

using namespace UnityEngine;
using namespace System;
class SpellEffectStartPosition : public virtual MonoBehaviour, public virtual Object
{
	public:
		Vector3* startPosition;
	public:
		Vector3* getStartPosition();
	public:
		void setStartPosition(Vector3* value);
	public:
		void SetSartPosition(Transform* start);
};
