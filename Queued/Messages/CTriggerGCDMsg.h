#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CTriggerGCDMsg : public virtual ValueType
		{
				uint Guid;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CTriggerGCDMsg();
				String* ToString();
		};
	}
}
