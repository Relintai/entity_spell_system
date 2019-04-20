#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CSendRequestRankDecreaseMsg : public virtual ValueType
		{
				uint Guid;
				int TalentId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CSendRequestRankDecreaseMsg();
				String* ToString();
		};
	}
}
