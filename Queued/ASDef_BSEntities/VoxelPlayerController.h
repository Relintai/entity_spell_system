#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Rigidbody.h"
#include "Touchpad.h"
#include "Turnpanel.h"
#include "Vector2.h"
#include "Vector3.h"
#include "WorldEntity.h"
#include "PlayerData.h"
#include "Stats.h"
#include "StateComponent.h"
#include "PlayerFacingComponent.h"
#include "TargetComponent.h"
#include "Rect.h"
#include "RaycastHit2D.h"
#include "Camera.h"
#include "RaycastResult.h"
#include <System/Collections/Generic/List.h>
#include "PointerEventData.h"
#include "GameObject.h"
#include "Collider2D.h"
#include "RaycastHit.h"
#include "Ray.h"
#include "Quaternion.h"
#include "EventSystem.h"
#include "BSSecondaryInputModule.h"
#include "BSState.h"
#include "BrokenSeals.h"
#include "Mathf.h"
#include "Physics.h"
#include "Collider.h"
#include "Stat.h"
#include "BSPointerEventData.h"
#include "Screen.h"

using namespace UnityEngine;
using namespace UnityEngine::EventSystems;
using namespace System::Collections::Generic;
using namespace BS::BSInput;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class VoxelPlayerController : public virtual MonoBehaviour, public virtual Object{
			public:
				float movementSpeed;
			public:
				float ROTATION_SPEED;
			public:
				float JUMP_FORCE;
			public:
				float GRAVITY;
			public:
				float TERMINAL_VELOCITY;
			public:
				float fingerMoveBeforeAimingModeOn;
			public:
				float maxAngleLeewayInSelection;
			public:
				float heightAboveThePlayer;
			public:
				float rotationX;
			public:
				float aimTargetingRange;
			public:
				float gravity;
			public:
				Rigidbody* rigidBody;
			public:
				Touchpad* touchPad;
			public:
				Turnpanel* turnpanel;
			public:
				Vector2* v2tmp1;
			public:
				Vector2* ftmp;
			public:
				Vector2* tmp;
			public:
				Vector2* tmp2;
			public:
				Vector3* v3tmp;
			public:
				Vector3* v3tmp2;
			private:
				WorldEntity* we;
			private:
				PlayerData* pd;
			public:
				Stats* playerStats;
			public:
				StateComponent* stateComponent;
			public:
				PlayerFacingComponent* playerFacing;
			public:
				bool touchInput;
			public:
				TargetComponent* targetComponent;
			public:
				Rect* tcRect;
			public:
				int tcPointer;
			public:
				float tcTime;
			public:
				bool tcDown;
			public:
				int tcButton;
			public:
				Vector2* tcTmpV2;
			public:
				Array<RaycastHit2D>* raycasthit;
			public:
				bool aimingModeOn;
			public:
				Camera* cam;
			private:
				bool menuOpen;
			public:
				List_T<RaycastResult>* raycastResult;
			public:
				PointerEventData* tcPed;
			public:
				List_T<GameObject>* clickThroughGOs;
			public:
				Vector2* circlePosTmp;
			public:
				Array<Collider2D>* circleColliders;
			public:
				Array<RaycastHit>* rcharr;
			private:
				Ray* ray;
			public:
				float originalY;
			public:
				RaycastHit* rch;
			public:
				Vector2* v2tmp;
			public:
				Vector2* v2mtmp;
			public:
				Vector2* aimTmp;
			public:
				Vector2* aim2Tmp;
			public:
				Vector2* aim3Tmp;
			public:
				Vector2* ac1tmp;
			public:
				Vector2* ac2tmp;
			private:
				int LAYER;
			private:
				Quaternion* inputQuaternion;
			private:
				Quaternion* targetQuaternion;
			public:
				Vector2* lastMoveVector;
			public:
				bool didMove;
			private:
				Vector2* mouseMoveDirection;
			private:
				bool mouseMOveDown;
			private:
				Vector2* mouseTargetDirection;
			private:
				bool mouseTargetDown;
			private:
				bool rMouseDOwn;
			private:
				void Start();
			private:
				void Update();
			private:
				void OnDestroy();
			public:
				bool EpsilonEquals(float a, float b);
			public:
				void setMovementSpeed(float ms);
			public:
				bool TryToTarget(float x, float y);
			public:
				void TryToTarget(Vector2* aimVector);
			public:
				void OnSpeedStatChanged(int statId, Stat* stat);
			public:
				float Calculate2DAngle(float fx, float fy, float sx, float sy);
			public:
				void OnPointerDown(PointerEventData* eventData);
			public:
				void OnPointerUp(PointerEventData* eventData);
			public:
				void OnTouchClick(BSPointerEventData* eventData);
			public:
				void BSOnMouseClick(BSPointerEventData* eventData);
			public:
				void BSOnMouseDown(BSPointerEventData* eventData);
			public:
				void BSOnMouseUp(BSPointerEventData* eventData);
			public:
				void BSOnMouseDrag(BSPointerEventData* eventData);
			private:
				void CalculateMouseMoveDirection(float x, float y);
			private:
				void CalculateMouseTargetDirection(float x, float y);
			private:
				void OnIngameMenuChanged(bool open);
			public:
				VoxelPlayerController();
		};
	}
}
