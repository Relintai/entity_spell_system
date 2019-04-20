#pragma once
#include <System/System.h>

using namespace System;
namespace BS {
	namespace Player {
		//Attribute: Serializable*
		struct CooldownSendSyncVar : public virtual ValueType{
				int spellId;
				float cooldown;
				CooldownSendSyncVar();
				String* ToString();
		};
	}
}
