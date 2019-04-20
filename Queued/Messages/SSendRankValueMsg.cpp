#include "SSendRankValueMsg.h"
namespace BS {
	namespace Networking {
		void SSendRankValueMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1043);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->TalentId);
			buf->WriteInt(this->Rank);
		}
		void SSendRankValueMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->TalentId = buf->ReadInt();
			this->Rank = buf->ReadInt();
		}
		SSendRankValueMsg::SSendRankValueMsg()
		{
		}
		String* SSendRankValueMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
