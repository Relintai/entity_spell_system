#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct TickSyncMsg : public virtual ValueType
		{
				int Tick;
				int Timestamp;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				TickSyncMsg();
				String* ToString();
		};
	}
}
