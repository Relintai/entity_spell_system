#pragma once
#include <System/System.h>
#include "FakeNetworkBehaviour.h"
#include "WorldEntity.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include "Camera.h"
#include "Rect.h"
#include "RaycastResult.h"
#include "PointerEventData.h"
#include "RaycastHit.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Entity.h"
#include "EventSystem.h"
#include "Stats.h"
#include "SpellCastData.h"
#include "Debug.h"
#include "SpellMgr.h"
#include "Ray.h"
#include "Physics.h"

using namespace UnityEngine;
using namespace BS::Player;
using namespace System::Collections::Generic;
using namespace UnityEngine::EventSystems;
using namespace System;
namespace BS {
	namespace SpellsNS {
		namespace SpellMgrs {
			class GameObjectSpellMgr : public virtual FakeNetworkBehaviour, public virtual Object
			{
				//Attribute: SerializeField*
				private:
					int spellId;
				private:
					WorldEntity* localPlayer;
				private:
					List_T<GameObject>* interact;
				private:
					Camera* cam;
				private:
					Rect* tcRect;
				private:
					int tcPointer;
				private:
					float tcTime;
				private:
					bool tcIsMouse;
				private:
					List_T<RaycastResult>* raycastResult;
				private:
					PointerEventData* tcPed;
				private:
					List_T<GameObject>* clickThroughGOs;
				private:
					RaycastHit* rch;
				private:
					Vector2* v2tmp;
				private:
					Vector3* tmp;
				private:
					Vector3* tmp2;
				public:
					int getSpellId();
				public:
					void setSpellId(int value);
				public:
				virtual void Start();
				public:
					void CastSpell(WorldEntity* player, GameObject* interactWith);
				public:
					void CmdCastSpell(WorldEntity* player, GameObject* interactWith);
				public:
					void SCastSpell(WorldEntity* player, GameObject* interactWith);
				public:
					void AICastSpell(WorldEntity* player, GameObject* interactWith);
				private:
					bool IsInRange(GameObject* player, GameObject* interactWith);
				private:
					void OnLocalPlayerChanged(Entity* p);
				public:
					bool TouchDown(float x, float y, int pointer, int button);
				public:
					bool TouchUp(float x, float y, int pointer, int button);
				public:
					bool TouchDragged(float x, float y, int pointer, int button);
				public:
					bool MouseDown(float x, float y, int button);
				public:
					bool MouseUp(float x, float y, int button);
				public:
					bool MouseDrag(float x, float y, float deltaX, float deltaY, int button);
				public:
					bool MouseMove(float x, float y, float deltaX, float deltaY);
				public:
					bool ScrollWheel(float deltaX, float deltaY);
				public:
					void OnPointerDown(float x, float y, int pointer, int button, bool isMouse);
				public:
					void OnPointerUp(float x, float y, int pointer, int button, bool isMouse);
				public:
					void TryToTarget(float x, float y);
				public:
					bool EpsilonEquals(float a, float b);
				public:
					GameObjectSpellMgr();
			};
		}
	}
}
