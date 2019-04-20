#include "SSendClearMsg.h"
namespace BS {
	namespace Networking {
		void SSendClearMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1038);
			buf->WriteUInt(this->Guid);
		}
		void SSendClearMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		SSendClearMsg::SSendClearMsg()
		{
		}
		String* SSendClearMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
