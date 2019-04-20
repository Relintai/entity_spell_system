#ifndef LOOT_DATA_ATTRIBUTE_HELPER_H
#define LOOT_DATA_ATTRIBUTE_HELPER_H

class LootDataAttributeHelper 
{
    private:
        int itemId;
        float percent;

    public:
        int getItemId();
        void setItemId(int value);
        float getPercent();
        void setPercent(float value);
        LootDataAttributeHelper(int itemId, float percent);
}

#endif
