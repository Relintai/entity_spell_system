#include "CSendRequestRankIncreaseMsg.h"
namespace BS {
	namespace Networking {
		void CSendRequestRankIncreaseMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1041);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->TalentId);
		}
		void CSendRequestRankIncreaseMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->TalentId = buf->ReadInt();
		}
		CSendRequestRankIncreaseMsg::CSendRequestRankIncreaseMsg()
		{
		}
		String* CSendRequestRankIncreaseMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
