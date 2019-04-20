#include "CommandRequestMsg.h"
namespace KinematicCharacterController {
	namespace Walkthrough {
		namespace NetworkingExample {
			void CommandRequestMsg::Serialize(SerializationBuffer* buf){
				buf->SeekZero();
				buf->WriteInt(-998);
				buf->WriteUInt(this->ForPlayerId);
				buf->WriteInt(this->ForTick);
			}
			void CommandRequestMsg::Deserialize(SerializationBuffer* buf)
			{
				this->ForPlayerId = buf->ReadUInt();
				this->ForTick = buf->ReadInt();
			}
			CommandRequestMsg::CommandRequestMsg()
			{
			}
			String* CommandRequestMsg::ToString()
			{
				return new String(CURRENT_TYPE);
			}

		}
	}
}
