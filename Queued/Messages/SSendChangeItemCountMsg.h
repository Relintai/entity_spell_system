#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendChangeItemCountMsg : public virtual ValueType
		{
				int SlotId;
				int Count;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendChangeItemCountMsg();
				String* ToString();
		};
	}
}
