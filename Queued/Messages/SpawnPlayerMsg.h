#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SpawnPlayerMsg : public virtual ValueType
		{
				int PlayerId;
				bool IsLocalPlayer;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SpawnPlayerMsg();
				String* ToString();
		};
	}
}
