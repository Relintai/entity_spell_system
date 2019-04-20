#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendStateFlagsMsg : public virtual ValueType
		{
				uint Guid;
				int Flags;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendStateFlagsMsg();
				String* ToString();
		};
	}
}
