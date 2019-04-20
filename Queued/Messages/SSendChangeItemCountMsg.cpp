#include "SSendChangeItemCountMsg.h"
namespace BS {
	namespace Networking {
		void SSendChangeItemCountMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1045);
			buf->WriteInt(this->SlotId);
			buf->WriteInt(this->Count);
		}
		void SSendChangeItemCountMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SlotId = buf->ReadInt();
			this->Count = buf->ReadInt();
		}
		SSendChangeItemCountMsg::SSendChangeItemCountMsg()
		{
		}
		String* SSendChangeItemCountMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
