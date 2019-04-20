#include "CAuraRemovedMsg.h"
namespace BS {
	namespace Networking {
		void CAuraRemovedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1033);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->AuraId);
		}
		void CAuraRemovedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->AuraId = buf->ReadInt();
		}
		CAuraRemovedMsg::CAuraRemovedMsg()
		{
		}
		String* CAuraRemovedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
