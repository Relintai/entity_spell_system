#include "SpriteAnimationController.h"
namespace BS {
	namespace Player {
		void SpriteAnimationController::Awake(){
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
		}
		void SpriteAnimationController::Start()
		{
			this->movementRotationQuaternion = Quaternion::Euler((float)0, (float)45, (float)0);
			this->spellCastData = this->owner->SpellCastData;
			this->spellCastData->COnCastStart += new SpellCastData::COnCastStartAction(DELEGATE_FUNC(SpriteAnimationController::OnCastStarted, _1));
			this->spellCastData->COnCastEnded += new SpellCastData::CONCastEndedAction(DELEGATE_FUNC(SpriteAnimationController::OnCastEnded, _1));
			this->spellCastData->COnCastFinished += new SpellCastData::CONCastFinishedAction(DELEGATE_FUNC(SpriteAnimationController::OnCastFinished, _1));
			this->spellCastData->COnCastFailed += new SpellCastData::CONCastFailedAction(DELEGATE_FUNC(SpriteAnimationController::OnCastFailed, _1));
			this->playerController = MonoBehaviour::GetComponent<PlayerController>();
			this->statComponent = this->owner->Stats;
			this->speedStat = this->statComponent->CSpeed;
			this->playerData = this->owner->PlayerData;
			this->weapon = this->playerData->Character->WeaponData->Weapon;
		}
		void SpriteAnimationController::Update()
		{
			if (this->animator == null) {
				this->animator = MonoBehaviour::gameObject->GetComponentInChildren<SpriteAnim>();
				if (this->animator == null) {
					return;
				}
				this->lastpos = MonoBehaviour::transform->position;
			}
			if (this->castingDirty) {
				if (this->casting) {
					this->castingDirty = false;
				}
				else {
					this->castingDirty = false;
				}
			}
			Vector3* vector = *(MonoBehaviour::transform->position) - *(this->lastpos);
			vector = this->movementRotationQuaternion * *vector;
			this->lastpos = MonoBehaviour::transform->position;
			bool arg_BE_0 = this->moving;
			if (vector->sqrMagnitude > (float)0.001) {
				this->moving = true;
			}
			else {
				this->moving = false;
			}
			if (arg_BE_0 != this->moving) {
				if (this->moving) {
					this->animator->PlayAnimation(1, (float)0.06 * (this->speedStat->NomodMax / this->speedStat->Max));
				}
				else {
					this->animator->PlayAnimation(0, (float)0.4);
				}
			}
			if (this->moving) {
				Vector3* localScale = this->animator->gameObject->transform->localScale;
				Vector3* localPosition = this->animator->gameObject->transform->parent->localPosition;
				if (vector->x < (float)-1E-05) {
					localPosition->z = (float)-0.4;
					localScale->x = (float)-1;
				}
				if (vector->x > (float)1E-05) {
					localPosition->z = (float)0.4;
					localScale->x = (float)1;
				}
				this->animator->gameObject->transform->localScale = localScale;
				this->animator->gameObject->transform->parent->localPosition = localPosition;
			}
		}
		void SpriteAnimationController::OnCastStarted(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellLoop"));
			this->casting = true;
			this->castingDirty = true;
		}
		void SpriteAnimationController::OnCastEnded(int spellId)
		{
			SoundMgr::StopBus(new String("SpellLoop"));
			this->casting = false;
			this->castingDirty = true;
		}
		void SpriteAnimationController::OnCastFailed(int spellId)
		{
			SoundMgr::PlaySoundAndForget(new String("SpellFail"));
		}
		void SpriteAnimationController::OnCastFinished(int spellId)
		{
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
		void SpriteAnimationController::TriggerAttack()
		{
		}

	}
}
