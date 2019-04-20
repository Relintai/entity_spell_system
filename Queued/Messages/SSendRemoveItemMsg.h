#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendRemoveItemMsg : public virtual ValueType
		{
				int SlotId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendRemoveItemMsg();
				String* ToString();
		};
	}
}
