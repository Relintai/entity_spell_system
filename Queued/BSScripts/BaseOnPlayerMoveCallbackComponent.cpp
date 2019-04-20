#include "BaseOnPlayerMoveCallbackComponent.h"
//Delegate declaration moved to header file
void BaseOnPlayerMoveCallbackComponent::addCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value){
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved = this->COnPlayerMove;
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved2;
	do{
		onPlayerMoved2 = onPlayerMoved;
		BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value2 = (BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*)(Delegate::Combine(onPlayerMoved2, value));
		onPlayerMoved = Interlocked::CompareExchange<BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*>(this->COnPlayerMove, value2, onPlayerMoved2);
	}
	while (*onPlayerMoved != *onPlayerMoved2);
}
void BaseOnPlayerMoveCallbackComponent::removeCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value)
{
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved = this->COnPlayerMove;
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved2;
	do {
		onPlayerMoved2 = onPlayerMoved;
		BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value2 = (BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*)(Delegate::Remove(onPlayerMoved2, value));
		onPlayerMoved = Interlocked::CompareExchange<BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*>(this->COnPlayerMove, value2, onPlayerMoved2);
	}
	while (*onPlayerMoved != *onPlayerMoved2);
}

void BaseOnPlayerMoveCallbackComponent::addSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value)
{
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved = this->SOnPlayerMove;
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved2;
	do {
		onPlayerMoved2 = onPlayerMoved;
		BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value2 = (BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*)(Delegate::Combine(onPlayerMoved2, value));
		onPlayerMoved = Interlocked::CompareExchange<BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*>(this->SOnPlayerMove, value2, onPlayerMoved2);
	}
	while (*onPlayerMoved != *onPlayerMoved2);
}
void BaseOnPlayerMoveCallbackComponent::removeSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value)
{
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved = this->SOnPlayerMove;
	BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* onPlayerMoved2;
	do {
		onPlayerMoved2 = onPlayerMoved;
		BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value2 = (BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*)(Delegate::Remove(onPlayerMoved2, value));
		onPlayerMoved = Interlocked::CompareExchange<BaseOnPlayerMoveCallbackComponent::OnPlayerMoved*>(this->SOnPlayerMove, value2, onPlayerMoved2);
	}
	while (*onPlayerMoved != *onPlayerMoved2);
}

public:
	virtual List_T<int>* getCSpells() = 0;
public:
	virtual List_T<int>* getSSpells() = 0;
void BaseOnPlayerMoveCallbackComponent::CallCOnPlayerMove(Entity* player)
{
	if (this->COnPlayerMove != null) {
		DELEGATE_INVOKE(this->COnPlayerMove, player);
	}
}
void BaseOnPlayerMoveCallbackComponent::CallSOnPlayerMove(Entity* player)
{
	if (this->SOnPlayerMove != null) {
		DELEGATE_INVOKE(this->SOnPlayerMove, player);
	}
}
bool BaseOnPlayerMoveCallbackComponent::COnPlayerMoveIsNull()
{
	return this->COnPlayerMove == null;
}
bool BaseOnPlayerMoveCallbackComponent::SOnPlayerMoveIsNull()
{
	return this->SOnPlayerMove == null;
}
BaseOnPlayerMoveCallbackComponent::BaseOnPlayerMoveCallbackComponent()
{
	CSpells_var = (List_T<int>*)(0);
	SSpells_var = (List_T<int>*)(0);
}

