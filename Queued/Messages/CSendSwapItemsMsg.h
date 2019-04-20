#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CSendSwapItemsMsg : public virtual ValueType
		{
				int Slot1;
				int Slot2;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CSendSwapItemsMsg();
				String* ToString();
		};
	}
}
