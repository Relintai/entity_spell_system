#ifndef LOOT_DATA_ATTRIBUTE_H
#define LOOT_DATA_ATTRIBUTE_H

#include "LootDataAttribute.h"
#include "LootDataAttributeHelper.h"

class LootDataAttribute 
{
    private:
        int minNum;
        int maxNum;
        List_T<LootDataAttributeHelper>* data;

    public:
        class <>c : public virtual Object
        {
            public:
                static LootDataAttribute::<>c* <>9 = new LootDataAttribute::<>c();
            public:
                static Comparison_T<LootDataAttributeHelper>* <>9__12_0;
            public:
                int <Set>b__12_0(LootDataAttributeHelper* a, LootDataAttributeHelper* b)
                {
                    if (a->getPercent() == b->getPercent()) {
                        return 0;
                    }
                    if (a->getPercent() > b->getPercent()) {
                        return 1;
                    }
                    return -1;
                }
        };

        int getMinNum();
        void setMinNum(int value);
        int getMaxNum();
        void setMaxNum(int value);
        List_T<LootDataAttributeHelper>* getData();
        void setData(List_T<LootDataAttributeHelper>* value);
        void Set(int minNum, int maxNum);
        LootDataAttribute();
};

#endif
