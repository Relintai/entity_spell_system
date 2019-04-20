#include "CHealTakenMsg.h"
namespace BS {
	namespace Networking {
		void CHealTakenMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1024);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->DealerGuid);
			buf->WriteInt(this->Value);
			buf->WriteBool(this->Crit);
		}
		void CHealTakenMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->DealerGuid = buf->ReadUInt();
			this->Value = buf->ReadInt();
			this->Crit = buf->ReadBool();
		}
		CHealTakenMsg::CHealTakenMsg()
		{
		}
		String* CHealTakenMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
