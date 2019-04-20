#include "SSendSentCraftMaterialsMsg.h"
namespace BS {
	namespace Networking {
		void SSendSentCraftMaterialsMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1053);
			buf->WriteString(this->Materials);
		}
		void SSendSentCraftMaterialsMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Materials = buf->ReadString();
		}
		SSendSentCraftMaterialsMsg::SSendSentCraftMaterialsMsg()
		{
		}
		String* SSendSentCraftMaterialsMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
