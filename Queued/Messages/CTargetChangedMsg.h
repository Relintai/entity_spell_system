#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CTargetChangedMsg : public virtual ValueType
		{
				uint Guid;
				uint TargetGuid;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CTargetChangedMsg();
				String* ToString();
		};
	}
}
