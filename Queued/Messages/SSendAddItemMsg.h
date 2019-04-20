#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendAddItemMsg : public virtual ValueType
		{
				int SlotId;
				int ItemId;
				int Count;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendAddItemMsg();
				String* ToString();
		};
	}
}
