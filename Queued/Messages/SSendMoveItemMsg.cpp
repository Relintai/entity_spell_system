#include "SSendMoveItemMsg.h"
namespace BS {
	namespace Networking {
		void SSendMoveItemMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1047);
			buf->WriteInt(this->Slot1);
			buf->WriteInt(this->Slot2);
		}
		void SSendMoveItemMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Slot1 = buf->ReadInt();
			this->Slot2 = buf->ReadInt();
		}
		SSendMoveItemMsg::SSendMoveItemMsg()
		{
		}
		String* SSendMoveItemMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
