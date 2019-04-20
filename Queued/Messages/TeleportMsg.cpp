#include "TeleportMsg.h"
namespace BS {
	namespace Networking {
		void TeleportMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1009);
			buf->WriteUInt(this->Guid);
			buf->WriteVector3(this->position);
			buf->WriteQuaternion(this->rotation);
		}
		void TeleportMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->position = buf->ReadVector3();
			this->rotation = buf->ReadQuaternion();
		}
		TeleportMsg::TeleportMsg()
		{
		}
		String* TeleportMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
