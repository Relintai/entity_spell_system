#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CHealTakenMsg : public virtual ValueType
		{
				uint Guid;
				uint DealerGuid;
				int Value;
				bool Crit;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CHealTakenMsg();
				String* ToString();
		};
	}
}
