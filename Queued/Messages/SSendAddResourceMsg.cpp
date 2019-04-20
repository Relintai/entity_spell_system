#include "SSendAddResourceMsg.h"
namespace BS {
	namespace Networking {
		void SSendAddResourceMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1040);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->Type);
		}
		void SSendAddResourceMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Type = buf->ReadInt();
		}
		SSendAddResourceMsg::SSendAddResourceMsg()
		{
		}
		String* SSendAddResourceMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
