#include "SSendTeamMsg.h"
namespace BS {
	namespace Networking {
		void SSendTeamMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1037);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->Team);
		}
		void SSendTeamMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Team = buf->ReadInt();
		}
		SSendTeamMsg::SSendTeamMsg()
		{
		}
		String* SSendTeamMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
