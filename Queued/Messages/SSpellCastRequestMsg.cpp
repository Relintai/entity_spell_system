#include "SSpellCastRequestMsg.h"
namespace BS {
	namespace Networking {
		void SSpellCastRequestMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1020);
			buf->WriteInt(this->SpellId);
		}
		void SSpellCastRequestMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SpellId = buf->ReadInt();
		}
		SSpellCastRequestMsg::SSpellCastRequestMsg()
		{
		}
		String* SSpellCastRequestMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
