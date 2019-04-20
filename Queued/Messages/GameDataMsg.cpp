#include "GameDataMsg.h"
namespace BS {
	namespace Networking {
		void GameDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1012);
			buf->WriteInt(this->Seed);
		}
		void GameDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Seed = buf->ReadInt();
		}
		GameDataMsg::GameDataMsg()
		{
		}
		String* GameDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
