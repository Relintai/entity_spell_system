#include "VoxelPlayerController.h"
namespace BS {
	namespace Player {
		void VoxelPlayerController::Start(){
			this->tcRect = ;
			this->v2tmp->Set((float)15, (float)15);
			this->tcRect->size = this->v2tmp;
			this->rigidBody = MonoBehaviour::GetComponent<Rigidbody>();
			this->tcDown = false;
			this->tcPed = new PointerEventData(EventSystem::current);
			this->cam = GameObject::FindGameObjectWithTag(new String("MainCamera"))->GetComponent<Camera>();
			this->originalY = MonoBehaviour::transform->position->y;
			this->we = MonoBehaviour::GetComponent<WorldEntity>();
			this->playerStats = this->we->Stats;
			this->playerStats->OnStatChanged += new Stats::OnStatChangeAction(DELEGATE_FUNC(VoxelPlayerController::OnSpeedStatChanged, _1, _2));
			this->movementSpeed = this->playerStats->CSpeed->Current;
			this->stateComponent = this->we->StateComponent;
			this->targetComponent = this->we->TargetComponent;
			this->playerFacing = this->we->PlayerFacingComponent;
			this->pd = this->we->PlayerData;
			BSSecondaryInputModule* expr_113 = BSSecondaryInputModule::GetInstance();
			expr_113->OnTouchClick += *(new BSSecondaryInputModule::OnBSSecondaryInputEvent(this->OnTouchClick));
			expr_113->OnMouseClick += *(new BSSecondaryInputModule::OnBSSecondaryInputEvent(this->BSOnMouseClick));
			BSState::GetInstance()->OnIngameMenuChanged += *(new BSState::OnIngameMenuChangedAction(this->OnIngameMenuChanged));
			this->ray->direction = new Vector3((float)0, (float)0, (float)1);
			this->inputQuaternion = Quaternion::Euler((float)0, (float)-45, (float)0);
			this->targetQuaternion = Quaternion::Euler((float)0, (float)-22.5, (float)0);
		}
		void VoxelPlayerController::Update()
		{
			if (this->touchPad == null) {
				this->touchPad = BrokenSeals::UI->Touchpad;
				this->turnpanel = BrokenSeals::UI->Turnpanel;
				if (this->turnpanel != null) {
					this->clickThroughGOs->Add(this->turnpanel->gameObject);
				}
			}
		}
		void VoxelPlayerController::OnDestroy()
		{
			BSSecondaryInputModule* instance = BSSecondaryInputModule::GetInstance();
			if ((instance != null) && !instance->IsDestroyed()) {
				instance->OnTouchClick -= *(new BSSecondaryInputModule::OnBSSecondaryInputEvent(this->OnTouchClick));
				instance->OnMouseClick -= *(new BSSecondaryInputModule::OnBSSecondaryInputEvent(this->BSOnMouseClick));
			}
		}
		bool VoxelPlayerController::EpsilonEquals(float a, float b)
		{
			return (((a + Mathf::Epsilon) >= b) && ((a - Mathf::Epsilon) <= b)) || (((b + Mathf::Epsilon) >= a) && ((b - Mathf::Epsilon) <= a));
		}
		void VoxelPlayerController::setMovementSpeed(float ms)
		{
			this->movementSpeed = ms;
		}
		bool VoxelPlayerController::TryToTarget(float x, float y)
		{
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
					return false;
				}
			}
			this->v3tmp->Set(x, y, (float)0);
			Vector3* vector = BrokenSeals::Instance->MainCamera->ScreenToWorldPoint(this->v3tmp);
			this->v2tmp->Set(vector->x, vector->y);
			int num2 = Physics::SphereCastNonAlloc(this->cam->ScreenPointToRay(new Vector3(x, y, (float)0)), (float)1.5, this->rcharr, float.PositiveInfinity, 2048);
			bool flag = false;
			for (int k = 0; k < num2; k += 1) {
				RaycastHit* raycastHit = this->rcharr->GetData(k);
				if (((raycastHit->collider->transform->gameObject->GetComponent<WorldEntity>() != null) && (this->targetComponent != null)) && (raycastHit->collider->gameObject != MonoBehaviour::gameObject)) {
					this->targetComponent->SetTarget(raycastHit->collider->transform->gameObject->GetComponent<WorldEntity>());
					flag = true;
				}
			}
			if (!flag && (this->targetComponent != null)) {
				this->targetComponent->SetTarget(null);
				return false;
			}
			return true;
		}
		void VoxelPlayerController::TryToTarget(Vector2* aimVector)
		{
			Vector3* vector = new Vector3(aimVector->x, (float)0, aimVector->y);
			vector = this->targetQuaternion * *vector;
			aimVector->x = vector->x;
			aimVector->y = vector->z;
			Vector3* origin = new Vector3(MonoBehaviour::transform->position->x, MonoBehaviour::transform->position->y, MonoBehaviour::transform->position->z - (float)10000);
			this->ray->origin = origin;
			int num = Physics::SphereCastNonAlloc(this->ray, this->aimTargetingRange, this->rcharr, float.PositiveInfinity, 2048);
			Collider* collider = null;
			float num2 = (float)1000;
			for (int i = 0; i < num; i += 1) {
				Collider* collider2 = this->rcharr->GetData(i)->collider;
				if ((collider2->gameObject->GetComponent<Stats>() != null) && !collider2->gameObject == MonoBehaviour::gameObject) {
					this->aim2Tmp->Set(collider2->gameObject->transform->position->x, collider2->gameObject->transform->position->z);
					this->aim3Tmp->Set(MonoBehaviour::transform->position->x, MonoBehaviour::transform->position->z);
					this->aim2Tmp -= this->aim3Tmp;
					this->aim2Tmp->Normalize();
					float num3 = this->Calculate2DAngle(this->aim2Tmp->x, this->aim2Tmp->y, aimVector->x, aimVector->y);
					if (((num3 > -this->maxAngleLeewayInSelection) && (num3 < this->maxAngleLeewayInSelection)) && (num3 < num2)) {
						num2 = num3;
						collider = collider2;
					}
				}
			}
			if (collider != null) {
				this->targetComponent->SetTarget(collider->gameObject->GetComponent<WorldEntity>());
				return;
			}
			this->targetComponent->SetTarget(null);
		}
		void VoxelPlayerController::OnSpeedStatChanged(int statId, Stat* stat)
		{
			if (statId != 1) {
				return;
			}
			this->movementSpeed = stat->Current;
		}
		float VoxelPlayerController::Calculate2DAngle(float fx, float fy, float sx, float sy)
		{
			this->ac1tmp->Set(fx, fy);
			this->ac2tmp->Set(sx, sy);
			float x = Vector2::Dot(this->ac1tmp, this->ac2tmp);
			return Mathf::Atan2((this->ac1tmp->x * this->ac2tmp->y) - (this->ac1tmp->y * this->ac2tmp->x), x) * (float)57.29578;
		}
		void VoxelPlayerController::OnPointerDown(PointerEventData* eventData)
		{
			this->tcDown = true;
			this->tcPointer = eventData->pointerId;
			this->tcButton = (int)(eventData->button);
			this->tcTime = (float)0;
			this->tcRect->x = eventData->position->x;
			this->tcRect->y = eventData->position->y;
		}
		void VoxelPlayerController::OnPointerUp(PointerEventData* eventData)
		{
			if (((this->tcTime < (float)0.1) && (this->tcPointer == eventData->pointerId)) && (this->tcButton == (int)(eventData->button))) {
				this->tcTmpV2->Set(eventData->position->x, eventData->position->y);
				if (this->tcRect->Contains(this->tcTmpV2)) {
					this->TryToTarget(eventData->position->x, eventData->position->y);
				}
			}
			this->tcDown = false;
		}
		void VoxelPlayerController::OnTouchClick(BSPointerEventData* eventData)
		{
			this->TryToTarget(eventData->position->x, eventData->position->y);
		}
		void VoxelPlayerController::BSOnMouseClick(BSPointerEventData* eventData)
		{
			if (eventData->button == BSPointerEventData::InputButton::Right) {
				this->TryToTarget(eventData->position->x, eventData->position->y);
			}
		}
		void VoxelPlayerController::BSOnMouseDown(BSPointerEventData* eventData)
		{
			if (eventData->button == BSPointerEventData::InputButton::Right) {
				this->rMouseDOwn = true;
				if (!this->TryToTarget(eventData->position->x, eventData->position->y)) {
					this->CalculateMouseTargetDirection(eventData->position->x, eventData->position->y);
					this->TryToTarget(this->mouseTargetDirection);
				}
				return;
			}
			if (eventData->button == BSPointerEventData::InputButton::Left) {
				this->mouseMOveDown = true;
				this->CalculateMouseMoveDirection(eventData->position->x, eventData->position->y);
			}
		}
		void VoxelPlayerController::BSOnMouseUp(BSPointerEventData* eventData)
		{
			if (eventData->button == BSPointerEventData::InputButton::Right) {
				this->mouseTargetDown = false;
				this->rMouseDOwn = false;
				return;
			}
			if (eventData->button == BSPointerEventData::InputButton::Left) {
				this->mouseMOveDown = false;
			}
		}
		void VoxelPlayerController::BSOnMouseDrag(BSPointerEventData* eventData)
		{
			if (this->rMouseDOwn && (eventData->button == BSPointerEventData::InputButton::Right)) {
				this->CalculateMouseTargetDirection(eventData->position->x, eventData->position->y);
				this->TryToTarget(this->mouseTargetDirection);
				return;
			}
			if (this->mouseMOveDown && (eventData->button == BSPointerEventData::InputButton::Left)) {
				this->CalculateMouseMoveDirection(eventData->position->x, eventData->position->y);
			}
		}
		void VoxelPlayerController::CalculateMouseMoveDirection(float x, float y)
		{
			Vector2* a = new Vector2(x, y);
			Vector2* vector = new Vector2((float)(Screen::width), (float)(Screen::height));
			*vector /= (float)2;
			*a -= *vector;
			a->Normalize();
			this->mouseMoveDirection = a;
		}
		void VoxelPlayerController::CalculateMouseTargetDirection(float x, float y)
		{
			Vector2* a = new Vector2(x, y);
			Vector2* vector = new Vector2((float)(Screen::width), (float)(Screen::height));
			*vector /= (float)2;
			*a -= *vector;
			a->Normalize();
			this->mouseTargetDirection = a;
		}
		void VoxelPlayerController::OnIngameMenuChanged(bool open)
		{
			this->menuOpen = open;
		}
		VoxelPlayerController::VoxelPlayerController()
		{
			ROTATION_SPEED = (float)100;
			JUMP_FORCE = (float)0.15;
			GRAVITY = (float)-0.7;
			TERMINAL_VELOCITY = (float)-20;
			fingerMoveBeforeAimingModeOn = (float)15;
			maxAngleLeewayInSelection = (float)40;
			heightAboveThePlayer = (float)30;
			rotationX = (float)56;
			aimTargetingRange = (float)20;
			touchInput = true;
			raycasthit = new Array<RaycastHit2D>(10);
			raycastResult = new List_T<RaycastResult>();
			clickThroughGOs = new List_T<GameObject>();
			circleColliders = new Array<Collider2D>(100);
			rcharr = new Array<RaycastHit>(100);
			LAYER = 2048;
			lastMoveVector = Vector2::zero;
			mouseMoveDirection = Vector2::zero;
			mouseTargetDirection = Vector2::zero;
		}

	}
}
