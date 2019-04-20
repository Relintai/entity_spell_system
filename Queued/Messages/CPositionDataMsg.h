#pragma once
#include <System/System.h>
#include "Vector3.h"
#include "Quaternion.h"
#include "SerializationBuffer.h"

using namespace UnityEngine;
using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CPositionDataMsg : public virtual ValueType
		{
				Vector3* Position;
				Quaternion* Rotation;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CPositionDataMsg();
				String* ToString();
		};
	}
}
