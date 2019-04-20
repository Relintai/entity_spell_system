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
		struct TeleportMsg : public virtual ValueType
		{
				uint Guid;
				Vector3* position;
				Quaternion* rotation;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				TeleportMsg();
				String* ToString();
		};
	}
}
