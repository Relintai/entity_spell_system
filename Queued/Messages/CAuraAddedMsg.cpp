#include "CAuraAddedMsg.h"
namespace BS {
	namespace Networking {
		void CAuraAddedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1032);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->CasterGuid);
			buf->WriteInt(this->AuraId);
			buf->WriteFloat(this->Time);
		}
		void CAuraAddedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->CasterGuid = buf->ReadUInt();
			this->AuraId = buf->ReadInt();
			this->Time = buf->ReadFloat();
		}
		CAuraAddedMsg::CAuraAddedMsg()
		{
		}
		String* CAuraAddedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
