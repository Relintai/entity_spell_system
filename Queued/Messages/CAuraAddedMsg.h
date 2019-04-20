#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CAuraAddedMsg : public virtual ValueType
		{
				uint Guid;
				uint CasterGuid;
				int AuraId;
				float Time;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CAuraAddedMsg();
				String* ToString();
		};
	}
}
