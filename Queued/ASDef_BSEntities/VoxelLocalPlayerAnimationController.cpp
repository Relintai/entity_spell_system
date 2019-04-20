#include "VoxelLocalPlayerAnimationController.h"
namespace BS {
	namespace Player {
		float VoxelLocalPlayerAnimationController::getMaxAnimationSpeed(){
			return this->maxAnimationSpeed;
		}
		void VoxelLocalPlayerAnimationController::setMaxAnimationSpeed(float value)
		{
			this->maxAnimationSpeed = value;
		}
		float VoxelLocalPlayerAnimationController::getRunSpeedMultiplier()
		{
			return this->runSpeedMultiplier;
		}
		void VoxelLocalPlayerAnimationController::setRunSpeedMultiplier(float value)
		{
			this->runSpeedMultiplier = value;
		}
		void VoxelLocalPlayerAnimationController::Awake()
		{
			this->we = MonoBehaviour::GetComponent<WorldEntity>();
			this->playerController = MonoBehaviour::GetComponent<PlayerController>();
			this->spellCastData = this->we->SpellCastData;
			this->targetComp = this->we->TargetComponent;
			this->stateComponent = this->we->StateComponent;
			this->stateComponent->COnStateChanged += new StateComponent::COnStateChangedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::COnStateChanged));
			this->statComponent = this->we->Stats;
			this->statComponent->OnDeath += new Stats::OnDeathAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnDied));
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnCastFailed, _1));
			BrokenSeals::BSState->OnIngameMenuChanged += *(new BSState::OnIngameMenuChangedAction(this->OnIngameMenuChanged));
			this->pd = this->we->PlayerData;
			this->pd->OnWeaponChanged += new PlayerData::OnWeapomChangedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnWeaponChanged, _1));
			DELEGATE_INVOKE(this->OnWeaponChanged, this->pd->weaponData);
			this->t = MonoBehaviour::transform;
		}
		void VoxelLocalPlayerAnimationController::Start()
		{
			ModelMaker* component = MonoBehaviour::GetComponent<ModelMaker>();
			if (component != null) {
				component->addOnModelChanged(new ModelMaker::ModelChangedAction(DELEGATE_FUNC(VoxelLocalPlayerAnimationController::OnUMAChanged, _1)));
				component->Generate();
			}
		}
		void VoxelLocalPlayerAnimationController::Update()
		{
			if (this->animator == null) {
				this->animator = MonoBehaviour::gameObject->GetComponentInChildren<Animator>();
				if (this->animator == null) {
					return;
				}
				this->animator->applyRootMotion = false;
				DELEGATE_INVOKE(this->OnWeaponChanged, this->pd->weaponData);
			}
			if (this->castingDirty) {
				this->animator->SetBool(new String("Turning"), false);
				if (this->casting) {
					this->animator->SetBool(new String("Cast"), true);
					this->castingDirty = false;
				}
				else {
					this->animator->SetBool(new String("Cast"), false);
					this->castingDirty = false;
					if (this->turning) {
						this->animator->SetBool(new String("Turning"), true);
					}
				}
			}
			if (this->menuOpen || this->statComponent->sIsDead) {
				if (this->turning) {
					this->animator->SetBool(new String("Turning"), false);
					this->turning = false;
				}
				if (this->moving) {
					this->moving = false;
					this->animator->SetBool(new String("Moving"), false);
					this->animator->SetFloat(new String("MoveX"), (float)0);
					this->animator->SetFloat(new String("MoveY"), (float)0);
				}
				if (this->hasTurnOffTimer) {
					this->turnOffTimer += Time::deltaTime;
					if (this->turnOffTimer > (float)0.1) {
						this->turnOffTimer = (float)0;
						this->hasTurnOffTimer = false;
						this->animator->SetBool(new String("Turning"), false);
						this->turning = false;
					}
				}
				return;
			}
			this->v2mtmp = this->playerController->LastMoveVector;
			if ((((this->v2mtmp->x <= (float)0.01) && (this->v2mtmp->x >= (float)-0.01)) && (this->v2mtmp->y <= (float)0.01)) && (this->v2mtmp->y >= (float)-0.01)) {
				if (this->moving) {
					this->moving = false;
					this->animator->SetBool(new String("Moving"), false);
					this->animator->SetFloat(new String("MoveX"), (float)0);
					this->animator->SetFloat(new String("MoveY"), (float)0);
				}
				if (this->hasTurnOffTimer) {
					this->turnOffTimer += Time::deltaTime;
					if (this->turnOffTimer > (float)0.1) {
						this->turnOffTimer = (float)0;
						this->hasTurnOffTimer = false;
						this->animator->SetBool(new String("Turning"), false);
						this->turning = false;
					}
				}
				if (Vector3::Distance(this->animator->gameObject->transform->localPosition, this->localPosition) > (float)0.2) {
					this->animator->gameObject->transform->localPosition = this->localPosition;
				}
				this->lastpostmp->Set(this->t->position->x, this->t->position->y, this->t->position->z);
				return;
			}
			if (this->speed == null) {
				this->speed = this->statComponent->CSpeed;
			}
			if (!this->moving) {
				this->moving = true;
				this->animator->SetBool(new String("Moving"), true);
			}
			if (Vector3::Distance(this->animator->gameObject->transform->localPosition, this->localPosition) > (float)0.2) {
				this->animator->gameObject->transform->localPosition = this->localPosition;
			}
			this->animator->SetFloat(new String("MoveX"), this->v2mtmp->x);
			this->animator->SetFloat(new String("MoveY"), this->v2mtmp->y);
			this->turnOffTimer = (float)0;
			this->hasTurnOffTimer = false;
			this->animator->SetBool(new String("Turning"), false);
			this->turning = false;
			Vector3* expr_2E2 = new Vector3(this->v2mtmp->x, (float)0, this->v2mtmp->y);
			float num = expr_2E2->x;
			float newX = expr_2E2->z;
			if (((num < (float)0) && this->overridefacing) && (this->targetComp->CTarget != null)) {
				Vector3* position = this->targetComp->CTarget->transform->position;
				this->overrideTmp->Set(position->x, position->y, position->z);
				this->overrideTmp -= MonoBehaviour::transform->position;
				this->overrideTmp->y = (float)0;
				newX = this->overrideTmp->x;
				num = this->overrideTmp->z;
				this->overrideRemainingTime -= Time::deltaTime;
				this->ftv3->Set(newX, (float)0, num);
				this->ftv3->Normalize();
				this->fq->SetLookRotation(this->ftv3, this->up);
				this->animator->gameObject->transform->rotation = this->fq;
				if (this->overrideRemainingTime <= (float)0) {
					this->overridefacing = false;
				}
			}
			else {
				this->ftv3->Set(newX, (float)0, num);
				this->ftv3->Normalize();
				this->fq->SetLookRotation(this->ftv3, this->up);
				this->animator->gameObject->transform->localRotation = this->fq;
			}
			this->animator->SetFloat(new String("RunSpeed"), (float)1);
			if (this->speed->Current > (float)4.5) {
				this->animator->SetFloat(new String("RunSpeedMultiplier"), ((float)4.5 + ((this->speed->Current - (float)4.5) * (float)0.33)) / (float)4.5);
				return;
			}
			this->animator->SetFloat(new String("RunSpeedMultiplier"), this->speed->Current / (float)4.5);
		}
		void VoxelLocalPlayerAnimationController::Turned(bool turned, float direction)
		{
			if (this->animator == null) {
				return;
			}
			if (this->moving || this->casting) {
				return;
			}
			if (turned) {
				this->animator->SetFloat(new String("TurnDirection"), direction);
				if (turned != this->turning) {
					this->animator->SetBool(new String("Turning"), true);
				}
				this->turning = true;
				if (this->hasTurnOffTimer) {
					this->hasTurnOffTimer = false;
					this->turnOffTimer = (float)0;
					return;
				}
			}
			else {
				if (this->turning && !this->hasTurnOffTimer) {
					this->hasTurnOffTimer = true;
					this->turnOffTimer = (float)0;
				}
			}
		}
		void VoxelLocalPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void VoxelLocalPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void VoxelLocalPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void VoxelLocalPlayerAnimationController::OnCastFinished(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			if (this->animator != null) {
				this->animator->SetBool(new String("Cast"), false);
				this->animator->SetTrigger(new String("SpellFinish1Trigger"));
				this->StartFacingOverride();
			}
			this->casting = false;
			this->castingDirty = false;
		}
		void VoxelLocalPlayerAnimationController::OnDied()
		{
			SoundMgr::StopBus(new String("SpellLoop"));
		}
		void VoxelLocalPlayerAnimationController::OnIngameMenuChanged(bool open)
		{
			this->menuOpen = open;
		}
		void VoxelLocalPlayerAnimationController::TriggerAttack()
		{
			if (this->animator != null) {
				this->animator->SetTrigger(new String("Attack1Trigger"));
				this->StartFacingOverride();
			}
		}
		void VoxelLocalPlayerAnimationController::OnUMAChanged(GameObject* umaGO)
		{
			DELEGATE_INVOKE(this->OnWeaponChanged, this->pd->weaponData);
			DELEGATE_INVOKE(this->COnStateChanged);
		}
		void VoxelLocalPlayerAnimationController::OnWeaponChanged(ItemData* id)
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
		void VoxelLocalPlayerAnimationController::COnStateChanged()
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
		void VoxelLocalPlayerAnimationController::StartFacingOverride()
		{
			this->overridefacing = true;
			this->overrideRemainingTime = this->overridefor;
		}
		void VoxelLocalPlayerAnimationController::OnAnimStopped()
		{
			if (this->moving) {
				this->moving = false;
				this->animator->SetBool(new String("Moving"), false);
				this->animator->SetFloat(new String("MoveX"), (float)0);
				this->animator->SetFloat(new String("MoveY"), (float)0);
			}
		}
		void VoxelLocalPlayerAnimationController::OnAnimStopFinished()
		{
		}
		VoxelLocalPlayerAnimationController::VoxelLocalPlayerAnimationController()
		{
			maxAnimationSpeed = (float)7;
			runSpeedMultiplier = (float)4.21;
			localPosition = new Vector3((float)0, (float)0, (float)0);
			overridefor = (float)0.3;
			up = Vector3::up;
			lastpos = Vector3::zero;
		}

	}
}
