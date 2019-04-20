#include "VoxelNetworkedPlayerAnimationController.h"
namespace BS {
	namespace Player {
		float VoxelNetworkedPlayerAnimationController::getMaxAnimationSpeed(){
			return this->maxAnimationSpeed;
		}
		void VoxelNetworkedPlayerAnimationController::setMaxAnimationSpeed(float value)
		{
			this->maxAnimationSpeed = value;
		}
		float VoxelNetworkedPlayerAnimationController::getRunSpeedMultiplier()
		{
			return this->runSpeedMultiplier;
		}
		void VoxelNetworkedPlayerAnimationController::setRunSpeedMultiplier(float value)
		{
			this->runSpeedMultiplier = value;
		}
		void VoxelNetworkedPlayerAnimationController::Start()
		{
			this->we = MonoBehaviour::GetComponent<WorldEntity>();
			this->spellCastData = this->we->SpellCastData;
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnCastFailed, _1));
			this->statComponent = this->we->Stats;
			this->statComponent->OnDeath += new Stats::OnDeathAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnDied));
			this->stateComponent = this->we->StateComponent;
			this->stateComponent->COnStateChanged += new StateComponent::COnStateChangedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::COnStateChanged));
			this->pd = this->we->PlayerData;
			Entity::RegisterOnLocalPlayerChange(new Entity::OnLocalPlayerChangedAction(this->LocalPlayerChanged));
			this->pd->OnWeaponChanged += new PlayerData::OnWeapomChangedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnWeaponChanged, _1));
			DELEGATE_INVOKE(this->OnWeaponChanged, this->pd->weaponData);
			this->t = MonoBehaviour::transform;
		}
		void VoxelNetworkedPlayerAnimationController::Update()
		{
			if (this->lptr == null) {
				return;
			}
			if (!this->umaGenerated) {
				this->tmp->Set(this->lptr->position->x, this->lptr->position->z);
				this->v2mtmp->Set(this->t->position->x, this->t->position->z);
				if (Vector2::Distance(this->tmp, this->v2mtmp) < this->umaGenerateDistance) {
					this->umaGenerated = true;
					ModelMaker* component = MonoBehaviour::GetComponent<ModelMaker>();
					if (component != null) {
						component->addOnModelChanged(new ModelMaker::ModelChangedAction(DELEGATE_FUNC(VoxelNetworkedPlayerAnimationController::OnUMAChanged, _1)));
						component->Generate();
					}
				}
			}
			if (this->animatorGameObjectFound && !this->animatorsEnabled) {
				this->framesSinceLastCheck += 1;
				if (this->framesSinceLastCheck > 15) {
					this->framesSinceLastCheck = 0;
					this->tmp->Set(this->lptr->position->x, this->lptr->position->z);
					this->v2mtmp->Set(this->t->position->x, this->t->position->z);
					if (Vector2::Distance(this->tmp, this->v2mtmp) < this->switchDistance) {
						this->animatorsEnabled = true;
						this->animatorgameObject->SetActive(true);
						DELEGATE_INVOKE(this->OnWeaponChanged, this->itemData);
					}
				}
				return;
			}
			if ((this->animatorGameObjectFound && this->animatorsEnabled) && (this->framesSinceLastCheck > 0)) {
				this->framesSinceLastCheck += 1;
				if (this->framesSinceLastCheck > 15) {
					this->framesSinceLastCheck = 0;
					this->tmp->Set(this->lptr->position->x, this->lptr->position->z);
					this->v2mtmp->Set(this->t->position->x, this->t->position->z);
					if (Vector2::Distance(this->tmp, this->v2mtmp) > this->switchDistance) {
						this->animatorsEnabled = false;
						this->animatorgameObject->SetActive(false);
						return;
					}
				}
			}
			if (this->framesSinceLastCheck == 0) {
				this->framesSinceLastCheck += 1;
			}
			if (this->animator == null) {
				this->animator = MonoBehaviour::gameObject->GetComponentInChildren<Animator>();
				if (this->animator == null) {
					return;
				}
				if (!this->animator->isInitialized) {
					return;
				}
				this->animatorGameObjectFound = true;
				this->animatorgameObject = this->animator->gameObject;
				this->animatorgameObject->transform->localPosition = this->localPosition;
				this->lastpostmp->Set(this->t->position->x, this->t->position->y, this->t->position->z);
				this->animator->applyRootMotion = false;
			}
			if (this->speed == null) {
				this->speed = this->statComponent->CSpeed;
			}
			if (!this->animatorsEnabled) {
				return;
			}
			if (this->castingDirty) {
				if (this->casting) {
					this->animator->SetBool(new String("Cast"), true);
					this->castingDirty = false;
				}
				else {
					this->animator->SetBool(new String("Cast"), false);
					this->castingDirty = false;
				}
			}
			this->v3tmp->Set(this->t->position->x, this->t->position->y, this->t->position->z);
			this->v3tmp -= this->lastpostmp;
			float expr_3D1 = this->v3tmp->magnitude;
			if (expr_3D1 > (float)5E-05) {
				if (!this->moving) {
					this->moving = true;
					this->movingchanged = true;
				}
				if (this->movestopQueued) {
					this->movestopQueued = false;
					this->timeSinceQueue = (float)0;
				}
				this->v3tmp->Normalize();
			}
			else {
				if (this->moving && !this->movestopQueued) {
					this->movestopQueued = true;
					this->timeSinceQueue = (float)0;
				}
			}
			if (this->movestopQueued) {
				this->timeSinceQueue += Time::deltaTime;
				this->v3tmp->Set(this->v3tmp2->x, this->v3tmp2->y, this->v3tmp2->z);
				this->moving = true;
				if (this->timeSinceQueue > (float)0.2) {
					this->movestopQueued = false;
					this->moving = false;
					this->movingchanged = true;
					this->timeSinceQueue = (float)0;
				}
			}
			if (this->movingchanged) {
				this->animator->SetBool(new String("Moving"), this->moving);
			}
			this->animator->SetFloat(new String("RunSpeed"), (float)1);
			if (this->speed->Current > (float)4.5) {
				this->animator->SetFloat(new String("RunSpeedMultiplier"), ((float)4.5 + ((this->speed->Current - (float)4.5) * (float)0.33)) / (float)4.5);
			}
			else {
				this->animator->SetFloat(new String("RunSpeedMultiplier"), this->speed->Current / (float)4.5);
			}
			if (Vector3::Distance(this->animator->gameObject->transform->localPosition, this->localPosition) > (float)0.2) {
				this->animator->gameObject->transform->localPosition = this->localPosition;
			}
			if (expr_3D1 > (float)5E-05) {
				Vector3* view = new Vector3(this->v3tmp->x, (float)0, this->v3tmp->z);
				view->Normalize();
				this->fq->SetLookRotation(view, Vector3::up);
				this->animator->gameObject->transform->localRotation = this->fq;
			}
			this->lastpostmp->Set(this->t->position->x, this->t->position->y, this->t->position->z);
		}
		void VoxelNetworkedPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySound3DAtTransform(new String("SpellLoop"), MonoBehaviour::transform);
			this->casting = true;
			this->castingDirty = true;
		}
		void VoxelNetworkedPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void VoxelNetworkedPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySound3DAtTransform(new String("SpellFail"), MonoBehaviour::transform);
		}
		void VoxelNetworkedPlayerAnimationController::OnDied()
		{
			SoundMgr::StopBus(new String("SpellLoop"));
		}
		void VoxelNetworkedPlayerAnimationController::OnCastFinished(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			if (this->animator != null) {
				this->animator->SetBool(new String("Cast"), false);
				this->animator->SetTrigger(new String("SpellFinish1Trigger"));
			}
			this->casting = false;
			this->castingDirty = false;
		}
		void VoxelNetworkedPlayerAnimationController::OnUMAChanged(GameObject* umaGO)
		{
			DELEGATE_INVOKE(this->OnWeaponChanged, this->pd->weaponData);
			DELEGATE_INVOKE(this->COnStateChanged);
		}
		void VoxelNetworkedPlayerAnimationController::OnWeaponChanged(ItemData* id)
		{
			this->itemData = id;
			if (this->animator == null) {
				return;
			}
			if (this->itemData == null) {
				this->animator->SetInteger(new String("Weapon"), 0);
				this->animator->SetTrigger(new String("ResetWeapon"));
				return;
			}
			this->animator->SetInteger(new String("Weapon"), id->GetAnimatorWeaponType());
			this->animator->SetTrigger(new String("ResetWeapon"));
		}
		void VoxelNetworkedPlayerAnimationController::TriggerAttack()
		{
			if (this->animator != null) {
				this->animator->SetTrigger(new String("Attack1Trigger"));
			}
		}
		void VoxelNetworkedPlayerAnimationController::COnStateChanged()
		{
			if (this->animator == null) {
				return;
			}
			if (this->stateComponent->CHasState(StateData::StateType::TYPE_STUN)) {
				if (!this->stun) {
					this->stun = true;
					this->animator->SetBool(new String("Stun"), true);
					this->animator->SetTrigger(new String("StunTrigger"));
					return;
				}
			}
			else {
				if (this->stun) {
					this->stun = false;
					this->animator->SetBool(new String("Stun"), false);
				}
			}
		}
		void VoxelNetworkedPlayerAnimationController::LocalPlayerChanged(Entity* lp)
		{
			this->localPlayer = lp;
			this->lptr = lp->transform;
		}
		bool VoxelNetworkedPlayerAnimationController::IsInLOS(Transform* p1, Transform* p2)
		{
			this->rchtmp->Set(p2->transform->position->x, p2->transform->position->y, p2->transform->position->z);
			this->rchtmp -= p1->transform->position;
			return Physics::Raycast(p1->transform->position, this->rchtmp, this->rcht, this->rchtmp->magnitude, this->LAYER);
		}
		VoxelNetworkedPlayerAnimationController::VoxelNetworkedPlayerAnimationController()
		{
			maxAnimationSpeed = (float)7;
			runSpeedMultiplier = (float)4.21;
			switchDistance = (float)40;
			umaGenerateDistance = (float)50;
			localPosition = new Vector3((float)0, (float)0, (float)0);
			animatorsEnabled = true;
			LAYER = 1;
		}

	}
}
