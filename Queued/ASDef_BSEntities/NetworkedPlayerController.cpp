#include "NetworkedPlayerController.h"
namespace BS {
	namespace Player {
		CharacterController* NetworkedPlayerController::getCharacterController(){
			return CharacterController_var;
		}
		void NetworkedPlayerController::setCharacterController(CharacterController* value)
		{
			CharacterController_var = value;
		}
		KinematicCharacterMotor* NetworkedPlayerController::getKinematicCharacterMotor()
		{
			return KinematicCharacterMotor_var;
		}
		void NetworkedPlayerController::setKinematicCharacterMotor(KinematicCharacterMotor* value)
		{
			KinematicCharacterMotor_var = value;
		}
		void NetworkedPlayerController::Start()
		{
			this->setCharacterController(MonoBehaviour::GetComponent<CharacterController>());
			this->setKinematicCharacterMotor(MonoBehaviour::GetComponent<KinematicCharacterMotor>());
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
			if (CxNet::IsServer) {
				SimpleNetworkedMovementManager::getInstance()->OnSPlayerAdded(this->owner, this);
			}
			if (CxNet::IsClient) {
				SimpleNetworkedMovementManager::getInstance()->OnCPlayerAdded(this->owner, this);
			}
			if ((!CxNet::IsServer && !this->owner->isLocalPlayer) || ((CxNet::IsServer && !this->owner->isLocalPlayer) && (this->owner->Type == EntityType::Player))) {
				this->getKinematicCharacterMotor()->enabled = false;
				this->getCharacterController()->enabled = false;
			}
		}
		void NetworkedPlayerController::SendInputs(float axisX, float axisY, float speed)
		{
			if (CxNet::IsServer) {
				SimpleNetworkedMovementManager::getInstance()->SendInputsToClients(axisX, axisY, speed, this->owner->PlayerData->GUID, this->owner->Connection);
			}
			if (CxNet::IsClient && this->owner->isLocalPlayer) {
				SimpleNetworkedMovementManager::getInstance()->SendInputToServer(axisX, axisY, speed);
			}
		}
		void NetworkedPlayerController::SendPosition()
		{
			if (CxNet::IsServer) {
				SimpleNetworkedMovementManager::getInstance()->SendPositionToClients(MonoBehaviour::transform, this->owner->PlayerData->GUID, this->owner->Connection);
			}
			if (CxNet::IsClient && this->owner->isLocalPlayer) {
				SimpleNetworkedMovementManager::getInstance()->SendPositionToServer(MonoBehaviour::transform);
			}
		}
		void NetworkedPlayerController::OnTeleportMessage(TeleportMsg& msg)
		{
			bool arg_05_0 = CxNet::IsClient;
		}
		void NetworkedPlayerController::OnSMovementDataMsg(SMovementDataMsg& msg)
		{
			this->moveaxes = msg.Axes;
			this->speed = msg.Speed;
		}
		void NetworkedPlayerController::OnCMovementDataMsg(CMovementDataMsg& msg)
		{
			this->moveaxes = msg.Axes;
			this->speed = msg.Speed;
		}
		void NetworkedPlayerController::OnSPositionDataMsg(SPositionDataMsg& msg)
		{
			PositionInterpolationHelper item = PositionInterpolationHelper();
			item.position = msg.Position;
			item.rotation = msg.Rotation;
			this->queuedPositions->Enqueue(item);
		}
		void NetworkedPlayerController::OnCPositionDataMsg(CPositionDataMsg& msg)
		{
			PositionInterpolationHelper item = PositionInterpolationHelper();
			item.position = msg.Position;
			item.rotation = msg.Rotation;
			this->queuedPositions->Enqueue(item);
		}
		void NetworkedPlayerController::Update()
		{
			if (((!CxNet::IsServer && !this->owner->isLocalPlayer) || ((CxNet::IsServer && !this->owner->isLocalPlayer) && (this->owner->Type == EntityType::Player))) && (this->queuedPositions->Count > 0)) {
				PositionInterpolationHelper positionInterpolationHelper = this->queuedPositions->Dequeue();
				MonoBehaviour::transform->position = positionInterpolationHelper.position;
				MonoBehaviour::transform->localRotation = positionInterpolationHelper.rotation;
			}
		}
		NetworkedPlayerController::NetworkedPlayerController()
		{
			queuedPositions = new Queue_T<PositionInterpolationHelper>();
			_isLocal = true;
			_id = -1;
			_connectionId = -1;
			CharacterController_var = (CharacterController*)(0);
			KinematicCharacterMotor_var = (KinematicCharacterMotor*)(0);
		}

	}
}
