#ifndef I_EFFECT_POINT_HELPER_H
#define I_EFFECT_POINT_HELPER_H

class IEffectPointGetter 
{
    public:
    enum class EffectPoints{
        NONE,
        WEAPON,
        BASE,
        BODY,
        RIGHT_HAND,
        LEFT_HAND,
        HEAD,
        RIGHT_EYE,
        LEFT_EYE
    };

    virtual Transform* GetEffectPoint(EffectPoints bodyPartEffectPoint) = 0;
};

#endif
