#include "CooldownSendSyncVar.h"
namespace BS {
	namespace Player {
		CooldownSendSyncVar::CooldownSendSyncVar(){
		}
		String* CooldownSendSyncVar::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
