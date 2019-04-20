#include "AddCPlayerSpellCooldownDataMsg.h"
namespace BS {
	namespace Networking {
		void AddCPlayerSpellCooldownDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1034);
			buf->WriteInt(this->SpellId);
			buf->WriteFloat(this->Cooldown);
			buf->WriteFloat(this->RemainingCooldown);
		}
		void AddCPlayerSpellCooldownDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SpellId = buf->ReadInt();
			this->Cooldown = buf->ReadFloat();
			this->RemainingCooldown = buf->ReadFloat();
		}
		AddCPlayerSpellCooldownDataMsg::AddCPlayerSpellCooldownDataMsg()
		{
		}
		String* AddCPlayerSpellCooldownDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
