#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendAddResourceMsg : public virtual ValueType
		{
				uint Guid;
				int Type;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendAddResourceMsg();
				String* ToString();
		};
	}
}
