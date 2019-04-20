#include "LootDataAttribute.h"

int LootDataAttribute::getMinNum(){
    return this->minNum;
}

void LootDataAttribute::setMinNum(int value)
{
    this->minNum = value;
}

int LootDataAttribute::getMaxNum()
{
    return this->maxNum;
}

void LootDataAttribute::setMaxNum(int value)
{
    this->maxNum = value;
}

List_T<LootDataAttributeHelper>* LootDataAttribute::getData()
{
    return this->data;
}

void LootDataAttribute::setData(List_T<LootDataAttributeHelper>* value)
{
    this->data = value;
}

void LootDataAttribute::Set(int minNum, int maxNum)
{
    this->setMinNum(minNum);
    this->setMaxNum(maxNum);
    List_T<LootDataAttributeHelper>* arg_33_0 = this->data;
    Comparison_T<LootDataAttributeHelper>* arg_33_1;
    if (arg_33_1 = LootDataAttribute::<>c::<>9__12_0 == null) {
        arg_33_1 = LootDataAttribute::<>c::<>9__12_0 = new Comparison_T<LootDataAttributeHelper>(LootDataAttribute::<>c::<>9-><Set>b__12_0);
    }
    arg_33_0->Sort(arg_33_1);
}

LootDataAttribute::LootDataAttribute()
{
    data = new List_T<LootDataAttributeHelper>();
}

