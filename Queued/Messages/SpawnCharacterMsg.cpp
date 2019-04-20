#include "SpawnCharacterMsg.h"
namespace BS {
	namespace Networking {
		void SpawnCharacterMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1007);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->ClassId);
			buf->WriteInt((int)(this->Type));
			buf->WriteBool(this->IsLocalPlayer);
			buf->WriteVector3(this->SpawnPosition);
			buf->WriteQuaternion(this->SpawnRotation);
			buf->WriteString(this->Name);
		}
		void SpawnCharacterMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->ClassId = buf->ReadInt();
			this->Type = (EntityType)(buf->ReadInt());
			this->IsLocalPlayer = buf->ReadBool();
			this->SpawnPosition = buf->ReadVector3();
			this->SpawnRotation = buf->ReadQuaternion();
			this->Name = buf->ReadString();
		}
		SpawnCharacterMsg::SpawnCharacterMsg()
		{
		}
		String* SpawnCharacterMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
