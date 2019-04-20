#include "SSendStateFlagsMsg.h"
namespace BS {
	namespace Networking {
		void SSendStateFlagsMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1036);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->Flags);
		}
		void SSendStateFlagsMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Flags = buf->ReadInt();
		}
		SSendStateFlagsMsg::SSendStateFlagsMsg()
		{
		}
		String* SSendStateFlagsMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
