#include "LootDataAttributeHelper.h"

int LootDataAttributeHelper::getItemId(){
    return this->itemId;
}

void LootDataAttributeHelper::setItemId(int value)
{
    this->itemId = value;
}

float LootDataAttributeHelper::getPercent()
{
    return this->percent;
}

void LootDataAttributeHelper::setPercent(float value)
{
    this->percent = value;
}

LootDataAttributeHelper::LootDataAttributeHelper(int itemId, float percent)
{
    this->setItemId(itemId);
    this->setPercent(percent);
}

