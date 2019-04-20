#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "WorldEntity.h"
#include "Vector2.h"
#include "PositionInterpolationHelper.h"
#include "Queue_T.h"
#include "MyPlayerCommands.h"
#include "CharacterController.h"
#include "KinematicCharacterMotor.h"
#include "CxNet.h"
#include "SimpleNetworkedMovementManager.h"
#include "EntityType.h"
#include "TeleportMsg.h"
#include "SMovementDataMsg.h"
#include "CMovementDataMsg.h"
#include "SPositionDataMsg.h"
#include "CPositionDataMsg.h"

using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace KinematicCharacterController::Walkthrough::NetworkingExample;
using namespace System;
using namespace KinematicCharacterController;
using namespace CxNetworking;
using namespace BS::Networking;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class NetworkedPlayerController : public virtual MonoBehaviour, public virtual Object{
			private:
				WorldEntity* owner;
			private:
				Vector2* moveaxes;
			private:
				float speed;
			private:
				Queue_T<PositionInterpolationHelper>* queuedPositions;
			//Attribute: NonSerialized*
			public:
				MyPlayerCommands CurrentCommands;
			private:
				bool _isLocal;
			private:
				int _id;
			private:
				int _connectionId;
			private:
				bool _hasProcessedTransientCommands;
			private:
				MyPlayerCommands _transientCommands;
			public:
				bool UsePrediction;
			public:
				CharacterController* getCharacterController();
			public:
				void setCharacterController(CharacterController* value);
			public:
				KinematicCharacterMotor* getKinematicCharacterMotor();
			public:
				void setKinematicCharacterMotor(KinematicCharacterMotor* value);
			private:
				void Start();
			public:
				void SendInputs(float axisX, float axisY, float speed);
			public:
				void SendPosition();
			public:
				void OnTeleportMessage(TeleportMsg& msg);
			public:
				void OnSMovementDataMsg(SMovementDataMsg& msg);
			public:
				void OnCMovementDataMsg(CMovementDataMsg& msg);
			public:
				void OnSPositionDataMsg(SPositionDataMsg& msg);
			public:
				void OnCPositionDataMsg(CPositionDataMsg& msg);
			private:
				void Update();
			public:
				CharacterController* CharacterController_var;
			public:
				KinematicCharacterMotor* KinematicCharacterMotor_var;
			public:
				NetworkedPlayerController();
		};
	}
}
