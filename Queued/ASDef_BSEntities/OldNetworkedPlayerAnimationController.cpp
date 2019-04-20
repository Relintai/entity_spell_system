#include "OldNetworkedPlayerAnimationController.h"
namespace BS {
	namespace Player {
		void OldNetworkedPlayerAnimationController::Awake(){
			this->spellCastData = MonoBehaviour::GetComponent<SpellCastData>();
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(OldNetworkedPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(OldNetworkedPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(OldNetworkedPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(OldNetworkedPlayerAnimationController::OnCastFailed, _1));
		}
		void OldNetworkedPlayerAnimationController::Start()
		{
			this->cam = BrokenSeals::Instance->MainCamera->transform;
			this->weapon = CharacterWeaponDataTypes::Sword;
			this->weaponTypeAsInt = 1;
			this->t = MonoBehaviour::transform;
			Rigidbody2D* expr_35 = MonoBehaviour::GetComponent<Rigidbody2D>();
			expr_35->angularVelocity = (float)0;
			expr_35->constraints = expr_35->constraints | RigidbodyConstraints2D::FreezeRotation;
		}
		void OldNetworkedPlayerAnimationController::Update()
		{
			if (this->animatorGameObjectFound && !this->animatorsEnabled) {
				this->framesSinceLastCheck += 1;
				if (this->framesSinceLastCheck > 15) {
					this->framesSinceLastCheck = 0;
					this->tmp->Set(this->cam->position->x, this->cam->position->y);
					this->v2mtmp->Set(this->t->position->x, this->t->position->y);
					if (Vector2::Distance(this->tmp, this->v2mtmp) < (float)14) {
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
					this->tmp->Set(this->cam->position->x, this->cam->position->y);
					this->v2mtmp->Set(this->t->position->x, this->t->position->y);
					if (Vector2::Distance(this->tmp, this->v2mtmp) > (float)14) {
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
				for (int j = 0; j < this->animators->Length; j += 1) {
					this->animators->GetData(j)->SetInteger(new String("weapontype"), this->weaponTypeAsInt);
				}
				for (int k = 0; k < MonoBehaviour::transform->childCount; k += 1) {
					if (MonoBehaviour::transform->GetChild(k)->name == *(new String("Graphic"))) {
						this->animatorGameObjectFound = true;
						this->animatorgameObject = MonoBehaviour::transform->GetChild(k)->gameObject;
					}
				}
			}
			if (!this->animatorsEnabled) {
				return;
			}
			if (this->castingDirty) {
				if (this->casting) {
					for (int l = 0; l < this->animators->Length; l += 1) {
						this->animators->GetData(l)->SetBool(new String("casting"), true);
						this->castingDirty = false;
					}
				}
				else {
					for (int m = 0; m < this->animators->Length; m += 1) {
						this->animators->GetData(m)->SetBool(new String("casting"), false);
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
			for (int n = 0; n < this->animators->Length; n += 1) {
				Animator* animator = this->animators->GetData(n);
				animator->SetFloat(new String("x"), this->v2mtmp->x);
				animator->SetFloat(new String("y"), this->v2mtmp->y);
				if (flag) {
					animator->SetFloat(new String("lastx"), this->v2mtmp->x);
					animator->SetFloat(new String("lasty"), this->v2mtmp->y);
				}
			}
			this->lastpostmp->Set(this->t->position->x, this->t->position->y);
		}
		void OldNetworkedPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void OldNetworkedPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void OldNetworkedPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void OldNetworkedPlayerAnimationController::OnCastFinished(int spellId)
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
		void OldNetworkedPlayerAnimationController::TriggerAttack()
		{
		}
		OldNetworkedPlayerAnimationController::OldNetworkedPlayerAnimationController()
		{
			animatorsEnabled = true;
		}

	}
}
