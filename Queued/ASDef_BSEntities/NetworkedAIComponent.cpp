#include "NetworkedAIComponent.h"
namespace BS {
	namespace AI {
		int NetworkedAIComponent::getClassID(){
			return this->classID;
		}
		WorldEntity* NetworkedAIComponent::getAggroedTo()
		{
			return AggroedTo_var;
		}
		void NetworkedAIComponent::setAggroedTo(WorldEntity* value)
		{
			AggroedTo_var = value;
		}
		StateComponent* NetworkedAIComponent::getStatec()
		{
			return Statec_var;
		}
		void NetworkedAIComponent::setStatec(StateComponent* value)
		{
			Statec_var = value;
		}
		SpellMgrComponent* NetworkedAIComponent::getSmgr()
		{
			return Smgr_var;
		}
		void NetworkedAIComponent::setSmgr(SpellMgrComponent* value)
		{
			Smgr_var = value;
		}
		TargetComponent* NetworkedAIComponent::getTargetComponent()
		{
			return TargetComponent_var;
		}
		void NetworkedAIComponent::setTargetComponent(TargetComponent* value)
		{
			TargetComponent_var = value;
		}
		SpellCastData* NetworkedAIComponent::getSpellCastData()
		{
			return SpellCastData_var;
		}
		void NetworkedAIComponent::setSpellCastData(SpellCastData* value)
		{
			SpellCastData_var = value;
		}
		Rigidbody* NetworkedAIComponent::getRigidBody()
		{
			return RigidBody_var;
		}
		void NetworkedAIComponent::setRigidBody(Rigidbody* value)
		{
			RigidBody_var = value;
		}
		WorldEntity* NetworkedAIComponent::getTarget()
		{
			return Target_var;
		}
		void NetworkedAIComponent::setTarget(WorldEntity* value)
		{
			Target_var = value;
		}
		AIStates NetworkedAIComponent::getCurrentState()
		{
			return CurrentState_var;
		}
		void NetworkedAIComponent::setCurrentState(AIStates value)
		{
			CurrentState_var = value;
		}
		Stats* NetworkedAIComponent::getStats()
		{
			return Stats_var;
		}
		void NetworkedAIComponent::setStats(Stats* value)
		{
			Stats_var = value;
		}
		PlayerSpellDataComponent* NetworkedAIComponent::getPsdc()
		{
			return Psdc_var;
		}
		void NetworkedAIComponent::setPsdc(PlayerSpellDataComponent* value)
		{
			Psdc_var = value;
		}
		PlayerData* NetworkedAIComponent::getPlayerData()
		{
			return PlayerData_var;
		}
		void NetworkedAIComponent::setPlayerData(PlayerData* value)
		{
			PlayerData_var = value;
		}
		PlayerFacingComponent* NetworkedAIComponent::getPfc()
		{
			return Pfc_var;
		}
		void NetworkedAIComponent::setPfc(PlayerFacingComponent* value)
		{
			Pfc_var = value;
		}
		MobSpellData* NetworkedAIComponent::getMobSpellData()
		{
			return MobSpellData_var;
		}
		void NetworkedAIComponent::setMobSpellData(MobSpellData* value)
		{
			MobSpellData_var = value;
		}
		float NetworkedAIComponent::getGlobalCooldown()
		{
			return GlobalCooldown_var;
		}
		void NetworkedAIComponent::setGlobalCooldown(float value)
		{
			GlobalCooldown_var = value;
		}
		List_T<WorldEntity>* NetworkedAIComponent::getPlayers()
		{
			return this->players;
		}
		NetworkedCharacterController* NetworkedAIComponent::getCharacterController()
		{
			return CharacterController_var;
		}
		void NetworkedAIComponent::setCharacterController(NetworkedCharacterController* value)
		{
			CharacterController_var = value;
		}
		KinematicCharacterMotor* NetworkedAIComponent::getKinematicCharacterMotor()
		{
			return KinematicCharacterMotor_var;
		}
		void NetworkedAIComponent::setKinematicCharacterMotor(KinematicCharacterMotor* value)
		{
			KinematicCharacterMotor_var = value;
		}
		void NetworkedAIComponent::Start()
		{
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
			Entity::OnSNetworkedPlayerAdded += *(new Entity::OnLocalPlayerChangedAction(this->OnPlayerRegistered));
			Entity::OnLocalPlayerChange += *(new Entity::OnLocalPlayerChangedAction(this->OnPlayerRegistered));
			this->setPsdc(this->owner->PlayerSpellDataComponent);
			this->setStats(this->owner->Stats);
			this->setStatec(this->owner->StateComponent);
			this->setSmgr(this->owner->SpellMgrComponent);
			this->setTargetComponent(this->owner->TargetComponent);
			this->setSpellCastData(this->owner->SpellCastData);
			this->setPfc(this->owner->PlayerFacingComponent);
			this->setRigidBody(MonoBehaviour::GetComponent<Rigidbody>());
			this->setCharacterController(MonoBehaviour::GetComponent<NetworkedCharacterController>());
			this->setKinematicCharacterMotor(MonoBehaviour::GetComponent<KinematicCharacterMotor>());
			this->getKinematicCharacterMotor()->enabled = false;
			this->getCharacterController()->enabled = false;
			this->getSpellCastData()->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(NetworkedAIComponent::COnCastEnded, _1));
			this->getStats()->SOnDamageTaken += new Stats::OnDamageTakenAction(DELEGATE_FUNC(NetworkedAIComponent::OnDamageTaken, _1, _2, _3, _4));
			this->setPlayerData(this->owner->PlayerData);
			int classId = this->getPlayerData()->ClassId;
			this->classID = classId;
			this->setMobSpellData(this->getPlayerData()->Character->MobSpellData);
			this->OnPlayerRegistered(null);
			this->SetState(AIStates::STATE_STAND);
		}
		void NetworkedAIComponent::FixedUpdate()
		{
			switch (this->getCurrentState()) {
				case AIStates::STATE_OFF:
					break;

				case AIStates::STATE_STAND:
					this->StateStand();
					break;

				case AIStates::STATE_DEAD:
					this->StateDead();
					return;

				case AIStates::STATE_ATTACK:
					this->StateAttack();
					return;

				default:
					return;
			}
		}
		void NetworkedAIComponent::OnDestroy()
		{
			Entity::OnSNetworkedPlayerAdded -= *(new Entity::OnLocalPlayerChangedAction(this->OnPlayerRegistered));
			Entity::OnLocalPlayerChange -= *(new Entity::OnLocalPlayerChangedAction(this->OnPlayerRegistered));
		}
		void NetworkedAIComponent::SetState(AIStates newState)
		{
			if ((newState == AIStates::STATE_ATTACK) && (this->getCurrentState() != AIStates::STATE_ATTACK)) {
				this->getKinematicCharacterMotor()->enabled = true;
				this->getCharacterController()->enabled = true;
			}
			else {
				if ((newState != AIStates::STATE_ATTACK) && (this->getCurrentState() == AIStates::STATE_ATTACK)) {
					this->getKinematicCharacterMotor()->enabled = false;
					this->getCharacterController()->enabled = false;
				}
			}
			this->setCurrentState(newState);
		}
		void NetworkedAIComponent::StateStand()
		{
			if (this->targetPlayer()) {
				this->SetState(AIStates::STATE_ATTACK);
			}
			ValueStat* sHealth = this->getStats()->SHealth;
			if (sHealth->Current < (sHealth->Max - (float)5)) {
				this->TryToCastSpell(this->getMobSpellData()->RegenerationSpells);
				return;
			}
			BotCharacterInputs botCharacterInputs = BotCharacterInputs();
			botCharacterInputs.MoveVector->x = (float)0;
			botCharacterInputs.MoveVector->y = (float)0;
			this->getCharacterController()->SetInputs(botCharacterInputs);
		}
		void NetworkedAIComponent::StateAttack()
		{
			if (!this->canSeePlayer()) {
				this->setAggroedTo(null);
				this->SetState(AIStates::STATE_STAND);
				return;
			}
			if (this->getTarget() == null) {
				return;
			}
			if (this->getStats()->sIsDead) {
				this->setTarget(null);
				this->getTargetComponent()->AISetTarget(null);
				this->SetState(AIStates::STATE_DEAD);
				return;
			}
			if (this->getTarget()->Stats->sIsDead) {
				this->setTarget(null);
				this->getTargetComponent()->AISetTarget(null);
				if (!this->targetPlayer()) {
					this->setAggroedTo(null);
					this->SetState(AIStates::STATE_DEAD);
					return;
				}
			}
			if (this->getStatec()->SHasState(StateData::StateType::TYPE_STUN) && !this->TryToCastSpell(this->getMobSpellData()->StunBreakSpells)) {
				return;
			}
			this->tmp0->Set(this->getTarget()->transform->position->x, this->getTarget()->transform->position->y, this->getTarget()->transform->position->z);
			this->tmp0 -= MonoBehaviour::transform->position;
			float magnitude = this->tmp0->magnitude;
			if (this->getSpellCastData()->SCasting && this->getTarget()->Stats->sIsDead) {
				this->setTarget(null);
				this->getTargetComponent()->AISetTarget(null);
				this->setAggroedTo(null);
				this->SetState(AIStates::STATE_STAND);
				return;
			}
			if ((!this->getSpellCastData()->SCasting && !this->getStats()->SHasGlobalCooldown) && (magnitude <= (float)1.8)) {
				this->getTargetComponent()->AISetTarget(this->getTarget());
				this->TryToCastSpell(this->getMobSpellData()->AttackSpells);
			}
			if ((!this->getSpellCastData()->SCasting || this->moveWhileCasting) && (magnitude > (float)1.4)) {
				if (magnitude > (float)4) {
					this->TryToCastSpell(this->getMobSpellData()->ChargeSpells);
				}
				this->tmp0->Set(this->getTarget()->transform->position->x, this->getTarget()->transform->position->y, this->getTarget()->transform->position->z);
				this->tmp0 -= MonoBehaviour::transform->position;
				if (this->tmp0->magnitude > (float)1.4) {
					BotCharacterInputs botCharacterInputs = BotCharacterInputs();
					Vector3* normalized = this->tmp0->normalized;
					botCharacterInputs.MoveVector->x = normalized->x;
					botCharacterInputs.MoveVector->y = normalized->z;
					this->getCharacterController()->SetInputs(botCharacterInputs);
					return;
				}
			}
			else {
				BotCharacterInputs botCharacterInputs2 = BotCharacterInputs();
				botCharacterInputs2.MoveVector->x = (float)0;
				botCharacterInputs2.MoveVector->y = (float)0;
				this->getCharacterController()->SetInputs(botCharacterInputs2);
			}
		}
		void NetworkedAIComponent::StateDead()
		{
			this->setTarget(null);
			if (!this->owner->Stats->sIsDead) {
				this->setAggroedTo(null);
				this->SetState(AIStates::STATE_STAND);
			}
			BotCharacterInputs botCharacterInputs = BotCharacterInputs();
			botCharacterInputs.MoveVector->x = (float)0;
			botCharacterInputs.MoveVector->y = (float)0;
			this->getCharacterController()->SetInputs(botCharacterInputs);
		}
		bool NetworkedAIComponent::canSeePlayer()
		{
			if (this->getTarget() != null) {
				this->tmp->Set(this->getTarget()->transform->position->x, this->getTarget()->transform->position->y, this->getTarget()->transform->position->z);
				this->tmp -= MonoBehaviour::transform->position;
				if (this->tmp->magnitude < (float)30) {
					return true;
				}
			}
			return false;
		}
		bool NetworkedAIComponent::targetPlayer()
		{
			for (int i = 0; i < this->players->Count; i += 1) {
				WorldEntity* worldEntity = this->players->GetData(i);
				if (((!worldEntity == null && !worldEntity->transform == MonoBehaviour::transform) && !worldEntity->getStats()->sIsDead) && worldEntity->getFactionComponent()->SIsEnemy(this->owner)) {
					this->tmp->Set(worldEntity->transform->position->x, worldEntity->transform->position->y, worldEntity->transform->position->z);
					this->tmp -= MonoBehaviour::transform->position;
					if ((this->tmp->magnitude < this->aggroRange) && !this->IsInLOS(worldEntity->transform, MonoBehaviour::transform)) {
						this->setAggroedTo(worldEntity);
						this->setTarget(worldEntity);
						this->RequestPath();
						return true;
					}
				}
			}
			return false;
		}
		bool NetworkedAIComponent::IsInLOS(Transform* p1, Transform* p2)
		{
			this->rchtmp->Set(p1->transform->position->x, p1->transform->position->y, p1->transform->position->z);
			this->rchtmp -= p2->transform->position;
			return Physics::Raycast(p2->transform->position, this->rchtmp, this->rcht, this->aggroRange, this->LAYER) && this->rcht->collider->gameObject->CompareTag(new String("Player"));
		}
		void NetworkedAIComponent::RequestPath()
		{
		}
		bool NetworkedAIComponent::IsSpellOnCooldown(int spellId)
		{
			for (int i = 0; i < this->getPsdc()->SSpellData->Count; i += 1) {
				if (this->getPsdc()->SSpellData->GetData(i)->SpellId == spellId) {
					return true;
				}
			}
			return false;
		}
		void NetworkedAIComponent::OnDamageTaken(int damage, bool crit, WorldEntity* receiver, WorldEntity* dealer)
		{
			if (this->getTarget() == null) {
				this->setTarget(dealer);
				this->setAggroedTo(dealer);
				this->SetState(AIStates::STATE_ATTACK);
			}
		}
		void NetworkedAIComponent::OnPlayerRegistered(Entity* p)
		{
			this->players->Clear();
			if (Entity::SNetworkedPlayers->Count > 0) {
				for (int i = 0; i < Entity::SNetworkedPlayers->Count; i += 1) {
					this->players->Add((WorldEntity*)(Entity::SNetworkedPlayers->GetData(i)));
				}
			}
			if (Entity::LocalPlayer != null) {
				this->players->Add((WorldEntity*)(Entity::LocalPlayer));
			}
		}
		bool NetworkedAIComponent::TryToCastSpell(List_T<MobSpellDataEntry>* spells)
		{
			if (this->getStats()->SHasGlobalCooldown) {
				return false;
			}
			for (int i = 0; i < spells->Count; i += 1) {
				MobSpellDataEntry* mobSpellDataEntry = spells->GetData(i);
				if (!this->IsSpellOnCooldown(mobSpellDataEntry->SpellId)) {
					this->getSmgr()->AICastSpell(mobSpellDataEntry->SpellId);
					if (mobSpellDataEntry->MoveWhileCasting && this->getSpellCastData()->SCasting) {
						this->moveWhileCasting = true;
					}
					return true;
				}
			}
			return false;
		}
		void NetworkedAIComponent::COnCastEnded(int spellId)
		{
			if (this->moveWhileCasting) {
				this->moveWhileCasting = false;
			}
		}
		NetworkedAIComponent::NetworkedAIComponent()
		{
			aggroRange = (float)10;
			nextWaypointRange = (float)0.4;
			players = new List_T<WorldEntity>();
			LAYER = 2049;
			canMove = true;
			AggroedTo_var = (WorldEntity*)(0);
			Statec_var = (StateComponent*)(0);
			Smgr_var = (SpellMgrComponent*)(0);
			TargetComponent_var = (TargetComponent*)(0);
			SpellCastData_var = (SpellCastData*)(0);
			RigidBody_var = (Rigidbody*)(0);
			Target_var = (WorldEntity*)(0);
			CurrentState_var = (AIStates)(0);
			Stats_var = (Stats*)(0);
			Psdc_var = (PlayerSpellDataComponent*)(0);
			PlayerData_var = (PlayerData*)(0);
			Pfc_var = (PlayerFacingComponent*)(0);
			MobSpellData_var = (MobSpellData*)(0);
			GlobalCooldown_var = (float)(0);
			CharacterController_var = (NetworkedCharacterController*)(0);
			KinematicCharacterMotor_var = (KinematicCharacterMotor*)(0);
		}

	}
}
