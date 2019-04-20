#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendRageMsg : public virtual ValueType
		{
				uint Guid;
				int Current;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendRageMsg();
				String* ToString();
		};
	}
}
