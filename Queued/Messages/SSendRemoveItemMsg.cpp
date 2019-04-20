#include "SSendRemoveItemMsg.h"
namespace BS {
	namespace Networking {
		void SSendRemoveItemMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1046);
			buf->WriteInt(this->SlotId);
		}
		void SSendRemoveItemMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SlotId = buf->ReadInt();
		}
		SSendRemoveItemMsg::SSendRemoveItemMsg()
		{
		}
		String* SSendRemoveItemMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
