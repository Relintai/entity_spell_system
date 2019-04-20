#pragma once
#include <System/System.h>

using namespace System;
namespace KinematicCharacterController {
	namespace Walkthrough {
		namespace NetworkingExample {
			enum class FrameworkNetworkMessageID{
				PlayerCommands = -1000,
				GlobalState,
				CommandRequest
			};
		}
	}
}
