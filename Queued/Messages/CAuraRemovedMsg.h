#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CAuraRemovedMsg : public virtual ValueType
		{
				uint Guid;
				int AuraId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CAuraRemovedMsg();
				String* ToString();
		};
	}
}
