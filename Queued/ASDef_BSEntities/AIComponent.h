#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "WorldEntity.h"
#include <System/Collections/Generic/List.h>
#include "Vector3.h"
#include "Vector2.h"
#include "RaycastHit.h"
#include "StateComponent.h"
#include "SpellMgrComponent.h"
#include "TargetComponent.h"
#include "SpellCastData.h"
#include "Rigidbody.h"
#include "AIStates.h"
#include "Stats.h"
#include "PlayerSpellDataComponent.h"
#include "PlayerData.h"
#include "PlayerFacingComponent.h"
#include "MobSpellData.h"
#include "BS.h"
#include "KinematicCharacterMotor.h"
#include "NetworkedPlayerController.h"
#include "Entity.h"
#include "ValueStat.h"
#include "PlayerCharacterInputs.h"
#include "StateData.h"
#include "Transform.h"
#include "Physics.h"
#include "MobSpellDataEntry.h"

using namespace UnityEngine;
using namespace BS::Player;
using namespace System::Collections::Generic;
using namespace KinematicCharacterController;
using namespace System;
namespace BS {
	namespace AI {
		//Forward Declaration
		class WorldEntity;

		class AIComponent : public virtual MonoBehaviour, public virtual Object{
			//Attribute: SerializeField*
			private:
				float aggroRange;
			//Attribute: SerializeField*
			private:
				float nextWaypointRange;
			//Attribute: SerializeField*
			private:
				int classID;
			private:
				bool moveWhileCasting;
			private:
				List_T<WorldEntity>* players;
			public:
				Vector3* tmp;
			public:
				Vector3* tmp0;
			public:
				Vector3* tmp2;
			public:
				Vector2* v2tmp;
			public:
				Vector3* ftmp;
			private:
				Vector3* lastPathEnd;
			private:
				int currentWaypointIndex;
			private:
				bool lookingForPath;
			private:
				WorldEntity* owner;
			private:
				Vector3* rchtmp;
			private:
				RaycastHit* rcht;
			private:
				int LAYER;
			private:
				bool grounded;
			private:
				bool canMove;
			public:
				int getClassID();
				//Ignored empty method declaration
			public:
				WorldEntity* getAggroedTo();
			public:
				void setAggroedTo(WorldEntity* value);
			public:
				StateComponent* getStatec();
			public:
				void setStatec(StateComponent* value);
			public:
				SpellMgrComponent* getSmgr();
			public:
				void setSmgr(SpellMgrComponent* value);
			public:
				TargetComponent* getTargetComponent();
			public:
				void setTargetComponent(TargetComponent* value);
			public:
				SpellCastData* getSpellCastData();
			public:
				void setSpellCastData(SpellCastData* value);
			public:
				Rigidbody* getRigidBody();
			public:
				void setRigidBody(Rigidbody* value);
			public:
				WorldEntity* getTarget();
			public:
				void setTarget(WorldEntity* value);
			public:
				AIStates getCurrentState();
			public:
				void setCurrentState(AIStates value);
			public:
				Stats* getStats();
			public:
				void setStats(Stats* value);
			public:
				PlayerSpellDataComponent* getPsdc();
			public:
				void setPsdc(PlayerSpellDataComponent* value);
			public:
				PlayerData* getPlayerData();
			public:
				void setPlayerData(PlayerData* value);
			public:
				PlayerFacingComponent* getPfc();
			public:
				void setPfc(PlayerFacingComponent* value);
			public:
				MobSpellData* getMobSpellData();
			public:
				void setMobSpellData(MobSpellData* value);
			public:
				float getGlobalCooldown();
			public:
				void setGlobalCooldown(float value);
			public:
				List_T<WorldEntity>* getPlayers();
				//Ignored empty method declaration
			public:
				BS::Player::CharacterController* getCharacterController();
			public:
				void setCharacterController(BS::Player::CharacterController* value);
			public:
				KinematicCharacterMotor* getKinematicCharacterMotor();
			public:
				void setKinematicCharacterMotor(KinematicCharacterMotor* value);
			public:
				NetworkedPlayerController* getNetworkedPlayerController();
			public:
				void setNetworkedPlayerController(NetworkedPlayerController* value);
			private:
				void Start();
			private:
				void FixedUpdate();
			private:
				void OnDestroy();
			public:
				void SetState(AIStates newState);
			public:
			virtual void StateStand();
			public:
			virtual void StateAttack();
			public:
			virtual void StateDead();
			public:
				bool canSeePlayer();
			public:
				bool targetPlayer();
			private:
				bool IsInLOS(Transform* p1, Transform* p2);
			private:
				void RequestPath();
			public:
				bool IsSpellOnCooldown(int spellId);
			public:
				void OnDamageTaken(int damage, bool crit, WorldEntity* receiver, WorldEntity* dealer);
			private:
				void OnPlayerRegistered(Entity* p);
			private:
				bool TryToCastSpell(List_T<MobSpellDataEntry>* spells);
			private:
				void COnCastEnded(int spellId);
			public:
				WorldEntity* AggroedTo_var;
			public:
				StateComponent* Statec_var;
			public:
				SpellMgrComponent* Smgr_var;
			public:
				TargetComponent* TargetComponent_var;
			public:
				SpellCastData* SpellCastData_var;
			public:
				Rigidbody* RigidBody_var;
			public:
				WorldEntity* Target_var;
			public:
				AIStates CurrentState_var;
			public:
				Stats* Stats_var;
			public:
				PlayerSpellDataComponent* Psdc_var;
			public:
				PlayerData* PlayerData_var;
			public:
				PlayerFacingComponent* Pfc_var;
			public:
				MobSpellData* MobSpellData_var;
			public:
				float GlobalCooldown_var;
			public:
				BS::Player::CharacterController* CharacterController_var;
			public:
				KinematicCharacterMotor* KinematicCharacterMotor_var;
			public:
				NetworkedPlayerController* NetworkedPlayerController_var;
			public:
				AIComponent();
		};
	}
}
