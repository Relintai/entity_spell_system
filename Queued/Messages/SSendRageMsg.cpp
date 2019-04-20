#include "SSendRageMsg.h"
namespace BS {
	namespace Networking {
		void SSendRageMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1039);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->Current);
		}
		void SSendRageMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Current = buf->ReadInt();
		}
		SSendRageMsg::SSendRageMsg()
		{
		}
		String* SSendRageMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
