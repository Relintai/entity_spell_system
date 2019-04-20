#include "OldLocalPlayerAnimationController.h"
namespace BS {
	namespace Player {
		void OldLocalPlayerAnimationController::Start(){
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
			this->rPlayer = ReInput::players->GetPlayer(0);
			this->spellCastData = this->owner->SpellCastData;
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(OldLocalPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(OldLocalPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(OldLocalPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(OldLocalPlayerAnimationController::OnCastFailed, _1));
			this->weapon = CharacterWeaponDataTypes::Sword;
			this->weaponTypeAsInt = 1;
		}
		void OldLocalPlayerAnimationController::Update()
		{
			if (this->animators == null) {
				this->animators = MonoBehaviour::gameObject->GetComponentsInChildren<Animator>();
				if (this->animators == null) {
					return;
				}
				for (int i = 0; i < this->animators->Length; i += 1) {
					this->animators->GetData(i)->SetInteger(new String("weapontype"), this->weaponTypeAsInt);
				}
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
			this->v2mtmp->Set(this->rPlayer->GetAxisRaw(new String("Move Horizontal")), this->rPlayer->GetAxisRaw(new String("Move Vertical")));
			bool flag = false;
			if (this->v2mtmp->sqrMagnitude > (float)0.2) {
				flag = true;
				this->moving = true;
			}
			else {
				this->moving = false;
			}
			for (int l = 0; l < this->animators->Length; l += 1) {
				Animator* animator = this->animators->GetData(l);
				animator->SetFloat(new String("x"), this->v2mtmp->x);
				animator->SetFloat(new String("y"), this->v2mtmp->y);
				if (flag) {
					animator->SetFloat(new String("lastx"), this->v2mtmp->x);
					animator->SetFloat(new String("lasty"), this->v2mtmp->y);
				}
			}
		}
		void OldLocalPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void OldLocalPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void OldLocalPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void OldLocalPlayerAnimationController::OnCastFinished(int spellId)
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
		void OldLocalPlayerAnimationController::TriggerAttack()
		{
		}

	}
}
