#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CStatUpdateMsg : public virtual ValueType
		{
				uint Guid;
				int SpellId;
				SerializationBuffer* Buffer;
				int next;
				void Initialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				void ResetToStats();
				void FinishMessage();
				bool HasNext();
				int Next();
				void Step();
				CStatUpdateMsg();
				String* ToString();
		};
	}
}
