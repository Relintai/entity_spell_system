#include "CSendRequestRankDecreaseMsg.h"
namespace BS {
	namespace Networking {
		void CSendRequestRankDecreaseMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1042);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->TalentId);
		}
		void CSendRequestRankDecreaseMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->TalentId = buf->ReadInt();
		}
		CSendRequestRankDecreaseMsg::CSendRequestRankDecreaseMsg()
		{
		}
		String* CSendRequestRankDecreaseMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
