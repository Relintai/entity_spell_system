#include "PlayerLocalTargetNextPrevSpellData.h"
namespace BS {
	namespace Player {
		PlayerLocalTargetNextPrevSpellData::PlayerLocalTargetNextPrevSpellData(WorldEntity* owner){
			LAYER = 2048;
			rch = new Array<RaycastHit>(100);
			direction = new Vector3((float)0, (float)1, (float)0);
			enemyTargets = new List_T<WorldEntity>();
			this->owner = owner;
			this->tc = owner->GetComponent<TargetComponent>();
		}
		void PlayerLocalTargetNextPrevSpellData::Refresh()
		{
			WorldEntity* cTarget = this->tc->CTarget;
			this->enemyTargetindex = 0;
			this->enemyTargets->Clear();
			int num = Physics::SphereCastNonAlloc(this->owner->transform->position, (float)20, this->direction, this->rch, (float)0, this->LAYER);
			for (int i = 0; i < num; i += 1) {
				RaycastHit* raycastHit = this->rch->GetData(i);
				WorldEntity* component = raycastHit->collider->gameObject->GetComponent<WorldEntity>();
				if (!*component == this->owner) {
					if (*component == *cTarget) {
						this->enemyTargetindex = i;
					}
					this->enemyTargets->Add(component);
				}
			}
		}
		void PlayerLocalTargetNextPrevSpellData::TargetNextEnemy()
		{
			if (this->enemyTargets->Count == 0) {
				return;
			}
			this->enemyTargetindex += 1;
			if (this->enemyTargetindex >= this->enemyTargets->Count) {
				this->enemyTargetindex = 0;
			}
			this->tc->SetTarget(this->enemyTargets->GetData(this->enemyTargetindex));
		}
		void PlayerLocalTargetNextPrevSpellData::TargetPreviousEnemy()
		{
			if (this->enemyTargets->Count == 0) {
				return;
			}
			this->enemyTargetindex -= 1;
			if (this->enemyTargetindex < 0) {
				this->enemyTargetindex = this->enemyTargets->Count - 1;
			}
			this->tc->SetTarget(this->enemyTargets->GetData(this->enemyTargetindex));
		}

	}
}
