#include "GameObjectSpellMgr.h"
namespace BS {
	namespace SpellsNS {
		namespace SpellMgrs {
			int GameObjectSpellMgr::getSpellId(){
				return this->spellId;
			}
			void GameObjectSpellMgr::setSpellId(int value)
			{
				this->spellId = value;
			}
			void GameObjectSpellMgr::Start()
			{
				Entity::RegisterOnLocalPlayerChange(new Entity::OnLocalPlayerChangedAction(this->OnLocalPlayerChanged));
				this->tcRect = ;
				this->v2tmp->Set((float)15, (float)15);
				this->tcRect->size = this->v2tmp;
				this->tcIsMouse = false;
				this->tcPed = new PointerEventData(EventSystem::current);
				this->clickThroughGOs->Add(GameObject::FindGameObjectWithTag(new String("TouchControl"))->transform->Find(new String("Turnpanel"))->gameObject);
				for (int i = 0; i < FakeNetworkBehaviour::transform->childCount; i += 1) {
					this->interact->Add(FakeNetworkBehaviour::transform->GetChild(i)->gameObject);
				}
				if (FakeNetworkBehaviour::transform->childCount == 0) {
					this->interact->Add(FakeNetworkBehaviour::gameObject);
				}
			}
			void GameObjectSpellMgr::CastSpell(WorldEntity* player, GameObject* interactWith)
			{
				Stats* stats = player->Stats;
				if (*player != this->localPlayer) {
					return;
				}
				if (stats->CIsDead) {
					return;
				}
				if (!this->IsInRange(player->gameObject, interactWith)) {
					return;
				}
				this->CmdCastSpell(player, interactWith);
			}
			void GameObjectSpellMgr::CmdCastSpell(WorldEntity* player, GameObject* interactWith)
			{
				Stats* stats = player->Stats;
				if (!this->isServer || stats->sIsDead) {
					return;
				}
				if (!this->IsInRange(player->gameObject, interactWith)) {
					return;
				}
				SpellCastData* spellCastData = player->SpellCastData;
				if (spellCastData == null) {
					Debug::Log(new String("GameObjectSpellMgr->CmdCastSpell: SpellCastData is null!"));
					return;
				}
				spellCastData->SSpellCastGameObject = interactWith;
				SpellMgr::CastSpell(player, this->spellId, (float)1);
			}
			void GameObjectSpellMgr::SCastSpell(WorldEntity* player, GameObject* interactWith)
			{
				Stats* component = player->GetComponent<Stats>();
				if (!this->isServer || component->sIsDead) {
					return;
				}
				if (!this->IsInRange(player->gameObject, interactWith)) {
					return;
				}
				SpellMgr::CastSpell(player, this->spellId, (float)1);
			}
			void GameObjectSpellMgr::AICastSpell(WorldEntity* player, GameObject* interactWith)
			{
				Stats* stats = player->Stats;
				if (!this->isServer || stats->sIsDead) {
					return;
				}
				if (!this->IsInRange(player->gameObject, interactWith)) {
					return;
				}
				SpellMgr::CastSpell(player, this->spellId, (float)1);
			}
			bool GameObjectSpellMgr::IsInRange(GameObject* player, GameObject* interactWith)
			{
				this->tmp->Set(player->transform->position->x, player->transform->position->y, player->transform->position->z);
				this->tmp -= interactWith->transform->position;
				this->tmp->y = (float)0;
				return this->tmp->sqrMagnitude <= (float)25;
			}
			void GameObjectSpellMgr::OnLocalPlayerChanged(Entity* p)
			{
				this->localPlayer = (WorldEntity*)(p);
				this->cam = GameObject::FindGameObjectWithTag(new String("MainCamera"))->GetComponent<Camera>();
			}
			bool GameObjectSpellMgr::TouchDown(float x, float y, int pointer, int button)
			{
				this->OnPointerDown(x, y, pointer, button, false);
				return false;
			}
			bool GameObjectSpellMgr::TouchUp(float x, float y, int pointer, int button)
			{
				this->OnPointerUp(x, y, pointer, button, false);
				return false;
			}
			bool GameObjectSpellMgr::TouchDragged(float x, float y, int pointer, int button)
			{
				return false;
			}
			bool GameObjectSpellMgr::MouseDown(float x, float y, int button)
			{
				this->OnPointerDown(x, y, 0, button, true);
				return false;
			}
			bool GameObjectSpellMgr::MouseUp(float x, float y, int button)
			{
				button = -1;
				this->OnPointerUp(x, y, 0, button, true);
				return false;
			}
			bool GameObjectSpellMgr::MouseDrag(float x, float y, float deltaX, float deltaY, int button)
			{
				return false;
			}
			bool GameObjectSpellMgr::MouseMove(float x, float y, float deltaX, float deltaY)
			{
				return false;
			}
			bool GameObjectSpellMgr::ScrollWheel(float deltaX, float deltaY)
			{
				return false;
			}
			void GameObjectSpellMgr::OnPointerDown(float x, float y, int pointer, int button, bool isMouse)
			{
				this->v2tmp->Set(x, y);
				this->tcRect->center = this->v2tmp;
				this->tcPointer = pointer;
				this->tcTime = (float)0;
				this->tcIsMouse = isMouse;
			}
			void GameObjectSpellMgr::OnPointerUp(float x, float y, int pointer, int button, bool isMouse)
			{
				if (this->tcPointer != pointer) {
					return;
				}
				if (this->tcIsMouse != isMouse) {
					return;
				}
				if (this->tcTime > (float)1) {
					return;
				}
				this->v2tmp->Set(x, y);
				if (this->tcRect->Contains(this->v2tmp)) {
					this->TryToTarget(x, y);
				}
			}
			void GameObjectSpellMgr::TryToTarget(float x, float y)
			{
				if (this->localPlayer == null) {
					return;
				}
				this->v2tmp->Set(x, y);
				this->tcPed->position = this->v2tmp;
				this->raycastResult->Clear();
				EventSystem::current->RaycastAll(this->tcPed, this->raycastResult);
				for (int i = 0; i < this->raycastResult->Count; i += 1) {
					RaycastResult* raycastResult = this->raycastResult->GetData(i);
					int num = 0;
					for (int j = 0; j < this->clickThroughGOs->Count; j += 1) {
						if (raycastResult->gameObject == *(this->clickThroughGOs->GetData(j))) {
							num += 1;
						}
					}
					if (num != this->raycastResult->Count) {
						return;
					}
				}
				this->tmp->Set(x, y, (float)0);
				Ray* ray = this->cam->ScreenPointToRay(this->tmp);
				this->tmp->Set(ray->origin->x, ray->origin->y, ray->origin->z);
				this->tmp2->Set(ray->direction->x, ray->direction->y, ray->direction->z);
				if (Physics::SphereCast(this->tmp, (float)0.5, this->tmp2, this->rch, (float)30)) {
					GameObject* gameObject = this->rch->collider->transform->gameObject;
					for (int k = 0; k < this->interact->Count; k += 1) {
						if (*gameObject == *(this->interact->GetData(k))) {
							this->CastSpell(this->localPlayer, gameObject);
						}
					}
				}
			}
			bool GameObjectSpellMgr::EpsilonEquals(float a, float b)
			{
				return ((a + (float)1E-07) < b) && ((a - (float)1E-07) > b);
			}
			GameObjectSpellMgr::GameObjectSpellMgr()
			{
				interact = new List_T<GameObject>();
				raycastResult = new List_T<RaycastResult>();
				clickThroughGOs = new List_T<GameObject>();
			}

		}
	}
}
