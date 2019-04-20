#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendMoveItemMsg : public virtual ValueType
		{
				int Slot1;
				int Slot2;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendMoveItemMsg();
				String* ToString();
		};
	}
}
