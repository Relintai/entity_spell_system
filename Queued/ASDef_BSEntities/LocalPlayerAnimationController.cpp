#include "LocalPlayerAnimationController.h"
namespace BS {
	namespace Player {
		void LocalPlayerAnimationController::Start(){
			this->movementRotationQuaternion = Quaternion::Euler((float)0, (float)45, (float)0);
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
			this->spellCastData = this->owner->SpellCastData;
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(LocalPlayerAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(LocalPlayerAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(LocalPlayerAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(LocalPlayerAnimationController::OnCastFailed, _1));
			this->speedStat = this->owner->Stats->CSpeed;
			this->weapon = CharacterWeaponDataTypes::Sword;
			this->playerController = MonoBehaviour::GetComponent<PlayerController>();
		}
		void LocalPlayerAnimationController::Update()
		{
			if (this->animators == null) {
				this->animators = MonoBehaviour::gameObject->GetComponentsInChildren<Animator>();
				if (this->animators == null) {
					return;
				}
				this->pgd = this->animators->GetData(0)->gameObject->GetComponent<Puppet2D_GlobalControl>();
				for (int i = 0; i < this->animators->Length; i += 1) {
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
			bool flag = false;
			Vector3* vector = *(MonoBehaviour::transform->position) - *(this->lastpos);
			vector = this->movementRotationQuaternion * *vector;
			*vector *= this->speedStat->Current * (float)5;
			this->lastpos = MonoBehaviour::transform->position;
			this->v2mtmp->x = vector->x;
			this->v2mtmp->y = vector->z;
			bool arg_135_0 = this->moving;
			if (vector->sqrMagnitude > (float)0.001) {
				flag = true;
				this->moving = true;
			}
			else {
				this->moving = false;
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
		}
		void LocalPlayerAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void LocalPlayerAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void LocalPlayerAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void LocalPlayerAnimationController::OnCastFinished(int spellId)
		{
			for (int i = 0; i < this->animators->Length; i += 1) {
				this->animators->GetData(i)->SetBool(new String("casting"), false);
				if (this->moving && (this->weapon != CharacterWeaponDataTypes::Bow)) {
					CharacterWeaponDataTypes arg_30_0 = this->weapon;
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
		void LocalPlayerAnimationController::TriggerAttack()
		{
		}
		LocalPlayerAnimationController::LocalPlayerAnimationController()
		{
			lastpos = Vector3::zero;
		}

	}
}
