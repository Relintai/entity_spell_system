#ifndef AURA_EFFECT_DATA_H
#define AURA_EFFECT_DATA_H

#include "EffectPoints.h"
#include "EffectLoader.h"
#include "EffectLoaderHelper.h"

class AuraEffectData 
{
    private:
        bool enabled;
        GameObject* effectPrefab;
        int effectId;
        EffectPoints effectPoint1;
        EffectPoints effectPoint2;
        static EffectPoints GetEffectPoint(String* effectPoint);
        static String* GetEffectPointString(EffectPoints effectPoint);
        void OnAuraEffectLoaded(EffectLoaderHelper* he);

    public:
        int getEffectId();
        void setEffectId(int value);
        bool getEnabled();
        void setEnabled(bool value);
        GameObject* getEffectPrefab();
        void setEffectPrefab(GameObject* value);
        EffectPoints getEffectPoint1();
        void setEffectPoint1(EffectPoints value);
        EffectPoints getEffectPoint2();
        void setEffectPoint2(EffectPoints value);
        void Set(String* effectPoint1, String* effectPoint2);
        void LoadEffect();
        void FromJSON(JsonReader* r);
        void ToJSON(JsonWriter* w);
};

#endif
