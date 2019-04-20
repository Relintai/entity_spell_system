#include "RemoveCPlayerSpellCooldownDataMsg.h"
namespace BS {
	namespace Networking {
		void RemoveCPlayerSpellCooldownDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1035);
			buf->WriteInt(this->SpellId);
		}
		void RemoveCPlayerSpellCooldownDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SpellId = buf->ReadInt();
		}
		RemoveCPlayerSpellCooldownDataMsg::RemoveCPlayerSpellCooldownDataMsg()
		{
		}
		String* RemoveCPlayerSpellCooldownDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
