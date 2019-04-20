#include "CDamageTakenMsg.h"
namespace BS {
	namespace Networking {
		void CDamageTakenMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1023);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->DealerGuid);
			buf->WriteInt(this->Value);
			buf->WriteBool(this->Crit);
		}
		void CDamageTakenMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->DealerGuid = buf->ReadUInt();
			this->Value = buf->ReadInt();
			this->Crit = buf->ReadBool();
		}
		CDamageTakenMsg::CDamageTakenMsg()
		{
		}
		String* CDamageTakenMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
