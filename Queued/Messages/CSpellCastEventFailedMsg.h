#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CSpellCastEventFailedMsg : public virtual ValueType
		{
				uint Guid;
				int SpellId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CSpellCastEventFailedMsg();
				String* ToString();
		};
	}
}
