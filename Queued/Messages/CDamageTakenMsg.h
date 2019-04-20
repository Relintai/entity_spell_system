#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CDamageTakenMsg : public virtual ValueType
		{
				uint Guid;
				uint DealerGuid;
				int Value;
				bool Crit;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CDamageTakenMsg();
				String* ToString();
		};
	}
}
