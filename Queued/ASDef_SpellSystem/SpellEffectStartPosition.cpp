#include "SpellEffectStartPosition.h"
Vector3* SpellEffectStartPosition::getStartPosition(){
	return this->startPosition;
}
void SpellEffectStartPosition::setStartPosition(Vector3* value)
{
	this->startPosition->Set(value->x, value->y, value->z);
}
void SpellEffectStartPosition::SetSartPosition(Transform* start)
{
	this->startPosition->Set(start->position->x, start->position->y, start->position->z);
}

