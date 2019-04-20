#pragma once
#include <System/System.h>
#include "BaseCharacterController.h"
#include "IEntity.h"
#include "Vector3.h"
#include "Transform.h"
#include "PlayerController.h"
#include "InterpolationPoint.h"
#include "Stats.h"
#include "StateComponent.h"
#include "WorldEntity.h"
#include "KinematicCharacterMotor.h"
#include "Time.h"
#include "MyPlayerCommands.h"
#include "BotCharacterInputs.h"
#include "CxNet.h"
#include "StateData.h"
#include "Quaternion.h"
#include "Mathf.h"
#include "Collider.h"
#include "HitStabilityReport.h"
#include "Stat.h"

using namespace KinematicCharacterController;
using namespace KinematicCharacterController::Walkthrough::NetworkingExample;
using namespace UnityEngine;
using namespace System;
using namespace CxNetworking;
namespace BS {
	namespace Player {
		class NetworkedCharacterController : public virtual BaseCharacterController, public virtual IEntity, public virtual Object
		{
			//Attribute: Header*(new String("Stable Movement"))
			public:
				float MaxStableMoveSpeed;
			public:
				float StableMovementSharpness;
			public:
				float OrientationSharpness;
			//Attribute: Header*(new String("Air Movement"))
			public:
				float MaxAirMoveSpeed;
			public:
				float AirAccelerationSpeed;
			public:
				float Drag;
			//Attribute: Header*(new String("Misc"))
			public:
				bool RotationObstruction;
			public:
				Vector3* Gravity;
			public:
				Transform* MeshRoot;
			//Attribute: NonSerialized*
			public:
				PlayerController* OwningPlayer;
			//Attribute: NonSerialized*
			public:
				int Id;
			//Attribute: NonSerialized*
			public:
				bool HasOwnership;
			//Attribute: NonSerialized*
			public:
				InterpolationPoint FromInterpolationPoint;
			//Attribute: NonSerialized*
			public:
				InterpolationPoint ToInterpolationPoint;
			//Attribute: NonSerialized*
			public:
				bool JumpConsumed;
			//Attribute: NonSerialized*
			public:
				float TimeSinceJumpRequested;
			//Attribute: NonSerialized*
			public:
				float TimeSinceLastAbleToJump;
			//Attribute: NonSerialized*
			public:
				bool IsStunned;
			//Attribute: NonSerialized*
			public:
				float StunTimeRemaining;
			private:
				Vector3* _moveInputVector;
			private:
				Vector3* _lookInputVector;
			private:
				bool _jumpRequested;
			private:
				bool _jumpedThisFrame;
			private:
				Stats* playerStats;
			private:
				StateComponent* stateComponent;
			private:
				WorldEntity* owner;
			private:
				void Awake();
			public:
				void SetCommands(MyPlayerCommands& inputs);
			public:
				void SetInputs(BotCharacterInputs& inputs);
			public:
			virtual void BeforeCharacterUpdate(float deltaTime);
			public:
			virtual void UpdateRotation(Quaternion* currentRotation, float deltaTime);
			public:
			virtual void UpdateVelocity(Vector3* currentVelocity, float deltaTime);
			public:
			virtual void AfterCharacterUpdate(float deltaTime);
			public:
			virtual bool IsColliderValidForCollisions(Collider* coll);
			public:
			virtual void OnGroundHit(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, HitStabilityReport& hitStabilityReport);
			public:
			virtual void OnMovementHit(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, HitStabilityReport& hitStabilityReport);
			public:
			virtual void PostGroundingUpdate(float deltaTime);
			public:
				void AddVelocity(Vector3* velocity);
			public:
			virtual void ProcessHitStabilityReport(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, Vector3* atCharacterPosition, Quaternion* atCharacterRotation, HitStabilityReport& hitStabilityReport);
			public:
				void OnSpeedStatChanged(int statId, Stat* stat);
			public:
				int GetId();
			public:
				void SetId(int id);
			public:
				bool GetHasOwnership();
			public:
				void SetHasOwnership(bool hasOwnership);
			public:
				uint GetEntityGUID();
			public:
				NetworkedCharacterController();
		};
	}
}
