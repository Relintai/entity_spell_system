#include "NetworkedPlayerAnimationController.h"
namespace BS {
	namespace Player {
		void NetworkedPlayerAnimationController::Start(){
			this->we = MonoBehaviour::GetComponent<WorldEntity>();
			this->spellCastData = this->we->SpellCastData;
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(NetworkedPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(NetworkedPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(NetworkedPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(NetworkedPlayerAnimationController::OnCastFailed, _1));
			Entity::RegisterOnLocalPlayerChange(new Entity::OnLocalPlayerChangedAction(this->LocalPlayerChanged));
			this->weapon = CharacterWeaponDataTypes::Sword;
			this->speedStat = this->we->Stats->CSpeed;
			this->t = MonoBehaviour::transform;
		}
		void NetworkedPlayerAnimationController::Update()
		{
			if (this->lptr == null) {
				return;
			}
			if (this->animatorGameObjectFound && !this->animatorsEnabled) {
				this->framesSinceLastCheck += 1;
				if (this->framesSinceLastCheck > 15) {
					this->framesSinceLastCheck = 0;
					this->tmp->Set(this->lptr->position->x, this->lptr->position->z);
					this->v2mtmp->Set(this->t->position->x, this->t->position->z);
					if (Vector2::Distance(this->tmp, this->v2mtmp) < (float)30) {
						this->animatorsEnabled = true;
						this->animatorgameObject->SetActive(true);
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
					if (Vector2::Distance(this->tmp, this->v2mtmp) > (float)30) {
						this->animatorsEnabled = false;
						this->animatorgameObject->SetActive(false);
						return;
					}
				}
			}
			if (this->framesSinceLastCheck == 0) {
				this->framesSinceLastCheck += 1;
			}
			if (this->animators == null) {
				this->animators = MonoBehaviour::gameObject->GetComponentsInChildren<Animator>();
				if (this->animators == null) {
					return;
				}
				for (int i = 0; i < this->animators->Length; i += 1) {
					if (!this->animators->GetData(i)->isInitialized) {
						this->animators = null;
						return;
					}
				}
				this->pgd = this->animators->GetData(0)->gameObject->GetComponent<Puppet2D_GlobalControl>();
				this->animatorgameObject = this->animators->GetData(0)->gameObject;
				this->animatorGameObjectFound = true;
			}
			if (!this->animatorsEnabled) {
				return;
			}
			if (this->castingDirty) {
				if (this->casting) {
					for (int j = 0; j < this->animators->Length; j += 1) {
						this->animators->GetData(j)->SetBool(new String("casting"), true);
						this->castingDirty = false;
					}
				}
				else {
					for (int k = 0; k < this->animators->Length; k += 1) {
						this->animators->GetData(k)->SetBool(new String("casting"), false);
						this->castingDirty = false;
					}
				}
			}
			this->v2mtmp->Set(this->t->position->x, this->t->position->y);
			this->v2mtmp -= this->lastpostmp;
			bool flag = false;
			if (this->v2mtmp->sqrMagnitude > (float)5E-05) {
				flag = true;
				this->moving = true;
				this->wasMoving = true;
				this->v2mtmp->Normalize();
				this->tmp2->Set(this->v2mtmp->x, this->v2mtmp->y);
			}
			else {
				if (this->wasMoving) {
					this->wasMoving = false;
					this->movestopQueued = true;
					this->timeSinceQueue = (float)0;
				}
				this->v2mtmp->Set((float)0, (float)0);
			}
			if (this->movestopQueued) {
				this->timeSinceQueue += Time::deltaTime;
				this->v2mtmp->Set(this->tmp2->x, this->tmp2->y);
				if (this->timeSinceQueue > (float)0.07) {
					this->movestopQueued = false;
					this->moving = false;
					this->v2mtmp->Set((float)0, (float)0);
				}
			}
			for (int l = 0; l < this->animators->Length; l += 1) {
				Animator* animator = this->animators->GetData(l);
				animator->SetFloat(new String("x"), Mathf::Abs(this->v2mtmp->x) > Mathf::Abs(this->v2mtmp->y) ? this->v2mtmp->x : this->v2mtmp->y);
				animator->SetFloat(new String("y"), this->v2mtmp->y);
				animator->SetFloat(new String("Speed"), this->speedStat->Current / (float)3);
				animator->SetBool(new String("moving"), this->moving);
				if (this->moving) {
					Vector3* localScale = animator->gameObject->transform->localScale;
					if ((this->v2mtmp->x < (float)-0.0001) && !this->pgd->flip) {
						this->pgd->flip = true;
					}
					if ((this->v2mtmp->x > (float)0.0001) && this->pgd->flip) {
						this->pgd->flip = false;
					}
					animator->gameObject->transform->localScale = localScale;
				}
				if (flag) {
					animator->SetFloat(new String("lastx"), this->v2mtmp->x);
					animator->SetFloat(new String("lasty"), this->v2mtmp->y);
				}
			}
			this->lastpostmp->Set(this->t->position->x, this->t->position->y);
		}
		void NetworkedPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void NetworkedPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void NetworkedPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void NetworkedPlayerAnimationController::OnCastFinished(int spellId)
		{
			for (int i = 0; i < this->animators->Length; i += 1) {
				Animator* animator = this->animators->GetData(i);
				animator->SetBool(new String("casting"), false);
				if (this->moving) {
					if (this->weapon == CharacterWeaponDataTypes::Bow) {
						animator->SetTrigger(new String("Shoot"));
					}
					else {
						if (this->weapon == CharacterWeaponDataTypes::Sword) {
							animator->SetTrigger(new String("Swing"));
						}
					}
				}
			}
			if (this->weapon == CharacterWeaponDataTypes::Bow) {
				SoundMgr::PlaySoundAndForget(new String("Bow"));
			}
			else {
				if (this->weapon == CharacterWeaponDataTypes::Sword) {
					SoundMgr::PlaySoundAndForget(new String("MHit"));
				}
				else {
					SoundMgr::PlaySoundAndForget(new String("SpellEnd"));
				}
			}
			this->casting = false;
			this->castingDirty = false;
		}
		void NetworkedPlayerAnimationController::LocalPlayerChanged(Entity* lp)
		{
			this->localPlayer = lp;
			this->lptr = lp->transform;
		}
		void NetworkedPlayerAnimationController::TriggerAttack()
		{
		}
		NetworkedPlayerAnimationController::NetworkedPlayerAnimationController()
		{
			animatorsEnabled = true;
		}

	}
}
