#include "SSpellCastStartedMsg.h"
namespace BS {
	namespace Networking {
		void SSpellCastStartedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1015);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->SpellId);
			buf->WriteFloat(this->CastTime);
		}
		void SSpellCastStartedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->SpellId = buf->ReadInt();
			this->CastTime = buf->ReadFloat();
		}
		SSpellCastStartedMsg::SSpellCastStartedMsg()
		{
		}
		String* SSpellCastStartedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
