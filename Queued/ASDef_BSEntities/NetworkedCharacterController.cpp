#include "NetworkedCharacterController.h"
namespace BS {
	namespace Player {
		void NetworkedCharacterController::Awake(){
			this->owner = BaseCharacterController::GetComponent<WorldEntity>();
			KinematicCharacterMotor* component = BaseCharacterController::GetComponent<KinematicCharacterMotor>();
			component->CharacterController = this;
			BaseCharacterController::SetupCharacterMotor(component);
			this->playerStats = this->owner->Stats;
			this->playerStats->OnStatChanged += new Stats::OnStatChangeAction(DELEGATE_FUNC(NetworkedCharacterController::OnSpeedStatChanged, _1, _2));
			this->MaxStableMoveSpeed = this->playerStats->CSpeed->Current;
			this->stateComponent = this->owner->StateComponent;
			this->FromInterpolationPoint = InterpolationPoint(Time::time, BaseCharacterController::getMotor()->TransientPosition, BaseCharacterController::getMotor()->TransientRotation);
			this->ToInterpolationPoint = InterpolationPoint(Time::time, BaseCharacterController::getMotor()->TransientPosition, BaseCharacterController::getMotor()->TransientRotation);
		}
		void NetworkedCharacterController::SetCommands(MyPlayerCommands& inputs)
		{
			if (this->IsStunned) {
				this->_moveInputVector = Vector3::zero;
				return;
			}
			this->_moveInputVector = Vector3::ClampMagnitude(new Vector3(inputs.MoveAxisRight, (float)0, inputs.MoveAxisForward), (float)1);
		}
		void NetworkedCharacterController::SetInputs(BotCharacterInputs& inputs)
		{
			if (this->IsStunned) {
				this->_moveInputVector = Vector3::zero;
				return;
			}
			this->_moveInputVector = inputs.MoveVector;
			this->_lookInputVector = inputs.LookVector;
		}
		void NetworkedCharacterController::BeforeCharacterUpdate(float deltaTime)
		{
			if (!CxNet::IsClient) {
				bool flag = this->stateComponent->CHasState(StateData::StateType::TYPE_STUN);
				bool flag2 = this->stateComponent->CHasState(StateData::StateType::TYPE_ROOT);
				if ((this->playerStats->sIsDead | flag) | flag2) {
					this->IsStunned = true;
					return;
				}
				this->IsStunned = false;
			}
		}
		void NetworkedCharacterController::UpdateRotation(Quaternion* currentRotation, float deltaTime)
		{
			currentRotation = Quaternion::identity;
		}
		void NetworkedCharacterController::UpdateVelocity(Vector3* currentVelocity, float deltaTime)
		{
			Vector3* b = Vector3::zero;
			currentVelocity = BaseCharacterController::getMotor()->GetDirectionTangentToSurface(currentVelocity, BaseCharacterController::getMotor()->GroundingStatus->GroundNormal) * currentVelocity->magnitude;
			Vector3* rhs = Vector3::Cross(this->_moveInputVector, BaseCharacterController::getMotor()->CharacterUp);
			b = (Vector3::Cross(BaseCharacterController::getMotor()->GroundingStatus->GroundNormal, rhs)->normalized * this->_moveInputVector->magnitude) * this->MaxStableMoveSpeed;
			currentVelocity = Vector3::Lerp(currentVelocity, b, (float)1 - Mathf::Exp(-this->StableMovementSharpness * deltaTime));
		}
		void NetworkedCharacterController::AfterCharacterUpdate(float deltaTime)
		{
		}
		bool NetworkedCharacterController::IsColliderValidForCollisions(Collider* coll)
		{
			return true;
		}
		void NetworkedCharacterController::OnGroundHit(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, HitStabilityReport& hitStabilityReport)
		{
		}
		void NetworkedCharacterController::OnMovementHit(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, HitStabilityReport& hitStabilityReport)
		{
		}
		void NetworkedCharacterController::PostGroundingUpdate(float deltaTime)
		{
		}
		void NetworkedCharacterController::AddVelocity(Vector3* velocity)
		{
		}
		void NetworkedCharacterController::ProcessHitStabilityReport(Collider* hitCollider, Vector3* hitNormal, Vector3* hitPoint, Vector3* atCharacterPosition, Quaternion* atCharacterRotation, HitStabilityReport& hitStabilityReport)
		{
		}
		void NetworkedCharacterController::OnSpeedStatChanged(int statId, Stat* stat)
		{
			if (statId != 1) {
				return;
			}
			this->MaxStableMoveSpeed = stat->Current;
		}
		int NetworkedCharacterController::GetId()
		{
			return this->Id;
		}
		void NetworkedCharacterController::SetId(int id)
		{
			this->Id = id;
		}
		bool NetworkedCharacterController::GetHasOwnership()
		{
			return this->owner->isLocalPlayer;
		}
		void NetworkedCharacterController::SetHasOwnership(bool hasOwnership)
		{
			this->HasOwnership = hasOwnership;
		}
		uint NetworkedCharacterController::GetEntityGUID()
		{
			return this->owner->PlayerData->GUID;
		}
		NetworkedCharacterController::NetworkedCharacterController()
		{
			MaxStableMoveSpeed = (float)4;
			StableMovementSharpness = (float)1000;
			OrientationSharpness = (float)1000;
			MaxAirMoveSpeed = (float)10;
			AirAccelerationSpeed = (float)5;
			Drag = (float)0.1;
			Gravity = new Vector3((float)0, (float)0, (float)0);
			Id = -1;
			TimeSinceJumpRequested = float.PositiveInfinity;
			StunTimeRemaining = (float)-1;
		}

	}
}
