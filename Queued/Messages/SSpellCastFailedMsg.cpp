#include "SSpellCastFailedMsg.h"
namespace BS {
	namespace Networking {
		void SSpellCastFailedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1017);
			buf->WriteUInt(this->Guid);
		}
		void SSpellCastFailedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		SSpellCastFailedMsg::SSpellCastFailedMsg()
		{
		}
		String* SSpellCastFailedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
