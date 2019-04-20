#pragma once
#include <System/System.h>
#include "Vector2.h"
#include "SerializationBuffer.h"

using namespace UnityEngine;
using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CMovementDataMsg : public virtual ValueType
		{
				Vector2* Axes;
				float Speed;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CMovementDataMsg();
				String* ToString();
		};
	}
}
