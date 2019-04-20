#include "SSendSentItemsMsg.h"
namespace BS {
	namespace Networking {
		void SSendSentItemsMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1048);
			buf->WriteString(this->Items);
		}
		void SSendSentItemsMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Items = buf->ReadString();
		}
		SSendSentItemsMsg::SSendSentItemsMsg()
		{
		}
		String* SSendSentItemsMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
